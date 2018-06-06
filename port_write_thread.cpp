#include "port_write_thread.h"
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <QObject>
#include <QMutex>
QMutex mutex_write_thread;
port_write_thread* port_write_thread::port_write_th = NULL;

port_write_thread::port_write_thread(QObject *parent) : QObject(parent)
{

}
void port_write_thread::port_write_thread_fun()
{
     timer = new QTimer(this);
     loop = new QEventLoop(this);

     QObject::connect(timer, SIGNAL(timeout()), this, SLOT(port_data_write()));

     if(timer->isActive() == false)
     {
         timer->start(set_time);
         timer_start = true;
     }

    loop->exec();

}
void port_write_thread::port_data_write()
{

    if(port_on_is_ok == false)
    {

        if(timer_start == true)
        {   mutex_write_thread.lock();
            if(timer_start == true)
            {
                timer->stop();
                emit port_write_thread_died("port_write_thread");   //自定义的线程关闭信号。当线程关闭后，线程才会发出finshed的信号
                timer_start = false;
            }
            mutex_write_thread.unlock();
        }

    }

     writeComData.clear();
     writeComData = port_data_send_area->property("text").toByteArray();

     if(writeComData != NULL)
    {
       qDebug()<<"write data: "<<writeComData;

       this->myCom->write(writeComData);
    }

}

port_write_thread* port_write_thread::port_write_thread_create()
{
    if(port_write_th == NULL)
    {
        mutex_write_thread.lock();
        if(port_write_th == NULL)
        {
             port_write_th = new port_write_thread();
        }
        mutex_write_thread.unlock();

    }
    return port_write_th;

}

void port_write_thread::port_write_thread_free()
{
    if(port_write_th == NULL)
    {
        return;
    }else
    {   mutex_write_thread.lock();
        if(port_write_th!=NULL)
        {
            delete(port_write_th);
        }
        mutex_write_thread.unlock();
        port_write_th = NULL;

    }
}
