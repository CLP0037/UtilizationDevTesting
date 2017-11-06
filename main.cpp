#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include <QString>
class ex{
public:
    int a;
    int b;


};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    //return a.exec();
    logindialog dlg;


    QVector<ex> ex_vec;
    ex ex_1;
    ex_1.a=1;
    ex_1.b=2;
    ex ex_2;
    ex_2.a=4;
    ex_2.b=3;
    ex_vec.push_back(ex_1);
    ex_vec.push_back(ex_2);






    if(dlg.exec() == QDialog::Accepted)  // 利用Accepted返回值判断按钮是否被按下
    {
        w.show();                        // 如果被按下，显示主窗口
        return a.exec();                 // 程序一直执行，直到主窗口关闭
    }
    else return 0;                       //如果没被按下，则不会进入主窗口，整个程序结束运行
}
