#ifndef PORT_WRITE_THREAD_H
#define PORT_WRITE_THREAD_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QThread>
#include <QEventLoop>
#include <QtSerialPort/QSerialPort>
class port_write_thread : public QObject
{
    Q_OBJECT
    friend class QmlPort;
public:
    static port_write_thread *port_write_thread_create();
    static void port_write_thread_free();
    void port_write_thread_fun();
    bool port_on_is_ok = false;
    bool port_write_ok_flags = false;
    bool timer_start         = false;

    QByteArray writeComData ;
    QObject                *port_data_send_area;

signals:
    void port_write_thread_died(QString str);
public slots:
    void port_data_write();
    //void port_write_thread_fun();
private:
   // QByteArray writearray;
    explicit port_write_thread(QObject *parent = 0);
    QTimer       *timer   = NULL;
    QEventLoop   *loop    = NULL;
    long         set_time = 0 ;
    QSerialPort *myCom    = NULL;
    static port_write_thread* port_write_th;
};

#endif // PORT_WRITE_THREAD_H
