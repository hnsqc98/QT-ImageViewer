#include "dlglinearfilter.h"
#include "ui_dlglinearfilter.h"
#include<QRegExp>  //包含正则表达式

using std::vector;

DlgLinearfilter::DlgLinearfilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLinearfilter)
{
    ui->setupUi(this);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(print_s1()));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(QString)),this,SLOT(print_s2()));
}

DlgLinearfilter::~DlgLinearfilter()
{
    delete ui;
}

void DlgLinearfilter::accept()
{
    QString str=ui->textEdit->toPlainText();
    QStringList rows=str.replace("\n","").trimmed().split(";");
    vector<double> data;
    int nCol=-1;
    for (int i=0;i<rows.size();++i)
    {
        if (rows[i].isEmpty()) continue;
        bool ok;
        int tmp;
        ok=parseRow(rows[i],data,tmp);
        if (nCol==-1) nCol=tmp;
        if (!ok||nCol!=tmp)
        {
            close();
            return;
        }
    }
    emit confirmed(data,nCol);
    close();
}

bool DlgLinearfilter::parseRow(QString row,std::vector<double>& data,int& nCol)
{
    nCol=0;
    QStringList cols=row.trimmed().split(QRegExp("\\s+|\\s*,"));  //两个\表示真实的一个
    for (int i=0;i<cols.size();++i)
    {
        if (cols[i].isEmpty()) continue;
        bool ok;
        double d=cols[i].toDouble(&ok);
        if (ok)
        {
            data.push_back(d);
            nCol++;
        }
        else
        {
            return ok;
        }
    }
    return true;
}


void DlgLinearfilter::print_s1()
{
    if(ui->comboBox->currentIndex()==0) ImageProcessor::modeFlag=0;
    else if(ui->comboBox->currentIndex()==1) ImageProcessor::modeFlag=1;
    else if(ui->comboBox->currentIndex()==2) ImageProcessor::modeFlag=2;
}

void DlgLinearfilter::print_s2()
{
    if(ui->comboBox_2->currentIndex()==0) ImageProcessor::colorFlag=0;  //灰度
    if(ui->comboBox_2->currentIndex()==1) ImageProcessor::colorFlag=1;  //彩色
}
