#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


/*
 QApplication app(argc, argv);
 
    QGraphicsScene scene;
    scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );
 
    QGraphicsItem *item = new QGraphicsEllipseItem( -50.0, -50.0, 100.0, 100.0, Q_NULLPTR );
    scene.addItem(item);
 
    QGraphicsView view( &scene );
    view.setRenderHints( QPainter::Antialiasing );
    view.show();
 
    return app.exec();
 */
