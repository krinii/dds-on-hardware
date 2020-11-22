---
title: Cross Communication
created: '2020-11-14T17:14:11.827Z'
modified: '2020-11-22T19:22:34.875Z'
---

# Cross Communication

The *topic name* and *type name* are both used to define a topic and two topics with the same name, but different type names does not communicate. This is the case for both vendors.

So far I am not able to make FastDDS and CycloneDDS communicate. I have made sure that both IDL's are the same (or atleast to the best of my understanding), they are called the same, they have the same elements and names, I would however like to note that the two vendors have different ways of declaring a topics IDL type. 
After looking into the cycloneDDS idl based files, it could seem like the way it implements its idl is an issue, it makes a module with a struct inside, which affects the naming of the type_name.
FastDDS type name = HelloWorld
CycloneDDS type name = HelloWorld::data
(gonna see if I can make fastDDS comply with cyclone instead): I can't change the name of the FastDDS type to comply with cyclone (: is an invaild charater).
Cyclone's idl structure contains a "module" with the name "HelloWorld" and inside the module is a struct named "data". FastDDS's idl only contains a struct, which in this case is called "HelloWorld". Cyclone does not accept an idl with only a struct (it will complie and make the idl include files, but they will not be complete/usable).

The domainid found with wireshark for cycloneDDS seems to change every time its started there is a chance its just because wireshark does not decode cyclone's messages correctly. FastDDS's domainid is consisently 0 as it should be.

On Loopback:
CycloneDDS Source and Destination: 172.17.0.1
FastDDS Source and Destination: 127.0.0.1

On Router:
The destination and sources are just the ip of the devices (the RPi's static ip)
