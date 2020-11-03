---
title: Test Results (FastDDS)
created: '2020-11-02T15:26:04.858Z'
modified: '2020-11-03T20:24:36.291Z'
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
