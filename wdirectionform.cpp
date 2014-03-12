#include "wdirectionform.h"
#include "ui_wdirectionform.h"
#include <QDebug>
#include <QTimerEvent>
#include <qmath.h>
#include <QDebug>
#include <QTransform>
#define GROUPWIDTH 500
#include "DCommon.h"
#include <QMouseEvent>


//-------------------------------------------------
DirectionIcon::DirectionIcon(quint8 id,QWidget *parent) :
    m_ucDirId(id),QLabel(parent)
{

    m_ucDir = 0;
    init();
    analyseId();
    this->setScaledContents(true);
    m_bConflict = false;
    m_bClickAll = true;
}

DirectionIcon::~DirectionIcon()
{
    qDebug()<<"~DirectionIcon()";
}

void DirectionIcon::init()
{
   // m_bValid = false;
    m_bGreen = false;
    m_bYellow = false;
    m_bRed = false;
    m_bFlash = false;
    m_bClick = false;

    m_bRightClick = false;
    m_bConflictGreen = false;
//    m_pConflictBase = NULL;
    m_ucPhaseId = 0;

    m_bFlashMode = true;//true 前半秒空 false后半秒空
    m_bClickAble = false;
    m_bTimer = false;
    m_bInclude = false;//包含相位标志
    m_ucIncludeNum = 0;//包含相位数量
//    m_pOverlapBase = NULL;
    m_iConflict = 0;
    this->setFlagValid(false);
    this->setPixmap(m_PixNull);
    this->disconnect(SIGNAL(includePhaseTurn(bool)));
    this->setToolTip(tr(""));
}

void DirectionIcon::initState()
{
    //m_bValid = false;
    m_bGreen = false;
    m_bYellow = false;
    m_bRed = false;
    m_bFlash = false;
    m_bClick = false;
    m_bRightClick = false;
    m_bConflictGreen = false;
    m_ucIncludeNum = 0;
    m_iConflict = 0;
//    m_pConflictBase = NULL;
    //m_ucPhaseId = 0;
    this->setPixmap(m_PixNull);
    this->setToolTip(tr(""));
}

void DirectionIcon::analyseId()
{
    bool bPed = false;
    bool bPedTwice = false;
    if(m_ucDirId>0&&m_ucDirId<DIRECTIONNUM+1)
    {
        m_ucDir = (m_ucDirId-1)/4;
        if((m_ucDirId-1)%4==3)
        {
            bPed = true;
        }
    }
    else if(m_ucDirId>DIRECTIONNUM&&m_ucDirId<DIRECTIONTOTAL+1)
    {
        m_ucDir = (m_ucDirId-1)-DIRECTIONNUM;
        bPedTwice = true;
    }
    if(m_ucDir==0||m_ucDir==2)
    {
        if(bPed)
        {
            this->setFixedSize(DIRICONHEIGHT,DIRICONWIDTH);
        }
        else if(bPedTwice)
        {
            this->setFixedSize(DIRICONHEIGHT/2,DIRICONWIDTH);
        }
        else
        {
            this->setFixedSize(DIRICONWIDTH,DIRICONHEIGHT);
        }
    }
    else if(m_ucDir==1||m_ucDir==3)
    {
        if(bPed)
        {
            this->setFixedSize(DIRICONWIDTH,DIRICONHEIGHT);
        }
        else if(bPedTwice)
        {
            this->setFixedSize(DIRICONWIDTH,DIRICONHEIGHT/2);
        }
        else
        {
            this->setFixedSize(DIRICONHEIGHT,DIRICONWIDTH);
        }
    }

}

void DirectionIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),*(this->pixmap()));
    if(m_ucPhaseId>MAXCOMPHASE)
    {
        QPen pen = painter.pen();
        pen.setWidth(10);
        painter.setPen(pen);
        painter.drawRect(this->rect());
    }
}

void DirectionIcon::setPhaseId(quint8 phaseId)
{
    m_ucPhaseId = phaseId;
    if(phaseId>0&&phaseId<MAXCOMPHASE)
    {
        m_bClickAble = true;//try
        //m_bValid = true;
    }
    else
    {
        m_bClickAble = false;
    }
}

quint8 DirectionIcon::getPhaseId()
{
    return m_ucPhaseId;
}

void DirectionIcon::setFlagValid(bool b)
{
    m_bValid = b;
    this->setVisible(b);
}

void DirectionIcon::setFlagGreen(bool b)
{
    m_bGreen = b;
    //m_bClick = b;
    if(b)
    {
        m_bYellow = false;
        m_bRed = false;
        if(m_bFlash||!m_bTimer)
            this->setPixmap(m_PixGreen);
    }
//    else if(m_bRed)
//    {
//        this->setPixmap(m_PixRed);
//    }
//    else if(m_bYellow)
//    {
//        this->setPixmap(m_PixYellow);
//    }
    else if(!m_bRed&&!m_bYellow)
    {
        this->setPixmap(m_PixNull);
    }
}

void DirectionIcon::setIconGreen(bool b)
{
    m_bGreen = b;
    m_bClick = b;
    if(b)
    {
        m_bYellow = false;
        m_bRed = false;
        if(m_iConflict==0)
        {
            this->setPixmap(m_PixGreen);
        }
        else
        {
            m_bRed = true;
            this->setPixmap(m_PixConflict);
            this->setToolTip(tr("此相位有冲突"));
//            qDebug()<<"setIconGreen------------------------------------------------- m_PixConflict";
        }
        if(m_bInclude)
        {
            emit includePhaseTurn(true);
        }
    }
    else
    {
        this->setPixmap(m_PixNull);
    }
}

void DirectionIcon::setIconRed(bool b)
{
    m_bRed = b;
    m_bRightClick = b;
    if(b)
    {
        m_bYellow = false;
        m_bGreen = false;
        this->setPixmap(m_PixRed);
    }
    else
    {
        this->setPixmap(m_PixNull);
    }
}

void DirectionIcon::setFlagYellow(bool b)
{
    m_bYellow = b;
    if(b)
    {
        m_bGreen = false;
        m_bRed = false;

        if(m_bFlash||!m_bTimer)
            this->setPixmap(m_PixYellow);
    }
//    else if(m_bRed)
//    {
//        this->setPixmap(m_PixRed);
//    }
//    else if(m_bGreen)
//    {
//        this->setPixmap(m_PixGreen);
//    }
    else if(!m_bGreen&&!m_bRed)
    {
        this->setPixmap(m_PixNull);
    }
}

void DirectionIcon::setFlagRed(bool b)
{
    m_bRed = b;
    if(b)
    {
        m_bGreen = false;
        m_bYellow = false;
        if(m_bFlash||!m_bTimer)
            this->setPixmap(m_PixRed);
    }
//    else if(m_bGreen)
//    {
//        this->setPixmap(m_PixGreen);
//    }
//    else if(m_bYellow)
//    {
//        this->setPixmap(m_PixYellow);
//    }
    else if(!m_bGreen&&!m_bYellow)
    {
        this->setPixmap(m_PixNull);
    }
}

void DirectionIcon::setPixGreen(QPixmap &pix)
{
    QTransform trans;
    m_PixGreen = pix.transformed(trans.rotate(m_ucDir*90));
}

void DirectionIcon::setPixYellow(QPixmap &pix)
{
    QTransform trans;
    m_PixYellow = pix.transformed(trans.rotate(m_ucDir*90));
}

void DirectionIcon::setPixRed(QPixmap &pix)
{
    QTransform trans;
    m_PixRed = pix.transformed(trans.rotate(m_ucDir*90));
}

void DirectionIcon::setPixNull(QPixmap &pix)
{
    QTransform trans;
    m_PixNull = pix.transformed(trans.rotate(m_ucDir*90));
    this->setPixmap(m_PixNull);
}

void DirectionIcon::setPixConflict(QPixmap &pix)
{
    QTransform trans;
    m_PixConflict = pix.transformed(trans.rotate(m_ucDir*90));
//    this->setPixmap(m_PixConflict);
}

void DirectionIcon::setFlash(bool b)
{
    if(b)
    {
        if(!m_bTimer)
        {
            m_iTimerId = this->startTimer(500);
            m_bTimer = true;
            if(m_bFlashMode)
            {
                m_bFlash = true;//true前半秒为空，false后半秒为空
            }
            else
            {
                m_bFlash = false;
            }
            //QTimerEvent*e;
            timerEvent(NULL);
        }
    }
    else
    {
        if(m_bTimer)
        {
            this->killTimer(m_iTimerId);
            m_bTimer = false;
        }
    }
}

void DirectionIcon::setFlagFlashMode(bool b)
{
    m_bFlashMode = b;
}

void DirectionIcon::timerEvent(QTimerEvent *)
{
    m_bFlash = !m_bFlash;
    if(m_bFlash)
    {
        if(m_bGreen)
        {
            this->setPixmap(m_PixGreen);
        }
        else if(m_bYellow)
        {
            this->setPixmap(m_PixYellow);
        }
        else if(m_bRed)
        {
            this->setPixmap(m_PixRed);
        }
    }
    else
    {

        this->setPixmap(m_PixNull);
    }
}

void DirectionIcon::mouseReleaseEvent(QMouseEvent *e)
{//qDebug()<<"mouseClick"<<m_bClickAble<<m_bValid;
    if(!m_bConflict)
    {
        if(m_bClickAll&&(m_bClickAble&&m_bValid&&m_iConflict==0||m_bRed)/*用于冲突相位&&m_ucPhaseId>0&&m_ucPhaseId<MAXCOMPHASE*/)
        {
            m_bClick = !m_bClick;
            if(m_bClick)
            {
                this->setPixmap(m_PixGreen);
                m_bGreen = true;
            }
            else
            {
                this->setPixmap(m_PixNull);
                m_bGreen = false;
            }
            if(m_bRed)
            {
                m_bRed = false;
            }
            if(m_bInclude)
            {
                emit includePhaseTurn(m_bClick);
            }//qDebug()<<"mouseClick mouseReleaseEvent";
            emit mouseClick(m_bClick,m_ucPhaseId);
        }
    }
    else if(m_bClickAll&&m_bClickAble&&m_bValid)
    {
        if(e->button()==Qt::LeftButton)//左键 选取 要设置的相位 为绿色
        {
            m_bClick = !m_bClick;
            if(m_bClick)
            {
                this->setPixmap(m_PixGreen);
                m_bGreen = true;
            }
            else
            {
                this->setPixmap(m_PixNull);
                m_bGreen = false;
            }
            if(m_bInclude)
            {
                emit includePhaseTurn(m_bClick);//点击 普通相位时 跟随相位也会显示 方便判断 方向冲突
            }
            emit leftClick(m_bClick,m_ucPhaseId);
        }
        else if(!m_bClick&&m_bConflictGreen)//右键选择冲突相位 为红色
        {
            m_bRightClick = !m_bRightClick;
            if(m_bRightClick)
            {
                this->setPixmap(m_PixRed);
                m_bRed = true;
            }
            else
            {
                this->setPixmap(m_PixNull);
                m_bRed = false;
            }
            emit rightClick(m_bRightClick,m_ucPhaseId);
        }
    }
}

quint32 DirectionIcon::getPhase()
{//qDebug()<<"getphase valid"<<m_bValid<<"click"<<m_bClick<<"phaseId"<<m_ucPhaseId;
    if(m_bValid&&m_bClick&&m_ucPhaseId>0&&m_ucPhaseId<MAXCOMPHASE)
    {
        return qPow(2,m_ucPhaseId-1);
    }
    else
    {
        return 0;
    }
}

void DirectionIcon::setFlagClickAble(bool b)
{
    m_bClickAble = b;
    m_bClickAll = b;
}

void DirectionIcon::setFlagInclude(bool b)
{qDebug()<<"include true"<<b;
    m_bInclude = b;
}

void DirectionIcon::setPedSmall(bool b)
{
    int w = this->width();
    int h = this->height();
    qDebug()<<"before"<<"width"<<w<<"height"<<h<<m_ucDirId;
    if(b)
    {
        if(w>h)
        {
            this->setFixedSize(DIRICONHEIGHT/2,h);
        }
        else
        {
            this->setFixedSize(w,DIRICONHEIGHT/2);
        }
    }
    else
    {
        if(w>h)
        {
            this->setFixedSize(DIRICONHEIGHT,h);
        }
        else
        {
            this->setFixedSize(w,DIRICONHEIGHT);
        }
    }
    qDebug()<<"after"<<"width"<<this->width()<<"height"<<this->height()<<m_ucDirId;
}

bool DirectionIcon::getFlagGreen()
{
    return m_bGreen;
}

bool DirectionIcon::getFlagValid()
{
    return m_bValid;
}

bool DirectionIcon::getFlagClickAble()
{
    return m_bClickAble;
}

QPixmap DirectionIcon::getGreenPix()
{/*
    if(m_bGreen)*/
        return *this->pixmap();
}

void DirectionIcon::setFlagConflict(bool b)
{
    m_bConflict = b;
}

void DirectionIcon::setFlagConflictGreen(bool b)
{
    m_bConflictGreen = b;
}

void DirectionIcon::setConflictGreen(bool b)
{
    m_bClick = b;
    if(b)
    {
        this->setPixmap(m_PixGreen);
        m_bGreen = true;
    }

    if(m_bInclude)
    {
        emit includePhaseTurn(m_bClick);
    }
    emit leftClick(m_bClick,m_ucPhaseId);
}

void DirectionIcon::editConflict(bool b)
{
    if(b)
    {
        m_iConflict++;
        this->setToolTip(tr("此相位有冲突"));
        if(m_bGreen&&!m_bRed)
        {
            this->setPixmap(m_PixConflict);
            m_bRed = true;
            this->update();
        }
        qDebug()<<"m_iConflict++"<<m_iConflict<<m_ucPhaseId;
    }
    else
    {
        if(m_iConflict>0)
        {
            m_iConflict--;
            if(m_iConflict==0)
            {
                if(m_bGreen&&m_bRed)
                {
                    this->setPixmap(m_PixGreen);
                    m_bRed = false;
                    this->update();
                }
                this->setToolTip(tr(""));
            }
        qDebug()<<"m_iConflict--"<<m_iConflict<<m_ucPhaseId;
        }
    }
}

//void DirectionIcon::setConflictBase(PhaseConflict_Table *p)
//{
//    m_pConflictBase = p;
//}

void DirectionIcon::on_includePhaseTurn(bool b)
{qDebug()<<"includePhaseTurn";
    if(m_ucPhaseId>MAXCOMPHASE)//跟随相位
    {
        if(b)
        {
            m_ucIncludeNum++;
        }
        else if(m_ucIncludeNum>0)
        {
            m_ucIncludeNum--;
        }

        if(m_ucIncludeNum>0)
        {
            this->setPixmap(m_PixGreen);
            m_bGreen = true;
        }
        else
        {
            this->setPixmap(m_PixNull);
            m_bGreen = false;
        }
    }
}
//-------------------------------------------------
WDirectionForm::WDirectionForm(QWidget *parent,bool bConflict) :
    QWidget(parent),m_bConflict(bConflict),
    ui(new Ui::WDirectionForm)
{
    ui->setupUi(this);
    setBack();
    setLayoutDir();
    if(bConflict)
    {
        this->setToolTip(tr("左键选取主相位(绿色)；\n右键选取要屏蔽的相位(红色)，第二次点击取消"));
    }
//    QGraphicsScene *scene = new QGraphicsScene(this);
//    int w = m_img.width();
//    int h = m_img.height();
//    scene->setSceneRect(-w/2,-h/2,w,h);
//    this->setScene(scene);
//    this->setCacheMode(CacheBackground);
    setLcdShow(false);
    m_bInitStageIcon = true;

    m_pConflictBase = NULL;
    m_pOverlapBase = NULL;
}

WDirectionForm::~WDirectionForm()
{
    delete ui;
}

void WDirectionForm::setLayoutDir()
{
    ui->layoutNorth->setDirection(QBoxLayout::RightToLeft);
    ui->layoutNPed->setDirection(QBoxLayout::LeftToRight);
    ui->layoutEast->setDirection(QBoxLayout::BottomToTop);
    ui->layoutEPed->setDirection(QBoxLayout::TopToBottom);
    ui->layoutSouth->setDirection(QBoxLayout::LeftToRight);
    ui->layoutSPed->setDirection(QBoxLayout::RightToLeft);
    ui->layoutWest->setDirection(QBoxLayout::TopToBottom);
    ui->layoutWPed->setDirection(QBoxLayout::BottomToTop);
    m_ListLayout.append(ui->layoutNorth);
    m_ListLayout.append(ui->layoutNPed);
    m_ListLayout.append(ui->layoutEast);
    m_ListLayout.append(ui->layoutEPed);
    m_ListLayout.append(ui->layoutSouth);
    m_ListLayout.append(ui->layoutSPed);
    m_ListLayout.append(ui->layoutWest);
    m_ListLayout.append(ui->layoutWPed);
    loadPixmap();
    for(int i=0;i<DIRECTIONTOTAL;i++)
    {
        DirectionIcon *icon = new DirectionIcon(i+1);
        connect(icon,SIGNAL(mouseClick(bool,quint8)),this,SIGNAL(mouseClick(bool,quint8)));
//         connect(icon,SIGNAL(mouseClick(quint8)),this,SLOT(on_mouseClick(quint8)));
        if(m_bConflict)
        {
            icon->setFlagConflict(true);
            connect(icon,SIGNAL(leftClick(bool,quint8)),this,SLOT(on_leftClick(bool,quint8)));
            connect(icon,SIGNAL(rightClick(bool,quint8)),this,SLOT(on_rightClick(bool,quint8)));
        }
        int dirIndex = 0;
        if(i<DIRECTIONNUM)
        {
            dirIndex = (i%4)*5;
            //icon->setPhaseId(i+1);//try
        }
        else
        {
            dirIndex = 3*5;
        }
        icon->setPixNull(m_ListPix[dirIndex+0]);
        icon->setPixGreen(m_ListPix[dirIndex+1]);
        icon->setPixYellow(m_ListPix[dirIndex+2]);
        icon->setPixRed(m_ListPix[dirIndex+3]);
        icon->setPixConflict(m_ListPix[dirIndex+4]);
        m_ListDirIcon.append(icon);

        int dir = 0;
        if(i<DIRECTIONNUM)
        {
            dir = i/4;
            if(i%4!=3)
            {
                m_ListLayout[dir*2]->addWidget(icon);
            }
            else
            {
                m_ListLayout[dir*2+1]->addWidget(icon);
            }
        }
        else
        {
            dir = i-DIRECTIONNUM;
            m_ListLayout[dir*2+1]->addWidget(icon);
        }
        //icon->setFlagClickAble(true);//try

        //setDirIconValid(i,true);
      //  icon->setFlagGreen(true);
//        icon->setFlagYellow(true);
//        icon->setFlagRed(true);
//        icon->setFlash(true);
    }
}

//dir: 0xff  8北 7东北 6东 5东南 4南 3西南 2西 1西北暂时只用4方向//可能得改 错误
void WDirectionForm::setBack(quint8 dir)
{
    QImage img;
    switch(dir&0xaa)
    {
    case 0xaa:
        img.load(":/Files/images/back.jpg");
        break;
    case 0x2a:
        img.load(":/Files/images/north.jpg");
        break;
    case 0x8a:
        img.load(":/Files/images/east.jpg");
        break;
    case 0xa2:
        img.load(":/Files/images/south.jpg");
        break;
    case 0xa8:
        img.load(":/Files/images/west.jpg");
        break;
    case 0x22:
        img.load(":/Files/images/ew.jpg");
        break;
    case 0x88:
        img.load(":/Files/images/sn.jpg");
        break;
    default:
        img.load(":/Files/images/back.jpg");
        break;
    }
    m_img = img;
    QPalette p = this->palette();
    p.setBrush(QPalette::Background,QBrush(img));
    this->setPalette(p);
    this->setAutoFillBackground(true);
    //update();
}

QImage WDirectionForm::getBackImage()
{
    return m_img;
}

void WDirectionForm::setDirIconValid(quint8 index, bool b)
{
    m_ListDirIcon[index]->setFlagValid(b);
    if(index<DIRECTIONNUM&&index%4==3)
    {
        m_ListDirIcon[index]->setPedSmall(false);
    }
    if(index>(DIRECTIONNUM-1))
    {
        int dir = index-DIRECTIONNUM;
        m_ListDirIcon[dir*4+3]->setPedSmall(b);
        qDebug()<<"turn small"<<dir*4+3<<b;
    }
}

//一个方向4种颜色，共7个方向+绿冲突 5种颜色7个方向
void WDirectionForm::loadPixmap()
{
    m_ListPix.clear();
    QStringList listCol;
    listCol<<"white"<<"green"<<"yellow"<<"red"<<"conflict";
    QStringList listDir;
    listDir<<"l.jpg"<<"s.jpg"<<"r.jpg"<<"ped.jpg"<<"sl.jpg"<<"rs.jpg"<<"rsl.jpg";
    int cntCol = listCol.count();
    int cntDir = listDir.count();
    for(int i=0;i<cntDir;i++)//7个方向
    {
        for(int j=0;j<cntCol;j++)//5种颜色
        {
            QString path = ":/Files/images/";
            path.append(listCol[j]);
            path.append(listDir[i]);
            QImage img;
            if(img.load(path))
            {
                m_ListPix.append(QPixmap::fromImage(img));
            }
            else
            {
                qDebug()<<"wdirectionform load img error"<<listCol[i]<<listDir[j];
            }
        }
    }
}

int WDirectionForm::getListIconIndex(quint8 loadNo)
{
    if(loadNo>31)
    {
        int listIndex = -1;
        int dir = (loadNo>>5)-1;
        if((loadNo&0x18)!=0)//人行
        {
            if((loadNo&0x07)!=2)//0,1
            {
                listIndex = dir*4+3;
            }
            else//2次
            {
                listIndex = dir+MAX_PHASEMAP_NUM;
            }
        }
        else
        {
            switch(loadNo&0x07)
            {
            case 1:
                listIndex = dir*4;
                break;
            case 2:
            case 3:
            case 6:
            case 7:
                listIndex = dir*4+1;
                break;
            case 4:
                listIndex = dir*4+2;
                break;
            default:
                break;
            }
        }
        if(listIndex<20)//所有路标20
        {
            return listIndex;
        }
        else
        {
            return -1;
        }
    }
    else if(loadNo>0&&loadNo<17)
    {
        return loadNo-1;
    }
    return -1;
}

int WDirectionForm::getListPixIndex(quint8 loadNo)
{
    int listIndex = -1;
    //int dir = (loadNo>>5)-1;
    if((loadNo&0x18)!=0)//人行
    {
        listIndex = 3*5;
    }
    else
    {
        switch(loadNo&0x07)
        {
        case 1:
            listIndex = 0*5;
            break;
        case 2:
            listIndex = 1*5;
            break;
        case 3:
            listIndex = 4*5;
            break;
        case 6:
            listIndex = 5*5;
            break;
        case 7:
            listIndex = 6*5;
            break;
        case 4:
            listIndex = 2*5;
            break;
        default:
            break;
        }
        if(listIndex<(m_ListPix.count()-4))
        {
            return listIndex;
        }
        else
        {
            return -1;
        }
    }
    return listIndex;
}

QList<bool> WDirectionForm::getListFlagGreen()
{
    QList<bool> list;
    foreach(DirectionIcon* icon,m_ListDirIcon)
    {
        list.append(icon->getFlagGreen());
    }
    list.append(m_ListDirIcon[16]->getFlagValid());
    list.append(m_ListDirIcon[17]->getFlagValid());
    list.append(m_ListDirIcon[18]->getFlagValid());
    list.append(m_ListDirIcon[19]->getFlagValid());
    return list;
}

QList<QPixmap> WDirectionForm::getListPixGreen()
{
    QList<QPixmap> list;
    foreach(DirectionIcon* icon,m_ListDirIcon)
    {
        if(icon->getFlagGreen())
        {
            list.append(icon->getGreenPix());
        }
    }
    return list;
}

quint16 WDirectionForm::getPhase()
{
    quint16 phase = 0;
    foreach(DirectionIcon* icon,m_ListDirIcon)
    {
        phase += icon->getPhase();
    }
    return phase;
}


DirectionIcon* WDirectionForm::getIcon(quint8 phaseId)
{
    if(phaseId==0)
    {
        return NULL;
    }
    foreach(DirectionIcon*icon,m_ListDirIcon)
    {
        if(icon->getPhaseId()==phaseId)
        {
            return icon;
        }
    }
    if(phaseId>MAXCOMPHASE&&phaseId<(MAXCOMPHASE+MAX_OVERLAP_NUM+1))
    {
        phaseId -= MAXCOMPHASE;
        if(m_pOverlapBase!=NULL)
        {
            Overlap_Table *p = m_pOverlapBase+phaseId-1;
            if(p->bIncludedPhaseLen>0)
            {
                quint8 comPhase = p->bIncludedPhase[0];
                if(comPhase>0)
                {
                    foreach(DirectionIcon*icon,m_ListDirIcon)
                    {
                        if(icon->getPhaseId()==comPhase)
                        {
                            return icon;
                        }
                    }
                }
            }
        }

    }
    return NULL;
}

void WDirectionForm::setLcdShow(bool b)
{
    ui->lcdNumber->setVisible(b);
}

void WDirectionForm::setLcdNum(int time)
{
    ui->lcdNumber->display(time);
}

void WDirectionForm::setAllowPhase(quint16 phase)
{
    qDebug()<<"setAllowPhase"<<phase;
    clearState();
    for(int i=0;i<16;i++)
    {
        if((phase&0x0001)==1)
        {
            quint8 phaseId = i+1;
            DirectionIcon* icon = getIcon(phaseId);
//            if(icon!=NULL)
//            {
//                icon->setIconGreen(true);
//            }
            if(m_pConflictBase!=NULL)
            {
                quint16 conflict = (m_pConflictBase+i)->uConflictPhase;
                quint16 temp = 1;
               // qDebug()<<tr("conflict%1").arg(conflict,16,2);
                for(int j=0;j<16;j++)
                {
//                    conflict>>j;
                    if(((conflict>>j)&temp)==1)
                    {
                        foreach(DirectionIcon* dir,m_ListDirIcon)
                        {//qDebug()<<"phaseId:"<<dir->getPhaseId()<<"editConflict"<<"dir->getPhaseId()"<<dir->getPhaseId()<<"j+1"<<j+1;
                            if(dir->getPhaseId()==(j+1))
                            {
                                dir->editConflict(true);

                            }
                        }
                    }
                }
            }
            else
            {
                qDebug()<<"setAllowPhase m_pConflictBase=NULL";
            }
            if(icon!=NULL)
            {
                icon->setIconGreen(true);
            }
        }
        phase>>=1;
    }

    if(!m_bInitStageIcon)
    {qDebug()<<" emit mouseClick setAllowPhase"<<phase;
        emit mouseClick();
    }
}

//更改阶段时
void WDirectionForm::clearState()
{
    foreach(DirectionIcon*icon,m_ListDirIcon)
    {
        icon->initState();
    }
}

void WDirectionForm::changeStage()
{
    foreach(DirectionIcon*icon,m_ListDirIcon)
    {
        icon->init();
    }
}

void WDirectionForm::setIconPixmap(QList<quint8> list)
{
    foreach(quint8 dirId,list)
    {
        int iconIndex = getListIconIndex(dirId);
        int pixIndex = getListPixIndex(dirId);
        if(iconIndex!=-1&&pixIndex!=-1)
        {
            DirectionIcon *icon = m_ListDirIcon[iconIndex];
            icon->setPixNull(m_ListPix[pixIndex+0]);
            icon->setPixGreen(m_ListPix[pixIndex+1]);
            icon->setPixYellow(m_ListPix[pixIndex+2]);
            icon->setPixRed(m_ListPix[pixIndex+3]);
            icon->setPixConflict(m_ListPix[pixIndex+4]);
        }
    }
}

void WDirectionForm::setFlagValid(QList<bool>list)
{
    int cnt = list.count();
    if(cnt!=m_ListDirIcon.count())
    {
        qDebug()<<"setflagvalid cnt error";
        return;
    }
    for(int i=0;i<cnt;i++)
    {/*
        m_ListDirIcon[i]->setFlagValid(list[i]);*/
        setDirIconValid(i,list[i]);
    }
}

void WDirectionForm::setPhaseId(QList<quint8> list)
{
    int cnt = list.count();
    if(cnt!=m_ListDirIcon.count())
    {
        qDebug()<<"setphaseid cnt error";
        return;
    }
    for(int i=0;i<cnt;i++)
    {
        m_ListDirIcon[i]->setPhaseId(list[i]);
    }
}

void WDirectionForm::setOverlapConnect(QList<quint8> listPhase)
{
    int cnt = listPhase.count();
    if(cnt<2)
    {
        return;
    }
    DirectionIcon* overlap = getIcon(listPhase[0]);

    if(overlap==NULL)
    {
        return;
    }
    for(int i=1;i<cnt;i++)
    {
        DirectionIcon* icon= getIcon(listPhase[i]);
        if(icon!=NULL)
        {
            icon->setFlagInclude(true);
            connect(icon,SIGNAL(includePhaseTurn(bool)),overlap,SLOT(on_includePhaseTurn(bool)));
        }
    }
}

void WDirectionForm::setUnClickAble()
{
    foreach(DirectionIcon* icon,m_ListDirIcon)
    {
        icon->setFlagClickAble(false);
    }
}

void WDirectionForm::setFlagInitStageIcon(bool b)
{
    m_bInitStageIcon = b;
}

void WDirectionForm::killFlash()
{
    foreach(DirectionIcon*icon,m_ListDirIcon)
    {
        icon->setFlash(false);
    }
}

void WDirectionForm::setConflict(quint8 phase, quint16 conflict,bool b)
{
    for(int i=0;i<16;i++)
    {
        if(i!=(phase-1))
        {
            quint16 c = conflict>>i;
            if((c&0x0001)==1)
            {
                foreach(DirectionIcon*icon,m_ListDirIcon)
                {
                    if(icon->getPhaseId()==(i+1))
                    {
                        if(m_bConflict)
                        {
                            icon->setIconRed(true);
                        }
                        else
                        {
                            icon->editConflict(b);
                        }
                    }
                }
            }
        }
    }
}

void WDirectionForm::setConflictBase(PhaseConflict_Table *p)
{
//    foreach(DirectionIcon*icon,m_ListDirIcon)
//    {
//        if(icon->getFlagClickAble())
//        {
//            icon->setConflictBase(p);
//        }
//    }

    m_pConflictBase = p;
}

void WDirectionForm::setConflictGreen(quint8 phaseId, bool b)
{
    if(phaseId>0&&phaseId<(MAX_PHASE_NUM+1))
    {
        foreach(DirectionIcon*icon,m_ListDirIcon)
        {
            if(icon->getPhaseId()==phaseId)
            {
                icon->setConflictGreen(b);
                break;
            }
        }
    }
}

void WDirectionForm::setOverlapBase(Overlap_Table *p)
{
    m_pOverlapBase = p;
}

//void WDirectionForm::on_mouseClick(quint8 phaseId)
//{

//    emit mouseClick(phaseId);
//}

void WDirectionForm::on_leftClick(bool b,quint8 phase)
{
    qDebug()<<"on_leftClick"<<b<<phase;
    foreach(DirectionIcon *icon,m_ListDirIcon)
    {
        if(icon->getPhaseId()!=phase)
        {
            icon->initState();
            if(b)
            {
                icon->setFlagConflictGreen(b);
            }
        }
    }

    emit leftClick(b,phase);
}

void WDirectionForm::on_rightClick(bool b,quint8 phase)
{
    qDebug()<<"on_rightClick"<<b<<phase;
    emit rightClick(b,phase);
}

//void WDirectionForm::mouseReleaseEvent(QMouseEvent *)
//{
//    this->scale(0.5,0.5);
//}

//void WDirectionForm::drawBackground(QPainter *painter, const QRectF &rect)
//{
//    painter->drawPixmap(int(this->sceneRect().left()),int(this->sceneRect().top()),QPixmap::fromImage(m_img));
//}
//-------------------------------------------------------------------------
StageGroup::StageGroup(QWidget *parent) :
    QWidget(parent)
{
    m_pIcon = NULL;
    m_ucDir = 0;
    setFixedSize(500,120);
    m_pLayoutGroup = new QHBoxLayout(this);
//    m_bClickPhase = true;
}

StageGroup::~StageGroup()
{
    qDebug()<<"~StageGroup()";
}

void StageGroup::addStage(phaseWidget *icon)
{
//    QList<phaseWidget*> list = this->findChildren<phaseWidget*>();
    int cnt = m_pListIcon.count();
    if(cnt>15)
    {
        return;
    }
    if(icon==NULL)
    {
        icon = new phaseWidget();
        icon->setBack(m_ucDir);
    }

    int index = 0;
    if(m_pIcon!=NULL)
    {
        index = m_pListIcon.indexOf(m_pIcon)+1;
    }
    for(int i=index;i<cnt;i++)
    {
        m_pLayoutGroup->removeWidget(m_pListIcon[i]);
    }

    m_pLayoutGroup->addWidget(icon);
    for(int i=index;i<cnt;i++)
    {
        m_pLayoutGroup->addWidget(m_pListIcon[i]);
    }
    connect(icon,SIGNAL(mouseClick(phaseWidget*)),this,SLOT(on_mouseClick(phaseWidget*)));
    m_pListIcon.insert(index,icon);
    on_mouseClick(icon);//点击状态
    setIconWidth();
}

void StageGroup::setListAllowGreen(QList<bool> listGreen, QList<QPixmap> listPix, quint16 phase)
{
    if(m_pIcon!=NULL)
    {
        m_pIcon->setListAllowGreen(listGreen,listPix,phase);
    }
}

void StageGroup::clearGroup()
{
//    if(m_bClearStageGroup)
    m_pListIcon.clear();
    QList<phaseWidget*> list = this->findChildren<phaseWidget*>();
    foreach(phaseWidget*icon,list)
    {
        delete icon;
        //icon->close();
    }
    m_pIcon = NULL;
}

void StageGroup::delIcon()
{
    if(m_pIcon!=NULL)
    {
        phaseWidget*icon = NULL;
        int index = m_pListIcon.indexOf(m_pIcon);
        int cnt = m_pListIcon.count();
        if(index<(cnt-1))
        {
            icon = m_pListIcon[index+1];
        }
        else if(cnt>1)
        {
            icon = m_pListIcon[index-1];
        }
        m_pListIcon.removeAt(index);
        m_pIcon->close();
        m_pIcon = NULL;
        if(icon!=NULL)
        {
            on_mouseClick(icon);
        }
        setIconWidth();
    }

}

void StageGroup::setBack(quint8 dir)
{
    m_ucDir = dir;
}

void StageGroup::setIconWidth()
{
    QList<phaseWidget*> list = this->findChildren<phaseWidget*>();
    int cnt = list.count();
    qDebug()<<"icon cnt:"<<cnt;
    int w = 100;
    if(cnt>4)
    {
         w = GROUPWIDTH/cnt-5;
    }

    foreach(phaseWidget*icon,list)
    {
        icon->setIconWidth(w);
    }
}

void StageGroup::getStageIndex(quint8 &index, quint8 &cnt)
{
    cnt = m_pListIcon.count();
    index = 0;
    if(m_pIcon!=NULL)
    {
        index = m_pListIcon.indexOf(m_pIcon);
        if(index==-1)
        {
            index = 0;
        }
    }
}

void StageGroup::setIconDark(quint8 index)
{
    int cnt = m_pListIcon.count();
    if(index<cnt)
    {
        for(int i=0;i<cnt;i++)
        {
            m_pListIcon[i]->setBackDark(i==index?true:false);
        }
    }
}

void StageGroup::mouseClick(quint8 index)
{
    if(index<m_pListIcon.count())
    {
//        setIconDark(index);
        phaseWidget* icon = m_pListIcon[index];
        on_mouseClick(icon);
    }
}

void StageGroup::on_mouseClick(phaseWidget *icon)
{
    m_pIcon = icon;
    emit mouseClick(icon->getPhase());
//    if(m_bClickPhase)//修改为 原先 在 wstage 里传递changeStageIndex（index）
//    {
//        emit mouseClick(icon->getPhase());
//    }
//    else
//    {
//        int index = m_pListIcon.indexOf(icon);
//        if(index!=-1)
//        {
//            emit mouseClick(index+1);
//        }
//    }
    QList<phaseWidget*> list = this->findChildren<phaseWidget*>();
    foreach(phaseWidget*w,list)
    {
        if(icon==w)
        {
            w->setBackDark(true);
        }
        else
        {
            w->setBackDark(false);
        }
    }
}
