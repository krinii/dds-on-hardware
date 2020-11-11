#!/usr/bin/python3

import sys
import time
import array
import numpy as np
from random import randint, seed
import csv
import os
import statistics
import matplotlib.pyplot as plt

filepath1 = ""


# filename1 = filepath1 + "test_8_bytes.txt"
filename1 = filepath1 + "test_DEPTH100.txt"


filenames_X = [filename1]

samples = []
cycles = 0

for i in range(len(filenames_X)):
    with open(filenames_X[i], newline='') as f1:
        csvReader = csv.reader(f1, delimiter=',')
        for row in csvReader:
            if int(row[1]) < 1500000:
                samples.append(int(row[1]))
                cycles = cycles + 1

np.histogram(samples)

print("Filename: ", filename1)

print("All samples:", sum(samples))

print("Number of cycles:", cycles)

print("Standard Deviation:", statistics.stdev(samples))

print("Average Samples", sum(samples)/cycles)
"""
rng = np.random.RandomState(10)  # deterministic random data
a = np.hstack((rng.normal(size=1000),
               rng.normal(loc=5, scale=2, size=1000)))
_ = plt.hist(a, bins='auto')  # arguments are passed to np.histogram
plt.title("Histogram with 'auto' bins")
"""

rng = samples
a = np.hstack((rng, rng))
_ = plt.hist(a, bins='auto')  # arguments are passed to np.histogram
plt.title("Histogram with 'auto' bins")
plt.show()
