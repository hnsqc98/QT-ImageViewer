#include "imageprocessor.h"

ImageProcessor::ImageProcessor()
{

}

QImage ImageProcessor::rgb2gray(const QImage& img)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            int red=qRed(rgb);
            int green=qGreen(rgb);
            int blue=qBlue(rgb);
            int gray=(red+green+blue)/3.0;
            ret.setPixel(i,j,qRgb(gray,gray,gray));
        }
    }
    return ret;
}

QImage ImageProcessor::inverse(const QImage& img)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            int red=255-qRed(rgb);
            int green=255-qGreen(rgb);
            int blue=255-qBlue(rgb);
            ret.setPixel(i,j,qRgb(red,green,blue));
        }
    }
    return ret;
}


QImage ImageProcessor::logTranformation(const QImage& img,double c)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            int gray=qGray(rgb);
            int newPixel=c*log(1+gray/255.0)*255;
            if (newPixel>=255) newPixel=255;
            ret.setPixel(i,j,qRgb(newPixel,newPixel,newPixel));
        }
    }
    return ret;
}

QImage ImageProcessor::contrastTranformation(const QImage& img,double m,double e)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            int gray=qGray(rgb);
            int newPixel=1/(1+pow(m/gray,e));
            if (newPixel>=255) newPixel=255;
            ret.setPixel(i,j,qRgb(newPixel,newPixel,newPixel));
        }
    }
    return ret;
}

QImage ImageProcessor::histogramEqualization(const QImage& img)
{
    QVector <int> gray(256);
    QVector <double> p(256);
    QVector <double> c(256);
    QVector <int> gnew(256);
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();

    //统计各灰度值出现次数
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            gray[qGray(rgb)]++;
        }
    }

    //计算各灰度值出现频数
    for (int i=0;i<=255;++i)
    {
        p[i]=gray[i]/double(w*h);
        //计算累计分布
        if(i==0)
        {
            c[i]=p[i];
        }
        else
        {
            c[i]=c[i-1]+p[i];
        }
        //得到均衡化之后的值，映射到0~255
        gnew[i]=int(255*c[i]+0.5);
    }
    //将新值赋予图片
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            int newPixel=gnew[qGray(rgb)];
            ret.setPixel(i,j,qRgb(newPixel,newPixel,newPixel));
        }
    }
    return ret;
}

QImage ImageProcessor::histogramColorful(const QImage& img)
{
    QVector <int> red(256),green(256),blue(256);
    QVector <double> pred(256),pgreen(256),pblue(256);
    QVector <double> cred(256),cgreen(256),cblue(256);
    QVector <int> newred(256),newgreen(256),newblue(256);
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            red[qRed(rgb)]++;
            green[qGreen(rgb)]++;
            blue[qBlue(rgb)]++;
        }
    }
    for (int i=0;i<=255;++i)
    {
        pred[i]=red[i]/double(w*h);
        pgreen[i]=green[i]/double(w*h);
        pblue[i]=blue[i]/double(w*h);
        if(i==0)
        {
            cred[i]=pred[i];
            cgreen[i]=pgreen[i];
            cblue[i]=pblue[i];
        }
        else
        {
            cred[i]=cred[i-1]+pred[i];
            cgreen[i]=cgreen[i-1]+pgreen[i];
            cblue[i]=cblue[i-1]+pblue[i];
        }
        newred[i]=int(255*cred[i]+0.5);
        newgreen[i]=int(255*cgreen[i]+0.5);
        newblue[i]=int(255*cblue[i]+0.5);
    }
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            int redPixel=newred[qRed(rgb)];
            int greenPixel=newred[qGreen(rgb)];
            int bluePixel=newred[qBlue(rgb)];
            ret.setPixel(i,j,qRgb(redPixel,greenPixel,bluePixel));
        }
    }
    return ret;
}

void ImageProcessor::RGBtoHSI(double r,double g,double b,double *h,double *s,double *i)
{
    double pi = 3.1415926;
    double temp = sqrt((r-g)*(r-g)+(r-b)*(g-b));
    temp = temp > 0?temp:0.01;
    if(b<=g)
        *h = acos(((r-g+r-b)/2.0)/temp);
    else
        *h = 2*pi - acos(((r-g+r-b)/2.0)/temp);
    temp = r+g+b>0?r+g+b:0.01;
    *s = 1.0-(3.0/temp)*qMin(qMin(r,g),b);
    *i = (r+g+b)/3.0;
}

void ImageProcessor::HSItoRGB(double h,double s,double i,double *r,double *g,double *b)
{
    double pi = 3.1415926;
    double otz =2*pi / 3.0;
    if(h >=0 && h < otz)
    {
        *b = i*(1.0-s);
        *r = i*(1.0+(s*cos(h))/(cos(pi/3.0-h)));
        *g = 3.0*i-(*b+*r);
    }
    else if(h >= otz && h < 2 * otz)
    {
        *r = i*(1-s);
        *g = i*(1+(s*cos(h-otz))/(cos(pi -h)));
        *b = 3*i-(*g+*r);
    }
    else
    {
        *g = i*(1-s);
        *b = i*(1+(s*cos(h-otz*2))/(cos(5*pi/6-h)));
        *r = 3*i-(*g+*b);
    }
}


QImage ImageProcessor::histogramHSI(const QImage& img)
{

    QImage ret(img);
    int w=ret.width();
    int h=ret.height();

    //申请空间,创建二维数组
    double** ph = new double*[w];
    for(int i=0;i<w;i++)
        ph[i] = new double[h];

    double** ps = new double*[w];
    for(int i=0;i<w;i++)
        ps[i] = new double[h];

    double** pi = new double*[w];
    for(int i=0;i<w;i++)
        pi[i] = new double[h];

    //RGB2HSI
    double max = 0;
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=img.pixel(i,j);
            RGBtoHSI(qRed(rgb),qGreen(rgb),qBlue(rgb),&ph[i][j],&ps[i][j],&pi[i][j]);
            max = max > pi[i][j]?max:pi[i][j];
        }
    }

        //对分量I进行直方图均衡
    int n = (int)(max+0.5);
    int *II = new int[n+1];
    double *IIPro = new double[n+1];
    double *IITemp = new double[n+1];
    double *IIJun = new double[n+1];

    for(int i = 0;i <= n;i++)
        II[i] = 0;

        //计算频率，即nk
    for(int i = 0;i < w;i++)
    {
        for(int j = 0;j < h;j ++)
        {
            II[(int)(pi[i][j]+0.5)]++;
        }
    }

        //计算每个数量级出现的概率
    for(int i = 0;i <= n;i++)
    {
        IIPro[i] = (II[i]*1.0)/(w*h);
    }

        //概率累加并计算均值
    IITemp[0] = IIPro[0];
    for(int i = 1;i <= n;i++)
    {
        IITemp[i] = IITemp[i-1]+IIPro[i];
        IIJun[i]= n*IITemp[i];
    }

    for(int i = 0;i < w;i++)
    {
        for(int j = 0;j < h;j ++)
        {
            pi[i][j] = IIJun[(int)(pi[i][j]+0.5)];
            double r,g,b;
            HSItoRGB(ph[i][j],ps[i][j],pi[i][j],&r,&g,&b);
            r = r > 255?255:(int)(r+0.5);
            g = g > 255?255:(int)(g+0.5);
            b = b > 255?255:(int)(b+0.5);
            ret.setPixel(i,j,qRgb(r,g,b));
        }
    }
    return ret;
}


