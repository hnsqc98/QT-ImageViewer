#ifndef DLGLINEARFILTER_H
#define DLGLINEARFILTER_H

#include <QDialog>
#include<QDebug>
#include<vector>
#include<QComboBox>
#include<imageprocessor.h>

namespace Ui {
class DlgLinearfilter;
}

class DlgLinearfilter : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLinearfilter(QWidget *parent = nullptr);

    ~DlgLinearfilter();

private:
    Ui::DlgLinearfilter *ui;
    bool parseRow(QString,std::vector<double>&,int&);

signals:
    void confirmed(std::vector<double>,int);

public slots:
    void accept();
    void print_s1();  //comboBox槽函数
    void print_s2();  //comboBox_2槽函数

};

#endif // DLGLINEARFILTER_H
