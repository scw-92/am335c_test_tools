#ifndef EQUIPMENT_THREAD_H
#define EQUIPMENT_THREAD_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>
class Equipment_thread : public QObject
{
    Q_OBJECT
    friend class Equipment;

    static void free();
    static Equipment_thread *my_e_thread;
    static QMutex *mutex;
public:
    void thread_handle_fun();
    static Equipment_thread * equipment_thread_create();
signals:
   // void pthread_stop();
    void auto_detection_signal(QString str);

public slots:
    void auto_detection();
    void mytimer_stop();
private:
    QTimer       *my_timer                     = NULL;
    QEventLoop   *loop                         = NULL;
    QObject                 * sd               = NULL;
    QObject                 * rtc              = NULL;
    QObject                 * i2c2             = NULL;
    QObject                 * usb2             = NULL;
    bool                    tmier_start        = false;

    explicit Equipment_thread(QObject *parent = 0);
};

#endif // EQUIPMENT_THREAD_H
