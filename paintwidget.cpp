#include "paintwidget.h"
#include "pdataprocess.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QDebug>

#include <QTimer>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDir>
#include <qmath.h>
#define CHANNELNUM 16


/*
   green:绿色通道;
   yellow:黄色通道;
   red:红色通道;
   flash:闪动通道;
   bLcd:lcd数字标志;
   time:阶段已用时间;
   simulate:模拟标志；
   timegreenflash:绿闪时间
   timegreen:阶段绿灯时间;
   timeyellow:阶段黄灯时间;
   timered:阶段红灯时间;

      bit0：东人行
      bit1：东车右行
      bit2：东车直行
      bit3：东车左行
            南
            西
            北
用转换函数 转为 北东南西  在 阶段配时 时 方向值转为相位值
*/
WPhaseStageWidget::WPhaseStageWidget(QWidget *parent,quint16 green,quint16 yellow,quint16 red,quint16 flash,quint16 width,bool bLcd,quint8 time,bool bsimulate,quint8 timegreenflash,quint8 timegreen,quint8 timeyellow,quint8 timered) :
    QWidget(parent)
{
    setPalette(QPalette(Qt::darkGreen));
    setAutoFillBackground(true);
    qDebug()<<"WPhaseStageWidget real show";
    m_fScale = qreal(width)/600;
    m_usWidth = width;
    m_usHeight = width;
    this->resize(m_usWidth,m_usHeight);
    this->setMinimumSize(m_usWidth,m_usHeight);
    this->setMaximumSize(m_usWidth,m_usHeight);

    m_bTimeEvent = true;
    m_bTimerStart = false;
    m_bNumColor = false;
   m_bSimulate = bsimulate;

   m_bIcon = false;
   m_bClickable = true;
   m_bClick = false;
   m_bClicked = false;

   m_bRealShow = true;//实时显示
   m_pDataProcess = NULL;
   m_pListChannelMap = NULL;
   m_pListComMap = NULL;
   m_pListOverlapMap = NULL;
    //m_bFlash = false;
   m_ucStageCnt = 0;

   m_uiNum = 0;

    m_bRed = false;

    if(0!=yellow)
    {
        m_bYellow = true;
    }
    else
    {
        m_bYellow = false;
    }
    if(0!=flash)
    {
        m_bFlash = true;
    }
    else
    {
        m_bFlash = false;
    }
    if(0!=green)
    {
        m_bGreen = false;
    }
    //m_bGreen = false;

    //m_iIndex = 0;

    for(int i=0;i<CHANNELNUM;i++)
    {
        m_bListGreen<<false;
        m_bListYellow<<false;
        m_bListRed<<false;
        m_bListFlash<<false;
        m_bListFlashChange<<false;
        m_bListPhaseChange<<false;

    }

//    setData(green,yellow,red,flash,time,timegreenflash,timegreen,timeyellow,timered);
    m_ucStageNo = 0;
    m_usTimePass = 0;
    m_bLcdNum = bLcd;
    m_LcdNumber = NULL;

//    if(m_bLcdNum||m_bSimulate)
//    {
//        m_bLcdNum = true;
//        m_LcdNumber = new QLCDNumber();

//        m_LcdNumber->setDigitCount(2);

//        //QGridLayout *gLayout = new QGridLayout(this);
//        QVBoxLayout *vLayout = new QVBoxLayout(this);


//        vLayout->setMargin(250);

//        vLayout->addWidget(m_LcdNumber);

//    }

    loadImage();
    setData(green,yellow,red,flash,time,timegreenflash,timegreen,timeyellow,timered);


}

WPhaseStageWidget::WPhaseStageWidget(PDataProcess*p,quint16 green,quint16 width,QWidget *parent):QWidget(parent),m_pDataProcess(p)
{

    setPalette(QPalette(Qt::darkGreen));
    setAutoFillBackground(true);
    qDebug()<<"WPhaseStageWidget stage show";
    m_fScale = qreal(width)/600;
    qDebug()<<m_fScale;
    m_usWidth = width;
    m_usHeight = width;


    m_bRed = false;//阶段红灯  用于lcd红色

    m_bYellow = false;//有黄灯 用于lcd黄色
    m_bFlashGreen = false;

    m_bTimeEvent = false;
    m_bTimerStart = false;
    m_bLcdNum = false;
    m_bFlash = false;
    m_bSimulate = false;
    m_bIcon = true;
    m_bNumColor = false;//闪烁时 数字闪烁

    m_bRealShow = false;//实时显示
    //m_pDataProcess = NULL;
    m_pListChannelMap = NULL;
    m_pListComMap = NULL;
    m_pListOverlapMap = NULL;

    setListPoint();

    m_LcdNumber = NULL;

    m_uiNum = 0;

    m_bClickable = true;
    m_bClick = true;
    m_bClicked = false;
    m_usTimePeriod = 0;
    m_ucStageCnt = 0;
    if(m_bIcon)
    {
        this->resize(500*m_fScale,500*m_fScale);
        this->setMinimumSize(500*m_fScale,500*m_fScale);
        this->setMaximumSize(500*m_fScale,500*m_fScale);
        m_bClickable = false;
    }
    else
    {
        this->resize(m_usWidth,m_usHeight);
    }

    for(int i=0;i<CHANNELNUM;i++)
    {
        m_bListGreen<<false;
        m_bListYellow<<false;
        m_bListRed<<false;
        m_bListFlash<<false;
        m_bListFlashChange<<false;
        m_bListPhaseChange<<false;
    }

//    m_ucTime;//阶段已过秒数
//    m_ucTimeGreenFlash;
//    m_ucTimeGreen;
//    m_ucTimeYellow;
//    m_ucTimeRed;

    if(0!=green)
    {
        m_bGreen = true;//阶段绿灯
    }
    m_ucStageNo = 0;
    loadImage();
    setData(green);
}

WPhaseStageWidget::WPhaseStageWidget(QList<quint16> listgreen, QList<quint8> timelistgreen, QList<quint8> timelistyellow, QList<quint8> timelistred, quint16 width,quint8 timegreenflash, QWidget *parent):QWidget(parent)
{
    setPalette(QPalette(Qt::darkGreen));
    setAutoFillBackground(true);
    qDebug()<<"WPhaseStageWidget simulate";
    m_fScale = qreal(width)/600;
    m_usWidth = width;
    m_usHeight = width;

    //this->move(50,50);





    m_bRed = false;//阶段红灯  用于lcd红色

    m_bYellow = false;//有黄灯 用于lcd黄色
    m_bFlashGreen = false;

    m_bTimeEvent = false;
    m_bTimerStart = false;
    m_bLcdNum = false;
    m_bFlash = false;
    m_bSimulate = true;

    m_bIcon = false;

    m_bNumColor = false;//闪烁时 数字闪烁
    m_LcdNumber = NULL;

    m_bClickable = false;
    m_bClick = false;
    m_bClicked = false;

    m_bRealShow = false;//实时显示
    m_pDataProcess = NULL;
    m_pListChannelMap = NULL;
    m_pListComMap = NULL;
    m_pListOverlapMap = NULL;

    m_uiNum = 0;

    m_ucStageCnt = 0;

    if(m_bIcon)
    {
        this->resize(m_usWidth-100*m_fScale,m_usHeight-100*m_fScale);
    }
    else
    {
        this->resize(m_usWidth,m_usHeight);
    }


    for(int i=0;i<CHANNELNUM;i++)
    {
        m_bListGreen<<false;
        m_bListYellow<<false;
        m_bListRed<<false;
        m_bListFlash<<false;
        m_bListFlashChange<<false;
        m_bListPhaseChange<<false;
    }


//    m_ListPhaseStage.append(listgreen);
//    m_ListTimeGreen.append(timelistgreen);
//    m_ListTimeYellow.append(timelistyellow);
//    m_ListTimeRed.append(timelistred);
//    m_ucStageNo = 0;
//    m_ucStageCnt = m_ListPhaseStage.count();
    setListData(listgreen,timelistgreen,timelistyellow,timelistred);

    loadImage();
    //setData(m_ListPhaseStage[m_ucStageNo]);
    m_usTimePass = 0;
    setData(m_ListPhaseStage[m_ucStageNo-1],0,0,0,0,timegreenflash,m_ListTimeGreen[m_ucStageNo-1],m_ListTimeYellow[m_ucStageNo-1],m_ListTimeRed[m_ucStageNo-1]);
    //setData(m_ListPhaseStage[m_ucStageNo],0,0,0,0,timegreenflash,18,9,9);
    qDebug()<<"widget width:"<<this->geometry().width()<<"height"<<this->geometry().height();
}

WPhaseStageWidget::~WPhaseStageWidget()
{
//    m_bListGreen.clear();
//    m_bListYellow.clear();
//    m_bListRed.clear();
//    m_bListFlash.clear();
//    m_bListPhaseChange.clear();
//    m_imgList.clear();
//    m_ListPhaseStage.clear();
//    m_ListTimeGreen.clear();
//    m_ListTimeYellow.clear();
//    m_ListTimeRed.clear();
    clearData();


    if(m_bTimerStart)
    {
        killTimer(m_uiTimerId);
    }
    if(m_LcdNumber!=NULL)
    {
        delete m_LcdNumber;
    }

}

void WPhaseStageWidget::clearData()
{
    m_bListGreen.clear();
    m_bListYellow.clear();
    m_bListRed.clear();
    m_bListFlash.clear();
    m_bListPhaseChange.clear();
    m_imgList.clear();

    m_ListPhaseStage.clear();
    m_ListTimeGreen.clear();
    m_ListTimeYellow.clear();
    m_ListTimeRed.clear();
    m_ListOption.clear();
}

void WPhaseStageWidget::clearListData()
{
    m_ListPhaseStage.clear();
    m_ListTimeGreen.clear();
    m_ListTimeYellow.clear();
    m_ListTimeRed.clear();
    m_ListOption.clear();
    m_ucStageNo = 0;
}

void WPhaseStageWidget::loadImage()
{
    m_imgList.clear();
    QStringList colorList;
    colorList<<"null"<<"green"<<"yellow"<<"red";
    QStringList directionList;
    directionList<<"ped.jpg"<<"r.jpg"<<"s.jpg"<<"l.jpg";
    QImage img;

   // QDir dir = QDir::currentPath();

    //qDebug()<<"path:"<<dir.absolutePath();":/images/logo.jpg"
    //QString path = "D:/kwq/practice/UTCS/build/images/";
    QString path = ":Files/images/";
    //QString path = "../picWidget/images/";
    for(int i=0;i<4;i++)
    {
        QString name = path+colorList[i];
        for(int j=0;j<4;j++)
        {
            if(img.load(name+directionList[j]))
            {
                QPixmap pixmap = QPixmap::fromImage(img);
                m_imgList<<pixmap;
            }
            else
            {
                qDebug()<<"load img error";
            }
        }
    }

}

void WPhaseStageWidget::paintEvent(QPaintEvent *)
{
    //qDebug()<<"m_uiNum:"<<++m_uiNum;
    QPainter painter(this);
    if(m_bIcon)
    {
        painter.translate(-50*m_fScale,-50*m_fScale);

    }

    painter.scale(m_fScale,m_fScale);



    QPen pen(Qt::darkGray);
    pen.setWidth(5);

    QBrush brush;
    if(m_bIcon)
    {
         QBrush brushTemp(Qt::white);
         painter.setBrush(brushTemp);
    }
    else
    {
        QBrush brushTemp(Qt::lightGray);
        painter.setBrush(brushTemp);
    }
   // QBrush brush(Qt::darkGray);
    painter.setPen(pen);
    //painter.setBrush(brush);


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

    QBrush brushW(Qt::white);

    painter.setBrush(brushW);
    pen = painter.pen();
    pen.setColor(Qt::gray);
    pen.setWidth(1);
    painter.setPen(pen);


    painter.translate(300,300);
    painter.save();

    int color = 0;

    int xPoint = -75;
    int yPoint = -240;
    int iDis = 40;
    int xHPoint = -80;
    int yHPoint = -150;

    qreal picScale = 1.8;

    if(m_bIcon)
    {
        xPoint = -55;
        yPoint = -155;
        iDis = 40;
        xHPoint = -60;
        yHPoint = -67;
    }

    QStringList strList;
    QFont font("Times", 30, QFont::Bold);

    painter.setFont(font);
    //strList<<"East"<<"South"<<"West"<<"North";
    strList<<QObject::tr("东")<<QObject::tr("南")<<QObject::tr("西")<<QObject::tr("北");
    //strList<<"E"<<"S"<<"W"<<"N";
    for(int i=0;i<4;i++)
    {


        painter.rotate(90);

        QPen penText(Qt::black);
        painter.setPen(penText);


        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

        if(!m_bIcon)
        {
            painter.drawText(-30,-300,50,50,Qt::AlignCenter,strList[i]);
            QPen penT = painter.pen();
            penT.setColor(Qt::white);
            painter.setPen(penT);
            brush = painter.brush();
            //QBrush brushT(Qt::transparent);
            QBrush brushT(Qt::white);
            painter.setBrush(brushT);
            for(int j=0;j<9;j++)
            {

                painter.drawRect(-94+j*23,-160,2,40);
                //painter.setBrush(brush);
            }
        }

        if(m_bListGreen[i*4+0])
        {
            if(m_bListFlash[i*4+0]||m_bFlashGreen)
            {
                //qDebug()<<i*4+0<<"change";
                m_bListFlashChange[i*4+0] = !m_bListFlashChange[i*4+0];
            }
            if(m_bListFlashChange[i*4+0]&&(m_bListPhaseChange[i*4+0]||m_bRealShow))
            {
                color = 0;
                //qDebug()<<i*4+0<<"flash";
            }
            else
            {
                if(m_bGreen||!m_bListPhaseChange[i*4+0])
                {
                    color = 1;
                }
                else if(m_bYellow&&m_bListPhaseChange[i*4+0])
                {
                    color = 3;
                }
                else if(m_bRed&&m_bListPhaseChange[i*4+0])
                {
                    color = 3;
                }
            }

        }
        else if(m_bListYellow[i*4+0])
        {

            if(m_bListFlash[i*4+0])
            {
                m_bListFlashChange[i*4+0] = !m_bListFlashChange[i*4+0];
            }
            if(m_bListFlashChange[i*4+0])
            {
                color = 0;
            }
            else
            {
                color = 2;
            }
        }
        else if(m_bListRed[i*4+0])
        {
            color = 3;
        }
        else
        {
            color = 0;
        }
        painter.setCompositionMode(QPainter::CompositionMode_Multiply);
       // painter.setCompositionMode(QPainter::CompositionMode_ColorBurn);

        if(m_bIcon)
        {
            painter.save();
            painter.scale(picScale,picScale);
            painter.drawPixmap(xHPoint,yHPoint,113,20,m_imgList[color*4+0]);
            painter.restore();
        }
        else
        {
            painter.drawPixmap(xHPoint,yHPoint,113,20,m_imgList[color*4+0]);
        }



        //----------------
        if(m_bListGreen[i*4+1])
        {
            if(m_bListFlash[i*4+1]||m_bFlashGreen)
            {
                //qDebug()<<"change";
                if(i==1)
                qDebug()<<i*4+1<<"change";
                m_bListFlashChange[i*4+1] = !m_bListFlashChange[i*4+1];
            }
            if(m_bListFlashChange[i*4+1]&&(m_bListPhaseChange[i*4+1]||m_bRealShow))
            {
                color = 0;
                if(i==1)
                qDebug()<<i*4+1<<"flash null";
            }
            else
            {
                if(m_bGreen||!m_bListPhaseChange[i*4+1])
                {
                    if(i==1)
                    qDebug()<<i*4+1<<"flash green";
                    color = 1;
                }
                else if(m_bYellow&&m_bListPhaseChange[i*4+1])
                {
                    color = 2;
                }
                else if(m_bRed&&m_bListPhaseChange[i*4+1])
                {
                    color = 3;
                }

            }
        }
        else if(m_bListYellow[i*4+1])
        {
            if(m_bListFlash[i*4+1])
            {
                m_bListFlashChange[i*4+1] = !m_bListFlashChange[i*4+1];
            }
            if(m_bListFlashChange[i*4+1])
            {
                color = 0;
            }
            else
            {
                color = 2;
            }
        }
        else if(m_bListRed[i*4+1])
        {
            color = 3;
        }
        else
        {
            color = 0;
        }

        //painter.drawPixmap(xPoint,yPoint,m_imgList[color*4+1]);

        if(m_bIcon)
        {
            painter.save();
            painter.scale(picScale,picScale);
            painter.drawPixmap(xPoint,yPoint,20,80,m_imgList[color*4+1]);
            painter.restore();
        }
        else
        {
            painter.drawPixmap(xPoint,yPoint,20,80,m_imgList[color*4+1]);
        }
        //----------------------------------
        if(m_bListGreen[i*4+2])
        {
            if(m_bListFlash[i*4+2]||m_bFlashGreen)
            {
                //qDebug()<<"change";
                //qDebug()<<i*4+2<<"change";
                m_bListFlashChange[i*4+2] = !m_bListFlashChange[i*4+2];
            }
            if(m_bListFlashChange[i*4+2]&&(m_bListPhaseChange[i*4+2]||m_bRealShow))
            {
                color = 0;
                //qDebug()<<i*4+2<<"flash";
            }
            else
            {
                if(m_bGreen||!m_bListPhaseChange[i*4+2])
                {
                    color = 1;
                }
                else if(m_bYellow&&m_bListPhaseChange[i*4+2])
                {
                    color = 2;
                }
                else if(m_bRed&&m_bListPhaseChange[i*4+2])
                {
                    color = 3;
                }
            }
        }
        else if(m_bListYellow[i*4+2])
        {

            if(m_bListFlash[i*4+2])
            {
                m_bListFlashChange[i*4+2] = !m_bListFlashChange[i*4+2];
            }
            if(m_bListFlashChange[i*4+2])
            {
                color = 0;
               // qDebug()<<i*4+3<<"flash";
            }
            else
            {
                color = 2;
            }
        }
        else if(m_bListRed[i*4+2])
        {
            color = 3;
        }
        else
        {
            color = 0;
        }

        //painter.drawPixmap(xPoint+iDis,yPoint,m_imgList[color*4+2]);

        if(m_bIcon)
        {
            painter.save();
            painter.scale(picScale,picScale);
            painter.drawPixmap(xPoint+iDis,yPoint,20,80,m_imgList[color*4+2]);
            painter.restore();
        }
        else
        {
            painter.drawPixmap(xPoint+iDis,yPoint,20,80,m_imgList[color*4+2]);
        }


        //-----------------------------
        if(m_bListGreen[i*4+3])
        {
            if(m_bListFlash[i*4+3]||m_bFlashGreen)
            {
                //qDebug()<<"change";
                //qDebug()<<i*4+3<<"change";
                m_bListFlashChange[i*4+3] = !m_bListFlashChange[i*4+3];
            }
            if(m_bListFlashChange[i*4+3]&&(m_bListPhaseChange[i*4+3]||m_bRealShow))
            {
                color = 0;
            }
            else
            {
                if(m_bGreen||!m_bListPhaseChange[i*4+3])
                {
                    color = 1;
                }
                else if(m_bYellow&&m_bListPhaseChange[i*4+3])
                {
                    color = 2;
                }
                else if(m_bRed&&m_bListPhaseChange[i*4+3])
                {
                    color = 3;
                }
            }
        }
        else if(m_bListYellow[i*4+3])
        {

            brush = painter.brush();
            if(m_bListFlash[i*4+3])
            {
                m_bListFlashChange[i*4+3] = !m_bListFlashChange[i*4+3];
            }

            if(m_bListFlashChange[i*4+3])
            {
                color = 0;
            }
            else
            {
                color = 2;
            }
        }
        else if(m_bListRed[i*4+3])
        {
            color = 3;
        }
        else
        {
            color = 0;
        }
//       painter.drawPixmap(xPoint+iDis+iDis,yPoint,m_imgList[color*4+3]);

       if(m_bIcon)
       {
           painter.save();
           painter.scale(picScale,picScale);
           painter.drawPixmap(xPoint+iDis+iDis,yPoint,20,80,m_imgList[color*4+3]);
           painter.restore();
       }
       else
       {
           painter.drawPixmap(xPoint+iDis+iDis,yPoint,20,80,m_imgList[color*4+3]);
       }




    }
    painter.restore();


    //if(m_bSimulate&&m_usTimePeriod!=0)
    if(m_usTimePeriod!=0&&m_ucStageCnt!=0)
    {
        quint16 xCirRect = 600/4;
        quint16 yCirRect = 600/4;
        quint16 cirDiameter = 600/4;
        QRectF rectAngle(xCirRect,yCirRect,cirDiameter,cirDiameter);
        QRectF rect(xCirRect+15,yCirRect+15,cirDiameter-30,cirDiameter-30);
        //QRectF rectAngle(200,200,100,100);

        qint32 startAngle = 90*16;

        qint32 greenAngle ;
        qint32 yellowAngle;
        qint32 redAngle;
        for(int i=0;i<m_ucStageCnt;i++)
        {
            qint32 stageSpanAngle = 0;
            qint32 stageStartAngle = startAngle;

            greenAngle = 16*360*m_ListTimeGreen[i]/m_usTimePeriod;
            yellowAngle = 16*360*m_ListTimeYellow[i]/m_usTimePeriod;
            redAngle = 16*360*m_ListTimeRed[i]/m_usTimePeriod;

            stageSpanAngle += greenAngle;
            stageSpanAngle += yellowAngle;
            stageSpanAngle += redAngle;

            pen = painter.pen();
            pen.setColor(Qt::darkGreen);
            painter.setPen(pen);
            brush = painter.brush();
//            QRadialGradient rg(xCirRect+cirDiameter/2,yCirRect+cirDiameter/2,cirDiameter/2,xCirRect+cirDiameter/2,yCirRect+cirDiameter/2);
//            rg.setColorAt(0,Qt::white);
//            rg.setColorAt(1,Qt::green);
//           painter.setBrush(rg);
            brush.setColor(Qt::green);
            painter.setBrush(brush);
            painter.drawPie(rectAngle,startAngle,-greenAngle);

        //    pen = painter.pen();
        //    pen.setColor(Qt::yellow);
        //    painter.setPen(pen);
            brush = painter.brush();
            brush.setColor(Qt::yellow);
            painter.setBrush(brush);
            startAngle -= greenAngle;
            painter.drawPie(rectAngle,startAngle,-yellowAngle);
        //    pen = painter.pen();
        //    pen.setColor(Qt::red);
        //    painter.setPen(pen);
            brush = painter.brush();
            brush.setColor(Qt::red);
            painter.setBrush(brush);
            startAngle -= yellowAngle;
            painter.drawPie(rectAngle,startAngle,-redAngle);
            startAngle -= redAngle;
            if(0!=m_ucStageCnt)
            {
                brush = painter.brush();
                switch(i)
                {
                case 0:
                    brush.setColor(Qt::blue);
                    break;
                case 1:
                    brush.setColor(Qt::cyan);
                    break;
                case 2:
                    brush.setColor(Qt::magenta);
                    break;
                case 3:
                    brush.setColor(Qt::darkRed);
                    break;
                case 4:
                    brush.setColor(Qt::darkCyan);
                    break;
                case 5:
                    brush.setColor(Qt::darkMagenta);
                    break;
                case 6:
                    brush.setColor(Qt::darkYellow);
                    break;
                case 7:
                    brush.setColor(Qt::gray);
                    break;
                default:
                    brush.setColor(Qt::gray);
                    break;
                }

                painter.setBrush(brush);

                painter.drawPie(rect,stageStartAngle,-stageSpanAngle);
            }


        }
        brush = painter.brush();
        brush.setColor(Qt::darkGreen);
        painter.setBrush(brush);
        painter.drawPie(rect,90*16,-16*360*m_usTimePass/(m_usTimePeriod));


    }


    //qDebug()<<m_ucTime/(m_ucTimeGreen+m_ucTimeYellow+m_ucTimeRed)*360;



}

void WPhaseStageWidget::mousePressEvent(QMouseEvent *e)
{
    if(m_bClick)
    {
        m_bClicked = !m_bClicked;
        emit(beClicked(this,m_ucStageNo));
    }


    if(m_bClickable)
    {
        int x = e->x();
        int y = e->y();
        x /= m_fScale;
        y /= m_fScale;
        x -= 300;
        y -= 300;
        //qDebug()<<"x:"<<x<<" y:"<<y;

        int xr = -75;//右转 右上角
        int yr = -250;
        int xw = 25;//图片宽
        int yl = 90;//图片长
        int xdis = 40;//路标间距

        //int xh = -70;//人行右上角
        int hdis = 95;//人行 距 右上角 y值
        int wh = 120;//图宽
        int yhl = 30;//图高
        QRect rectRight;
        QRect rectStraight;
        QRect rectLeft;
        QRect rectHuman;

        rectRight.setRect(xr,yr,xw,yl);
        rectStraight.setRect(xr+xdis,yr,xw,yl);
        rectLeft.setRect(xr+xdis+xdis,yr,xw,yl);
        rectHuman.setRect(xr,yr+hdis,wh,yhl);

        //区域范围
        int xleft = 30;
        int ybottom = -120;


        bool bContain = false;

        int pos;
        int dir;


        QPoint p;//坐标转换后的点
        if(x>xr&&x<xleft&&y>yr&&y<ybottom)
        {
            pos = 3;
            p.setX(x);
            p.setY(y);
        }
        if(x>yr&&x<ybottom&&y<-xr&&y>-xleft)
        {
            pos = 2;
            p.setX(-y);
            p.setY(x);

        }
        if(x<-xr&&x>-xleft&&y>-ybottom&&y<-yr)
        {
            pos = 1;
            p.setX(-x);
            p.setY(-y);
        }
        if(x<-yr&&x>-ybottom&&y>xr&&y<xleft)
        {
            pos = 0;
            p.setX(y);
            p.setY(-x);
        }

        if(rectRight.contains(p))
        {
            dir = 1;

            bContain = true;
        }
        else if(rectStraight.contains(p))
        {
            dir = 2;

            bContain = true;
        }
        else if(rectLeft.contains(p))
        {
            dir = 3;

            bContain = true;
        }
        else if(rectHuman.contains(p))
        {
            dir = 0;

            bContain = true;
        }

        if(bContain)
        {
            m_bListGreen[pos*4+dir] = !m_bListGreen[pos*4+dir];
            emit beClicked(this,m_ucStageNo);
            quint16 green = getGreenChannel();
            m_ListPhaseStage.replace(m_ucStageNo-1,green);
            //qDebug()<<"pos:"<<pos*4+dir<<"green:"<<green;
        }


        //quint16 g = getGreenChannel();
        this->update();
    }

}

void WPhaseStageWidget::mouseMoveEvent(QMouseEvent *)
{
    //qDebug()<<"x:"<<e->x()<<" y:"<<e->y();
}

void WPhaseStageWidget::timerEvent(QTimerEvent *e)
{
    //qDebug()<<"time event id"<<e->timerId();
    m_uiTimerId = e->timerId();
    m_bTimeEvent =!m_bTimeEvent;
//    if(m_bRealShow&&m_bTimerStart)
//    {
//        this->killTimer(m_uiTimerId);
//        m_bTimerStart = false;
//        qDebug()<<"kill timer";
//    }


    if(m_bLcdNum)
    {
        if(m_bTimeEvent&&m_bSimulate)//0118edit
        {
            m_ucTime++;
            m_usTimePass++;
            if(m_usTimePass>=m_usTimePeriod)
            {
                m_usTimePass = 0;
            }

            if(m_ucTime>=(m_ucTimeGreen+m_ucTimeYellow+m_ucTimeRed))
            {
                m_ucStageNo++;
                if(m_ucStageNo-1>=m_ucStageCnt)
                {
                    m_ucStageNo = 1;
                }
                //setData(m_ListPhaseStage[m_ucStageNo],0,0,0,0,m_ucTimeGreenFlash,m_ucTimeGreen,m_ucTimeYellow,m_ucTimeRed);
                if(m_bSimulate)
                {
                    setData(m_ListPhaseStage[m_ucStageNo-1],0,0,0,0,m_ucTimeGreenFlash,m_ListTimeGreen[m_ucStageNo-1],m_ListTimeYellow[m_ucStageNo-1],m_ListTimeRed[m_ucStageNo-1]);
                }
                else
                {
                    m_ucTime = 0;
                }


            }



        }
//        if(m_bRealShow)
//            this->update();
        m_bNumColor =!m_bNumColor;
        setLcdNumDisplay();
    }


    //if(!m_bRealShow)
        update();
}

void WPhaseStageWidget::killFlashTimer()
{
    if(m_bRealShow&&m_bTimerStart)
    {
        this->killTimer(m_uiTimerId);
        m_bTimerStart = false;
        //qDebug()<<"kill timer";
    }
}

void WPhaseStageWidget::setData(quint16 green, quint16 yellow, quint16 red, quint16 flash,quint8 time,quint8 timegreenflash,quint8 timegreen,quint8 timeyellow,quint8 timered)
{

    if(0!=green)
    {

        //qDebug()<<"before green chl "<<QObject::tr("%1").arg(green,4,16,a);
        changeDataToInterface(green);

        //qDebug()<<"after green chl "<<QObject::tr("%1").arg(green,4,16,a);
    }
    if(0!=yellow)
    {
        changeDataToInterface(yellow);
    }
    if(0!=red)
    {
        changeDataToInterface(red);
    }
    if(0!=flash)
    {
        changeDataToInterface(flash);
    }
    QChar a = '0';
//    qDebug()<<"after green"<<QObject::tr("%1").arg(green,4,16,a);
//    qDebug()<<"after yellow"<<QObject::tr("%1").arg(yellow,4,16,a);
//    qDebug()<<"after red"<<QObject::tr("%1").arg(red,4,16,a);
//    qDebug()<<"after flash"<<QObject::tr("%1").arg(flash,4,16,a);

    if(m_bRealShow)
    {
        m_bRed = false;

        if(0!=yellow)
        {
            m_bYellow = true;
        }
        else
        {
            m_bYellow = false;
        }

        if(0!=flash)
        {
            m_bFlash = true;
            //m_bFlashGreen = true;
        }
        else
        {
            m_bFlash = false;
            if(m_bRealShow)
            {
                for(int i=0;i<16;i++)
                    m_bListFlashChange[i] = false;
            }
           // m_bFlashGreen = false;
        }
        if(0!=green)
        {
            m_bGreen = false;
        }
    }


    if((m_bLcdNum||m_bSimulate)&&(NULL==m_LcdNumber))
    {
        m_bLcdNum = true;
        m_LcdNumber = new QLCDNumber();

        m_LcdNumber->setDigitCount(2);
        //m_LcdNumber->;
        //QRect rect(0,0,600*m_fScale,640*m_fScale);
        //QGridLayout *gLayout = new QGridLayout(this);

        QVBoxLayout *vLayout = new QVBoxLayout(this);

        m_LcdNumber->resize(m_usWidth/6,m_usHeight/6);
        vLayout->setMargin(250*m_fScale);
        vLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        vLayout->addWidget(m_LcdNumber);

    }
    else if(!m_bSimulate&&(m_LcdNumber!=NULL)&&!m_bRealShow)
    {
        if(m_LcdNumber->isHidden())
        {
        }
        else
        {
            m_bLcdNum = false;
            m_LcdNumber->hide();
        }

    }
    else if(m_bSimulate&&(m_LcdNumber!=NULL))
    {
        if(m_LcdNumber->isHidden())
        {
            m_bLcdNum = true;
            m_LcdNumber->show();
        }

    }

    int channelNum = 16;
    int nextStage;
    if(m_bSimulate)
    {
        emit beClicked(this,m_ucStageNo);
        nextStage = m_ucStageNo+1;
        if(nextStage-1>=m_ucStageCnt)
        {
            nextStage = 1;
        }

    }

    for(int i=0;i<channelNum;i++)
    {
        if(m_bSimulate)
        {
            quint16 current = m_ListPhaseStage[m_ucStageNo-1];
            changeDataToInterface(current);

            quint16 next = m_ListPhaseStage[nextStage-1];
            changeDataToInterface(next);

            if((quint8(current>>i)&0x01)==(quint8(next>>i)&0x01))
            {
               m_bListPhaseChange[i] = false;
            }
            else
            {

                 m_bListPhaseChange[i] = true;
                 //qDebug()<<i<<"phase change true";

            }
        }

        if(((quint8)(yellow>>i))&0x01)
        {

            m_bListYellow[i] = true;
        }
        else
        {
            m_bListYellow[i] = false;
        }

        if(((quint8)(red>>i))&0x01)
        {

            m_bListRed[i] = true;
        }
        else
        {
            m_bListRed[i] = false;
        }

        if(((quint8)(green>>i))&0x01)
        {

            m_bListGreen[i] = true;

        }
        else
        {
            m_bListGreen[i] = false;
            if(m_bSimulate)
            {
                m_bListRed[i] = true;
            }

        }



        if(((quint8)(flash>>i))&0x01)
        {
            m_bListFlash[i] = true;
        }
        else
        {
            m_bListFlash[i] = false;
        }


    }
    if((m_bFlash||m_bSimulate)&&!m_bTimerStart)
    {
        if(m_bRealShow)
        {
            this->startTimer(550);
        }
        else
        {
            this->startTimer(500);
        }

        m_bTimerStart = true;
        //qDebug()<<"start timer";

    }
    else if(!m_bFlash&&!m_bSimulate&&m_bTimerStart)
    {
        this->killTimer(m_uiTimerId);
        m_bTimerStart = false;
        //qDebug()<<"kill timer";
    }

    m_ucTime = time;
    m_ucTimeGreenFlash = timegreenflash;
    m_ucTimeGreen = timegreen;
    m_ucTimeYellow = timeyellow;
    m_ucTimeRed = timered;

//    quint16 stagetime = m_ucTimeGreen+m_ucTimeYellow+m_ucTimeRed;
//    if(0!=stagetime)
//    {
//        m_uiAngleGreen = 360*m_ucTimeGreen/stagetime*16;
//        m_uiAngleYellow = 360*m_ucTimeYellow/stagetime*16;
//        m_uiAngleRed = 360*16-m_uiAngleGreen-m_uiAngleYellow;
//        //qDebug()<<"green:"<<m_uiAngleGreen<<"yellow:"<<m_uiAngleYellow<<"red:"<<m_uiAngleRed;
//    }
    if(m_bRealShow)
    {
        this->update();
    }

    setLcdNumDisplay();
}

void WPhaseStageWidget::setLcdNumDisplay()
{
    if(m_bLcdNum&&!m_bRealShow)
    {
        if(m_ucTime<m_ucTimeGreen)
        {
            m_bGreen = true;
            m_bRed = false;
            m_bYellow = false;

            m_LcdNumber->display(m_ucTimeGreen-m_ucTime);
            if(m_ucTime>=(m_ucTimeGreen-m_ucTimeGreenFlash))
            {
                m_bFlashGreen = true;
                //qDebug()<<"m_bFlashGreen true";
            }
         }
        else if(m_ucTime<(m_ucTimeGreen+m_ucTimeYellow))
        {
            //if(m_bSimulate)
            //{
                m_bFlashGreen = false;
                m_bGreen = false;
                m_bYellow = true;

            //}

            m_LcdNumber->display(m_ucTimeYellow-m_ucTime+m_ucTimeGreen);
        }
        else if(m_ucTime<(m_ucTimeGreen+m_ucTimeYellow+m_ucTimeRed))
        {
            //if(m_bSimulate)
            //{
            m_bFlashGreen = false;
                m_bGreen = false;
                m_bRed = true;
                m_bYellow = false;
            //}

            m_LcdNumber->display(m_ucTimeYellow-m_ucTime+m_ucTimeGreen+m_ucTimeRed);
        }




        //m_bNumColor =!m_bNumColor;
        QPalette p =m_LcdNumber->palette();
        if(m_bGreen)
        {
            if(m_bFlashGreen&&m_bNumColor)
            {
                p.setColor(QPalette::WindowText,Qt::black);
            }
            else
            {
                p.setColor(QPalette::WindowText,Qt::green);
            }
        }
        else if(m_bYellow)
        {

                p.setColor(QPalette::WindowText,Qt::yellow);



        }
        else if(m_bRed)
        {
            p.setColor(QPalette::WindowText,Qt::red);
        }

        m_LcdNumber->setPalette(p);
    }
    else if(m_bRealShow)
    {
        if(m_LcdNumber!=NULL)
        m_LcdNumber->display(m_ucTime);
    }
}

void WPhaseStageWidget::setListData(QList<quint16> listgreen, QList<quint8> timelistgreen, QList<quint8> timelistyellow, QList<quint8> timelistred)
{

    m_ListPhaseStage.clear();
    m_ListTimeGreen.clear();
    m_ListTimeYellow.clear();
    m_ListTimeRed.clear();
    m_ListOption.clear();

    m_ListPhaseStage.append(listgreen);
    m_ListTimeGreen.append(timelistgreen);
    m_ListTimeYellow.append(timelistyellow);
    m_ListTimeRed.append(timelistred);

    m_ucStageNo = 0xff;
    m_ucStageCnt = m_ListPhaseStage.count();

    setTimePeriod();

    //无option数据 用0x00代替
    for(quint8 i=0;i<m_ucStageCnt;i++)
    {
        m_ListOption<<0x00;
    }
}

//index 为 链表顺序 从0起
void WPhaseStageWidget::editListData(bool badd, bool breplace, bool bdel,quint8 index, quint16 greenchannel, quint8 timegreen, quint8 timeyellow, quint8 timered,quint8 option)
{
    if(badd)
    {
//        if(0==greenchannel)
//        {
//            m_bClickable = true;
//        }
        m_ListPhaseStage.insert(index,greenchannel);
        m_ListTimeGreen.insert(index,timegreen);
        m_ListTimeYellow.insert(index,timeyellow);
        m_ListTimeRed.insert(index,timered);
        m_ListOption.insert(index,option);

    }
    else if(breplace)
    {
        m_ListPhaseStage.replace(index,greenchannel);
        m_ListTimeGreen.replace(index,timegreen);
        m_ListTimeYellow.replace(index,timeyellow);
        m_ListTimeRed.replace(index,timered);
        m_ListOption.replace(index,option);
    }
    else if(bdel)
    {
        m_ListPhaseStage.removeAt(index);
        m_ListTimeGreen.removeAt(index);
        m_ListTimeYellow.removeAt(index);
        m_ListTimeRed.removeAt(index);
        m_ListOption.removeAt(index);
        index = 0xff;
    }

    m_ucStageNo = index+1;
    setTimePeriod();
}

/*将 外部数据顺序 转换为 界面顺序
外部: 0~15 对应 北： 左 直 右 人 东 南 西
界面：          东：人 右 直 左 南 西 北
*/
void WPhaseStageWidget::changeDataToInterface(quint16& bits)
{
//    QChar a = '0';
//    qDebug()<<"befor change "<<QObject::tr("%1").arg(bits,4,16,a);
    quint16 temp = 0;
    //--------------相位值转为 方向值---------------
    temp = bits;
    bits = 0;
    if(m_bRealShow)
    {

        for(int i=0;i<16;i++)
        {
            if(((temp>>i)&0x0001)==1)
            {

                quint8 chl = 0;
                chl = (*m_pListChannelMap)[i];
                if(chl>0)
                {
                    bits += qPow(2,chl-1);
                }

            }
        }
    }
    else
    {
        for(int i=0;i<CHANNELNUM;i++)
        {

            if((temp>>i)&0x0001)
            {
                quint8 phase = i+1;
                int dir = 0;
                for(int j=0;j<16;j++)
                {

                    //qDebug()<<"m_pListComMap is NULL"<<m_pListComMap->count()<<m_pListOverlapMap->count()<<m_pListChannelMap->count();
                    if((*m_pListComMap)[j]==phase||(*m_pListOverlapMap)[j]==phase)
                    {
                        dir = j+1;
                        break;
                    }
                }

                if(dir>0)
                {
                    bits += qPow(2,dir-1);
                }
            }
        }
    }
    //--------------转换 北东南西 成 东南西北---------------
    //if(!m_bRealShow)
    {
        temp = 0;
        temp |= (bits&0x000f);
        temp |= ((bits&0xf000)>>8);
        temp |= ((bits&0x0f00));
        temp |= ((bits&0x00f0)<<8);
        bits = 0;
        for(int i=0;i<CHANNELNUM;i++)
        {
            bits <<= 1;
            bits |= ((temp>>i)&0x0001);
        }
    }
    //qDebug()<<"after change "<<QObject::tr("%1").arg(bits,4,16,a);
}

void WPhaseStageWidget::changeInterfaceToData(quint16 &bits)
{
    quint16 temp = 0;
    temp |= ((bits&0x000f)<<8);
    temp |= (bits&0x00f0);
    temp |= ((bits&0x0f00)>>8);
    temp |= (bits&0xf000);

    bits = 0;
    for(int i=0;i<CHANNELNUM;i++)
    {

        bits <<= 1;
        bits |= ((temp>>i)&0x0001);
    }
    //-------对应相位值-------普通相位1-16 对应2的0-15次方  跟随相位1-8对应2的0-7次方----------
    temp = bits;
    bits = 0;
    for(int i=0;i<CHANNELNUM;i++)
    {

        if((temp>>i)&0x0001)
        {
            quint8 phase = (*m_pListOverlapMap)[i]==0?(*m_pListComMap)[i]:(*m_pListOverlapMap)[i];

            if(phase>0)
            {
                bits += qPow(2,phase-1);
            }
        }
    }
}

void WPhaseStageWidget::setClickable(bool b)
{
    m_bClickable = b;
}
quint16 WPhaseStageWidget::getGreenChannel()
{
    quint16 green = 0;
    for(int i=15;i>-1;i--)
    {
        green <<= 1;
        if(m_bListGreen[i])
        {
            green |= 0x0001;

        }

    }

    changeInterfaceToData(green);
    QChar c = '0';
    //qDebug()<<"get data:"<<QObject::tr("0x%1").arg(green,4,16,c);
    return green;
}

void WPhaseStageWidget::setGreenChannel(quint16 green)
{
    m_bSimulate = false;
    m_bLcdNum = false;

    setData(green);
    QChar c = '0';
   // qDebug()<<"before change set data:"<<QObject::tr("0x%1").arg(green,4,16,c);
    update();
}

void WPhaseStageWidget::setClicked(bool b)
{
    m_bClick = b;
}

quint16 WPhaseStageWidget::getPhase(quint8 index)
{
    return m_ListPhaseStage[index];
}

quint8 WPhaseStageWidget::getTimeGreen(quint8 index)
{
    if(index==0xff)
    {
        if(0xff!=m_ucStageNo)
        {
            return m_ListTimeGreen[m_ucStageNo-1];
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return m_ListTimeGreen[index];
    }
}

quint8 WPhaseStageWidget::getTimeYellow(quint8 index)
{

    if(index==0xff)
    {
        if(0xff!=m_ucStageNo)
        {
            return m_ListTimeYellow[m_ucStageNo-1];
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return m_ListTimeYellow[index];
    }
}

quint8 WPhaseStageWidget::getTimeRed(quint8 index)
{

    if(index==0xff)
    {
        if(0xff!=m_ucStageNo)
        {
            return m_ListTimeRed[m_ucStageNo-1];
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return m_ListTimeRed[index];
    }
}

quint8 WPhaseStageWidget::getOption(quint8 index)
{

    if(index==0xff)
    {
        if(0xff!=m_ucStageNo)
        {
            return m_ListOption[m_ucStageNo-1];
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return m_ListOption[index];
    }
}

void WPhaseStageWidget::setCurIndex(quint8 stageindex)
{
    m_ucStageNo = stageindex;
}

quint8 WPhaseStageWidget::getCurIndex()
{
    return m_ucStageNo;
}

quint8 WPhaseStageWidget::getStageCount()
{
    return m_ucStageCnt;
}

void WPhaseStageWidget::setIconDark(bool b)
{
    if(!b)
    {
        this->setBackgroundRole(QPalette::Light);
    }
    else
    {
        this->setBackgroundRole(QPalette::Mid);
    }
}

void WPhaseStageWidget::setIconWidth(quint16 width)
{
    m_usWidth = width;
    m_usHeight = width;
    m_fScale = qreal(width)/600;
    if(m_bIcon)
    {
        //qDebug()<<"enter icon width";
        this->resize(500*m_fScale,500*m_fScale);
        this->setMinimumSize(500*m_fScale,500*m_fScale);
        this->setMaximumSize(500*m_fScale,500*m_fScale);
        m_bClickable = false;
    }

}

bool WPhaseStageWidget::getBeClicked()
{
    return m_bClicked;
}
void WPhaseStageWidget::emitBeClicked()
{
    emit beClicked(this,m_ucStageNo);
}

void WPhaseStageWidget::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    setListPoint();
}

void WPhaseStageWidget::setListPoint(QList<quint8> *listChannel,QList<quint8>*listCom,QList<quint8>*listOver)
{
    if(listChannel==NULL)
    {
        m_pListChannelMap = &m_pDataProcess->m_ListChannelMap;
        m_pListComMap = &m_pDataProcess->m_ListComMap;
        m_pListOverlapMap = &m_pDataProcess->m_ListOverlapMap;
    }
    else
    {
        m_pListChannelMap = listChannel;
        m_pListComMap = listCom;
        m_pListOverlapMap = listOver;
    }
}
void WPhaseStageWidget::setRealShowFlag(bool breal/*,bool blcd*/)
{
    m_bRealShow = breal;
//    m_bListPhaseChange.clear();
//    for(int i=0;i<16;i++)
//    {
//        m_bListPhaseChange<<true;
//    }
    //m_bLcdNum = blcd;
}

void WPhaseStageWidget::setSimulate(bool b)
{
    m_bSimulate = b;

    //int cnt = m_ListPhaseStage.count();
    QChar a = '0';
//    for(int i=0;i<cnt;i++)
//    {
//        //qDebug()<<"list "<<i<<QObject::tr("%1").arg(m_ListPhaseStage[i],4,16,a);
//    }
    if(m_bSimulate)
    {

        m_bRed = false;//阶段红灯  用于lcd红色

        m_bYellow = false;//有黄灯 用于lcd黄色
        m_bFlashGreen = false;

        //m_bTimeEvent = false;
        //m_bTimerStart = false;
        //m_bLcdNum = false;
        m_bFlash = false;


        m_bIcon = false;

        //m_bNumColor = false;//闪烁时 数字闪烁
        //m_LcdNumber = NULL;

        m_bClickable = false;
        m_bClick = false;
        m_ucStageNo = 1;

        for(int i=0;i<CHANNELNUM;i++)
        {
            m_bListFlashChange[i] = false;
        }

        setData(m_ListPhaseStage[0],0,0,0,0,3,m_ListTimeGreen[0],m_ListTimeYellow[0],m_ListTimeRed[0]);
    }
    else if(m_bTimerStart)
    {
        //m_ucStageNo = 0xff;

        this->killTimer(m_uiTimerId);
        m_bTimerStart = false;
        m_usTimePass = 0;
        //qDebug()<<"killTimer";

        //清理 过度阶段 变换标志
        for(int i=0;i<CHANNELNUM;i++)
        {
            m_bListPhaseChange[i] = false;
        }
    }
}

void WPhaseStageWidget::setTimePeriod()
{
    m_ucStageCnt = m_ListPhaseStage.count();
    m_usTimePeriod = 0;
    for(int i=0;i<m_ucStageCnt;i++)
    {
        m_usTimePeriod += m_ListTimeGreen[i];
        m_usTimePeriod += m_ListTimeYellow[i];
        m_usTimePeriod += m_ListTimeRed[i];
    }
}
