# -*- coding: utf-8 -*-
"""
Created on Mon Dec  9 21:38:21 2019

@author: Andrew Kwok
"""

<<<<<<< HEAD
=======
import tkinter

from matplotlib.backends.backend_tkagg import(
    FigureCanvasTkAgg, NavigationToolbar2Tk)

from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure

>>>>>>> 5e91394118c8ae556e0e5e693a13c55cc533b51b
from mpl_toolkits import mplot3d

##%matplotlib inline
import numpy as np
import matplotlib.pyplot as plt

<<<<<<< HEAD
fig = plt.figure()
ax = plt.axes(projection='3d')

# Data for a three-dimensional line
#zline = np.linspace(0, 15, 10) ##start, stop, samples
#xline = np.sin(zline)
#yline = np.cos(zline)

zbox = np.array([0, 10, 10, 10, 10, 0, 0, 10, 10, 0, 0, 0, 10, 10])
xbox = np.array([0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0, 10, 10, 0])
ybox = np.array([0, 0, 10, 10, 0, 0, 10, 10, 10, 10, 0, 0, 0, 0])
=======
root = tkinter.Tk()
root.wm_title("Embedding in TK")
>>>>>>> 5e91394118c8ae556e0e5e693a13c55cc533b51b

zline = np.array([1, 5, 10, 35, 1])
xline = np.array([3, 5, 70, 20, 3])
yline = np.array([2, 5, 20, 50, 2])

<<<<<<< HEAD
ax.plot3D(xline, yline, zline, 'red')

ax.plot3D(xbox, ybox, zbox, 'gray')
=======
fig = Figure(figsize=(5,4), dpi=300)
t = np.arange(0, 3, .01)
fig.add_subplot(111, projection='3d').plot3D(xline, yline, zline, 'red')

canvas = FigureCanvasTkAgg(fig, master=root) #A tk.DrawingArea
canvas.draw()
canvas.get_tk_widget().pack(side=tkinter.TOP, expand=1)

toolbar = NavigationToolbar2Tk(canvas, root)
toolbar.update()
canvas.get_tk_widget().pack(side=tkinter.TOP, expand=1)

def on_key_press(event):
    print("you pressed {}".format(event.key))
    key_press_handler(event, canvas, toolbar)
    
canvas.mpl_connect("key_press_event", on_key_press)

def _quit():
    root.quit() # stops mainloop
    root.destroy() # this is necessary on windows to prevent
                   # Fatal Python Error: PyEval_RestoreThread: NULL tstate
    
button = tkinter.Button(master=root, text="Quit", width=10, command=_quit)
button.place(x=20,y=20)

tkinter.mainloop()
>>>>>>> 5e91394118c8ae556e0e5e693a13c55cc533b51b
