#include "itemems.h"

ItemEms::ItemEms()
{
    
}

void ItemEms::SetMcastTuObj(udp_crtc *_udp)
{
    udp_ =_udp;    
    memset (buff_out, 0x00, 1500);   
    p_tu = (packetTU *) (buff_out + sizeof(PacketHead));
    p_tu->key = 2;
    strcpy (p_tu->name,"Frauscher_TU");
    uc_ptr = buff_out + sizeof(PacketHead) + 1 + strlen (p_tu->name) + 1;
    uc_ptr[0] = 1;
    uc_ptr[1] = 1;
    uc_ptr[2] = 1;
    uc_ptr[3] = 1;
    uc_ptr[4] = 1;
}

void ItemEms::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::red));
    qDebug() << "item pressed.";
    uc_ptr[3] = 0x80;
    uc_ptr[4] = 0x80;
    udp_->SndPacket(buff_out, sizeof(PacketHead) + 1 + strlen (p_tu->name) + 1  + 5);
}

void ItemEms::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(QBrush(Qt::yellow));
    uc_ptr[3] = 0x40;
    uc_ptr[4] = 0x40;
    udp_->SndPacket(buff_out, sizeof(PacketHead) + 1 + strlen (p_tu->name) + 1  + 5);
    qDebug() << "item released.";
}
