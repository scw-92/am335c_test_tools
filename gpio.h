#ifndef GPIO_H
#define GPIO_H

#include <QObject>
#include <QProcess>
#include <qmap.h>
#include <QThread>
#include "gpio_thread.h"
#include <QTimer>
class gpio : public QObject
{
    Q_OBJECT
    friend class main_ui;
public:
    //explicit gpio(QObject *parent = 0);
    static gpio* gpio_create(QObject *parent = 0);
    static void free();
    static bool  auto_flags ;
signals:
    void thread_start();
    void g_stop_thread_sin();
public slots:
    void gpio_setup();
    void led6_bt_handle(int);
    void led3_bt_handle(int);
    void led4_bt_handle(int);
    void ai1_bt_handle(int);
    void ai2_bt_handle(int);
    void ai3_bt_handle(int);
    void ji116_bt_handle(int);
    void ji115_bt_handle(int);
    void mio2_8_bt_handle(int);
    void mio2_7_bt_handle(int);
    void auto_open_handle();
    void auto_close_handle();
    void g_stop_thread();
    void thread_stop_handle();
    void test_show(QObject*,int);
    void auto_get_gpio_status();


private:
    explicit gpio(QObject *parent = 0);
    int gpio_set(int nu);
    int gpio_auto_test(int nu,int value);
    int gpio_get(int nu);
    //void ai_bt_handle(int nu);

    bool thread_start_flags = false;
    bool my_timer_flags     = false;
    QObject     *led6      = NULL ;
    QObject     *led3      = NULL ;
    QObject     *led4      = NULL ;
    QObject     *ai1       = NULL ;
    QObject     *ai2       = NULL ;
    QObject     *ai3       = NULL ;
    QObject     *ji115     = NULL ;
    QObject     *ji116     = NULL ;
    QObject     *mio2_8    = NULL ;
    QObject     *mio2_7    = NULL ;

    QObject     *led6_bt   = NULL ;
    QObject     *led3_bt   = NULL ;
    QObject     *led4_bt   = NULL ;
    QObject     *ai1_bt    = NULL ;
    QObject     *ai2_bt    = NULL ;
    QObject     *ai3_bt    = NULL ;
    QObject     *ji116_bt  = NULL ;
    QObject     *ji115_bt  = NULL ;
    QObject     *mio2_8_bt = NULL ;
    QObject     *mio2_7_bt = NULL ;
    QObject     *auto_open_bt  = NULL ;
    QObject     *auto_close_bt = NULL ;


    static      gpio* my_gpio     ;
    gpio_thread *g_thread      = NULL;
    QThread     *g_qthread     = NULL;
    QProcess    p;
    QMap<int, QObject *> *gpio_out_map;
    QMap<int, QObject *> *gpio_in_map;
    QMap<int, QObject *> *ai_map;
    QTimer            *   my_timer = NULL;

    unsigned int gpio_out_array[5]  = {22,23,29,115,116};
    unsigned int gpio_in_array[2]   = {45,46};
    int gpio_out_count              = 5;
    int gpio_in_count               = 2;
    int ai_array[3]                 = {0,1,2};
    int ai_count                    = 3;
    int count_clean =              0;


};

#endif // GPIO_H
