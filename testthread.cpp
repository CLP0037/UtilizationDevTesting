#include "testthread.h"
#include "mainwindow.h"
#include "publicdataclass.h"
#include "mainwindow.h"
#include "dev_protocol.h"
#include<QDebug>
#include <QDateTime>

extern PublicDataclass Dataclass;
//extern  MyThread threadA;
//extern DEV_protocol Dev_protocol;

//extern PublicDataclass Dataclass;
//MyThread threadA;
DEV_protocol Dev_protocol;



TestThread::TestThread()
{

}

void TestThread::run()
{
    while(Dataclass.DEV_testprocess)//true
    {
        qDebug()<<"Test thread";
        //char var,tmp[256];

        QString str_msg;
        str_msg="";
        QString str_protocol;
        str_protocol="";


        if(Dataclass.TestINFO.testSteps_currentTeststep==1)//step1====启动测试后读取版本信息
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_versionRead==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[0]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_versionRead=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,1,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="设备版本信息读取: ";
                Dataclass.TestINFO.test_resendtimes++;
            }

        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==2)//step2====版本信息读取成功后读取当前时间
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_timeRead==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[1]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_timeRead=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,2,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="设备当前时间读取: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==3)//step3===="设备终端电压读取: "
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_voltageRead==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[2]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_voltageRead=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,3,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="设备终端电压读取: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==4)//step4===="设备遥信变位读取: "
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_yxchangeRead==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[3]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_yxchangeRead=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,4,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="设备遥信变位读取: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==5)//step5===="电表有功电能读取转发1: "
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_meterenergyRead_4851==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[4]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_meterenergyRead_4851=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,5,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="电表有功电能读取转发1: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==6)//step6===="电表有功电能读取转发2: "
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_meterenergyRead_4852==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[5]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_meterenergyRead_4852=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,6,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="电表有功电能读取转发2: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==7)//step7====ESAM版本信息读取
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_ESAMRead==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[6]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_ESAMRead=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,7,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="ESAM版本信息读取: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==8)//step8====以太网参数下设1
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_internetParamset_1==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[7]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_internetParamset_1=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,81,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="以太网参数下设1: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==9)//step9====以太网参数下设2
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_internetParamset_2==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[7]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_internetParamset_2=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,82,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="以太网参数下设2: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==10)//step10====以太网参数下设3
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_internetParamset_3==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[7]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep=0;//Dataclass.TestINFO.testSteps_currentTeststep++;等待以太网上线
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_internetParamset_3=false;

                if(Dataclass.TestINFO.testSteps_currentLevel==1)
                {
                    Dataclass.DEV_testprocess_end=true;//若只选择了串口测试相关项，测试结束
                    emit(this->testprocess_end());
                }
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,83,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="以太网参数下设3: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

//        if(Dataclass.TestINFO.testSteps_currentTeststep==11)//step11====以太网登录确认
//        {
//            if(Dataclass.TestINFO.step_Selected[10]==false
//                    ||Dataclass.DEV_internetLogin==true
//                    ||(Dataclass.TestINFO.test_resendtimes>2))//未选择当前测试项   收到成功回复  重发过两次
//            {
//                Dataclass.TestINFO.testSteps_currentTeststep++;
//                Dataclass.TestINFO.test_resendtimes=0;
//                Dataclass.DEV_internetLogin=false;
//            }
//            else
//            {
//                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,101,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
//                str_msg="以太网登录确认: ";
//                Dataclass.TestINFO.test_resendtimes++;
//            }
//        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==12)//step12====GPRS参数下设1
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_gprsParamset_1==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[9]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep++;
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_gprsParamset_1=false;
            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,91,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="GPRS参数下设1: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

        if(Dataclass.TestINFO.testSteps_currentTeststep==13)//step13====GPRS参数下设2
        {
            if(((Dataclass.TestINFO.test_resendtimes>0)&&(Dataclass.DEV_gprsParamset_2==true||(Dataclass.TestINFO.test_resendtimes>2)))
                    ||(Dataclass.TestINFO.step_Selected[9]==false))//未选择当前测试项   收到成功回复  重发过两次
            {
                Dataclass.TestINFO.testSteps_currentTeststep=0;//Dataclass.TestINFO.testSteps_currentTeststep++;//等待GPRS上线
                Dataclass.TestINFO.test_resendtimes=0;
                Dataclass.DEV_gprsParamset_2=false;

                if(Dataclass.TestINFO.testSteps_currentLevel==2)
                {
                    Dataclass.DEV_testprocess_end=true;//若只选择了串口测试相关项和网口测试相关项，测试结束
                    emit(this->testprocess_end());
                }

            }
            else
            {
                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,92,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
                str_msg="GPRS参数下设2: ";
                Dataclass.TestINFO.test_resendtimes++;
            }
        }

//        if(Dataclass.TestINFO.testSteps_currentTeststep==14)//step14====GPRS登录确认
//        {
//            if(Dataclass.TestINFO.step_Selected[13]==false
//                    ||Dataclass.DEV_internetLogin==true
//                    ||(Dataclass.TestINFO.test_resendtimes>2))//未选择当前测试项   收到成功回复  重发过两次
//            {
//                Dataclass.TestINFO.testSteps_currentTeststep++;
//                Dataclass.TestINFO.test_resendtimes=0;
//                Dataclass.DEV_internetLogin=false;
//            }
//            else
//            {
//                Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,101,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
//                str_msg="GPRS登录确认: ";
//                Dataclass.TestINFO.test_resendtimes++;
//            }
//        }

        /*
        if(Dataclass.DEV_testprocess_start==true)//step1====启动测试后读取版本信息
        {
            Dataclass.DEV_testprocess_start=false;

            Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,1,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
            str_msg="设备版本信息读取: ";
            //qDebug("the Buffer_send[0] is:%d\n",Dataclass.Buffer_send.at(0));

//            QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
//            str_msg+=datatime->time().toString();
//            MainWindow->textEdit_msg->append(str);
//            str.clear();

//            buf=Dataclass.Buffer_send.data();
//            for(var=0;var<24;var++)
//            {
//                ::snprintf(tmp,256, "%02X", (unsigned char)(*buf));
//                buf++;
//                str_protocol+=QString::fromUtf8(tmp);
//                str_protocol+=" ";
//            }
//            ui->textEdit_msg->append(str);
//            this->threadA.TxData.clear();
//            this->threadA.TxData.append(Dataclass.Buffer_send,Dataclass.BufLen_send);
//            this->threadA.changeTxState(true);

        }

        if(Dataclass.DEV_versionRead==true)//step2====版本信息读取成功后读取当前时间
        {
            Dataclass.DEV_versionRead=false;

            Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,2,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
            str_msg="设备当前时间读取: ";
        }

        if(Dataclass.DEV_timeRead==true)//step3====当前时间读取成功后读取终端电压
        {
            Dataclass.DEV_timeRead=false;

            Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,3,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
            str_msg="设备终端电压读取: ";
        }
        if(Dataclass.DEV_voltageRead==true)//step4====读取电压成功后读取遥信变位
        {
            Dataclass.DEV_voltageRead=false;

            Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,4,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
            str_msg="设备遥信变位读取: ";
        }
        if(Dataclass.DEV_yxchangeRead==true)//step5====读取遥信变位成功后转发读取电能表
        {
            Dataclass.DEV_yxchangeRead=false;

            Dataclass.BufLen_send=this->Dev_protocol.Encode(Dataclass.Buffer_send,5,Dataclass.get_DEV_addr(),Dataclass.get_ammeter_addr());
            str_msg="电表有功电能读取转发: ";
        }
*/


        Dataclass.ShowStr_Msg=str_msg;
        Dataclass.ShowStr_Protocol=str_protocol;

        if(Dataclass.ShowStr_Msg!=""&&Dataclass.BufLen_send>0)//有内容发送
        {
            if(Dataclass.TestINFO.testSteps_currentTeststep<=10)//串口发送
            {
//                char *buf_send;
//                buf_send=Dataclass.Buffer_send.data();

                this->threadA.TxData.clear();
                this->threadA.TxData.append(Dataclass.Buffer_send,Dataclass.BufLen_send);
                this->threadA.changeTxState(true);
            }
            else//网口发送
            {
                //m_tcpsocket->write(Dataclass.Buffer_send);
                //sendmsg_server()
                emit(this->sendmsg_server());
            }

        }

        sleep(20);
    }
}

void TestThread::stop()
{
//   TestThread.terminate();
//   TestThread.wait();
   //threadTest

}
