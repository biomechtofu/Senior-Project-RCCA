#include "communication.h"

const char *portName = "\\\\.\\COM3";

SerialPort *MCU;
#define DataLength 7

Communication::Communication()
{
    MCU = new SerialPort(portName);
}

void Communication::up()
{
    const char InCmd[7] = {1,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
    else
    {
        printf("No MCU connected");
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

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
        int has_Read = MCU->readSerialPort(read, DataLength);
        if(has_Read)
        {

        }
    }
}

void Communication::replay()
{
    const char InCmd[7] = {14,0,0,0,0,0,0};

    if(MCU->isConnected()){
        MCU->writeSerialPort(&InCmd[0], DataLength);
    }
}
