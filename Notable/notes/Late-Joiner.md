---
title: Late-Joiner
created: '2020-11-09T10:58:12.438Z'
modified: '2020-11-10T22:06:15.882Z'
---

# Late-Joiner
Having history enabled greatly reduces the amount of samples received doing a speed test.

**Anything "higher" TRANSIENT_LOCAL seems to not allow samples for late-joiners**, the slow reader is still able to get samples it "missed" from after it was created, so the history still works. This the same case when communicating on the same device and over two seperate ones.

## Limit (Cyclone)
The MAX_SAMPLES cannot be 1, when working with a read operator and polling, as this will fill up the history cache and it will not be emptied since we are using read and not take

80 bytes works fine

## Speed (Cyclone)


## History Size
A reader with keep all history kind, reliable communication, and sample size 640k bytes

### Samples in cache at the time it consistenly started to loose samples
The numbers are based on observations. The value is noted from around the point where the reader loses samples between its read operations.
|  | 1469 | 1362 | 1312 | 1280 | 1496 |  |  |  |  |
| - | - | - | - | - | - | - | - | - | - |

The program starts to slow down, this can be seen in both the frequency of prints changing, and by the fact that the reader get more samples per read operation. The reader does about two read operation in time the writer does a write operation. These things happens in spikes.

#### Discission
As seen in the prevouis test and this one, there is an important balance to be found with the MAX_SAMPLES define/variable, this is something that FastDDS does not have to think about since it does not give the choice of changing it.

## FastDDS
640000 and 320000 :The reader was unsable after the second sample

With a idl size of 80 bytes, the reader is working fine, but stops taking samples after 400. FastDDS has ResourceLimits max_samples_per_instance set to 400 by [default](https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/core/policy/standardQosPolicies.html#resourcelimitsqospolicy)

80 byes: Worked fine, stopped after 20000 samples
