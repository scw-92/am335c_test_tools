#ifndef PORT_READ_THREAD_H
#define PORT_READ_THREAD_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QThread>
#include <QEventLoop>
#include <QtSerialPort/QSerialPort>

class port_read_thread : public QObject
{
    Q_OBJECT
public:

    static port_read_thread * port_read_thread_create();
    static void port_read_thread_free();
    void port_read_thread_fun();
    bool port_on_is_ok = false;
    bool tmier_start  =  false;
    friend class QmlPort;
signals:
   void port_read_thread_died(QString str);
   void port_read_over_signals(QByteArray);

public slots:
   void port_data_read();
private:
    explicit port_read_thread(QObject *parent = 0);
    QTimer                     *timer    = NULL;
    QEventLoop                 *loop     = NULL;
    static port_read_thread    *port_read_th;
    QSerialPort                *myCom    = NULL;
    long                       set_time  = 0 ;
    QByteArray                 readComData ;

};

#endif // PORT_READ_THREAD_H
