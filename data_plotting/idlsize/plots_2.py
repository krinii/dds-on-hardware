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

fast_pi4 = [2739280]
fast_lap = [8334424]

# plt.bar(cyc_pi2, x_b , align='center', alpha=0.5)
# plt.legend(['CycloneDDS Laptop', 'CycloneDDS RPi4', 'CycloneDDS RPi2', 'FastDDS Laptop', 'FastDDS RP4'])
# plt.title('CycloneDDS')

barWidth = 0.25
width = 0.25
x_pos = np.arange(len(x_b))
r1 = np.arange(len(fast_lap))
r2 = [x + barWidth for x in r1]


fig, ax = plt.subplots()
rects3 = ax.bar(x_pos - width/2, fast_lap, width, label='Laptop')
rects2 = ax.bar(x_pos + width/2, fast_pi4, width, label='RPi4')


# plt.bar(r1, fast_lap, width=barWidth, label='Laptop')
# plt.bar(r2, fast_pi4, width=barWidth, label='RPi4')



# plt.bar(x_pos, cyc_pi2, align='center', alpha=0.5)
# plt.xticks(x_pos, x_b)
plt.xticks(x_pos, x_b)
plt.ylabel('Bytes')
plt.xlabel('Buffer Size')
plt.title('IDL size Capacity (FastDDS)')
#plt.yscale('log')
plt.grid(b=True, which='both', color='#BBBBBB', linestyle='-', axis='y')
plt.legend()

'''
plt.yscale('log')
plt.xlabel('Bytes')
plt.xticks(x_b)
plt.ylabel('Samples')
plt.grid(b=True, which='both', color='#BBBBBB', linestyle='-')
'''
plt.show()
