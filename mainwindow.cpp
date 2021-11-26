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
    /*
    item1 = new QGraphicsRectItem(50,50,400,25); 	
    //item1 = new QGraphicsRectItem(-100,-100,400,25); 	
    scene.addItem(item1);   
    item1->setBrush(QBrush(Qt::blue));
    */
    item1ems = new ItemEms (); 	
    item1ems->setRect(50,50,400,25);
    scene.addItem(item1ems);   
    item1ems->setBrush(QBrush(Qt::blue));
    udp_o = new Multicast (14350, true, "224.1.1.1");
    item1ems->SetMcastTuObj(udp_o);
    
    axels = new QGraphicsSimpleTextItem ("0");
    axels->setPos(50,80);
    scene.addItem(axels);   
    
    fse_errors = new QGraphicsSimpleTextItem ("0");
    fse_errors->setPos(50,110);
    scene.addItem(fse_errors);   
    
    
    track_info_i = new QGraphicsSimpleTextItem ("0");
    track_info_i->setPos(50,140);    
    scene.addItem(track_info_i);   
    
    channels_name  = new QGraphicsSimpleTextItem ("0");
    channels_name->setPos(50,170);
    scene.addItem(channels_name);   
    
      connect(&qtimer, SIGNAL (timeout()), this, SLOT (Blinking()));
    qtimer.start (100);
    
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
                channel_name_q.push(ts->name);
                pthread_mutex_unlock(&mutex);            
                if (strcmp (ts->name, "Frauscher_TS") == 0) {
                    int index_first = sizeof (PacketHead) + 1 + strlen (ts->name) + 1 + 2 + 2;
                    track_info = *((uint *)(buff_in + index_first));                         
                }            
                if (strcmp (ts->name, "Frauscher_TS_TI") == 0) {
                    int index_first = sizeof (PacketHead) + 1 + strlen (ts->name) + 1 + 2 + 2;                    
                    memcpy ((void *)&axels_count, buff_in + index_first, 4);                    
                    memcpy ((void *)&fse_com_errors, buff_in + index_first + 4, 4);                    
                }            
            } 
        } 
    }
}

void MainWindow::Blinking()
{   
    if ((track_info&0x000000c0) == 0x00000080) 
        item1ems->setBrush (QBrush(Qt::black));
    else 
        item1ems->setBrush (QBrush(Qt::blue));
 
    pthread_mutex_lock(&mutex);            
    if (!channel_name_q.empty()) {
         channels_name ->setText(channel_name_q.front().c_str());    
         channel_name_q.pop();
         //QString q_tmp = QString::number(channel_name_q.size());
         //axels->setText(QString::number(channel_name_q.size()));          
         //axels->setText(QString().number(channel_name_q.size()));         
         axels->setText(QString("axels: %1").arg((uint)axels_count,0,10));          
         fse_errors->setText(QString("fse errors: %1").arg((uint)fse_com_errors,0,10));          
         track_info_i->setText(QString("track states: 0x%1").arg(track_info,4,16));
       }
    else {
          channels_name->setText("queue is empty");
    }     
    
    pthread_mutex_unlock(&mutex);            
}


void MainWindow::on_pushButton_clicked()
{
    item1ems->setBrush (QBrush(Qt::green));             
}

