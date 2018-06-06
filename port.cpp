#include "QmlPort.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMutex>
QMutex port_mutex;
QmlPort *QmlPort::my_qml_port = NULL;
QmlPort::QmlPort(QObject *parent) : QObject(parent)
{

}



void  QmlPort::port_setup()
{

   // QObject::connect(port_on,)

    QObject::connect(port_on,SIGNAL(clicked()),this,SLOT(port_on_handle()));


    QObject::connect(port_close,SIGNAL(clicked()),this,SLOT(port_close_handle()));

}

QmlPort* QmlPort::create_qml_port(QObject *parent)
{
   if(my_qml_port == NULL)
   {
       port_mutex.lock();
       if(my_qml_port == NULL)
       {
             my_qml_port = new QmlPort(parent);
       }
       port_mutex.unlock();
   }

   return my_qml_port;
}

void QmlPort::free()
{
    if(my_qml_port != NULL)
    {
        port_mutex.lock();
        if(my_qml_port == NULL)
        {
            my_qml_port->port_close_handle();
            while(1)
            {
                if(!my_qml_port->qml_port_thread_read_on && !my_qml_port->qml_port_thread_write_on && !my_qml_port->my_com_setup_on)
                {
                    delete(my_qml_port);
                    my_qml_port=NULL;
                    break;
                }
            }
        }
        port_mutex.unlock();
        my_qml_port = NULL;
    }
}
void QmlPort::port_close_handle()
{

    if(qml_port_thread_read_on)
    {
        port_read_th->port_on_is_ok = false;
    }
    if(qml_port_thread_write_on)
    {
        port_write_th->port_on_is_ok = false;

    }
}
void QmlPort::port_on_handle()
{

    if(qml_port_on == false)
    {
       if(my_com_setup_on == false)
       {
            my_com_setup();
       }

       if(my_com_setup_on)
       {
           if(qml_port_thread_read_on == false)
           {
                port_read_thread_setup();
           }
           if(qml_port_thread_write_on == false)
           {
               port_write_thread_setup();
           }


       }

    }else
    {
        return ;
    }


}


void QmlPort::my_com_setup()
{
    myCom = new QSerialPort(this);
    myCom->setPortName(port_nu_file->property("text").toString());

    qDebug() << port_nu_file->property("text").toString();
   // qDebug()<<port_data_bit->property("currentText").toInt();

    if(myCom->open(QIODevice::ReadWrite))
    {
        int speed = port_speed->property("currentText").toInt();
        switch(speed)
        {
        case 115200:
            myCom->setBaudRate(QSerialPort::Baud115200);
            break;
        case 9600:
            myCom->setBaudRate(QSerialPort::Baud9600);
            break;
        default:
            myCom->setBaudRate(QSerialPort::Baud115200);
            break;

        }

        int data_bit = port_data_bit->property("currentText").toInt();
        switch (data_bit)
        {
        case 8:
            myCom->setBaudRate(QSerialPort::Data8);
            break;
        case 7:
            myCom->setBaudRate(QSerialPort::Data8);
            break;
        case 6:
            myCom->setBaudRate(QSerialPort::Data8);
            break;
        case 5:
            myCom->setBaudRate(QSerialPort::Data8);
            break;
        default:
            myCom->setBaudRate(QSerialPort::Data8);
            break;
        }

        int parity = port_check->property("currentText").toInt();
        switch(parity)
        {
        case 0:
            myCom->setParity(QSerialPort::NoParity);
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            myCom->setParity(QSerialPort::NoParity);
            break;
        }

        int stop_bit = port_stop->property("currentText").toInt();
        switch(stop_bit)
        {
         case 0:
            myCom->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 1:
            myCom->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            myCom->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            myCom->setStopBits(QSerialPort::OneStop);
            break;
        }

        QString flow_con = port_flow_con->property("currentText").toString();
        if(flow_con.compare("none") == 0)
        {
            myCom->setFlowControl(QSerialPort::NoFlowControl);
        }else if(flow_con.compare("soft")== 0)
        {
            myCom->setFlowControl(QSerialPort::SoftwareControl);
        }else if(flow_con.compare("hard") == 0)
        {
            myCom->setFlowControl(QSerialPort::HardwareControl);
        }
        my_com_setup_on = true;
    }else
    {
        my_com_setup_on = false;
        qDebug()<<"my_com open error";
        delete(myCom);
        myCom = NULL;
    }
}



int QmlPort::port_read_thread_setup()
{
    port_read_th = port_read_thread::port_read_thread_create();
    if(port_read_th == NULL)
    {
        qml_port_thread_read_on = false;
        port_read_th->port_on_is_ok  = false;
        return -1;
    }else
    {
        port_read_thd = new QThread(this);
        port_read_th->moveToThread(port_read_thd);
        port_read_th->myCom = myCom;
        port_read_th->set_time  =  port_recv_time->property("text").toInt();

        QObject::connect(this,&QmlPort::port_read_signals,port_read_th,&port_read_thread::port_read_thread_fun);
        QObject::connect(port_read_th,&port_read_thread::port_read_thread_died,this,&QmlPort::deal_thread);
        QObject::connect(port_read_th,&port_read_thread::port_read_over_signals,this,&QmlPort::port_data_recv_fun);



        port_read_thd->start();
        port_read_th->port_on_is_ok = true;
        emit port_read_signals();
        qml_port_thread_read_on     = true;

    }
}


int QmlPort::port_write_thread_setup()
{
    port_write_th = port_write_thread::port_write_thread_create();
    if(port_write_th == NULL)
    {
        qml_port_thread_write_on    = false;
        port_write_th->port_on_is_ok = false;
        return -1;
    }else
    {
        port_write_thd = new QThread(this);
        port_write_th->moveToThread(port_write_thd);
        port_write_th->myCom = myCom;
        port_write_th->set_time  =  port_send_time->property("text").toInt();
        port_write_th->port_data_send_area = port_data_send;


        QObject::connect(this,&QmlPort::port_write_signals,port_write_th,&port_write_thread::port_write_thread_fun);
        QObject::connect(port_write_th,&port_write_thread::port_write_thread_died,this,&QmlPort::deal_thread);

        port_write_thd->start();
        port_write_th->port_on_is_ok = true;
        emit port_write_signals();
       // qDebug()<<"write_pthread-on";
        qml_port_thread_write_on = true;

    }
}

void  QmlPort::deal_thread(QString str)
{


    if(!str.compare("port_read_thread"))
        {
            port_read_thd->quit();
            port_read_thd->wait();

            port_read_thread::port_read_thread_free();
            delete(this->port_read_thd);

            port_read_thd = NULL;

            qml_port_on = false;
            my_com_setup_on = false;
            qml_port_thread_read_on = false;
            qDebug()<<"port_read_thread died ok ";

        }else if (!str.compare("port_write_thread"))
        {
            port_write_thd->quit();
            port_write_thd->wait();
            port_write_thread::port_write_thread_free();
           // delete(this->port_write_th);
            delete(this->port_write_thd);

            qml_port_on = false;
            my_com_setup_on = false;
            qml_port_thread_write_on    = false;
            qDebug()<<"port_write_thread died ok ";
        }


    if( !qml_port_thread_read_on && !qml_port_thread_write_on)
    {
        if(this->myCom != NULL)
        {
            delete(this->myCom);
            this->myCom = NULL;
            my_com_setup_on = false;
        }
    }

}

 void QmlPort::port_data_recv_fun(QByteArray str)
 {
     if(port_read_count>330)
     {
         port_read_count = 0;
         port_data_recv->setProperty("text","");

     }
     QMetaObject::invokeMethod(port_data_recv, "set_text",Q_ARG(QVariant,str));
     port_read_count += str.length();
 }
