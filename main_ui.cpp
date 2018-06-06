#include "main_ui.h"
#include <QObject>
#include <QDebug>
#include <QThread>
//#include "equipment_thread.h"
main_ui::main_ui(QObject *parent) : QObject(parent)
{
    engine = new QQmlApplicationEngine();
    engine->load(QUrl("qrc:/main.qml"));

    if (engine->rootObjects().isEmpty())
        return ;

    object = engine->rootObjects();
    ApplicationWindow            = object[0];
    listView                     = ApplicationWindow->findChild<QObject*>("ListView");

    QObject::connect(listView,SIGNAL(send(QString,QString)),this,SLOT(qml_model_prase(QString,QString)));
  //  object_tools.clear();



}
void main_ui::qml_model_prase(QString des,QString src)
{
    if(src.compare("none") == 0)
    {
       page_des = ApplicationWindow->findChild<QObject*>(des);
       page_des->setProperty("visible",true);

    }else
    {
       page_des = ApplicationWindow->findChild<QObject*>(des);
       page_src = ApplicationWindow->findChild<QObject*>(src);
       page_src->setProperty("visible",false);
       page_des->setProperty("visible",true);

    }


    if(qml_port)
    {
          qml_port->port_close_handle();

    }

    if(my_equipment)
    {
        if(my_equipment->my_e_thread)
        {
            emit equipment_timer_stop();
        }
    }
    if(my_gpio)
    {
        if(my_gpio->g_thread)
        {
            emit gpio_timer_stop();
        }

        if(my_gpio->my_timer_flags)
        {
                 if(my_gpio->my_timer->isActive())
                {
                    my_gpio->my_timer->stop();
                    my_gpio->my_timer_flags = false;
                }

        }
    }

    if(des.compare("port_page") == 0)
   {
        port_handle();
   }else if(des.compare("gpio_page") == 0)
    {
        gpio_handle();
    }else if(des.compare("equipment_page") == 0)
    {
        equipment_handle();
    }else if(des.compare("protocol_page") == 0)
    {
        protocol_handle();
    }
}



void  main_ui::port_handle()
{
    if(qml_port == NULL)
    {
        qml_port =  QmlPort::create_qml_port(this);
       // object_tools.append(qml_port);
        QObject::connect(this,&main_ui::port_handle_ok,qml_port,&QmlPort::port_setup);
        qml_port->port_nu_file     =  page_des->findChild<QObject*>("port_nu_file");
        qml_port->port_data_bit    =  page_des->findChild<QObject*>("port_data_bit");
        qml_port->port_speed       =  page_des->findChild<QObject*>("port_speed");
        qml_port->port_stop        =  page_des->findChild<QObject*>("port_stop");
        qml_port->port_check       =  page_des->findChild<QObject*>("port_check");
        qml_port->port_flow_con    =  page_des->findChild<QObject*>("port_flow_con");
        qml_port->port_recv_time   =  page_des->findChild<QObject*>("port_recv_time");
        qml_port->port_send_time   =  page_des->findChild<QObject*>("port_send_time");
        qml_port->port_on          =  page_des->findChild<QObject*>("port_on");
        qml_port->port_close       =  page_des->findChild<QObject*>("port_close");
        qml_port->port_data_recv   =  page_des->findChild<QObject*>("port_data_recv");
        qml_port->port_data_send   =  page_des->findChild<QObject*>("port_data_send");
        emit port_handle_ok();
    }

}
void  main_ui::gpio_handle()
{
    if(my_gpio == NULL)
    {
        my_gpio = gpio::gpio_create(this);
      //  object_tools.append(my_gpio);
        QObject::connect(this,&main_ui::gpio_handle_ok,my_gpio,&gpio::gpio_setup);
        QObject::connect(this,&main_ui::gpio_timer_stop,my_gpio,&gpio::g_stop_thread);
        my_gpio->led6             =   page_des->findChild<QObject*>("led6");
        my_gpio->led3             =   page_des->findChild<QObject*>("led3");
        my_gpio->led4             =   page_des->findChild<QObject*>("led4");
        my_gpio->ai1              =   page_des->findChild<QObject*>("ai1");
        my_gpio->ai2              =   page_des->findChild<QObject*>("ai2");
        my_gpio->ai3              =   page_des->findChild<QObject*>("ai3");
        my_gpio->ji115            =   page_des->findChild<QObject*>("ji115");
        my_gpio->ji116            =   page_des->findChild<QObject*>("ji116");
        my_gpio->mio2_8           =   page_des->findChild<QObject*>("mio2_8");
        my_gpio->mio2_7           =   page_des->findChild<QObject*>("mio2_7");

        my_gpio->led6_bt          =   page_des->findChild<QObject*>("led6_bt");
        my_gpio->led3_bt          =   page_des->findChild<QObject*>("led3_bt");
        my_gpio->led4_bt          =   page_des->findChild<QObject*>("led4_bt");
        my_gpio->ai1_bt           =   page_des->findChild<QObject*>("ai1_bt");
        my_gpio->ai2_bt           =   page_des->findChild<QObject*>("ai2_bt");
        my_gpio->ai3_bt           =   page_des->findChild<QObject*>("ai3_bt");
        my_gpio->ji116_bt         =   page_des->findChild<QObject*>("ji116_bt");
        my_gpio->ji115_bt         =   page_des->findChild<QObject*>("ji115_bt");
        my_gpio->mio2_8_bt        =   page_des->findChild<QObject*>("mio2_8_bt");
        my_gpio->mio2_7_bt        =   page_des->findChild<QObject*>("mio2_7_bt");
        my_gpio->auto_open_bt     =   page_des->findChild<QObject*>("auto_open");
        my_gpio->auto_close_bt    =   page_des->findChild<QObject*>("auto_close");

        my_gpio->gpio_out_map->insert(22,my_gpio->led3);
        my_gpio->gpio_out_map->insert(23,my_gpio->led4);
        my_gpio->gpio_out_map->insert(29,my_gpio->led6);
        my_gpio->gpio_out_map->insert(115,my_gpio->ji115);
        my_gpio->gpio_out_map->insert(116,my_gpio->ji116);

        my_gpio->gpio_in_map->insert(45,my_gpio->mio2_7);
        my_gpio->gpio_in_map->insert(46,my_gpio->mio2_8);
        my_gpio->ai_map->insert(0,my_gpio->ai1);
        my_gpio->ai_map->insert(0,my_gpio->ai2);
        my_gpio->ai_map->insert(0,my_gpio->ai3);
                // qDebug()<<my_gpio->gpio_in_map->size()<<my_gpio->gpio_out_map->size()<<my_gpio->led3;
        //qDebug()<<(*my_gpio->gpio_in_map)[45]<<my_gpio->gpio_out_map->size()<<my_gpio->led3;

        emit gpio_handle_ok();
    }
}

void main_ui::equipment_handle()
{
    if(!my_equipment)
    {

        my_equipment             = Equipment::equipment_create(this);

        QObject::connect(this,&main_ui::equipment_handle_ok,my_equipment,&Equipment::equipment_setup);
        QObject::connect(this,&main_ui::equipment_timer_stop,my_equipment,&Equipment::thread_deal_fun);
        QObject::connect(this,&main_ui::my_equipment_second_setup,my_equipment,&Equipment::equipment_second_setup);


        my_equipment->sd         = page_des->findChild<QObject*>("sd");
        my_equipment->i2c2       = page_des->findChild<QObject*>("i2c2");
        my_equipment->usb2       = page_des->findChild<QObject*>("usb2");
        my_equipment->rtc        = page_des->findChild<QObject*>("rtc");

        emit equipment_handle_ok();
    }else
    {
        qDebug()<<"hello world1";
       if(my_equipment->my_e_thread)
       {
//           qDebug()<<"hello world2";
//           my_equipment->equipment_thread = new QThread(my_equipment);
//           qDebug()<<"hello world3";
//           my_equipment->my_e_thread      = Equipment_thread::equipment_thread_create();
//           qDebug()<<"hello world4";
//           my_equipment->my_e_thread->moveToThread(my_equipment->equipment_thread);
//           qDebug()<<"hello world5";
           emit my_equipment_second_setup();
       }
    }
}


void main_ui::protocol_handle()
{
    if(!my_protocol)
    {

        my_protocol             = Protocol::protocol_create(this);

        QObject::connect(this,&main_ui::protocol_handle_ok,my_protocol,&Protocol::protocol_setup);
        my_protocol->local0_ip                       = page_des->findChild<QObject*>("local0_ip");
        my_protocol->local1_ip                       = page_des->findChild<QObject*>("local1_ip");
        my_protocol->t_machine_ip                    = page_des->findChild<QObject*>("t_machine_ip");
        my_protocol->set_ip0_bt                      = page_des->findChild<QObject*>("set_ip0_bt");
        my_protocol->set_ip1_bt                      = page_des->findChild<QObject*>("set_ip1_bt");
        my_protocol->ping_bt                         = page_des->findChild<QObject*>("ping_bt");
        my_protocol->ping_result                     = page_des->findChild<QObject*>("ping_result");

        emit protocol_handle_ok();
    }
}
