#include "equipment_thread.h"
#include <QDebug>
Equipment_thread *Equipment_thread::my_e_thread = NULL;
QMutex           *Equipment_thread::mutex       = new QMutex();

Equipment_thread::Equipment_thread(QObject *parent) : QObject(parent)
{


}
void Equipment_thread::thread_handle_fun()
{

    if(!my_timer)
    {
        my_timer = new QTimer(this);
        QObject::connect(my_timer, SIGNAL(timeout()), this, SLOT(auto_detection()));
    }
    if(!loop)
    {
        loop = new QEventLoop(this);
    }

     if(my_timer->isActive() == false)
     {
         my_timer->start(2000);
         tmier_start = true;
     }

    loop->exec();
}


Equipment_thread * Equipment_thread::equipment_thread_create()
{
    if(!my_e_thread)
    {
        mutex->lock();
        if(!my_e_thread)
        {
            my_e_thread = new Equipment_thread();
        }
        mutex->unlock();
    }
    return my_e_thread;
}

 void Equipment_thread::free()
 {
     if(my_e_thread)
     {
         mutex->lock();
         if(my_e_thread)
         {
             //my_equipment = new Equipment(parent);
             delete my_e_thread;
             my_e_thread = NULL;
         }
         mutex->unlock();
     }
 }

 void Equipment_thread::mytimer_stop()
 {
     if(tmier_start == true)
     {
         mutex->lock();
         if(tmier_start == true)
         {
              my_timer->stop();
              qDebug()<<" my_timer->stop";

             // emit pthread_stop();   //自定义的线程关闭信号。当线程关闭后，线程才会发出finshed的信号
              tmier_start = false;
         }
         mutex->unlock();
     }

 }
void Equipment_thread::auto_detection()
{


        qDebug()<<"e_thread-start";

        char cmd[100] = {0};

        sprintf(cmd,"ls /dev/input/mouse0");

        if(system(cmd)==0)
        {
            //this->usb1->setProperty("source","qrc:/images/ok.png");
            //this->usb2->setProperty("source","qrc:/images/ok.png");
            emit auto_detection_signal("usb_ok");

        }else
        {
            //this->usb1->setProperty("source","qrc:/images/no_avi.png");
            //this->usb2->setProperty("source","qrc:/images/no_avi.png");
            emit auto_detection_signal("usb_no");
        }

         memset(cmd,0,100);
         sprintf(cmd,"ls /dev/mmcblk0");
         if(system(cmd)==0)
         {
            // qDebug()<<"sd_ok";
              //this->sd->setProperty("source","qrc:/images/ok.png");
             emit auto_detection_signal("sd_ok");
         }else
         {
            // qDebug()<<"sd_no";

             //this->sd->setProperty("source","qrc:/images/no_avi.png");
             emit auto_detection_signal("sd_no");
         }

         memset(cmd,0,100);
         sprintf(cmd,"hwclock -r");
         if(system(cmd)==0)
         {
             emit auto_detection_signal("rtc_ok");
         }else
         {

             emit auto_detection_signal("rtc_no");
         }

         memset(cmd,0,100);
         sprintf(cmd,"sht30_test");
         if(system(cmd)==0)
         {
             emit auto_detection_signal("sht30_ok");
         }else
         {

             emit auto_detection_signal("sht30_no");
         }

}
