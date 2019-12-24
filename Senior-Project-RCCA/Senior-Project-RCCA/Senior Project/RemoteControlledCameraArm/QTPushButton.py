# -*- coding: utf-8 -*-
"""
Created on Sun Dec 22 15:47:00 2019

@author: Andrew
"""

from PyQt5.uic import loadUiType

from matplotlib.figure import Figure
from matplotlib.backends.backend_qt5agg import (
        FigureCanvasQTAgg as FigureCanvas,
        NavigationToolbar2QT as NavigationToolbar)

#Return custom GUI app class, and base class of GUI app
Ui_MainWindow, QMainWindow = loadUiType('SPRCCA_GUI.ui')

class Main(QMainWindow, Ui_MainWindow):
    def __init__(self, ):
        super(Main,  self).__init__()
        self.setupUi(self)
        
if __name__ == '__main__':
    import sys
    from PyQt5 import QtGui
    
    app = QtGui(sys.argv)
    main = Main()
    main.show()
    sys.exit(app.exec_())