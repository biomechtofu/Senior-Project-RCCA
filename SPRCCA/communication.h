#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QString>
#include "SerialPort.hpp"
#include <iostream>
#include <QList>
#include <QVector3D>
#include <QVariant>
#include <QHash>
#include <QByteArray>
#include <QModelIndex>
#include <QAbstractListModel>

using namespace std;

class Communication : public QAbstractListModel
{
    Q_OBJECT

public:
    Communication(QObject * parent = Q_NULLPTR);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int roll = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

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

private:
    QList<QVector3D> m_data;
};

#endif // COMMUNICATION_H
