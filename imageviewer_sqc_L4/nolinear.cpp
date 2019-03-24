#include "nolinear.h"
#include "ui_nolinear.h"

Nolinear::Nolinear(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nolinear)
{
    ui->setupUi(this);
}

Nolinear::~Nolinear()
{
    delete ui;
}

void Nolinear::accept()
{
    qDebug()<<"accept";
    bool ok;
    int s=ui->lineEdit->text().toInt(&ok);
    if (ok)
    {
        emit confirmed(s);
    }
    close();
}
