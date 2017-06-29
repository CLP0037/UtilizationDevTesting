#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);//对于输入的密码显示成小黑点的样式
}

logindialog::~logindialog()
{
    delete ui;
}

void logindialog::on_loginBtn_clicked()//登录
{
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    if(ui->usrLineEdit->text().trimmed() == tr("admin") &&
           ui->pwdLineEdit->text() == tr("123456"))
    {
       accept();
    } else {
       QMessageBox::warning(this, tr("Waring"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
       // 清空内容并定位光标到输入用户名
      ui->usrLineEdit->clear();
      ui->pwdLineEdit->clear();
      ui->usrLineEdit->setFocus();
    }
}
