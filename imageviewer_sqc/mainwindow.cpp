#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fd(new QFileDialog(this)),
    scene(nullptr),pitem(nullptr)
{
    fd->setNameFilter("Image(*.bmp *.png *.jpg *.gif)");
    fd->setFileMode(QFileDialog::ExistingFile);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete fd;
    delete pitem;
    delete scene;
    delete ui;
}

void MainWindow::on_btnopen_clicked()
{
    qDebug()<<"clicked";
    if(fd->exec())
    {
        QStringList files=fd->selectedFiles();
        qDebug()<<files[0];

        QDir dir=fd->directory();
        QStringList filters;
        filters<<"*.bmp"<<"*.jpg"<<"*.png";
        imgs=dir.entryInfoList(filters);
        for (int i=0;i<imgs.size();++i)
        {
            if(imgs[i].absoluteFilePath()==files[0])
            {
                idx=i;
                break;
            }
        }
        showImage();
    }
}


void MainWindow::reset()
{
    qDebug()<<"clicked";
    pitem->reset();
    QRectF rect=pitem->boundingRect();
    scene->setSceneRect(rect);
    ui->graphicsView->fitInView(pitem,Qt::KeepAspectRatio);
    ui->graphicsView->centerOn(pitem);
}

void MainWindow::on_btnreset_clicked()
{
    reset();
}


void MainWindow::on_btnback_clicked()
{
    if (idx==0) idx=imgs.size();
    idx--;
    showImage();
}

void MainWindow::on_btnnext_clicked()
{
    if (idx==imgs.size()-1) idx=-1;
    idx++;
    showImage();
}


void MainWindow::showImage()
{
    if(pitem)
    {
        delete pitem;
        pitem=nullptr;
    }
    if (scene)
    {
        delete scene;
        scene=nullptr;
    }
    scene=new QGraphicsScene(this);
    QImage image(imgs[idx].absoluteFilePath());
    pitem =new MyPixmapItem();
    pitem->setPixmap(QPixmap::fromImage(image));
    scene->addItem(pitem);
    ui->graphicsView->setScene(scene);
    reset();
}
