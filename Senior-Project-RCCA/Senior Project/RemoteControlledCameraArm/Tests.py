# -*- coding: utf-8 -*-
"""
Created on Mon Dec  9 21:38:21 2019

@author: Andrew Kwok
"""

from mpl_toolkits import mplot3d

##%matplotlib inline
import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = plt.axes(projection='3d')

# Data for a three-dimensional line
#zline = np.linspace(0, 15, 10) ##start, stop, samples
#xline = np.sin(zline)
#yline = np.cos(zline)

zbox = np.array([0, 10, 10, 10, 10, 0, 0, 10, 10, 0, 0, 0, 10, 10])
xbox = np.array([0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0, 10, 10, 0])
ybox = np.array([0, 0, 10, 10, 0, 0, 10, 10, 10, 10, 0, 0, 0, 0])

zline = np.array([1, 5, 10, 35, 1])
xline = np.array([3, 5, 70, 20, 3])
yline = np.array([2, 5, 20, 50, 2])

ax.plot3D(xline, yline, zline, 'red')

ax.plot3D(xbox, ybox, zbox, 'gray')