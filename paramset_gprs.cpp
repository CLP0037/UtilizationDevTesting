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

    Dataclass.Testinfo_Set.D_gprsParam="";//GPRS参数配置
    Dataclass.Testinfo_Set.D_gprsParam+="参数1：工作模式-";
    Dataclass.Testinfo_Set.D_gprsParam+=ui->comBox_workmodel->currentText();
    Dataclass.Testinfo_Set.D_gprsParam+=";在线方式-";
    Dataclass.Testinfo_Set.D_gprsParam+=ui->comBox_onlinestyle->currentText();
    Dataclass.Testinfo_Set.D_gprsParam+=";连接方式-";
    Dataclass.Testinfo_Set.D_gprsParam+=ui->comBox_linkstyle->currentText();
    Dataclass.Testinfo_Set.D_gprsParam+=";连接应用方式-";
    Dataclass.Testinfo_Set.D_gprsParam+=ui->comBox_applicationType->currentText();
    Dataclass.Testinfo_Set.D_gprsParam+=";APN-";
    Dataclass.Testinfo_Set.D_gprsParam+= Dataclass.GPRS_Param.APN;
    Dataclass.Testinfo_Set.D_gprsParam+=";用户名-";
    Dataclass.Testinfo_Set.D_gprsParam+=Dataclass.GPRS_Param.userName;
    Dataclass.Testinfo_Set.D_gprsParam+= ";密码-";
    Dataclass.Testinfo_Set.D_gprsParam+= Dataclass.GPRS_Param.password;
    Dataclass.Testinfo_Set.D_gprsParam+= ";   参数2：主站IP-";
    Dataclass.Testinfo_Set.D_gprsParam+= Dataclass.GPRS_Param.IP;
    Dataclass.Testinfo_Set.D_gprsParam+= ";主站端口-";
    Dataclass.Testinfo_Set.D_gprsParam+= ui->lineEdit_sPort_server->text().trimmed();

    accept();
}
