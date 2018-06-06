#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include "equipment_thread.h"
class Equipment : public QObject
{
    Q_OBJECT
    friend class main_ui;
    static Equipment * equipment_create(QObject * parent);
    static void free();
    static QMutex *mutex ;
    static Equipment *my_equipment;
public:


signals:
    void equipment_setup_ok();
    void equipment_thread_tiemr_stop();
public slots:
    void equipment_setup();
    void thread_deal_fun();
    void equipment_second_setup();
    void auto_detection_deal(QString str);
private:
   explicit Equipment(QObject *parent = 0);
   QObject                 * sd               = NULL;
   QObject                 * rtc              = NULL;
   QObject                 * i2c2             = NULL;
   QObject                 * usb2             = NULL;
   QThread                 * equipment_thread = NULL;
   Equipment_thread        * my_e_thread      = NULL;


};

#endif // EQUIPMENT_H
