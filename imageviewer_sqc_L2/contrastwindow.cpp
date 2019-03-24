#include "contrastwindow.h"
#include "ui_contrastwindow.h"

ContrastWindow::ContrastWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastWindow)
{
    ui->setupUi(this);
}

ContrastWindow::~ContrastWindow()
{
    delete ui;
}

void ContrastWindow::accept()
{
    qDebug()<<"accept";
    bool ok;
    double m=ui->lineEdit->text().toDouble(&ok);
    double e=ui->lineEdit_2->text().toDouble(&ok);
    if (ok)
    {
        emit confirmed(m,e);
    }
    close();
}
