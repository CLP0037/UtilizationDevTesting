#ifndef PARAMCONFIG_H
#define PARAMCONFIG_H

#include <QDialog>
#include "publicdataclass.h"

namespace Ui {
class Paramconfig;
}

class Paramconfig : public QDialog
{
    Q_OBJECT

public:
    explicit Paramconfig(QWidget *parent = 0);
    ~Paramconfig();
    void ui_init(void);


    //PublicDataclass Dataclass;








private slots:
    void on_pushBtn_OK_clicked();

private:
    Ui::Paramconfig *ui;
};

#endif // PARAMCONFIG_H
