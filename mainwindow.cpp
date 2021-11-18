#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

#include <QGraphicsItem>
#include <QString>

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
    axels = new QGraphicsSimpleTextItem ("0");
    axels->setPos(250,80);
    scene.addItem(axels);   
    connect(&qtimer, SIGNAL (timeout()), this, SLOT (Blinking()));
    qtimer.start (200);
    //thr_blinking = new std::thread (&MainWindow::Blinking, this);
 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Blinking()
{
    static bool f = false;
    if (f) {
        item1->setBrush (QBrush(Qt::black));
        f = false;
    }
    else {
        item1->setBrush (QBrush(Qt::blue));
        f = true;        
    }
}


void MainWindow::on_pushButton_clicked()
{
     item1->setBrush (QBrush(Qt::green));
     static int axels_i = 0;
     axels_i++;     
     axels->setText(QString::number(axels_i));     
     
}

