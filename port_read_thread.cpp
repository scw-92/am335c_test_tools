
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include "port_read_thread.h"
#include <QMutex>
QMutex mutex_read_thread;
port_read_thread * port_read_thread::port_read_th = NULL;
port_read_thread::port_read_thread(QObject *parent) : QObject(parent)
{
       myCom = NULL;
}
void port_read_thread::port_read_thread_fun()
{

   // QTimer timer;                    定义定时器对象的第一种方式，在线程函数体内申明并且定义
    timer = new QTimer(this);          //定义定时器对象的第二种方式，在线程头文件中声明，在线程函数体内定义
    //QEventLoop loop;                //定义循环事件对象的第一种方式，在线程函数体内申明并且定义
    loop = new QEventLoop(this);     //定义循环事件对象的第二种方式，在线程头文件中声明，在线程函数体内定义
                                     //定义事件循环(定时器)对象的两种方式都可以


    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(port_data_read()));


    if(timer->isActive() == false)
    {
        timer->start(set_time);
        tmier_start = true;
    }


   loop->exec();
}
void port_read_thread::port_data_read()
{
    if(port_on_is_ok == false)
    {
        if(tmier_start == true)
        {
            mutex_read_thread.lock();
            if(tmier_start == true)
            {
                 timer->stop();
                 emit port_read_thread_died("port_read_thread");   //自定义的线程关闭信号。当线程关闭后，线程才会发出finshed的信号
                 tmier_start = false;
            }
            mutex_read_thread.unlock();
        }

    }

   //  QByteArray readComData ;
    mutex_read_thread.lock();
      readComData.clear();
      readComData = this->myCom->readAll();
    if(readComData != NULL)
    {
       qDebug()<<"come form "<<readComData;
       emit port_read_over_signals(readComData);
       readComData.clear();
    }
    mutex_read_thread.unlock();


}
port_read_thread * port_read_thread::port_read_thread_create()
{
    if(port_read_th == NULL)
    {
        mutex_read_thread.lock();
        if(port_read_th == NULL)
        {
             port_read_th = new port_read_thread();
        }
        mutex_read_thread.unlock();
    }
    return port_read_th;
}

void port_read_thread::port_read_thread_free()
{
    if(port_read_th == NULL)
    {
        return;
    }else
    {   mutex_read_thread.lock();
        if(port_read_th != NULL)
        {
            delete(port_read_th);
        }
        mutex_read_thread.unlock();
        port_read_th = NULL;
    }
}
