#ifndef PUBLICDATACLASS_H
#define PUBLICDATACLASS_H

#include <QString>

class PublicDataclass
{
public:
    PublicDataclass();



    void set_PortName(const QString num);
    QString get_PortName();

    void set_BaudRate(int baudRate);
    int get_BaudRate();

    void set_DEV_addr(const QString dev_addr);
    QString get_DEV_addr();
    void set_ammeter_addr(const QString am_addr);
    QString get_ammeter_addr();

    void set_IP_server(const QString ip);
    QString get_IP_server();
    void set_Port_server(int port);
    int get_Port_server();

    //
    QByteArray Buffer_rev;
    QByteArray Buffer_send;
    int BufLen_rev;
    int BufLen_send;
    QByteArray buf_rev;//接收缓存====用于分帧处理


    //测试流程标志位
    bool DEV_testprocess;
    //测串口
    bool DEV_testprocess_start;
    bool DEV_versionRead;
    bool DEV_timeRead;
    bool DEV_voltageRead;
    bool DEV_yxchangeRead;
    bool DEV_meterenergyRead_4851;
    bool DEV_meterenergyRead_4852;
    bool DEV_ESAMRead;

    bool DEV_internetParamset_1;
    bool DEV_internetParamset_2;
    bool DEV_internetParamset_3;
    //测网口
    bool DEV_internetLogin;//
    bool DEV_gprsParamset_1;
    bool DEV_gprsParamset_2;
    //测gprs
    bool DEV_gprsLogin;//

    bool DEV_testprocess_end;

    //msg
    QString ShowStr_Msg;
    QString ShowStr_Protocol;

    //sever====登陆帧心跳帧报文上送时间
    QByteArray Buffer_time;


    //测试结果显示
    typedef struct testResult
    {
        QString Result_HCS;//帧头
        QString Result_FCS;//整帧
        QString Result_describe;//结果描述
    }tResult;

    tResult Result_version;       //版本
    tResult Result_time;          //时间
    tResult Result_voltage;       //电压
    tResult Result_yxchange;      //遥信变位
    tResult Result_meterenergy;   //电能量读取转发4851+4852

    tResult Result_ESAM;          //ESAM
    tResult Result_internetParam;//以太网参数1+2+3
//    tResult Result_internetParam2;
//    tResult Result_internetParam3;
    tResult Result_gprsParam;    //gprs参数1+2
//    tResult Result_gprsParam2;

    tResult Result_internetlogin;
    tResult Result_gprslogin;


    //测试相关参数
    typedef struct testInformation
    {
        int testSteps_total;//测试总步骤数：8+2+1=11
        int testSteps_currentLevel;//当前步骤阶段：1阶段==串口通讯；2阶段==网口通讯；3阶段==GPRS通讯
        int testSteps_totalLevel;
        int testSteps_currentTeststep;//当前测试步骤
        bool step_Selected[11];//testSteps_total
        int test_resendtimes;

    }testInfo;
    testInfo TestINFO;

    //GPRS设置参数
    typedef struct gprsParamSet
    {
        //第一步===========
        unsigned char workmodel;//工作模式
        unsigned char onlineType;//在线方式
        unsigned char linkType;//连接方式
        unsigned char applicationType;//连接应用方式
        QString APN;//APN  CMNET
        QString userName;//用户名
        QString password;//密码
        //代理服务器
        //代理端口
        //超时时间及重发次数
        int heartbeatCycle;//心跳周期
        //第二步=========
        QString IP;//主站IP
        int port;//主站端口
    }gprsParam;

    gprsParam GPRS_Param;

    //INTERNET设置参数
    typedef struct internetParamSet
    {
        //第一步===========
        unsigned char workmodel;//工作模式
        unsigned char linkType;//连接方式
        unsigned char applicationType;//连接应用方式
        //超时时间及重发次数
        int heartbeatCycle;//心跳周期
        //第二步===========
        QString IP_server;//主站IP
        int port_server;//主站端口
        //第三步===========
        unsigned char IP_setway;//IP配置方式:DHCP（0），静态（1），PPPoE（2）

        QString IP_dev;//设备IP
        QString IP_subnetmask;//子网掩码
        QString IP_gateway;//网关地址
        int port_dev;//设备端口
    }interParam;

    interParam INTERNET_Param;

private:

    //串口参数
    QString PortName;  //串口号
    int BaudRate;      //波特率

    //网口相关参数(服务器IP和地址)
    QString IP_server;
    int Port_server;

    //设备地址信息
    QString DEV_addr;//终端地址
    QString ammeter_addr;//电表地址


};

#endif // PUBLICDATACLASS_H
