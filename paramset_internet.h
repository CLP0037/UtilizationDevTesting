#ifndef PARAMSET_INTERNET_H
#define PARAMSET_INTERNET_H

#include <QDialog>
#include "publicdataclass.h"

namespace Ui {
class Paramset_internet;
}

class Paramset_internet : public QDialog
{
    Q_OBJECT

public:
    explicit Paramset_internet(QWidget *parent = 0);
    ~Paramset_internet();

private slots:
    void on_pushBtn_OK_clicked();

private:
    Ui::Paramset_internet *ui;
};

#endif // PARAMSET_INTERNET_H
