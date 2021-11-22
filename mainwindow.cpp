#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

#include <QGraphicsItem>
#include <QString>
#include <string.h>
#include "lan.h"

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
    
    track_info_i = new QGraphicsSimpleTextItem ("0");
    track_info_i->setPos(300,80);    
    scene.addItem(track_info_i);   
    
    channels_name  = new QGraphicsSimpleTextItem ("0");
    channels_name->setPos(200,120);
    scene.addItem(channels_name);   
    
      connect(&qtimer, SIGNAL (timeout()), this, SLOT (Blinking()));
    qtimer.start (200);
    udp_o = new Multicast (14350, true, "224.1.1.1");
    track_info = 0x0000;
    axels_count = 0.0;
    pthread_mutex_init (&mutex, NULL);
    thr_net = new std::thread (&MainWindow::ReceivePacket, this);
 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReceivePacket(void)
{
    unsigned char buff_in [2000];
    PacketTS *ts = (PacketTS*)(buff_in + 42); 
    while (1) {         
        memset (buff_in, 0x00, 2000);
        int size = udp_o->GetPacket((char*)buff_in, 2000000);
        if (size) {
            if (ts->key == 1) {// key
                pthread_mutex_lock(&mutex);            
                channel_name = ts->name;
                pthread_mutex_unlock(&mutex);            
                if (strcmp (ts->name, "Frauscher_TS") == 0) {
                    int index_first = sizeof (PacketHead) + strlen (ts->name) + 1 + 2 + 2;
                    track_info = *((uint *)(buff_in + index_first));                         
                }            
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
    pthread_mutex_lock(&mutex);            
    channels_name ->setText(channel_name.c_str());
    pthread_mutex_unlock(&mutex);            
}


void MainWindow::on_pushButton_clicked()
{
    item1->setBrush (QBrush(Qt::green));    
    axels_i++;     
    axels->setText(QString::number(axels_i));          
    //track_info_i->setText(str_tmp);     
    track_info_i->setText(QString::number(track_info));
    
     
}

