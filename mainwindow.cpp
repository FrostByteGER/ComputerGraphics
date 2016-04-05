#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect slider A to change param A in OGLWidget
    connect(ui->sliderA, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setParamA(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
