#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_designButton_clicked();

    void on_plotButton_clicked();

    void on_FFTButton_clicked();

private:
    Ui::MainWindow *ui;
    void setupSimpleDemo(QCustomPlot *customPlot);
    QString demoName;

};

#endif // MAINWINDOW_H
