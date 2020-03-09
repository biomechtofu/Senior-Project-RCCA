#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QString>
#include "SerialPort.hpp"
#include <iostream>

class Communication : public QObject
{
    Q_OBJECT

public:
    Communication();

public slots:
    void up();
    void down();
    void left();
    void right();
    void in();
    void out();
    void tiltup();
    void tiltdown();
    void panleft();
    void panright();
    void rollleft();
    void rollright();
    void record();
    void replay();
};

#endif // COMMUNICATION_H
