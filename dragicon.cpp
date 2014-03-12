#include "dragicon.h"
#include <QApplication>
#include <QDebug>
#include <QDrag>

DragIcon::DragIcon(QPixmap pix,QString str,QWidget *parent) :
    QLabel(parent)
{
    setScaledContents(true);
    setPixmap(pix);

    m_IconStr = str;


}

void DragIcon::setIconCursor(bool b)
{
    if(b)
    {
        this->setCursor(Qt::SplitHCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

void DragIcon::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        startPos = ev->pos();
    }
}

void DragIcon::mouseMoveEvent(QMouseEvent *ev)
{
//    if((ev->button()&Qt::LeftButton))
//    {
//        return;
//    }

    if((ev->pos()-startPos).manhattanLength()<QApplication::startDragDistance())
    {
        return;
    }

    QPixmap pix = *pixmap();

    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<pix<<QPoint(ev->pos()-rect().topLeft());
    QMimeData *mimeData = new QMimeData;
    mimeData->setData(m_IconStr,data);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(ev->pos()-rect().topLeft()));
    drag->setPixmap(pix);

    hide();

    Qt::DropAction dropAction = drag->start(Qt::MoveAction);
    if(dropAction==Qt::MoveAction)
    {
        //qDebug()<<"close drag icon";
        //close();
    }
    else
    {
        //qDebug()<<"show drag icon";
        show();
    }
}
