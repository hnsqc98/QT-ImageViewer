#include "bilateral.h"
#include "ui_bilateral.h"

Bilateral::Bilateral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bilateral)
{
    ui->setupUi(this);
}

Bilateral::~Bilateral()
{
    delete ui;
}

void Bilateral::accept()
{
    qDebug()<<"accept";
    bool ok;
    int s=ui->lineEdit->text().toInt(&ok);
    double xigemas=ui->lineEdit_2->text().toDouble(&ok);
    double xigemac=ui->lineEdit_3->text().toDouble(&ok);
    if (ok)
    {
        emit confirmed(s,xigemas,xigemac);
    }
    close();
}
