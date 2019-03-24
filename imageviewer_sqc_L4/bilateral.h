#ifndef BILATERAL_H
#define BILATERAL_H

#include <QDialog>
#include<QDebug>

namespace Ui {
class Bilateral;
}

class Bilateral : public QDialog
{
    Q_OBJECT

public:
    explicit Bilateral(QWidget *parent = nullptr);
    ~Bilateral();

public slots:
    void accept();

signals:
    void confirmed(int,double,double);

private:
    Ui::Bilateral *ui;
};

#endif // BILATERAL_H
