#!/usr/bin/python3

import sys
import time
import array
import numpy as np
import pandas as pd
import statistics
import matplotlib.pyplot as plt

# sns.set_theme(style="darkgrid")

x_b = [128000, 256000, 384000]

cyc_lap_hist = [8879.3, 3614.61, 2561.99]
fast_lap_hist = [30078.25, 9681.68, 5200.07]

cyc_lap_reli = [14277.34, 7158.14, 3358.46]
fast_lap_reli = [132965.63, 64540.0, 42549.0]


ax = plt.gca()
ax.tick_params(axis = 'both', which = 'major', labelsize = 22)
ax.tick_params(axis = 'both', which = 'minor', labelsize = 22)


### CycloneDDS History vs. No History
# plt.plot(x_b, cyc_lap_hist, '-o', x_b, cyc_lap_reli, '-^', linewidth=4, markersize=12)
# plt.legend(['Laptop with History', 'Laptop without History'], fontsize=24)
# plt.title('Cyclone DDS History vs. No History', fontsize=26)

### FastDDS History vs. No History
plt.plot(x_b, fast_lap_hist, '-o', x_b, fast_lap_reli, '-^', linewidth=4, markersize=12)
plt.legend(['Laptop with History', 'Laptop without History'], fontsize=24)
plt.title('Fast DDS History vs. No History', fontsize=26)

# plt.yscale('log')
plt.xlabel('Bytes', fontsize=24)
plt.xticks(x_b)
plt.ylabel('Samples', fontsize=24)
plt.grid(b=True, which='both', color='#BBBBBB', linestyle='-')
plt.show()
