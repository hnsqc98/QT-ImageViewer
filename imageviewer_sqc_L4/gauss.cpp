#include "gauss.h"
#include "ui_gauss.h"

Gauss::Gauss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gauss)
{
    ui->setupUi(this);
}

Gauss::~Gauss()
{
    delete ui;
}

void Gauss::accept()
{
    qDebug()<<"accept";
    bool ok;
    int s=ui->lineEdit->text().toInt(&ok);
    double xigema=ui->lineEdit_2->text().toDouble(&ok);
    if (ok)
    {
        emit confirmed(s,xigema);
    }
    close();
}
