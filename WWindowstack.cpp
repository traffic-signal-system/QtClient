//author: sun
//date:2011.09.29


#include "WWindowstack.h"
//#include "WDetectormoniter.h"
#include <QVBoxLayout>
#include "PDataProcess.h"
#include <QPushButton>
#include <QBrush>
#include <QPalette>
#include <QImage>
#include <QDebug>

WWindowstack::WWindowstack(QWidget *parent) :
    QStackedWidget(parent),
    m_pDataProcess(NULL)
{
    //在此添加窗体页面
    //页面：0
//    m_detectormonitor = new WDetectormoniter;
//    addWidget(m_detectormonitor);

//    QPushButton *test = new QPushButton("hello");
//    addWidget(test);

//    m_UserLogIn = new WUserLogIn;
//    addWidget(m_UserLogIn);

    //用户管理
    m_UserView = new WUserViewDlg;
    addWidget(m_UserView);

    m_NodeParaDlg = new WNodeParaDlg;

    m_TimeBaseDlg = new WTimeBaseDlg;

    m_Stage = new WStageWidget;

    m_PhaseDlg = new WPhaseWidget;
    //m_PhaseDlg->setFixedSize(500,680);

    m_StatusDlg = new WStatus;

    //-------检测器界面-------
    m_DetDlg = new WDetWidget;

    //--------事件日志------
    m_EventDlg = new WEventLogWidget;

    //-----------群--------------
    m_ClusterDlg = new WClusterDlg;

    //-----------vip-------
    m_VipDlg = new WVipDlg;

    //--------系统参数-------------
    m_SystemPara = new WSystemPara;

    //------------冲突相位-------------
    m_Conflict = new WConflct;

    //------------交通流量统计-----------------
    m_Traffic = new WTraffic;

    //----------时段表---------------------------
    m_Schedule = new WScheduleDlg;

    //-------------------------顺序--界面顺序与按钮顺序一致-----------
    addWidget(m_UserView);
    addWidget(m_NodeParaDlg);
    addWidget(m_PhaseDlg);
    addWidget(m_Stage);
    addWidget(m_DetDlg);
    addWidget(m_StatusDlg);
    addWidget(m_TimeBaseDlg);
    addWidget(m_ClusterDlg);
    addWidget(m_VipDlg);
    addWidget(m_EventDlg);
    addWidget(m_SystemPara);
    addWidget(m_Conflict);
    addWidget(m_Schedule);
    addWidget(m_Traffic);



    //在此设置显示
    setCurrentIndex(5);

    QImage img;
    if(img.load(":Files/images/bgdd.png"))
    {
        qDebug()<<"image succ";
    }
    else
    {
        qDebug()<<"image err";
    }
    QBrush *brush = new QBrush;
    brush->setTextureImage(img);
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    p.setBrush(QPalette::Window,*brush);
    this->setPalette(p);
}

WWindowstack::~WWindowstack()
{
//    delete m_detectormonitor;
    delete m_NodeParaDlg;//1101try
}

void WWindowstack::setProcessor(PDataProcess *processor)
{
    m_pDataProcess = processor;
//    for(int i=0; i<2; i++)//err
//    {
//        WPage *page = (WPage*)widget(i);
//        page->setProcessor(processor);
//    }
//    m_detectormonitor->setProcessor(processor);
    m_NodeParaDlg->setDataProcess(processor);
    m_TimeBaseDlg->setDataProcess(processor);
    m_Stage->setDataProcess(processor);
    m_PhaseDlg->setDataProcess(processor);
    m_StatusDlg->setDataProcess(processor);
    m_DetDlg->setDataProcess(processor);
    m_EventDlg->setDataProcess(processor);
    m_ClusterDlg->setDataProcess(processor);
    m_VipDlg->setDataProcess(processor);
    m_UserView->setDataProcess(processor);
    m_Conflict->setDataProcess(processor);
    m_SystemPara->setDataProcess(processor);
    m_Traffic->setDataProcess(processor);
    m_Schedule->setDataProcess(processor);
}

void WWindowstack::setWidgetIndex(int index)
{
    if(index==6)//时基表界面
    {
        //bool bSingle = m_pDataProcess->m_bFlagSingle;
        int nodeIndex = m_pDataProcess->m_TscIdList.indexOf(QString::number(m_pDataProcess->m_uiCurNodeId));
        if(nodeIndex!=-1)
        {
//            quint8 ctId = m_pDataProcess->m_TscClusterIdList[nodeIndex];
            //bool b = ctId==1?true:false;
            //m_Stage->showStagePage(bSingle||b);//在默认群里 也当单机用
        }
    }
    else if(index==8)
    {
        m_VipDlg->showCurVip();//
    }
    else if(index==0)
    {
//        m_UserView->initViewData();
    }
    setCurrentIndex(index);
}


