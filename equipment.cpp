#include "equipment.h"
#include <QDebug>

QMutex    *Equipment::mutex          = new  QMutex();
Equipment *Equipment::my_equipment   = NULL;
Equipment::Equipment(QObject *parent) : QObject(parent)
{

}
void Equipment::equipment_setup()
{
    equipment_thread        = new QThread(this);
    my_e_thread             = Equipment_thread::equipment_thread_create();

    my_e_thread->sd         = this->sd;
    my_e_thread->i2c2       = this->i2c2;
    my_e_thread->usb2       = this->usb2;
    my_e_thread->rtc        = this->rtc;
            //my_e_thread

    my_e_thread->moveToThread(equipment_thread);
    qDebug()<<"equipment_set";
    QObject::connect(this,&Equipment::equipment_setup_ok,my_e_thread,&Equipment_thread::thread_handle_fun);
    QObject::connect(this,&Equipment::equipment_thread_tiemr_stop,my_e_thread,&Equipment_thread::mytimer_stop);
    QObject::connect(my_e_thread,&Equipment_thread::auto_detection_signal,this,&Equipment::auto_detection_deal);
    //QObject::connect(my_e_thread,&Equipment_thread::pthread_stop,this,&Equipment::thread_deal_fun);
    equipment_thread->start();
    emit equipment_setup_ok();

}
void Equipment::equipment_second_setup()
{
    equipment_thread->start();
    emit equipment_setup_ok();
}
Equipment * Equipment::equipment_create(QObject * parent)
{
    if(!my_equipment)
    {
        mutex->lock();
        if(!my_equipment)
        {
            my_equipment = new Equipment(parent);
        }
        mutex->unlock();
    }
    return my_equipment;
}

void Equipment::free()
{
    if(!my_equipment)
    {
        mutex->lock();
        if(!my_equipment)
        {
            //my_equipment = new Equipment(parent);
            delete my_equipment;
            my_equipment = NULL;
        }
        mutex->unlock();
    }
}

void Equipment::thread_deal_fun()
{
    emit equipment_thread_tiemr_stop();
    if(equipment_thread && my_e_thread )
    {
        equipment_thread->quit();
        equipment_thread->wait();
       // Equipment_thread::free();
    }

}
void Equipment::auto_detection_deal(QString str)
{


    if(!str.compare("usb_ok"))
    {
        //qDebug()<<"usbojk";
       // this->usb1->setProperty("source","qrc:/images/avi.png");
        this->usb2->setProperty("source","qrc:/images/avi.png");
    }else if(!str.compare("usb_no"))
    {
        //this->usb1->setProperty("source","qrc:/images/no_avi.png");
        this->usb2->setProperty("source","qrc:/images/no_avi.png");
    }else if(!str.compare("sd_ok"))
    {
        this->sd->setProperty("source","qrc:/images/avi.png");
    }else if(!str.compare("sd_no"))
    {
        this->sd->setProperty("source","qrc:/images/no_avi.png");
    }else if(!str.compare("rtc_ok"))
    {
        this->rtc->setProperty("source","qrc:/images/avi.png");
    }else if(!str.compare("rtc_no"))
    {
        this->rtc->setProperty("source","qrc:/images/no_avi.png");
    }else if(!str.compare("sht30_ok"))
    {
        this->i2c2->setProperty("source","qrc:/images/avi.png");
    }else if(!str.compare("sht30_no"))
    {
        this->i2c2->setProperty("source","qrc:/images/no_avi.png");
    }
}
