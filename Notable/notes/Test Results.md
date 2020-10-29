---
title: Test Results
created: '2020-10-27T19:08:39.885Z'
modified: '2020-10-29T20:21:59.657Z'
---

# Test Results

## IDL size
### Laptop
| 1000000 | 100000 | 10000 | 1000 | 100 | 10 | 1 |
| ------- | ------ | ----- | ---- | --- | -- | - |
| 2072    | 21376  | 214464 | 2145304 | 8372616* | 8372616** | 8372616** |


##### Notes
The laptop froze for a little while when sending the 214464 bytes message. It does not work everytime, sometimes the reader just gets Killed. The reader seems to work everytime when it is started first.
Staying with the same idl size, but going down to 1000 max samples makes the reader stable again and now works when writer is started first

For 2145304 bytes it sometimes frezzes, but the message still gets through and does **not get Killed**

8372616* is not stable, give segmentation fault sometimes
8372616** bytes, 10, and 1 buffer size: its very unstable still giving segmentation fault.

*is the value that does not give a segmentation fault. The programs can be complied at 21453752 bytes

### Pi2
| 1000000 | 100000 | 10000 | 1000 | 100 | 10 | 1 |
| ------- | ------ | ----- | ---- | --- | -- | - |
| 368* | 3728 | 37312 | 372864** | 3675200** | 8379072*** | 8379072*** |

#### Notes
*Complies at 2144 bytes, but gives segmenation fault. Segmentation fault stops at about 800 bytes, but now the program is killed.

10000 samples 37312 bytes is very slow.

** Unstable, gets killed sometimes

*** Any higher and it gives a segmentation fault (core dumped)

### Pi4
| 1000000 | 100000 | 10000 | 1000 | 100 | 10 | 1 |
| ------- | ------ | ----- | ---- | --- | -- | - |
| 1864*  | 18664 | 186752 | 1865072 | 8376016** | 8376016** | 8376016** |

#### Notes
*Gets killed sometimes.
8376016 bytes no real lag and any higher gives a segmentation fault, does not always.
8376016** publisher sometimes give segmentation fault.
