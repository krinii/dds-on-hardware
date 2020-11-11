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

fast_lap_reli = [887219.79, 132965.63, 64540.0, 42549.0, 32011.6, 24157.24]
fast_lap_bf = [981686.34, 134827.08, 66410.14, 43738.2, 32349.63, 25192.78]
fast_pi4_reli = [112713.44, 17442.75, 5669.85, 3172.47, 2246.29, 1672.18]
fast_pi4_bf = [120521.31, 17507.38, 5766.48, 3628.75, 2723.82, 2220.29]

cyc_lap_reli = [1036757.81, 14277.34, 7158.14, 3358.46, 2424.45, 1669.92]
cyc_lap_bf = [715886.12, 13685.5, 6928.79, 2787.69, 1801.53, 1438.3]
cyc_pi4_reli = [118100.02, 2193.85, 1064.41, 712.64, 534.71, 386.89]
cyc_pi4_bf = [106517.27, 2127.31, 1085.31, 712.02, 532.22, 266.24]
cyc_pi2_reli = [48220.89, 669.29, 319.39, 191.89, 135.85, 103.49]
cyc_pi2_bf = [42161.96, 685.47, 285.05, 150.69, 113.76, 68.96]


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

### Comparison Cyclone Laptop and FastDDS Laptop
# plt.plot(x_b, cyc_lap_reli, '-o', x_b, cyc_lap_bf, '-^', x_b, fast_lap_reli, '-s', x_b, fast_lap_bf, '-p')
# plt.legend(['CycloneDDS Laptop Reliable', 'CycloneDDS Laptop Best Effort', 'FastDDS Laptop Reliable', 'FastDDS Laptop Best Effort'])

### All CycloneDDS data
# plt.plot(x_b, cyc_lap_reli, '-o', x_b, cyc_lap_bf, '-^', x_b, cyc_pi4_reli, '-s', x_b, cyc_pi4_bf, '-p', x_b, cyc_pi2_reli, '-D', x_b, cyc_pi2_bf, '-h')
# plt.legend(['Laptop Reliable', 'Laptop Best Effort', 'RPi4 Reliable', 'RPi4 Best Effort', 'RPi2 Reliable', 'RPi2 Best Effort'])
# plt.title('CycloneDDS')

### All FastDDS data 
# plt.plot(x_b, fast_lap_reli, '-o', x_b, fast_lap_bf, '-^', x_b, fast_pi4_reli, '-s', x_b, fast_pi4_bf, '-p')
# plt.legend(['Laptop Reliable', 'Laptop Best Effort', 'RPi4 Reliable', 'RPi4 Best Effort'])
# plt.title('FastDDS')

### All Devices Reliable both Vendors 
plt.plot(x_b, cyc_lap_reli, '-o', x_b, cyc_pi4_reli, '-^', x_b, cyc_pi2_reli, '-s', x_b, fast_lap_reli, '-p', x_b, fast_pi4_reli, '-D')
plt.legend(['CycloneDDS Laptop', 'CycloneDDS RPi4', 'CycloneDDS RPi2', 'FastDDS Laptop', 'FastDDS RP4'])
# plt.title('CycloneDDS')

plt.yscale('log')
plt.xlabel('Bytes')
plt.xticks(x_b)
plt.ylabel('Samples')
plt.grid(b=True, which='both', color='#BBBBBB', linestyle='-')
plt.show()
