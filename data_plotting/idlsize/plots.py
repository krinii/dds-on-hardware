#!/usr/bin/python3

import sys
import time
import array
import numpy as np
import pandas as pd
import statistics
import matplotlib.pyplot as plt
import seaborn as sns

# sns.set_theme(style="darkgrid")

x_b = [1, 10, 100, 1000, 10000, 100000, 1000000]

cyc_pi2 = [8379072, 8379072, 3675200, 372864, 37312, 3728, 368]
cyc_pi4 = [8376016, 8376016, 8376016, 1865072, 186752, 18664, 1864]
cyc_lap = [8372616, 8372616, 8372616, 2145304, 214464, 21376, 2072]

# print("Correlation:", np.corrcoef(x_b, cyc_pi2))
# plt.bar(cyc_pi2, x_b , align='center', alpha=0.5)
# plt.legend(['CycloneDDS Laptop', 'CycloneDDS RPi4', 'CycloneDDS RPi2', 'FastDDS Laptop', 'FastDDS RP4'])
# plt.title('CycloneDDS')

barWidth = 0.25
x_pos = np.arange(len(x_b))
r1 = np.arange(len(cyc_lap))
r2 = [x + barWidth for x in r1]
r3 = [x + barWidth for x in r2]

'''
fig, ax = plt.subplots()
rects3 = ax.bar(x_pos - 2*width/3, cyc_lap, width, label='Laptop')
rects2 = ax.bar(x_pos + width/3, cyc_pi4, width, label='RPi4')
rects3 = ax.bar(x_pos + 3*width/3, cyc_pi2, width, label='RPi2')
'''

ax = plt.gca()
ax.tick_params(axis = 'both', which = 'major', labelsize = 22)
ax.tick_params(axis = 'both', which = 'minor', labelsize = 22)

plt.bar(r1, cyc_lap, width=barWidth, label='Laptop')
plt.bar(r2, cyc_pi4, width=barWidth, label='RPi4')
plt.bar(r3, cyc_pi2, width=barWidth, label='RPi2')


# plt.bar(x_pos, cyc_pi2, align='center', alpha=0.5)
# plt.xticks(x_pos, x_b)
plt.xticks([r + barWidth for r in range(len(cyc_lap))], x_b)
plt.ylabel('Bytes', fontsize=24)
plt.xlabel('Buffer Size', fontsize=24)
plt.title('IDL size Capacity (CycloneDDS)', fontsize=26)
plt.yscale('log')
plt.grid(b=True, which='both', color='#BBBBBB', linestyle='-', axis='y')
plt.legend(fontsize=24)

'''
plt.yscale('log')
plt.xlabel('Bytes')
plt.xticks(x_b)
plt.ylabel('Samples')
plt.grid(b=True, which='both', color='#BBBBBB', linestyle='-')
'''
plt.show()
