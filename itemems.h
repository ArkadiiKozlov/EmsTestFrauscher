#ifndef ITEMEMS_H
#define ITEMEMS_H

#include <QGraphicsRectItem>
#include <QtGui>
#include "udp-s.h"
#include "lan.h"

class ItemEms : public QGraphicsRectItem
{
    private: 
    udp_crtc * udp_;
    unsigned char buff_out[1500];
    packetTU *p_tu;
    unsigned char *uc_ptr;
    public:
        ItemEms();
        void SetMcastTuObj (udp_crtc *_udp);
    protected:
    
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);
};

#endif // ITEMEMS_H
