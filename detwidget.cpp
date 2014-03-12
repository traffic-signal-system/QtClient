#include "detwidget.h"

#include <QDebug>
#include <QPainter>


#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPoint>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include <QLabel>
#include <QGroupBox>
#include <QStringList>
#include <QGridLayout>
#include <QLineEdit>
#define FLOWWIDTH 10
#define FLOWHEIGHT 31
#define FLOWBASE 3
#define PIXWIDTH 650
#define PIXHEIGHT 40

DetIcon::DetIcon(QWidget *parent) :
    QDialog(parent)
{

    m_iRadius = 8;
    m_bIncludeMouse = false;
    m_bSend = false;
    //m_pStDetector = NULL;
    m_ucDetNo = 0;
    m_bGreen = false;
    m_bRed = false;
    //m_iTimer = 0;
    this->setFixedSize(m_iRadius*2,m_iRadius*2);
}

DetIcon::~DetIcon()
{
    qDebug()<<"~DetIcon()"<<m_ucDetNo;
}

void DetIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPalette p = this->palette();
    p.setColor(QPalette::Background,Qt::transparent);
    this->setPalette(p);



    if(m_bRed)
    {
       QBrush brush(Qt::red);
       painter.setBrush(brush);
    }
    else if(m_bGreen)
    {
        QBrush brush(Qt::green);
        painter.setBrush(brush);
    }
    else if(m_bIncludeMouse)
    {
        QBrush brush(Qt::darkGray);
        painter.setBrush(brush);
    }
    else
    {
        QBrush brush(Qt::white);
        painter.setBrush(brush);
    }


    painter.drawRect(0,0,m_iRadius*2,m_iRadius*2);

    if(m_ucDetNo!=0)
    {
        painter.drawText(m_iRadius-8,m_iRadius-8,16,16,Qt::AlignCenter,tr("%1").arg(m_ucDetNo));
    }

}

void DetIcon::mouseMoveEvent(QMouseEvent *ev)
{
    if(((ev->pos()-m_posStart).manhattanLength())<5)
    {
        return;
    }
    m_bDrag = true;
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<(int)this;
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("Drag-Icon",data);

//    QDrag *drag = new QDrag(this);
//    drag->setMimeData(mimeData);
//    drag->setHotSpot(QPoint(ev->pos()-rect().topLeft()));
//    Qt::DropAction dropAction = drag->start(Qt::CopyAction|Qt::MoveAction);

    QDrag drag(this);
    drag.setMimeData(mimeData);
    drag.setHotSpot(QPoint(ev->pos()-rect().topLeft()));
    Qt::DropAction dropAction = drag.start(Qt::CopyAction|Qt::MoveAction);

    if(dropAction==Qt::MoveAction)
    {
        //close();
    }
    else
    {
        show();
    }
}

void DetIcon::enterEvent(QEvent *)
{
    //
    //emit mouseStatus(true,true,m_ucDetNo,this->mapToParent(this->geometry().topRight()));
    //int id = this->startTimer(2000);
    //qDebug()<<"timer id"<<id;
    m_bIncludeMouse = true;
    this->update();

}

void DetIcon::leaveEvent(QEvent *)
{

    //emit mouseStatus(false,true,m_ucDetNo,QPoint(0,0));
    m_bIncludeMouse = false;
    this->update();
    if(m_bSend)
    {
        //qDebug()<<"detector:"<<m_ucDetNo<<"mouse leave";
        m_bSend = false;
        //emit mouseStatus(false,true,m_ucDetNo,QPoint(0,0));
    }
}

void DetIcon::setDetectorNo(quint8 no)
{
    m_ucDetNo = no;
}

quint8 DetIcon::getDetectorNo()
{
    return m_ucDetNo;
}

void DetIcon::setRadius(int r)
{
    m_iRadius = r;
    this->setFixedSize(m_iRadius*2,m_iRadius*2);
}

/*
 b true 有车 false 无车
 detAlarm 检测器报警状态
 coilAlarm 感应线圈报警状态
*/
void DetIcon::setDetStatus(bool b, quint8 detAlarm, quint8 coilAlarm)
{
    m_bGreen = b;

    if((detAlarm!=0||coilAlarm!=0)&&!b)
    {
        m_bRed = true;
        QString alarmStr = QString::number(m_ucDetNo)+tr("检测器:");
        if(detAlarm&0x01)
        {
            alarmStr += tr("不活动");
        }
        if(detAlarm&0x02)
        {
            alarmStr += tr("存在时间过长");
        }
        if(detAlarm&0x04)
        {
            alarmStr += tr("不稳定");
        }
        if(detAlarm&0x08)
        {
            alarmStr += tr("通讯故障");
        }
        if(detAlarm&0x10)
        {
            alarmStr += tr("配置故障");
        }
        if(detAlarm&0x80)
        {
            alarmStr += tr("未知故障");
        }
        alarmStr += tr(" 感应线圈:");
        if(coilAlarm&0x01)
        {
            alarmStr += tr("未知故障");
        }
        if(coilAlarm&0x02)
        {
            alarmStr += tr("watchdog故障");
        }
        if(coilAlarm&0x04)
        {
            alarmStr += tr("线圈开路");
        }
        if(coilAlarm&0x08)
        {
            alarmStr += tr("电感不足");
        }
        if(coilAlarm&0x10)
        {
            alarmStr += tr("感应变化量超限");
        }
        qDebug()<<alarmStr;
    }
    else
    {
        m_bRed = false;
    }
    this->update();
}

void DetIcon::emitLeaveContent()
{
    emit leaveContent(this);
}

void DetIcon::timerEvent(QTimerEvent *t)
{
    if(m_bTimer)
    {
        m_bTimer = false;
        this->killTimer(t->timerId());
         qDebug()<<"deticon kill timer 600";
        //emit mouseStatus(false,true,m_ucDetNo,QPoint(0,0));
    }


    if(m_bIncludeMouse)
    {
        m_bSend = true;
//        emit mouseStatus(true,true,m_ucDetNo,this->mapToGlobal(this->geometry().topLeft()));
        //qDebug()<<"detector:"<<m_ucDetNo<<"mouse enter"<<this->mapToGlobal(this->geometry().topRight())<<this->geometry().topRight();
    }
}

void DetIcon::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        m_posStart = ev->pos();
        m_bDrag = false;
    }
}

void DetIcon::mouseReleaseEvent(QMouseEvent *e)
{
    if(!m_bDrag)
    {
        emit mouseStatus(true,true,m_ucDetNo,this->mapToGlobal(e->pos()));
    }
}

void DetIcon::clearState()
{
    m_bGreen = false;
    m_bRed = false;
    this->update();
}

//-------------------------------------------------------

DetContent::DetContent(QWidget *parent) :
    QDialog(parent)
{
//    m_ucDirection = 1;
//    m_sDegree = 0;
//    m_bPed = false;
    //m_pPix = NULL;
    m_bImg = false;
    this->setAcceptDrops(true);
    QPalette p = this->palette();
    p.setColor(QPalette::Background,Qt::gray);
    this->setPalette(p);
    m_ucDirNo = 0;
    m_pDetBase = NULL;
    m_pGLayout = NULL;

    m_bIncludeMouse = false;
    m_bSend = false;
    m_ListIcon<<NULL<<NULL<<NULL<<NULL;
}

DetContent::~DetContent()
{
    qDebug()<<"~DetContent";
}

void DetContent::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
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


void DetContent::dragMoveEvent(QDragMoveEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
    {
        if(children().contains(e->source()))
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
}


void DetContent::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
    {

        QByteArray data = e->mimeData()->data("Drag-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        int i;
        DetIcon *icon;
        stream>>i;
        icon = static_cast<DetIcon*>((void*)(i));
        if(children().contains(e->source()))
        {
            e->setDropAction(Qt::MoveAction);
            //m_pLayout->addWidget(icon);
            //addIcon(icon);

            //qDebug()<<"move";
        }
        else
        {
            e->acceptProposedAction();
            //m_pLayout->addWidget(icon);

           //icon->move(150,150);
            //qDebug()<<"copy"<<e->pos()<<this->mapToGlobal(e->pos())<<this->mapToParent(e->pos());
        }
        bool bFlagDir = m_ucDirection%2==0?false:true;//南北为true 东西为false
        int position = bFlagDir?e->pos().y():e->pos().x();
        addIcon(icon,position/10);
        //qDebug()<<"dropevent"<<m_pLayout->count();
        //        delete e->mimeData();

    }
    else
    {
        e->ignore();
    }

}

void DetContent::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();

    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.rotate(m_sDegree);
    if(m_bPed)
    {
        painter.translate(57,7);
    }
    else
    {
        switch(m_ucDirection)
        {
        case 1:
           // painter.translate(-81,0);
            break;
        case 2:
            painter.translate(0,-80);
            break;
        case 3:
            painter.translate(-21,-80);
            break;
        case 4:
            painter.translate(-21,0);
            break;
        default:
            break;
        }

        //painter.translate(100,100);
    }


    if(m_bImg)
    {
        if(!m_bPed)
        {
            int base = 0;
            //painter.drawPixmap(0,0,21,80,*m_pPix);
            if(m_ucDirection==2||m_ucDirection==3)
            {
                base = -20;
            }
            painter.drawImage(0,base,m_img);
            int r = 8;
            int d = 25;
            QPen p(Qt::DotLine);
            painter.setPen(p);
            painter.drawEllipse(r/2,base+r,r,r);
            painter.drawEllipse(r/2,base+r+d,r,r);
            painter.drawEllipse(r/2,base+r+d+d,r,r);
            painter.drawEllipse(r/2,base+r+d+d+d,r,r);
            //painter.drawRect(0,0,21,80);
        }
        else
        {
            painter.drawImage(0,0,m_img);
        }
    }

    //qDebug()<<"m_sDegree:"<<m_sDegree;


    painter.restore();
}

void DetContent::enterEvent(QEvent *)
{

    //qDebug()<<"load:"<<(m_ucDirection-1)*4+m_ucType<<"mouse enter"<<this->mapToGlobal(this->geometry().topRight())<<this->geometry().topRight();
    this->startTimer(2000);
    m_bIncludeMouse = true;

}

void DetContent::leaveEvent(QEvent *)
{

    //qDebug()<<"load:"<<(m_ucDirection-1)*4+m_ucType<<"mouse leave";
    m_bIncludeMouse = false;
    if(m_bSend)
    {
        m_bSend = false;
        //emit mouseStatus(false,false,m_ucDirNo,QPoint(0,0));
    }
}

void DetContent::mousePressEvent(QMouseEvent *e)
{
//    if(ev->button()==Qt::LeftButton)
//    {
//        m_posStart = ev->pos();
//        m_bDrag = false;
//    }
    emit mouseStatus(true,false,m_ucDirNo,this->mapToGlobal(e->pos()));
}
/*
 no 为方向号 1-16
*/
void DetContent::setDirNo(quint8 no)
{
    m_ucDirNo = no;
}

quint8 DetContent::getDirNo()
{
    return m_ucDirNo;
}

void DetContent::setData(quint8 dir, quint8 type,quint8 index,quint8 phase)
{
    m_ucPhase = phase;
    m_ucDirection = dir;
    m_ucType = type;
    m_ucLoadIndex = index;

    if(type>0)
    {
        QString str = tr(":Files/images/null");
        switch(type)
        {
        case 1:
            str += tr("l.jpg");
            m_bPed = false;
            break;
        case 2:
            str += tr("s.jpg");
            m_bPed = false;
            break;
        case 3:
            str += tr("r.jpg");
            m_bPed = false;
            break;
        case 4:
            str += tr("ped.jpg");
            m_bPed = true;
            break;
        default:
            str += tr("s.jpg");
            break;
        }
        //QImage img;
        if(m_img.load(str))
        {
            //m_pPix = &QPixmap::fromImage(m_img);
            m_bImg = true;
            qDebug()<<"load img succ"<<str;
        }
        else
        {
           m_bImg = false;
            qDebug()<<"load img errer";
        }

    }
    else
    {
        m_bImg = false;
    }
int space = 0;
int iconLen = 100;
    switch(dir)
    {
    case 1:
        m_sDegree = 0;//北
        if(!m_bPed)
        {
            this->setFixedSize(21,iconLen);
            m_pLayout = new QVBoxLayout(this);
            m_pLayout->setDirection(QBoxLayout::BottomToTop);
           // m_pLayout->setContentsMargins(0,40,22,190);
             m_pLayout->setSpacing(space);

        }
        else
        {
            this->setFixedSize(114,14);
        }
        break;
    case 2:
        m_sDegree = 90;//东
        if(!m_bPed)
        {
            this->setFixedSize(iconLen,21);
            m_pLayout = new QHBoxLayout(this);
            m_pLayout->setDirection(QBoxLayout::LeftToRight);
            m_pLayout->setContentsMargins(0,0,81,22);
            m_pLayout->setSpacing(space);
        }
        else
        {
            this->setFixedSize(14,114);
        }
        break;
    case 3:
        m_sDegree = 180;
        if(!m_bPed)
        {
            this->setFixedSize(22,iconLen);
            m_pLayout = new QVBoxLayout(this);
            m_pLayout->setDirection(QBoxLayout::TopToBottom);
            m_pLayout->setContentsMargins(0,0,21,80);
            m_pLayout->setSpacing(space);
        }
        else
        {
            this->setFixedSize(114,14);
        }
        break;
    case 4:
        m_sDegree = 270;
        if(!m_bPed)
        {
            this->setFixedSize(iconLen,22);
            m_pLayout = new QHBoxLayout(this);
            m_pLayout->setDirection(QBoxLayout::RightToLeft);
            m_pLayout->setContentsMargins(0,5,80,21);
            m_pLayout->setSpacing(space);
        }
        else
        {
            this->setFixedSize(14,114);
        }
        break;
    default:
        //setFixedSize(160,100);
        m_pGLayout = new QGridLayout(this);
        m_pGLayout->setSpacing(5);
        //m_pGLayout->setContentsMargins(0,50,200,200);
        break;
    }
    //setFixedSize(200,200);
}

void DetContent::addIcon(DetIcon *i,quint8 pos,bool b)
{
    //qDebug()<<"addIcon";
    if(m_pGLayout==NULL)
    {
        qDebug()<<"addIcon layout";
        m_pLayout->addWidget(i);
        m_pLayout->removeWidget(i);

        //qDebug()<<"pos :"<<position/10;

            switch(pos)
            {
            case 0:
            case 1:
            case 2:
                changeListIcon(m_ucDirection,1,i,b);
                break;
            case 3:
            case 4:

                changeListIcon(m_ucDirection,2,i,b);
                break;
            case 5:
            case 6:
            case 7:

                changeListIcon(m_ucDirection,3,i,b);
                break;
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                //i->move(this->mapFromGlobal(QPoint(0,75)));
               changeListIcon(m_ucDirection,4,i,b);
                break;
            default:
                break;
            }
    }
    else
    {
        qDebug()<<"addIcon grid";
        quint8 no = i->getDetectorNo();
        if(no>0)
        {
            m_pGLayout->addWidget(i,no/7,no%7);
        }
        if(b)
        {
            i->emitLeaveContent();
            setIconData(i->getDetectorNo());
        }
        else
        {
//            if(no>0&&no<(MAX_DETECTORNUM+1)&&m_pDataProcess->m_pTscInfo!=NULL)
//            {
//                Detector_Table *p =  m_pDataProcess->m_pTscInfo->tbDetector+no-1;
//                p->bCallPhase = 0;
//            }
        }

    }

    emit detChangePos(i->getDetectorNo());
}

//void DetContent::mousePressEvent(QMouseEvent *e)
//{
//   //qDebug()<<"pos"<<e->pos();
//}

void DetContent::setContentData()
{
//    //----------------修改请求相位 所属车道 及位置顺序
//    QList<DetIcon*> list = this->findChildren<DetIcon*>();
//    int cnt = list.count();
//     qDebug()<<"cnt:"<<cnt;
//    for(int i=0;i<cnt;i++)
//    {
//        quint8 no = list[i]->getDetectorNo();
//        if(m_pDetBase!=NULL&&no>0)
//        {
//            Detector_Table *p = m_pDetBase+no-1;
//            p->bCallPhase = m_ucPhase;
//            p->bOption&=0x07;
//            p->bOption|=(m_ucLoadIndex<<6);
//            p->bOption|=(((quint8)i)<<3);
//        }
//        qDebug()<<"i:"<<i<<no;
//    }


}

void DetContent::setDetBase(PDataProcess *p)
{
    m_pDataProcess = p;
}

/*
 输入参数：dir 方向 1：北 2：东 3：南 4：西
 pos: 检测器位置 离（0，0）的距离 值为 1，2，3，4
*/
void DetContent::changeListIcon(quint8 dir, quint8 pos,DetIcon* i,bool b)
{
    if(dir<1||dir>4||pos<1||pos>4)
    {
        qDebug()<<"changeListIcon err";
        return;
    }
    int index;
    bool bFlagDir;//南北为true 东西为false
    switch(dir)
    {
    case 1:
        bFlagDir = true;
        index = 4-pos;
        break;
    case 4:
        bFlagDir = false;
        index = 4-pos;
        break;
    case 2:
        bFlagDir = false;
        index = pos-1;
        break;
    case 3:
        bFlagDir = true;
        index = pos-1;
        break;
    default:

        break;
    }

    if(m_ListIcon[index]!=NULL)
    {
        emit removeIcon(m_ListIcon[index]);
    }
    m_ListIcon[index] = i;
    i->emitLeaveContent();
    connect(i,SIGNAL(leaveContent(DetIcon*)),this,SLOT(on_IconLeave(DetIcon*)));
    //qDebug()<<"add icon connect";
    if(bFlagDir)
    {
        //qDebug()<<"pos::"<<pos;
        i->move(0,(pos-1)*25);
    }
    else
    {
        i->move((pos-1)*25,0);
    }
    if(b)
    {
        setIconData(i->getDetectorNo(),index);
    }

}

/*
 设置检测器 请求相位phase ，第几车道load，前后位置pos;
*/
void DetContent::setIconData(quint8 iconNo,quint8 index)
{
    if(iconNo<1||iconNo>32)
    {
        qDebug()<<"set icon data err";
        return;
    }
    m_pDetBase = m_pDataProcess->m_pTscInfo->tbDetector;
    Detector_Table *p = m_pDetBase+iconNo-1;
    p->bCallPhase = m_ucPhase;
    p->bOption &= 0x3f;//bit6 bit7 用于车道号
    //qDebug()<<"loadIndex:"<<m_ucLoadIndex;
    m_ucLoadIndex<<=6;
    p->bOption |= m_ucLoadIndex;
    switch(index)//战术 感应 战略 为单选
    {
    case 0://速度检测器
        //qDebug()<<tr("检测器：")<<iconNo<<tr(":位置1");
        p->bOption|=0x10;//速度
        p->bProperty&=0x8f;//去掉战略检测器 去掉 感应检测器
        //p->bProperty&=0xbf;//
        p->bProperty|=0x20;//选上战术
        break;
    case 1:
        //qDebug()<<tr("检测器：")<<iconNo<<tr(":位置2");
        p->bOption&=0xef;// 去掉 速度
        p->bProperty&=0x8f;
       // p->bProperty&=0xef;//去掉战略检测器
        p->bProperty|=0x20;//选上战术
        break;
    case 2:
       // qDebug()<<tr("检测器：")<<iconNo<<tr(":位置3");
        p->bOption&=0xef;// 去掉 速度
        p->bProperty&=0x8f;//去掉战略检测器 去掉战术
        //p->bProperty|=0xdf;//
        p->bProperty|=0x40;//选上感应
        break;
    case 3://战略检测器
       // qDebug()<<tr("检测器：")<<iconNo<<tr(":位置4");
        p->bOption&=0xef;// 去掉 速度
        p->bProperty&=0x8f;//去掉 战术 感应
        //p->bProperty|=0xdf;//去掉战术
        p->bProperty|=0x10;//选上战略检测器
        break;
    default:
        break;
    }
}

void DetContent::timerEvent(QTimerEvent *e)
{
    this->killTimer(e->timerId());
    if(m_bIncludeMouse)
    {
        m_bSend = true;
        //emit mouseStatus(true,false,m_ucDirNo,this->mapToGlobal(this->geometry().topLeft()));
    }
}

void DetContent::on_IconLeave(DetIcon *icon)
{
    for(int i=0;i<4;i++)
    {
        if(m_ListIcon[i]==icon)
        {
            m_ListIcon[i] = NULL;
            icon->disconnect(this);
            qDebug()<<"leave content disconnect";
        }
    }
}
//------------------------------------------------------
//----------------------------------------------------------------------------------------
DetParaDlg::DetParaDlg(QWidget *parent):
        QWidget(parent)
{
    init();
//    m_pDirBase = NULL;
//    m_pDetBase = NULL;
    //this->setMouseTracking(true);
    m_bInit = false;
    m_bDataChange = false;
    m_bClick = false;
    connect(confirmBtn,SIGNAL(clicked()),this,SLOT(on_confirmBtn()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(on_cancelBtn()));
    connect(cbDetNo,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbDetNoChange(int)));
//    connect(cbDetNo,SIGNAL(highlighted(int)),this,SLOT(on_cbHightLight(int)));
//    connect(cbDir,SIGNAL(highlighted(int)),this,SLOT(on_cbHightLight(int)));
//    connect(cbPhase,SIGNAL(highlighted(int)),this,SLOT(on_cbHightLight(int)));
    connect(cbDirLoad,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbDirNoChange(int)));
    connect(cbPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dataChange()));
    for(int i=0;i<6;i++)
    {
        connect(listOptionCheck[i],SIGNAL(clicked()),this,SLOT(on_dataChange()));
        if(i<5)
        {
            connect(listTypeCheck[i],SIGNAL(clicked()),this,SLOT(on_dataChange()));
            if(i<3)
            {
                connect(listTypeRadio[i],SIGNAL(clicked()),this,SLOT(on_dataChange()));
            }
        }
    }
    connect(cbDir,SIGNAL(activated(int)),this,SLOT(on_dataChange()));

    connect(sbValidTime,SIGNAL(editingFinished()),this,SLOT(on_dataChange()));
    connect(sbValidTime,SIGNAL(valueChanged(int)),this,SLOT(on_dataChange()));

    connect(leSaturation,SIGNAL(textChanged(QString)),this,SLOT(on_dataChange()));

    connect(sbOccupancy,SIGNAL(editingFinished()),this,SLOT(on_dataChange()));
    connect(sbOccupancy,SIGNAL(valueChanged(int)),this,SLOT(on_dataChange()));

    connect(sbLoadNum,SIGNAL(valueChanged(int)),this,SLOT(on_dataChange()));
    connect(sbLoadNum,SIGNAL(editingFinished()),this,SLOT(on_dataChange()));
    //connect(cbDirLoad,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dataChange()));
}

DetParaDlg::~DetParaDlg()
{
    qDebug()<<"~DetParaDlg";
}

void DetParaDlg::init()
{
//    QString str = QObject::tr("what is this");
//    this->setWhatsThis(str);
//    QString strTool = QObject::tr("tool tip");
//    QString strStatus = QObject::tr("status tip");
//    this->setToolTip(strTool);
//    this->setStatusTip(strStatus);
    this->setAttribute(Qt::WA_MSWindowsUseDirect3D);
//    detWidget = new QWidget(this);
//    typeWidget = new QWidget(this);
//    optionWidget = new QWidget(this);

    QLabel *lbDetNo = new QLabel(tr("检测器号:"));
    QLabel *lbPhase = new QLabel(tr("请求相位:"));
    gbAdvanced = new QGroupBox(tr("高级参数"));
    btnMore = new QPushButton(tr("更多>>"));
    QGroupBox *gbType = new QGroupBox(tr("类型参数:")/*,typeWidget*/);
    QLabel *lbDir = new QLabel(tr("方向:"));
    QLabel *lbValidTime = new QLabel(tr("有效时间"));
    QGroupBox *gbOption = new QGroupBox(tr("选项参数:")/*,optionWidget*/);
    QLabel *lbSaturation = new QLabel(tr("饱和流量:"));
    QLabel *lbOccupancy = new QLabel(tr("饱和占有率:"));
    QLabel *lbDirLoad = new QLabel(tr("车道方向"));
    QLabel *lbLoadNum = new QLabel(tr("车道数:"));

    QGroupBox *detGroup = new QGroupBox(/*detWidget*/);
//detGroup->setMaximumWidth(160);

    cbDetNo = new QComboBox;
    QStringList listDetNo;
    QStringList listPhase;
    QStringList listDirLoad;
    listDetNo<<tr(" ");
    listPhase<<tr(" ");
    listDirLoad<<tr(" ")<<tr("北左")<<tr("北直")<<tr("北右")<<tr("北人行")<<tr("东左")<<tr("东直")<<tr("东右")<<tr("东人行")<<tr("南左")<<tr("南直")<<tr("南右")<<tr("南人行")<<tr("西左")<<tr("西直")<<tr("西右")<<tr("西人行");
    for(int i=0;i<32;i++)
    {
        listDetNo<<tr("检测器")+tr("%1").arg(i+1);
        if(i<16)
        {
            listPhase<<tr("相位")+tr("%1").arg(i+1);
        }
    }
    cbDetNo->addItems(listDetNo);

    cbPhase = new QComboBox;
    cbPhase->addItems(listPhase);

    cbDirLoad = new QComboBox;
    cbDirLoad->addItems(listDirLoad);

    QStringList typeRadioStr;
    typeRadioStr<<tr("战略")<<tr("战术")<<tr("感应");
    for(int i=0;i<3;i++)
    {
        QRadioButton *rb = new QRadioButton(typeRadioStr[i]);
        listTypeRadio<<rb;
    }

    QStringList typeCheckStr;
    typeCheckStr<<tr("机动车")<<tr("自行车")<<tr("公交车")<<tr("行人按钮")<<tr("请求");
    for(int i=0;i<5;i++)
    {
        QCheckBox *cb = new QCheckBox(typeCheckStr[i]);
        listTypeCheck<<cb;
    }

    cbDir = new QComboBox;
    QStringList listDir;
    listDir<<tr(" ")<<tr("北")<<tr("东北")<<tr("东")<<tr("东南")<<tr("南")<<tr("西南")<<tr("西")<<tr("西北");
    cbDir->addItems(listDir);

    sbValidTime = new QSpinBox;
    sbValidTime->setRange(0,255);

    QStringList listOption;
    listOption<<tr("区分车型")<<tr("关键车道")<<tr("流量")<<tr("占有率")<<tr("速度")<<tr("排队长度");
    for(int i=0;i<6;i++)
    {
        QCheckBox *opCb = new QCheckBox(listOption[i]);
        listOptionCheck<<opCb;
    }

    leSaturation = new QLineEdit();

    sbOccupancy = new QSpinBox;
    sbOccupancy->setRange(0,200);

    sbLoadNum = new QSpinBox;
    sbLoadNum->setRange(1,4);
    //------------------------
    m_gbDet = new QGroupBox;
    m_gbDet->setMaximumWidth(165);

    m_gbLoad = new QGroupBox;
    m_gbLoad->setVisible(false);
    //-------------------
    QVBoxLayout *lbVLayout = new QVBoxLayout;
    QVBoxLayout *rightVLayout = new QVBoxLayout;
    QHBoxLayout *hLayoutBtn = new QHBoxLayout;
    QHBoxLayout *hLayoutMore = new QHBoxLayout(gbAdvanced);
    hLayoutMore->setMargin(0);
    QVBoxLayout *vLayoutLB = new QVBoxLayout;
    QVBoxLayout *vLayoutRight = new QVBoxLayout;

    vLayoutLB->setSpacing(1);
    vLayoutRight->setSpacing(1);
    lbVLayout->setSpacing(1);
    rightVLayout->setSpacing(1);

    QVBoxLayout *vLayoutDetGroup = new QVBoxLayout(detGroup);
    vLayoutDetGroup->setSpacing(1);
    vLayoutDetGroup->setMargin(3);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vDetLayout = new QVBoxLayout(m_gbDet);
    QVBoxLayout *lbLoadLayout = new QVBoxLayout;
    QVBoxLayout *rightLoadLayout = new QVBoxLayout;
    QHBoxLayout *hLoadLayout = new QHBoxLayout(m_gbLoad);
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    QGridLayout *typeGLayout = new QGridLayout(gbType);
    QGridLayout *optionGLayout = new QGridLayout(gbOption);

    typeGLayout->setSpacing(1);
    typeGLayout->setMargin(3);
    optionGLayout->setSpacing(1);
    optionGLayout->setMargin(3);

    for(int i=0;i<6;i++)
    {
        if(i<5)
        {
            typeGLayout->addWidget(listTypeCheck[i],i/2+2,i%2);
            if(i<3)
            {
                typeGLayout->addWidget(listTypeRadio[i],i/2,i%2);
            }
        }
        optionGLayout->addWidget(listOptionCheck[i],i/2,i%2);
    }

    lbVLayout->addWidget(lbDetNo);
    lbVLayout->addWidget(lbPhase);

    //lbVLayout->addWidget(lbLoadNum);

    rightVLayout->addWidget(cbDetNo);
    rightVLayout->addWidget(cbPhase);
    hLayout->addLayout(lbVLayout);
    hLayout->addLayout(rightVLayout);

    vLayoutLB->addWidget(lbDir);
    vLayoutLB->addWidget(lbValidTime);
    vLayoutLB->addWidget(lbSaturation);
    vLayoutLB->addWidget(lbOccupancy);
    vLayoutRight->addWidget(cbDir);
    vLayoutRight->addWidget(sbValidTime);
    vLayoutRight->addWidget(leSaturation);
    vLayoutRight->addWidget(sbOccupancy);
    //rightVLayout->addWidget(sbLoadNum);


    hLayoutMore->addLayout(vLayoutLB);
    hLayoutMore->addLayout(vLayoutRight);

    hLayoutBtn->addStretch();
    hLayoutBtn->addWidget(btnMore);
    vLayoutDetGroup->addLayout(hLayout);
    vLayoutDetGroup->addLayout(hLayoutBtn);
    vLayoutDetGroup->addWidget(gbAdvanced);
    gbAdvanced->setVisible(false);
//------------------------------------------
    confirmBtn = new QPushButton(tr("确定"));
    cancelBtn = new QPushButton(tr("取消"));
    QHBoxLayout *btnHLayout = new QHBoxLayout;
    btnHLayout->addStretch();
    btnHLayout->addWidget(confirmBtn);
    btnHLayout->addWidget(cancelBtn);
    btnHLayout->addStretch();
//-------------------------------------------------
    vDetLayout->addWidget(detGroup);
    vDetLayout->addWidget(gbType);
    vDetLayout->addWidget(gbOption);

vDetLayout->setMargin(0);
vDetLayout->setSpacing(2);


    lbLoadLayout->addWidget(lbDirLoad);
    lbLoadLayout->addWidget(lbLoadNum);
    rightLoadLayout->addWidget(cbDirLoad);
    rightLoadLayout->addWidget(sbLoadNum);

    sbLoadNum->setEnabled(false);

    hLoadLayout->addLayout(lbLoadLayout);
    hLoadLayout->addLayout(rightLoadLayout);

    mainVLayout->addWidget(m_gbDet);
    mainVLayout->addWidget(m_gbLoad);
//    mainVLayout->addLayout(btnHLayout);
    mainVLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainVLayout->setSpacing(0);
//    QPalette p = this->palette();
//    p.setColor(QPalette::Background,Qt::transparent);
//    this->setPalette(p);
//    this->setAutoFillBackground(true);

    connect(btnMore,SIGNAL(clicked()),this,SLOT(on_btnMore()));
}

void DetParaDlg::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
//    m_pDirBase = p->m_pTscInfo->tbPhaseMap;
//    m_pDetBase = p->m_pTscInfo->tbDetector;
}

void DetParaDlg::enterEvent(QEvent *)
{
    //qDebug()<<"mouse enter dlg";
    if(m_bClick)
    {
        m_bClick = false;
        return;
    }
   // emit mouseStatus(true);
}

void DetParaDlg::leaveEvent(QEvent *)
{
  // qDebug()<<"mouse leave dlg";


//   if(!m_bClick)
//   {
//       emit mouseStatus(false);
//   }
    //
}

void DetParaDlg::closeEvent(QCloseEvent *)
{
    emit closeDlg();
}

void DetParaDlg::setData(quint8 detNo, quint8 loadNo)
{

    //qDebug()<<"m_ucDetNo:"<<m_ucDetNo;
    getDataFromInterfase();
    clearInterface();

    m_ucDirNo = loadNo;
    m_ucDetNo = detNo;
    if(detNo!=0)
    {
        showData(true);
    }
    else if(loadNo!=0)
    {
        showData(false);
    }

}

void DetParaDlg::clearInterface()
{
//    cbDetNo->clear();
//    cbPhase->clear();
qDebug()<<"clear data";
    m_bInit = false;
//    m_bDataChange = false;
    cbDetNo->setCurrentIndex(0);
    cbPhase->setCurrentIndex(0);
    int trbCnt = listTypeRadio.count();
    for(int i=0;i<trbCnt;i++)
    {
        listTypeRadio[i]->setChecked(false);
    }
    listTypeCheck;
    int tcbCnt = listTypeCheck.count();
    for(int i=0;i<tcbCnt;i++)
    {
        listTypeCheck[i]->setChecked(false);
    }
    cbDir->setCurrentIndex(0);
    //cbDir->clear();
    sbValidTime->clear();
    int optionCnt = listOptionCheck.count();
    for(int i=0;i<optionCnt;i++)
    {
      listOptionCheck[i]->setChecked(false);
    }
    leSaturation->clear();;
    sbOccupancy->clear();
    //sbLoadNum->clear();
    cbDirLoad->setCurrentIndex(0);
    m_bInit = true;
}

void DetParaDlg::showData(bool b)
{
    if(b)
    {
        if(m_ucDetNo>0&&m_ucDetNo<33)
        {
            //qDebug()<<"det no:"<<m_ucDetNo;
            cbDetNo->setCurrentIndex(m_ucDetNo);
        }

        m_gbDet->show();
        m_gbLoad->hide();
    }
    else
    {
        if(m_ucDirNo>0&&m_ucDirNo<17)
        {
            cbDirLoad->setCurrentIndex(m_ucDirNo);

        }

        m_gbDet->hide();
        m_gbLoad->show();
    }
}

void DetParaDlg::getDataFromInterfase()
{
    if(m_bDataChange)
    {
        qDebug()<<"send detpara data";
        m_bDataChange = false;
        if(m_ucDetNo>0&&m_ucDetNo<49&&!m_gbDet->isHidden())
        {
            Detector_Table *p = m_pDataProcess->m_pTscInfo->tbDetector+m_ucDetNo-1;

            p->bCallPhase = cbPhase->currentIndex();

            int dirIndex = cbDir->currentIndex();
            quint8 dir = 0x01;
            if(dirIndex>0&&dirIndex<9)
            {
                p->bDirection = dir<<(dirIndex-1);
            }
            else
            {
                p->bDirection = 0;
            }

            p->bDelayTime = sbValidTime->value();

            p->uLaneSaturation = leSaturation->text().toInt();

            p->bSaturationOccupancy = sbOccupancy->value();

            p->bOption &= 0xc0;
            p->bProperty = 0;
            for(int i=0;i<6;i++)
            {
                if(listOptionCheck[i]->isChecked())
                {
                    p->bOption |= (0x01<<i);
                }

                if(i<5)
                {
                    if(listTypeCheck[i]->isChecked())
                    {
                        if(i==4)
                        {
                            p->bProperty |= 0x80;
                        }
                        else
                        {
                            p->bProperty |= (0x01<<i);
                        }
                    }
                    if(i<3)
                    {
                        if(listTypeRadio[i]->isChecked())
                        {
                            p->bProperty |= (0x01<<(4+i));
                            //qDebug()<<"raido check"<<i<<p->bProperty;
                        }
                    }
                }
            }
            //m_pDataProcess->sendDetectorToLib();
        }
        else if(m_ucDirNo>0&&m_ucDirNo<17&&!m_gbLoad->isHidden())
        {
            PhaseMap_Table *p = m_pDataProcess->m_pTscInfo->tbPhaseMap+m_ucDirNo-1;
            p->bLaneNum = sbLoadNum->value();
            //m_pDataProcess->sendPhaseMapToLib();
        }
    }


}

//void DetParaDlg::mousePressEvent(QMouseEvent *)
//{
//    qDebug()<<"mouse click";
//    m_bClick = true;
//}

//void DetParaDlg::mouseMoveEvent(QMouseEvent *e)
//{
//    qDebug()<<"mouse move "<<e->pos();
//}

void DetParaDlg::on_confirmBtn()
{
    this->close();
    getDataFromInterfase();
    m_pDataProcess->sendPhaseMapToLib();
    m_pDataProcess->sendDetectorToLib();
}

void DetParaDlg::on_cancelBtn()
{
    this->close();
}

void DetParaDlg::on_cbDetNoChange(int index)
{
    getDataFromInterfase();
    if(index<1||index>48)
    {
        qDebug()<<"index error"<<index;
        clearInterface();
        this->setWindowTitle(tr(""));
        return;
    }
//    qDebug()<<"index det no"<<index;
//    qDebug()<<"phase"<<p->bCallPhase;
//    qDebug()<<"type"<<tr("%1").arg();
//    qDebug()<<"index det no"<<index;
//    qDebug()<<"index det no"<<index;
    m_bInit = false;
    this->setWindowTitle(cbDetNo->currentText());
    m_ucDetNo = index;
//    m_bDataChange = false;
    Detector_Table *p = m_pDataProcess->m_pTscInfo->tbDetector+index-1;
    //cbDetNo->setcu;
    cbPhase->setCurrentIndex(p->bCallPhase);

    quint8 type = p->bProperty;
    quint8 dir = p->bDirection;
    quint8 option = p->bOption;
    if(dir==0)
    {
        cbDir->setCurrentIndex(0);
    }
    for(int i=0;i<8;i++)
    {
        if(((type>>i)&0x01)==1)
        {
//            switch(i)
//            {
//            case 4:
//                qDebug()<<tr("战略检测器");
//                break;
//            case 5:
//                qDebug()<<tr("战术检测器");
//                break;
//            case 6:
//                qDebug()<<tr("感应检测器");
//                break;
//            default:
//                break;
//            }
            if(i<4)
            {
                listTypeCheck[i]->setChecked(true);
            }
            else if(i<7)
            {
                listTypeRadio[i-4]->setChecked(true);
            }
            else
            {
                listTypeCheck[4]->setChecked(true);
            }
         }
        if(((dir>>i)&0x01)==1)
        {
            cbDir->setCurrentIndex(i+1);
        }
        if(((option>>i)&0x01)==1)
        {
            if(i<6)
            {
                listOptionCheck[i]->setChecked(true);
            }

        }
    }

    sbValidTime->setValue(p->bDelayTime);

    leSaturation->setText(QString::number(p->uLaneSaturation));
    sbOccupancy->setValue(p->bSaturationOccupancy);
    m_bInit = true;
//    sbLoadNum->clear();
}

void DetParaDlg::on_cbDirNoChange(int index)//从1起
{
    getDataFromInterfase();
    m_bInit = false;
    if(index>0&&index<17)
    {
        this->setWindowTitle(cbDirLoad->currentText());
        m_ucDirNo = index;
//        sbLoadNum->setValue((m_pDataProcess->m_pTscInfo->tbPhaseMap+index-1)->bLaneNum);
        sbLoadNum->setValue(m_pDataProcess->m_ListLoadNum[index-1]);
    }
    else
    {
        this->setWindowTitle(tr(""));
        sbLoadNum->clear();
    }
    m_bInit = true;
}

void DetParaDlg::on_dataChange()
{
    if(m_bInit)
    {
        m_bDataChange = true;
        getDataFromInterfase();
        qDebug()<<tr("data change");
    }

}

void DetParaDlg::on_detChangePos(int detNo)
{
    if(detNo>0&&detNo<(MAX_DETECTORNUM+1))
    {
        if(cbDetNo->currentIndex()==detNo)
        {
            on_cbDetNoChange(detNo);
        }
        else
        {
            cbDetNo->setCurrentIndex(detNo);
        }

    }
}

void DetParaDlg::on_btnMore()
{
    if(gbAdvanced->isVisible())
    {
        gbAdvanced->setVisible(false);
        btnMore->setText(tr("更多>>"));
    }
    else
    {
        gbAdvanced->setVisible(true);
        btnMore->setText(tr("<<隐藏"));
    }
}

//void DetParaDlg::on_cbHightLight(int)
//{
//    qDebug()<<"hight light";
//    m_bClick = true;
//}
//---------------------------------------------------


DetWidget::DetWidget(QWidget *dlgParent,QWidget *parent) :
    QWidget(parent)
{
    QPalette p = this->palette();
    p.setColor(QPalette::Background,Qt::green);
    this->setPalette(p);
    //this->move(-50,-50);
    this->setFixedSize(500,500);

    int TRANS = -60;
    m_pDetBase = NULL;
    m_bAutoStatus = false;
    m_bAutoAlarm = false;

    m_pDetPara = new DetParaDlg(dlgParent);
    for(int i=0;i<5;i++)
    {
        QLabel *group = new QLabel(this);


        if(i==0)//放在中间
        {
            group->resize(200,200);
            QHBoxLayout *mLayout = new QHBoxLayout(group);
            DetContent *middle = new DetContent();
            middle->setData(0);
            //middle->setDetBase(m_pDataProcess->m_pTscInfo->tbDetector);
            m_ListLoad<<middle;
            mLayout->addWidget(m_ListLoad[0]);
            group->move(200+TRANS,200+TRANS);
            connect(middle,SIGNAL(detChangePos(int)),m_pDetPara,SLOT(on_detChangePos(int)));
        }
        else if(i==1)
        {
            group->setFixedSize(200,130);
            QHBoxLayout *nLayout = new QHBoxLayout(group);
            nLayout->setDirection(QBoxLayout::RightToLeft);
            group->move(200+TRANS,50+TRANS);

        }
        else if(i==2)
        {
            group->setFixedSize(130,200);
            QVBoxLayout *eLayout = new QVBoxLayout(group);
            eLayout->setDirection(QBoxLayout::BottomToTop);
            group->move(450+TRANS,200+TRANS);

        }
        else if(i==3)
        {
            group->setFixedSize(200,130);
            QHBoxLayout *sLayout = new QHBoxLayout(group);
            sLayout->setDirection(QBoxLayout::LeftToRight);
            group->move(200+TRANS,450+TRANS);

        }
        else if(i==4)
        {
            group->setFixedSize(130,200);
            QVBoxLayout *wLayout = new QVBoxLayout(group);
            wLayout->setDirection(QBoxLayout::TopToBottom);
            group->move(50+TRANS,200+TRANS);

        }

        m_ListGroup<<group;
    }

//    m_pDetPara = NULL;
    m_cMouseCnt = 0;


    init();
}

DetWidget::~DetWidget()
{
    if(m_bAutoStatus)
    {
        m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORSTS,0);
    }
    if(m_bAutoAlarm)
    {
        m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORWARN_TABLE,0);
    }
}

void DetWidget::init()
{
//    m_pDetPara = new DetParaDlg(this);
//    m_pDetPara->hide();
    connect(m_pDetPara,SIGNAL(closeDlg()),this,SLOT(on_closeDetParaDlg()));
    connect(m_pDetPara,SIGNAL(mouseStatus(bool)),this,SLOT(on_dlgMouseStatus(bool)));
//    QHBoxLayout *hLayout = new QHBoxLayout(this);
//    hLayout->addWidget(m_pDetPara);
//    hLayout->removeWidget(m_pDetPara);
}

void DetWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(-50,-50);
    QRectF rectGreen(0,0,600,600);

    painter.fillRect(rectGreen,QColor(7,14,30));

    QPen pen(Qt::darkRed);
    pen.setWidth(5);
    QBrush brushTemp(QColor(89,89,89));
    painter.setBrush(brushTemp);
    painter.setPen(pen);
    QPainterPath path;
    path.moveTo(200,0);
    path.lineTo(200,160);

    QRectF rect(QPoint(120,120),QSize(80,80));
    path.arcTo(rect,270*16,-90);

    path.lineTo(0,200);

    path.lineTo(0,400);
    path.lineTo(160,400);
    path.arcTo(120,400,80,80,90,-90);

    path.lineTo(200,600);
    path.lineTo(400,600);
    path.lineTo(400,440);
    path.arcTo(400,400,80,80,180,-90);
    path.lineTo(600,400);
    path.lineTo(600,200);
    path.lineTo(440,200);
    path.arcTo(400,120,80,80,270,-90);
    path.lineTo(400,0);
    path.lineTo(200,0);
    painter.drawPath(path);
}

void DetWidget::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;

    //m_pDetBase = p->m_pTscInfo->tbDetector;
    m_pListLoadNum = &(p->m_ListLoadNum);//当前节点
    m_pListPhase = &(p->m_ListPhaseMap);

    m_pDetPara->setDataProcess(p);

    if(m_ListLoad.count()>0)
    {
        m_ListLoad[0]->setDetBase(m_pDataProcess);
    }
    connect(p,SIGNAL(rcvDet()),this,SLOT(on_rcvDetector()));
    connect(p,SIGNAL(rcvDetAutoReport(unsigned char*,int)),this,SLOT(on_rcvDetStatus(unsigned char*,int)));
    connect(p,SIGNAL(rcvDetAlarm()),this,SLOT(on_rcvDetAlarm()));
}

void DetWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    m_bFlagShow = !m_bFlagShow;
    m_ListLoad[0]->setVisible(m_bFlagShow);
//    if(m_bFlagShow)
//    {
//        m_ListLoad[0]->show();
//        //m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORSTS,0);
//        //m_bAutoStatus = false;
//    }
//    else
//    {
//        m_ListLoad[0]->hide();
//        //m_pDataProcess->sendDetectorToLib();
//        //qDebug()<<"send det to lib";
//        //m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORSTS,10);
//        //m_bAutoStatus = true;
//    }
}

/*
*/
void DetWidget::rankDetector()
{
    if(m_pDataProcess!=NULL)
    {
        if(m_pDataProcess->m_pTscInfo==NULL)
        {
            return;
        }
        m_pDetBase = m_pDataProcess->m_pTscInfo->tbDetector;
//        qDebug()<<"m_pListPhase:"<<*m_pListPhase;
        for(int i=0;i<32;i++)
        {
            Detector_Table* p = m_pDetBase+i;
            quint8 phase = p->bCallPhase;

//            qDebug()<<"after detwidget before rank";
            int dirIndex = m_pListPhase->indexOf(phase);
            //qDebug()<<i+1<<"dirIndex"<<dirIndex;
            if(dirIndex>15||phase==0)
            {
                m_ListLoad[0]->addIcon(m_ListIcon[i],0,false);
//                qDebug()<<"dirindex>15 continue"<<i+1<<dirIndex<<"phase"<<phase;
                continue;
            }

            int dir = dirIndex/4;//方向 北0，东1，南2，西3
            bool bFlag = true;//北 西 为true
            if(dir==2||dir==1)
            {
                bFlag = false;
            }

            if(dirIndex!=-1)
            {
                quint8 loadNum = 0;
                for(int j=0;j<dirIndex;j++)
                {
                    if(j%4!=3)//去除人行 车道
                    {
                        loadNum += (*m_pListLoadNum)[j];//取得之前方向的 车道数
                        //qDebug()<<dirIndex<<"load num:"<<loadNum;
                    }

                }
                quint8 loadIndex = p->bOption>>6;//扩展 道路数的顺序号

                loadIndex+=loadNum;
                //qDebug()<<"load Index"<<loadIndex;
                quint8 pos=0;
                quint8 property = p->bProperty;
                if((property&0x10)!=0)
                {
                    if(bFlag)
                    {
                        pos = 1;//战略检测器 位置4
                    }
                    else
                    {
                        pos = 8;//战略检测器 位置4
                    }
                }
                else if((property&0x40)!=0)
                {
                    if(bFlag)
                    {
                        pos = 3;//感应检测器 位置3
                    }
                    else
                    {
                        pos = 5;//感应检测器 位置3
                    }

                }
                else if((property&0x20)!=0)
                {
                    if(((p->bOption)&0x10)!=0)//速度检测器 位置1
                    {
                        if(bFlag)
                        {
                            pos = 8;//战术 位置3
                        }
                        else
                        {
                            pos = 1;//战术检测器 位置3
                        }

                    }
                    else
                    {
                        if(bFlag)
                        {
                            pos = 5;//位置2
                        }
                        else
                        {
                            pos = 3;//
                        }

                    }
                }
                else
                {
                    m_ListLoad[0]->addIcon(m_ListIcon[i],0,false);
                    //qDebug()<<"det no:"<<i+1<<"middle";
                    //return;
                    continue;
                }
                //qDebug()<<"det:"<<i+1<<"phase:"<<phase<<"dirIndex:"<<dirIndex<<"LoadIndex"<<loadIndex<<"pos"<<pos;
                if(loadIndex+2>m_ListLoad.count())
                {
                    m_ListLoad[0]->addIcon(m_ListIcon[i],0,false);
                }
                else
                {
                    m_ListLoad[loadIndex+1]->addIcon(m_ListIcon[i],pos,false);//0位置 放中间容器
                }

            }
            else
            {
                m_ListLoad[0]->addIcon(m_ListIcon[i],0,false);
//                qDebug()<<"det no:"<<i+1<<"middle";

            }
        }
    }
}

void DetWidget::mouseMoveEvent(QMouseEvent *)
{
    //qDebug()<<"detwidget move"<<e->pos();
}

void DetWidget::timerEvent(QTimerEvent *e)
{//qDebug()<<"detwidget kill timer 700";
    this->killTimer(e->timerId());
//    if(m_cMouseCnt<1)
//    {
//        m_pDetPara->hide();
//        qDebug()<<"timer close dlg";
//    }
    if(m_cMouseCnt>0)
    {
        m_pDetPara->show();
        //qDebug()<<"timer close dlg";
        //m_pDetPara->optionWidget->move(QPoint(100,100));
    }
}

void DetWidget::setFlowList(QList<FlowWidget*> &list)
{
    m_pListFlow = list;
}
//void DetWidget::enterEvent(QEvent *)
//{
//    qDebug()<<"mouse enter widget";
//}

//void DetWidget::leaveEvent(QEvent *)
//{
//    qDebug()<<"mouse leave widget";
//}

//------slot--------
void DetWidget::on_rcvDetector()
{
    qDebug()<<"rcv detector";
    bool bFlag = m_ListLoad.count()>1?true:false;

    if(bFlag)
    {

        int cnt = m_ListIcon.count();
        DetContent *middle = m_ListLoad[0];
        for(int i =0;i<cnt;i++)
        {
            middle->addIcon(m_ListIcon[i],0,false);
            m_ListIcon[i]->setDetStatus(false);
        }
        int loadCnt = m_ListLoad.count();
        for(int i=1;i<loadCnt;i++)
        {
            m_ListLoad[i]->disconnect(this);

            m_ListLoad[i]->close();
            qDebug()<<"detcontent close"<<i;
        }
        m_ListLoad.clear();
        m_ListLoad<<middle;
    }

    int numN = 0;
    int numE = 0;
    int numS = 0;
    int numW = 0;
    //QList<quint8> list;
    //list<<1<<2<<1<<1<<1<<1<<1<<1<<1<<3<<1<<1<<1<<1<<1<<1;
    for(int i=0;i<16;i++)
    {
        quint8 num = (*m_pListLoadNum)[i];//list[i];//

        if(/*num==0||*/num>4)//做限定 以后可去除（没有 道路数时）每个路标至少 一车道 0527修改
        {
            num = 1;
        }
        if(i%4!=3)//不管 人行
        {
            switch(i/4)
            {
            case 0:
                numN += num;
                break;
            case 1:
                numE += num;
                break;
            case 2:
                numS += num;
                break;
            case 3:
                numW += num;
                break;
            default:
                break;
            }
            for(int j=0;j<num;j++)
            {
                DetContent *load = new DetContent();
                load->setAttribute(Qt::WA_DeleteOnClose);
                load->setData(i/4+1,i%4+1,j,(*m_pListPhase)[i]);
                load->setDetBase(m_pDataProcess);
                m_ListLoad<<load;
                load->setDirNo(i+1);//i 0-15对应 方向1-16
                connect(load,SIGNAL(removeIcon(DetIcon*)),this,SLOT(on_removeIcon(DetIcon*)));
                connect(load,SIGNAL(mouseStatus(bool,bool,quint8,QPoint)),this,SLOT(on_mouseStatus(bool,bool,quint8,QPoint)));
                connect(load,SIGNAL(detChangePos(int)),m_pDetPara,SLOT(on_detChangePos(int)));
            }
        }


    }
qDebug()<<"numN"<<numN<<"numE"<<numE<<"numS"<<numS<<"numW"<<numW<<"count"<<m_ListLoad.count();
    for(int i=0;i<5;i++)
    {
        QLabel *group = m_ListGroup[i];

        if(i==0)//放在中间
        {
        }
        else if(i==1)
        {
            QHBoxLayout *nLayout = (QHBoxLayout *)group->layout();

            for(int j=0;j<numN;j++)
            {
                nLayout->addWidget(m_ListLoad[j+1]);
            }

        }
        else if(i==2)
        {
            QVBoxLayout *eLayout = (QVBoxLayout *)group->layout();

            for(int j=0;j<numE;j++)
            {
                eLayout->addWidget(m_ListLoad[numN+j+1]);
            }

        }
        else if(i==3)
        {
            QHBoxLayout *sLayout = (QHBoxLayout *)group->layout();

            for(int j=0;j<numS;j++)
            {
                sLayout->addWidget(m_ListLoad[numN+numE+j+1]);
            }

        }
        else if(i==4)
        {
            QVBoxLayout *wLayout = (QVBoxLayout *)group->layout();

            for(int j=0;j<numW;j++)
            {
                wLayout->addWidget(m_ListLoad[numN+numE+numS+j+1]);
            }

        }
    }

    if(m_ListIcon.count()==0)
    {
        for(int i=0;i<MAX_DETECTORNUM;i++)
        {
            DetIcon *detIcon = new DetIcon();
            detIcon->setDetectorNo(i+1);
            m_ListIcon<<detIcon;
            connect(detIcon,SIGNAL(mouseStatus(bool,bool,quint8,QPoint)),this,SLOT(on_mouseStatus(bool,bool,quint8,QPoint)));

            //m_ListLoad[0]->addIcon(detIcon);
        }
    }
    rankDetector();
}

void DetWidget::on_removeIcon(DetIcon *icon)
{
    m_ListLoad[0]->addIcon(icon);
    icon->clearState();
}

void DetWidget::on_rcvDetStatus(unsigned char *para1, int)
{
    if(*para1==0)
    {
        if(!m_pDataProcess->m_bFlagShowDetector)
        {
            emit stopDetStatus();
            return;
        }
//        m_pDataProcess->requireTscTable(TSC_STATUS_DETECTORWARN_TABLE);
        para1++;
        quint8 cnt = *para1;
        para1++;
        DetectorStatus_Table *p = (DetectorStatus_Table*)para1;
        m_bDetAlarm = false;
        m_ListDetStatus.clear();
        m_ListDetAlarm.clear();
        quint8 status = 0;
        quint8 alarm = 0;
        for(quint8 i=0;i<cnt;i++)
        {
            bool bStatus = false;
            bool bAlarm = false;
            status = p->bStatus;
            alarm = p->bAlarm;
            //qDebug()<<"detstatus index:"<<p->bNo;
            for(quint8 j=0;j<8;j++)
            {
                if(((status>>j)&0x01)==1)
                {
                    m_ListDetStatus<<true;
                    bStatus = true;
                }
                else
                {
                    m_ListDetStatus<<false;
                    bStatus = false;
                }
                if(((alarm>>j)&0x01)==1)
                {
                    m_ListDetAlarm<<true;
                    bAlarm = true;
                    if(!m_bDetAlarm)
                    {
                        m_bDetAlarm = true;
                        //if(m_pDataProcess->requireTscTable(TSC_STATUS_DETECTORWARN_TABLE))
                        if(m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORWARN_TABLE,5))
                        {
                            m_bAutoAlarm = true;
                            qDebug()<<"require detector alarm table";
                        }
                    }

                }
                else
                {
                    m_ListDetAlarm<<false;
                    bAlarm = false;
                }
                if(bStatus&&bAlarm)
                {
                    qDebug()<<"det data error";
                }
            }

            p++;
        }

        int listCnt = m_ListDetStatus.count();
        for(int i=0;i<listCnt;i++)
        {
            if(i<32)
            {
                m_ListIcon[i]->setDetStatus(m_ListDetStatus[i]);

            }
        }
        //-------------------

        quint8 flowDet = 0;//1-32
        if(m_pListFlow.count()==4)
        {
            flowDet = m_pListFlow[0]->getDetNo();
        }
        for(int i=0;i<4;i++)
        {
            if(flowDet+i<listCnt+1/*33*/&&flowDet>0)
            {
                m_pListFlow[i]->setStatus(m_ListDetStatus[flowDet+i-1]);
            }
        }
    }
}

void DetWidget::on_rcvDetAlarm()
{

    m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORWARN_TABLE,0);
    m_bAutoAlarm = false;

    DetectorAlarm_Table *p = m_pDataProcess->m_pTscInfo->tbDetectorAlarm;
    int cnt = m_ListDetAlarm.count();
    if(cnt>0)
    {
        for(int i=0;i<cnt;i++)
        {
            if(i<32)
            {
                if(m_ListDetAlarm[i])
                {
                    //qDebug()<<"alarm:"<<i;
                    m_ListIcon[i]->setDetStatus(false,(p+i)->bAlarmStatus,(p+i)->bCoilAlarmStatus);
                }
            }
        }
    }
}

void DetWidget::on_mouseStatus(bool b, bool btype, quint8 index, QPoint p)
{
    if(b)
    {
        m_cMouseCnt++;
        QPoint pos = this->mapTo(this,p);
        QPoint thispos = this->mapToGlobal(this->geometry().topLeft());
        //qDebug()<<"pos x before:"<<pos.x()<<"this"<<thispos.x()<<"m_pDetPara size"<<m_pDetPara->size();
        if(pos.x()>400+thispos.x())
        {
            pos.setX( pos.x()-m_pDetPara->size().width()-20);
            //qDebug()<<"pos x after:"<<pos.x();
        }
        else
        {
            pos.setX( pos.x()+20);
        }

        if(pos.y()>200+thispos.y())
        {
            pos.setY(pos.y()-m_pDetPara->size().height()/2);
        }
        QPoint tempPos = this->mapToGlobal(this->geometry().topRight());
//        m_pDetPara->move(tempPos);
        //m_pDetPara->detWidget->move(QPoint(0,0));
       // m_pDetPara->detWidget->setFixedSize(200,200);
        if(btype)
        {
            //qDebug()<<"set det no:"<<index;
            m_pDetPara->setData(index);
        }
        else//车道
        {
            m_pDetPara->setData(0,index);
        }

        this->startTimer(700);
        qDebug()<<"detwidget start timer 700";
//        if(m_pDetPara->isHidden())
//        {
//            m_pDetPara->show();
//        }

        //qDebug()<<p<<pos<<m_pDetPara->geometry().size();
    }
    else
    {
        if(m_cMouseCnt>0)
        {
            m_cMouseCnt--;
        }
        if(m_cMouseCnt<1)
        {
            //m_pDetPara->hide();
            //this->startTimer(2000);
        }
    }
}

void DetWidget::on_dlgMouseStatus(bool b)
{
    if(b)
    {
        m_cMouseCnt++;
    }
    else if(m_cMouseCnt>0)
    {
        m_cMouseCnt--;
        if(m_cMouseCnt<1&&!m_pDetPara->hasFocus())
        {
            m_pDetPara->hide();
            //qDebug()<<"dlg leave mouse close dlg";
        }
    }
}

void DetWidget::on_closeDetParaDlg()
{
    m_cMouseCnt = 0;
}

//------------------------------------------------------
FlowWidget::FlowWidget(QWidget *parent) :
        QWidget(parent),m_cstCol(QColor(128,64,0))
{
    resize(PIXWIDTH+50,PIXHEIGHT);
    pix = QPixmap(PIXWIDTH,PIXHEIGHT);
    pix.fill(m_cstCol);
    m_bStatusPre = false;
    m_bStatus = false;
    m_bLine = false;
    m_bData = false;
    m_uiNum = 0;
    m_ucDetNo = 0;
    //clearData();
    QPalette p = this->palette();
    p.setColor(QPalette::Background,m_cstCol);
    this->setPalette(p);
}

FlowWidget::~FlowWidget()
{
    qDebug()<<"~FlowWidget";
}

void FlowWidget::paintEvent(QPaintEvent *)
{

    QPainter pp(&pix);
    QPen pen = pp.pen();
    if(!m_bLine)
    {
        m_bLine = true;
        pen.setColor(Qt::darkGray);
        pp.setPen(pen);
        pp.drawLine(0,FLOWBASE+FLOWHEIGHT,PIXWIDTH,FLOWBASE+FLOWHEIGHT);
    }

    pixTemp = pix;
    pix.fill(m_cstCol);
   // pp.fillRect(0,0,500,40,Qt::white);
    pen.setColor(Qt::darkGray);
    pp.setPen(pen);
    pp.drawLine(PIXWIDTH-FLOWWIDTH,FLOWBASE+FLOWHEIGHT,PIXWIDTH,FLOWBASE+FLOWHEIGHT);

    pen.setColor(Qt::blue);
    pp.setPen(pen);
    if(m_bData)
    {
        if(m_bStatusPre)
        {
            if(m_bStatus)
            {
                //qDebug()<<"draw 1";
                pp.drawLine(PIXWIDTH-FLOWWIDTH,FLOWBASE,PIXWIDTH,FLOWBASE);
            }
            else
            {
                //qDebug()<<"draw 2";
                pp.drawLine(PIXWIDTH-FLOWWIDTH,FLOWBASE,PIXWIDTH-FLOWWIDTH,FLOWBASE+FLOWHEIGHT);
                pp.drawLine(PIXWIDTH-FLOWWIDTH,FLOWBASE+FLOWHEIGHT,PIXWIDTH,FLOWBASE+FLOWHEIGHT);
            }
        }
        else
        {
            if(m_bStatus)
            {
                //qDebug()<<"draw 3";
                pp.drawLine(PIXWIDTH-FLOWWIDTH,FLOWBASE+FLOWHEIGHT,PIXWIDTH-FLOWWIDTH,FLOWBASE);
                pp.drawLine(PIXWIDTH-FLOWWIDTH,FLOWBASE,PIXWIDTH,FLOWBASE);
                //pp.drawLine(500,5,500,35);
            }
            else
            {
                //qDebug()<<"draw 4";
                pp.drawLine(PIXWIDTH-FLOWWIDTH,FLOWBASE+FLOWHEIGHT,PIXWIDTH,FLOWBASE+FLOWHEIGHT);
            }
        }
        if(m_bLine)
        {
            pp.drawPixmap(-FLOWWIDTH,0,PIXWIDTH,PIXHEIGHT,pixTemp);
        }
        m_bData = false;
    }
    else
    {
        pp.drawPixmap(0,0,PIXWIDTH,PIXHEIGHT,pixTemp);
    }

    //qDebug()<<"paintEvent"<<"m_bStatusPre"<<m_bStatusPre<<"m_bStatus"<<m_bStatus<<pixTemp.size();



    m_bStatusPre = m_bStatus;
    QPainter painter(this);
    painter.drawPixmap(20,0,PIXWIDTH,40,pix);
    QFont serifFont("Times", 17, QFont::Bold);
    painter.setFont(serifFont);
    painter.setPen(QPen(Qt::green));
    painter.drawText(0,10,20,30,Qt::AlignCenter,QString::number(m_ucDetNo));
    QFont numFont("Times", 8, QFont::Bold);
    painter.setFont(numFont);
    painter.drawText(20+PIXWIDTH,10,30,30,Qt::AlignCenter,QString::number(m_uiNum));
}

void FlowWidget::mousePressEvent(QMouseEvent *)
{
//    bClick = !bClick;

//    if(bClick)
//    {
//        m_iTimerId = this->startTimer(500);
//    }
//    else
//    {
//        this->killTimer(m_iTimerId);
//    }

}

void FlowWidget::setStatus(bool b)
{

    if(m_bStatus&&!b)
    {
        m_uiNum++;
    }
    m_bStatus = b;
    m_bData = true;
    update();
}

void FlowWidget::setDetNo(quint8 detNo)
{
    if(detNo>0&&detNo<49)
    {
        m_ucDetNo = detNo;
    }
    else
    {
        m_ucDetNo = 0;
    }

}

quint8 FlowWidget::getDetNo()
{
    return m_ucDetNo;
}

void FlowWidget::clearData()
{
    pix.fill(m_cstCol);
    pixTemp.fill(m_cstCol);
    m_bStatusPre = false;//先前状态
    m_bStatus = false;//现在状态 true 有车 false 无车
    m_bLine = false;//初始化时 画底线
    m_bData = false;//是否是 检测器 设置 数据 以区别于 重画
    m_uiNum = 0;
    update();
}

void FlowWidget::timerEvent(QTimerEvent *)
{
    bTimer = !bTimer;
    setStatus(bTimer);
}
