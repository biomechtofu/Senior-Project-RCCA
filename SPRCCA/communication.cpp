#include "communication.h"
#include "math.h"
#include <QtDataVisualization/QAbstract3DSeries>
#include <QQuickItem>
#include <QQuickView>
#include <QUrl>


using namespace QtDataVisualization;

const char *portName = "\\\\.\\COM3";

SerialPort *MCU;
#define DataLength 7

int tilt_pos;
int pan_pos;
int roll_pos;

Communication::Communication(QObject * parent) : QAbstractListModel(parent)
{
    MCU = new SerialPort(portName);
}

void Communication::up()
{
    const char InCmd[7] = {1,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::left()
{
    const char InCmd[7] = {2,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::right()
{
    const char InCmd[7] = {3,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::down()
{
    const char InCmd[7] = {4,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::in()
{
    const char InCmd[7] = {6,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::out()
{
    const char InCmd[7] = {5,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}


void Communication::tiltup()
{
    const char InCmd[7] = {7,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::tiltdown()
{
    const char InCmd[7] = {8,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::panleft()
{
    const char InCmd[7] = {9,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::panright()
{
    const char InCmd[7] = {10,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::rollleft()
{
    const char InCmd[7] = {11,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::rollright()
{
    const char InCmd[7] = {12,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}

void Communication::record()
{
    const char InCmd[7] = {13,0,0,0,0,0,0};
    char read[DataLength];
    int x_pos;
    int y_pos;
    int z_pos;

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
        int has_Read = MCU->readSerialPort(read, DataLength);
        if(has_Read)
        {
            tilt_pos = read[1] | (read[2] << 8);
            pan_pos = read[3] | (read[4] << 8);
            roll_pos = read[5] | (read[6] << 8);

            x_pos = 1 * cos(tilt_pos/16 * 1.8);
            y_pos = 1 * cos(pan_pos/16 * 1.8);
            z_pos = 1 * sin(roll_pos/16 * 1.8);

            qDebug() << "Xpos" << x_pos;
            qDebug() << "Ypos" << y_pos;
            qDebug() << "Zpos" << z_pos;

            m_data.append(QVector3D(x_pos, y_pos, z_pos));
        }
    }
}

int Communication::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant Communication::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    QVector3D point = m_data[index.row()];

    switch(role)
    {
        case Qt::UserRole + 1: return point.x(); break;
        case Qt::UserRole + 2: return point.y(); break;
        case Qt::UserRole + 3: return point.z(); break;
    }
    return QVariant();
}

QHash<int, QByteArray> Communication::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[Qt::UserRole + 1] = "x";
        roles[Qt::UserRole + 2] = "y";
        roles[Qt::UserRole + 3] = "z";
        return roles;
}

void Communication::replay()
{
    const char InCmd[7] = {14,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}
