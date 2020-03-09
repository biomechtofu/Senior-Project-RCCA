/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *In;
    QPushButton *Out;
    QPushButton *Up;
    QPushButton *Let;
    QPushButton *Right;
    QPushButton *Down;
    QPushButton *Control;
    QPushButton *Record;
    QPushButton *Replay;
    QPushButton *Quit;
    QWidget *Graph;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1216, 670);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        In = new QPushButton(centralwidget);
        In->setObjectName(QString::fromUtf8("In"));
        In->setGeometry(QRect(10, 10, 151, 61));
        Out = new QPushButton(centralwidget);
        Out->setObjectName(QString::fromUtf8("Out"));
        Out->setGeometry(QRect(260, 10, 161, 61));
        Up = new QPushButton(centralwidget);
        Up->setObjectName(QString::fromUtf8("Up"));
        Up->setGeometry(QRect(120, 90, 171, 61));
        Let = new QPushButton(centralwidget);
        Let->setObjectName(QString::fromUtf8("Let"));
        Let->setGeometry(QRect(10, 160, 161, 71));
        Right = new QPushButton(centralwidget);
        Right->setObjectName(QString::fromUtf8("Right"));
        Right->setGeometry(QRect(250, 160, 171, 71));
        Down = new QPushButton(centralwidget);
        Down->setObjectName(QString::fromUtf8("Down"));
        Down->setGeometry(QRect(120, 240, 171, 61));
        Control = new QPushButton(centralwidget);
        Control->setObjectName(QString::fromUtf8("Control"));
        Control->setGeometry(QRect(120, 330, 171, 61));
        Record = new QPushButton(centralwidget);
        Record->setObjectName(QString::fromUtf8("Record"));
        Record->setGeometry(QRect(120, 410, 171, 61));
        Replay = new QPushButton(centralwidget);
        Replay->setObjectName(QString::fromUtf8("Replay"));
        Replay->setGeometry(QRect(120, 490, 171, 61));
        Quit = new QPushButton(centralwidget);
        Quit->setObjectName(QString::fromUtf8("Quit"));
        Quit->setGeometry(QRect(10, 570, 151, 51));
        Graph = new QWidget(centralwidget);
        Graph->setObjectName(QString::fromUtf8("Graph"));
        Graph->setGeometry(QRect(440, 10, 761, 611));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        Graph->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1216, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        In->setText(QCoreApplication::translate("MainWindow", "In", nullptr));
        Out->setText(QCoreApplication::translate("MainWindow", "Out", nullptr));
        Up->setText(QCoreApplication::translate("MainWindow", "Up", nullptr));
        Let->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        Right->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        Down->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        Control->setText(QCoreApplication::translate("MainWindow", "Arm Control", nullptr));
        Record->setText(QCoreApplication::translate("MainWindow", "Record", nullptr));
        Replay->setText(QCoreApplication::translate("MainWindow", "Replay", nullptr));
        Quit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
