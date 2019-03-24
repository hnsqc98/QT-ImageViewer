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
#include"dlglinearfilter.h"
#include"gauss.h"
#include"bilateral.h"
#include"nolinear.h"

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
    DlgLinearfilter *dlgLinear;

    int idx;
    void showImage();
    void showImage(QImage img);
    void reset();
    void normalizeKernal(std::vector<double>&);
    QImage getCurrentImage() const; //函数对于类是常量的，不能改变任何类的成员变量

    DlgLog *dlgLog;
    ContrastWindow *contrastwindow;
    Gauss *gauss;
    Bilateral *bilateral;
    Nolinear *nolinear;




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
    void on_actionGauss_triggered();
    void on_actionBilateral_triggered();
    void on_DlgLog_confirmed(double);
    void on_ContrastWindow_confirmed(double,double);
    void on_Gauss_confirmed(int,double);
    void on_Bilateral_confirmed(int,double,double);
    void on_Nolinear_confirmed(int);

    void on_actionLinear_triggered();
    void on_DlgLinearfilter_confirmed(std::vector<double>,int);

    void on_actionmedian_triggered();
    void on_actioncorrosion_triggered();
    void on_actionswell_triggered();
};

#endif // MAINWINDOW_H
