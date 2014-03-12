#include "phase.h"
#include <QPainter>
#include <QDebug>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include <QTransform>
#include <QApplication>

#define WORDWIDTH 30
#define CHLWIDTH 20
#define LOADWIDTH 50
#define TIMEOUT600 600
#define SCALECHL 1.3
#define SCALEPHASE 0.6
#define COLORWIDTH 130
#define BARWIDTH 5
#define BARHEIGHT 25

WordIcon::WordIcon(quint8 id,bool bUsed,bool bContent, bool bValid, QWidget *parent):
    m_ucPhaseId(id),m_bUsed(bUsed),m_bContent(bContent),m_bValid(bValid),QLabel(parent)
{
    if(m_bContent)
    {
        this->setFixedSize(WORDWIDTH*SCALEPHASE,WORDWIDTH*SCALEPHASE);
//        qDebug()<<"WORDWIDTH*SCALEPHASE"<<WORDWIDTH*SCALEPHASE;
    }
    else
    {
        this->setFixedSize(WORDWIDTH,WORDWIDTH);
    }
    if(id>MAXCOMPHASE)
    {
        m_bOverlap = true;
//        if(!m_bContent)
//            this->setToolTip(tr("跟随相位可拖拽用于路标"));
    }
    else
    {
        m_bOverlap = false;
//        if(!m_bContent)
//            this->setToolTip(tr("普通相位可拖拽用于路标、跟随相位里的包含相位容器(黄色)和修正相位容器(黑色)"));
    }

    m_bMouseIn = false;
    m_bDrag = false;
    m_bDirContent = false;
    m_bClick = false;
    m_bAmend = false;
}

WordIcon::~WordIcon()
{
    qDebug()<<"~WordIcon()"<<"phase Id:"<<m_ucPhaseId;
}

void WordIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(m_bContent)
    {
        painter.scale(SCALEPHASE,SCALEPHASE);
    }
    QFont font("Times",12);
    QPen pen;

   if(m_bMouseIn||m_bClick)
   {
       QBrush brushBack(Qt::lightGray);
       painter.setBrush(brushBack);
       painter.drawRect(0,0,WORDWIDTH,WORDWIDTH);

   }
   if(m_bValid)
   {
       if(m_bDirContent)
       {
           pen.setColor(Qt::red);
       }
       else
       {
           pen.setColor(Qt::black);
       }
   }
   if(m_bAmend)
   {
       pen.setColor(Qt::yellow);
   }
   if(!m_bValid||m_bUsed)
   {
       //qDebug()<<"valid false yellow"<<m_ucPhaseId;
       pen.setColor(Qt::blue);
   }
   painter.setPen(pen);
   painter.setFont(font);
//   QString str = "P";
   QString str;
   if(m_bOverlap)
   {
       str = tr("跟");
   }
   else
   {
       str = tr("相");
   }
   painter.drawText(1,-2,WORDWIDTH/2,WORDWIDTH,Qt::AlignCenter,str);


//   if(m_bOverlap)
//   {
////       QFont fontDot("Times",25);
////       painter.setFont(fontDot);
////       str = "'";
////       painter.drawText(10,7,25,25,Qt::AlignCenter,str);
//   }

   QFont fontNum("Times",11);
   painter.setFont(fontNum);
   quint8 id = m_ucPhaseId;
   if(m_bOverlap)
   {
       id -= MAXCOMPHASE;
   }
   str = QString::number(id);
   painter.drawText(12,13,15,17,Qt::AlignCenter,str);
}

void WordIcon::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        m_posStart = ev->pos();
        m_bDrag = false;
    }
}

void WordIcon::mouseMoveEvent(QMouseEvent *ev)
{
    if(((ev->pos()-m_posStart).manhattanLength())<WORDWIDTH/2||!m_bValid)
    {
        return;
    }
    emit leaveContent(this);
    m_bDrag = true;
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<(int)this<<QPoint(ev->pos()-rect().topLeft());
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("Drag-Icon",data);

    QDrag drag(this);
    drag.setMimeData(mimeData);
    drag.setHotSpot(QPoint(ev->pos()-rect().topLeft()));
    Qt::DropAction dropAction = drag.start(Qt::CopyAction|Qt::MoveAction);

    if(dropAction==Qt::MoveAction)
    {qDebug()<<"phase close"<<m_ucPhaseId;
        //close();
    }
    else
    {
        show();
    }
}

void WordIcon::mouseReleaseEvent(QMouseEvent *)
{
    if(!m_bDrag)
    {
        m_bClick = !m_bClick;
        emit mouseClick(m_ucPhaseId,m_bClick);
    }
}

void WordIcon::enterEvent(QEvent *)
{
    if(m_bValid)
    {
        m_bMouseIn = true;
        this->update();
    }

}

void WordIcon::leaveEvent(QEvent *)
{
    m_bMouseIn = false;
    this->update();
}

void WordIcon::on_setOverlapFlagValid(bool b)
{
    m_bValid = b;
    this->update();
}

bool WordIcon::getFlagUsed()
{
    return m_bUsed;
}

void WordIcon::setFlagUsed(bool b)
{
    m_bUsed = b;
//    this->setToolTip(tr("红色相位图标，可拖拽用于路标。"));
    this->update();
}

bool WordIcon::getFlagOverlapContent()
{
    return m_bContent;
}

quint8 WordIcon::getId()
{
    return m_ucPhaseId;
}

void WordIcon::setFlagDirContent(bool b)
{
//    this->setToolTip(tr("红色相位图标，可拖拽用于路标。"));
    m_bDirContent = b;
}

bool WordIcon::getFlagDirContent()
{
    return m_bDirContent;
}

void WordIcon::setFlagClick(bool b)
{
    m_bClick = b;
    this->update();
}

bool WordIcon::getFlagClick()
{
    return m_bClick;
}

void WordIcon::setFlagAmend(bool b)
{
    m_bAmend = b;
    this->update();
}

//--------------------------------------------------

ChlIcon::ChlIcon(quint8 id, bool bUsed, QWidget *parent):
        QLabel(parent),m_ucChlId(id),m_bUsed(bUsed)
{

    m_pix = QPixmap::fromImage(QImage(":/Files/images/signal.png"));
    this->setFixedSize(CHLWIDTH,CHLWIDTH*3);


    m_bMouseIn = false;
    m_bDrag = false;
    m_ucPhaseId = 0;
    m_bClick = false;
//    this->setToolTip(tr("通道图标可拖拽放于绿色容器"));
}

ChlIcon::~ChlIcon()
{
    qDebug()<<"~ChlIcon()"<<"channel Id:"<<m_ucChlId;
}

void ChlIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(m_bUsed)
    {
        painter.scale(SCALECHL,SCALECHL);
    }
    QFont font("Times",10);
    QPen pen;
pen.setColor(Qt::white);
   if(m_bMouseIn||m_bClick)
   {
//       QBrush brushBack(Qt::lightGray);
       QBrush brushBack(Qt::white);
       painter.setBrush(brushBack);
       painter.drawRect(0,0,CHLWIDTH,CHLWIDTH);

   }

   painter.setPen(pen);
   painter.setFont(font);
//   QString str = "C";
   QString str = tr("通");
   painter.drawText(1,4,CHLWIDTH/2,CHLWIDTH-4,Qt::AlignCenter,str);

   QFont fontNum("Times",7);
   painter.setFont(fontNum);
   str = QString::number(m_ucChlId);
   painter.drawText(CHLWIDTH/2+1,9,9,8,Qt::AlignCenter,str);
   if(!m_bUsed)
   {
       painter.drawPixmap(0,CHLWIDTH,CHLWIDTH,CHLWIDTH*2,m_pix);
   }
}

void ChlIcon::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        m_posStart = ev->pos();
        m_bDrag = false;
    }
}

void ChlIcon::mouseMoveEvent(QMouseEvent *ev)
{
    if(((ev->pos()-m_posStart).manhattanLength())<CHLWIDTH/2)
    {
        return;
    }
    emit leaveContent(this);
    m_bDrag = true;
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<(int)this<<QPoint(ev->pos()-rect().topLeft());
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("Chl-Icon",data);

    QDrag drag(this);
    drag.setMimeData(mimeData);
    drag.setPixmap(m_pix);
    drag.setHotSpot(QPoint(ev->pos()-rect().topLeft()));
    Qt::DropAction dropAction = drag.start(Qt::CopyAction|Qt::MoveAction);

    if(dropAction==Qt::MoveAction)
    {//qDebug()<<"channel close"<<m_ucChlId;
        //close();
    }
    else
    {
        show();
    }
}

void ChlIcon::mouseReleaseEvent(QMouseEvent *)
{
    if(!m_bDrag)
    {
        m_bClick = !m_bClick;
        emit mouseClick(m_ucChlId,m_bClick,m_ucPhaseId);
    }
}

void ChlIcon::enterEvent(QEvent *)
{
    m_bMouseIn = true;
    this->update();
}

void ChlIcon::leaveEvent(QEvent *)
{
    m_bMouseIn = false;
    this->update();
}

void ChlIcon::setFlagUsed(bool b)
{
    m_bUsed = b;
    if(b)
    {/*qDebug()<<"change height";*/
        this->setFixedSize(WORDWIDTH,WORDWIDTH);;
    }
    else
    {
        this->setFixedSize(CHLWIDTH,CHLWIDTH*3);
    }
}

quint8 ChlIcon::getId()
{
    return m_ucChlId;
}

quint8 ChlIcon::getPhaseId()
{
    return m_ucPhaseId;
}

void ChlIcon::setChlPhaseId(quint8 id)
{
    m_ucPhaseId = id;
}

void ChlIcon::setFlagClick(bool b)
{
    m_bClick = b;
    this->update();
}

//----------------------------------------------------
IconContent::IconContent(bool bType, quint8 id, QWidget *parent):
        m_bType(bType),m_ucContentId(id),QWidget(parent)
{
    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setMargin(0);
    m_hLayout->setSpacing(1);
    if(bType)//通道容器
    {
        this->setFixedSize(/*CHLWIDTH*4*/70,WORDWIDTH+10);//与painter区域同
//        this->setToolTip(tr("绿色容器放通道图标"));
    }
    else
    {
        this->setFixedSize(/*CHLWIDTH*4*/70,CHLWIDTH);
    }

    if(m_ucContentId>OVERLAPPHASENUM)
    {
        m_bAmend = true;
//        if(!bType)
//        this->setToolTip(tr("黑色容器放修正相位图标"));
    }
    else
    {
        m_bAmend = false;
//        if(!bType)
//        this->setToolTip(tr("黄色容器放包含相位图标"));
    }
    this->setAcceptDrops(true);
}

IconContent::~IconContent()
{
    qDebug()<<"~IconContent()";
}

void IconContent::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon")&&!m_bType)
    {
        QByteArray data = e->mimeData()->data("Drag-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        WordIcon *icon;
        stream>>i>>offset;
        icon = static_cast<WordIcon*>((void*)(i));
        if(icon->getId()>MAXCOMPHASE)
        {
            return;
        }
        if(icon->getFlagDirContent())//在方向容器里的相位
        {
            return;
        }
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
    else if(e->mimeData()->hasFormat("Chl-Icon")&&m_bType)
    {
        qDebug()<<"chl enter";
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

void IconContent::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon")||e->mimeData()->hasFormat("Chl-Icon"))
    {

        QByteArray data;
        if(m_bType)
        {
            data = e->mimeData()->data("Chl-Icon");
        }
        else
        {
            data = e->mimeData()->data("Drag-Icon");
        }
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        stream>>i>>offset;
        if(m_bType&&e->mimeData()->hasFormat("Chl-Icon"))
        {
            if(m_ListId.count()>3)
            {
                return;
            }
            ChlIcon *chlIcon = static_cast<ChlIcon*>((void*)(i));
            addChl(chlIcon);
        }
        else if((e->mimeData()->hasFormat("Drag-Icon")))
        {
            WordIcon *icon;
            icon = static_cast<WordIcon*>((void*)(i));
            if(icon->getFlagDirContent())//如果是从方向容器来的 不响应
            {
                return;
            }
            quint8 id = icon->getId();
            if(!checkId(id))
            {
                return;
            }

            bool bContent = icon->getFlagOverlapContent();
            if(bContent)//包含容器间
            {
                addComPhase(icon);
            }
            else
            {
                addComPhase(id);
            }
            //        delete e->mimeData();
        }

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
    else
    {
        e->ignore();
    }
}

void IconContent::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rect;
    if(m_bType)
    {
        rect.setRect(0,0,CHLWIDTH*4,WORDWIDTH+10);
//        QColor newCol = QColor(7,14,30);
        painter.fillRect(rect,QColor(41,40,31));
    }
    else
    {
        rect.setRect(0,0,CHLWIDTH*4,CHLWIDTH);
        if(m_bAmend)
        {
            painter.fillRect(rect,Qt::black);
        }
        else
        {
            painter.fillRect(rect,Qt::yellow);
        }
    }
}

bool IconContent::checkId(quint8 id)
{
   if(m_ListId.contains(id))
   {
       return false;
   }
   else
   {
       return true;
   }

}

bool IconContent::checkIcon(WordIcon*icon)
{
    QList<WordIcon*> list = this->findChildren<WordIcon*>();
    int cnt = list.count();
    for(int i=0;i<cnt;i++)
    {
        if(list[i]==icon)
        {
            return false;
        }
    }
    return true;//不包含
}

bool IconContent::checkIcon(ChlIcon*icon)
{
    QList<ChlIcon*> list = this->findChildren<ChlIcon*>();
    int cnt = list.count();
    for(int i=0;i<cnt;i++)
    {
        if(list[i]==icon)
        {
            return false;
        }
    }
    return true;//不包含
}

void IconContent::addComPhase(quint8 id)
{
//    qDebug()<<"new wordicon";
    WordIcon *icon = new WordIcon(id,false,true);
    icon->setAttribute(Qt::WA_DeleteOnClose);
    addComPhase(icon);
}

void IconContent::addComPhase(WordIcon *icon)
{
//    qDebug()<<"phase drop add list id"<<icon->getId();
    m_ListId.append(icon->getId());
    m_hLayout->addWidget(icon);
    icon->setFlagAmend(m_bAmend);
    if(icon->getFlagClick())
    {
        on_mouseClickPhase(icon->getId(),true);
    }
    connect(icon,SIGNAL(leaveContent(WordIcon*)),this,SLOT(on_phaseLeaveContent(WordIcon*)));
    connect(icon,SIGNAL(mouseClick(quint8,bool)),this,SLOT(on_mouseClickPhase(quint8,bool)));
    emit setOverlapValid(true);
}

void IconContent::addChl(ChlIcon *icon)
{
    qDebug()<<"chl drop add list id"/*<<icon->getId()*/;
    m_ListId.append(icon->getId());
    icon->setFlagUsed();
    icon->setChlPhaseId(m_ucContentId);
    m_hLayout->addWidget(icon);
    connect(icon,SIGNAL(leaveContent(ChlIcon*)),this,SLOT(on_chlLeaveContent(ChlIcon*)));
}

/*
 容器里 只有 设置 click为false,（设置true只用于 非容器里的 相位）
*/
void IconContent::setFlagClick(quint8 phaseId, bool b)
{
    if(!b)
    {
        QList<WordIcon*> list = this->findChildren<WordIcon*>();
        int cnt = list.count();
        for(int i=0;i<cnt;i++)
        {
            WordIcon *icon = list[i];
            if(icon->getId()==phaseId)
            {
                icon->setFlagClick(false);
            }
        }
    }
}

quint8 IconContent::getContentId()
{
    return m_ucContentId;
}

void IconContent::clearContent()
{
    m_ListId.clear();
    if(!m_bType)
    {
        QList<WordIcon*> list = this->findChildren<WordIcon*>();
        foreach(WordIcon* icon,list)
        {
            icon->close();
        }
    }
}

QList<quint8>&IconContent::getListData()
{
    m_ListId.clear();
    if(m_bType)//通道容器 用不上 (一通道对应一相位)
    {
        QList<ChlIcon*> list = this->findChildren<ChlIcon*>();
        foreach(ChlIcon*icon,list)
        {
            m_ListId.append(icon->getId());
        }
    }
    else
    {
        QList<WordIcon*> list = this->findChildren<WordIcon*>();
        foreach(WordIcon*icon,list)
        {
            m_ListId.append(icon->getId());
        }
    }
//    qSort(m_ListId);
    return m_ListId;
}
//bool IconContent::getFlagAmend()
//{
//    return m_bAmend;
//}

void IconContent::on_chlLeaveContent(ChlIcon *icon)
{
//    qDebug()<<"chl leave  remove list id"<<icon->getId();
    m_ListId.removeOne(icon->getId());
    m_hLayout->removeWidget(icon);
    icon->setChlPhaseId(0);
    icon->disconnect(this);
}

void IconContent::on_phaseLeaveContent(WordIcon *icon)
{
    m_ListId.removeOne(icon->getId());
    m_hLayout->removeWidget(icon);

    icon->disconnect(this);

//    qDebug()<<"phase leave  remove list id"<<icon->getId();
    QList<WordIcon*> list = this->findChildren<WordIcon*>();
//    qDebug()<<"list id cnt"<<m_ListId.count()<<"content contain icon cnt"<<list.count();
    if(m_ListId.count()==0)
    {
        emit setOverlapValid(false);
    }
}

void IconContent::on_mouseClickPhase(quint8 phaseId, bool bClick)
{
    emit mouseClickPhase(m_ucContentId,bClick,phaseId);
}

//----------------------------------------------
LoadIcon::LoadIcon(/*QPixmap pix,*/quint8 loadNo,QWidget *parent) :
    QLabel(parent),m_ucLoadNo(loadNo)/*,m_Pix(pix)*/
{

    QPalette palette;
    palette.setColor(QPalette::Background,Qt::green);
    this->setPalette(palette);

    m_pIcon = NULL;
    m_bPed = false;
    m_pLayout = NULL;
    this->setScaledContents(true);

    analyseDir();
    this->setAcceptDrops(true);
    m_ucPhaseId = 0;
    m_bValid = false;
    m_bClick = false;
    m_ucNum = 1;
}

LoadIcon::~LoadIcon()
{

    qDebug()<<"~LoadIcon()"<<m_ucLoadNo;
}

void LoadIcon::loadImage()
{
    if(m_ucLoadNo<32&&m_ucLoadNo>0)
    {
        m_iDirect = (m_ucLoadNo-1)/4;//0 北 1 东 2 南 3 西
        quint8 newId=0;
        switch(m_iDirect)
        {
         case 0:
             newId |= 0x20;
             break;
         case 1:
             newId |= 0x40;
             break;
         case 2:
            newId |= 0x60;
             break;
         case 3:
             newId |= 0x80;
             break;
         default:
             break;
        }

        switch((m_ucLoadNo-1)%4)
        {
        case 0:
            newId |= 0x01;
            m_img.load(":/Files/images/whitel.jpg");
            break;
        case 1:
            newId |= 0x02;
            m_img.load(":/Files/images/whites.jpg");
            break;
        case 2:
            newId |= 0x04;
            m_img.load(":/Files/images/whiter.jpg");
            break;
        case 3:
            newId |= 0x08;
            m_bPed = true;
            m_img.load(":/Files/images/whiteped.jpg");
            break;
        default:
            break;
        }

        m_ucLoadNo = newId;
        qreal angle = m_iDirect*90;
        QTransform trans;
        this->setPixmap(QPixmap::fromImage(m_img.transformed(trans.rotate(angle/*,Qt::ZAxis*/))));
    }
    else if(m_ucLoadNo>31)
    {
        switch(m_ucLoadNo&0x18)
        {
        case 0x00://机动车
            {
                m_bPed = false;
                switch(m_ucLoadNo&0x07)
                {
                case 1:
                    m_img.load(":/Files/images/whitel.jpg");
                    break;
                case 2:
                    m_img.load(":/Files/images/whites.jpg");
                    break;
                case 3:
                    m_img.load(":/Files/images/whitesl.jpg");
                    break;
                case 4:
                    m_img.load(":/Files/images/whiter.jpg");
                    break;
                case 5:
//                    m_img.load(":/Files/images/whiters.jpg");
                    break;
                case 6:
                    m_img.load(":/Files/images/whiters.jpg");
                    break;
                case 7:
                    m_img.load(":/Files/images/whitersl.jpg");
                    break;
                }

                break;
            }
        case 0x08://人行
            {
                m_bPed = true;
                m_img.load(":/Files/images/whiteped.jpg");
                switch(m_ucLoadNo&0x07)
                {
                case 0://1次过街
//                    m_img.load(":/Files/images/whiteped.jpg");
                    break;
                case 1://2次过街1
//                    m_img.load(":/Files/images/whiteped.jpg");
                    break;
                case 3://2次过街2
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                }
                break;
            }
        case 0x10:
            break;
        case 0x11:
            break;
        }
        switch(m_ucLoadNo&0xe0)
        {
        case 0x20://北
            m_iDirect = 0;
            break;
        case 0x40://东
            m_iDirect = 1;
            break;
        case 0x60://南
            m_iDirect = 2;
            break;
        case 0x80://西
            m_iDirect = 3;
            break;
        }
        qreal angle = m_iDirect*90;
        QTransform trans;
        this->setPixmap(QPixmap::fromImage(m_img.transformed(trans.rotate(angle/*,Qt::ZAxis*/))));

    }
}
void LoadIcon::analyseDir()
{
    loadImage();
    if(m_bPed)//人行
    {/*
        m_img.load(":/Files/images/whiteped.jpg");*/
        if(m_iDirect%2==0)//南北
        {
            if((m_ucLoadNo&0x07)!=0)//二次
            {
                this->setFixedSize(57,/*14*/32);
                if(m_pLayout==NULL)
                    m_pLayout = new QHBoxLayout(this);
                m_pLayout->setContentsMargins(20,0,37,32);
            }
            else
            {
                this->setFixedSize(106,/*14*/32);
                if(m_pLayout==NULL)
                    m_pLayout = new QHBoxLayout(this);
                m_pLayout->setContentsMargins(40,0,74,32);
            }

        }
        else//东西
        {
            if((m_ucLoadNo&0x07)!=0)//二次
            {
                this->setFixedSize(/*14*/32,57);
                if(m_pLayout==NULL)
                    m_pLayout = new QVBoxLayout(this);
                m_pLayout->setContentsMargins(0,20,32,37);
            }
            else
            {
                this->setFixedSize(/*14*/32,106);
                if(m_pLayout==NULL)
                    m_pLayout = new QVBoxLayout(this);
                m_pLayout->setContentsMargins(0,40,32,74);
            }
        }
    }
    else
    {
        if(m_iDirect%2==0)//南北
        {
            this->setFixedSize(32,106);
            if(m_pLayout==NULL)
                m_pLayout = new QVBoxLayout(this);
            m_pLayout->setContentsMargins(0,36,32,70);
        }
        else//东西
        {
            this->setFixedSize(106,32);
            if(m_pLayout==NULL)
                m_pLayout = new QHBoxLayout(this);
            m_pLayout->setContentsMargins(36,0,70,32);
        }
    }

}

void LoadIcon::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
    {
        QByteArray data = e->mimeData()->data("Drag-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        WordIcon *icon;
        stream>>i>>offset;
        icon = static_cast<WordIcon*>((void*)(i));
        if(icon->getFlagOverlapContent()||icon->getFlagUsed())
        {
//            if(icon->getFlagOverlapContent())
//            {
//                icon->close();
//            }
            return;
        }
        if(children().contains(e->source()))
        {
//            qDebug()<<"Load"<<m_ucLoadNo<<"accept move phase"<<icon->getId();
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
//            qDebug()<<"Load"<<m_ucLoadNo<<"accept copy phase"<<icon->getId();
            e->acceptProposedAction();
        }


    }
}


void LoadIcon::dragMoveEvent(QDragMoveEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
    {
        QByteArray data = e->mimeData()->data("Drag-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        WordIcon *icon;
        stream>>i>>offset;
        icon = static_cast<WordIcon*>((void*)(i));
        if(icon->getFlagOverlapContent()||icon->getFlagUsed())
        {
            return;
        }
        if(children().contains(e->source()))
        {
            //qDebug()<<"Load"<<m_ucLoadNo<<"accept move phase"<<icon->getId();
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            //qDebug()<<"Load"<<m_ucLoadNo<<"accept copy phase"<<icon->getId();
            e->acceptProposedAction();
        }
    }
}


void LoadIcon::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
    {

        QByteArray data = e->mimeData()->data("Drag-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        WordIcon *icon;
        stream>>i>>offset;
        icon = static_cast<WordIcon*>((void*)(i));
        bool bDirContent = icon->getFlagDirContent();
        //qDebug()<<"dir content drop drag---------------------";
        if(bDirContent)//容器间 move
        {
            addPhaseIcon(icon);
        }
        else
        {
            icon->setFlagUsed();
            addPhaseIcon(icon->getId());
        }

        if(children().contains(e->source()))
        {
            //qDebug()<<"Load"<<m_ucLoadNo<<"accept move phase"<<icon->getId();
            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {
            //qDebug()<<"Load"<<m_ucLoadNo<<"accept copy phase"<<icon->getId();
            e->acceptProposedAction();
        }
        //        delete e->mimeData();
    }
    else
    {
        e->ignore();
    }

}

void LoadIcon::mouseReleaseEvent(QMouseEvent *)
{
    m_bClick = !m_bClick;
    this->update();
    emit mouseClickDir(m_ucLoadNo,m_bClick);
}

void LoadIcon::mouseDoubleClickEvent(QMouseEvent *)
{
    emit mouseDoubleClick(m_ucLoadNo);
}

void LoadIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //QRect r = this->rect();
    painter.drawPixmap(this->rect(),*(this->pixmap()));
    if(m_bClick)
    {
//        qDebug()<<"draw rect loadicon";
        QPen pen(Qt::gray);
        pen.setWidth(15);
        painter.setPen(pen);
        painter.drawRect(this->rect());
    }
}

void LoadIcon::addPhaseIcon(WordIcon *icon)
{
    if(m_pIcon!=NULL)
    {
        clearPhaseIcon();
    }
    m_pIcon = icon;
    m_bValid = true;
    m_ucPhaseId = icon->getId();
    m_pLayout->addWidget(icon);
    if(icon->getFlagClick())
    {
        on_mouseClickPhase(m_ucPhaseId,true);
    }
    connect(icon,SIGNAL(leaveContent(WordIcon*)),this,SLOT(on_phaseLeaveContent(WordIcon*)));
    connect(icon,SIGNAL(mouseClick(quint8,bool)),this,SLOT(on_mouseClickPhase(quint8,bool)));
}

void LoadIcon::addPhaseIcon(quint8 id)
{
    if(id>0)
    {
        WordIcon *icon = new WordIcon(id,false,false);
        emit clearContent(id,true);
        icon->setAttribute(Qt::WA_DeleteOnClose);
        icon->setFlagDirContent(true);
        addPhaseIcon(icon);
    }
}

bool LoadIcon::getFlagPed()
{
    return m_bPed;
}

void LoadIcon::setFlagValid(bool b)
{
    m_bValid = b;
//    if(b)
//    {
//        show();
//    }
//    else
//    {
//        hide();
//    }
    this->setVisible(b);
    if(!b)
    {
        this->clearPhaseIcon();//若隐藏 清除相位
    }
}

//void LoadIcon::setFlagV

bool LoadIcon::getFlagValid()
{
    return m_bValid;
}

void LoadIcon::clearPhaseIcon()
{
    if(m_pIcon!=NULL)
    {//qDebug()<<"loadicon clear m_pIcon------------";
        m_pLayout->removeWidget(m_pIcon);
        m_pIcon->close();
        m_pIcon = NULL;
        m_bValid = false;
        emit clearContent(m_ucPhaseId);//使 相位 used为false；
        m_ucPhaseId = 0;
    }
}

void LoadIcon::setFlagClick(quint8 phaseId,bool b)
{
    if(!b)
    {
        QList<WordIcon*> list = this->findChildren<WordIcon*>();
        int cnt = list.count();
        for(int i=0;i<cnt;i++)
        {
            WordIcon *icon = list[i];
            if(icon->getId()==phaseId)
            {
                icon->setFlagClick(false);
            }
        }
    }
}

void LoadIcon::setFlagClick(bool bClick)
{
    m_bClick = bClick;
    this->update();
}

quint8 LoadIcon::getContentId()
{
    return m_ucLoadNo;
}

void LoadIcon::setLoadNo(quint8 loadNo)
{
    m_ucLoadNo = loadNo;
    analyseDir();
}

quint8 LoadIcon::getPhaseId()
{
    quint8 id = 0;
    if(m_pIcon!=NULL)
    {
        id = m_pIcon->getId();
    }
    return id;
}

quint8 LoadIcon::getLoadNum()
{
    return m_ucNum;
}

void LoadIcon::setLoadNum(quint8 num)
{
    m_ucNum = num;
}

void LoadIcon::on_phaseLeaveContent(WordIcon *icon)
{//qDebug()<<"wordicon leave load m_pIcon=NULL------------";
    m_pIcon = NULL;
    m_bValid = false;
    m_ucPhaseId = 0;
    m_pLayout->removeWidget(icon);
    icon->disconnect(this);
}

void LoadIcon::on_mouseClickPhase(quint8 phaseId, bool bClick)
{
    emit mouseClickPhase(m_ucLoadNo,bClick,phaseId);
}

//------------------------------------------------
phaseWidget::phaseWidget(quint16 width,QWidget *parent):
        QWidget(parent)
{
    m_sAllowPhase = 0;
    m_bNorth = true;
    m_bEast = true;
    m_bSouth = true;
    m_bWest = true;
    this->setIconWidth(width);
    setPalette(QPalette(QColor(7,14,30)));
    setAutoFillBackground(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

phaseWidget::~phaseWidget()
{
    qDebug()<<"~phaseWidget()";
}

void phaseWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
     painter.scale(m_rScale*0.833,m_rScale*0.833);
    QRectF rectGreen(0,0,600,600);
    //painter.fillRect(rectGreen,Qt::gray);

    QPen pen(Qt::darkRed);
    pen.setWidth(5);
    painter.setPen(pen);
    QBrush brushTemp(QColor(89,89,89));
    painter.setBrush(brushTemp);
    QPainterPath path;
    if(m_bNorth)
    {
        path.moveTo(200,0);
        path.lineTo(200,160);
    }
    else
    {
        path.moveTo(160,200);
    }
    if(m_bWest)
    {
        if(m_bNorth)
        {
            QRectF rect(QPoint(120,120),QSize(80,80));
            path.arcTo(rect,270*16,-90);
        }

        path.lineTo(0,200);

        path.lineTo(0,400);
        path.lineTo(160,400);
        if(m_bSouth)
        {
            path.arcTo(120,400,80,80,90,-90);
        }
    }
    if(m_bSouth)
    {
        path.lineTo(200,600);
        path.lineTo(400,600);
        path.lineTo(400,440);
        if(m_bEast)
        {
            path.arcTo(400,400,80,80,180,-90);
        }
    }
    if(m_bEast)
    {
        path.lineTo(600,400);
        path.lineTo(600,200);
        path.lineTo(440,200);
        if(m_bNorth)
        {
            path.arcTo(400,120,80,80,270,-90);
        }
    }
    if(m_bNorth)
    {
        path.lineTo(400,0);
        path.lineTo(200,0);
    }
    painter.drawPath(path);

//    if(!m_bNorth)
//    {
//        QRect northRect(0,0,600,200);
//        painter.fillRect(northRect,Qt::darkGreen);
//        painter.drawLine(0,200,600,200);
//    }
//    if(!m_bEast)
//    {
//        QRect northRect(400,0,200,600);
//        painter.fillRect(northRect,Qt::darkGreen);
//        painter.drawLine(400,0,400,600);
//    }
//    if(!m_bSouth)
//    {
//        QRect northRect(0,400,600,200);
//        painter.fillRect(northRect,Qt::darkGreen);
//        painter.drawLine(0,400,600,400);
//    }
//    if(!m_bWest)
//    {
//        QRect northRect(0,0,200,600);
//        painter.fillRect(northRect,Qt::darkGreen);
//        painter.drawLine(200,0,200,600);
//    }

    painter.save();
    painter.translate(300,300);
    QStringList strList;
    //strList<<QObject::tr("北")<<QObject::tr("东")<<QObject::tr("南")<<QObject::tr("西");
    strList<<QObject::tr("东")<<QObject::tr("南")<<QObject::tr("西")<<QObject::tr("北");
    pen.setWidth(1);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    QFont font("Times", 30, QFont::Bold);
    painter.setFont(font);
    for(int i=0;i<4;i++)
    {
        painter.rotate(90);
        painter.drawText(-25,-100,40,40,Qt::AlignCenter,strList[i]);
    }

    painter.restore();
   painter.scale(1.2,1.2);


    //painter.drawImage(0,0,m_img);
    int cnt = m_bListGreen.count();
    if(cnt!=20+4)//增加二次过街valid
    {
        qDebug()<<"list cnt error"<<cnt;
        return;
    }

    int pixIndex = 0;
    for(int i=0;i<20;i++)
    {
        if(m_bListGreen[i])
        {
            QRect rect;
            switch(i)
            {
            case 0:
                rect.setRect(266+20,0,LOADWIDTH,100);
                break;
            case 1:
                rect.setRect(216+20,0,LOADWIDTH,100);
                break;
            case 2:
                rect.setRect(166+20,0,LOADWIDTH,100);
                break;
            case 3:
                if(m_bListGreen[16+4])
                {
                    rect.setRect(170,120,60,LOADWIDTH);
                }
                else
                {
                    rect.setRect(170,120,130,LOADWIDTH);
                }
                break;
            case 4:
                rect.setRect(400,266+20,100,LOADWIDTH);
                break;
            case 5:
                rect.setRect(400,216+20,100,LOADWIDTH);
                break;
            case 6:
                rect.setRect(400,166+20,100,LOADWIDTH);
                break;
            case 7:
                if(m_bListGreen[17+4])
                {
                    rect.setRect(350,170,LOADWIDTH,60);
                }
                else
                {
                    rect.setRect(350,170,LOADWIDTH,130);
                }
                break;
            case 8:
                rect.setRect(204-20,400,LOADWIDTH,100);
                break;
            case 9:
                rect.setRect(254-20,400,LOADWIDTH,100);
                break;
            case 10:
                rect.setRect(304-20,400,LOADWIDTH,100);
                break;
            case 11:
                if(m_bListGreen[18+4])
                {
                    rect.setRect(280,350,60,LOADWIDTH);
                }
                else
                {
                    rect.setRect(210,350,130,LOADWIDTH);
                }
                break;
            case 12:
                rect.setRect(0,204-20,100,LOADWIDTH);
                break;
            case 13:
                rect.setRect(0,254-20,100,LOADWIDTH);
                break;
            case 14:
                rect.setRect(0,304-20,100,LOADWIDTH);
                break;
            case 15:
                if(m_bListGreen[19+4])
                {
                    rect.setRect(120,280,LOADWIDTH,60);
                }
                else
                {
                    rect.setRect(120,210,LOADWIDTH,130);
                }
                break;
            case 16:
                rect.setRect(230,120,60,LOADWIDTH);
                break;
            case 17:
                rect.setRect(350,240,LOADWIDTH,60);
                break;
            case 18:
                rect.setRect(210,350,60,LOADWIDTH);
                break;
            case 19:
                rect.setRect(120,210,LOADWIDTH,60);
                break;
            default:
                break;
            }
            painter.drawPixmap(rect,m_ListPix[pixIndex++]);
        }
    }
}

//void phaseWidget::setFlagDirection(bool bNorth, bool bEast, bool bSouth, bool bWest)
//{
//    m_bNorth = bNorth;
//    m_bEast = bEast;
//    m_bSouth = bSouth;
//    m_bWest = bWest;
//    this->update();
//}

void phaseWidget::setBack(quint8 dir)
{
    if(dir==0)
    {
        m_bNorth = true;
        m_bEast = true;
        m_bSouth = true;
        m_bWest = true;
        return;
    }
    m_bNorth = false;
    m_bEast = false;
    m_bSouth = false;
    m_bWest = false;
    if((dir&0x80)!=0)
    {
        m_bNorth = true;
    }
    if((dir&0x20)!=0)
    {
        m_bEast = true;
    }
    if((dir&0x08)!=0)
    {
        m_bSouth = true;
    }
    if((dir&0x02)!=0)
    {
        m_bWest = true;
    }
}

void phaseWidget::setListAllowGreen(QList<bool> listGreen, QList<QPixmap> listPix,quint16 phase)
{qDebug()<<tr("setlistallowgreen%1").arg(phase,4,16);
    m_sAllowPhase = phase;
    m_bListGreen.clear();
    m_ListPix.clear();
    m_bListGreen.append(listGreen);
    m_ListPix.append(listPix);
    this->update();
}

void phaseWidget::setIconWidth(quint16 w)
{
    m_rScale = ((qreal)w)/ICONWIDTH;
    this->setFixedSize(w,w);
}

void phaseWidget::mouseReleaseEvent(QMouseEvent *)
{
    qDebug()<<"mouse click phase icon";
    //m_bClickAble = !m_bClickAble;
//    setBackDark(true);

    emit mouseClick(this);
}

//true 显示不同 其实是显示 比较亮
void phaseWidget::setBackDark(bool b)
{
    if(b)
    {
        this->setBackgroundRole(QPalette::Light/*Midlight*/);
    }
    else
    {
        this->setBackgroundRole(QPalette::Mid);
    }
}

quint16 phaseWidget::getPhase()
{
    return m_sAllowPhase;
}
//---------------------------------------------------------
DragIcon::DragIcon(QPixmap pix,QString str,QWidget *parent) :
    QLabel(parent)
{
    setScaledContents(true);
    setPixmap(pix);

    m_IconStr = str;
    setIconCursor(true);


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

//-------------------------------------------------
ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAcceptDrops(true);
    this->setFixedSize(COLORWIDTH,BARHEIGHT);
    QPixmap pix1(BARWIDTH,BARHEIGHT);
    pix1.fill(Qt::blue);
    QPixmap pix2(BARWIDTH,BARHEIGHT);
    pix2.fill(Qt::black);
    //m_IconY = new DragIcon(QPixmap(BARWIDTH,BARHEIGHT),QString::number(1),this);
    m_IconY = new DragIcon(pix1,QString::number(1),this);//1黄
    //m_IconR = new DragIcon(QPixmap(BARWIDTH,BARHEIGHT),QString::number(2),this);
    m_IconR = new DragIcon(pix2,QString::number(2),this);//2红

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
    if(e->mimeData()->hasFormat("1"))//黄
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
    else if(e->mimeData()->hasFormat("2"))//红
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
        if(posX<BARWIDTH)
        {
            QPoint global = this->mapToGlobal(QPoint(offset.x(),offset.y()));
            //this->cursor().setPos(e->pos().x()+this->geometry().x(),offset.y()+this->geometry().y());
            this->cursor().setPos(global);
        }
        else if(posX>(COLORWIDTH-BARWIDTH))
        {
            QPoint global = this->mapToGlobal(QPoint(COLORWIDTH-BARWIDTH+offset.x(),offset.y()));
            //this->cursor().setPos(e->pos().x()+this->geometry().x(),offset.y()+this->geometry().y());
            this->cursor().setPos(global);
        }

//        if(posX<(m_ucGreen+BARWIDTH))
//        {
//            if(posX>BARWIDTH)
//            {
//                m_ucYellow = posX;
//                m_ucGreen = posX-BARWIDTH;
////                }
//            }
//            else
//            {
//                m_ucYellow = BARWIDTH;
//                m_ucGreen = 0;
//            }
//        }
//        else if(posX>(COLORWIDTH-BARWIDTH))
//        {
//            posX = COLORWIDTH-BARWIDTH;
//            m_ucYellow = COLORWIDTH-BARWIDTH;
//        }
//        else
//        {
//           m_ucYellow = posX;

//        }
        //----------------
        qint16 dif = 0;
        if(posX<=(COLORWIDTH-BARWIDTH)&&posX>=(m_ucGreen+BARWIDTH))
        {
            dif = posX - m_ucYellow;
            m_ucYellow = posX;
            if((m_ucGreen+dif)>=0)
            {
                m_ucGreen += dif;
            }
            else
            {
                m_ucGreen = 0;
            }
        }
        else if(posX<(m_ucGreen+BARWIDTH))
        {
            dif = posX-m_ucYellow;
            if((m_ucGreen+dif)>=0)
            {
                m_ucYellow = posX;
                m_ucGreen+=dif;
            }
            else
            {
                m_ucYellow = m_ucGreen+BARWIDTH;
            }
        }
        else if(posX>(COLORWIDTH-BARWIDTH))
        {
            m_ucYellow = COLORWIDTH-BARWIDTH;
        }
        //------------------
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

    emit colorTimeChange(m_TimeGreen,m_TimeYellow,m_TimeRed);
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
        emit colorTimeChange(m_TimeGreen,m_TimeYellow,m_TimeRed);
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
        emit colorTimeChange(m_TimeGreen,m_TimeYellow,m_TimeRed);
    }
    else
    {
        e->ignore();
    }
    //        delete e->mimeData();

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
        emit colorTimeChange(m_TimeGreen,m_TimeYellow,m_TimeRed);
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
//    m_TimeGreen = qRound(((qreal)m_ucGreen)*totalTime/totalColor);
//    m_TimeRed = qRound((qreal(COLORWIDTH-m_ucYellow-BARWIDTH))*totalTime/totalColor);
//    m_TimeYellow = totalTime-m_TimeGreen-m_TimeRed;
    m_TimeRed = qRound((qreal(COLORWIDTH-m_ucYellow-BARWIDTH))*totalTime/totalColor);
    m_TimeYellow = qRound(qreal(m_ucYellow-m_ucGreen-BARWIDTH)*totalTime/totalColor);
    m_TimeGreen = totalTime - m_TimeRed - m_TimeYellow;
    if(m_TimeRed>=0&&m_TimeYellow>=0&&m_TimeGreen>=0)
    {
        quint16 redWidth;
        quint16 yellowWidth;
        if(totalTime>0)
        {
            redWidth = quint16(m_TimeRed)*totalColor/totalTime;
            yellowWidth = quint16(m_TimeYellow)*totalColor/totalTime;
            m_ucYellow = COLORWIDTH-redWidth-BARWIDTH;
            m_ucGreen = m_ucYellow-yellowWidth-BARWIDTH;
            if(m_ucGreen>=0&&m_ucGreen<=(m_ucYellow-BARWIDTH))
            {
                m_IconY->move(m_ucGreen,0);
            }
            if(m_ucYellow>=(m_ucGreen+BARWIDTH)&&m_ucYellow<=(COLORWIDTH-BARWIDTH))
            {
                m_IconR->move(m_ucYellow,0);
            }
        }
    }



//    emit colorTimeChange(m_TimeGreen,m_TimeYellow,m_TimeRed);
}
