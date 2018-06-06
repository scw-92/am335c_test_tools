#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <QObject>
#include "QmlPort.h"
#include <QQmlApplicationEngine>
#include <list>
#include <QDebug>
#include <QVariant>
#include <QBitArray>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "gpio.h"
#include "equipment.h"
#include "protocol.h"


class main_ui : public QObject
{
    Q_OBJECT
public:

    explicit main_ui(QObject *parent = 0);
    void  port_handle();
    void  gpio_handle();
    void  equipment_handle();
    void  protocol_handle();

signals:
    void port_handle_ok();
    void gpio_handle_ok();
    void equipment_handle_ok();
    void equipment_timer_stop();
    void my_equipment_second_setup();
    void gpio_timer_stop();
    void protocol_handle_ok();


public slots:
    void qml_model_prase(QString des,QString src);
   // void  port_handle();

private:
    QQmlApplicationEngine  *engine              = NULL;
    QList<QObject *>       object;
    QList<QObject *>       object_tools;
    QObject                *ApplicationWindow   = NULL;
    QObject                *listView            = NULL;
    QObject                *stackView           = NULL;
    QObject                *page_des            = NULL;
    QObject                *page_src            = NULL;
    QmlPort                *qml_port            = NULL;
    gpio                   *my_gpio             = NULL;
    Protocol               *my_protocol         = NULL;
    Equipment              *my_equipment         = NULL;
};

#endif // MAIN_UI_H
