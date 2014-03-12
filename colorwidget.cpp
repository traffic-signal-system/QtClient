#include "colorwidget.h"
#include <QDebug>
#include <QPainter>
#define COLORWIDTH 130
#define BARWIDTH 5
#define BARHEIGHT 25

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAcceptDrops(false);
    this->setFixedSize(COLORWIDTH,BARHEIGHT);
    QPixmap pix1(BARWIDTH,BARHEIGHT);
    pix1.fill(Qt::blue);
    QPixmap pix2(BARWIDTH,BARHEIGHT);
    pix2.fill(Qt::black);
    //m_IconY = new DragIcon(QPixmap(BARWIDTH,BARHEIGHT),QString::number(1),this);
    m_IconY = new DragIcon(pix1,QString::number(1),this);
    //m_IconR = new DragIcon(QPixmap(BARWIDTH,BARHEIGHT),QString::number(2),this);
    m_IconR = new DragIcon(pix2,QString::number(2),this);

    setTimeValue();
}

void ColorWidget::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("1")||e->mimeData()->hasFormat("2"))
    {
        if(children().contains(e->source()))
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            e->acceptProposedAction();
        }
    }
}

void ColorWidget::dragMoveEvent(QDragMoveEvent *e)
{

    qint16 posX;
    if(e->mimeData()->hasFormat("1"))
    {
        QByteArray data = e->mimeData()->data("1");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPixmap pix;
        QPoint offset;
        stream>>pix>>offset;
         posX = qint16(e->pos().x())-qint16(offset.x());

        if((e->pos().y()-offset.y())!=0)
        {
            QPoint global = this->mapToGlobal(QPoint(e->pos().x(),offset.y()));
            //this->cursor().setPos(e->pos().x()+this->geometry().x(),offset.y()+this->geometry().y());
            this->cursor().setPos(global);

        }

        if(posX>qint16((m_ucYellow-BARWIDTH)))
        {
            //qDebug()<<"enter1";

            if((posX+BARWIDTH)<(COLORWIDTH-BARWIDTH))
            {
                m_ucYellow = posX+BARWIDTH;
                m_ucGreen = m_ucYellow-BARWIDTH;

            }
            else if((posX+BARWIDTH)>=(COLORWIDTH-BARWIDTH))
            {

                m_ucYellow = COLORWIDTH-BARWIDTH;
                m_ucGreen = m_ucYellow-BARWIDTH;

            }

        }
        else if(posX<=0)
        {

            m_ucGreen = 0;


        }
        else
        {

            m_ucGreen = quint8(posX);
            //qDebug()<<m_ucGreen;

        }
        QPoint global;

            global = this->mapToGlobal(QPoint(m_ucGreen+offset.x(),offset.y()));



        this->cursor().setPos(global);
        setBarPos();
        this->update();
        if(children().contains(e->source()))
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            e->acceptProposedAction();
        }
    }
    else if(e->mimeData()->hasFormat("2"))
    {
        QByteArray data = e->mimeData()->data("2");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPixmap pix;
        QPoint offset;
        stream>>pix>>offset;
        posX = e->pos().x()-offset.x();
        if((e->pos().y()-offset.y())!=0)
        {
            QPoint global = this->mapToGlobal(QPoint(e->pos().x(),offset.y()));
            //this->cursor().setPos(e->pos().x()+this->geometry().x(),offset.y()+this->geometry().y());
            this->cursor().setPos(global);
        }

        if(posX<(m_ucGreen+BARWIDTH))
        {
            if(posX>BARWIDTH)
            {
                m_ucYellow = posX;
                m_ucGreen = posX-BARWIDTH;
            }
            else
            {
                m_ucYellow = BARWIDTH;
                m_ucGreen = 0;
            }
        }
        else if(posX>(COLORWIDTH-BARWIDTH))
        {
            m_ucYellow = COLORWIDTH-BARWIDTH;
        }
        else
        {
           m_ucYellow = posX;
        }
        //this->cursor().setPos(m_ucYellow+offset.x()+this->geometry().x(),offset.y()+this->geometry().y());
        QPoint global = this->mapToGlobal(QPoint(m_ucYellow+offset.x(),offset.y()));
        this->cursor().setPos(global);
        setBarPos();
        this->update();
        if(children().contains(e->source()))
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            e->acceptProposedAction();
        }
    }

}



void ColorWidget::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("1"))
    {

        QByteArray data = e->mimeData()->data("1");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPixmap pix;
        QPoint offset;
        stream>>pix>>offset;

        m_IconY->move(m_ucGreen,0);

        m_IconY->show();

        if(children().contains(e->source()))
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
            this->update();
        }
        else
        {
            e->acceptProposedAction();
        }
    }
    else if(e->mimeData()->hasFormat("2"))
    {

        QByteArray data = e->mimeData()->data("2");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPixmap pix;
        QPoint offset;
        stream>>pix>>offset;

        m_IconR->move(m_ucYellow,0);
        m_IconR->show();

        if(children().contains(e->source()))
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
            setBarPos();
            this->update();
        }
        else
        {
            e->acceptProposedAction();
        }
    }
    else
    {
        e->ignore();
    }

}



void ColorWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    QBrush brush(Qt::green);

    painter.setBrush(brush);
    painter.drawRect(0,0,m_ucGreen,BARHEIGHT);

    brush.setColor(Qt::yellow);
    painter.setBrush(brush);
    painter.drawRect(m_ucGreen,0,(m_ucYellow-m_ucGreen),BARHEIGHT);

    brush.setColor(Qt::red);
    painter.setBrush(brush);
    painter.drawRect(m_ucYellow,0,(COLORWIDTH-m_ucYellow),BARHEIGHT);

    painter.drawText(QPointF(m_ucGreen/2-2,BARHEIGHT*3/4),QString::number(m_TimeGreen));
    painter.drawText(QPointF((m_ucYellow+m_ucGreen+BARWIDTH)/2-2,BARHEIGHT*3/4),QString::number(m_TimeYellow));
    painter.drawText(QPointF((COLORWIDTH+m_ucYellow+BARWIDTH)/2-2,BARHEIGHT*3/4),QString::number(m_TimeRed));

}

/*
 设置时间条时间，调整 位置
*/
void ColorWidget::setTimeValue(quint8 green, quint8 yellow, quint8 red)
{
    m_TimeGreen = green;
    m_TimeYellow = yellow;
    m_TimeRed = red;

    quint8 total = green+yellow+red;
    if(total>0)
    {
        m_ucYellow = COLORWIDTH - ((quint16)red)*(COLORWIDTH-BARWIDTH*2)/total-BARWIDTH;
        quint16 redWidth = COLORWIDTH - m_ucYellow - BARWIDTH;

        quint16 yellowWidth;
        if(m_TimeRed!=0)
        {
            yellowWidth = (quint16)(m_TimeYellow)*redWidth/m_TimeRed;
        }
        else
        {
            yellowWidth = (quint16)m_TimeYellow*(COLORWIDTH-2*BARWIDTH)/total;
        }


        m_ucGreen = m_ucYellow - yellowWidth - BARWIDTH;
    }
    m_IconY->move(m_ucGreen,0);
    m_IconR->move(m_ucYellow,0);
    update();
}

void ColorWidget::setStageTime(quint8 stagetime)
{

    if(stagetime>(m_TimeYellow+m_TimeRed))
    {
        m_TimeGreen = stagetime-m_TimeYellow-m_TimeRed;
        setTimeValue(m_TimeGreen,m_TimeYellow,m_TimeRed);
    }

}

void ColorWidget::setEditable(bool b)
{
    this->setAcceptDrops(b);
    m_IconY->setIconCursor(b);
    m_IconR->setIconCursor(b);
}

quint8 ColorWidget::getTimeGreen()
{
    return m_TimeGreen;
}

quint8 ColorWidget::getTimeYellow()
{
    return m_TimeYellow;
}

quint8 ColorWidget::getTimeRed()
{
    return m_TimeRed;
}

void ColorWidget::setBarPos()
{

    quint16 totalTime = m_TimeGreen+m_TimeYellow+m_TimeRed;
    quint16 totalColor = COLORWIDTH-2*BARWIDTH;
    m_TimeGreen = qRound(((qreal)m_ucGreen)*totalTime/totalColor);

    m_TimeRed = qRound((qreal(COLORWIDTH-m_ucYellow-BARWIDTH))*totalTime/totalColor);

    m_TimeYellow = totalTime-m_TimeGreen-m_TimeRed;

    quint16 redWidth;
    quint16 yellowWidth;
    if(totalTime>0)
    {
        redWidth = quint16(m_TimeRed)*totalColor/totalTime;
        yellowWidth = quint16(m_TimeYellow)*totalColor/totalTime;
        m_ucYellow = COLORWIDTH-redWidth-BARWIDTH;

        m_ucGreen = m_ucYellow-yellowWidth-BARWIDTH;
        m_IconY->move(m_ucGreen,0);
        m_IconR->move(m_ucYellow,0);
    }

}
