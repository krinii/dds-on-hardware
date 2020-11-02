---
title: Test Results (FastDDS)
created: '2020-11-02T15:26:04.858Z'
modified: '2020-11-02T15:31:20.152Z'
---

# Test Results (FastDDS)

## IDL size

### Laptop
Becomes a bit unstable at 7200000 bytes. No error, segmentation fault or Kills, it just does not always react to the message from the publisher, but it does say that it has been matched and when the publisher shutdown, but it does not read anything, it will sometimes if you just send a few more, but some are lost. This behavior seems simaler to how the  cyclone programs reacted, but they gave a segmentation fault instead of doing nothing.
