#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "paramconfig.h"
#include "paramset_internet.h"
#include "paramset_gprs.h"

#include "publicdataclass.h"
#include "mythread.h"
#include "dev_protocol.h"
#include "testthread.h"

#include<QtNetwork/QTcpSocket>
#include<QtNetwork/QTcpServer>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //extern PublicDataclass Dataclass;
    //MyThread threadA;
    TestThread threadTest;
    //DEV_protocol Dev_protocol;

    QTcpSocket *m_tcpsocket=NULL;
    QTcpServer *m_tcpserver=NULL;




private slots:
    void displayRxData();
    void displayTxData();
    void End_process();
    void sendMessage_server();

    void ShowMsg(int type,QByteArray buf_msg);

    void on_pushBtn_Start_clicked();

    void on_pushBtn_Stop_clicked();

    void on_pushBtn_Reset_clicked();

    void on_pushBtn_Restart_clicked();

    void on_lineEdit_devaddr_editingFinished();

    void on_lineEdit_ammetervaddr_editingFinished();

    void on_pushButton_clear_clicked();

    void on_btn_Link_clicked();

    void on_btn_unLink_clicked();

public slots:
    void newConnect();
    void readMessage();
    void sendMessage();
    void changeTest(int row, int col);

private:
    Ui::MainWindow *ui;
    QTableView *tableview;

    Paramconfig paramfrm;

    Paramset_internet paraminter_frm;
    Paramset_gprs paramgprs_frm;


};

#endif // MAINWINDOW_H
