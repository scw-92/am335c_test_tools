#include "gpio_thread.h"
#include <QDebug>
#include <QThread>
gpio_thread *gpio_thread::my_g_thread = NULL;
QMutex *gpio_thread::mutex = new QMutex();
gpio_thread::gpio_thread(QObject *parent) : QObject(parent)
{
    //
}
void gpio_thread::free()
{
            if(my_g_thread)
            {
                mutex->lock();
                if(my_g_thread)
                {
                    delete my_g_thread;
                    my_g_thread = NULL;
                }
                mutex->unlock();
            }

}


gpio_thread * gpio_thread::gpio_thread_create()
{
    if(gpio_thread::my_g_thread == NULL)
    {
        gpio_thread::mutex->lock();
        if(gpio_thread::my_g_thread == NULL)
        {
            gpio_thread::my_g_thread = new gpio_thread();
        }
        gpio_thread::mutex->unlock();
        return my_g_thread;
    }
}


void gpio_thread::gpio_thread_stop()
{
    thread_flags = false;
}

void gpio_thread::thread_handle_fun()
{

    thread_flags = true;
    if(!my_timer)
    {
        my_timer = new QTimer(this);
        QObject::connect(my_timer, SIGNAL(timeout()), this, SLOT(auto_get_gpio_status()));
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

void gpio_thread::auto_get_gpio_status()
{


        int ret = -1;
        count_clean++;
        if(count_clean== 99)
        {
            count_clean =0;
        }

        for(int nu = 0;nu < this->gpio_out_count;nu++)
        {
           QThread::msleep(100);
            if(count_clean % 2 == 0 )
           {
               ret=  gpio_auto_test(gpio_out_array[nu],1);
           }else
           {
               ret=  gpio_auto_test(gpio_out_array[nu],0);
           }

            emit test_over((*gpio_out_map)[gpio_out_array[nu]],ret);


        }

//        for(int i = 0;i< gpio_in_count;i++)
//        {
//            QThread::msleep(100);
//            ret = gpio_get(gpio_in_array[i]);
//           // emit test_over((*gpio_out_map)[gpio_out_array[i]],ret);
//        }

//        for(int j = 0;j < ai_count;j++)
//        {
//            ai_bt_handle(ai_array[j]);
//        }


        if(!thread_flags)
        {
            if(my_timer->isActive())
            {
                my_timer->stop();
                tmier_start = false;
                emit thread_stop_ok();
            }
        }
}

int gpio_thread::gpio_get(int nu)
{
    char cmd[100] = {0};
    int  value     =-1;
    sprintf(cmd,"cd /sys/class/gpio && echo %d > export",nu,nu);
    system(cmd);
    memset(cmd,0,100);
    sprintf(cmd,"cd  /sys/class/gpio/gpio%d",nu);
    if(system(cmd)!=0)
    {
        qDebug()<< "echo -1";
        (*gpio_in_map)[nu]->setProperty("source","qrc:/images/no_avi.png");
        return -1;//no_avi
    }else
    {
        memset(cmd,0,100);
        sprintf(cmd,"/sys/class/gpio/gpio%d/value",nu);
        p.start("cat",QStringList()<<cmd);
        p.waitForFinished();
        qDebug()<<"gpio-get";
        value  = p.readAll().toInt();
        qDebug()<<"value"<<value;
//*/        switch(value)
//        {
//        case -1:
//            (*gpio_int_map)[nu]->setProperty("source","qrc:/images/no_avi.png");
//            break;
//        case 0:
//            (*gpio_int_map)[nu]->setProperty("source","qrc:/images/ok_0.png");
//            break;
//        case 1:
//            (*gpio_int_map)[nu]->setProperty("source","qrc:/images/ok_1.png");
//            break;

//        }*/
    }





}
//void gpio_thread::ai_bt_handle(int nu)
//{
//   // this->mio1_4->setProperty("source","qrc:/images/ok_0.png");
//    char   cmd[100] = {0};
//    double  voltage  = 0;
//    int    count    = 0 ;
//    sprintf(cmd,"ls /sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);

//    if(system(cmd) != 0)
//    {
//        (*ai_map)[nu]->setProperty("text","不可用");
//    }else
//    {
//        memset(cmd,0,100);
//        sprintf(cmd,"/sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);
//        p.start("cat",QStringList()<<cmd);
//        p.waitForFinished();
//        count  = p.readAll().toInt();

//        voltage = 8.946 * count / 6756.75;

//       QMetaObject::invokeMethod((*ai_map)[nu], "set_text",Q_ARG(QVariant,voltage));

//    }

//}


int gpio_thread::gpio_auto_test(int nu,int value)
{
    char cmd[100] = {0};

    sprintf(cmd,"cd /sys/class/gpio && echo %d > export && cd gpio%d && echo out > direction",nu,nu);
    system(cmd);
    memset(cmd,0,100);
    sprintf(cmd,"cd  /sys/class/gpio/gpio%d",nu);
    if(system(cmd)!=0)
    {

        qDebug()<< "echo -1";
        return -1;//no_avi
    }

    memset(cmd,0,100);
    if(value)
    {
        sprintf(cmd,"echo 1 >  /sys/class/gpio/gpio%d/value",nu);
        if(system(cmd)==0)
        {
             qDebug()<< "echo 1";
            return 1;

        }else
        {
            return -1;
        }

    }else
    {
        sprintf(cmd,"echo 0 >  /sys/class/gpio/gpio%d/value",nu);
        if(system(cmd) == 0)
        {
            qDebug()<< "echo 0";
            return 0;


        }else
        {
            return -1;
        }

    }
}
