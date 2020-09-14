---
title: Log Book
created: '2020-03-11T09:53:48.064Z'
modified: '2020-09-14T14:27:59.626Z'
---

# Log Book

## Week 11

### 10/3-2020
Installed and started to learn how to use docker. I went through the docker toturial [Get Started](https://docs.docker.com/get-started/) which made sure that docker was installed correctly, it also goes into dockerfiles.
I also watched and followed [Docker Beginner Tutorial](https://www.youtube.com/watch?v=wi-MGFhrad0&list=PLhW3qG5bs-L99pQsZ74f-LC-tOEsBp2rK) on youtube which went into a bit detail on some of the docker functions

## 11/3-2020
Started reading the content on https://docs.docker.com/develop/develop-images/dockerfile_best-practices/

Up after https://docs.docker.com/network/bridge/ and https://docs.docker.com/storage/storagedriver/

## Week 13
I have made a dockerfile, based on the ubuntu image, which has the cyclonedds library installed and all the necessary programs to make it work. Some of the biggest issuse were to install cmake, since at first I tried to install it from scratch as I could not find it with apt-get install, but after running an apt-get update I could, but this was after I had almost installed it from scratch in the dockerfile. After cmake was installed it was just a question of which programs were missing, I found these by manually trying to install the library in the docker container, the missing programs were maven and java development kit. The dockerfile copies the cyclonedds repository from my PC instead of installing git to download it from github. I ended up using a bashscript to installl the library as I had problems with excuting the makefiles in the correct dictoreis from the dockerfile.

### 31/3-2020
I have so far been able to make a two containers made from the same image communicate with eachother througt dds with the roundtrip and helloworld examples in the cyclonedds library, as of now I am not able to communicate the same way from my computer to a docker container.
I have now uploaded code to the STM32-E407 board from a windows machine through the micro-USB with the arduino IDE by following the steps in the "STM32-E407 development board - USER’S MANUAL" (STM32-E407.pdf) on page 23. I had issues getting the PC to recognize the board, but by installing the driver with the Zadig Installer and setting up the boot pins the PC recognized the board. Than I got an upload error from the IDE(Cannot open DFU device 0483:df11) it turned out the I also needed the STM32 Bootloader which I also installed from Zadig. After this there were no more issues and the example code (Blink_LED) works on the board. Next step would most likely be to do the same but througt the ARM-USB-OCD-H on a Linux machine instead of the micro-USB on a Windows machine

### 2/4-2020
I tried to program the STM32 from the JTAG using openOCD with the projekt and command I was given by Kasper. It seems like the JTAG can't see/is not connected to the board correclty as I get the same error when running the command wether the JTAG is plugged into the board or not.

### 3/4-2020
It seems that I have established a connection between the JTAG and the board now. The problem seems to have been the boot mode, both system Memory and embedded SRAM seems to give a connection, but I have choosen to use the system memory since the other one give a few more lines which seems to be connection related. My new problem is now that when openOCD tries to write to the board it gives three warnings saying that "no flash bank found for address" on "10000000", "1006e358", "1006e9d2" which I at the moment presumes is something in the code or something with the jumpers. I'm gonna look into it in the manuel, but if I can't find I'll have to write to Bart and/or Kasper and ask if they know whats wrong since I was given the demo by Kasper 

## Week 34

### 18/8-2020
Meeting with Thor.

Stopped working with the STM32-E407. The compliere workspace's Docker can start up and I have been unable to make the remote-container extension rebuild the container, I can make the container with docker itself. I started to setup the raspberry pi's with a ubuntu server.

### 20/8-2020
Meeting with Bart. Talked about the choice of going over to the pi's instead of the STM32-E407, desided that I could go back to the board later, but work on the pi's for now in order to start understanding and learning about the DDS protocol. Bart came up with different tests that I could perform with the pi's.

Borrow a raspberry pi 3 from Thor to test wifi. Found a few guide on how to setup a pi on eduroam, I have not implemented any yet, some of the guides seems to specific to work for my case.

Ordered wifi dongles and ethernet cables for the pi's

### 21/8-2020
Got the raspberry pi 3 connected to the internet on my home network both cabled and wireless. Installed the required software for cycloneDDS to work.

Received the dongles and cables

## Week 35

### 24/8-2020
Tried to setup the raspberry pi 2's with the wifi dongles. The pi does not recognise the usb dongle as a wifi adapter. I found a [repository](https://github.com/kelebek333/rtl8188fu/tree/arm#how-to-install-for-arm-devices) thourgh a few forms and it worked for them, but I can't build the driver on the pi's.

I tried installing the cycloneDDS on the pi, but could not do it without having the pi connected to the internet. I ran the roundTrip example on the pi's seperatly, it worked on both. i then connected both pi's to the network and tried the same example and it worked with out any changes to the code, ran roundTripPong on one pi and roundTripPing on the other.

I have created a image from the sd card which only have the neccesary software to run cycloneDDS (+ apt-offline, but it should be irrelavent)

### 25/8-2020
I made the pi's request a static ip over their ethernet, so that I don't have to re-authentecate the ssh connection everytime they get a new ip as it has happened that they got eachothers old ip addresses. I followed this [guide](https://thepihut.com/blogs/raspberry-pi-tutorials/how-to-give-your-raspberry-pi-a-static-ip-address-update)

I have made and setup a private github and created a ssh connection to it from my pc

### 26/8-2020
Found more potential paper to look into

### 27/8-2020
I have moved the helloworld example from cyclonedds lib to anohter folder. To be able to complie the code, I only had to change one line in the cmakelist, I just had to change the path to the CycloneDDS librarie (find_package), at the moment it is the absolute path, so it has to be changed for the pi's

I have started to make my own program, using the helloworld program as a template. And I have found and started to use the CycloneDDS C api reference to get a more detailed understanidng of the library

## Week 36

### 31/8-2020
Tried to make the looping publisher and subscriber, but it does not work atm, it seems like the data is being let go off. I can make the subscriber run in a loop, but I can't get it to recieve more than one message, after which it gets stuck in the loop or it dumps the core. Seems to have something to do with how samples and infos is handeled.

### 2/9-2020
The subscriber loop now works. I have put the code that writes into a while true loop, inside another while loop, and the only other change I had to make was to "reset" the rc variable back to 0 in each cycle. The publisher loop also works, I have simply put the writing part into a while loop.

### 3/9-2020
Started the work on a simplere version of the ping pong example. It seems that the code uses the same topic to write over both ways, and then uses a partition to make sure that ping does not pick up its own message with its reader and vice versa. The partition is made to the qos using the dds_qset_partition() function.

### 4/9-2020
The simple ping pong programs can now send and recieve messages between eachother, however, when pong tries to display the message from ping it writes a long number for the id (should be 0) and nothing for the message part. Found the mistake, I was sending the address of a non-pointer in ping which explains the long number recieved by pong.

### 6/9-2020
A program "Join group 239.255.0.1 for any sources" twice when it starts. Both subscriber and publisher will "ping" "239.255.0.1 (Protocol RTPS)" the network every once in awhile when waiting for the other one to appear on the network.

## Week 37

### 7/9-2020
I have started putting code bits into functions from the simplePingPong code to make it easier for me to understand later and to it better for re-use later on. I have also moved from Sublime Text over to VSCode in order to have library support/syntax to make programming easier. To add the library I had to add its IncludePath to a file called c_cpp_properties.json which is created by C/C++ extension (I think)

### 8/9-2020
I added loops to the simplePingPong programs. I had an issue where both ping and pong would take the first message they  received and then print that one 9 more times instead of the new once. The problems seems to have been because I used dds_read and not dds_take, seen as the code worked after I made the switch. I would guess that I could get around this "problem" by somehow checking if there is a new message or something like that. By looking at the documentation I found that dds_take removes the sample from the data Reader so it cannot be read/taken again 
(not sure if counts for all data readers on the topic or only the one used with the function, should be looked into. it seems to be possible to remove it for others, but not sure, it says something about 
*The buffer required for data values, could be allocated explicitly or can use the memory from data reader to prevent
copy. In the latter case, buffer and sample_info should be returned back, once it is no longer using the
Data.* not sure what it means exactly, but I have to find out)(dds_take_wl can access loaned samples and dds_return_loan can return it)
Learning more about the memory space should be an upcomming priority.

### 9/9-2020
Playing around with some sample buffer to try and understand how it works.
So I put a 1000 ms sleep, in the subscirber from pubSubLoop, after the creation of the reader. The publisher has no delay and as soon as the reader is discovered and the subscriber will then read all 10 messages one by one even with a sample buffer of size one. From this I would guess that if I increased the buffer size forexample 10 I would only have to do one take, will test tomorrow.

**Instances seems** to refer to data/messages in the dataWriter's data/memory space. dds_dispose *This operation requests the Data Distribution Service to modify the instance and mark it for deletion.
Copies of the instance and its corresponding samples, which are stored in every connected reader ...*, tihs would suggest that a dataWriter can have a instance it made be delete after it have been sent and recieved by dataReader, even in the reader's memory.

### 10/9-2020
Looking into the IDL files I found that the naming of the data type goes as following: _**module name** _ **struct name**_. So for example if the module is called RoundTripModule and the struct is called DataType than the data type will be called **RoundTripModule_DataType**.

Waitset are interseting, they are used to control your program, they can be used to make the program wait for data or shutdown the program when the writer is terminated (it would seem).

I removed the while 10 loop in pubsubloop's subscriber and inscread its buffer size to 10 and it works the same as before. 
I put a 1s delay into the publisher after it has sent its 5th message, the subscriber only got 5 messages, **this was expected** since the program only wait for a message to be sent once, instead of before where it would wait for every message, maybe the reader does not stop reading as long as the writer makes a contiuned stream of data or the dds_sleepfor does something that signals the network that it has stopped working for a bit. The reader gets all 10 messges when the puhslisher only has a 10ms delay. Anything higher than 10ms seems to have the same effect as the 1s does.
It seems that the program only reads the newest message from each **key**, so the only reason it worked like when it had a loop around it was becuase I changed the key of the publisher's message every message. Finding a way to take all messages would be useful and I think it has something to do with the QoS.
When having sPing and sPong running infinit, I am able to turn off ping and then on again with out it being an issue for pong, ping seems to just rediscover pong and then move on. **Contiuned on 14/9-2020**

### 11/9-2020
I have given the PI's static I ip's through the [router](https://url.net.au/help/routers/mikrotik-951-assign-static-leases-to-device) now. The old process didn't work after a while so I hope the router will make sure the ip's stays static.

Setup wireshark and router
https://www.wizzycom.net/traffic-capture-from-a-mikrotik-device-to-wireshark/

The tcp and ssh messages seen between the RTPS message are the prints from the program.

I have been capturing the helloworld publisher in a few different ways, so there is something to compare, but only up til the point it waits for the reader to be discovered.

It seems like there is nothing to observe on the network when a topic is created by the helloworld publisher. Maybe some will happen when two "node" connects to the same topic.

## Week 38

### 14/9-2020
While preparing the PubSubloop programs to have infinit cycles I found that the publisher does not know when the subscriber is gone, this does make sense as there is no kind of check in the code which would find out that the reader is gone, I presume that this is what I should use the waitset for, but also it should not be an issue that the publisher just contiunes to write as the messages will be saved in the dataWriters history, depending on the QoS which is the next big feature to look into.

**Contiuning from **
RoundTrip example: Ping will not start working again after pong has been turned off and on again, this could simply be cause by the functinallity of the code. Pong still works and is accpted by ping after ping have been turned off and on.
The same goes for my own simplePingPong, and I know why it works like this now. It is because that when you turn off pong, ping will get stucḱ waiting for a message from pong, before it sends one back again, and when you turn pong back on it will wait for a message from ping before it writes back to ping. And it works with turning ping off becasue ping always send a message as its first action.

PubSubLoop has a 500 ms delay after each write, both for making it easier to read the wireshark capture and to make sure that the dataReader takes the messages one by one, this part does not matter really, it should not matter if the reader take more than one messages at a time.

Some of the test from today was made because I was unsure if wireshark can actually capture the actual messages between the two raspberry pi's. I am still not sure, but it should become cleare after looking into the captures at greater depths. 

