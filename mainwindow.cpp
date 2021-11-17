#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("EmsTest");
    ui->graphicsView->setScene(&scene);
    scene.setBackgroundBrush(Qt::gray);   
    item1 = new QGraphicsRectItem(50,50,400,25); 	
    scene.addItem(item1);   
    item1->setBrush(QBrush(Qt::blue));
    thr_blinking = new std::thread (&MainWindow::Blinking, this);
 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Blinking()
{
    while (1) {
        item1->setBrush (QBrush(Qt::black));
        usleep (200000);
        item1->setBrush (QBrush(Qt::blue));
        usleep (200000);
    }
}

