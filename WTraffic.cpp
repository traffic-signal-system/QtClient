#include "WTraffic.h"
#include "ui_wtraffic.h"
#include <QPainter>


WTraffic::WTraffic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WTraffic)
{
    ui->setupUi(this);
    m_pDataProcess = NULL;
//    ui->cbDeviceId->setChecked(true);
    ui->combDeviceId->setEnabled(false);
    ui->cbTime->setChecked(true);
    QDateTime time = QDateTime::currentDateTime();
    ui->deEndTime->setDateTime(time);

    m_pGrgph = new trafficLine(ui->graphWid);

}

WTraffic::~WTraffic()
{
    delete ui;
}

void WTraffic::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    ui->tableView->setModel(p->m_pModelTraffic);

    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,57);
    ui->tableView->setColumnWidth(2,130);
    ui->tableView->setColumnWidth(3,55);
    ui->tableView->setColumnWidth(4,67);
    ui->tableView->setColumnWidth(5,67);
    ui->tableView->setColumnWidth(6,67);
    ui->combDeviceId->setModel(p->m_EventNameModel);
    connect(ui->cbDeviceId,SIGNAL(clicked(bool)),this,SLOT(on_cbDevicedCheck(bool)));
    connect(ui->cbTime,SIGNAL(clicked(bool)),this,SLOT(on_cbTimeCheck(bool)));
    connect(ui->btnQuery,SIGNAL(clicked()),this,SLOT(on_btnQuery()));
    connect(ui->btnDelete,SIGNAL(clicked()),this,SLOT(on_btnDelete()));

    m_pGrgph->setDataProcess(p);
    connect(ui->btnUp,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnUp()));
    connect(ui->btnDown,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnDown()));
    connect(ui->btnLeft,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnLeft()));
    connect(ui->btnRight,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnRight()));
    connect(ui->btnLeftBig,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnLeftBig()));
    connect(ui->btnRightBig,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnRightBig()));
    connect(ui->btnPageUp,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnPageUp()));
    connect(ui->btnPageDown,SIGNAL(clicked()),m_pGrgph,SLOT(on_btnPageDown()));
}

void WTraffic::on_cbDevicedCheck(bool b)
{
    ui->combDeviceId->setEnabled(b);
}

void WTraffic::on_cbTimeCheck(bool b)
{
    ui->deStartTime->setEnabled(b);
    ui->deEndTime->setEnabled(b);
}

void WTraffic::on_btnQuery()
{
    if(m_pDataProcess!=NULL)
    {
        quint32 id = 0;
        if(ui->cbDeviceId->isChecked())
        {
            int index = ui->combDeviceId->currentIndex();
            if(index!=-1)
            {
                id = m_pDataProcess->m_TscIdList[index].toInt();
            }
        }
        quint32 sTime = 0;
        quint32 eTime = 0;
        quint32 disTime = 5*60;
        int index = ui->combDisTime->currentIndex();
        switch(index)
        {
        case 0:
            disTime = 5*60;
            break;
        case 1:
            disTime = 15*60;
            break;
        case 2:
            disTime = 30*60;
            break;
        case 3:
            disTime = 60*60;
            break;
        case 4:
            disTime = 24*60*60;
            break;
        case 5:
            disTime = 30*24*60*60;
            break;
        default:
            break;
        }
//        qDebug()<<"index:"<<index<<"distime"<<disTime;

        m_pGrgph->clearData();
        m_pGrgph->setDisTime(disTime);

        if(ui->cbTime->isChecked())
        {
            sTime = ui->deStartTime->dateTime().toTime_t();
            eTime = ui->deEndTime->dateTime().toTime_t();
        }
        if(ui->cbDeviceId->isChecked()||ui->cbTime->isChecked())
        {
            QStandardItemModel *pModel = m_pDataProcess->m_pModelTraffic;
            pModel->removeRows(0,pModel->rowCount());
            m_pDataProcess->requireTrafficStatistics(id,disTime,sTime,eTime);
        }
    }
}

void WTraffic::on_btnDelete()
{
    if(m_pDataProcess!=NULL)
    {
        quint32 id = 0;
        if(ui->cbDeviceId->isChecked())
        {
            int index = ui->combDeviceId->currentIndex();
            if(index!=-1)
            {
                id = m_pDataProcess->m_TscIdList[index].toInt();
            }
        }
        quint32 sTime = 0;
        quint32 eTime = 0;
        quint32 disTime = 5*60;
        if(ui->cbTime->isChecked())
        {
            sTime = ui->deStartTime->dateTime().toTime_t();
            eTime = ui->deEndTime->dateTime().toTime_t();
        }
        m_pDataProcess->deleteTrafficStatistics(id,disTime,sTime,eTime);
    }
}

//----------------------------------------------------------
trafficLine::trafficLine(QWidget *parent):
        QWidget(parent)
{
    m_uiMaxX = 0;
    m_uiMaxY = 0;
    m_uiMinTime = 0;
    m_uiDisTime = 0;
    m_pDataProcess = NULL;
    m_iCnt = 0;
    this->setFixedSize(TRAFFICWIDTH,TRAFFICHEIGHT);
    m_rScale = 1;
    m_rTranslate = 0;
    m_iPageIndex = 0;
}
trafficLine::~trafficLine()
{

}

void trafficLine::paintEvent(QPaintEvent *)
{
    QPixmap pix(TRAFFICX,TRAFFICY+20);//20用于x轴下方的文字
    QPainter paint(&pix);
    paint.fillRect(QRect(0,0,TRAFFICX,TRAFFICY+20),Qt::lightGray);
    paint.translate(m_rTranslate,TRAFFICY);
    paint.scale(m_rScale,1);
    int cnt = m_listPath.count();
    QPainterPath path;
    QFont font;
    font = paint.font();
    font.setWeight(5);
//    qDebug()<<"font"<<font.weight()<<font.bold();
//    font.setWeight(5);
    //font.setBold(true);
    int newCnt = (m_iPageIndex+UNITPAGECNT)>cnt?cnt:(m_iPageIndex+UNITPAGECNT);
    for(int i=m_iPageIndex;i<newCnt;i++)
    {
        QPen pen(m_listCol[i]);
        paint.setPen(pen);
        paint.drawPath(m_listPath[i]);

    }
    for(int i=0;i<m_iCnt;i++)
    {
        path.addText(TRAFFICUNIT*i,15,font,tr("%1").arg(i));//try
    }
    QPen pen1(Qt::black);
    paint.setPen(pen1);

    path.moveTo(0,0);
    path.lineTo(TRAFFICX/m_rScale-m_rTranslate,0);

    paint.drawPath(path);
    QPainter paint1(this);
    paint1.fillRect(QRect(0,0,TRAFFICWIDTH,TRAFFICHEIGHT),Qt::lightGray);
    paint1.drawPixmap(TRAFFICDISX,TRAFFICDISY,TRAFFICX,TRAFFICY+20,pix);
    QPainterPath pathY;
    pathY.moveTo(TRAFFICDISX,TRAFFICDISY);
    pathY.lineTo(TRAFFICDISX,TRAFFICDISY+TRAFFICY);
    for(int i=0;i<5;i++)
    {
        pathY.addText(0,i*50+TRAFFICDISY,font,tr("%1").arg(m_uiMaxY*(4-i)/4));
    }
    paint1.drawPath(pathY);
    paint1.drawText(TRAFFICDISX,TRAFFICHEIGHT-5,m_strTimeMsg);
    for(int i=m_iPageIndex;i<newCnt;i++)
    {
        QPen pen(m_listCol[i]);
        paint1.setPen(pen);
        paint1.drawText(530/*+i/UNITPAGECNT*60*/,i%UNITPAGECNT*20,55,20,Qt::AlignCenter,m_listName[i]);
    }
}

void trafficLine::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    connect(p,SIGNAL(trafficMaxMinTime(quint32,quint32,quint32)),this,SLOT(on_setMaxMinY(quint32,quint32,quint32)));
    connect(p,SIGNAL(trafficData(QString ,QMap<quint32,quint32> )),this,SLOT(on_setLineData(QString,QMap<quint32,quint32>)));
    connect(p,SIGNAL(completeTraffic()),this,SLOT(on_completeTraffic()));

}

void trafficLine::setDisTime(quint32 dis)
{
    m_uiDisTime = dis;
}

void trafficLine::on_setMaxMinY(quint32 maxTime, quint32 minTime, quint32 maxY)
{
    m_strTimeMsg.clear();
    m_uiMaxX = maxTime;
    m_uiMinTime = minTime;
    m_uiMaxY = maxY;
    if(m_uiDisTime!=0)
    {
        m_iCnt = (m_uiMaxX-m_uiMinTime)/m_uiDisTime;
    }
    QString maxStr = QDateTime::fromTime_t(m_uiMaxX).toString("yyyy-MM-dd hh:mm:ss");
    QString minStr = QDateTime::fromTime_t(m_uiMinTime).toString("yyyy-MM-dd hh:mm:ss");
    m_strTimeMsg.append(tr("开始时间:%1 结束时间:%2 间隔时间:").arg(minStr).arg(maxStr));
    switch(m_uiDisTime)
    {
    case 60*5:
        m_strTimeMsg.append(tr("5分钟"));
        break;
    case 60*15:
        m_strTimeMsg.append(tr("15分钟"));
        break;
    case 60*30:
        m_strTimeMsg.append(tr("30分钟"));
        break;
    case 60*60:
        m_strTimeMsg.append(tr("1小时"));
        break;
    case 60*60*24:
        m_strTimeMsg.append(tr("1天"));
        break;
    case 60*60*24*30:
        m_strTimeMsg.append(tr("1个月"));
        break;
    default:
        break;
    }

    qDebug()<<"m_iCnt"<<m_iCnt<<"on_setMaxMinY"<<"m_uiMaxX"<<maxStr<<"m_uiMinTime"<<minStr;
}

void trafficLine::clearData()
{
    m_listName.clear();
    m_listCol.clear();
    m_listPath.clear();

    m_rScale = 1;
    m_rTranslate = 0;
    m_iPageIndex = 0;

    this->update();
}

void trafficLine::on_setLineData(QString strName, QMap<quint32, quint32> mapData)
{
    m_listName.append(strName);
    QPainterPath path;

//    qDebug()<<strName<<"on_setLineData mapdata cnt"<<mapData.count()<<m_uiMinTime<<m_uiMaxX<<"m_uiMaxX-m_uiMinTime"<<m_uiMaxX-m_uiMinTime<<"m_uiDisTime"<<m_uiDisTime;
    for(int i=0;i<=m_iCnt;i++)
    {
        quint32 colume = 0;
        quint32 key = i*m_uiDisTime+m_uiMinTime;
        if(mapData.contains(key))
        {
            colume = mapData[key];
        }

        if(m_uiDisTime>0&&m_uiMaxY>0)
        {
            qint32 yPox = -1*(qint32)((colume*TRAFFICY)/m_uiMaxY);
            QPointF point(i*TRAFFICUNIT,yPox);
//            qDebug()<<" i point"<<i<<point;
            if(i==0)
            {
                path.moveTo(point);
            }
            else
            {
                path.lineTo(point);
            }
        }
    }
//            path.lineTo((m_uiMaxX-m_uiMinTime)*TRAFFICUNIT/m_uiDisTime,0);
//            path.lineTo(0,0);
        m_listPath.append(path);

        int cnt = m_listCol.count();
        switch(cnt%9)
        {
        case 0:
            m_listCol.append(Qt::red);
            break;
        case 1:
            m_listCol.append(Qt::darkRed);
            break;
        case 2:
            m_listCol.append(Qt::green);
            break;
        case 3:
            m_listCol.append(Qt::darkGreen);
            break;
        case 4:
            m_listCol.append(Qt::darkBlue);
            break;
        case 5:
            m_listCol.append(Qt::darkCyan);
            break;
        case 6:
            m_listCol.append(Qt::magenta);
            break;
        case 7:
            m_listCol.append(Qt::darkMagenta);
            break;
        case 8:
            m_listCol.append(Qt::yellow);
            break;
        default:
            break;
        }
}

void trafficLine::on_completeTraffic()
{
    this->update();
}

void trafficLine::on_btnUp()
{
    m_rScale += 0.1;
    this->update();
}

void trafficLine::on_btnDown()
{
    if(m_rScale>0.1)
    {
        m_rScale -= 0.1;
        this->update();
    }
}

void trafficLine::on_btnLeft()
{
    m_rTranslate--;
    this->update();
}

void trafficLine::on_btnRight()
{
    if(m_rTranslate<0)
    {
        m_rTranslate++;
        this->update();
    }
}

void trafficLine::on_btnLeftBig()
{
    m_rTranslate-=250;
    this->update();
}

void trafficLine::on_btnRightBig()
{
    if(m_rTranslate<0)
    {
        m_rTranslate+=250;
        if(m_rTranslate>0)
        {
            m_rTranslate = 0;
        }
        this->update();
    }
}

void trafficLine::on_btnPageUp()
{
    int cnt = m_listPath.count();
    if((m_iPageIndex+9)<cnt)
    {
        m_iPageIndex+=9;
        this->update();
    }

}

void trafficLine::on_btnPageDown()
{
    m_iPageIndex-=9;
    if(m_iPageIndex<0)
    {
        m_iPageIndex = 0;
    }
    this->update();
}
