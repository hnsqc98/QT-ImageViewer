#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include<QImage>
#include<cmath>
#include<QVector>
#include<QtGlobal>
#include<QDebug>

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

};

#endif // IMAGEPROCESSOR_H
