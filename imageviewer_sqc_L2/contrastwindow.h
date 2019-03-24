#ifndef CONTRASTWINDOW_H
#define CONTRASTWINDOW_H

#include <QDialog>
#include<QDebug>
namespace Ui {
class ContrastWindow;
}

class ContrastWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ContrastWindow(QWidget *parent = nullptr);
    ~ContrastWindow();

public slots:
    void accept();

signals:
    void confirmed(double,double);

private:
    Ui::ContrastWindow *ui;
};

#endif // CONTRASTWINDOW_H
