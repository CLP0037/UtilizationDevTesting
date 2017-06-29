#ifndef PARAMSET_GPRS_H
#define PARAMSET_GPRS_H

#include <QDialog>
#include "publicdataclass.h"

namespace Ui {
class Paramset_gprs;
}

class Paramset_gprs : public QDialog
{
    Q_OBJECT

public:
    explicit Paramset_gprs(QWidget *parent = 0);
    ~Paramset_gprs();

private slots:
    void on_pushBtn_OK_clicked();

private:
    Ui::Paramset_gprs *ui;
};

#endif // PARAMSET_GPRS_H
