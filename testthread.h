#ifndef TESTTHREAD_H
#define TESTTHREAD_H
#include <QThread>

#include "paramconfig.h"
#include "publicdataclass.h"
#include "mythread.h"
#include "dev_protocol.h"
#include "testthread.h"


class TestThread:public QThread
{
    Q_OBJECT
public:
    TestThread();
    MyThread threadA;
    DEV_protocol Dev_protocol;
    void stop();

protected:
    void run();

private:
    //TestThread* threadTest;

signals:
    void testprocess_end();//测试线程终止
    void sendmsg_server();//网口发送报文
};

#endif // TESTTHREAD_H
