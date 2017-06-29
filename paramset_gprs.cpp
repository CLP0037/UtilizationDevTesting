#include "paramset_gprs.h"
#include "ui_paramset_gprs.h"

extern PublicDataclass Dataclass;

Paramset_gprs::Paramset_gprs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paramset_gprs)
{
    ui->setupUi(this);
}

Paramset_gprs::~Paramset_gprs()
{
    delete ui;
}

void Paramset_gprs::on_pushBtn_OK_clicked()//GPRS参数配置确认
{

    Dataclass.GPRS_Param.workmodel=ui->comBox_workmodel->currentIndex();//工作模式
    Dataclass.GPRS_Param.onlineType=ui->comBox_onlinestyle->currentIndex();//在线方式
    Dataclass.GPRS_Param.linkType=ui->comBox_linkstyle->currentIndex();//连接方式
    Dataclass.GPRS_Param.applicationType=ui->comBox_applicationType->currentIndex();//连接应用方式
    Dataclass.GPRS_Param.APN=ui->lineEdit_APN->text().trimmed();//APN  CMNET
    Dataclass.GPRS_Param.userName=ui->lineEdit_user->text().trimmed();//用户名
    Dataclass.GPRS_Param.password=ui->lineEdit_password->text().trimmed();//密码
    Dataclass.GPRS_Param.heartbeatCycle=ui->lineEdit_heartbeat->text().trimmed().toInt();//心跳周期

    Dataclass.GPRS_Param.IP=ui->lineEdit_IP_server->text().trimmed();
    Dataclass.GPRS_Param.port=ui->lineEdit_sPort_server->text().trimmed().toInt();

    accept();
}
