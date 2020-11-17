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

x_b = [1]

cyc_pi2 = [8379072]
cyc_pi4 = [8376016]
cyc_lap = [8372616]
fast_pi4 = [2739280]
fast_lap = [8334424]

# plt.bar(cyc_pi2, x_b , align='center', alpha=0.5)
# plt.legend(['CycloneDDS Laptop', 'CycloneDDS RPi4', 'CycloneDDS RPi2', 'FastDDS Laptop', 'FastDDS RP4'])
# plt.title('CycloneDDS')

barWidth = 0.35
x_pos = np.arange(len(x_b))
r1 = np.arange(len(cyc_lap))
r2 = [x + barWidth for x in r1]
r3 = [x + barWidth for x in r2]
r4 = [x + barWidth for x in r3]
r5 = [x + barWidth for x in r4]

'''
fig, ax = plt.subplots()
rects3 = ax.bar(x_pos - 2*width/3, cyc_lap, width, label='Laptop')
rects2 = ax.bar(x_pos + width/3, cyc_pi4, width, label='RPi4')
rects3 = ax.bar(x_pos + 3*width/3, cyc_pi2, width, label='RPi2')
'''
ax = plt.gca()
ax.tick_params(axis = 'both', which = 'major', labelsize = 22)
ax.tick_params(axis = 'both', which = 'minor', labelsize = 22)


plt.bar(r1, cyc_lap, width=barWidth, label='CycloneDDS Laptop')
plt.bar(r2, cyc_pi4, width=barWidth, label='CycloneDDS RPi4')
plt.bar(r3, cyc_pi2, width=barWidth, label='CycloneDDS RPi2')
plt.bar(r4, fast_lap, width=barWidth, label='FastDDS Laptop')
plt.bar(r5, fast_pi4, width=barWidth, label='FastDDS RPi4')

# plt.bar(x_pos, cyc_pi2, align='center', alpha=0.5)
# plt.xticks(x_pos, x_b)
plt.xticks([r + barWidth for r in range(len(cyc_lap))], x_b)
plt.ylabel('Bytes', fontsize=24)
plt.xlabel('Buffer Size', fontsize=24)
plt.title('CycloneDDS vs FastDDS', fontsize=26)
#plt.yscale('log')
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
