#include "paramset_internet.h"
#include "ui_paramset_internet.h"

extern PublicDataclass Dataclass;

Paramset_internet::Paramset_internet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paramset_internet)
{
    ui->setupUi(this);
}

Paramset_internet::~Paramset_internet()
{
    delete ui;
}

void Paramset_internet::on_pushBtn_OK_clicked()//internet以太网参数配置确认
{
    //
    Dataclass.INTERNET_Param.workmodel=ui->comBox_workmodel->currentIndex();
    Dataclass.INTERNET_Param.linkType=ui->comBox_linkstyle->currentIndex();
    Dataclass.INTERNET_Param.applicationType=ui->comBox_applicationType->currentIndex();
    Dataclass.INTERNET_Param.heartbeatCycle=ui->lineEdit_heartbeat->text().trimmed().toInt();
    //
    Dataclass.INTERNET_Param.IP_server=ui->lineEdit_sIP_server->text().trimmed();
    Dataclass.INTERNET_Param.port_server=ui->lineEdit_sPort_server->text().trimmed().toInt();
    //
    Dataclass.INTERNET_Param.IP_setway=ui->comBox_IP_setway->currentIndex();
    Dataclass.INTERNET_Param.IP_dev=ui->lineEdit_sIP_dev->text().trimmed();
    Dataclass.INTERNET_Param.IP_subnetmask=ui->lineEdit_sIP_subnetmask->text().trimmed();
    Dataclass.INTERNET_Param.IP_gateway=ui->lineEdit_sPort_gateway->text().trimmed();

//    //========================//
//    QByteArray buf;
//    QStringList strList=Dataclass.INTERNET_Param.IP_subnetmask.split(".",QString::SkipEmptyParts);
//    bool ok;
//    int aa;
//    for(int n=0;n<strList.size();n++)
//    {
//        aa=strList[n].toInt(&ok,10);
//        buf.append(aa);
//    }
//    //=======================//

    accept();
}
