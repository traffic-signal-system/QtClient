#include "wstatus.h"
#include "ui_status.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <qendian.h>
#include "pdataprocess.h"
WStatus::WStatus(QWidget *parent) :
        QWidget(parent),ui(new Ui::Status)
{
    QWidget *w = new QWidget();
    ui->setupUi(w);
//    m_pStatus = new WPhaseStageWidget(this,0,0,0,0,390,true);
//    m_pStatus->setClickable(false);
    m_pStatus = new WStage(ui->groupStage);
    m_pStatus->setUnClickAble();
    m_pStatus->setFlagClickPhase();
    m_pStatus->setLedShow();

//    ui->hStatusLayout->addWidget(m_pStatus);
    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    vLayout->addStretch();
    vLayout->addWidget(w);
    vLayout->addStretch();

    hLayout->addStretch();
    hLayout->addLayout(vLayout);
    hLayout->addStretch();

//    QDateTime time;
//    time = QDateTime::currentDateTime();
//    ui->dateTimeEdit->setDateTime(time);

    ui->rbDef->hide();

    m_bBeginCheck = false;
    //m_bSendCheck = false;
    m_pDataProcess = NULL;
    m_bChange = false;
    m_uiCurNodeId = 0;

    m_bManual = false;

    m_iTimeOffset =  0;
    m_bRcvTscTime = false;

//    m_bDefault = false;

    ui->rbRed->setEnabled(false);
    ui->rbYellow->setEnabled(false);
    ui->rbClose->setEnabled(false);
    ui->cbPhaseNum->setEnabled(false);
    ui->nextStepBtn->setEnabled(false);
    ui->nextStageBtn->setEnabled(false);

    connect(ui->checkBtn,SIGNAL(clicked()),this,SLOT(on_checkBtn()));
    connect(ui->rbManual,SIGNAL(clicked()),this,SLOT(on_ctrlTypeChange()));
    connect(ui->rbAutoCtrl,SIGNAL(clicked()),this,SLOT(on_ctrlTypeChange()));

    connect(ui->rbClose,SIGNAL(clicked()),this,SLOT(on_lightModeChange()));
    connect(ui->rbRed,SIGNAL(clicked()),this,SLOT(on_lightModeChange()));
    connect(ui->rbYellow,SIGNAL(clicked()),this,SLOT(on_lightModeChange()));
//    connect(ui->rbDef,SIGNAL(clicked()),this,SLOT(on_lightModeChange()));

    connect(ui->cbPhaseNum,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbPhaseChange(int)));

    connect(ui->nextStepBtn,SIGNAL(clicked()),this,SLOT(on_nextStepBtn()));
    connect(ui->nextStageBtn,SIGNAL(clicked()),this,SLOT(on_nextStageBtn()));
    connect(ui->cbService,SIGNAL(clicked(bool)),this,SLOT(on_cbService(bool)));
    QDateTime time = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(time);

    ui->groupBox_7->hide();
    ui->cbPhaseNum->hide();
    ui->label_4->hide();
    ui->nextStageBtn->hide();
    ui->cbService->hide();
}

WStatus::~WStatus()
{
    if(ui->cbFlashStatus->isChecked())
    {
        qDebug()<<"flash status";
        ui->cbFlashStatus->click();
    }
    delete ui;
}

void WStatus::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
   // m_pStatus->setDataProcess(p);
    m_pDataProcess->setBeginCheck(m_bBeginCheck);

    connect(p,SIGNAL(rcvAutoReport(unsigned char*,int,quint32)),this,SLOT(on_rcvAutoReport(unsigned char*,int,quint32)));
    connect(p,SIGNAL(rcvTscTime(quint32)),this,SLOT(on_rcvTscTime(quint32)));
    connect(p,SIGNAL(rcvManualCtrl(bool)),this,SLOT(on_rcvManualCtrl(bool)));

    connect(ui->cbFlashStatus,SIGNAL(clicked(bool)),this,SLOT(on_cbFlashStatus(bool)));
    connect(p,SIGNAL(cbFlashStatus(bool)),ui->cbFlashStatus,SLOT(setChecked(bool)));
    connect(m_pStatus,SIGNAL(changeStageIndex(quint8)),this,SLOT(on_selectStageIndex(quint8)));
    connect(p,SIGNAL(changeNodeId()),this,SLOT(on_nodeChange()));
//    connect(p,SIGNAL(rcvPhase()),this,SLOT(on_changeNode()));//实时读取时
}

/*
 输入：0-31位 分在 a,b,c,d
*/
quint32 WStatus::makeNum(quint8 a, quint8 b, quint8 c, quint8 d)
{
    quint32 num = 0;
    num+=d;
    num<<=8;
    num+=c;
    num<<=8;
    num+=b;
    num<<=8;
    num+=a;
    return num;

}

void WStatus::changeNode()
{
    if(m_pDataProcess->m_mapVip.contains(m_uiCurNodeId))
    {//qDebug()<<"-------------------------------changeNode-----------------------------------------"<<m_uiCurNodeId;
        SVipData* data = m_pDataProcess->m_mapVip[m_uiCurNodeId];
        m_pStatus->changeNode(data->m_ListLoadNo,data->m_ListValid,data->m_ListPhaseMap);
        m_pStatus->setUnClickAble();
        m_pStatus->setChannelMap(data->m_ListLoadMap);
        ui->cbPhaseNum->clear();
        ui->cbPhaseNum->addItems(getComPhaseList(data->m_ListPhaseMap));
        m_pStatus->setBack(data->m_ucDir);
        if(m_pDataProcess->m_mapTsc.contains(m_uiCurNodeId))
        {
            STscInfo* tsc = m_pDataProcess->m_mapTsc[m_uiCurNodeId];
            m_pStatus->setOverlapConnect(tsc->tbOverlap);
//            m_pStatus->setBack(m_pDataProcess->m_ucDir);
        }
    }
}

QStringList WStatus::getComPhaseList(QList<quint8> &list)
{
    QStringList comList;
    QList<quint8> com;
    foreach(quint8 phase,list)
    {
        if(phase>0&&phase<32)
        {
            com.append(phase);
//            comList.append(QString::number(phase));
        }
    }
    qSort(com);
    comList.append(tr(" "));
    foreach(quint8 id,com)
    {
        comList.append(QString::number(id));
    }

    return comList;
}

//void WStatus::addStage()
//{
//    WPhaseStageWidget *w;
//    int cnt = m_ListStage.count();
//    for(int i=0;i<cnt;i++)
//    {
//        w = m_ListStage[i];
//        w->close();
//    }
//    m_ListStage.clear();
//    StageTime_Table *p = &(m_pDataProcess->m_pTscInfo->tbStageTime[m_ucTimeStage-1][0]);

//    quint16 width = 0;
//    if(m_ucStageNum<=6)
//    {
//        width = 100;
//    }
//    else
//    {
//        width = 600/m_ucStageNum;
//    }


//    for(int i=0;i<16;i++)
//    {
//        if((p+i)->bStageNo!=0)
//        {
//            //qDebug()<<"stage Index"<<QString::number((p+i)->bStageNo);
//            quint16 green = qFromBigEndian<quint16>((p+i)->uEnablePhase);
//            w = new WPhaseStageWidget(m_pDataProcess,green,width);
//            w->setAttribute(Qt::WA_DeleteOnClose);
//            m_ListStage.append(w);
//            ui->hStageLayout->addWidget(w);

//        }
//        else
//        {
//            if(i!=m_ucStageNum)
//            {
//                qDebug()<<"stage num err"<<i;
//            }
//            break;
//        }
//    }
//}

//void WStatus::setIconDark(quint8 stageId)
//{
//    int cnt = m_ListStage.count();
//    for(int i=0;i<cnt;i++)
//    {
//        if(i+1==stageId)
//        {
//            m_ListStage[i]->setIconDark(false);
//        }
//        else
//        {
//            m_ListStage[i]->setIconDark(true);
//        }
//    }
//}

//--------------------------
void WStatus::on_checkBtn()
{
        quint32 timeSec = ui->dateTimeEdit->dateTime().toTime_t()+3600*8;
        QDateTime time = QDateTime::fromTime_t(timeSec);
        if(!ui->cbService->isChecked())
        {
            qDebug()<<"cbService is checked timeSec=0";
            timeSec = 0;
        }
        else
        {
            ui->cbService->setChecked(false);
            m_bBeginCheck = false;
        }

        qDebug()<<"time:"<<timeSec<<time.toString("yyyy-MM-dd hh:mm:ss")<<"timeSec"<<timeSec;
        m_pDataProcess->sendCheckTimeToTsc(timeSec);
//        ui->checkBtn->setText(tr("开始校时"));
        m_bRcvTscTime = false;//修改信号机时间后重新接收


}

void WStatus::on_ctrlTypeChange()
{
    if(ui->rbManual->isChecked())
    {
//        m_bManual = true;

//        ui->rbRed->setEnabled(true);
//        ui->rbYellow->setEnabled(true);
//        ui->rbClose->setEnabled(true);
//        ui->cbPhaseNum->setEnabled(true);
//        ui->nextStepBtn->setEnabled(true);
//        ui->nextStageBtn->setEnabled(true);
        qDebug()<<QObject::tr("手动控制")<<QString::number((unsigned char)(TSC_COMMAND_SWITCH_CONTROL));

        m_pDataProcess->sendCtrolCmd(CS_CMDTYPE_TSC_CONTROL_COMMAND,TSC_COMMAND_SWITCH_CONTROL,0x0a);


    }
    else
    {
        m_bManual = false;
//        ui->groupBox_3->setVisible(false);
//        ui->groupBox_4->setVisible(false);
        ui->rbRed->setChecked(false);
        ui->rbYellow->setChecked(false);
        ui->rbClose->setChecked(false);
        ui->rbDef->setChecked(true);

//        ui->rbRed->setCheckable(false);
//        ui->rbYellow->setCheckable(false);
//        ui->rbClose->setCheckable(false);
        ui->rbRed->setEnabled(false);
        ui->rbYellow->setEnabled(false);
        ui->rbClose->setEnabled(false);
        ui->cbPhaseNum->setEnabled(false);
        ui->nextStepBtn->setEnabled(false);
        ui->nextStageBtn->setEnabled(false);

        qDebug()<<"auto ctrl change";
        m_pDataProcess->sendCtrolCmd(CS_CMDTYPE_TSC_CONTROL_COMMAND,TSC_COMMAND_SWITCH_SYSTEMCONTROL,0);

        //----------
        ui->rbDef->setChecked(true);
    }

}

void WStatus::on_lightModeChange()
{
//    bool b = false;
    quint8 para2 = 0;
    if(ui->rbRed->isChecked())
    {
        para2 = 253;
//        m_bDefault = false;
    }
    else if(ui->rbYellow->isChecked())
    {
        para2 = 254;
//        m_bDefault = false;
    }
    else if(ui->rbClose->isChecked())
    {
        para2 = 255;
//        m_bDefault = false;
    }
//    else if(ui->rbDef->isCheckable())
//    {
//       b = true;
//       m_bDefault = true;
//    }

    if(m_bManual)
    {
        //qDebug()<<"light change";
        m_pDataProcess->sendCtrolCmd(CS_CMDTYPE_TSC_CONTROL_COMMAND,TSC_COMMAND_SWITCH_SYSTEMCONTROL,para2);
    }
    ui->cbPhaseNum->setEnabled(false);
    ui->nextStepBtn->setEnabled(false);
    ui->nextStageBtn->setEnabled(false);

}

void WStatus::on_cbPhaseChange(int index)
{
    if(ui->rbManual->isChecked())
    {
        if(index!=-1)
        {
            int phase = ui->cbPhaseNum->currentText().toInt();
            if(phase>1&&phase<(MAX_PHASEMAP_NUM+1))
            m_pDataProcess->sendCtrolCmd(CS_CMDTYPE_TSC_CONTROL_COMMAND,TSC_COMMAND_GOSTEP,phase);
        }
    }
}

void WStatus::on_nextStepBtn()
{
    m_pDataProcess->sendCtrolCmd(CS_CMDTYPE_TSC_CONTROL_COMMAND,TSC_COMMAND_GOSTEP,0);
}

void WStatus::on_nextStageBtn()
{
    quint8 stage = 0;
    if(m_ucCurStage<m_ucStageNum)
    {
        stage = m_ucCurStage;
    }
    m_pDataProcess->sendCtrolCmd(CS_CMDTYPE_TSC_CONTROL_COMMAND,TSC_COMMAND_SWITCH_STAGE,++stage);
}

void WStatus::on_cbFlashStatus(bool b)
{qDebug()<<"click flash check box";
    m_bRcvTscTime = false;
    if(b)
    {

        m_pDataProcess->requireTscTime();
//        m_pDataProcess->m_bFlagAutoReport = true;
        //m_pDataProcess->requireAutoReport(0xf8,10);
        //m_pDataProcess->requireAutoReport(0xf5,20);//信号机状态值
    }
    else
    {
        m_pStatus->killFlash();
        m_pDataProcess->requireAutoReport(0xf8,0,m_uiCurNodeId);
        //m_pDataProcess->requireAutoReport(0xf5,0);
        //m_pStatus->killFlashTimer();
        //m_pStatus
    }
}

void WStatus::on_rcvAutoReport(unsigned char *para1, int len,quint32 id)
{
    if(len==26)//25字节    add 20131114 。增加周期时长
    {
//        m_uiCurNodeId = id;
        if(!m_pDataProcess->m_bFlagShowStatus||id!=m_uiCurNodeId)
        {
           qDebug()<<"rcv auto report"<<m_pDataProcess->m_bFlagShowStatus<<id<<m_uiCurNodeId;
            ui->cbFlashStatus->setChecked(false);
            m_pStatus->killFlash();
            m_pDataProcess->requireAutoReport(0xf8,0,id);
            if(ui->cbFlashStatus->isChecked())
            {
                on_cbFlashStatus(false);
            }
            ui->rbAutoCtrl->setChecked(true);
            m_bManual = false;
            return;
        }
        unsigned char p[25];
        memcpy(p,para1+1,len-1);
        QChar a = '0';
       for(int i=0;i<24;i++)
          qDebug()<<"before p "<<QObject::tr("%1").arg(p[i],2,16,a);
        switch(p[0]&0x03)
        {
        case 0x00:
            break;
        case 0x01:
            break;
        case 0x02:
            break;
        default:
            break;
        }
        bool bLight = false;
        switch(p[0]&0x0c)
        {
        case 0x00://关灯
            bLight = true;
            //ui->rbManual->setChecked(true);
            ui->rbClose->setChecked(true);
            break;
        case 0x04://全红
            bLight = true;
            //ui->rbManual->setChecked(true);
            ui->rbRed->setChecked(true);
            break;
        case 0x08://闪光
            bLight = true;
            //ui->rbManual->setChecked(true);
            ui->rbYellow->setChecked(true);
            break;
        case 0x0c://标准
            //ui->rbAutoCtrl->setChecked(true);
            //ui->rbAutoCtrl->clicked(true);
            ui->rbDef->setChecked(true);
            break;
        default:
            break;
        }

QString statusStr;
        bool bManual = false;
        m_bManual = false;
        switch(p[0]&0xf0)
        {
        case 0x60://手动
            bManual = true;
            if(!ui->rbManual->isChecked())
            {
                //ui->rbManual->setChecked(true);
//                ui->rbManual->click();
            }
            statusStr.append(tr("手动"));
            break;

        case 0x10://多时段
            statusStr.append(tr("多时段"));
            //ui->rbAutoCtrl->setChecked(true);
            break;

        case 0x20://系统优化
            statusStr.append(tr("系统优化"));
           // ui->rbAutoCtrl->setChecked(true);
            break;
        case 0x30://无电线缆协调
            statusStr.append(tr("无电线缆协调"));
            //ui->rbAutoCtrl->setChecked(true);
            break;

        case 0x70://感应
            statusStr.append(tr("感应"));
            //ui->rbAutoCtrl->setChecked(true);
            break;
        case 0xa0://自适应
            statusStr.append(tr("自适应"));
           // ui->rbAutoCtrl->setChecked(true);
            break;
        case 0xb0://面板控制
            statusStr.append(tr("面板控制"));
           // ui->rbAutoCtrl->setChecked(true);
            break;
        default:
            statusStr.append(tr("未知控制"));
            //ui->rbAutoCtrl->setChecked(true);
            break;
        }
        m_pDataProcess->setStatusBarMessage(statusStr,LBFIRST);
        ui->leSchedule->setText(QString::number(p[1]));//时段号
        ui->lePattern->setText(QString::number(p[2]));//方案号
        quint8 timeStage = p[3];
        ui->leStage->setText(QString::number(timeStage));//配时号
        ui->leCycle->setText(QString::number(p[5]));
        m_ucStageNum = p[4];
        quint8 stageIndex = p[5];

        m_ucTime = p[6];
        m_ucTimePassed = p[7];
        //quint8 time = m_ucTime - m_ucTimePassed>0?m_ucTime - m_ucTimePassed:0;
        int tol = m_ucTime;
        int passed = m_ucTimePassed;
        int time = tol-passed;
        time+=1;



        if(bManual)
        {
            time = m_ucTimePassed;
        }

        quint32 red = 0;
        quint32 yellow = 0;
        quint32 green = 0;
        quint32 flash = 0;

        red = makeNum(p[8],p[9],p[10],p[11]);
        yellow = makeNum(p[12],p[13],p[14],p[15]);
        green = makeNum(p[16],p[17],p[18],p[19]);
        flash = makeNum(p[20],p[21],p[22],p[23]);

        //增加第25个字节，主要是显示周期时长。   add 20131114
        ui->leCycle_2->setText(QString::number(p[24]));


        m_pStatus->setData(green,yellow,red,flash,time);
        //-----------------------------
        quint32 nodeId = m_pDataProcess->getCurrentNodeId();
        if(nodeId!=m_uiCurNodeId)
        {
            m_pStatus->setData(0,0,0,0,0);
            m_uiCurNodeId = nodeId;
            changeNode();
            m_bChange = true;
            m_bRcvTscTime = false;
            return;
        }
        if(timeStage!=m_ucTimeStage)
        {
            m_ucTimeStage = timeStage;
            m_bChange = true;
        }
        if(m_bChange)
        {
            m_bChange = false;
            StageTime_Table (*p)[MAX_STAGE_NUM];
            p = m_pDataProcess->m_pTscInfo->tbStageTime;
            m_pStatus->setStageBase(*(p+timeStage-1));
        }

        if(bManual)
        {
            m_bManual = bManual;
            if(!ui->rbManual->isChecked())
            {
                //ui->rbManual->setChecked(true);
//                ui->rbManual->click();
            }
        }
        if(stageIndex!=m_ucCurStage)
        {
            m_ucCurStage = stageIndex;
            //qDebug()<<QObject::tr("阶段号：")<<m_ucCurStage;
            if(m_ucCurStage>0)
            {
                m_pStatus->setIconDark(m_ucCurStage-1);
            }
//            setIconDark(m_ucCurStage);
        }

//        qDebug()<<"==========================================================="<<m_bBeginCheck<<m_bRcvTscTime;
        if(!m_bBeginCheck)
        {
            if(!m_bRcvTscTime)
            {
                qDebug()<<"require tsc time=++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=";
                m_pDataProcess->requireTscTime();
            }
            else
            {

//                qDebug()<<"===========================================================";
                QDateTime time = QDateTime::currentDateTime();
                quint32 t = time.toTime_t()-m_iTimeOffset;
                ui->dateTimeEdit->setDateTime(QDateTime::fromTime_t(t));
                QDateTime iTime = ui->dateTimeEdit->dateTime();
//                qDebug()<<tr("currentTime:%1;tscTime%2;interfaceTime%3").arg(time.toString("yyyy-MM-dd hh:mm:ss")).arg(QDateTime::fromTime_t(t).toString("yyyy-MM-dd hh:mm:ss")).arg(iTime.toString("yyyy-MM-dd hh:mm:ss"));
            }

        }

        //-----------------------------------
        if(m_bManual==bManual)
        {
            if(m_bFirst)
            {
                m_bFirst = false;
            }
            if(bLight&&m_bManual)
            {
                ui->rbManual->setChecked(true);

                ui->rbRed->setEnabled(true);
                ui->rbYellow->setEnabled(true);
                ui->rbClose->setEnabled(true);
            }
            else if(!m_bManual)
            {
                ui->rbAutoCtrl->setChecked(true);
                on_rcvManualCtrl(false);
            }
            else
            {
                ui->rbManual->setChecked(true);
                ui->cbPhaseNum->setEnabled(true);
                ui->nextStepBtn->setEnabled(true);
                ui->nextStageBtn->setEnabled(true);
            }
        }
        else if(m_bFirst)
        {
            m_bManual = bManual;
        }
        else
        {
            m_bFirst = true;
        }

     //----------------------------------------------

    }
    else
    {
        qDebug()<<"auto report len err"<<len;
    }


}

void WStatus::on_rcvManualCtrl(bool b)
{
    if(b)
    {
        m_bManual = true;

        ui->rbRed->setEnabled(true);
        ui->rbYellow->setEnabled(true);
        ui->rbClose->setEnabled(true);
        ui->cbPhaseNum->setEnabled(true);
        ui->nextStepBtn->setEnabled(true);
        ui->nextStageBtn->setEnabled(true);
    }
    else
    {
        ui->rbAutoCtrl->setChecked(true);
        ui->rbRed->setEnabled(false);
        ui->rbYellow->setEnabled(false);
        ui->rbClose->setEnabled(false);
        ui->cbPhaseNum->setEnabled(false);
        ui->nextStepBtn->setEnabled(false);
        ui->nextStageBtn->setEnabled(false);
        qDebug()<<tr("手动控制失败");
//        m_pDataProcess->setStatusBarMessage(tr("手动控制失效"));
    }
}

void WStatus::on_rcvTscStatus(unsigned char *, int)
{

}

void WStatus::on_rcvTscTime(quint32 t)
{
    QDateTime time = QDateTime::currentDateTime();
    //time.addSecs(3600*8);
    m_iTimeOffset =  time.toTime_t()-t+3600*8;
    m_bRcvTscTime = true;
    if(ui->cbFlashStatus->isChecked())
    {
        if(!m_pDataProcess->m_bFlagAutoReport)
         m_pDataProcess->requireAutoReport(0xf8,10);
    }
//    qDebug()<<"on_rcvTscTime ++++++++++++++++++++++++++++++m_iTimeOffset:"<<t<<time.toTime_t()<<m_iTimeOffset;
//    QDateTime time = QDateTime::fromTime_t(t);
//    ui->dateTimeEdit->setDateTime(time);
}

void WStatus::on_selectStageIndex(quint8 index)
{
    if(ui->rbManual->isChecked())
    {
        qDebug()<<"manual ctrl select stage----------------------------------------------------------"<<index+1;
        m_pDataProcess->sendCtrolCmd(CS_CMDTYPE_TSC_CONTROL_COMMAND,TSC_COMMAND_SWITCH_STAGE,++index);
    }
}

void WStatus::on_nodeChange()
{
    m_pStatus->setData(0,0,0,0,0);
    m_uiCurNodeId = m_pDataProcess->m_uiCurNodeId;
    ui->rbAutoCtrl->setChecked(true);
    ui->rbDef->setChecked(true);

    ui->rbRed->setEnabled(false);
    ui->rbYellow->setEnabled(false);
    ui->rbClose->setEnabled(false);
    ui->cbPhaseNum->setEnabled(false);
    ui->nextStepBtn->setEnabled(false);
    ui->nextStageBtn->setEnabled(false);


    m_bManual = false;
    m_bFirst = false;
    changeNode();
    m_ucCurStage = 0;
    m_ucStageNum = 0;
    m_bChange = true;
    m_bRcvTscTime = false;
//    m_bBeginCheck = false;
}

void WStatus::on_cbService(bool b)
{
    m_bBeginCheck = b;
}
