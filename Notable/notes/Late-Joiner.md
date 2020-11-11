---
title: Late-Joiner
created: '2020-11-09T10:58:12.438Z'
modified: '2020-11-11T22:32:16.689Z'
---

# Late-Joiner

## CycloneDDS
Having history enabled greatly reduces the amount of samples received doing a speed test.

**Anything "higher" TRANSIENT_LOCAL seems to not allow samples for late-joiners**, the slow reader is still able to get samples it "missed" from after it was created, so the history still works. This the same case when communicating on the same device and over two seperate ones.

### Limit
The MAX_SAMPLES cannot be 1, when working with a read operator and polling, as this will fill up the history cache and it will not be emptied since we are using read and not take

80 bytes works fine

### Speed
I performed the 256000 bytes Reliable communication speed test, on the laptop, the same way as in the R/W speed test, but now both the writer and reader had their durability set to TRANSIENT_LOCAL and there history kind set to keep all with a depth of 100. 
**Result:** 3614.61 average samples over 5 seconds with a standard deviation of 47.3.
This is significantly slower than the original test which got 7197.23 average samples over 5 seconds

### History Size
A reader with keep all history kind, reliable communication, and sample size 640k bytes

#### Samples in cache at the time it consistenly started to loose samples
The numbers are based on observations. The value is noted from around the point where the reader loses samples between its read operations.
|  | 1469 | 1362 | 1312 | 1280 | 1496 |  |  |  |  |
| - | - | - | - | - | - | - | - | - | - |

The program starts to slow down, this can be seen in both the frequency of prints changing, and by the fact that the reader get more samples per read operation. The reader does about two read operation in time the writer does a write operation. These things happens in spikes.

##### Discission
As seen in the prevouis test and this one, there is an important balance to be found with the MAX_SAMPLES define/variable, this is something that FastDDS does not have to think about since it does not give the choice of changing it.

### Behavior

#### TRANSIENT_LOCAL - Reliable Reliability
A late joining subscriber is able to get samples it missed, the amount of samples received is depending on the smallest DEPTH from the writer and reader. Meaning that if the reader has a depth of 10, but the writer has a depth of 5, so when the reader joins it will only receive the last 5 samples from the writer as this was what it saved, but the reader will still keep the latest 10 samples by it self. This rule seems to not matter for a listener, it seems like it will just read everything it can from the writer, so if the writer has a depth of 7 and the reader 5, the listener will read 7 samples. 
Having two readers, one using polling and one using a listener to read with. Both has a depth of 7 and the writer one of 10. When the polling reader is late to join it will receive the 7 newest samples from the writers history. When the reader using a listener joins late, then it will receive the 10 samples stored in the writers history. So it would seem like the listener is able to get all the data that the writer has stored no matter what its own history is set to, this does however not change how many samples the reader with a listener is able to store by it self

##### Over Router
The behavior is same as communication on the same machine as over the Router for Reliable reliability. Late joiners are still not able to receive old samples over Best Effort reliability.

#### TRANSIENT_LOCAL - Best Effort Reliability
A late joining reader does is not able to receive old samples from the writer as it did with Reliable reliability.

## FastDDS

### Speed
I performed the 256000 bytes Reliable communication speed test, on the laptop, the same way as in the R/W speed test, but now both the writer and reader had their durability set to TRANSIENT_LOCAL and there history kind set to keep all with a depth of 100. 
**Result:** 9681.68 average samples over 5 seconds with a standard deviation of 1099.7.
This is quite a bit slower than the original test which got 64540.0 average samples over 5 seconds

### Limit
640000 and 320000 :The reader was unsable after the second sample

With a idl size of 80 bytes, the reader is working fine, but stops taking samples after 400. FastDDS has ResourceLimits max_samples_per_instance set to 400 by [default](https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/core/policy/standardQosPolicies.html#resourcelimitsqospolicy)

80 byes: Worked fine, stopped after 20000 samples

### Behavior

#### TRANSIENT_LOCAL - Reliable Reliability
A late joining subscriber is able to get samples it missed, the amount of samples received is depending on the smallest DEPTH from the writer and reader. Meaning that if the reader has a depth of 10, but the writer has a depth of 5, so when the reader joins it will only receive the last 5 samples from the writer as this was what it saved, but the reader will still keep the latest 10 samples by it self. 

Having two readers, one using polling and one using a listener to read with. Both has a depth of 7 and the writer one of 10. When the polling reader is late to join it will receive the 7 newest samples from the writers history. When the reader using a listener joins late, then it will receive the 10 samples stored in the writers history. So it would seem like the listener is able to get all the data that the writer has stored no matter what its own history is set to, this does however not change how many samples the reader with a listener is able to store by it self

##### Over Router
The behavior is same as communication on the same machine as over the Router for Reliable reliability, but over the Router Best Effort reliability has the a late joiner of any kind is sometimes able to receive old samples from the writer, but it is not consistent. Don't really see a pattern, have had two readers on the same machine. Tried with polling and listener, both works sometimes and sometimes they don't. The readers on the same same machine as the writer are still not able to get old samples.

##### Decission
The Best Effort thing could just be casued by the fact that a Best Effort network does not make sure that the samples was received.

#### TRANSIENT - Reliable Reliability
I get the following message when I try to make a transient writer:
2020-11-11 15:06:32.963 [RTPS_PARTICIPANT Error] Couldn't create persistence service for transient/persistent writer -> Function createWriter
2020-11-11 15:06:32.963 [DATA_WRITER Error] Problem creating associated Writer -> Function enable

The Durability Service Policy is not yet implemented in FastDDS and they [write](https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/core/policy/standardQosPolicies.html#durabilityserviceqospolicy) that it is used to confgure the built-in reader and writer for transient and persistent writers, so that could explain why it does not work.

#### TRANSIENT_LOCAL - Best Effort Reliability
A late joining reader does is not able to receive old samples from the writer as it did with Reliable reliability.
