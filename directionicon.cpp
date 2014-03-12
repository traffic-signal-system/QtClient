#include "directionicon.h"
#include <QTimerEvent>
#include <qmath.h>
#include <QDebug>
#include <QTransform>


DirectionIcon::DirectionIcon(quint8 id,QWidget *parent) :
    m_ucDirId(id),QLabel(parent)
{

    m_ucDir = 0;
    init();
    analyseId();
    this->setScaledContents(true);
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
    m_ucPhaseId = 0;

    m_bFlashMode = true;//true 前半秒空 false后半秒空
    m_bClickAble = false;
    m_bTimer = false;
    m_bInclude = false;//包含相位标志
    m_ucIncludeNum = 0;//包含相位数量
    this->setFlagValid(false);
    this->disconnect(SIGNAL(includePhaseTurn(bool)));
}

void DirectionIcon::initState()
{
    //m_bValid = false;
    m_bGreen = false;
    m_bYellow = false;
    m_bRed = false;
    m_bFlash = false;
    m_bClick = false;
    m_ucIncludeNum = 0;
    //m_ucPhaseId = 0;
    this->setPixmap(m_PixNull);
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
        this->setPixmap(m_PixGreen);
    }
    else
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
        this->setPixmap(m_PixGreen);
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

void DirectionIcon::setFlagYellow(bool b)
{
    m_bYellow = b;
    if(b)
    {
        m_bGreen = false;
        m_bRed = false;
        this->setPixmap(m_PixYellow);
    }
    else
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
        this->setPixmap(m_PixRed);
    }
    else
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

void DirectionIcon::mouseReleaseEvent(QMouseEvent *ev)
{//qDebug()<<"mouseClick"<<m_bClickAble<<m_bValid;
    if(m_bClickAble&&m_bValid/*&&m_ucPhaseId>0&&m_ucPhaseId<MAXCOMPHASE*/)
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
            emit includePhaseTurn(m_bClick);
        }
        emit mouseClick();

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

QPixmap DirectionIcon::getGreenPix()
{/*
    if(m_bGreen)*/
        return *this->pixmap();
}

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
