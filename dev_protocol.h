#ifndef DEV_PROTOCOL_H
#define DEV_PROTOCOL_H

#include <QString>



class DEV_protocol
{
public:
    DEV_protocol();

    int Encode(QByteArray &buf,int dataty,QString DEV_adr,QString ammeter_adr);//报文组包
    int Decode(QByteArray buf);//报文解包

    int Get_C_from_dataty(int dataty);//控制域获取
    void Get_A_from_dataty(int dataty);//地址域获取
    void Get_APDU_from_dataty(int dataty);//链路用户数据组包

    unsigned short Get_HCS(QByteArray buf,int start,int len);//帧头校验
    unsigned short Get_FCS(QByteArray buf,int start,int len);//帧校验

    int Get_CS(QByteArray buf,int start,int len);//累加校验和

    int GET_weekint(QString week);



private:
    int C;//控制域
    int A;//地址域

};

#endif // DEV_PROTOCOL_H
