#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <thread>

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
        std::thread *thr_net;
        QGraphicsRectItem* item1;
        QTimer qtimer;
        QGraphicsSimpleTextItem* track_info_i;
        QGraphicsSimpleTextItem* axels;
        
        udp_crtc *udp_o;
        volatile atomic <uint> track_info;
        volatile atomic <float> axels_count;
        int axels_i = 0;
        char str_tmp [50];
};
#endif // MAINWINDOW_H
