---
title: Test Results
created: '2020-10-27T19:08:39.885Z'
modified: '2020-10-27T21:27:13.629Z'
---

# Test Results

## IDL size
### Laptop
| 1000000 | 100000 | 10000 | 1000 | 100 | 10 | 1 |
| ------- | ------ | ----- | ---- | --- | -- | - |
| 2072    | 21376  | 214464 | 2145304 | 8372616_*_ | 8372616_**_ | 8372616_**_ |


#### Notes
The laptop froze for a little while when sending the 214464 bytes message. It does not work everytime, sometimes the reader just gets Killed. The reader seems to work everytime when it is started first.
Staying with the same idl size, but going down to 1000 max samples makes the reader stable again and now works when writer is started first

For 2145304 bytes it sometimes frezzes, but the message still gets through and does **not get Killed**

8372616* is not stable, give segmentation fault sometimes
8372616** bytes, 10, and 1 buffer size: its very unstable still giving segmentation fault.

_*_ is the value that does not give a segmentation fault. The programs can be complied at 21453752 bytes

### Pi4
| 1000000 | 100000 | 10000 | 1000 | 100 | 10 | 1 |
| ------- | ------ | ----- | ---- | --- | -- | - |
|  |  |  |  |  |  |  |
