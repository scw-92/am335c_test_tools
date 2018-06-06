#include "protocol.h"
#include <QDebug>

Protocol *     Protocol::my_protocol  = NULL  ;
QMutex *       Protocol::my_mutex     =new QMutex()   ;



Protocol::Protocol(QObject *parent) : QObject(parent)
{

}


Protocol *     Protocol::protocol_create(QObject *parent)
{
    if(Protocol::my_protocol == NULL)
    {
        Protocol::my_mutex->lock();
        if(Protocol::my_protocol == NULL)
        {
            Protocol::my_protocol = new Protocol(parent);
        }

         Protocol::my_mutex->unlock();
    }
     return Protocol::my_protocol;
}


void  Protocol::free()
{
    if(Protocol::my_protocol)
    {
        Protocol::my_mutex->lock();
        if(Protocol::my_protocol)
        {
            delete Protocol::my_protocol;
        }

        Protocol::my_protocol = NULL;
        Protocol::my_mutex->unlock();
    }
}

void Protocol::protocol_setup()
{
    QObject::connect(set_ip0_bt,SIGNAL(clicked()),this,SLOT(set_ip0_bt_handle()));
    QObject::connect(set_ip1_bt,SIGNAL(clicked()),this,SLOT(set_ip1_bt_handle()));
    QObject::connect(ping_bt,SIGNAL(clicked()),this,SLOT(ping_bt_handle()));
}
void Protocol::set_ip0_bt_handle()
{

    char  cmd_ip[100] = {0};
    sprintf(cmd_ip,"ifconfig eth0 %s",local0_ip->property("text").toString().toStdString().c_str());
    QMetaObject::invokeMethod(ping_result, "set_clean");
    if(system(cmd_ip) != 0)
    {
       // local0_ip->setProperty("text","IP设置出错");
        QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,"eth0:IP设置出错"));
    }else
    {
         QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,"eth0:IP设置成功"));
    }
}
void Protocol::set_ip1_bt_handle()
{
     QMetaObject::invokeMethod(ping_result, "set_clean");
    char  cmd_ip[100] = {0};
    sprintf(cmd_ip,"ifconfig eth1 %s",local1_ip->property("text").toString().toStdString().c_str());

    if(system(cmd_ip) != 0)
    {
        //local0_ip->setProperty("text","IP设置出错");
        QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,"eth1:IP设置出错"));
    }else
    {
         QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,"eth1:IP设置成功"));
    }
}
void Protocol::ping_bt_handle()
{

    if(!my_timer)
    {
        Protocol::my_mutex->lock();
        if(!my_timer)
        {
            my_timer = new QTimer(this);
            QObject::connect(my_timer, SIGNAL(timeout()), this, SLOT(ping_timer_handle()));
        }

        Protocol::my_mutex->unlock();
    }


    if(!timer_start_flasgs)
    {

        Protocol::my_mutex->lock();
        if(!timer_start_flasgs)
        {

            if(my_timer->isActive() == false)
             {
                 my_timer->start(500);
                 timer_start_flasgs = true;
             }
        }
        Protocol::my_mutex->unlock();
    }

}
void Protocol::showPingResult(PingResult pingResult)
{
    char result_ip[100] = {0};
    for (unsigned int icmpEchoReplyIndex = 0; icmpEchoReplyIndex < pingResult.icmpEchoReplys.size(); icmpEchoReplyIndex++) {
            IcmpEchoReply icmpEchoReply = pingResult.icmpEchoReplys.at(icmpEchoReplyIndex);
            if (icmpEchoReply.isReply) {
                sprintf(result_ip,"%d byte from %s: icmp_seq=%u ttl=%d rtt=%.3f ms\n",
                        icmpEchoReply.icmpLen,
                        icmpEchoReply.fromAddr.c_str(),
                        icmpEchoReply.icmpSeq,
                        icmpEchoReply.ipTtl,
                        icmpEchoReply.rtt);
                QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,result_ip));
                memset(result_ip,0,100);

            } else {
               // printf("request timeout\n");
                QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,"request timeout\n"));
            }
        }
}
void Protocol::ping_timer_handle()
{
    char  hostOrIp[100] = {0};
    char ip_result[100] = {0};
    int nsend = 0, nreceived = 0;
    bool ret;
    PingResult pingResult;
    Ping ping = Ping();
    QMetaObject::invokeMethod(ping_result, "set_clean");


    sprintf(hostOrIp,"%s",t_machine_ip->property("text").toString().toStdString().c_str());
//    qDebug()<<"hostOrIp"<<hostOrIp<<"pingResult.ip.c_str()"<<pingResult.ip.c_str();

        QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,"ping start,please wait!!!\n"));
        for (int count = 1; count <= 4; count++) {
            ret = ping.ping(hostOrIp, 1, pingResult);
            if (count == 1) {
                sprintf(ip_result,"PING %s(%s): %d bytes data in ICMP packets.\n",hostOrIp, pingResult.ip.c_str(), pingResult.dataLen);
               // qDebug()<<"hostOrIp"<<hostOrIp<<"pingResult.ip.c_str()"<<pingResult.ip.c_str();
                QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,ip_result));
                memset(ip_result,0,100);
            }
            if (!ret) {
                sprintf(ip_result,"%s\n", pingResult.error.c_str());
                QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,ip_result));
                memset(ip_result,0,100);
                break;
            }
            showPingResult(pingResult);
            nsend += pingResult.nsend;
            nreceived += pingResult.nreceived;
        }
        if (ret) {
            sprintf(ip_result,"%d packets transmitted, %d received , %%%d lost\n", nsend, nreceived,
                (nsend - nreceived) / nsend * 100);
            QMetaObject::invokeMethod(ping_result, "set_text",Q_ARG(QVariant,ip_result));
            memset(ip_result,0,100);

        }

        if(my_timer->isActive())
         {
             my_timer->stop();
         }
        timer_start_flasgs = false;

}
