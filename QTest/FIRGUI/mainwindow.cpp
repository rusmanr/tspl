#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fir.h>
#include <fft.h>

using namespace std;
using namespace splab;


typedef double  Type;
const   int     MINLEN = 1;
const   int     MAXLEN = 1000;
const   int     STEP   = 10;
Vector<double> bfac;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);

    ui->customPlot->setOpenGl(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_designButton_clicked()
{
    string  wType = "Hamming";

    string  fType = "lowpass";
    double  fs = 1000,
            fpass = 200,
            apass = -3,
            fstop = 300,
            astop = -20;
    FIR fir( fType, wType );
    fir.setParams( fs, fpass, apass, fstop, astop );

//    string  fType = "highpass";
//    double  fs = 1000,
//            fstop = 200,
//            astop = -20,
//            fpass = 300,
//            apass = -3;
//    FIR fir( fType, wType );
//    fir.setParams( fs, fstop, astop, fpass, apass );

//    string  fType = "bandpass";
//    double  fs = 1000,
//            fstop1 = 100,
//            astop1 = -20,
//            fpass1 = 200,
//            fpass2 = 300,
//            apass1 = -3,
//            fstop2 = 400,
//            astop2 = -20;
//    FIR fir( fType, wType );
//    fir.setParams( fs, fstop1, astop1, fpass1, fpass2, apass1, fstop2, astop2 );

//    string  fType = "bandstop";
//    double  fs = 1000,
//            fpass1 = 100,
//            apass1 = -3,
//            fstop1 = 200,
//            fstop2 = 300,
//            astop1 = -20,
//            fpass2 = 400,
//            apass2 = -3;
//    FIR fir( fType, wType );
//    fir.setParams( fs, fpass1, apass1, fstop1, fstop2, astop1, fpass2, apass2 );

    fir.design();
    fir.dispInfo();
    bfac = fir.getCoefs();
    for (int i=0; i<bfac.size() ;i++ ) {
        double & BValue = bfac[i];

        ui->textBrowser->append(" element at " + QString::number(i) + " : " + QString::number(bfac[i]));
        ui->textBrowser->append("using pointer " + QString::number(BValue));
        cout << bfac[i] << endl;
        cout << &BValue << endl;
        qDebug() << "debug bfac[i] : " << bfac[i];
        qDebug() << "debug BValue : " << BValue;

    }
//    float y = 0.0;

//      y = y + bfac.at(i)* y0[i];

    cout << endl;

}

void MainWindow::setupSimpleDemo(QCustomPlot *customPlot)
{
  demoName = "Simple Demo";

  // add two new graphs and set their look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  customPlot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
  // generate some points of data (y0 for first, y1 for second graph):
  QVector<double> x(251), y0(251), y1(251), yn(251);
  Vector< complex<Type> >  sn, Rk, Sk, xn;
  Vector<Type> rn, tn;
  //Generate Signal, mixed 2 sine
  for (int i=0; i<251; ++i)
  {
    x[i] = i;
    y0[i] = qSin(2*M_PI*100*i/6000.0)+qSin(2*M_PI*450*i/6000.0);//qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
//    y1[i] = 1.0;//qExp(-i/150.0);              // exponential envelope
  }
  // calculate filter
  for (int i=0; i<251-20; i++){
      yn[i]=0;
      for (int j=0; j < 20; j++)
          yn[i] += y0[i+j] * bfac[j];
  }
  rn.resize(251);
  for (int i=0; i<251; ++i)
  {
       y1[i] = yn[i];
       rn[i] =y1[i];
  }
  // calculate FFT
  //Sk[i].real(); use this to access real part of complex number
  Sk = fftr2c( rn );

  //plot FFT result

  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  customPlot->graph(1)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::on_plotButton_clicked()
{
  setupSimpleDemo(ui->customPlot);
}

void MainWindow::on_FFTButton_clicked()
{
    Vector< complex<Type> >  sn, Rk, Sk, xn;
    Vector<Type> rn, tn;

    cout << "forward transform: complex to complex." << endl;
    cout << "inverse transform: complex to complex." << endl << endl;
    cout << "signal length" << "\t" << "mean(abs((sn-xn))" << endl;
    for( int len=MINLEN; len<MAXLEN; len+=STEP )
    {
        sn.resize(len);
        for( int i=0; i<len; ++i )
            sn[i] = complex<Type>( rand()%10, rand()%10 );

        Sk = fftc2c( sn );
        xn = ifftc2c( Sk );
//        Sk = fft( sn );
//        xn = ifft( Sk );
        cout << "    " << len << "\t\t" << "  " << sum(abs(sn-xn))/len << endl;
    }
    cout << endl << endl;

    cout << "forward transform: real to complex ." << endl;
    cout << "inverse transform: complex to real." << endl << endl;
    cout << "signal length" << "\t" << "mean(abs((rn-tn))" << endl;
    for( int len=MINLEN; len<MAXLEN; len+=STEP )
    {
        rn.resize(len);
        for( int i=0; i<len; ++i )
            rn[i] = rand()%10;

        Rk = fftr2c( rn );
        tn = ifftc2r( Rk );

//        Rk = fft( rn );
//        tn = real( ifft(Rk) );
        cout << "    " << len << "\t\t" << "  " << sum((rn-tn))/len << endl;
    }
    cout << endl;

}
