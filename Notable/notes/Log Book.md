---
title: Log Book
created: '2020-03-11T09:53:48.064Z'
modified: '2020-09-02T11:43:01.257Z'
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
