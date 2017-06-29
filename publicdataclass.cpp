#include "publicdataclass.h"

PublicDataclass::PublicDataclass()
{



}

//PortName
void PublicDataclass::set_PortName(const QString num)
{
     this->PortName=num;
}
QString PublicDataclass::get_PortName()
{
     return this->PortName;
}
//BaudRate
void PublicDataclass::set_BaudRate(int baudRate)
{
     this->BaudRate=baudRate;
}
int PublicDataclass::get_BaudRate()//int baudRate
{
    return this->BaudRate;
}

//网口相关参数(服务器IP和地址)
//QString IP_server;
//int Port_server;
void PublicDataclass::set_IP_server(const QString ip)
{
    this->IP_server=ip;
}
QString PublicDataclass::get_IP_server()
{
     return this->IP_server;
}

void PublicDataclass::set_Port_server(int port)
{
    this->Port_server=port;
}
int PublicDataclass::get_Port_server()
{
    return this->Port_server;
}


//设备地址信息
//QString DEV_addr;//终端地址
//QString ammeter_addr;//电表地址
void PublicDataclass::set_DEV_addr(const QString dev_addr)
{
    this->DEV_addr=dev_addr;
}
QString PublicDataclass::get_DEV_addr()
{
    return this->DEV_addr;
}

void PublicDataclass::set_ammeter_addr(const QString am_addr)
{
    this->ammeter_addr=am_addr;
}
QString PublicDataclass::get_ammeter_addr()
{
    return this->ammeter_addr;
}
