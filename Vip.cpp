#include "Vip.h"
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QTime>
#include <QMouseEvent>
#include <QListWidget>
#include <QDebug>
#define VIPDIAMETER 20
#define VIPTIMELEN 630
#define VIPCONTENTWIDTH 680
#define VIPCONTENTHEIGHT 50

VipNode::VipNode(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(VIPDIAMETER*3,VIPDIAMETER*2);
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_nodeId = 0;
    m_ucStageIndex = 1;//µÚ¼¸½×¶Î 1 Æð
    m_usTime = 0;
    QPalette p = this->palette();
    p.setColor(QPalette::Background,Qt::transparent);
    this->setPalette(p);
    QFont font = this->font();
    int w = font.weight()/8;
    //qDebug()<<"font w"<<w;
    font.setWeight(w);
    this->setFont(font);
    m_ucCurStage = 0;
}

VipNode::~VipNode()
{
}

void VipNode::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        //qDebug()<<"leftbutton";
        m_pos = ev->pos();
        emit mouseSelect(this);
    }
}

void VipNode::mouseMoveEvent(QMouseEvent *e)
{
    if((e->pos()-m_pos).manhattanLength()<15)
        return;
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<(int)this<<QPoint(e->pos()-rect().topLeft());
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("VipNode",data);

    QDrag drag(this);
    drag.setMimeData(mimeData);
    drag.setHotSpot(QPoint(e->pos()-rect().topLeft()));
    Qt::DropAction dropAction = drag.start(Qt::CopyAction|Qt::MoveAction);
}


void VipNode::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QBrush brush(m_color);
    p.setBrush(brush);
    //p.drawRect(0,0,VIPDIAMETER*2,VIPDIAMETER*2);
    p.drawEllipse(QPoint(VIPDIAMETER*3/2,VIPDIAMETER/2),VIPDIAMETER/2,VIPDIAMETER/2);
    QPen pen(Qt::yellow);
    p.setPen(pen);
    p.drawText(QPoint(VIPDIAMETER+10,VIPDIAMETER-5),QString::number(m_ucCurStage));
//    QFont font = this->font();
//    int w = font.weight();
//    qDebug()<<"font w"<<w;
//    font.setWeight(w);
    //this->setFont(font);
    p.drawText(0,VIPDIAMETER*4/5,VIPDIAMETER*3,VIPDIAMETER,Qt::AlignCenter,m_strName);


}

void VipNode::setNodeId(quint32 id, QString name)
{
    m_nodeId = id;
    m_strName = name;
    setColorGreen(false);
}

void VipNode::setColorGreen(bool b)
{
    if(b)
    {
        m_color = QColor(0,255,0);
    }
    else
    {
        if(m_color==QColor(0,255,0)||!m_color.isValid())
        {
            int r = qrand()%255;
            qDebug()<<"set vip node color-----------------"<<r;
            m_color = QColor((r+m_nodeId*10)%255,(r*5+m_nodeId*10)%170,(r*8+m_nodeId*10)%255);
        }
    }
    this->update();
}

quint32 VipNode::getNodeId()
{
    return m_nodeId;
}

void VipNode::setStageIndex(quint8 index)
{
    m_ucStageIndex = index;
    m_ucCurStage = index;
    this->update();
}

quint8 VipNode::getStageIndex()
{
    return m_ucStageIndex;
}

void VipNode::setTimeOffset(quint16 t)
{
    m_usTime = t;
}

quint16 VipNode::getTimeOffset()
{
    return m_usTime;
}
void VipNode::setIconDark(bool b)
{
    if(!b)
    {
        this->setBackgroundRole(QPalette::Light);
    }
    else
    {
        this->setBackgroundRole(QPalette::Shadow);
    }
}

void VipNode::setCurStage(quint8 stage)
{
    m_ucCurStage = stage;
}

//--------slot---------



//----------------------------------------------------------

VipNodeContent::VipNodeContent(QWidget *parent):
        QWidget(parent)
{
    m_Layout = new QHBoxLayout(this);
    m_Layout->setMargin(0);
    m_Layout->setSpacing(200);
    m_Layout->setContentsMargins((VIPCONTENTWIDTH-VIPTIMELEN)/2,(VIPCONTENTHEIGHT-VIPDIAMETER)/2,(VIPCONTENTWIDTH+VIPTIMELEN)/2,(VIPCONTENTHEIGHT+VIPDIAMETER)/2);
    m_usLen = 400;
    this->setFixedSize(VIPCONTENTWIDTH,VIPCONTENTHEIGHT);
    this->setAcceptDrops(true);
}

VipNodeContent::~VipNodeContent()
{

}

void VipNodeContent::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(0,0,VIPCONTENTWIDTH,VIPCONTENTHEIGHT,QColor(128,64,0));
    QPen pen(Qt::yellow);
    p.setPen(pen);
    p.drawLine(QPoint((VIPCONTENTWIDTH-VIPTIMELEN)/2,VIPCONTENTHEIGHT/2),QPoint((VIPCONTENTWIDTH+VIPTIMELEN)/2,VIPCONTENTHEIGHT/2));
}

void VipNodeContent::dragEnterEvent(QDragEnterEvent *e)
{
        if(e->mimeData()->hasFormat("VipNode"))
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

void VipNodeContent::dragMoveEvent(QDragMoveEvent *e)
{
    if(e->mimeData()->hasFormat("VipNode"))
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
        QByteArray data = e->mimeData()->data("VipNode");
        QDataStream stream(&data,QIODevice::ReadOnly);
        VipNode *node;
        int nodeData;
        QPoint offSet;
        stream>>nodeData>>offSet;
        node = static_cast<VipNode*>((void*)nodeData);
//        QPoint newPos = e->pos()-offSet;
//        newPos.setY((VIPCONTENTHEIGHT-VIPDIAMETER)/2);
    }
}

void VipNodeContent::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("VipNode"))
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
        QByteArray data = e->mimeData()->data("VipNode");
        QDataStream stream(&data,QIODevice::ReadOnly);
        VipNode *node;
        int nodeData;
        QPoint offSet;
        stream>>nodeData>>offSet;
        node = static_cast<VipNode*>((void*)nodeData);
        addIcon(node);
//        QPoint newPos = e->pos()-offSet;
//        newPos.setY((VIPCONTENTHEIGHT-VIPDIAMETER)/2);
//        //        delete e->mimeData();

    }
}

void VipNodeContent::addIcon(VipNode *node)
{
    //node->setAutoFillBackground(true);
    if(!m_ListNode.contains(node))
    {
        m_ListNode.append(node);
        connect(node,SIGNAL(mouseSelect(VipNode*)),this,SLOT(on_mouseSelect(VipNode*)));
    }
    m_Layout->addWidget(node);

}

void VipNodeContent::addIcon(quint32 id,QString name)
{
    VipNode* node = new VipNode;
    node->setNodeId(id,name);
    addIcon(node);
}

void VipNodeContent::delIcon(quint32 id)
{qDebug()<<"delete vip node"<<id;
    int cnt = m_ListNode.count();
    for(int i=0;i<cnt;i++)
    {
        VipNode *node = m_ListNode[i];
        if(node->getNodeId()==id)
        {
            m_Layout->removeWidget(node);
            m_ListNode.removeAt(i);
            node->close();
            return;
        }
    }
}

void VipNodeContent::getVipData(/*QList<quint32> &listId, QList<quint8> &listStage, QList<quint16> &listTime*/)
{
    m_ListNode.clear();
    m_ListNodeId.clear();
    m_ListStageIndex.clear();
    m_ListTimeOffset.clear();
    QList<VipNode*> listNode = this->findChildren<VipNode *>();
    int cnt = listNode.count();
    QList<int> listPos;
    for(int i=0;i<cnt;i++)
    {
        listPos.append(listNode[i]->geometry().left());
        qDebug()<<"vipNode Pos:"<<listPos[i];
    }
    qSort(listPos);
    qDebug()<<cnt<<"m_Layout";
    for(int i=0;i<cnt;i++)
    {
        foreach(VipNode*node,listNode)
        {
            if(node->geometry().left()==listPos[i])
            {
                m_ListNode.append(node);
                break;
            }
        }

        m_ListNodeId.append(m_ListNode[i]->getNodeId());
        qDebug()<<"nodeid"<<m_ListNodeId[i];
        m_ListStageIndex.append(m_ListNode[i]->getStageIndex());
        m_ListTimeOffset.append(m_ListNode[i]->getTimeOffset());
//        listId.append(m_ListNode[i]->getNodeId());
//        listStage.append(m_ListNode[i]->getStageIndex());
//        listTime.append(m_ListNode[i]->getTimeOffset());
    }

}

void VipNodeContent::clearNode()
{
    int cnt = m_ListNode.count();
    for(int i=0;i<cnt;i++)
    {
        m_ListNode[i]->close();
    }
    m_ListNode.clear();
//    m_ListNodeId.clear();
//    m_ListStageIndex.clear();
//    m_ListTimeOffset.clear();
}

void VipNodeContent::setVipNodeGreen(quint32 id, bool b,quint8 stageId)
{
    foreach(VipNode*node,m_ListNode)
    {
        if(node->getNodeId()==id)
        {qDebug()<<"setVipNodeGreen"<<id<<b;
            node->setColorGreen(b);
            if(stageId>0)
            {
                node->setCurStage(stageId);
            }
        }
    }
}

QList<quint32> VipNodeContent::getIdList()
{
    return m_ListNodeId;
}

QList<quint8> VipNodeContent::getStageList()
{
    return m_ListStageIndex;
}
QList<quint16> VipNodeContent::getTimeList()
{
    return m_ListTimeOffset;
}

//---------------------slot-------------
void VipNodeContent::on_mouseSelect(VipNode *node)
{
    int cnt = m_ListNode.count();
    for(int i=0;i<cnt;i++)
    {
        VipNode* n = m_ListNode[i];
        if(n==node)
        {qDebug()<<node->getNodeId()<<"set dark"<<cnt;
            n->setIconDark(true);
        }
        else
        {
            n->setIconDark(false);
        }
    }
    emit mouseSelect(node);
}
