#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

#include <QGraphicsItem>
#include <QString>
#include <string.h>

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
    track_info_i = new QGraphicsSimpleTextItem ("0");
    track_info_i->setPos(300,80);
    scene.addItem(axels);   
    scene.addItem(track_info_i);   
    connect(&qtimer, SIGNAL (timeout()), this, SLOT (Blinking()));
    qtimer.start (200);
    udp_o = new Multicast (14350, true, "224.1.1.1");
    track_info = 0x0000;
    axels_count = 0.0;
    thr_net = new std::thread (&MainWindow::ReceivePacket, this);
 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReceivePacket(void)
{

 unsigned char buff_in [2000];
 
 while (int size = udp_o->GetPacket((char*)buff_in, 2000000)) {         
        if (buff_in[42] == 1) {// key
            if (strcmp ((char *)(buff_in+43), "Frauscher_TS") == 0) {
                int index_first = 43 + strlen ((char *)(buff_in + 43)) + 1 + 2 + 2;
                track_info = *((uint *)(buff_in + index_first));     
                
                // memcpy (str_tmp, buff_in+43, 20);
               }            
           } 
 } 
 
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
     axels_i++;     
     axels->setText(QString::number(axels_i));          
     //track_info_i->setText(str_tmp);     
     track_info_i->setText(QString::number(track_info));     
     
}

