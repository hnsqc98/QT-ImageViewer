#include "dlglog.h"
#include "ui_dlglog.h"
#include<QDebug>

DlgLog::DlgLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLog)
{
    ui->setupUi(this);
}

DlgLog::~DlgLog()
{
    delete ui;
}

void DlgLog::accept()
{
    qDebug()<<"accept";
    bool ok;
    double c=ui->lineEdit->text().toDouble(&ok);
    if (ok)
    {
        emit confirmed(c);
    }
    close();
}
