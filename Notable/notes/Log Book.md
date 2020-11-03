---
title: Log Book
created: '2020-03-11T09:53:48.064Z'
modified: '2020-11-03T20:26:43.341Z'
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

**Contiuning from 10/9-2020**
RoundTrip example: Ping will not start working again after pong has been turned off and on again, this could simply be cause by the functinallity of the code. Pong still works and is accpted by ping after ping have been turned off and on.
The same goes for my own simplePingPong, and I know why it works like this now. It is because that when you turn off pong, ping will get stucḱ waiting for a message from pong, before it sends one back again, and when you turn pong back on it will wait for a message from ping before it writes back to ping. And it works with turning ping off becasue ping always send a message as its first action.

PubSubLoop has a 500 ms delay after each write, both for making it easier to read the wireshark capture and to make sure that the dataReader takes the messages one by one, this part does not matter really, it should not matter if the reader take more than one messages at a time.

Some of the test from today was made because I was unsure if wireshark can actually capture the actual messages between the two raspberry pi's. I am still not sure, but it should become cleare after looking into the captures at greater depths. 

### 15/9-2020
Started making the requirement specification more detailed/polished as this should help give me more direction to my work so I don't spread my focus to much (**suggested by Thor**). I should make the requirements so that it is somewhat clear what kind of test I can do to *prove* that the requirement have been met.

### 16/9-2020
Working on the requriment specification
https://blivprojektleder.dk/kravspecifikation/

### 18/9-2020
I have created an account at **Adlinktech** so that I can try their Vortex Insight program to monitor my DDS programs, I only have a 30-day trail atm.


## Week 39
### 21/9-2020
Update the requirement specification so that it should follow Thor's guidelines, it's not done yet, but way closer than before, still need to finish the problem analyse. 
I have printed and than started reading a DDS tutorial, notes will be made during and it seems promising.

### 22/9-2020
Wrote some notes about partitions which more or less just needs to be added to the latex document.

### 23/9-2020
I found the soucre code for the cycloneDDS functions, the library is complied so they were binaries. They are in the "cyclonedds/src/core/ddsc/src" of the git repository and they are separated into different files

### 25/9-2020
The DDSI specification seems to have more of the relavant information regarding the more tecnical parts of the protocol. **This is not completly correct, the DDSI is the layer below DDS and the "I" stands for Interoperability Wire Protocol, so it should be more about how the actual communication works**

The DDS specification seems to only focus on the programming objects of the protocol.

Read the two lastes bookmarks in the DDS folder and read the DDSI specification.

### 26/9-2020
Qoute from DDSI specification section 7.1: 
*The DDS specification does not address the protocol used by the implementation to exchange messages over
transports such as TCP/UDP/IP, so different implementations of DDS will not interoperate with each other
unless vendor-specific “bridges” are provided.*

It would seems like I'm on the right track.

### 27/9-2020
Section 8.3 is about the **Messages Module**, might be relavent.

Section 8.5 is about the ** Discovery module**, this is what makes the participants able to discover eachother. Important to understand.

Section 7.6 qoute: *RTPS supports a wide variety of transports and transport QoS. The protocol is designed to be able to run on multicast and best-effort transports, such as UDP/IP and requires only very simple services from the transport.
In fact, it is sufficient that the transport offers a connectionless service capable of sending packets best-effort.
That is, the transport need not guarantee each packet will reach its destination or that packets are delivered in-
order. Where required, RTPS implements reliability in the transfer of data and state above the transport interface. This does not preclude RTPS from being implemented on top of a reliable transport. It simply makes it possible to support a wider range of transports.*

Section 7.6 has a general requirements from RTPS for the underlying transport (layer?). Short useful information.

**pubSubLoop_instanceTest** has a writer and a reader, the writer only writes to one instance every 500ms and the reader takes a messages every 1s. I can see from the msgNr element that the reader only get about every second message (this is mostly casued by the fact that the sleep functions are only relative), which makes sense as there has been made no changes to the QoS, so the history only holds 1 message and the writer overwrites the old message every 500ms.

## Week 40

### 28/9-2020
To try and see if cycloneDDS could run as cpp instead of c I just changed the file extension. Without any changes to the code I can run the code as cpp, but I do get a few warnings from the complier (warnings can be found in picture first_cpp_complie_warnings.png).
Added iostream's cout, everything still works the printf syntax warning is gone since I removed them (fun right).


Acording to an artical from [Adlink](https://istkb.adlinktech.com/article/ddsi-networking-service-ports/), UDP port numbers are limited to 64K which will allow 230 domains with up to 120 Participants per node per domain.

Quote from [Adlink](https://istkb.adlinktech.com/article/vortex-opensplice-memory-user-questions/):
* **Is it possible to deploy OpenSplice on a node with only volatile memory storage?**

*Yes. The only shortfall this brings is that this particular node will be unable to store data in a Persistent state, i.e. data will not outlive a restart on this node. However as long as there is at least one node in the system with non-volatile memory deployed in the system this will be used to store Persistent data from the entire system. The Transient persistency option will still be available on the volatile node as this doesn’t rely on non-volatile memory. All functionality offered by the full set of supported profiles are available on diskless nodes too.* This is useful if it works for other vendors aswell.

### 30/9-2020
DDSI specification Table 8.16 has a reference to the UDP header: *The Address is set to the Address of the source of the message, assuming the Transport used supports this (e.g., for UDP the source address is part of the UDP header). Otherwise it is set to
LOCATOR_ADDRESS_INVALID.*

Section 8.3.5.4
*SequenceNumber
A sequence number is a 64-bit signed integer, that can take values in the range: -2^63 <= N <= 2^63-1. The selection of 64 bits as the representation of a sequence number ensures the sequence numbers never 1 wrap. Sequence numbers begin at 1.*

I don't necessarly think the SequenceNumber is off any real relavance for DDS in general (the specification says it has no relation to DDS), but this does give us a limit to the amount of message in a system (I think this is for the entire system, but I am not sure yet). The specification also mentions: *Even assuming an extremely fast rate of message generation for a single RTPS Writer such as 100 messages per microsecond, the 64-bit integer would not roll over for approximately 3000 years of uninterrupted operation.*

Terminology(I guess): When a RTPS writer has new data it will update a data-object in its local cache and then informs the readers that changes has been made (and term vise they update their own acordingly I think)

In the Message Module: **Logical Interpretation** sections give a describtion of what the message is used for, should be useful for remembering or for short catch ups.

Heartbeats (Section 8.3.7.5) inform the readers of new data in writers and of which are new.

### 1/10-2020
The DDSI describes the wire protocol for DDS (more explenation). It has some interesting points and there are many detailted decribtions of how some the DDS functionallties work, but it is of greater interest for a DDS devoloper than a DDS implementer. 

A behavior describtion of what happens, in DDSI, when a dataWriter discovers a dataReader can be found in section 8.4.8.1 for reliable and 8.4.9.1 for best-effot. Qoute from section 8.4.9.1.1: *This transition is triggered by the configuration of an RTPS Writer ‘the_rtps_writer’ with a matching RTPS Reader. This configuration is done by the Discovery protocol (8.5) as a consequence of the discovery of a DDS DataReader that matches the DDS DataWriter that is related to ‘the_rtps_writer.’*

**For Report**: Describe the elements that comes with any DDS message like timestamps and more. Also, in best-effot communication, can you keep track of the message order (since they could be sent out of order, is there a way(probaly timestamps) or do you have to use reliable communication?)

Describe the different QoS setting and explain how they work and how they could used/relevant for different applications.

### 2/10-2020
Section 8.5.2: DDS discovery is done with built-in dataWriters and dataReader which has pre-defined QoS and Topics (there are four built-in topics and each has a dataWriter and dataReader). The dataWriters announce the presence and QoS of the local DDS Participant
and the DDS Entities it contains (DataReaders, DataWriters and Topics) to the rest of the network.
The built-in dataReaders collect this information from remote Participants, which is then used by the DDS
implementation to identify matching remote Entities. The built-in dataWriter can be used as a regular (it also acts as one) dataReader and can be accessed by the user with the DDS API.
The dataType used for discovery is called SPDPdiscoveredParticipantData and it's attribute are described in table 8.73.
Quote from section 8.5.3.3.2: *Periodically, the SPDP examines the SPDPbuiltinParticipantReader HistoryCache looking for stale entries defined as those that have not been refreshed for a period longer than their specified leaseDuration. Stale entries are removed.*. It would seem like the reader makes sure to only keep track of active/alive writers.

### 3/-9-2020
**For Report**: It might be useful to have a section describing some the RTPS-DDSI functionllaity, mostly thing like how it relates to DDS writer and reader, you could use some of the figures that describe the relationship between the RTPS and DDS entities like for example the writer and reader. The disovery model would mostly also be interesting. And a general describtion of what the RTPS-DDSI is (if you can).

Time_Based_Filter can either be implemented on the writer or the reader side. Implemented on the writer will save bandwidth. The choice is made by the vendor.

ContentFiltered Topics (section 8.7.3) can be implemented on the writer, the reader side or both. Implemented on the writer will save bandwidth. The choice is made by the vendor. When filtering on the reader side any message that does not pass the filter will be dropped by the middelware. When implemented on the writer side will casue messages that does not pass the filter to sometimes not be sent which conserves bandwidth.
Content-Filters can be updated at runtime.

### 4/9-2020
Section 9.1 has a list of points as to why UDP/Ip is a sutable transport for RTPS-DDSI.

Section 9.4.1 states that a submessage has a boundary of 32-bits with repect to the start of the Message (Not sure what excally that means yet there are some illustrations in the specification that might help).
*In the case of UDP/IP, the length of the Message is the
length of the UDP payload.*

Section 9.4.5.3 describes the mapping of the Data Submessage.
Section 9.6.1.2 User traffic explains the choice of port (losely).
Section 10.7 has a really good example of what a user-defined message could look like.
All application data seems to be in the **serializedPayload** element in the **Data** submessage.

## Week 41

### 5/10-2020
The test describtion chapter needs alot of cleaning up (things have changed). You should talk about some of the things you did before you tested the requirements.

### 7/10-2020
I have started the testing of the history setting.
**History:**
First I set the reader to have a histery depth of 3. I have changed nothing in the writer. The reader uses the "take" operation and this has made the reader able to able to get all messages from the writer, where before it would only get every second. A new-commer/late-joiner reader will not get any of the old data since the writer's history depth is 1 (default values)(history is a local QoS), a reader does not check for information in other readers and most important the default durability is volatile which tell the servive(DDS) that is should only attemp to provide data to exitsing reader at the time where the data was written(See DDS specificaion page 105).
*view_state*
I tried to make the reader use the *read* operation instead of *take*. To do tihs I have to look at the *view state* to make sure that I don't keep keep looking at old data as if it was new, I made a check and the first time the reader reads/takes data the view_state is DDS_VST_NEW, but the second time its DDS_VST_OLD even though I can see that the data being displayed is new.
**view_state seems to relate to the instance, so its tell you if it is the first time the reader reads from the instance and not if the sample/data has been read before by the reader, instead you should use the sample_state**
~~**There's also problems with sample_state, it reads the first 5 messages and then its stops and says that the data in the cache is read, then once in awhile it will read the 3 (history cache) newest samples and return to saying that the data has been read.**~~ ~~**_This only happens when using the read operation and not with the take operation_** **Changed the depth to 5 instead and it only read the first 2 samples**~~
**It was a problem in the first if statement, I was thinking that the new samples would "push out" the olds ones so I checked 0 and I should probaly check the last postion instead of the first one. The newest sample will be in the last positon starting from 0 and pushing out 0 when full** I need to find a better why to check if there is new data(Done). Later its gonna be with waitset or a lisener.

**_Note for data availability test_**
To make data avaliable for new comer reader you have to make changes to both the history and durability QoS settings. The history setting just at least needs to have its depth changed, you can also change the keep_last to keep_all, but that will depend on the application requirements. The durability changes depends on how you want the data store and how persistant the systems should be in perserving the data.

### 8/10-2020
A DataWriter has RELIABILITY set to RELIABLE by defualt and a DataReader has it set to BEST_EFFORT by defualt. So it makes sense that the examples had the subscriber be reliable, but didn't change anything on the publisher.

I have confirmed that by just changing the writers history does not give new comers any of the old samples, it would seem like I have to make changes to the Durability

I have applied the history changes to the topic instead of the reader and it seems to work the same way as when I did it to the reader. So it looks like the QoS of a topic applies to all the entities in that topic. Somehow it seems like it enough to just make the topic in the reader application have a history.

I tried to apply the durability changes to only the readers in the HistoryTopicTest project, but when I did this it seemed like the writer and readers did not have a connection, I need to find a way to detect wether a connection is made or not, at the moment I just have to see that the writer does not find a reader (which I guess could be fine). I have applied the durability setting to all the Topics in HistoryTopicTest and all the readers and writer in HistoryTest and I am still not able to make a late-joiner receive old data, I am not sure what I'm doing wrong. **It would seem like I have to change durability-service setting for it to work. Durability-service can be applied to both topics and writer, but a  [guide](https://github.com/eclipse-cyclonedds/cyclonedds/blob/master/docs/manual/config.rst) mentioned that it is the topic, gonna try both**. I have applied durability service to the writer in HistoryTest and a late-joiner is now able to aquire earlier data. I have removed the history change from the writer so it is now only applied by the durability service and it still works. I let a reader have a larger depth then the writer and it only get the amount of samples specified by the writer. I also tried having the writer have a larger depth then the reader and it only gets the amount of samples specified by the readers depth. So the lowest depth sets the limit as one would excpeted.
I applied the durability service setting to the HistoryTopicTest project, but only in the writer program and it works. I'm not sure what is gonna happen when I apply it to the "other" topics, most likely nothing as it should be the same topic.

### 9/10-2020
I have to install stress-ng and iperf on the PI's, is done with apt, and I need to find out how to use the programs.

I have started documenting my findings/learnings from the HistoryTest and HistoryTopicTest projects in overleaf in an effort to make a template for later tests.
## 42
### 12/10-2020
Installed Valgrind, a tool used for observing a programs memory usage.

### 13/10-2020
From the history test I found that the readers can get old data as a late-joiner if they don't have a durability of at least transisent_local, which I don't quite understand why, I have might have written something about it earliere, but if not I should look into it for the discussion part of the test.
**For the test chapter**
Maybe setup the test so that they can kinda be in a table, something like "two rows, one for best effort and one for reliabe and then columns with DETPHS" and then you just write if it works. You could also just make "headlines" where you write up the parameters and then write how it looked, something like: 
"**TRANSISENT_LOCAL, HISTORY_KEEP_LAST, DEPTH 10, BEST EFFORT:** a late-joining reader recievies old data from the writer" or "**TRANSISENT_LOCAL, HISTORY_KEEP_ALL, BEST EFFORT:** a late-joining reader recievies old data from the writer and either the writer or reader crashed after 100000 samples".

**HistoryTopicTest**
So I tried to put the durability_service into both the writer and a reader. The reader that have the durability_service is not getting any old data as a late-joiner.

### 14/10-202
The "setbuf(stdout, NULL)" does not remove the New Read print issue.
A massif.out file from Valgrind can be printed with "ms_print"m, which makes the data easier to analyse. massif-visualizer is gui for analysing the massif.out files

### 15/10-2020
When connecting to the pi's with **screen** over serial, you have to run the screen command while the pi is booting up. `screen /dev/ttyUSB0 115200`

### 16/10-2020
Started learning how to use Valgrind:
[Massif](https://www.valgrind.org/docs/manual/ms-manual.html): a heap profiler (`valgrind --tool=massif <program>`)
*Massif is a heap profiler. It measures how much heap memory your program uses. This includes both the useful space, and the extra bytes allocated for book-keeping and alignment purposes. It can also measure the size of your program's stack(s), although it does not do so by default.*

A massif.out."number" file will be made after the program is termianted, in the execution folder.
## 43
### 19/10-2020
**HistoryTest 2 instances:**
I added another writer to the HistoryTest project to see how the history setting acts with two instances. **Notice** it is not necessary to make another program, the same writer can write to any instance you want to and one program can have multiple wirters. This was simply done so that I didn't have to remove code later if I need to test with only one instance.
**The late-joining reader gets gets DEPTH samples from both instances.** 
**It works the same Topics**

I have made the project folders for testing data seperation (Primarily domains) and data fitlers (ContentFilter's and more). Nothing is implemented yet, it is still just a copy of the memoryTest project.

### 20/10-2020
**Partition**
Use the simplePingPong project for testing partitions. The partition is used to make sure that the samples in the ping writer is not read by the ping reader, same goes for the pong writer and reader. 
**Content Filter**
The filter works. In cycloneDDS you create a funciton which makes the logic operations. The function is given to the topic with dds_set_topic_filter(). The user made filter function has to take a constent void pointer and return a boolean. `typedef bool (*dds_topic_filter_fn)(const void *sample)`. It is only implemented in the subscriber.c at the moment. The filter is applied to the topic individually in each program, and I only applied the fitler to one of the programs (subscriber.c) and it was able to recieve samples, this most mean that one can implement different filters on the same topic.

**New Read issues continued**
I now know how it is possible for the program to spam, it somehow get a true from one of the two check functions, but the for loop which checks them again does not find anything, so the loop skips the delays with the break.
**Instead of using DEPTH as the size I now use rc in the check function, it seems to have worked, but I can't know for sure yet**

### 21/10-2020
**Content Fitler**
I applied two different content filters to the two readers over the same topic, they both got the messages that the filter would let through. This "proves" that one can apply different content filters on the same topic.
Applied a content filter to just the writer and none of the readers got any of the samples that the filter should take, I would guess that the samples are never sent, but I don't know for sure (acoridnfg to notes from *3/9-2020*: The service might send some of the samples that did not pass the filter).

**Listener:**
*The listener will only be invoked on the changes of communication status
indicated by the specified mask.* qoute from **DDS_Formal-15-04-10.pdf**.
Only one listener can be attached to an entity at a time.
**I have implemented a listener in one of the readers which listens to requested_incompatible_qos, offered_incompatible_qos, and data_available**
**The callbacks "data_available" and "requested_incompatible_qos" works as they should, have not tested "offered_incompatible_qos".**
**Important: The callback association has to be done before the listener is attached to a entity.**
Put the reading and sample displaying code into the data available callback and it worked the same way as when using polling. I added a 3 second delay and a print into the "empty" while loop and the data available callback runs regardless of the delay, so you should be able to do almost whatever you want to do and the listener should interrupt it and run its function.

**WaitSet**
Waitset's are used for waiting for status changes that affects the enitiy the waitset is attached to.

### 22/10-2020
Do the writingSpeedTest with different IDL's (Larger) to see if it makes a differens.

CycloneDDS chooses to use the loopback when I turn off my wifi module. When it does this I am able to see a lot more information with wireshark (most notable the HEARTBEAT).

### 23/10-2020
**IDL** in the read/write speed test: I have made the large idl have 259 doubles elements, it contains 2 seperate double and an array of 257 doubles, this is the max size for the array, any higher and it will not complie (giving the error found in "complie_error_with_arr_larger_then_257"). The reader gives a message "Killed" in the terminal when I try to receive a message of two doubles and arrary of 257 doubles (Guessign the OS kills it).
Sending 2032 bytes is able to be send, but the laptop start being non responsive and only the first cycle of reads gets a few 1000 samples and the rest all get below 5 and in some cases 0.

## Week 44

### 26/10-2020
Worked on the performs test section in the report.

### 27/10-2020
Ved at ændre MAX_SAMPLES til **100000** i stedet for **1000000** kan programmet complie med en idl større end 257 bytes, som ellers var et problem før, men nu kan jeg gå helt op til 20000 bytes. Det ser ud til at jo mindre MAX_SAMPLES er jo større kan idl'en være. Til testen: Find forholdet mellem MAX_SAMPLES og idl størelse.
MAX_SAMPLES størrelse er meget vigtig at tænke på. Den afgøre hvor mange samples en reader kan modtage per read operation og den er delt mellem alle instances. Så hvis MAX_SAMPLES er 1 vil det kun være muligt at modtage en sample af gangen, hvis readeren er hurtig nok kan den ind hente beskederne i dens cache, men det er ikke reliable.
**Note** Any element in the idl will take up 8 bytes as defined in the RTPS.

### 28/10-2020
Installed both Fast RTPS and RTI Connext. RTI is not really that simple and toke at bit to work and changing the code toke at bit as well. Fast RTPS seems easier to complie, need more testing. None of the implementations can communicate, and I have no idea how to fix it. Might have to scrap the cross communication performance test, since I can't make it work atm, and just write about it instead, but then do more of the test with two different implemenations.

### 29/10-2020
Gonna change the MAX_SAMPLES define to 100 in all the read/write speed test programs.

### 30/10-2020
Performed the R/W speed test (cyclonedds) on the PI2 and laptop, almost done on the pi4 as well

### 31/10-2020
Finished R/W performance test for cyclone and wrote the results into overleaf document

## Week 45

### 2/11-2020
**For Report:** Restructure the chapters, have less chapters, so make more things into section.
[Domain mapping to UDP](https://github.com/eclipse-cyclonedds/cyclonedds/blob/master/docs/manual/config.rst#mapping-of-dcps-domains-to-ddsi-domains). Entire articel have some good information.

**For learning curve section:** eProsimas's implementation comes with a lot of different examples for both FastDDS and FastRTPS. 

FastDDS does not seem to have a read or take funciton, it instead uses `take_next_sample` and `read_next_sample` which are set up with: [*The read_next_sample operation is semantically equivalent to the read operation where the input Data sequence has max_length=1, the sample_states=NOT_READ, the view_states=ANY_VIEW_STATE, and the instance_states=ANY_INSTANCE_STATE.*](https://fast-dds.docs.eprosima.com/en/latest/fastdds/api_reference/dds_pim/subscriber/datareader.html?highlight=take#datareader) The same goes for take. So I can not do the same memory test as with cyclone.

### 3/11-2020
Finished idl test on Laptop.
Installed FastDDS on Pi4, I tried on pi4 with bith ubuntu 18 and 20, but it didn't work.
Finished idl size test on Pi4.
