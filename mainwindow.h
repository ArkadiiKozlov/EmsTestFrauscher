#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <thread>
#include <queue>
#include "itemems.h"
#include "udp-s.h"


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT
        
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private:
             void ReceivePacket (void);           
    private slots:        
        void Blinking ();
        void on_pushButton_clicked();        
        
    private:
        Ui::MainWindow *ui;
        QGraphicsScene scene;
        QGraphicsScene scene2;
        std::thread *thr_net;
        QGraphicsRectItem* item1;
        ItemEms *item1ems;
        QTimer qtimer;
        QGraphicsSimpleTextItem* axels;
        QGraphicsSimpleTextItem* fse_errors;
        QGraphicsSimpleTextItem* track_info_i;        
        QGraphicsSimpleTextItem* channels_name;
        udp_crtc *udp_o;
        atomic <uint> track_info;
        atomic <float> axels_count;        
        atomic <float> fse_com_errors;                
        pthread_mutex_t mutex;
        queue <string> channel_name_q;        
        
};
#endif // MAINWINDOW_H
