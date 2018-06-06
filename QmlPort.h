#ifndef PORT_H
#define PORT_H

#include <QObject>
//#include <main_ui.h>
#include <QVariant>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "port_read_thread.h"
#include "port_write_thread.h"
#include <QThread>
#include <QDebug>

class QmlPort : public QObject
{
    Q_OBJECT
public:

    static QmlPort* create_qml_port(QObject *parent);
    //static void free_qml_port();
    static void free();
    friend class main_ui;

signals:
    void port_read_signals();
    void port_write_signals();


public slots:
  void  port_setup();
  void  port_on_handle();
  void  port_close_handle();
  void  deal_thread(QString str);
  void  port_data_recv_fun(QByteArray);

private:
    explicit QmlPort(QObject *parent = 0);
    void my_com_setup();
    int port_read_thread_setup();
    int port_write_thread_setup();
    QObject         *port_nu_file;
    QObject         *port_data_bit;
    QObject         *port_speed;
    QObject         *port_stop;
    QObject         *port_check;
    QObject         *port_flow_con;
    QObject         *port_recv_time;
    QObject         *port_send_time;
    QObject         *port_on;
    QObject         *port_close;
    QObject         *port_data_recv;
    QObject         *port_data_send;
    static QmlPort  *my_qml_port;
    bool             qml_port_on              = false;
    bool             qml_port_thread_read_on  = false;
    bool             my_com_setup_on          = false;
    bool             qml_port_thread_write_on = false;
    QSerialPort     *myCom                    = NULL;
    QThread         *port_read_thd            = NULL;
    QThread         *port_write_thd           = NULL;
    port_read_thread *port_read_th            = NULL;
    port_write_thread *port_write_th          = NULL;
    int               port_read_count = 0;

    //port_read_thread *port_read_th;



};


#endif // PORT_H
