#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

using std::vector;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fd(new QFileDialog(this)),
    scene(nullptr),pitem(nullptr),
    dlgLinear(new DlgLinearfilter(this)),
    dlgLog(new DlgLog(this)),
    contrastwindow(new ContrastWindow(this))

{
    fd->setNameFilter("Image(*.bmp *.png *.jpg *.gif *.jpeg)");
    fd->setFileMode(QFileDialog::ExistingFile);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete fd;
    delete pitem;
    delete scene;
    delete ui;
    delete dlgLog;
    delete contrastwindow;
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
        filters<<"*.bmp"<<"*.jpg"<<"*.png"<<"*.gif"<<"*.jpeg";
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
    QImage image(imgs[idx].absoluteFilePath());
    showImage(image);
}

void MainWindow::showImage(QImage img)
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
    pitem->setPixmap(QPixmap::fromImage(img));
    scene->addItem(pitem);
    ui->graphicsView->setScene(scene);

    reset();
}


void MainWindow::on_actionrgb2gray_triggered()
{
    qDebug()<<"rgb2gray";
    //读取照片
    if(!pitem) return;
    QImage image=getCurrentImage();

    //rgb2gray
    image=ImageProcessor::rgb2gray(image);
    //show image
    showImage(image);
}

void MainWindow::on_actionlog_triggered()
 {
     qDebug()<<"log";
     dlgLog->exec();
 }

void MainWindow::on_actioninverse_triggered()
 {
     qDebug()<<"inverse";
     //读取照片
     if(!pitem) return;
     QImage image=getCurrentImage();

     //inverse
     image=ImageProcessor::inverse(image);
     //show image
     showImage(image);
 }

void MainWindow::on_actioncontrast_triggered()
{
    qDebug()<<"contrast";
    contrastwindow->exec();
}

void MainWindow::on_actionhistogram_triggered()
{
    qDebug()<<"histogram";
    //读取照片
    if(!pitem) return;
    QImage image=getCurrentImage();

    //histogramEqualization
    image=ImageProcessor::histogramEqualization(image);
    //show image
    showImage(image);
}

void MainWindow::on_actionhistogramC_triggered()
{
    qDebug()<<"histogramColorful";
    //读取照片
    if(!pitem) return;
    QImage image=getCurrentImage();

    //histogramEqualization_colorful
    image=ImageProcessor::histogramColorful(image);
    //show image
    showImage(image);
}

void MainWindow::on_actionhistogramHSI_triggered()
{
    qDebug()<<"histogramHSI";
    //读取照片
    if(!pitem) return;
    QImage image=getCurrentImage();

    //histogramEqualization_HSI
    ImageProcessor F;
    image=F.histogramHSI(image);
    //show image
    showImage(image);
}

void MainWindow::on_DlgLog_confirmed(double c)
 {
     qDebug()<<c;
     //读取照片
     if(!pitem) return;
     QImage image=getCurrentImage();

     image=ImageProcessor::logTranformation(image,c);
     //show image
     showImage(image);
 }

void MainWindow::on_ContrastWindow_confirmed(double m,double e)
 {
     qDebug()<<m;
     qDebug()<<e;
     //读取照片
     if(!pitem) return;
     QImage image=getCurrentImage();

     image=ImageProcessor::logTranformation(image,m);
     //show image
     showImage(image);
 }

QImage MainWindow::getCurrentImage() const
{
    QList<QGraphicsItem*> items=ui->graphicsView->scene()->items();
    QGraphicsPixmapItem* item=(QGraphicsPixmapItem*) items.at(0);
    QImage image=item->pixmap().toImage();
    return image;
}



void MainWindow::on_actionLinear_triggered()
{
    qDebug()<<"log";
    dlgLinear->exec();

}


void MainWindow::on_DlgLinearfilter_confirmed(vector<double> data,int nCol)
{
    qDebug()<<nCol;
    QImage img=getCurrentImage();
    //归一化
    normalizeKernal(data);
    img=ImageProcessor::linearFilter(img,data,nCol);
    showImage(img);
}

void MainWindow::normalizeKernal(vector<double>& data)
{
    double sum=0;
    for (int i=0;i<data.size();++i)
        sum+=data[i];
    if (sum==0||sum==1) return;
    for (int i=0;i<data.size();++i)
    {
        data[i]=data[i]/sum;
    }

}
