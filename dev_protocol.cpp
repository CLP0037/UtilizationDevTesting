#include "dev_protocol.h"
#include<qstring.h>

#include <QString>
#include <QStringList>
#include <QList>
#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include "Checksum.h"
#include "publicdataclass.h"
#include <QChar>

extern PublicDataclass Dataclass;

DEV_protocol::DEV_protocol()
{

}


int DEV_protocol::Encode(QByteArray &buf, int dataty,QString DEV_adr,QString ammeter_adr)//组包
{
    //QString DEV_adr:终端地址
    //QString ammeter_adr:电表地址
//    #if 0
//    #endif
    //return 0;
    int length=0;
    int len_devaddr=0;
    buf.clear();
    buf.append(0x68);//buf[0] = 0x68;

    buf.append((char)0x00);//buf[length++]=0x00;//L
    buf.append((char)0x00);//buf[length++]=0x00;//L

    //buf[length++]=Get_C_from_dataty(dataty);//控制域
    buf.append(0x43);//buf[length++]=0x43;

    //地址域
    if(DEV_adr=="AAAAAAAAAAAA"||DEV_adr=="")
    {
        buf.append(0x45);//buf[length++]=0x45;
        buf.append(0xAA);//buf[length++]=0xAA;
        buf.append(0xAA);//buf[length++]=0xAA;
        buf.append(0xAA);//buf[length++]=0xAA;
        buf.append(0xAA);//buf[length++]=0xAA;
        buf.append(0xAA);//buf[length++]=0xAA;
        buf.append(0xAA);//buf[length++]=0xAA;
        buf.append(0x10);//buf[length++]=0x10;
    }
    else
    {

        int len_a=DEV_adr.size();
        len_devaddr=(len_a/2)+2;
        buf.append((len_a/2)-1);//buf[length++]=(len_a/2)-1;//数据长度

        for(int n=0;n<len_a/2;n++)
        {
            bool ok;
            int hex_out=DEV_adr.mid(len_a-2-2*n,2).toInt(&ok,16);
            buf.append(hex_out);//buf[length++]=devArray[n];
        }
        buf.append((char)0x00);//buf[length++]=0x00;//
    }

    //帧头校验
    buf.append((char)0x00);//buf[length++]=0x00;//
    buf.append((char)0x00);//buf[length++]=0x00;//

    //  数据域组包
    switch(dataty)
    {
    //=======================串口通讯组包========================//
    case 1://读设备版本
    {
        buf.append(0x05);//buf[length++]=0x05;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append(0x43);//buf[length++]=0x43;
        buf.append((char)0x00);//buf[length++]=0x00;
        buf.append(0x03);//buf[length++]=0x03;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append((char)0x00);//buf[length++]=0x00;
    }
        break;

    case 2://读当前时间
    {
        buf.append(0x05);//buf[length++]=0x05;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append(0x40);//buf[length++]=0x40;
        buf.append((char)0x00);//buf[length++]=0x00;
        buf.append(0x02);//buf[length++]=0x02;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append((char)0x00);//buf[length++]=0x00;
    }
        break;

    case 3://读终端电压
    {
        buf.append(0x05);//buf[length++]=0x05;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append(0x20);//buf[length++]=0x20;
        buf.append((char)0x00);//buf[length++]=0x00;
        buf.append(0x02);//buf[length++]=0x02;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append((char)0x00);//buf[length++]=0x00;
    }
        break;

    case 4://读遥信变位
    {
        buf.append(0x05);//buf[length++]=0x05;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append(0xF2);//buf[length++]=0xF2;
        buf.append(0x03);//buf[length++]=0x03;
        buf.append(0x02);//buf[length++]=0x02;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append((char)0x00);//buf[length++]=0x00;
    }
        break;

    case 5://读电表正向有功电能===4851
    case 6://读电表正向有功电能===4852
    {
        buf.append(0x09);//buf[length++]=0x09;
        buf.append(0x07);//buf[length++]=0x07;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append(0xF2);//buf[length++]=0xF2;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append(0x02);//buf[length++]=0x02;

        if(dataty==5)
            buf.append(0x01);//buf[length++]=0x01;//01===4851;02===4852
        else if(dataty==6)
            buf.append(0x02);

        buf.append(0x03);//buf[length++]=0x03;//波特率：2400
        buf.append(0x02);//buf[length++]=0x02;//偶校验
        buf.append(0x08);//buf[length++]=0x08;//数据位：8
        buf.append(0x01);//buf[length++]=0x01;//停止位：1
        buf.append((char)0x00);//buf[length++]=0x00;//流控：无

        buf.append((char)0x00);//buf[length++]=0x00;//超时时间
        buf.append(0x0A);//buf[length++]=0x0A;//
        buf.append((char)0x00);//buf[length++]=0x00;//
        buf.append(0x0A);//buf[length++]=0x0A;//

        buf.append(0x10);//buf[length++]=0x10;//长度=16

        buf.append(0x68);//buf[length++]=0x68;//

        //电表地址
        int len_b=ammeter_adr.size();//数据长度
        int ammeter_adr_buf1;
        int ammeter_adr_buf2;
        bool ok_adr;
        for(int n=0;n<len_b/2;n++)
        {
            ammeter_adr_buf1=ammeter_adr.mid(len_b-2-2*n,1).toInt(&ok_adr,10);
            ammeter_adr_buf2=ammeter_adr.mid(len_b-1-2*n,1).toInt(&ok_adr,10);

            buf.append(ammeter_adr_buf1*16+ammeter_adr_buf2);//ammeter_adr.mid(len_b-2-2*n,2)
        }

        buf.append(0x68);//buf[length++]=0x68;
        buf.append(0x11);//buf[length++]=0x11;
        buf.append(0x04);//buf[length++]=0x04;
        buf.append(0x33);//buf[length++]=0x33;
        buf.append(0x32);//buf[length++]=0x32;
        buf.append(0x34);//buf[length++]=0x34;
        buf.append(0x33);//buf[length++]=0x33;
        buf.append(0x56);//buf[length++]=0x56;
        buf.append(0x16);//buf[length++]=0x16;
        buf.append((char)0x00);//buf[length++]=0x00;
    }
        break;

    case 7://ESAM版本信息读取组包
    {
        buf.append(0x05);//05 01 00
        buf.append(0x01);
        buf.append((char)0x00);

        buf.append(0xF1);//F1 00 03 00
        buf.append((char)0x00);
        buf.append(0x03);
        buf.append((char)0x00);

        buf.append((char)0x00);//00===无时间标签

    }break;

    //case 8://以太网参数下设组包======分3步
    case 81://第一步:设置工作模式、在线方式、连接方式等参数
    {
        buf.append(0x06);//06 01 00
        buf.append(0x01);
        buf.append((char)0x00);

        buf.append(0x45);//45 10 02 00
        buf.append(0x10);
        buf.append(0x02);
        buf.append((char)0x00);

        buf.append(0x02);//02 08
        buf.append(0x08);

        buf.append(0x16);//工作模式:混合模式（0），客户机模式（1），服务器模式（2）
        buf.append(Dataclass.INTERNET_Param.workmodel);

        buf.append(0x16);//连接方式:TCP（0），UDP（1）
        buf.append(Dataclass.INTERNET_Param.linkType);

        buf.append(0x16);//连接应用方式:主备模式（0），多连接模式（1）
        buf.append(Dataclass.INTERNET_Param.applicationType);

        buf.append(0x01);//类型：1;长度：0
        buf.append((char)0x00);

        buf.append(0x09);//类型：9;长度：4====代理服务器地址
        buf.append(0x04);
        buf.append((char)0x00);
        buf.append((char)0x00);
        buf.append((char)0x00);
        buf.append((char)0x00);

        buf.append(0x12);//类型：18;值：0====代理端口
        buf.append((char)0x00);
        buf.append((char)0x00);

        buf.append(0x04);//类型：4;长度：8====超时时间及重发次数
        buf.append(0x08);
        buf.append(0x31);

        buf.append(0x12);//类型：18;值：0====300=0x012c
        buf.append((Dataclass.INTERNET_Param.heartbeatCycle&0xff00)>>8);
        buf.append(Dataclass.INTERNET_Param.heartbeatCycle&0x00ff);

        buf.append((char)0x00);//00===无时间标签

    }break;
    case 82://第二步:设置主站IP、端口
    {
        buf.append(0x06);//06 01 00
        buf.append(0x01);
        buf.append((char)0x00);

        buf.append(0x45);//45 10 03 00
        buf.append(0x10);
        buf.append(0x03);
        buf.append((char)0x00);

        buf.append(0x01);//类型：1;长度：1
        buf.append(0x01);

        buf.append(0x02);//类型：2;项数：2
        buf.append(0x02);

        buf.append(0x09);//类型：9;长度：主站IP长度
        QStringList strList=Dataclass.INTERNET_Param.IP_server.split(".",QString::SkipEmptyParts);
        buf.append(strList.size());


        bool ok;
        int aa;
        for(int n=0;n<strList.size();n++)
        {
            aa=strList[n].toInt(&ok,10);
            buf.append(aa);
        }

        buf.append(0x12);//类型：18;值：主站Port
        buf.append((Dataclass.INTERNET_Param.port_server&0xff00)>>8);
        buf.append(Dataclass.INTERNET_Param.port_server&0x00ff);

        buf.append((char)0x00);//00===无时间标签

    }break;
    case 83://第三步:设置终端IP、端口
    {
        buf.append(0x06);//06 01 00
        buf.append(0x01);
        buf.append((char)0x00);

        buf.append(0x45);//45 10 03 00
        buf.append(0x10);
        buf.append(0x04);
        buf.append((char)0x00);

        buf.append(0x02);//类型：2;项数：6
        buf.append(0x06);

        buf.append(0x16);//类型：2;值：IP配置方式
        buf.append(Dataclass.INTERNET_Param.IP_setway);

        buf.append(0x09);//类型：9;长度：设备IP长度
        QStringList strList=Dataclass.INTERNET_Param.IP_dev.split(".",QString::SkipEmptyParts);
        buf.append(strList.size());
        bool ok;
        int aa;
        for(int n=0;n<strList.size();n++)
        {
            aa=strList[n].toInt(&ok,10);
            buf.append(aa);
        }

        buf.append(0x09);//类型：9;长度：子网掩码IP长度
        strList.clear();
        strList=Dataclass.INTERNET_Param.IP_subnetmask.split(".",QString::SkipEmptyParts);
        buf.append(strList.size());


        for(int n=0;n<strList.size();n++)
        {
            aa=strList[n].toInt(&ok,10);
            buf.append(aa);
        }

        buf.append(0x09);//类型：9;长度：网关IP长度
        strList.clear();
        strList=Dataclass.INTERNET_Param.IP_gateway.split(".",QString::SkipEmptyParts);
        buf.append(strList.size());


        for(int n=0;n<strList.size();n++)
        {
            aa=strList[n].toInt(&ok,10);
            buf.append(aa);
        }

       buf.append(0x09);//类型：9;长度：0
       buf.append((char)0x00);

       buf.append(0x09);//类型：9;长度：0
       buf.append((char)0x00);

        buf.append((char)0x00);//00===无时间标签

    }break;
    //case 9://GPRS参数下设组包======分2步
    case 91://第一步:设置工作模式、在线方式、连接方式等参数
    {
        buf.append(0x06);//06 01 00
        buf.append(0x01);
        buf.append((char)0x00);

        buf.append(0x45);//45 00 02 00
        buf.append((char)0x00);
        buf.append(0x02);
        buf.append((char)0x00);

        buf.append(0x02);//02 0C
        buf.append(0x0C);

        buf.append(0x16);//工作模式:混合模式（0），客户机模式（1），服务器模式（2）
        buf.append(Dataclass.GPRS_Param.workmodel);

        buf.append(0x16);//在线方式:永久在线（0），被动激活（1）
        buf.append(Dataclass.GPRS_Param.onlineType);

        buf.append(0x16);//连接方式:TCP（0），UDP（1）
        buf.append(Dataclass.GPRS_Param.linkType);

        buf.append(0x16);//连接应用方式:主备模式（0），多连接模式（1）
        buf.append(Dataclass.GPRS_Param.applicationType);

        buf.append(0x01);//类型：1;长度：0
        buf.append((char)0x00);

        buf.append(0x0A);//类型：10;长度：APN长度
        buf.append(Dataclass.GPRS_Param.APN.size());
        for(int n=0;n<Dataclass.GPRS_Param.APN.size();n++)
        {
            buf.append(Dataclass.GPRS_Param.APN.data()[n]);
        }

        buf.append(0x0A);//类型：10;长度：userName长度
        buf.append(Dataclass.GPRS_Param.userName.size());
        for(int n=0;n<Dataclass.GPRS_Param.userName.size();n++)
        {
            buf.append(Dataclass.GPRS_Param.userName.data()[n]);
        }

        buf.append(0x0A);//类型：10;长度：password长度
        buf.append(Dataclass.GPRS_Param.password.size());
        for(int n=0;n<Dataclass.GPRS_Param.password.size();n++)
        {
            buf.append(Dataclass.GPRS_Param.password.data()[n]);
        }

        buf.append(0x09);//类型：9;长度：4====代理服务器地址
        buf.append(0x04);
        buf.append((char)0x00);
        buf.append((char)0x00);
        buf.append((char)0x00);
        buf.append((char)0x00);

        buf.append(0x12);//类型：18;值：0====代理端口
        buf.append((char)0x00);
        buf.append((char)0x00);

        buf.append(0x04);//类型：4;长度：8====超时时间及重发次数
        buf.append(0x08);
        buf.append(0x53);

        buf.append(0x12);//类型：18;值：0====300=0x012c
        buf.append((Dataclass.GPRS_Param.heartbeatCycle&0xff00)>>8);
        buf.append(Dataclass.GPRS_Param.heartbeatCycle&0x00ff);

        buf.append((char)0x00);//00===无时间标签
    }break;
    case 92://第二步:设置主站IP、端口
    {
        buf.append(0x06);//06 01 00
        buf.append(0x01);
        buf.append((char)0x00);

        buf.append(0x45);//45 00 03 00
        buf.append((char)0x00);
        buf.append(0x03);
        buf.append((char)0x00);

        buf.append(0x01);//类型：1;长度：1
        buf.append(0x01);

        buf.append(0x02);//类型：2;项数：2
        buf.append(0x02);

        buf.append(0x09);//类型：9;长度：主站IP长度
        buf.append(Dataclass.GPRS_Param.IP.size());

        QStringList strList=Dataclass.GPRS_Param.IP.split(".",QString::SkipEmptyParts);
        bool ok;
        int aa;
        for(int n=0;n<strList.size();n++)
        {
            aa=strList[n].toInt(&ok,10);
            buf.append(aa);
        }

        buf.append(0x12);//类型：18;值：主站Port
        buf.append((Dataclass.GPRS_Param.port&0xff00)>>8);
        buf.append(Dataclass.GPRS_Param.port&0x00ff);

        buf.append((char)0x00);//00===无时间标签

    }break;

    //=======================手动命令组包========================//
    case 21://恢复出厂设置
    {
        buf.append(0x07);//buf[length++]=0x07;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append(0x43);//buf[length++]=0x43;
        buf.append((char)0x00);//buf[length++]=0x00;
        buf.append(0x04);//buf[length++]=0x04;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append((char)0x00);//buf[length++]=0x00;
        buf.append((char)0x00);//buf[length++]=0x00;
    }
        break;

    case 22://设备重启
    {
        buf.append(0x07);//buf[length++]=0x07;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append(0x43);//buf[length++]=0x43;
        buf.append((char)0x00);//buf[length++]=0x00;
        buf.append(0x01);//buf[length++]=0x01;
        buf.append((char)0x00);//buf[length++]=0x00;

        buf.append((char)0x00);//buf[length++]=0x00;
        buf.append((char)0x00);//buf[length++]=0x00;
    }
        break;

    //=======================网络通讯组包========================//
    case 101://设备网络建立连接组包===确认
    case 102://设备心跳帧组包===确认
    {
        buf.append(0x81);//
        buf.append((char)0x00);//
        buf.append(0x80);//

        //接收到的时间===组包
        for(int n=0;n<Dataclass.Buffer_time.size();n++)
        {
            buf.append(Dataclass.Buffer_time[n]);
        }
        //系统时间
        QDateTime time_now = QDateTime::currentDateTime();
        QString year=time_now.toString("yyyy");
        QString month=time_now.toString("MM");
        QString day=time_now.toString("dd");
        QString week=time_now.toString("ddd");
        QString hour=time_now.toString("hh");
        QString minute=time_now.toString("mm");
        QString second=time_now.toString("ss");
        QString minisecond=time_now.toString("zzz");
        int year_int;
        int month_int;
        int day_int;
        int week_int;
        int hour_int;
        int minute_int;
        int second_int;
        int minisecond_int;
        bool ok;


        //当前系统时间组包1
       for(int n=0;n<8;n++)//年-月-日-星期-时-分-秒-毫秒
       {
           switch(n)
           {
           case 0://年
           {
               year_int=year.toInt(&ok,10);
               buf.append((year_int&0xff00)>>8);
               buf.append(year_int&0x00ff);
           }break;
           case 1://月
           {
               month_int=month.toInt(&ok,10);
               buf.append(month_int);
           }break;
           case 2://日
           {
               day_int=day.toInt(&ok,10);
               buf.append(day_int);
           }break;
           case 3://星期
           {
               week_int=this->GET_weekint(week);
               buf.append(week_int);//
           }break;
           case 4://时
           {
               hour_int=hour.toInt(&ok,10);
               buf.append(hour_int);
           }break;
           case 5://分
           {
               minute_int=minute.toInt(&ok,10);
               buf.append(minute_int);
           }break;
           case 6://秒
           {
               second_int=second.toInt(&ok,10);
               buf.append(second_int);
           }break;
           case 7://毫秒
           {
               minisecond_int=minisecond.toInt(&ok,10);
               buf.append((minisecond_int&0xff00)>>8);
               buf.append(minisecond_int&0x00ff);
           }break;
           }

       }
        //当前系统时间组包2
       for(int n=0;n<8;n++)//年-月-日-星期-时-分-秒-毫秒
       {
           switch(n)
           {
           case 0://年
           {
               year_int=year.toInt(&ok,10);
               buf.append((year_int&0xff00)>>8);
               buf.append(year_int&0x00ff);
           }break;
           case 1://月
           {
               month_int=month.toInt(&ok,10);
               buf.append(month_int);
           }break;
           case 2://日
           {
               day_int=day.toInt(&ok,10);
               buf.append(day_int);
           }break;
           case 3://星期
           {
               week_int=this->GET_weekint(week);
               buf.append(week_int);//
           }break;
           case 4://时
           {
               hour_int=hour.toInt(&ok,10);
               buf.append(hour_int);
           }break;
           case 5://分
           {
               minute_int=minute.toInt(&ok,10);
               buf.append(minute_int);
           }break;
           case 6://秒
           {
               second_int=second.toInt(&ok,10);
               buf.append(second_int);
           }break;
           case 7://毫秒
           {
               minisecond_int=minisecond.toInt(&ok,10);
               buf.append((minisecond_int&0xff00)>>8);
               buf.append(minisecond_int&0x00ff);
           }break;
           }

       }

        buf.append((char)0x00);//
    }break;


    }

    //帧校验
    buf.append((char)0x00);//buf[length++]=0x00;
    buf.append((char)0x00);//buf[length++]=0x00;


    buf.append(0x16);//buf[length++]=0x16;
    length=buf.size();

    //帧长度
    buf[1]=length-2;

    //帧头校验
    QByteArray data = buf.mid(1,(len_devaddr+3));//QByteArray::fromHex( "15 00 43 03 59 46 46 14 00" );
    unsigned short crc16ForX25 = Checksum::crc16ForX25( data );
    QString::number( crc16ForX25, 16 );

    //buf.append((uchar)(crc16ForX25&0xff));//buf[length++]=(uchar)(crc16ForX25&0xff);
    //buf.append((uchar)((crc16ForX25&0xff00)>>8));//buf[length++]=(uchar)((crc16ForX25&0xff00)>>8);
    buf[len_devaddr+4]=(uchar)(crc16ForX25&0xff);
    buf[len_devaddr+5]=(uchar)((crc16ForX25&0xff00)>>8);

    //帧校验
    QByteArray data1 = buf.mid(1,buf.size()-4);//QByteArray::fromHex( "1c 00 81 03 59 46 46 14 00" );//"409c"
    unsigned short crc16ForX25_1 = Checksum::crc16ForX25( data1 );
    QString::number( crc16ForX25_1, 16 );
    //buf.append((uchar)(crc16ForX25_1&0xff));//buf[length++]=(uchar)(crc16ForX25_1&0xff);
    //buf.append((uchar)((crc16ForX25_1&0xff00)>>8));//buf[length++]=(uchar)((crc16ForX25_1&0xff00)>>8);
    buf[length-3]=(uchar)(crc16ForX25_1&0xff);
    buf[length-2]=(uchar)((crc16ForX25_1&0xff00)>>8);

    return length;



}

//mon tue wed thu fri sat sun
int DEV_protocol::GET_weekint(QString week)
{
    int weekint=0;
    QString weeks=week.toLower();
//    switch(weeks)
//    {
//        case "mon":
//        {
//            weekint=1;
//        }break;
//    }
    if(weeks=="mon") weekint=1;
    else if(weeks=="tue") weekint=2;
    else if(weeks=="wed") weekint=3;
    else if(weeks=="thu") weekint=4;
    else if(weeks=="fri") weekint=5;
    else if(weeks=="sat") weekint=6;
    else if(weeks=="sun") weekint=7;

    return weekint;
}

/*
void DEV_protocol::Decode()//解包
{

}
*/

int DEV_protocol::Get_C_from_dataty(int dataty)//控制域获取
{
    int C=0;

    switch(dataty)
    {
       case 1:

        break;



    }

    return C;
}

/*
void DEV_protocol::Get_A_from_dataty(int dataty)//地址域获取
{

}

void DEV_protocol::Get_APDU_from_dataty(int dataty)//链路用户数据组包
{

}


*/
unsigned short DEV_protocol::Get_HCS(QByteArray buf,int start,int len)//帧头校验
{
    QByteArray data = buf.mid(start,len);//
    unsigned short crc16ForX25 = Checksum::crc16ForX25( data );
    return crc16ForX25;
}

unsigned short DEV_protocol::Get_FCS(QByteArray buf,int start,int len)//整帧校验
{
    QByteArray data = buf.mid(start,len);//
    unsigned short crc16ForX25 = Checksum::crc16ForX25( data );
    return crc16ForX25;
}



int DEV_protocol::Decode(QByteArray buf)
{
    int dataty=0;
    unsigned short HCS_show;    //帧校验====帧校验位显示值
    unsigned short HCS_caculate;//帧校验====通过报文及帧校验方法计算值
    unsigned short FCS_show;    //帧校验====帧校验位显示值
    unsigned short FCS_caculate;//帧校验====通过报文及帧校验方法计算值

    int DEV_adr_len=0;
    //int ammeter_adr_len=0;
    QString DEV_adr;
    QString ammeter_adr;
    //bool ok;

    //char* data_buf=new char[buf.size()];
    if(buf[0]!=(char)0x68)
    {
        dataty=1;
    }
    else
    {

        DEV_adr_len=(buf[4]&0x0F)+1;
        QByteArray devadr_buf;
        //QString devadr_str;
        devadr_buf.clear();
        for(int n=0;n<DEV_adr_len;n++)
        {
            devadr_buf.append(buf[4+DEV_adr_len-n]);
        }
        //devadr_str=QString(devadr_buf);//十六进制直接转换为字符串

        HCS_show=((unsigned char)buf[DEV_adr_len+6])+((unsigned char)buf[DEV_adr_len+7]*256);
        HCS_caculate=this->Get_HCS(buf,1,DEV_adr_len+5);
        FCS_show=((unsigned char)buf[buf.size()-3])+((unsigned char)buf[buf.size()-2]*256);
        FCS_caculate=this->Get_HCS(buf,1,(buf.size()-4));

        //读取版本信息+时间+电压+YX变位+ESAM版本信息读取
        if(((buf[DEV_adr_len+8]&0x0f)==(char)0x05)&&(buf[DEV_adr_len+9]==(char)0x01))//85 01 00
        {
            if((buf[DEV_adr_len+11]==(char)0x43)&&(buf[DEV_adr_len+13]==(char)0x03))//版本信息
            {
                Dataclass.DEV_versionRead=true;
//                unsigned short aa=(unsigned short)buf[DEV_adr_len+6];
//                unsigned short bb=(unsigned short)buf[DEV_adr_len+7]*256;
//                HCS_show=((unsigned char)buf[DEV_adr_len+6])+((unsigned char)buf[DEV_adr_len+7]*256);
//                //HCS_show=(buf.mid(DEV_adr_len+6,1)).toInt(&ok,10)+(256*(buf.mid(DEV_adr_len+7,1)).toInt(&ok,10));
//                HCS_caculate=this->Get_HCS(buf,1,DEV_adr_len+5);
                if(HCS_show==HCS_caculate)
                {
                    Dataclass.Result_version.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_version.Result_HCS="帧校验不正确";
                }

//                FCS_show=((unsigned char)buf[buf.size()-3])+((unsigned char)buf[buf.size()-2]*256);
//                FCS_caculate=this->Get_HCS(buf,1,(buf.size()-4));

                if(FCS_show==FCS_caculate)
                {
                    Dataclass.Result_version.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_version.Result_FCS="帧校验不正确";
                }
                Dataclass.Result_version.Result_describe="Recieve OK :";//

                int item_num=buf[DEV_adr_len+17];//项目数
                QByteArray describe_data=buf.mid(DEV_adr_len+18,buf.size()-(DEV_adr_len+19)-3);
                int current_len=0;
                for(int n=0;n<item_num;n++)
                {
                    current_len=describe_data[1];
                    Dataclass.Result_version.Result_describe+=QString(describe_data.mid(2,current_len));
                    Dataclass.Result_version.Result_describe+=" ";
                    describe_data.remove(0,(current_len+2));
                }

                dataty=11;
            }
            else if((buf[DEV_adr_len+11]==(char)0x40)&&(buf[DEV_adr_len+13]==(char)0x02))//时间
            {
                Dataclass.DEV_timeRead=true;

                if(HCS_show==HCS_caculate)//=====
                {
                    Dataclass.Result_time.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_time.Result_HCS="帧校验不正确";
                }
                if(FCS_show==FCS_caculate)//=====
                {
                    Dataclass.Result_time.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_time.Result_FCS="帧校验不正确";
                }
//                Dataclass.Result_time.Result_HCS="0x00";
//                Dataclass.Result_time.Result_FCS="0x00";
                Dataclass.Result_time.Result_describe="Recieve OK :";

                QByteArray describe_data=buf.mid(DEV_adr_len+17,buf.size()-(DEV_adr_len+18)-3);
                QByteArray test = describe_data.mid(0,2);
                int test_int = (unsigned char)(test[1]) + (unsigned char) (test[0]) *256;
                Dataclass.Result_time.Result_describe+=QString("%1").arg(test_int);//年
                Dataclass.Result_time.Result_describe+="年-";
                test =describe_data.mid(2,1);
                test_int=(unsigned char)(test[0]);
                Dataclass.Result_time.Result_describe+=QString("%1").arg(test_int);//月
                Dataclass.Result_time.Result_describe+="月-";
                test =describe_data.mid(3,1);
                test_int=(unsigned char)(test[0]);
                Dataclass.Result_time.Result_describe+=QString("%1").arg(test_int);//日
                Dataclass.Result_time.Result_describe+="日-";
                test =describe_data.mid(4,1);
                test_int=(unsigned char)(test[0]);
                Dataclass.Result_time.Result_describe+=QString("%1").arg(test_int);//时
                Dataclass.Result_time.Result_describe+="时-";
                test =describe_data.mid(5,1);
                test_int=(unsigned char)(test[0]);
                Dataclass.Result_time.Result_describe+=QString("%1").arg(test_int);//分
                Dataclass.Result_time.Result_describe+="分-";
                test =describe_data.mid(6,1);
                test_int=(unsigned char)(test[0]);
                Dataclass.Result_time.Result_describe+=QString("%1").arg(test_int);//秒
                Dataclass.Result_time.Result_describe+="秒-";
                test =describe_data.mid(7,2);
                test_int=(unsigned char)(test[0]);
                Dataclass.Result_time.Result_describe+=QString::number(test_int);//毫秒
                Dataclass.Result_time.Result_describe+="毫秒";

                dataty=12;
            }
            else if((buf[DEV_adr_len+11]==(char)0x20)&&(buf[DEV_adr_len+13]==(char)0x02))//终端电压
            {
                Dataclass.DEV_voltageRead=true;

                if(HCS_show==HCS_caculate)//=====
                {
                    Dataclass.Result_voltage.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_voltage.Result_HCS="帧校验不正确";
                }
                if(FCS_show==FCS_caculate)//=====
                {
                    Dataclass.Result_voltage.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_voltage.Result_FCS="帧校验不正确";
                }
//                Dataclass.Result_voltage.Result_HCS="0x00";
//                Dataclass.Result_voltage.Result_FCS="0x00";
                Dataclass.Result_voltage.Result_describe="Recieve OK :";

                int item_num=buf[DEV_adr_len+17];//项目数
                QByteArray describe_data=buf.mid(DEV_adr_len+18,buf.size()-(DEV_adr_len+19)-3);
                //int current_len=0;
                for(int n=0;n<item_num;n++)
                {
                    //current_len=describe_data[1];
                    QByteArray test = describe_data.mid(0,3);
                    int test_int = (unsigned char)(test[2]) + (unsigned char) (test[1]) *256;
                    Dataclass.Result_voltage.Result_describe+=QString("%1").arg(test_int);
                    Dataclass.Result_voltage.Result_describe+=" ";
                    describe_data.remove(0,3);
                }
                dataty=13;
            }
            else if((buf[DEV_adr_len+11]==(char)0xF2)&&(buf[DEV_adr_len+12]==(char)0x03)&&(buf[DEV_adr_len+13]==(char)0x02))//YX变位
            {
                Dataclass.DEV_yxchangeRead=true;

                if(HCS_show==HCS_caculate)//=====
                {
                    Dataclass.Result_yxchange.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_yxchange.Result_HCS="帧校验不正确";
                }
                if(FCS_show==FCS_caculate)//=====
                {
                    Dataclass.Result_yxchange.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_yxchange.Result_FCS="帧校验不正确";
                }
//                Dataclass.Result_yxchange.Result_HCS="0x00";
//                Dataclass.Result_yxchange.Result_FCS="0x00";
                Dataclass.Result_yxchange.Result_describe="Recieve OK :";

                int item_num=buf[DEV_adr_len+19];//项目数
                QByteArray describe_data=buf.mid(DEV_adr_len+20,buf.size()-(DEV_adr_len+19)-3);
                //int current_len=0;
                for(int n=0;n<item_num;n++)
                {
                    //current_len=describe_data[1];
                    QByteArray test = describe_data.mid(0,2);
                    Dataclass.Result_yxchange.Result_describe+="类型：";
                    int test_int = (unsigned char)(test[0]);
                    Dataclass.Result_yxchange.Result_describe+=QString("%1").arg(test_int);
                    Dataclass.Result_yxchange.Result_describe+=",";
                    Dataclass.Result_yxchange.Result_describe+="值：";
                    test_int = (unsigned char)(test[1]);
                    Dataclass.Result_yxchange.Result_describe+=QString("%1").arg(test_int);
                    Dataclass.Result_yxchange.Result_describe+=" ";
                    describe_data.remove(0,2);
                }

                dataty=14;
            }
            else if((buf[DEV_adr_len+11]==(char)0xF1)&&(buf[DEV_adr_len+12]==(char)0x00)&&(buf[DEV_adr_len+13]==(char)0x03))//ESAM信息
            {
                Dataclass.DEV_ESAMRead=true;

                if(HCS_show==HCS_caculate)//=====
                {
                    Dataclass.Result_ESAM.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_ESAM.Result_HCS="帧校验不正确";
                }
                if(FCS_show==FCS_caculate)//=====
                {
                    Dataclass.Result_ESAM.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_ESAM.Result_FCS="帧校验不正确";
                }
                Dataclass.Result_ESAM.Result_describe="Recieve OK :";
                int item_num=buf[DEV_adr_len+17];//内容报文长度
                QByteArray describe_data=buf.mid(DEV_adr_len+18,buf.size()-(DEV_adr_len+18)-3-2);
                char *buf;
                char tmp[256];
                buf=describe_data.data();
                for(int n=0;n<item_num;n++)
                {
                    ::snprintf(tmp,256, "%02X", (unsigned char)(*buf));
                    buf++;
                    Dataclass.Result_ESAM.Result_describe+=QString::fromUtf8(tmp);
                    Dataclass.Result_ESAM.Result_describe+=" ";
                }
                dataty=17;
            }
        }
        //转发读取电表
        else if(((buf[DEV_adr_len+8]&0x0f)==(char)0x09)&&(buf[DEV_adr_len+9]==(char)0x07))//09 07 00
        {
            if((buf[DEV_adr_len+11]==(char)0xF2)&&(buf[DEV_adr_len+12]==(char)0x01)&&(buf[DEV_adr_len+13]==(char)0x02))//读取电表
            {


                if(HCS_show==HCS_caculate)//=====
                {
                    Dataclass.Result_meterenergy.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_meterenergy.Result_HCS="帧校验不正确";
                }
                if(FCS_show==FCS_caculate)//=====
                {
                    Dataclass.Result_meterenergy.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_meterenergy.Result_FCS="帧校验不正确";
                }
//                Dataclass.Result_meterenergy.Result_HCS="0x00";
//                Dataclass.Result_meterenergy.Result_FCS="0x00";
                Dataclass.Result_meterenergy.Result_describe="Recieve OK :";

                int item_num=buf[DEV_adr_len+16];//转发报文长度
                QByteArray describe_data=buf.mid(DEV_adr_len+17,buf.size()-(DEV_adr_len+17)-3-2);
                char *buf_data;
                char tmp[256];
                buf_data=describe_data.data();
                for(int n=0;n<item_num;n++)
                {
                    ::snprintf(tmp,256, "%02X", (unsigned char)(*buf_data));
                    buf_data++;
                    Dataclass.Result_meterenergy.Result_describe+=QString::fromUtf8(tmp);
                    Dataclass.Result_meterenergy.Result_describe+=" ";
                }

                //char nnn=buf[DEV_adr_len+14];
                if(buf[DEV_adr_len+14]==(char)0x01)
                {
                    Dataclass.DEV_meterenergyRead_4851=true;
                    dataty=15;
                }
                else if(buf[DEV_adr_len+14]==(char)0x02)
                {
                    Dataclass.DEV_meterenergyRead_4852=true;
                    dataty=16;
                }

            }
        }
        //复位+恢复出厂设置
        else if(((buf[DEV_adr_len+8]&0x0f)==(char)0x07)&&(buf[DEV_adr_len+9]==(char)0x01))//87 01 00
        {
            if((buf[DEV_adr_len+11]==(char)0x43)&&(buf[DEV_adr_len+13]==(char)0x01))//硬件复位
            {

            }
            else if((buf[DEV_adr_len+11]==(char)0x43)&&(buf[DEV_adr_len+13]==(char)0x04))//恢复出厂设置
            {

            }
        }

        //GPRS或internet参数设置确认回复
        else if(((buf[DEV_adr_len+8]&0x0f)==(char)0x06)&&(buf[DEV_adr_len+9]==(char)0x01))//86 01 00
        {
            if((buf[DEV_adr_len+11]==(char)0x45)&&buf[DEV_adr_len+12]==(char)0x00)
            {
                if(HCS_show==HCS_caculate)//=====
                {
                    Dataclass.Result_gprsParam.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_gprsParam.Result_HCS="帧校验不正确";
                }
                if(FCS_show==FCS_caculate)//=====
                {
                    Dataclass.Result_gprsParam.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_gprsParam.Result_FCS="帧校验不正确";
                }
                Dataclass.Result_gprsParam.Result_describe="Recieve OK";
                if((buf[DEV_adr_len+13]==(char)0x02))//公网通信模块1确认 属性2
                {
                    Dataclass.DEV_gprsParamset_1=true;
                    Dataclass.Result_gprsParam.Result_describe="Recieve OK :公网通信模块1确认_1";
                    dataty=22;
                }
                else if((buf[DEV_adr_len+13]==(char)0x03))//公网通信模块1确认 属性3
                {
                    Dataclass.DEV_gprsParamset_2=true;
                    Dataclass.Result_gprsParam.Result_describe="Recieve OK :公网通信模块1确认_2";
                    dataty=23;
                    if(Dataclass.TestINFO.step_Selected[10]==true)
                        Dataclass.TestINFO.testSteps_currentLevel=3;//GPRS参数下设结束，进入第三测试阶段
                }
            }
            else if((buf[DEV_adr_len+11]==(char)0x45)&&buf[DEV_adr_len+12]==(char)0x10)
            {
                if(HCS_show==HCS_caculate)//=====
                {
                    Dataclass.Result_internetParam.Result_HCS=QString::number(HCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_internetParam.Result_HCS="帧校验不正确";
                }
                if(FCS_show==FCS_caculate)//=====
                {
                    Dataclass.Result_internetParam.Result_FCS=QString::number(FCS_caculate,16);
                }
                else
                {
                    Dataclass.Result_internetParam.Result_FCS="帧校验不正确";
                }
                Dataclass.Result_internetParam.Result_describe="Recieve OK";

                if((buf[DEV_adr_len+13]==(char)0x02))//以太网通信模块1确认 属性2
                {
                    Dataclass.DEV_internetParamset_1=true;
                    Dataclass.Result_internetParam.Result_describe="Recieve OK :以太网通信模块1确认_1";
                    dataty=18;
                }
                else if((buf[DEV_adr_len+13]==(char)0x03))//以太网通信模块1确认 属性3
                {
                    Dataclass.DEV_internetParamset_2=true;
                    Dataclass.Result_internetParam.Result_describe="Recieve OK :以太网通信模块1确认_2";
                    dataty=19;
                }
                else if((buf[DEV_adr_len+13]==(char)0x04))//以太网通信模块1确认 属性4
                {
                    Dataclass.DEV_internetParamset_3=true;
                    Dataclass.Result_internetParam.Result_describe="Recieve OK :以太网通信模块1确认_3";
                    dataty=20;
                    if(Dataclass.TestINFO.step_Selected[9]==true||Dataclass.TestINFO.step_Selected[8]==true)
                        Dataclass.TestINFO.testSteps_currentLevel=2;//以太网参数参数下设结束，进入第二测试阶段
                }
            }

        }
        //登录帧或心跳帧
        else if((buf[DEV_adr_len+8]&0x0f)==(char)0x01)
        {
            QString loginResult_HCS;
            QString loginResult_FCS;
            QString loginResult_describe;
            if(HCS_show==HCS_caculate)//=====
            {
                loginResult_HCS=QString::number(HCS_caculate,16);
            }
            else
            {
                loginResult_HCS="帧校验不正确";
            }
            if(FCS_show==FCS_caculate)//=====
            {
                loginResult_FCS=QString::number(FCS_caculate,16);
            }
            else
            {
                loginResult_FCS="帧校验不正确";
            }
            loginResult_describe="Recieve OK:登录上线确认";

            Dataclass.Buffer_time.clear();
            for(int n=0;n<10;n++)//存储接收到的登录帧上传时间
            {
                Dataclass.Buffer_time.append(buf[DEV_adr_len+13+n]);
            }

            if((buf[DEV_adr_len+10]&0x0f)==(char)0x00)//登录
            {
                if(Dataclass.TestINFO.testSteps_currentLevel==2)
                {
                    Dataclass.DEV_internetLogin=true;//以太网登录确认
                    dataty=21;
                    Dataclass.TestINFO.testSteps_currentTeststep=12;//登录确认后可以下设GPRS参数

                    Dataclass.Result_internetlogin.Result_HCS=loginResult_HCS;
                    Dataclass.Result_internetlogin.Result_FCS=loginResult_FCS;
                    Dataclass.Result_internetlogin.Result_describe=loginResult_describe;

                }
                else if(Dataclass.TestINFO.testSteps_currentLevel==3)
                {
                    Dataclass.DEV_gprsLogin=true;//GPRS登录确认
                    dataty=24;

                    Dataclass.Result_gprslogin.Result_HCS=loginResult_HCS;
                    Dataclass.Result_gprslogin.Result_FCS=loginResult_FCS;
                    Dataclass.Result_gprslogin.Result_describe=loginResult_describe;

                }
            }
            else if((buf[DEV_adr_len+10]&0x0f)==(char)0x01)//心跳
            {
                dataty=25;//心跳帧
            }
        }
    }
    return dataty;
}
