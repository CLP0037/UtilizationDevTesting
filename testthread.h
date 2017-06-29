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

};

#endif // TESTTHREAD_H
