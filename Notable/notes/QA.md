---
title: QA
created: '2020-11-13T09:17:51.753Z'
modified: '2020-11-20T19:25:29.934Z'
---

# QA

## CycloneDDS

### Reliable reliability
#### Disconnected RPi2 ethernet cable:
##### Listener
Gave the following error when cable was disconmected: 
*1605272794.578859 [0]        tev: ddsi_udp_conn_write failed with retcode -1*
After a few errors the listener will react to the fact it has been disconencted from the publsiher/writer.
The program starts to receive samples shortly after having its ethernet cable reconnected.

##### Polling
Gave the following error when cable was disconmected.
1605272974.340710 [0]        tev: ddsi_udp_conn_write failed with retcode -1
After a few errors the listener will react to the fact it has been disconencted from the publsiher/writer.
The program starts to receive samples shortly after having its ethernet cable reconnected.

##### Publisher
After disconnecting the ethernet cable started givnig the following error at the rate of the write operation:
*1605271866.768567 [0]        tev: ddsi_udp_conn_write failed with retcode -1*
the error starts almost imidiatly after the cable is disconnected. The writer will start to write again after a bit (Gonna guess it writes on the loop back or somethings else), but it will still give the error with an interval now.
The reader on the other device gets samples a lillte bit after the ethernet cable is reconnected.

#### Disconnected RPi4 ethernet cable:
##### Listener
Gave the following error when cable was disconmected: 
*1605270727.324337 [0]        tev: ddsi_udp_conn_write failed with retcode -1*
After a few errors the listener will react to the fact it has been disconencted from the publsiher/writer.
The program starts to receive samples shortly after having its ethernet cable reconnected.

##### Polling
Gave the following error when cable was disconmected
*1605271065.456395 [0]        tev: ddsi_udp_conn_write failed with retcode -1*
After a few errors the listener will react to the fact it has been disconencted from the publsiher/writer.
The program starts to receive samples shortly after having its ethernet cable reconnected.

##### Publisher
After disconnecting the ethernet cable started givnig the following error at the rate of the write operation:
*1605272062.534299 [0] publisherL: ddsi_udp_conn_write failed with retcode -1*
*1605272081.836448 [0]        tev: ddsi_udp_conn_write failed with retcode -1*
the error starts almost imidiatly after the cable is disconnected. The writer will start to write again after a bit (Gonna guess it writes on the loop back or somethings else), but it will still give the error with an interval now.

The reader on the other device gets samples a lillte bit after the ethernet cable is reconnected.

#### Disconnected Laptop turn off wifi module:
##### Listener
Same:
*1605273853.521658 [0]        tev: ddsi_udp_conn_write failed with retcode -1*

##### Polling
Same
*1605273980.504454 [0]        tev: ddsi_udp_conn_write failed with retcode -1*

##### Publisher
Same
*1605274068.189229 [0] publisherL: ddsi_udp_conn_write failed with retcode -1*
*1605274068.289974 [0]        tev: ddsi_udp_conn_write failed with retcode -1*



### Best Effort reliability
#### Disconnected RPi2 ethernet cable:
##### Listener
Same
*1605275296.491261 [0]        tev: ddsi_udp_conn_write failed with retcode -1*

##### Polling
Same
*1605275352.625535 [0]        tev: ddsi_udp_conn_write failed with retcode -1*

##### Publisher
Same
*1605275116.296691 [0] publisherL: ddsi_udp_conn_write failed with retcode -1*
*1605275136.903059 [0]        tev: ddsi_udp_conn_write failed with retcode -1*


#### Disconnected RPi4 ethernet cable:
##### Listener
Same
*1605275021.907347 [0]        tev: ddsi_udp_conn_write failed with retcode -1*

##### Polling
Same
*1605275085.712196 [0]        tev: ddsi_udp_conn_write failed with retcode -1*

##### Publisher
same
*1605275262.124670 [0]        tev: ddsi_udp_conn_write failed with retcode -1*


#### Disconnected Laptop turn off wifi module:
##### Listener
Same
*1605275460.709983 [0]        tev: ddsi_udp_conn_write failed with retcode -1*
##### Polling
Same
*1605275472.589697 [0]        tev: ddsi_udp_conn_write failed with retcode -1*

##### Publisher
Same
*1605275614.312350 [0] publisherL: ddsi_udp_conn_write failed with retcode -1*
*1605275614.740704 [0]        tev: ddsi_udp_conn_write failed with retcode -1*


## FastDDS
### Reliability reliability
#### Disconnected RPi4 ethernet cable:
##### Listener
After a while the subscriber's listener finds out that the subscribers where unmatched.
Reconection is rather quick

##### Polling
After a while the subscriber's listener finds out that the subscribers where unmatched.
Reconection is rather quick

##### Publisher
After a while the publisher's listener finds out that the publishers where unmatched.


#### Disconnected Laptop turn off wifi module:
##### Listener
After a while the subscriber's listener finds out that the subscribers where unmatched.

##### Polling
After a while the subscriber's listener finds out that the subscribers where unmatched.

##### Publisher
After a while the publisher's listener finds out that the publishers where unmatched.


### Best Effort reliability
#### Disconnected RPi4 ethernet cable:
##### Listener
After a while the subscriber's listener finds out that the subscribers where unmatched.

##### Polling
After a while the subscriber's listener finds out that the subscribers where unmatched.

##### Publisher
After a while the publisher's listener finds out that the publishers where unmatched.

#### Disconnected Laptop turn off wifi module:
##### Listener
After a while the subscriber's listener finds out that the subscribers where unmatched.

##### Polling
After a while the subscriber's listener finds out that the subscribers where unmatched.

##### Publisher
After a while the publisher's listener finds out that the publishers where unmatched.
There is no indication other than the listeners reaction to "publisher unmacthed".

### Both
If the writer and reader are started on two different networks (They can't communicate, funny right) and then the writer machine is connected to the same network as the reader they will not start communicating. Same goes for the other way around.
