#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QMutex>
#include "ping.h"

#include <QTimer>

class Protocol : public QObject
{
    Q_OBJECT
    friend class main_ui;
public:
    static QMutex   *my_mutex ;
    static Protocol *     my_protocol;
    static Protocol *     protocol_create(QObject *parent = 0);
    static void           free();
    void showPingResult(PingResult pingResult);


signals:

public slots:
        void protocol_setup();
        void set_ip0_bt_handle();
        void set_ip1_bt_handle();
        void ping_bt_handle();
        void ping_timer_handle();
private:
     explicit Protocol(QObject *parent = 0);
     QObject            *local1_ip                       = NULL;
     QObject            *local0_ip                       = NULL;
     QObject            *t_machine_ip                    = NULL;
     QObject            *set_ip0_bt                      = NULL;
     QObject            *set_ip1_bt                      = NULL;
     QObject            *ping_bt                         = NULL;
     QObject            *ping_result                     = NULL;
     bool               timer_start_flasgs               =false;
     QTimer             *my_timer                        = NULL;



};

#endif // PROTOCOL_H
