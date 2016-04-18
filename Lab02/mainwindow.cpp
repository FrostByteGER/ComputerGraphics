#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->RotationSlider, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setParamB(int)));
    connect(ui->RotationSlider, SIGNAL(valueChanged(int)), this, SLOT(setText(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setText(const int& i){
    ui->RotationLabel->setText("Rotation: " + QString::number(i) + "°");
}
