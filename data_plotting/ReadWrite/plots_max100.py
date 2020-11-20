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

x_b = [8, 128000, 256000, 384000, 512000, 640000]

cyc_lap_reli = [1036757.81, 14277.34, 7158.14, 3358.46, 2424.45, 1669.92]
cyc_lap_bf = [715886.12, 13685.5, 6928.79, 2787.69, 1801.53, 1438.3]
cyc_pi4_reli = [118100.02, 2193.85, 1064.41, 712.64, 534.71, 386.89]
cyc_pi4_bf = [106517.27, 2127.31, 1085.31, 712.02, 532.22, 266.24]
cyc_pi2_reli = [48220.89, 669.29, 319.39, 191.89, 135.85, 103.49]
cyc_pi2_bf = [42161.96, 685.47, 285.05, 150.69, 113.76, 68.96]

cyc_lap_reli_100 = [1055812.21, 14371.11, 7197.23, 3326.19, 2412.53, 1534.12]
cyc_lap_bf_100 = [716975.00, 13653.98, 6965.4, 2610.38, 1797.44, 1440.41]
cyc_pi4_reli_100 = [119599.04, 2180.59, 1061.93, 710.7, 536.08, 399.66]
cyc_pi4_bf_100 = [106784.54, 2115.39, 1094.64, 719.76, 528.24, 264.9]
cyc_pi2_reli_100 = [48959.21, 721.51, 337.28, 206.41, 154.84, 104.48]
cyc_pi2_bf_100 = [41619.89, 756.87, 295.94, 149.4, 112.11, 70.17]


'''
cyc_lap_reli_plot = pd.DataFrame({"Bytes":x_b, "Samples":cyc_lap_reli})
cyc_lap_bf_plot = pd.DataFrame({"Bytes":x_b, "Samples":cyc_lap_bf})
cyc_pi4_reli_plot = pd.DataFrame({"Bytes":x_b, "Samples":cyc_pi4_reli})
cyc_pi4_bf_plot = pd.DataFrame({"Bytes":x_b, "Samples":cyc_pi4_reli})
cyc_pi2_reli_plot = pd.DataFrame({"Bytes":x_b, "Samples":cyc_pi4_reli})
cyc_pi2_bf_plot = pd.DataFrame({"Bytes":x_b, "Samples":cyc_pi4_reli})

fast_lap_reli_plot = pd.DataFrame({"Bytes":x_b, "Samples":fast_lap_reli})
fast_lap_bf_plot = pd.DataFrame({"Bytes":x_b, "Samples":fast_lap_bf})
fast_pi4_reli_plot = pd.DataFrame({"Bytes":x_b, "Samples":fast_pi4_reli})
fast_pi4_bf_plot = pd.DataFrame({"Bytes":x_b, "Samples":fast_pi4_bf})
'''

# sns.lineplot(data=cyc_lap_reli_plot, x="Bytes", y="Samples")
# plt.show()

# plt.plot(x_b, cyc_lap_reli, '-o', x_b, cyc_pi4_reli, '-^', x_b, cyc_pi2_reli, '-s')
# plt.legend(['Laptop', 'RPi4', 'RPi2'])

# plt.plot(x_b, cyc_lap_bf, '-o', x_b, cyc_pi4_bf, '-^', x_b, cyc_pi2_bf, '-s')
# plt.legend(['Laptop', 'RPi4', 'RPi2'])

# plt.plot(x_b, fast_lap_reli, '-o', x_b, fast_pi4_reli, '-^')
# plt.legend(['Laptop', 'RPi4'])
# plt.plot(x_b, fast_lap_bf, '-o', x_b, fast_pi4_bf, '-^')
# plt.legend(['Laptop', 'RPi4'])

# plt.plot(x_b, fast_lap_reli, '-o', x_b, fast_pi4_reli, '-^')
# plt.legend(['Laptop', 'RPi4'])

# plt.plot(x_b, cyc_lap_reli, '-o', x_b, cyc_lap_bf, '-^')
# plt.legend(['Laptop Reliable', 'Laptop Best Effort'])

# plt.plot(x_b, fast_lap_reli, '-o', x_b, fast_lap_bf, '-^')
# plt.legend(['Laptop Reliable', 'Laptop Best Effort'])

ax = plt.gca()
ax.tick_params(axis = 'both', which = 'major', labelsize = 22)
ax.tick_params(axis = 'both', which = 'minor', labelsize = 22)


### CycloneDDS Reliable Buffer Size 1 vs. 100
# plt.plot(x_b, cyc_lap_reli, '-o', x_b, cyc_lap_reli_100, '-^', x_b, cyc_pi4_reli, '-s', x_b, cyc_pi4_reli_100, '-p', x_b, cyc_pi2_reli, '-D', x_b, cyc_pi2_reli_100, '-h', linewidth=4, markersize=12)
# plt.legend(['Laptop Buffer Size 1', 'Laptop Buffer Size 100', 'RPi4 Buffer Size 1', 'RPi4 Buffer Size 100', 'RPi2 Buffer Size 1', 'RPi2 Buffer Size 100'], fontsize=24)
# plt.title('CycloneDDS Reliable Buffer Size 1 vs. 100', fontsize=26)


### CycloneDDS Best Effort Buffer Size 1 vs. 100
plt.plot(x_b, cyc_lap_bf, '-o', x_b, cyc_lap_bf_100, '-^', x_b, cyc_pi4_bf, '-s', x_b, cyc_pi4_bf_100, '-p', x_b, cyc_pi2_bf, '-D', x_b, cyc_pi2_bf_100, '-h', linewidth=4, markersize=12)
plt.legend(['Laptop Buffer Size 1', 'Laptop Buffer Size 100', 'RPi4 Buffer Size 1', 'RPi4 Buffer Size 100', 'RPi2 Buffer Size 1', 'RPi2 Buffer Size 100'], fontsize=24)
plt.title('CycloneDDS Best Effort Buffer Size 1 vs. 100', fontsize=26)

plt.yscale('log')
plt.xlabel('Bytes', fontsize=24)
plt.xticks(x_b)
plt.ylabel('Samples', fontsize=24)
plt.grid(b=True, which='both', color='#BBBBBB', linestyle='-')
plt.show()
