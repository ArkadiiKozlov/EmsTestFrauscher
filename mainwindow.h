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
        
    private slots:        
        void Blinking ();
        void on_pushButton_clicked();        
        
    private:
        Ui::MainWindow *ui;
        QGraphicsScene scene;
        //std::thread *thr_blinking;
        QGraphicsRectItem* item1;
        QTimer qtimer;
        QGraphicsSimpleTextItem* axels;
        
};
#endif // MAINWINDOW_H
