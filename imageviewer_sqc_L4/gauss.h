#ifndef GAUSS_H
#define GAUSS_H

#include <QDialog>
#include<QDebug>

namespace Ui {
class Gauss;
}

class Gauss : public QDialog
{
    Q_OBJECT

public:
    explicit Gauss(QWidget *parent = nullptr);
    ~Gauss();

public slots:
    void accept();

signals:
    void confirmed(int,double);

private:
    Ui::Gauss *ui;
};

#endif // GAUSS_H
