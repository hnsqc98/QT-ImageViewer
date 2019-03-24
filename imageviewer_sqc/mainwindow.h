#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "mypixmapitem.h"

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
    void reset();


public slots:
    void on_btnopen_clicked();
    void on_btnreset_clicked();
    void on_btnback_clicked();
    void on_btnnext_clicked();
};

#endif // MAINWINDOW_H
