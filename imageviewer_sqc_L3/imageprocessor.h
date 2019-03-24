#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include<QImage>
#include<cmath>
#include<QVector>
#include<QtGlobal>
#include<QDebug>
#include<QSize>

class ImageProcessor
{
public:
    ImageProcessor();
    static QImage rgb2gray(const QImage& img);
    static QImage inverse(const QImage& img);
    static QImage logTranformation(const QImage& img,double c);
    static QImage contrastTranformation(const QImage& img,double m,double e);
    static QImage histogramEqualization(const QImage& img);
    static QImage histogramColorful(const QImage& img);
    QImage histogramHSI(const QImage& img);
    void RGBtoHSI(double r,double g,double b,double *h,double *s,double *i);
    void HSItoRGB(double h,double s,double i,double *r,double *g,double *b);

    static QImage zeroize(const QImage& img,std::vector<double> data,int nCol); //滤波，补零
    static QImage repeat(const QImage& img,std::vector<double> data,int nCol); //滤波，重复
    static QImage mirror(const QImage& img,std::vector<double> data,int nCol); //滤波，镜像
    static QImage filtercolor(const QImage& img,std::vector<double> data,int nCol); //滤波，重复，rgb
    static QImage mirrorcolor(const QImage& img,std::vector<double> data,int nCol); //滤波，镜像，rgb

    static QImage linearFilter(const QImage&,std::vector<double>,int);

    static int colorFlag;
    static int modeFlag;
};

#endif // IMAGEPROCESSOR_H
