#ifndef GPIO_THREAD_H
#define GPIO_THREAD_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>
#include <QProcess>
class gpio_thread : public QObject
{
    Q_OBJECT

    friend class gpio;
    static void free();
    static gpio_thread *my_g_thread;
    static gpio_thread * gpio_thread_create();
    static QMutex *mutex;
public:
    void thread_handle_fun();
    int  gpio_auto_test(int nu,int value);
    int  gpio_get(int nu);
    void ai_bt_handle(int nu);
    void gpio_thread_stop();

signals:
    void thread_stop_ok();
    void test_over(QObject *,int);
public slots:
    void auto_get_gpio_status();
private:
    explicit gpio_thread(QObject *parent = 0);
    bool                    tmier_start        = false;
    bool                    thread_flags       = false;
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
    QMap<int, QObject *> *gpio_out_map = NULL;
    QMap<int, QObject *> *gpio_in_map  = NULL;
    QMap<int, QObject *> *ai_map    = NULL;
    QTimer       *my_timer                     = NULL;
    QEventLoop   *loop                         = NULL;
    unsigned int gpio_out_array[5]  = {22,23,29,115,116};
    unsigned int gpio_in_array[2]   = {45,46};
    int gpio_out_count              = 5;
    int gpio_in_count               = 2;
    int ai_array[3]                 = {0,1,2};
    int ai_count                    = 3;
    int count_clean =       0;
    QProcess    p;

};

#endif // GPIO_THREAD_H
