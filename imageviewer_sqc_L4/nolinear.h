#ifndef NOLINEAR_H
#define NOLINEAR_H

#include <QDialog>
#include<QDebug>
namespace Ui {
class Nolinear;
}

class Nolinear : public QDialog
{
    Q_OBJECT

public:
    explicit Nolinear(QWidget *parent = nullptr);
    ~Nolinear();

public slots:
    void accept();

signals:
    void confirmed(int);

private:
    Ui::Nolinear *ui;
};

#endif // NOLINEAR_H
