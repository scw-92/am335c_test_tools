#include "gpio.h"
#include <QMutex>
#include <QVariant>
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <QThread>
 static bool clicked_1_flags = false;
QMutex gpio_mutex ;
gpio* gpio::my_gpio = NULL;
bool gpio::auto_flags = true;


gpio::gpio(QObject *parent) : QObject(parent)
{
    //QProcess p = new QProcess();
    p.setProcessChannelMode(QProcess::MergedChannels);

    //unsigned int gpio_out_array[5]  = {22,23,29,115,116};
    //unsigned int gpio_in_array[2]   = {45,46};
    gpio_out_map = new QMap<int, QObject *>();
    gpio_in_map  = new QMap<int, QObject *>();
    ai_map       = new QMap<int, QObject *>();
   // qDebug()<<gpio_out_map<<gpio_in_map;

    my_timer    = new QTimer(this);
    QObject::connect(my_timer, SIGNAL(timeout()), this, SLOT(auto_get_gpio_status()));


}
gpio* gpio::gpio_create(QObject *parent )
{
    if(my_gpio == NULL)
    {
        gpio_mutex.lock();
        if(my_gpio == NULL)
        {
            my_gpio = new gpio(parent);
        }
        gpio_mutex.unlock();
    }
    return my_gpio;
}


void gpio::free()
{
    if(my_gpio!=NULL)
    {
        gpio_mutex.lock();
        if(my_gpio!=NULL)
        {
            delete(my_gpio);
            my_gpio = NULL;
        }
        gpio_mutex.unlock();
    }
}void gpio::gpio_setup()
{
    //QObject::connect(my_gpio->led1_bt,SING,my_gpio,&gpio::gpio_setup);
    QObject::connect(my_gpio->led6_bt,  SIGNAL(send(int)),this,SLOT(led6_bt_handle(int)));
    QObject::connect(my_gpio->led3_bt,  SIGNAL(send(int)),this,SLOT(led3_bt_handle(int)));
    QObject::connect(my_gpio->led4_bt,  SIGNAL(send(int)),this,SLOT(led4_bt_handle(int)));
    QObject::connect(my_gpio->ai1_bt,   SIGNAL(send(int)),this,SLOT(ai1_bt_handle(int)));
    QObject::connect(my_gpio->ai2_bt,   SIGNAL(send(int)),this,SLOT(ai2_bt_handle(int)));
    QObject::connect(my_gpio->ai3_bt,   SIGNAL(send(int)),this,SLOT(ai3_bt_handle(int)));
    QObject::connect(my_gpio->ji116_bt, SIGNAL(send(int)),this,SLOT(ji116_bt_handle(int)));
    QObject::connect(my_gpio->ji115_bt, SIGNAL(send(int)),this,SLOT(ji115_bt_handle(int)));
    QObject::connect(my_gpio->auto_open_bt,SIGNAL(clicked()),this,SLOT(auto_open_handle()));
    QObject::connect(my_gpio->auto_close_bt,SIGNAL(clicked()),this,SLOT(auto_close_handle()));



}

void gpio::led6_bt_handle(int nu)
{
    switch(gpio_set(nu))
    {
    case -1:
        this->led6->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        this->led6->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        this->led6->setProperty("source","qrc:/images/ok_1.png");
        break;

    }

}

void gpio::led3_bt_handle(int nu)
{
    //this->led3->setProperty("source","qrc:/images/ok_0.png");
    switch(gpio_set(nu))
    {
    case -1:
        this->led3->setProperty("source","qrc:/images/no_avi.png");
        (*gpio_out_map)[23]->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        this->led3->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        this->led3->setProperty("source","qrc:/images/ok_1.png");
        break;

    }
}

void gpio::led4_bt_handle(int nu)
{
    //this->led4->setProperty("source","qrc:/images/ok_0.png");
    switch(gpio_set(nu))
    {
    case -1:
        this->led4->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        this->led4->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        this->led4->setProperty("source","qrc:/images/ok_1.png");
        break;

    }
}

void gpio::ji116_bt_handle(int nu)
{
    //this->mio1_1->setProperty("source","qrc:/images/ok_0.png");
    switch(gpio_set(nu))
    {
    case -1:
        this->ji116->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        this->ji116->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        this->ji116->setProperty("source","qrc:/images/ok_1.png");
        break;

    }
}

void gpio::ji115_bt_handle(int nu)
{
    //this->mio1_2->setProperty("source","qrc:/images/ok_0.png");
    switch(gpio_set(nu))
    {
    case -1:
        this->ji115->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        this->ji115->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        this->ji115->setProperty("source","qrc:/images/ok_1.png");
        break;

    }
}


void gpio::mio2_8_bt_handle(int nu)
{
    //this->mio1_3->setProperty("source","qrc:/images/ok_0.png");
    switch(gpio_set(nu))
    {
    case -1:
        this->mio2_8->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        this->mio2_8->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        this->mio2_8->setProperty("source","qrc:/images/ok_1.png");
        break;

    }
}
void gpio::mio2_7_bt_handle(int nu)
{
    //this->mio1_3->setProperty("source","qrc:/images/ok_0.png");
    switch(gpio_set(nu))
    {
    case -1:
        this->mio2_7->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        this->mio2_7->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        this->mio2_7->setProperty("source","qrc:/images/ok_1.png");
        break;

    }
}
void gpio::ai1_bt_handle(int nu)
{
   // this->mio1_4->setProperty("source","qrc:/images/ok_0.png");
    char   cmd[100] = {0};
    double  voltage  = 0;
    int    count    = 0 ;
    sprintf(cmd,"ls /sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);

    if(system(cmd) != 0)
    {
        this->ai1->setProperty("text","不可用");
    }else
    {
        memset(cmd,0,100);
        sprintf(cmd,"/sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);
        p.start("cat",QStringList()<<cmd);
        p.waitForFinished();
        count  = p.readAll().split('\n')[0].toInt();
        voltage = count * 1.8 / 4095 / 0.09;

       QMetaObject::invokeMethod(ai1, "set_text",Q_ARG(QVariant,voltage));

    }

}
void gpio::ai2_bt_handle(int nu)
{
   // this->mio1_4->setProperty("source","qrc:/images/ok_0.png");
    char   cmd[100] = {0};
    double  voltage  = 0;
    int    count    = 0 ;
    sprintf(cmd,"ls /sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);

    if(system(cmd) != 0)
    {
        this->ai2->setProperty("text","不可用");
    }else
    {
        memset(cmd,0,100);
        sprintf(cmd,"/sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);
        p.start("cat",QStringList()<<cmd);
        p.waitForFinished();
        count  = p.readAll().split('\n')[0].toInt();

        voltage = count * 1.8 / 4095 / 0.09;

       QMetaObject::invokeMethod(ai2, "set_text",Q_ARG(QVariant,voltage));

    }

}

void gpio::ai3_bt_handle(int nu)
{
   // this->mio1_4->setProperty("source","qrc:/images/ok_0.png");
    char   cmd[100] = {0};
    double  voltage  = 0;
    int    count    = 0 ;
    sprintf(cmd,"ls /sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);

    if(system(cmd) != 0)
    {
        this->ai3->setProperty("text","不可用");
    }else
    {
        memset(cmd,0,100);
        sprintf(cmd,"/sys/bus/iio/devices/iio:device0/in_voltage%d_raw",nu);
        p.start("cat",QStringList()<<cmd);
        p.waitForFinished();
        count  = p.readAll().split('\n')[0].toInt();

       // qDebug()<<"------------ai3---------->"<<count;
        voltage = count * 1.8 / 4095 / 0.09;

       QMetaObject::invokeMethod(ai3, "set_text",Q_ARG(QVariant,voltage));

    }

}



int gpio::gpio_set(int nu)
{


    char cmd[100] = {0};

    sprintf(cmd,"cd /sys/class/gpio && echo %d > export && cd gpio%d && echo out > direction",nu,nu);
    system(cmd);
    memset(cmd,0,100);
    sprintf(cmd,"cd  /sys/class/gpio/gpio%d",nu);
   // qDebug()<< "echo -3";
    if(system(cmd)!=0)
    {

        qDebug()<< "echo -1";
        return -1;
    }
   // qDebug()<< "echo -2";
    memset(cmd,0,100);
    if(clicked_1_flags == false)
    {
        sprintf(cmd,"echo 1 >  /sys/class/gpio/gpio%d/value",nu);
        clicked_1_flags = true;
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
        clicked_1_flags = false;
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
void gpio::g_stop_thread()
{

    emit g_stop_thread_sin();
}
void gpio::auto_open_handle()
{

    if(!thread_start_flags)
    {

        g_qthread = new QThread(this);
        g_thread  = gpio_thread::gpio_thread_create();


        g_thread->led3 = this->led3;

        g_thread->led6 = this->led6;
        g_thread->led4 = this->led4;
        g_thread->ai1 = this->ai1;
        g_thread->ai2 = this->ai2;
        g_thread->ai3 = this->ai3;
        g_thread->ji115 = this->ji115;
        g_thread->ji116 = this->ji116;
        g_thread->mio2_8 = this->mio2_8;
        g_thread->mio2_7 = this->mio2_7;

        g_thread->gpio_out_map = this->gpio_out_map;
        g_thread->gpio_in_map  = this->gpio_in_map;
        g_thread->ai_map       = this->ai_map;


        g_thread->moveToThread(g_qthread);
        QObject::connect(this,&gpio::thread_start,this->g_thread,&gpio_thread::thread_handle_fun);
        QObject::connect(this->g_thread,&gpio_thread::thread_stop_ok,this,&gpio::thread_stop_handle);
        QObject::connect(this,&gpio::g_stop_thread_sin,g_thread,&gpio_thread::gpio_thread_stop);
        QObject::connect(g_thread,&gpio_thread::test_over,this,&gpio::test_show);
       //qDebug()<<"---------------------------"<< (*g_thread->gpio_in_map)[45];
       g_qthread->start();
       g_thread->thread_flags = true;
       emit thread_start();
       thread_start_flags = true;
    }else
    {
        if(!g_thread->thread_flags)
        {
            g_qthread->start();
            g_thread->thread_flags = true;
            emit thread_start();
        }
    }


    if(!my_timer_flags)
    {
             if(!my_timer->isActive())
            {
                my_timer->start(2000);
                my_timer_flags = true;
            }

    }

}


void gpio::auto_get_gpio_status()
{
    int ret = -1;
    ai3_bt_handle(2);
    ai2_bt_handle(1);
    ai1_bt_handle(0);
    gpio_get(45);
    gpio_get(46);


}


int gpio::gpio_get(int nu)
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
        value  = p.readAll().split('\n')[0].toInt();

        //qDebug()<<"---------------------------gpio-get:"<< p.readAll().split('\n')[0].toInt();
        switch(value)
        {
        case -1:
            (*gpio_in_map)[nu]->setProperty("source","qrc:/images/no_avi.png");
            break;
        case 0:
            (*gpio_in_map)[nu]->setProperty("source","qrc:/images/ok_0.png");
            break;
        case 1:
            (*gpio_in_map)[nu]->setProperty("source","qrc:/images/ok_1.png");
            break;

        }
    }


}



void gpio::test_show(QObject *object ,int ret)
{
    switch(ret)
    {
    case -1:
        object->setProperty("source","qrc:/images/no_avi.png");
        break;
    case 0:
        object->setProperty("source","qrc:/images/ok_0.png");
        break;
    case 1:
        object->setProperty("source","qrc:/images/ok_1.png");
        break;

    }

}

void gpio::thread_stop_handle()
{
    g_thread->thread_flags = false;
    if(g_thread && g_qthread )
    {
        g_qthread->quit();
        g_qthread->wait();
        qDebug()<<"g_thread_stop_ok";
       // Equipment_thread::free();
    }
}

void gpio::auto_close_handle()
{
    //gpio::auto_flags = false;
    g_thread->thread_flags = false;


    if(my_timer_flags)
    {
             if(my_timer->isActive())
            {
                my_timer->stop();
                my_timer_flags = false;
            }

    }

}


