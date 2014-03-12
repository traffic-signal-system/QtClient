#include "ctnode.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>
#include <QPoint>
#include <QHBoxLayout>
//#include <QPalette>
//#include <QDrag>
#define NODEWIDTH 20
#define NODEHEIGHT 200
#define CONTENTWIDTH 500
#define CONTENTHEIGHT 280
#define CIRCLELEN 400
CtNode::CtNode(QWidget *parent) :
    QLabel(parent)
{
    this->setFixedSize(NODEWIDTH,NODEHEIGHT);

    this->setAttribute(Qt::WA_DeleteOnClose);
    //m_ListTime<<10<<3<<3<<14<<3<<3<<18<<3<<3;
    m_ucCount = 0;
    m_ucCircle = 0;
    m_ucCtCircle = 0;
    m_iOffSet = 0;
    m_ucPosIndex = 0;
    m_ucStageIndex = 1;
    //calGreenTime();
    //this->startTimer(1000);
    QPalette p = this->palette();
    p.setColor(QPalette::Text,Qt::yellow);
    this->setPalette(p);
}

CtNode::~CtNode()
{
}

void CtNode::calGreenTime()
{
    int cnt = m_ListTime.count();
    //qDebug()<<"m_Listtime cnt"<<cnt;
    if(cnt%3==0)
    {
        m_ucCount = cnt;
        qDebug()<<"calGreenTime------------ m_ucCount"<<this->text()<<m_ucCount;

        for(quint8 i=0;i<cnt;i++)
        {
            m_ucCircle+=m_ListTime[i];
        }
        m_ListNewTime.clear();
        quint8 tolTime = 0;
        for(int i=0;i<cnt;i++)
        {
            quint8 newTime = ((quint16)m_ListTime[i])*NODEHEIGHT/((quint16)m_ucCircle);
//qDebug()<<"new time"<<newTime;
            if(i==cnt-1)
            {
                tolTime+=newTime;
                qint8 dif = NODEHEIGHT-tolTime;
                if(dif<cnt)
                {
                    for(int j=0;j<dif;j++)
                    {
                        quint8 index = 0;
                        if(j<(cnt/3))
                        {
                            index = j*3;
                        }
                        else
                        {
                            index = (j-cnt/3)*3;
                        }

//                        qDebug()<<tr("前阶段绿灯")<<j<<m_ListNewTime[index];
                        m_ListNewTime[index]+=1;
//                        qDebug()<<tr("后阶段绿灯")<<j<<m_ListNewTime[index];
                    }
                }
                else
                {
                    qDebug()<<tr("calGreenTime差距")<<dif<<cnt/3;
                }
                m_ListNewTime.append(newTime);
            }
            else
            {
                m_ListNewTime.append(newTime);
                tolTime+=newTime;
            }
        }
    }

}

void CtNode::paintEvent(QPaintEvent *e)
{//qDebug()<<"m_ListNewTime.count()"<<m_ListNewTime.count();
    if(m_ListNewTime.count()>0)
    {
       // qDebug()<<"node paintevent";
        QPixmap pix=QPixmap(NODEWIDTH,NODEHEIGHT*2);

        QPainter p(&pix);
        qint16 newPos = NODEHEIGHT*2;
        while(newPos>0)
        {
            for(quint8 i=0;i<m_ucCount;i++)
            {

                if(i%3==0)
                {
                    if((i/3+1)==m_ucStageIndex)
                    {
                        QBrush brush(Qt::green);
                        p.setBrush(brush);
                    }
                    else
                    {
                        QBrush brush(Qt::darkGreen);
                        p.setBrush(brush);
                    }
                }
                else if(i%3==1)
                {
                    QBrush brush(Qt::yellow);
                    p.setBrush(brush);
                }
                else if(i%3==2)
                {
                    QBrush brush(Qt::red);
                    p.setBrush(brush);
                }
                p.drawRect(0,newPos-m_ListNewTime[i],NODEWIDTH,m_ListNewTime[i]);
                if(i%3==0&&(i/3+1)==m_ucStageIndex)
                {
//                    QPen pen = p.pen();
//                    QPen newPen(Qt::darkGreen);
//                    p.setPen(newPen);
                    p.drawText(NODEWIDTH/2,newPos-m_ListNewTime[i]/2,/*NODEWIDTH/3,NODEWIDTH/3,Qt::AlignCenter,*/QString::number(i/3+1));
//                    p.setPen(pen);
                }
                newPos-=m_ListNewTime[i];
            }
        }

        QPainter painter(this);

        painter.drawPixmap(0,-m_iOffSet,NODEWIDTH,NODEHEIGHT*2,pix);
        QLabel::paintEvent(e);
    }

}

void CtNode::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        //qDebug()<<"leftbutton";
        m_pos = ev->pos();
        emit mouseSelect(m_uiCtNodeId);
    }
}

void CtNode::mouseMoveEvent(QMouseEvent *e)
{
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<(int)this<<QPoint(e->pos()-rect().topLeft());
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("CtNode",data);

    QDrag drag(this);
    drag.setMimeData(mimeData);
    drag.setHotSpot(QPoint(e->pos()-rect().topLeft()));

    Qt::DropAction dropAction = drag.start(Qt::CopyAction|Qt::MoveAction);

}

void CtNode::timerEvent(QTimerEvent *)
{
    m_iOffSet+=NODEHEIGHT/((quint16)m_ucCircle);
    m_iOffSet = m_iOffSet%NODEHEIGHT;
    this->update();
}


void CtNode::setCtNodeId(quint32 id)
{
    m_uiCtNodeId = id;

    qDebug()<<"new cluster node----------------"<<id;
}

quint32 CtNode::getCtNodeId()
{
    return m_uiCtNodeId;
}

void CtNode::setListTime(QList<quint8> list)
{
    m_ListTime = list;
    calGreenTime();
}

/*
 t为已经换算到NODEHEIGHT的长度
*/
void CtNode::setOffSet(qint32 t)
{
    m_iOffSet = t%NODEHEIGHT;
    if(m_iOffSet<0)
    {
        m_iOffSet+=NODEHEIGHT;
    }
   // m_ucTimeOffset = m_iOffSet*((int)m_ucCtCircle)/NODEHEIGHT;
//    emit offsetChange(m_ucTimeOffset);
    this->update();
}

void CtNode::setStageIndex(quint8 index)
{
    m_ucStageIndex = index;
}

void CtNode::setCtNodeText(QString str)
{
    int cnt = str.count();
    for(int i=cnt-1;i>=0;i--)
    {
        str.insert(i,tr("\n "));
    }
    QLabel::setText(str);
    //qDebug()<<"set text"<<str;
}

void CtNode::getPoint(QPoint &first, QPoint &second)
{
    int fy = NODEHEIGHT - m_iOffSet;
    int width = m_ListNewTime[(m_ucStageIndex-1)*3];
    int sy = fy - width;
    first = this->mapToGlobal(QPoint(0,fy));
    second = this->mapToGlobal(QPoint(0,sy));
}

void CtNode::setPosIndex(quint8 index)
{
    m_ucPosIndex = index;
}

quint8 CtNode::getPosIndex()
{
    return m_ucPosIndex;
}

void CtNode::setCtCircle(quint8 ctCircle)
{
    m_ucCtCircle = ctCircle;
}

//---------------------------------------------------------
CtNodeContent::CtNodeContent(QWidget *parent):
        QWidget(parent)
{
    this->setFixedSize(CONTENTWIDTH,CONTENTHEIGHT);
//    QPalette p = this->palette();
//    p.setColor(QPalette::Background,QColor(128,64,0));
//    this->setPalette(p);
    this->setAcceptDrops(true);
    m_Layout = new QHBoxLayout(this);
    //QStringList strList;
    //strList<<tr("一")<<tr("二")<<tr("三")<<tr("四")<<tr("五")<<tr("六");
//    for(int i=0;i<6;i++)
//    {
//        CtNode *ct = new CtNode(this);
//        ct->setCtNodeText(strList[i]);
//        ct->setCtNodeId(i+1);
//        m_ListCtNode.append(ct);
//    }
    //------------------------
//    m_siCtCircle = 30;
//    m_siClick = 0;
    //this->setAutoFillBackground(false);
    m_ucKeyIndex = 0;
    m_ucKeyOffset = 0;
    m_bFlagDragMove = false;
    //m_pNode = NULL;
    m_iLeft = 0;
    m_iRight = 0;
    m_iDif = 0;
    m_siCtCircle = 100;
}

CtNodeContent::~CtNodeContent()
{
}

void CtNodeContent::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(0,0,CONTENTWIDTH,CONTENTHEIGHT,QColor(128,64,0));

    //p.translate(-m_siClick*100,0);
    QPen pen(Qt::gray);
    int w = p.pen().width();
    pen.setWidth(3);
    p.setPen(pen);
    p.drawLine(0,(CONTENTHEIGHT+NODEHEIGHT)/2,CONTENTWIDTH,(CONTENTHEIGHT+NODEHEIGHT)/2);
    pen.setColor(Qt::yellow);
    pen.setWidth(w);
    p.setPen(pen);
    p.drawText(CONTENTWIDTH/2-20,(CONTENTHEIGHT+NODEHEIGHT)/2+30,QObject::tr("周期:%1").arg(m_siCtCircle));
    p.drawText((CONTENTWIDTH-CIRCLELEN)/2-45,(CONTENTHEIGHT+NODEHEIGHT)/2+13,QObject::tr("相位差:"));
    for(int i=0;i<5;i++)
    {
        if((m_siCtCircle*i)%4==0)
            p.drawText(CIRCLELEN/4*i+(CONTENTWIDTH-CIRCLELEN)/2,(CONTENTHEIGHT+NODEHEIGHT)/2+13,QString::number(m_siCtCircle*i/4));
    }

    QPoint first;
    QPoint second;
    QPoint fLine;
    QPoint sLine;
    CtNode *fNode = NULL;
    CtNode *sNode = NULL;
    getLineCtNode(&fNode,&sNode);
    //qDebug()<<"node"<<fNode<<sNode;
    if(fNode!=sNode)
    {
        fNode->getPoint(first,second);
        sNode->getPoint(fLine,sLine);
        pen.setStyle(Qt::DashLine);
        p.setPen(pen);
        first = this->mapFromGlobal(first);
        second = this->mapFromGlobal(second);
        fLine = this->mapFromGlobal(fLine);
        sLine = this->mapFromGlobal(sLine);

        //qDebug()<<"draw line"<<first<<fLine;
        p.drawLine(first,fLine);
        p.drawLine(second,sLine);
    }
//
    if(m_iLeft==0&&m_iRight==0&&m_iDif==0)
    {
    }
    else if(m_bFlagDragMove)
    {
        qDebug()<<"paint content"<<m_iLeft<<m_iRight<<m_iDif;
        p.drawLine(QPoint(m_iLeft,(CONTENTHEIGHT-NODEHEIGHT)/2),QPoint(m_iRight,(CONTENTHEIGHT-NODEHEIGHT)/2));
        p.drawText((m_iLeft+m_iRight+20)/2,(CONTENTHEIGHT-NODEHEIGHT)/2-5,QString::number(m_iDif));

    }

    if(m_bUpdate)
    {
        this->update();

        m_bUpdate = false;
    }

}

void CtNodeContent::mousePressEvent(QMouseEvent *)
{
//    int b;
//    if(e->button()==Qt::LeftButton)
//    {
//        m_siClick++;
//        b = 1;
//    }
//    else if(e->button()==Qt::RightButton)
//    {
//        b = -1;
//        //if(m_siClick!=0)
//        {
//            m_siClick--;
//        }
//    }
//    //qDebug()<<"m_siClick"<<m_siClick;
//    int cnt = m_ListCtNode.count();
//    for(int i=0;i<cnt;i++)
//    {
//        QPoint p = m_ListCtNode[i]->geometry().topLeft();
//        //qDebug()<<p<<this->mapFromParent(p);

//        int xPos = p.x()-(b*CIRCLELEN/2);
//        int yPos = p.y();
//        setOffset(QPoint(xPos,yPos),m_ListCtNode[i]);
//       // m_ListCtNode[i]->move(50*i*m_siClick,25);
//    }
//    this->update();
    //this->set(m_siClick*100,50,400,250);
}

void CtNodeContent::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
    //qDebug()<<"drag enter";
    if(e->mimeData()->hasFormat("CtNode"))
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

void CtNodeContent::dragMoveEvent(QDragMoveEvent *e)
{
    e->accept();

    //qDebug()<<"drag move";
    if(e->mimeData()->hasFormat("CtNode"))
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
        QByteArray data = e->mimeData()->data("CtNode");
        QDataStream stream(&data,QIODevice::ReadOnly);
        CtNode *node;
        int nodeData;
        QPoint offSet;
        stream>>nodeData>>offSet;
        node = static_cast<CtNode*>((void*)nodeData);
        QPoint newPos = e->pos()-offSet;
        newPos.setY((CONTENTHEIGHT-NODEHEIGHT)/2);
//        int dif = (newPos.x()%400)*NODEHEIGHT/CIRCLELEN;
//        if(dif<0)
//        {
//            dif = -dif;
//        }
//        node->setOffSet(dif);
        setOffset(newPos,node);

        m_iRight = node->geometry().left();
        m_iLeft = getLeftNodePos(m_iRight);
        m_iDif = (m_iRight-m_iLeft)*m_siCtCircle/CIRCLELEN;//与相邻节点的时间差
        this->update();
//        if(!m_bFlagDragMove)
//        {
//            m_bFlagDragMove = true;
//            //m_pNode = node;
//        }

//        node->move(newPos);
    }
}

void CtNodeContent::dropEvent(QDropEvent *e)
{ e->accept();
    qDebug()<<e->mimeData()->formats();
    if(e->mimeData()->hasFormat("CtNode"))
    {
        m_bFlagDragMove = true;
        QByteArray data = e->mimeData()->data("CtNode");
        QDataStream stream(&data,QIODevice::ReadOnly);
        CtNode *node;
        int nodeData;
        QPoint offSet;
        stream>>nodeData>>offSet;
        node = static_cast<CtNode*>((void*)nodeData);
        QPoint newPos = e->pos()-offSet;
        newPos.setY((CONTENTHEIGHT-NODEHEIGHT)/2);
//        int dif = (newPos.x()%400)*NODEHEIGHT/CIRCLELEN;
//        if(dif<0)
//        {
//            dif = -dif;
//        }
//        node->setOffSet(dif);
        setOffset(newPos,node);
        m_bUpdate = true;

        m_iRight = node->geometry().left();
        m_iLeft = getLeftNodePos(m_iRight);
        m_iDif = (m_iRight-m_iLeft)*m_siCtCircle/CIRCLELEN;//与相邻节点的时间差
        qDebug()<<"m_iDif:"<<m_iDif;
//        node->move(newPos);
//qDebug()<<"node drop pos"<<node->geometry().topLeft()<<newPos;
        calOffsetList(node->getCtNodeId());
        if(children().contains(e->source()))
        {
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            e->acceptProposedAction();
        }
        //        delete e->mimeData();
    }
    else
    {
        e->ignore();
    }
}

void CtNodeContent::setCtCircle(quint8 c)
{
    m_siCtCircle = c;
    this->update();
}

void CtNodeContent::setOffset(QPoint p,CtNode*node)
{
    //qDebug()<<"befor x"<<p.x();
    int x = p.x()/(CIRCLELEN/m_siCtCircle)*(CIRCLELEN/m_siCtCircle);
   // qDebug()<<"after x"<<x;
    int dif = ((x-(CONTENTWIDTH-CIRCLELEN)/2)%CIRCLELEN)*NODEHEIGHT/CIRCLELEN;
//qDebug()<<"dif"<<dif;
    node->setOffSet(dif);
    p.setX(x);
    node->move(p);
}

/*
 x为相位差，先换算成content的距离长度
*/
void CtNodeContent::setOffset(int x, CtNode *node)
{
    int newX = x*CIRCLELEN/m_siCtCircle+(CONTENTWIDTH-CIRCLELEN)/2;
    //qDebug()<<"newX"<<newX;
    int dif = ((newX-(CONTENTWIDTH-CIRCLELEN)/2)%CIRCLELEN)*NODEHEIGHT/CIRCLELEN;
    node->setOffSet(dif);
    node->move(QPoint(newX,(CONTENTHEIGHT-NODEHEIGHT)/2));
}

void CtNodeContent::getLineCtNode(CtNode **f, CtNode **s)
{
    int cnt = m_ListCtNode.count();
    int min = (CIRCLELEN+CONTENTWIDTH)/2;
    int max = (CONTENTWIDTH-CIRCLELEN)/2;
    for(int i=0;i<cnt;i++)
    {
        CtNode *node = m_ListCtNode[i];
        int x = node->geometry().left();
        if(x>(CONTENTWIDTH-CIRCLELEN)/2&&x<(CIRCLELEN+CONTENTWIDTH)/2)
        {
            if(min>x)
            {
                min = x;
                *f = node;
                //qDebug()<<"min "<<x;
            }
            if(max<x)
            {
                max = x;
                *s = node;
                //qDebug()<<"max "<<x;
            }
        }
    }
}

void CtNodeContent::moveLeftRight(int b,int len)
{
    m_bFlagDragMove = false;
    int cnt = m_ListCtNode.count();
    if(len==0)
    {
        len = CIRCLELEN/2;
    }
    else if(len==1&&m_siCtCircle!=0)
    {
        len = CIRCLELEN/m_siCtCircle;
    }
    for(int i=0;i<cnt;i++)
    {
        QPoint p = m_ListCtNode[i]->geometry().topLeft();
        //qDebug()<<p<<this->mapFromParent(p);

        int xPos = p.x()-(b*len);
        int yPos = p.y();
        setOffset(QPoint(xPos,yPos),m_ListCtNode[i]);
       // m_ListCtNode[i]->move(50*i*m_siClick,25);
    }
    this->update();
}
/*
 t为相位差 一周期内；
*/
void CtNodeContent::appendCtNode(CtNode *node,int t)
{
    m_Layout->addWidget(node);
    m_Layout->removeWidget(node);
    m_ListCtNode.append(node);
    int offset = node->getPosIndex()*m_siCtCircle+t%m_siCtCircle;
    qDebug()<<"append node index"<<node->getPosIndex()<<"offset"<<t<<offset;
    setOffset(offset,node);

}

void CtNodeContent::clearCtNodeList()
{
    int cnt = m_ListCtNode.count();
    for(int i=0;i<cnt;i++)
    {
        m_ListCtNode[i]->close();
    }
    m_ListCtNode.clear();
    m_ListRelativeOffset.clear();
}

void CtNodeContent::calOffsetList(quint32 nodeId)
{
    m_ListRelativeOffset.clear();
    int cnt = m_ListCtNode.count();

    int base = 0;
    for(int i=0;i<cnt;i++)
    {
        int x = (m_ListCtNode[i]->geometry().left()-(CONTENTWIDTH-CIRCLELEN)/2)*m_siCtCircle/CIRCLELEN;
        if(i==0)
        {
            base = x;
            m_ListRelativeOffset.append(x);
        }
        else
        {
            m_ListRelativeOffset.append(x-base);
        }
    }

qDebug()<<"caloffsetlist"<<m_ListRelativeOffset;

    if(nodeId!=0)
    {
        emit offsetChange(nodeId);
    }
}
//list 同顺序 节点号 index offset
void CtNodeContent::calPosIndexList()
{
    //qDebug()<<"before"<<m_ListRelativeOffset;
    int cnt = m_ListRelativeOffset.count();
    m_ListNodePosIndex.clear();
    if(cnt>0&&m_siCtCircle>0)
    {
        int min = 0;
        int index = -1;
        int base = m_ListRelativeOffset[0];
        for(int i=1;i<cnt;i++)
        {
            m_ListRelativeOffset[i] += base;
        }
        qDebug()<<"caloffsetlist1"<<m_ListRelativeOffset;
        if(cnt>m_ucKeyIndex)
        {
            //qDebug()<<"m_ListRelativeOffset"<<m_ListRelativeOffset.count();
            int keyOffset = m_ListRelativeOffset[m_ucKeyIndex];//取得原list里 key节点的 offset值
            int diff = keyOffset - m_ucKeyOffset;
            for(int i=0;i<cnt;i++)
            {
                m_ListRelativeOffset[i] = m_ListRelativeOffset[i] - diff;
            }
        }
        qDebug()<<"caloffsetlist2"<<m_ListRelativeOffset;
        for(int i=0;i<cnt;i++)
        {
            if(i==0)
            {
                min = m_ListRelativeOffset[0];
                index = 0;
            }
            else if(min>m_ListRelativeOffset[i])
            {
                index = i;
                min = m_ListRelativeOffset[i];
            }
        }
        int x = min/m_siCtCircle;
//qDebug()<<"min x"<<x<<min;
        if(x>0)
        {
            for(int i=0;i<cnt;i++)
            {
                m_ListRelativeOffset[i] -= x*m_siCtCircle;
            }
        }
        else if(x<0)
        {
            for(int i=0;i<cnt;i++)
            {
                m_ListRelativeOffset[i] -= (x-1)*m_siCtCircle;
            }
        }
        else if(x==0&&min<0)
        {
            for(int i=0;i<cnt;i++)
            {
                m_ListRelativeOffset[i] += m_siCtCircle;
            }
        }

        for(int i=0;i<cnt;i++)
        {
            m_ListNodePosIndex.append(m_ListRelativeOffset[i]/m_siCtCircle);
            m_ListRelativeOffset[i] %= m_siCtCircle;
            qDebug()<<m_ListCtNode[i]->getCtNodeId()<<"index"<<m_ListNodePosIndex[i]<<"offset"<<m_ListRelativeOffset[i];
        }
        m_ListNodePosIndex[m_ucKeyIndex] |= 0x80;
        qDebug()<<"caloffsetlist3"<<m_ListRelativeOffset;
//qDebug()<<"after"<<m_ListRelativeOffset<<"index"<<m_ListNodePosIndex;
    }
}

void CtNodeContent::setKeyData(quint8 index, quint8 offset)
{
    m_ucKeyIndex = index;
    m_ucKeyOffset = offset;
}

quint8 CtNodeContent::getCurNodeListCount()
{
    return m_ListCtNode.count();
}

int CtNodeContent::getLeftNodePos(int left)
{
    int cnt = m_ListCtNode.count();

    QList<int> listLeft;
    for(int i=0;i<cnt;i++)
    {
        listLeft.append(m_ListCtNode[i]->geometry().left());
    }
    qSort(listLeft);
    int index = listLeft.indexOf(left);
    if(index>0)
    {
        return listLeft[index-1];
    }
    else
    {
        return (CONTENTWIDTH-CIRCLELEN)/2;
    }
}

void CtNodeContent::setFlagDragMove(bool b)
{
    m_bFlagDragMove = b;
    update();
}

//----------slots-------------
//void CtNodeContent::on_mouseSelectCtNode(quint32 ctNodeId)
//{
//    emit mouseSelectCtNode(ctNodeId)
//}
