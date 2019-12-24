# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'SPRCCA_GUI.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1127, 665)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.QuitButton = QtWidgets.QPushButton(self.centralwidget)
        self.QuitButton.setGeometry(QtCore.QRect(10, 550, 161, 61))
        self.QuitButton.setObjectName("QuitButton")
        self.UpButton = QtWidgets.QPushButton(self.centralwidget)
        self.UpButton.setGeometry(QtCore.QRect(160, 20, 161, 61))
        self.UpButton.setObjectName("UpButton")
        self.RightButton = QtWidgets.QPushButton(self.centralwidget)
        self.RightButton.setGeometry(QtCore.QRect(310, 100, 161, 61))
        self.RightButton.setObjectName("RightButton")
        self.DownButton = QtWidgets.QPushButton(self.centralwidget)
        self.DownButton.setGeometry(QtCore.QRect(160, 180, 161, 61))
        self.DownButton.setObjectName("DownButton")
        self.LeftButton = QtWidgets.QPushButton(self.centralwidget)
        self.LeftButton.setGeometry(QtCore.QRect(10, 100, 161, 61))
        self.LeftButton.setObjectName("LeftButton")
        self.Control = QtWidgets.QPushButton(self.centralwidget)
        self.Control.setGeometry(QtCore.QRect(160, 310, 161, 61))
        self.Control.setObjectName("Control")
        self.RecordButton = QtWidgets.QPushButton(self.centralwidget)
        self.RecordButton.setGeometry(QtCore.QRect(160, 390, 161, 61))
        self.RecordButton.setObjectName("RecordButton")
        self.ReplayButton = QtWidgets.QPushButton(self.centralwidget)
        self.ReplayButton.setGeometry(QtCore.QRect(160, 470, 161, 61))
        self.ReplayButton.setObjectName("ReplayButton")
        self.GraphGui = QtWidgets.QWidget(self.centralwidget)
        self.GraphGui.setGeometry(QtCore.QRect(490, 10, 621, 601))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.GraphGui.sizePolicy().hasHeightForWidth())
        self.GraphGui.setSizePolicy(sizePolicy)
        self.GraphGui.setObjectName("GraphGui")
        self.mplvl = QtWidgets.QVBoxLayout(self.GraphGui)
        self.mplvl.setContentsMargins(0, 0, 0, 0)
        self.mplvl.setObjectName("mplvl")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1127, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.QuitButton.setText(_translate("MainWindow", "Quit"))
        self.UpButton.setText(_translate("MainWindow", "Up"))
        self.RightButton.setText(_translate("MainWindow", "Right"))
        self.DownButton.setText(_translate("MainWindow", "Down"))
        self.LeftButton.setText(_translate("MainWindow", "Left"))
        self.Control.setText(_translate("MainWindow", "Arm Control"))
        self.RecordButton.setText(_translate("MainWindow", "Record"))
        self.ReplayButton.setText(_translate("MainWindow", "Replay"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
