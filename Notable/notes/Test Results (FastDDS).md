---
title: Test Results (FastDDS)
created: '2020-11-02T15:26:04.858Z'
modified: '2020-11-06T16:49:00.146Z'
---

# Test Results (FastDDS)

## IDL size

### Laptop
Becomes a bit unstable at 7200000 bytes. No error, segmentation fault or Kills, it just does not always react to the message from the publisher, but it does say that it has been matched and when the publisher shutdown, but it does not read anything, it will sometimes if you just send a few more, but some are lost. This behavior seems simaler to how the  cyclone programs reacted, but they gave a segmentation fault instead of doing nothing.

7600000: as as 7200000, works after second publisher start.

8000000: worked after 3 tries. Sometimes first try.
16000000: Segmentation fault (core dumped) when starting publisher.

8372616: Program started, segmentation fault (core dumped) after prints

8320000: Works fine
8336000: Publisher can write sometimes, but will give segmentation fault more often. its very unstable. Subscriber worked the second time the writer wrote.
8328000: subscriber worked the second time.
8334424: Works and subscriber receives the first message from the publisher.

### PI 4
8334424: Worked after 3 tries with the publisher. None of the programs give a segmentation fault

8334400: Work after 3 tries, but did work first try a few times 

3120000: Almost works on first try everytime, sometimes it needs two.

2720000: Works first try. Time to go up

2740000: Close
2739280: Works fine

## R/W Speed

### Laptop Reliable
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 887219.79 | 132965.63 | 64540.0 | 42549.0 | 32011.6 | 24157.24 |
#### Standard Deviation
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 47515.5 | 3279.8 | 1854.1 | 1258.9 | 765.5 | 661.3 |

### Laptop Best Effort
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 981686.34 | 134827.08 | 66410.14 | 43738.2 | 32349.63 | 25192.78 |
#### Standard Deviation
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 33423.8 | 4314.9 | 1857.1 | 1381.4 | 941.1 | 690.7 |


### Pi4 Reliable
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 112713.44 | 17442.75 | 5669.85 | 3172.47 | 2246.29 | 1672.18 |
#### Standard Deviation
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 748.3 | 1077.9 | 76.5 | 33.7 | 216.7 | 258.8 |

### Pi4 Best Effort
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 120521.31 | 17507.38 | 5766.48 | 3628.75 | 2723.82 | 2220.29 |
#### Standard Deviation
| 8 | 128000 | 256000 | 384000 | 512000 | 640000 |
| - | -- | --- | ---- | ----- | ------ |
| 585.5 | 101.9 | 38.8 | 11.0 | 20.8 | 12.1 |
