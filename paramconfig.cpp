#include "paramconfig.h"
#include "ui_paramconfig.h"
#include "mythread.h"
#include "publicdataclass.h"

#include <QtCore/QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

PublicDataclass Dataclass;
Paramconfig::Paramconfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Paramconfig)
{
    ui->setupUi(this);//初始化当前设备可用串口

    this->ui_init();
}

Paramconfig::~Paramconfig()
{
    delete ui;
}

void Paramconfig::on_pushBtn_OK_clicked()//确定====更新串口网口连接参数
{
//    PublicDataclass *Data;
//    Data = new PublicDataclass();
    //串口相关参数赋值
    Dataclass.set_PortName(ui->comboBox->currentText());
    Dataclass.set_BaudRate(ui->comboBox_Boundrate->currentText().trimmed().toInt());

    //网口相关参数赋值
    Dataclass.set_IP_server(ui->lineEdit_sIP->text());
    Dataclass.set_Port_server(ui->lineEdit_sPort->text().trimmed().toInt());

    accept();
}

void Paramconfig::ui_init(void)
{
    // Example use QSerialPortInfo

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        // Example use QSerialPort
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
           ui->comboBox->addItem(info.portName());
            serial.close();
        }
    }

    //ui->lineEdit_sIP->setDisabled(true);
}
