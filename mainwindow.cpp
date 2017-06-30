#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qabstractitemmodel.h" //<QAbstractItemModel>
#include "QStandardItemModel.h"
#include "mythread.h"
#include "dev_protocol.h"
#include "paramconfig.h"
#include "publicdataclass.h"
#include "testthread.h"
#include <QtCore/QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDialog>  //对话框显示
#include <QMessageBox>

extern PublicDataclass Dataclass;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug(GIT_VERSION);
    qDebug(GIT_VERSIONMODIFY);
    ui->setupUi(this);
    QString wTitle="用电终端测试软件_";

    wTitle+=GIT_VERSION;
    wTitle+=" ";
    wTitle+=GIT_VERSIONMODIFY;
    this->setWindowTitle(wTitle);//"用电终端测试软件_"+GIT_VERSION+"_"+GIT_VERSIONMODIFY

    //去掉最大化最小化按钮，保留关闭按钮
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    //设置行列数
    ui->tableWidget_Result->setRowCount(11);//11行
    ui->tableWidget_Result->setColumnCount(5);

    //第2列====测试项目名称
    //
    ui->tableWidget_Result->setItem(0,1,new QTableWidgetItem("设备版本信息读取"));
    ui->tableWidget_Result->setItem(1,1,new QTableWidgetItem("设备系统时间读取"));
    ui->tableWidget_Result->setItem(2,1,new QTableWidgetItem("设备终端电压读取"));
    ui->tableWidget_Result->setItem(3,1,new QTableWidgetItem("设备遥信变位读取"));
    ui->tableWidget_Result->setItem(4,1,new QTableWidgetItem("电表有功电能转发_4851"));
    ui->tableWidget_Result->setItem(5,1,new QTableWidgetItem("电表有功电能转发_4852"));
    ui->tableWidget_Result->setItem(6,1,new QTableWidgetItem("ESAM版本信息读取"));
    ui->tableWidget_Result->setItem(7,1,new QTableWidgetItem("以太网参数下设"));
    //
    ui->tableWidget_Result->setItem(8,1,new QTableWidgetItem("以太网登录"));
    ui->tableWidget_Result->setItem(9,1,new QTableWidgetItem("GPRS参数下设"));
    //
    ui->tableWidget_Result->setItem(10,1,new QTableWidgetItem("GPRS登录"));


    ui->tableWidget_Result->setAlternatingRowColors(1); //隔行显示颜色
    ui->tableWidget_Result->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_Result->show();

    for(int n=0;n<11;n++)//第1列为复选框
    {
        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        ui->tableWidget_Result->setItem(n,0,check);
        if(n >= 8){
            check->flags();
            check->setFlags(check->flags() & (~Qt::ItemIsEnabled));
        }
    }
     connect(ui->tableWidget_Result, SIGNAL(cellChanged(int,int)), this, SLOT(changeTest(int, int)));

     ui->tableWidget_Result->setEditTriggers(QAbstractItemView::NoEditTriggers); //即可设置整个表格不可编辑

     threadTest.threadA.changeTxState(false);
     threadTest.threadA.TxData.clear();
     connect(&threadTest.threadA, SIGNAL(comRecive()), this, SLOT(displayRxData()));//收到报文在报文显示窗展示
     connect(&threadTest.threadA, SIGNAL(comSend()), this, SLOT(displayTxData()));//发送的报文在报文显示窗展示

     connect(&this->threadTest,SIGNAL(testprocess_end()),this,SLOT(End_process()));//完成测试结束测试线程//testprocess_end()  End_process()
     connect(&this->threadTest,SIGNAL(sendmsg_server()),this,SLOT(sendMessage_server()));//sendmessage_server()   sendMessage_server()

     ui->pushBtn_Start->setDisabled(true);
     ui->pushBtn_Stop->setDisabled(true);
     ui->pushBtn_Restart->setDisabled(true);
     ui->pushBtn_Reset->setDisabled(true);
     ui->btn_Link->setDisabled(false);
     ui->btn_unLink->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    this->threadTest.threadA.stop();
    while(this->threadTest.threadA.isRunning()){
        QThread::sleep(1);
    }
    this->threadTest.stop();

    while(this->threadTest.isRunning()){
        QThread::sleep(1);
    }
}

void MainWindow::changeTest(int row, int col)
{
    int row_select;
    //测试过程中不允许修改测试项的选中状态
    if(Dataclass.DEV_testprocess==false)
    {
        if(ui->tableWidget_Result ->item(row, col)->checkState() == Qt::Checked)//某行某列被选中
        {
             //某行某列
            row_select=row;
            Dataclass.TestINFO.step_Selected[row_select]=true;
            //Dataclass.TestINFO.testSteps_totalLevel=2;
            switch(row_select)
            {

            case 0:
            {

            }break;

            case 7://以太网参数下设=====弹窗设置以太网相关参数
            {
                if(paraminter_frm.exec()==QDialog::Accepted)//设置以太网参数确认
                {
                    //  可选择测试以太网测试相关项
                    for(int n=0;n<2;n++)
                    {
                        QTableWidgetItem *check = ui->tableWidget_Result->item((row_select+1+n),0);
                        check->setFlags(check->flags() | Qt::ItemIsEnabled);
                    }
                }

            }break;

            case 9://GPRS参数下设=====弹窗设置GPRS相关参数
            {
                if(paramgprs_frm.exec()==QDialog::Accepted)//设置GPRS参数确认
                {
                    //可选择测试GPRS相关项
                    QTableWidgetItem *check = ui->tableWidget_Result->item((row_select+1),0);
                    check->setFlags(check->flags() | Qt::ItemIsEnabled);
                }

            }break;

            }
        }
        else if(ui->tableWidget_Result ->item(row, col)->checkState() == Qt::Unchecked)//某行某列被取消选中
        {
            row_select=row;
            Dataclass.TestINFO.step_Selected[row_select]=false;
        }

    }

}


void MainWindow::on_pushBtn_Start_clicked()//启动测试
{
    if(ui->lineEdit_devaddr->text().trimmed()=="")//若终端地址输入为空，赋值为AAAAAAAAAAAA
    {
        ui->lineEdit_devaddr->setText("AAAAAAAAAAAA");
        Dataclass.set_DEV_addr("AAAAAAAAAAAA");
    }

    if(ui->lineEdit_ammetervaddr->text().trimmed()=="")//电表地址为空
    {
        //弹窗提示电表地址为空======读电表正向有功电能时会用到

        return;
    }
    else
    {
        //测试过程中地址设置不可用
        //终端地址相关参数赋值
        if((Dataclass.get_DEV_addr()!=ui->lineEdit_devaddr->text().trimmed())&&(ui->lineEdit_devaddr->text().trimmed()!=""))
        {
            Dataclass.set_DEV_addr(ui->lineEdit_devaddr->text().trimmed());
        }
        //电表地址相关参数赋值
        if((Dataclass.get_ammeter_addr()!=ui->lineEdit_ammetervaddr->text().trimmed())&&(ui->lineEdit_ammetervaddr->text().trimmed()!=""))
        {
            Dataclass.set_ammeter_addr(ui->lineEdit_ammetervaddr->text().trimmed());
        }
        ui->lineEdit_devaddr->setDisabled(true);
        ui->lineEdit_ammetervaddr->setDisabled(true);


        Dataclass.TestINFO.testSteps_total=14;//目前可选的总测试项目数为11 总步骤为14
        Dataclass.TestINFO.testSteps_currentLevel=1;
        Dataclass.TestINFO.testSteps_currentTeststep=1;

        if(Dataclass.TestINFO.step_Selected[10]==true)
        {
            Dataclass.TestINFO.testSteps_totalLevel=3;
        }
        else if(Dataclass.TestINFO.step_Selected[9]==true||Dataclass.TestINFO.step_Selected[8]==true)
        {
            Dataclass.TestINFO.testSteps_totalLevel=2;
        }
        else Dataclass.TestINFO.testSteps_totalLevel=1;

        //启动测试线程
        Dataclass.DEV_testprocess=true;
        Dataclass.DEV_testprocess_start=true;
        this->threadTest.start();
        ui->pushBtn_Start->setDisabled(true);
        ui->pushBtn_Stop->setDisabled(false);
        ui->pushBtn_Reset->setDisabled(true);
        ui->pushBtn_Restart->setDisabled(true);

        //清空结果显示
        for(int n=0;n<11;n++)
        {
            ui->tableWidget_Result->setItem(n,2,new QTableWidgetItem(""));
            ui->tableWidget_Result->setItem(n,3,new QTableWidgetItem(""));
            ui->tableWidget_Result->setItem(n,4,new QTableWidgetItem(""));
        }
        ui->tableWidget_Result->show();
    }
}

void MainWindow::on_pushBtn_Stop_clicked()//停止测试
{
    ui->lineEdit_devaddr->setDisabled(false);
    ui->lineEdit_ammetervaddr->setDisabled(false);

    //停止测试线程
    //this->threadTest.stop();
    //this->threadTest.terminate();
    //this->threadTest.wait();
    Dataclass.DEV_testprocess=false;

    ui->pushBtn_Start->setDisabled(false);
    ui->pushBtn_Stop->setDisabled(true);
    ui->pushBtn_Reset->setDisabled(false);
    ui->pushBtn_Restart->setDisabled(false);
}

void MainWindow::on_pushBtn_Reset_clicked()//恢复出厂设置====21
{
    //Dataclass.Buffer_send=NULL;

    Dataclass.BufLen_send=threadTest.Dev_protocol.Encode(Dataclass.Buffer_send,21,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
//    qDebug("the Buffer_send[0] is:%d\n",Dataclass.Buffer_send.at(0));

//    QByteArray Qarr;
//    char var,tmp[256];
//    char *buf;
//    char cmdCloseDoor[24]={0x68,0x16,0x00,0x43,0x03,0x59,0x46,0x46,0x14,0x00,0x0C,0xD2,0x07,0x01,0x00,0x43,0x00,0x04,0x00,0x00,0x00,0xC9,0x1B,0x16};
//    QString str="设备恢复出厂设置: ";
//    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());


//    str+=datatime->time().toString();
//    ui->textEdit_msg->append(str);
//    str.clear();
    //Qarr.append(cmdCloseDoor,24);

    //buf=Qarr.data();
//    buf=Dataclass.Buffer_send.data();
//    for(var=0;var<24;var++)
//    {
//        ::snprintf(tmp,256, "%02X", (unsigned char)(*buf));
//        buf++;
//        str+=QString::fromUtf8(tmp);
//        str+=" ";
//    }
//    ui->textEdit_msg->append(str);
    threadTest.threadA.TxData.clear();
    //this->threadA.TxData.append(cmdCloseDoor,24);
    threadTest.threadA.TxData.append(Dataclass.Buffer_send,Dataclass.BufLen_send);
    threadTest.threadA.changeTxState(true);

}

void MainWindow::on_pushBtn_Restart_clicked()//设备重启====22
{
    Dataclass.BufLen_send=threadTest.Dev_protocol.Encode(Dataclass.Buffer_send,22,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
//    qDebug("the Buffer_send[0] is:%d\n",Dataclass.Buffer_send.at(0));

//    char var,tmp[256];
//    char *buf;
//    QString str="设备重启: ";
//    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());


//    str+=datatime->time().toString();
//    ui->textEdit_msg->append(str);
//    str.clear();

//    //buf=Qarr.data();
//    buf=Dataclass.Buffer_send.data();
//    for(var=0;var<24;var++)
//    {
//        ::snprintf(tmp,256, "%02X", (unsigned char)(*buf));
//        buf++;
//        str+=QString::fromUtf8(tmp);
//        str+=" ";
//    }
//    ui->textEdit_msg->append(str);
    threadTest.threadA.TxData.clear();
    //this->threadA.TxData.append(cmdCloseDoor,24);
    threadTest.threadA.TxData.append(Dataclass.Buffer_send,Dataclass.BufLen_send);
    threadTest.threadA.changeTxState(true);
}


void MainWindow::on_lineEdit_devaddr_editingFinished()//设备地址输入结束
{
    //终端地址相关参数赋值
    if((Dataclass.get_DEV_addr()!=ui->lineEdit_devaddr->text().trimmed())&&(ui->lineEdit_devaddr->text().trimmed()!=""))
    {
        Dataclass.set_DEV_addr(ui->lineEdit_devaddr->text().trimmed());
    }
}

void MainWindow::on_lineEdit_ammetervaddr_editingFinished()//电表地址输入结束
{
    //电表地址相关参数赋值
    if((Dataclass.get_ammeter_addr()!=ui->lineEdit_ammetervaddr->text().trimmed())&&(ui->lineEdit_ammetervaddr->text().trimmed()!=""))
    {
        Dataclass.set_ammeter_addr(ui->lineEdit_ammetervaddr->text().trimmed());
    }
}

void MainWindow::displayRxData()//显示串口接收报文内容
{
//    QString str;
//    char tmp[256];
//    char *buf;
//    char var;
//    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
    if(threadTest.threadA.requestData.size()>0)
   {
        //将接收的内容放入缓存数据buffer
        for(int n=0;n<threadTest.threadA.requestData.size();n++)
        {
            Dataclass.buf_rev.append(threadTest.threadA.requestData[n]);
        }
        //基于规约完整性判断
        while(Dataclass.buf_rev.size()>10)
        {
            int len_rev=0;//从报文中获取的数据长度

            if(Dataclass.buf_rev[0]==(char)0x68)//检查帧头
            {
                len_rev=Dataclass.buf_rev[1]+2;//完整帧长
                if(Dataclass.buf_rev.size()<len_rev)//数据区尚未接收完整
                {
                    break;
                }
                //得到完整的数据进行显示，解包分析
                this->ShowMsg(2,Dataclass.buf_rev);//界面显示

                //Decode(QByteArray buf);
                int decode_dataty=threadTest.Dev_protocol.Decode(Dataclass.buf_rev);//threadTest.threadA.requestData
                //基于读取的结果显示到界面
                switch(decode_dataty)
                {
                    case 11:
                    {
                        ui->tableWidget_Result->setItem(0,2,new QTableWidgetItem(Dataclass.Result_version.Result_HCS));
                        ui->tableWidget_Result->setItem(0,3,new QTableWidgetItem(Dataclass.Result_version.Result_FCS));
                        ui->tableWidget_Result->setItem(0,4,new QTableWidgetItem(Dataclass.Result_version.Result_describe));

                        ui->tableWidget_Result->show();
                    }break;
                    case 12:
                    {
                        ui->tableWidget_Result->setItem(1,2,new QTableWidgetItem(Dataclass.Result_time.Result_HCS));
                        ui->tableWidget_Result->setItem(1,3,new QTableWidgetItem(Dataclass.Result_time.Result_FCS));
                        ui->tableWidget_Result->setItem(1,4,new QTableWidgetItem(Dataclass.Result_time.Result_describe));

                        ui->tableWidget_Result->show();
                    }break;
                    case 13:
                    {
                        ui->tableWidget_Result->setItem(2,2,new QTableWidgetItem(Dataclass.Result_voltage.Result_HCS));
                        ui->tableWidget_Result->setItem(2,3,new QTableWidgetItem(Dataclass.Result_voltage.Result_FCS));
                        ui->tableWidget_Result->setItem(2,4,new QTableWidgetItem(Dataclass.Result_voltage.Result_describe));

                        ui->tableWidget_Result->show();
                    }break;
                    case 14:
                    {
                        ui->tableWidget_Result->setItem(3,2,new QTableWidgetItem(Dataclass.Result_yxchange.Result_HCS));
                        ui->tableWidget_Result->setItem(3,3,new QTableWidgetItem(Dataclass.Result_yxchange.Result_FCS));
                        ui->tableWidget_Result->setItem(3,4,new QTableWidgetItem(Dataclass.Result_yxchange.Result_describe));

                        ui->tableWidget_Result->show();
                    }break;
                    case 15://4851
                    {
                        ui->tableWidget_Result->setItem(4,2,new QTableWidgetItem(Dataclass.Result_meterenergy.Result_HCS));
                        ui->tableWidget_Result->setItem(4,3,new QTableWidgetItem(Dataclass.Result_meterenergy.Result_FCS));
                        ui->tableWidget_Result->setItem(4,4,new QTableWidgetItem(Dataclass.Result_meterenergy.Result_describe));

                        ui->tableWidget_Result->show();
                    }break;

                    case 16:
                    {
                        ui->tableWidget_Result->setItem(5,2,new QTableWidgetItem(Dataclass.Result_meterenergy.Result_HCS));
                        ui->tableWidget_Result->setItem(5,3,new QTableWidgetItem(Dataclass.Result_meterenergy.Result_FCS));
                        ui->tableWidget_Result->setItem(5,4,new QTableWidgetItem(Dataclass.Result_meterenergy.Result_describe));

                        ui->tableWidget_Result->show();
                    }break;

                    case 17:
                    {
                        ui->tableWidget_Result->setItem(6,2,new QTableWidgetItem(Dataclass.Result_ESAM.Result_HCS));
                        ui->tableWidget_Result->setItem(6,3,new QTableWidgetItem(Dataclass.Result_ESAM.Result_FCS));
                        ui->tableWidget_Result->setItem(6,4,new QTableWidgetItem(Dataclass.Result_ESAM.Result_describe));

                        ui->tableWidget_Result->show();
                    }break;

                    case 18:
                        case 19:
                        case 20:
                    {
                        ui->tableWidget_Result->setItem(7,2,new QTableWidgetItem(Dataclass.Result_internetParam.Result_HCS));
                        ui->tableWidget_Result->setItem(7,3,new QTableWidgetItem(Dataclass.Result_internetParam.Result_FCS));
                        ui->tableWidget_Result->setItem(7,4,new QTableWidgetItem(Dataclass.Result_internetParam.Result_describe));

                        ui->tableWidget_Result->show();

                        if(decode_dataty==20)
                        {
                            QMessageBox *msgfrm =new QMessageBox(this);
                            msgfrm->setText("以太网测试开始，请连接网线。  ");

                            msgfrm->show();
                        }

                    }break;
                }

                Dataclass.buf_rev.remove(0,len_rev);
            }
            else//帧头不正确时，清除清除1位
            {
                Dataclass.buf_rev.remove(0,1);
            }
        }

//        str="收到数据: ";
//        str+=datatime->time().toString();
//        ui->textEdit_msg->append(str);
//        str.clear();

//        buf=threadTest.threadA.requestData.data();
//        qDebug() << "receive num:" <<threadTest.threadA.requestData.size();
//        for(var=0;var<threadTest.threadA.requestData.size();var++)
//        {
//            ::snprintf(tmp,256, "%02X", (unsigned char)(*buf));
//            buf++;
//            str+=QString::fromUtf8(tmp);
//            str+=" ";
//        }
//        ui->textEdit_msg->append(str);//界面显示接收到的报文显示

    }
    threadTest.threadA.requestData.clear();
}

void MainWindow::End_process()//结束测试线程
{
    if(Dataclass.DEV_testprocess_end==true)//&&Dataclass.TestINFO.testSteps_totalLevel==1  end=====若只选了串口测试，串口测试结束
    {
        Dataclass.DEV_testprocess_end=false;
        Dataclass.DEV_testprocess=false;
        Dataclass.TestINFO.testSteps_currentLevel=0;
        Dataclass.TestINFO.testSteps_currentTeststep=1;

        //停止测试线程
        ui->lineEdit_devaddr->setDisabled(false);
        ui->lineEdit_ammetervaddr->setDisabled(false);
        //this->threadTest.stop();
//        this->threadTest.terminate();
//        this->threadTest.wait();
        ui->pushBtn_Start->setDisabled(false);
        ui->pushBtn_Stop->setDisabled(true);
        ui->pushBtn_Reset->setDisabled(false);
        ui->pushBtn_Restart->setDisabled(false);

        QMessageBox *msgfrm =new QMessageBox(this);
        msgfrm->setText("当前设备测试结束。  ");
        msgfrm->show();
    }
}

void MainWindow::displayTxData()//显示串口发送报文内容
{
//    QString str;
//    char tmp[256];
//    char *buf;
//    char var;
//    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
//    if(threadTest.threadA.TxData.size()>0)
//    {
//        str="发送数据: ";
//        str+=datatime->time().toString();
//        ui->textEdit_msg->append(str);
//        str.clear();

//        buf=threadTest.threadA.TxData.data();
//        qDebug() << "send num:" <<threadTest.threadA.TxData.size();
//        for(var=0;var<threadTest.threadA.TxData.size();var++)
//        {
//            ::snprintf(tmp,256, "%02X", (unsigned char)(*buf));
//            buf++;
//            str+=QString::fromUtf8(tmp);
//            str+=" ";
//        }
//        ui->textEdit_msg->append(str);//界面显示发送到的报文显示
//    }
    this->ShowMsg(1,threadTest.threadA.TxData);
    threadTest.threadA.TxData.clear();
}

void MainWindow::ShowMsg(int type,QByteArray buf_msg)//串口报文收发显示
{
    QString str;
    char tmp[256];
    char *buf_msgshow;

    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
    if(buf_msg.size()>0)
    {
        if(type==1)str="发送数据: ";
        else if(type==2)str="接收数据: ";
        str+=datatime->time().toString();
        ui->textEdit_msg->append(str);
        str.clear();

        buf_msgshow=buf_msg.data();
        qDebug() << "send num:" <<buf_msg.size();
        for(int var=0;var<buf_msg.size();var++)
        {
            ::snprintf(tmp,256, "%02X", (unsigned char)(*buf_msgshow));
            buf_msgshow++;
            str+=QString::fromUtf8(tmp);
            str+=" ";
        }
        ui->textEdit_msg->append(str);//界面显示发送到的报文显示
    }
}

void MainWindow::on_pushButton_clear_clicked()//清空报文显示
{
    ui->textEdit_msg->clear();
}

void MainWindow::newConnect()
{
    ui->textEdit_msg->append("new client connected!!!");

    m_tcpsocket = m_tcpserver->nextPendingConnection();//设置监听
    connect(m_tcpsocket,SIGNAL(readyRead()),this,SLOT(readMessage())); //服务器接收客户端的消息
    connect(m_tcpsocket,SIGNAL(disconnected()),m_tcpsocket,SLOT(deleteLater()));
}
void MainWindow::readMessage()//读取网络通讯接收报文
{
    char buf_server[1024];
    QString str_server;
    int length=m_tcpsocket->bytesAvailable();
    m_tcpsocket->read(buf_server, length);

    if(length>0)
    {
        QByteArray bufread_server=QByteArray(buf_server,length);
        //界面显示接收的报文显示
        ShowMsg(2,bufread_server);

        int decode_dataty=threadTest.Dev_protocol.Decode(bufread_server);//threadTest.threadA.requestData
        //基于读取的结果显示到界面
        switch(decode_dataty)
        {
            case 21://以太网登录确认
            {
                ui->tableWidget_Result->setItem(8,2,new QTableWidgetItem(Dataclass.Result_internetlogin.Result_HCS));
                ui->tableWidget_Result->setItem(8,3,new QTableWidgetItem(Dataclass.Result_internetlogin.Result_FCS));
                ui->tableWidget_Result->setItem(8,4,new QTableWidgetItem(Dataclass.Result_internetlogin.Result_describe));

                ui->tableWidget_Result->show();
            }break;
            case 22:
            {
                ui->tableWidget_Result->setItem(9,2,new QTableWidgetItem(Dataclass.Result_gprsParam.Result_HCS));
                ui->tableWidget_Result->setItem(9,3,new QTableWidgetItem(Dataclass.Result_gprsParam.Result_FCS));
                ui->tableWidget_Result->setItem(9,4,new QTableWidgetItem(Dataclass.Result_gprsParam.Result_describe));

                ui->tableWidget_Result->show();
            }break;
            case 23:
            {
                ui->tableWidget_Result->setItem(9,2,new QTableWidgetItem(Dataclass.Result_gprsParam.Result_HCS));
                ui->tableWidget_Result->setItem(9,3,new QTableWidgetItem(Dataclass.Result_gprsParam.Result_FCS));
                ui->tableWidget_Result->setItem(9,4,new QTableWidgetItem(Dataclass.Result_gprsParam.Result_describe));

                ui->tableWidget_Result->show();

                //GPRS参数下设确认结束，断开当前连接
                //m_tcpsocket->disconnect();
//                QMessageBox *msgfrm =new QMessageBox(this);
//                msgfrm->setText("以太网测试结束，当前连接已断开，请断开网线，同时插入GPRS卡。  ");
//                msgfrm->show();
               QMessageBox::information(this, QString("提示"), QString("以太网测试结束，当前连接已断开，请断开网线，同时插入GPRS卡。  "), QMessageBox::tr("  确定(&O)  "));
                m_tcpsocket->close();

            }break;
            case 24://GPRS登录确认
            {
                ui->tableWidget_Result->setItem(10,2,new QTableWidgetItem(Dataclass.Result_gprslogin.Result_HCS));
                ui->tableWidget_Result->setItem(10,3,new QTableWidgetItem(Dataclass.Result_gprslogin.Result_FCS));
                ui->tableWidget_Result->setItem(10,4,new QTableWidgetItem(Dataclass.Result_gprslogin.Result_describe));

                ui->tableWidget_Result->show();

//                if(Dataclass.TestINFO.testSteps_currentLevel==3)
//                {
                    Dataclass.DEV_testprocess_end=true;//串口、网口、GPRS测试相关项，测试结束
                    emit(this->threadTest.testprocess_end());
//                }

            }break;
        }

        if(decode_dataty==21||decode_dataty==24)//登录上线，回复确认
        {
            Dataclass.BufLen_send=threadTest.Dev_protocol.Encode(Dataclass.Buffer_send,101,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
            m_tcpsocket->write(Dataclass.Buffer_send);//登录上线，回复确认
        }
        else if(decode_dataty==25)//心跳帧确认
        {
            Dataclass.BufLen_send=threadTest.Dev_protocol.Encode(Dataclass.Buffer_send,102,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
            m_tcpsocket->write(Dataclass.Buffer_send);//心跳帧确认
        }

        if(Dataclass.Buffer_send.size()>0)
        {//界面显示发送的报文显示
            ShowMsg(1,Dataclass.Buffer_send);
        }
        /*
        //QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
        if(buf_server[0]!=(char)0x68)//非法帧
            return;
        else
        {
            int adr_len=(buf_server[4]&0x0F)+1;

            if(((buf_server[adr_len+8]&0x0f)==(char)0x01)&&(buf_server[adr_len+10]==(char)0x00))//收到建立连接
            {
                Dataclass.Buffer_time.clear();
                for(int n=0;n<10;n++)//存储接收到的登录帧上传时间
                {
                    Dataclass.Buffer_time.append(buf_server[adr_len+13+n]);
                }

//                str_server="接收建立连接：";
//                str_server+=datatime->time().toString();
//                ui->textEdit_msg->append(str_server);
//                str_server.clear();

//                qDebug() << "receive num:" <<length;
//                for(int var=0;var<length;var++)
//                {
//                    str_server.append(QString::number(static_cast<unsigned char>(buf_server[var]), 16).toUpper());
//                    //str_server+=QString::number(buf_server[var], 16);//buf_server[var];//QString::fromUtf8(buf_server[var]);
//                    str_server+=" ";
//                }
//                ui->textEdit_msg->append(str_server);//界面显示接收报文显示

                Dataclass.BufLen_send=threadTest.Dev_protocol.Encode(Dataclass.Buffer_send,101,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                m_tcpsocket->write(Dataclass.Buffer_send);
            }
            else if(((buf_server[adr_len+8]&0x0f)==0x01)&&(buf_server[adr_len+10]==0x01))//收到心跳测试
            {
                Dataclass.Buffer_time.clear();
                for(int n=0;n<10;n++)//存储心跳帧上传时间
                {
                    Dataclass.Buffer_time.append(buf_server[adr_len+13+n]);
                }
//                str_server="接收心跳测试：";
//                str_server+=datatime->time().toString();
//                ui->textEdit_msg->append(str_server);
//                str_server.clear();

//                qDebug() << "receive num:" <<length;
////                QByteArray array(buf_server, length);
////                ui->textEdit_msg->setText(QString(array.toHex()));
//                for(int var=0;var<length;var++)
//                {
////                    int v = buf_server[var];
////                    str_server+=QString::number(v, 16);//QString::fromUtf8(buf_server[var]);
//                    str_server.append(QString::number(static_cast<unsigned char>(buf_server[var]), 16).toUpper());
//                    str_server+=" ";
//                }
//                ui->textEdit_msg->append(str_server);//界面显示接收报文显示

                Dataclass.BufLen_send=threadTest.Dev_protocol.Encode(Dataclass.Buffer_send,102,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                m_tcpsocket->write(Dataclass.Buffer_send);
            }



            if(Dataclass.Buffer_send.size()>0)
            {//界面显示发送的报文显示
                ShowMsg(1,Dataclass.Buffer_send);
            }


        }
        */

    }

}

void MainWindow::sendMessage_server()//发送
{
    if(Dataclass.Buffer_send.size()>0)
        m_tcpsocket->write(Dataclass.Buffer_send);
}


void MainWindow::sendMessage()
{

    QTextStream out(m_tcpsocket);
    //out<<ui->lineEdit->text()<<endl;

}

void MainWindow::on_btn_Link_clicked()//连接
{
    if(paramfrm.exec()==QDialog::Accepted)//成功打开串口和网口
    {
        //成功打开串口，显示当前连接的串口号和波特率
        threadTest.threadA.startCom();
        qDebug() << "Brush:" <<"thread starting";
        //this->threadA.setPortnum(Dataclass.get_PortName());
        threadTest.threadA.changeComState(false);
        threadTest.threadA.start();

        qDebug() << "Result      : " << "Link_OK";
        ui->textEdit_msg->append("串口网口打开完成:"
                                 +Dataclass.get_PortName()+","
                                 +QString::number(Dataclass.get_BaudRate(),10));
        //tcp连接初始化
        m_tcpserver = new QTcpServer(this);
        m_tcpsocket = new QTcpSocket(this);
        m_tcpserver->listen(QHostAddress::Any,Dataclass.get_Port_server());//监听的端口号6666
        connect(m_tcpserver,SIGNAL(newConnection()), this,SLOT(newConnect()));
    }


    ui->pushBtn_Start->setDisabled(false);
    ui->pushBtn_Stop->setDisabled(true);
    ui->pushBtn_Restart->setDisabled(false);
    ui->pushBtn_Reset->setDisabled(false);
    ui->btn_Link->setDisabled(true);
    ui->btn_unLink->setDisabled(false);
}

void MainWindow::on_btn_unLink_clicked()//断开连接
{
    qDebug() << "Brush:" <<"thread1 stoping";
    threadTest.threadA.stop();
    qDebug() << "Brush:" <<"com close";

    m_tcpsocket->close();
    ui->textEdit_msg->append("串口网口关闭完成");

    ui->pushBtn_Start->setDisabled(true);
    ui->pushBtn_Stop->setDisabled(true);
    ui->pushBtn_Restart->setDisabled(true);
    ui->pushBtn_Reset->setDisabled(true);
    ui->btn_Link->setDisabled(false);
    ui->btn_unLink->setDisabled(true);
}
