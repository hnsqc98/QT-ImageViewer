#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "mypixmapitem.h"
#include"imageprocessor.h"
#include"dlglog.h"
#include"contrastwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileDialog *fd;
    QGraphicsScene *scene;
   // QGraphicsPixmapItem *pitem;
    MyPixmapItem *pitem;
    QFileInfoList imgs;
    int idx;
    void showImage();
    void showImage(QImage img);
    void reset();
    QImage getCurrentImage() const; //函数对于类是常量的，不能改变任何类的成员变量

    DlgLog *dlgLog;
    ContrastWindow *contrastwindow;

public slots:
    void on_btnopen_clicked();
    void on_btnreset_clicked();
    void on_btnback_clicked();
    void on_btnnext_clicked();
    void on_actionrgb2gray_triggered();
    void on_actionlog_triggered();
    void on_actioncontrast_triggered();
    void on_actioninverse_triggered();
    void on_actionhistogram_triggered();
    void on_actionhistogramC_triggered();
    void on_actionhistogramHSI_triggered();
    void on_DlgLog_confirmed(double);
    void on_ContrastWindow_confirmed(double,double);
};

#endif // MAINWINDOW_H
