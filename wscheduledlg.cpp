#include "wscheduledlg.h"

#include <QStringList>
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QSplitter>
#include <qendian.h>
#include <WinSock2.h>
#include <QMessageBox>
#include <QTimerEvent>
#include <qendian.h>

const QString SUMMERYDAY = QObject::tr("夏日制时基表");
const QString WINNERDAY = QObject::tr("冬日制时基表");
const QString SPECIALDAY = QObject::tr("特殊日时基表");
#include "CommClass.h"



WScheduleDlg::WScheduleDlg(QWidget *parent) :
    QDialog(parent)
{
    initDlg();
    patternDeligate = NULL;

//    eventView->setEnabled(false);
//    addEventBtn->setEnabled(false);
    delEventBtn->setEnabled(false);
    editSchBtn->setEnabled(false);
//    delSchBtn->setEnabled(false);
//    appSchBtn->setEnabled(false);
    m_bMoreClick = false;

    m_bFlagBtn = false;
    m_bFlagAdd = false;
    m_bFlagEdit = false;
    m_bFlagDel = false;
    m_bFlagSchAdd = false;
    m_bFlagSchEdit = false;
    m_bFlagSchDel = false;
    m_bTimeOut = false;
    m_bTimer = false;
    m_pTimeBase = new TimeBase_Table;
    m_pSchedule = new Schedule_Table[MAX_SCHEDULE_EVENT_NUM];
//    connect(selCB,SIGNAL(clicked()),this,SLOT(showSeason()));
    connect(sumRBtn,SIGNAL(clicked()),this,SLOT(showSumBtn()));
    connect(winRBtn,SIGNAL(clicked()),this,SLOT(showSumBtn()));
    connect(sumBtn,SIGNAL(clicked()),this,SLOT(showSumSelect()));

    connect(moreBtn,SIGNAL(clicked()),this,SLOT(on_moreBtn()));

    m_bClusterClick = false;
//    addBtn->setVisible(true);
    editBtn->setVisible(false);

//    selCB->setVisible(false);
    m_pDataProcess = NULL;
    showSeason();
}

WScheduleDlg::~WScheduleDlg()
{
    qDebug()<<"~WScheduleDlg";
    if(m_pTimeBase!=NULL)
    {
        delete m_pTimeBase;
        m_pTimeBase = NULL;
    }
    if(m_pSchedule!=NULL)
    {
        delete[] m_pSchedule;
        m_pSchedule = NULL;
    }
    if(ctrlDeligate!=NULL)
    {
        delete ctrlDeligate;
        ctrlDeligate = NULL;
    }
    if(timeDeligate!=NULL)
    {
        delete timeDeligate;
        timeDeligate = NULL;
    }
    if(patternDeligate!=NULL)
    {
        delete patternDeligate;
        patternDeligate = NULL;
    }
}

void WScheduleDlg::initDlg()
{
    this->setAutoFillBackground(true);
    tbView = new QListView;
    tbView->setMaximumWidth(120);
    tbView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbView->setMinimumWidth(100);

    tabWidget = new QTabWidget;
    normalWidget = new QWidget;
    specialWidget = new QWidget;

    normalWidget->setAutoFillBackground(true);
    specialWidget->setAutoFillBackground(true);
    tabWidget->setAutoFillBackground(true);

    tabWidget->addTab(normalWidget,tr("平日"));
    tabWidget->addTab(specialWidget,tr("特殊日"));

    selCB = new QCheckBox(tr("区分冬夏"));
    winRBtn = new QRadioButton(tr("冬日制"));
    sumRBtn = new QRadioButton(tr("夏日制"));
    sumBtn = new QPushButton(tr("更多"));
    sumBtn->hide();
selCB->hide();
winRBtn->hide();
//    winRBtn->setEnabled(false);
//    sumRBtn->setEnabled(false);
//    sumBtn->setEnabled(false);

    QStringList monthStrList;
    monthStrList<<QString::fromLocal8Bit("一月")<<QString::fromLocal8Bit("二月")<<QString::fromLocal8Bit("三月")<<QString::fromLocal8Bit("四月");
    monthStrList<<QString::fromLocal8Bit("五月")<<QString::fromLocal8Bit("六月")<<QString::fromLocal8Bit("七月")<<QString::fromLocal8Bit("八月");
    monthStrList<<QString::fromLocal8Bit("九月")<<QString::fromLocal8Bit("十月")<<QString::fromLocal8Bit("十一月")<<QString::fromLocal8Bit("十二月");

    startMonthCB = new QComboBox;
    startMonthCB->addItems(monthStrList);
    endMonthCB = new QComboBox;
    endMonthCB->addItems(monthStrList);
    sumWidget = new QWidget;

    startMonthLB = new QLabel(tr("夏日制从:"));
    endMonthLB = new QLabel(tr("到"));

    endMonthLB->setMaximumWidth(20);

    winRBtn->setChecked(true);
    startMonthCB->hide();
    endMonthCB->hide();
    startMonthLB->hide();
    endMonthLB->hide();

    startMonthCB->setCurrentIndex(4);
    endMonthCB->setCurrentIndex(8);

    QHBoxLayout *seasonHLayout = new QHBoxLayout;

    seasonHLayout->addWidget(winRBtn);
    seasonHLayout->addSpacing(50);
    seasonHLayout->addWidget(sumRBtn);
    seasonHLayout->addWidget(sumBtn);
    seasonHLayout->addStretch();
    seasonHLayout->setSizeConstraint(QLayout::SetFixedSize);
    QHBoxLayout *sumHLayout = new QHBoxLayout(sumWidget);
    sumHLayout->setSpacing(10);
    sumHLayout->addWidget(startMonthLB);
    sumHLayout->addWidget(startMonthCB);
    sumHLayout->addWidget(endMonthLB);
    sumHLayout->addWidget(endMonthCB);
    sumHLayout->addSpacing(50);
    QVBoxLayout *upVLayout = new QVBoxLayout();
    upVLayout->addWidget(selCB);
    upVLayout->addLayout(seasonHLayout);
    upVLayout->addWidget(sumWidget);

    upVLayout->setSizeConstraint(QLayout::SetFixedSize);



    QStringList wdStrList;
    wdStrList<<QString::fromLocal8Bit("日")<<QString::fromLocal8Bit("一")<<QString::fromLocal8Bit("二")<<QString::fromLocal8Bit("三");
    wdStrList<<QString::fromLocal8Bit("四") <<QString::fromLocal8Bit("五")<<QString::fromLocal8Bit("六");
    int i;
    for( i=0;i<7;i++)
    {
        QCheckBox *wdCB = new QCheckBox(wdStrList[i]);
        weekDayList.append(wdCB);
    }

    QGroupBox *weekGroup = new QGroupBox(tr("星期"));
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout(weekGroup);
    hLayout1->addWidget(weekDayList[0]);
    hLayout1->addStretch();
    for(i=0;i<3;i++)
    {
        hLayout2->addWidget(weekDayList[i+1]);
        hLayout3->addWidget(weekDayList[i+4]);
    }
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    QVBoxLayout *normalVLayout = new QVBoxLayout(normalWidget);
    normalVLayout->addLayout(upVLayout);
    normalVLayout->addWidget(weekGroup);




    for(i=0;i<12;i++)
    {
        QCheckBox *monthCB = new QCheckBox(monthStrList[i]);
        monthCB->setMinimumWidth(52);
        monthCB->setMaximumWidth(52);
        monthList.append(monthCB);
    }


    for(i=0;i<32;i++)
    {
        QCheckBox *monthDayCB = new QCheckBox(QString::number(i+1));
        monthDayCB->setMinimumWidth(37);
        monthDayCB->setMaximumWidth(37);
        monthDayList.append(monthDayCB);
    }
    //--------------------------
    cbAllDay = new QCheckBox(tr("全选"));
    cbAllDay->setMinimumWidth(37);
    cbAllDay->setMaximumWidth(44);

    QGroupBox *monthGroup = new QGroupBox(tr("月份:"));
    QHBoxLayout *monthHLayout1 = new QHBoxLayout;
    QHBoxLayout *monthHLayout2 = new QHBoxLayout;

    QGroupBox *monthDayGroup = new QGroupBox(tr("日期:"));
    QHBoxLayout *monthDayHLayout1 = new QHBoxLayout;
    QHBoxLayout *monthDayHLayout2 = new QHBoxLayout;
    QHBoxLayout *monthDayHLayout3 = new QHBoxLayout;
    QHBoxLayout *monthDayHLayout4 = new QHBoxLayout;

    for(i=0;i<6;i++)
    {
        monthHLayout1->addWidget(monthList[i]);
        monthHLayout2->addWidget(monthList[i+6]);
    }
    for(i=0;i<8;i++)
    {
        monthDayHLayout1->addWidget(monthDayList[i]);
        monthDayHLayout2->addWidget(monthDayList[i+8]);
        monthDayHLayout3->addWidget(monthDayList[i+16]);
        if(i!=7)
        {
            monthDayHLayout4->addWidget(monthDayList[i+24]);
        }

    }
    monthDayHLayout4->addWidget(cbAllDay);
   // monthDayHLayout4->addSpacing(40);


    QVBoxLayout *monthVLayout = new QVBoxLayout(monthGroup);
    monthVLayout->addLayout(monthHLayout1);
    monthVLayout->addLayout(monthHLayout2);

    QVBoxLayout *monthDayVLayout = new QVBoxLayout(monthDayGroup);
    monthDayVLayout->addLayout(monthDayHLayout1);
    monthDayVLayout->addLayout(monthDayHLayout2);
    monthDayVLayout->addLayout(monthDayHLayout3);
    monthDayVLayout->addLayout(monthDayHLayout4);

    QVBoxLayout *specialVlayout = new QVBoxLayout(specialWidget);
    specialVlayout->addWidget(monthGroup);
    specialVlayout->addWidget(monthDayGroup);


    QGroupBox *schGroup = new QGroupBox;
    QVBoxLayout *schVLayout = new QVBoxLayout(schGroup);
    QLabel *scheduleLB = new QLabel(tr("时间计划号:"));
    scheduleLB->setMaximumWidth(50);

    schView = new QListView;
    scheduleCB = new QComboBox;
    scheduleCB->setFixedWidth(90);

    addSchBtn = new QPushButton(tr("添加"));
    editSchBtn = new QPushButton(tr("编辑"));
    delSchBtn = new QPushButton(tr("删除"));
    appSchBtn = new QPushButton(tr("应用"));
    readSchBtn = new QPushButton(tr("读取"));

    QHBoxLayout *bottomHLayout = new QHBoxLayout;
    bottomHLayout->setSpacing(5);
    bottomHLayout->setSpacing(15);
    bottomHLayout->addStretch();
    bottomHLayout->addWidget(addSchBtn);
//    bottomHLayout->addWidget(editSchBtn);
    bottomHLayout->addWidget(delSchBtn);
    bottomHLayout->addWidget(appSchBtn);
    bottomHLayout->addWidget(readSchBtn);
    bottomHLayout->addStretch();
    eventView = new QTableView();
    QStringList ctrlStrList;

    ctrlStrList<<tr("自主控制")<<tr("关灯")<<tr("闪光")<<tr("全红")<<tr("感应")<<tr("无电线缆协调")<<tr("单点优化")<<tr("主从线控")<<tr("系统优化")<<tr("干预线控");
    ctrlDeligate = new ComboxDeligate(ctrlStrList);
    timeDeligate = new TimeEditDeligate();
    eventView->setItemDelegateForColumn(1,ctrlDeligate);
    eventView->setItemDelegateForColumn(0,timeDeligate);

    moreBtn = new QPushButton(tr("更多>>"));
    QHBoxLayout *hMoreLayout = new QHBoxLayout;
    hMoreLayout->addStretch();
    hMoreLayout->addWidget(moreBtn);
moreBtn->hide();
    addEventBtn = new QPushButton(tr("添加"));
    delEventBtn = new QPushButton(tr("删除"));

    QHBoxLayout *hEventLayout = new QHBoxLayout;
    hEventLayout->addStretch();
    hEventLayout->addWidget(addEventBtn);
    hEventLayout->addWidget(delEventBtn);
    hEventLayout->addStretch();

    schVLayout->addLayout(hMoreLayout);
    schVLayout->addWidget(eventView);
    schVLayout->addLayout(hEventLayout);


    QVBoxLayout *rightVLayout = new QVBoxLayout;


    rightVLayout->setSizeConstraint(QLayout::SetFixedSize);

    QHBoxLayout *mainUpHLayout = new QHBoxLayout;


    addBtn = new QPushButton(tr("添加"));
    editBtn = new QPushButton(tr("编辑"));
    appBtn = new QPushButton(tr("应用"));
    delBtn = new QPushButton(tr("删除"));
    readBtn = new QPushButton(tr("读取"));
    cbChoice = new QComboBox;
    QStringList choiceList;
    choiceList.append(tr("特殊日"));
    choiceList.append(tr("冬日制"));
    choiceList.append(tr("夏日制"));
    cbChoice->addItems(choiceList);

//    appBtn->setEnabled(false);
//    delBtn->setEnabled(false);
    editBtn->setEnabled(false);

    QHBoxLayout *downHLayout = new QHBoxLayout;
    //downHLayout->setMargin(15);
    downHLayout->setSpacing(15);
    downHLayout->addStretch();
    downHLayout->addWidget(addBtn);
    downHLayout->addWidget(cbChoice);
//    downHLayout->addWidget(editBtn);
    downHLayout->addWidget(delBtn);
    downHLayout->addWidget(appBtn);
    downHLayout->addWidget(readBtn);
    downHLayout->addStretch();



//--------------------------------------------------------
    QHBoxLayout *hSchNoLayout = new QHBoxLayout;
    hSchNoLayout->addWidget(scheduleLB);
    hSchNoLayout->addWidget(scheduleCB);

    hSchNoLayout->addStretch();


    rightVLayout->addWidget(tabWidget);

    rightVLayout->addLayout(hSchNoLayout);
    //bottomHLayout->addStretch();

    mainUpHLayout->addStretch();
    mainUpHLayout->addWidget(tbView);
    mainUpHLayout->addSpacing(10);
    mainUpHLayout->addLayout(rightVLayout);
    mainUpHLayout->addStretch();


    schView->setMaximumWidth(120);
    QHBoxLayout *mainDownHlayout = new QHBoxLayout;
    mainDownHlayout->addStretch();
    mainDownHlayout->addWidget(schView);
    mainDownHlayout->addSpacing(10);
    mainDownHlayout->addWidget(schGroup);
    mainDownHlayout->addStretch();
    schGroup->setMinimumWidth(400);
    tabWidget->setMinimumWidth(400);

    //------------------------cluster------------
        ctBtn = new QPushButton(tr("群"));
        QHBoxLayout *ctHLayout = new QHBoxLayout;
        ctHLayout->addStretch();
        ctHLayout->addWidget(ctBtn);
        ctHLayout->addStretch();


    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    //mainVLayout->addStretch();
//    mainVLayout->addLayout(mainUpHLayout);
//    mainVLayout->addSpacing(5);
//    mainVLayout->addLayout(downHLayout);
//    mainVLayout->addSpacing(20);
    mainVLayout->addLayout(mainDownHlayout);
    mainVLayout->addSpacing(5);
    mainVLayout->addLayout(bottomHLayout);
    mainVLayout->addSpacing(10);
//    mainVLayout->addLayout(ctHLayout);
    ctBtn->hide();
//tabWidget->setEnabled(false);
    addEventBtn->setToolTip(tr("添加时段里的事件"));
    delEventBtn->setToolTip(tr("删除时段里的事件"));
    addSchBtn->setToolTip(tr("添加新时段"));
    editSchBtn->setToolTip(tr("编辑某个时段"));
    delSchBtn->setToolTip(tr("删除某个时段"));
    appSchBtn->setToolTip(tr("发送时段表"));
    readSchBtn->setToolTip(tr("读取时段表"));

    addBtn->setToolTip(tr("添加新时基"));
    editBtn->setToolTip(tr("编辑某个时基"));
    appBtn->setToolTip(tr("发送时基表"));
    delBtn->setToolTip(tr("删除某个时基"));
    readBtn->setToolTip(tr("读取时基表"));
}

void WScheduleDlg::on_changeSpecialModel()
{
    clearInterface();
    tabWidget->setCurrentIndex(1);
    m_ucBase = 0;
    m_ucCount = 20;
    if(m_pDataProcess->m_pModelTimeBaseName->rowCount()>0)
    {
        on_clickTimebaseIndex(m_pDataProcess->m_pModelTimeBaseName->index(0,0));
    }
}

void WScheduleDlg::on_dataChange()
{qDebug()<<"on_dataChange()";
    if(m_bDataInit)
    {
        TimeBase_Table *pTimeBase = NULL;
        if(m_bClusterClick)
        {
            qDebug()<<"on_dataChange cluster";
            pTimeBase = m_pDataProcess->m_pClusterInfo->tbCTTimeBase+m_ucTimeBaseIndex;
        }
        else
        {
            qDebug()<<"on_dataChange tsc";
            pTimeBase = m_pDataProcess->m_pTscInfo->tbTimeBase+m_ucTimeBaseIndex;
        }
        getDataFromInterface(pTimeBase);
    }
}

void WScheduleDlg::on_tabChange(int index)
{
    clearInterface();
    setCheckBoxEnable(false);
    //int base = 0;
    int cnt = 0;
    //tabWidget->setEnabled(false);
    if(index==0)
    {
        if(winRBtn->isChecked())
        {
            m_ucBase = WIN_TIMEBASE_INDEX;
            cnt = MAX_TIMEBASE_NUM-WIN_TIMEBASE_INDEX;
        }
        else if(sumRBtn->isChecked())
        {
            m_ucBase = SUM_TIMEBASE_INDEX;
            cnt = WIN_TIMEBASE_INDEX-SUM_TIMEBASE_INDEX;
        }
    }
    else if(index==1)
    {
        m_ucBase = 0;
        cnt = SUM_TIMEBASE_INDEX;
    }
    m_ucCount = cnt;
    TimeBase_Table *p = NULL;
    if(m_bClusterClick)
    {
        p = m_pDataProcess->m_pClusterInfo->tbCTTimeBase;
    }
    else
    {
        p = m_pDataProcess->m_pTscInfo->tbTimeBase;
    }
    m_pDataProcess->setTimeBaseModel(p,m_ucBase,cnt);
}


void WScheduleDlg::on_clickTimebaseIndex(QModelIndex index)
{
//    if(!index.isValid())
//    {
//        setCheckBoxEnable(false);
//        return;
//    }

//    tbView->setCurrentIndex(index);
//    QString str = m_pDataProcess->m_ListTimeBaseName[index.row()];
//    int num;
////    m_ucBase = getBaseNum(str);
//    if(str.length()==8)
//    {
//        num = str.right(2).toInt();
//    }
//    if(str.length()==7)
//    {
//        num = str.right(1).toInt();
//    }
//    m_ucTimeBaseIndex = m_ucBase+num-1;
////    m_ucTimeBaseIndex = m_ucBase+index.row();
//    if(m_bClusterClick)
//    {qDebug()<<"on_clickTimebaseIndex cluster";
//        TimeBase_Table *pTimeBase = m_pDataProcess->m_pClusterInfo->tbCTTimeBase+m_ucTimeBaseIndex;
//        setInterfaceFromData(pTimeBase);
//    }
//    else
//    {qDebug()<<"on_clickTimebaseIndex tsc";
//        TimeBase_Table *pTimeBase = &m_pDataProcess->m_pTscInfo->tbTimeBase[m_ucTimeBaseIndex];
//        setInterfaceFromData(pTimeBase);
//    }
}

void WScheduleDlg::on_clickSchIndex(QModelIndex index)
{
    schView->setCurrentIndex(index);
    addEventBtn->setVisible(true);
    delEventBtn->setVisible(true);
    qDebug()<<"index row"<<index.row()<<"index col"<<index.column();
}

void WScheduleDlg::showSumSelect()
{
    //m_bFlagBtn = true;
    sumBtn->setVisible(false);
//    if(m_bFlagBtn)
//    {
//        sumBtn->setText(tr("隐藏"));
//    }
//    else
//    {
//        sumBtn->setText(tr("更多"));
//    }
    if(m_bFlagBtn)
    {
        startMonthCB->show();
        endMonthCB->show();
        startMonthLB->show();
        endMonthLB->show();

    }
    else
    {
        startMonthCB->hide();
        endMonthCB->hide();
        startMonthLB->hide();
        endMonthLB->hide();
    }
}

void WScheduleDlg::showSumBtn()
{
    clearInterface();
//    tabWidget->setEnabled(false);
    if(sumRBtn->isChecked())
    {
        //sumBtn->show();
        m_bFlagBtn = true;
        showSumSelect();
        m_ucBase = SUM_TIMEBASE_INDEX;
        m_ucCount = WIN_TIMEBASE_INDEX-SUM_TIMEBASE_INDEX;


    }
    else
    {
        sumBtn->hide();
        m_bFlagBtn = false;
        showSumSelect();

        m_ucBase = WIN_TIMEBASE_INDEX;
        m_ucCount = MAX_TIMEBASE_NUM-WIN_TIMEBASE_INDEX;

    }
    TimeBase_Table *p = NULL;

    if(m_pDataProcess!=NULL)
    {
        if(m_bClusterClick)
        {
            p = m_pDataProcess->m_pClusterInfo->tbCTTimeBase;
        }
        else if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            p = m_pDataProcess->m_pTscInfo->tbTimeBase;
        }
        m_pDataProcess->setTimeBaseModel(p,m_ucBase,m_ucCount);
    }
}

void WScheduleDlg::showSeason()
{
    if(selCB->isChecked())
    {
        winRBtn->setEnabled(true);
        sumRBtn->setEnabled(true);
        sumBtn->setEnabled(true);
        sumRBtn->setChecked(true);
        showSumBtn();
    }
    else
    {
        winRBtn->setEnabled(false);
        winRBtn->setChecked(true);
        sumRBtn->setEnabled(false);
        sumBtn->hide();
        showSumBtn();
    }

//    showSumBtn();
    if(m_bFlagBtn)
    {
        showSumSelect();
    }
}

void WScheduleDlg::setDataProcess(PDataProcess *dp)
{
    m_pDataProcess = dp;

    connect(addBtn,SIGNAL(clicked()),this,SLOT(on_addBtn()));
    connect(editBtn,SIGNAL(clicked()),this,SLOT(on_editBtn()));
    connect(delBtn,SIGNAL(clicked()),this,SLOT(on_delBtn()));
    connect(appBtn,SIGNAL(clicked()),this,SLOT(on_appBtn()));
    connect(readBtn,SIGNAL(clicked()),this,SLOT(on_readBtn()));

    connect(addSchBtn,SIGNAL(clicked()),this,SLOT(on_addSchBtn()));
    connect(editSchBtn,SIGNAL(clicked()),this,SLOT(on_editSchBtn()));
    connect(delSchBtn,SIGNAL(clicked()),this,SLOT(on_delSchBtn()));
    connect(appSchBtn,SIGNAL(clicked()),this,SLOT(on_appSchBtn()));
    connect(readSchBtn,SIGNAL(clicked()),this,SLOT(on_readSchBtn()));
    connect(dp,SIGNAL(clusterClick(bool)),this,SLOT(on_clusterClick(bool)));

    tbView->setModel(m_pDataProcess->m_pModelTimeBaseName);
    if(m_pDataProcess->m_pModelEvent!=NULL)
    {
        eventView->setModel(m_pDataProcess->m_pModelEvent);
        eventView->hideColumn(3);
        eventView->hideColumn(4);
        for(int i=0;i<3;i++)
            eventView->setColumnWidth(i,110);
    }

    scheduleCB->setModel(m_pDataProcess->m_pModelScheduleName);

    schView->setModel(m_pDataProcess->m_pModelScheduleName);

    setPatternDeligate();

    connect(tbView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_tbViewSelect(QModelIndex)));
//    connect(m_pDataProcess,SIGNAL(receivedTimeBaseResponse(char*,int)),this,SLOT(on_rcvTimeBaseResponse(char*,int)));

    connect(schView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_schViewSelect(QModelIndex)));
    connect(schView,SIGNAL(entered(QModelIndex)),this,SLOT(on_schViewSelect(QModelIndex)));
//    connect(m_pDataProcess,SIGNAL(receivedScheduleResponse(char*,int)),this,SLOT(on_rcvScheduleResponse(char*,int)));

    connect(eventView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_eventViewSelect(QModelIndex)));
    connect(addEventBtn,SIGNAL(clicked()),this,SLOT(on_addEventBtn()));
    connect(delEventBtn,SIGNAL(clicked()),this,SLOT(on_delEventBtn()));
    connect(m_pDataProcess,SIGNAL(updateTimePatternName()),this,SLOT(on_updatePatternDeligate()));
    connect(ctBtn,SIGNAL(clicked()),this,SLOT(on_ctBtn()));
    //----------------------------

    foreach(QCheckBox*cb,monthDayList)
    {
        connect(cb,SIGNAL(clicked()),this,SLOT(on_dataChange()));
    }
    connect(cbAllDay,SIGNAL(clicked(bool)),this,SLOT(on_cbAllDay(bool)));
    foreach(QCheckBox*cb,monthList)
    {
        connect(cb,SIGNAL(clicked()),this,SLOT(on_dataChange()));
    }
    foreach(QCheckBox*cb,weekDayList)
    {
        connect(cb,SIGNAL(clicked()),this,SLOT(on_dataChange()));
    }
    connect(scheduleCB,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dataChange()));
    connect(startMonthCB,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dataChange()));
    connect(endMonthCB,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dataChange()));

    connect(dp,SIGNAL(changeSpecialModel()),this,SLOT(on_changeSpecialModel()));
//    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_tabChange(int)));
    connect(dp,SIGNAL(clickTimebaseIndex(QModelIndex)),this,SLOT(on_clickTimebaseIndex(QModelIndex)));
    connect(dp,SIGNAL(clickSchIndex(QModelIndex)),this,SLOT(on_clickSchIndex(QModelIndex)));

}

void WScheduleDlg::on_addBtn()
{
    TimeBase_Table *p;
    if(m_bClusterClick)
    {
        p = m_pDataProcess->m_pClusterInfo->tbCTTimeBase;
    }
    else
    {
        p = m_pDataProcess->m_pTscInfo->tbTimeBase;
    }
    switch(cbChoice->currentIndex())
    {
    case 0:
        tabWidget->setCurrentIndex(1);
        m_ucBase = SPECIAL_TIMEBASE_INDEX;
        break;
    case 1:
        tabWidget->setCurrentIndex(0);
        if(selCB->isChecked())
        {
            selCB->click();
        }
        m_ucBase = WIN_TIMEBASE_INDEX;
        break;
    case 2:
        tabWidget->setCurrentIndex(0);
        if(!selCB->isChecked())
        {
            selCB->click();
        }

        m_ucBase = SUM_TIMEBASE_INDEX;
        break;
        default:
        m_ucBase = SPECIAL_TIMEBASE_INDEX;
        break;
    }
    qDebug()<<"cbChoice inede"<<cbChoice->currentIndex()<<"base"<<m_ucBase;
    m_pDataProcess->addTimebaseIndex(p,m_ucBase,m_ucCount);
}

void WScheduleDlg::on_editBtn()
{
    m_bFlagEdit = !m_bFlagEdit;
    if(m_bFlagEdit)
    {
        appBtn->setEnabled(true);
        delBtn->setEnabled(false);
        editBtn->setText(tr("取消编辑"));
    }
    else
    {
        appBtn->setEnabled(false);
        editBtn->setText(tr("编辑"));
    }
    addBtn->setEnabled(!m_bFlagEdit);
}

void WScheduleDlg::on_delBtn()
{
    TimeBase_Table *p = NULL;
    if(m_bClusterClick)
    {
        p = m_pDataProcess->m_pClusterInfo->tbCTTimeBase;
    }
    else
    {
        p = m_pDataProcess->m_pTscInfo->tbTimeBase;
    }

    memset(p+m_ucTimeBaseIndex,0,sizeof(TimeBase_Table));
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->setTimeBaseModel(p,m_ucBase,m_ucCount);
    }
}

void WScheduleDlg::on_appBtn()
{
    m_pDataProcess->sendTimeBaseToLib(m_bClusterClick);
}

void WScheduleDlg::on_readBtn()
{
    if(m_pDataProcess->m_bFlagCluster)
    {
        quint8 ctId = m_pDataProcess->getCurClusterId();
        m_pDataProcess->requireDataBaseTable(CLUSTER_TIMEBASE,ctId);
    }
    else
    {
        m_pDataProcess->requireTscTable(TSC_TABLE_TIMEBASE);
    }
}

void WScheduleDlg::on_moreBtn()
{
    m_bMoreClick = !m_bMoreClick;
    if(m_bMoreClick)
    {
        moreBtn->setText(tr("隐藏<<"));

        eventView->showColumn(3);
        eventView->showColumn(4);
        for(int i=0;i<5;i++)
        eventView->setColumnWidth(i,70);
    }
    else
    {
        moreBtn->setText(tr("更多>>"));
        eventView->hideColumn(3);
        eventView->hideColumn(4);
        for(int i=0;i<3;i++)
            eventView->setColumnWidth(i,116);
    }
}

void WScheduleDlg::on_addEventBtn()
{
    QStandardItemModel *model = m_pDataProcess->m_pModelEvent;
    if(model->rowCount()<MAX_SCHEDULE_EVENT_NUM)
    {
        QStandardItem item /*= new QStandardItem(1,5)*/;
        model->appendRow(&item);
    }
}

void WScheduleDlg::on_delEventBtn()
{
    QStandardItemModel *model = m_pDataProcess->m_pModelEvent;
    model->removeRow(m_ucEventIndex);
    m_pDataProcess->on_schEventChange();
    delEventBtn->setEnabled(false);
}

void WScheduleDlg::on_addSchBtn()
{
//    m_bFlagSchAdd = !m_bFlagSchAdd;
//    if(m_bFlagSchAdd)
//    {
        //addSchBtn->setText(tr("取消添加"));
    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM];
    if(m_bClusterClick)
    {
        p = m_pDataProcess->m_pClusterInfo->tbCTSchedule;
    }
    else
    {
        p = m_pDataProcess->m_pTscInfo->tbSchedule;
    }
        quint8 schIndex = m_pDataProcess->getScheduleIndex(p);
        m_ucScheduleIndex = schIndex;

//    }
//    else
//    {
//        addSchBtn->setText(tr("添加"));
//    }
//    appSchBtn->setEnabled(m_bFlagSchAdd);
//    addEventBtn->setEnabled(m_bFlagSchAdd);//事件
//    eventView->setEnabled(m_bFlagSchAdd);
    m_pDataProcess->addScheduleNameList(m_ucScheduleIndex+1,p);
    addEventBtn->setVisible(true);
    delEventBtn->setVisible(true);
//    delSchBtn->setEnabled(!m_bFlagSchAdd);
//    editSchBtn->setEnabled(!m_bFlagSchAdd);

}


void WScheduleDlg::on_editSchBtn()
{

    m_bFlagSchEdit = !m_bFlagSchEdit;
    if(m_bFlagSchEdit)
    {
        editSchBtn->setText(tr("取消编辑"));



    }
    else
    {
        editSchBtn->setText(tr("编辑"));
    }
    appSchBtn->setEnabled(m_bFlagSchEdit);
    addEventBtn->setEnabled(m_bFlagSchEdit);
//    eventView->setEnabled(m_bFlagSchEdit);

     addSchBtn->setEnabled(!m_bFlagSchEdit);
     delSchBtn->setEnabled(!m_bFlagSchEdit);
}

void WScheduleDlg::on_delSchBtn()
{
    QModelIndex index = schView->currentIndex();
    if(index.isValid())
    {
        //int tbSize = sizeof(Schedule_Table);
        int i = m_ucScheduleIndex;
        Schedule_Table (*tbSchedule)[MAX_SCHEDULE_EVENT_NUM];
        tbSchedule = m_pDataProcess->m_pTscInfo->tbSchedule;
        for(int j=0;j<MAX_SCHEDULE_EVENT_NUM;j++)
        {
            tbSchedule[i][j].bNo = i+1;
            tbSchedule[i][j].bEventNo = 0;
            tbSchedule[i][j].bHour = 0;
            tbSchedule[i][j].bMinute = 0;
            tbSchedule[i][j].bControlMode = 0;
            tbSchedule[i][j].bTimePatternNo = 0;
            tbSchedule[i][j].bAssistantOut = 0;
            tbSchedule[i][j].bSpecialOut = 0;
        }
        //qDebug()<<"del sch current index"<<index.isValid()<<index.row();
        int cnt = m_pDataProcess->m_pModelScheduleName->rowCount();
        if(cnt<2)
        {
            addEventBtn->setVisible(false);
            delEventBtn->setVisible(false);
        }
        m_pDataProcess->delScheduleNameList(index);
    }

}
void WScheduleDlg::on_appSchBtn()
{
    m_pDataProcess->sendScheduleToLib(m_bClusterClick);
////    addEventBtn->setEnabled(false);
//    bool bSend;
//    bool bCluster = m_pDataProcess->getClusterState();


//    m_pDataProcess->getDataFromScheduleModel();
//    if(bCluster)
//    {
//        bSend = m_pDataProcess->sendClusterSchedule(m_ucScheduleIndex,m_bFlagSchAdd,m_bFlagSchEdit,m_bFlagSchDel);
//    }
//    else
//    {
//        //bSend = m_pDataProcess->sendScheduleToLib(m_ucScheduleIndex,m_bFlagSchAdd,m_bFlagSchEdit,m_bFlagSchDel);
//    }
//    if(bSend)
//    {
////        appSchBtn->setEnabled(false);
//        delEventBtn->setEnabled(false);
//        if(m_bFlagSchAdd)
//        {
//            addSchBtn->setText(tr("添加"));
//        }
//        else
//        {
//            editSchBtn->setText(tr("编辑"));
//        }
//        editSchBtn->setEnabled(false);
//        addSchBtn->setEnabled(false);
////        eventView->setEnabled(false);

//        startTimeOut();
//    }
//    else
//    {
//        qDebug()<<"app send error";
//    }
}

void WScheduleDlg::on_readSchBtn()
{
    if(m_pDataProcess->getClusterState())
    {
        m_pDataProcess->requireDataBaseTable(CLUSTER_SCHEDULE,m_pDataProcess->getCurClusterId());
    }
    else
    {
        m_pDataProcess->requireTscTable(TSC_TABLE_SCHEDULE);
    }
}

void WScheduleDlg::on_rcvTimeBaseResponse(char *para1, int)
{
    if(*para1==0x01)
    {
        QString str;
        para1++;
        switch(*para1)
        {
        case CS_ERRTYPE_RIGHT://       = 0x00  ,  //正确
            {
                if(m_bTimer)
                {
                    this->killTimer(m_iTimerId);
                    m_bTimer = false;
                }
                if(!m_bTimeOut)
                {
//                    m_pDataProcess->updateLocalTimeBase(m_ucTimeBaseIndex,m_bFlagAdd,m_bFlagEdit,m_bFlagDel,m_pTimeBase);
                }
                if(m_bFlagAdd)
                {
                    addBtn->setEnabled(true);
                    if(!m_bTimeOut)
                    {
                        str = QObject::tr("添加时基表成功");
                    }
                    else
                    {
                        str = QObject::tr("添加时基表超时");
                    }
                    m_bFlagAdd = false;
                }
                if(m_bFlagEdit)
                {
                    addBtn->setEnabled(true);
                    if(!m_bTimeOut)
                    {
                        str = QObject::tr("编辑时基表成功");
                    }
                    else
                    {
                        str = QObject::tr("编辑时基表超时");
                    }
                    m_bFlagEdit = false;
                }
                if(m_bFlagDel)
                {
                    if(!m_bTimeOut)
                    {
                        str = QObject::tr("删除时基表成功");
                    }
                    else
                    {
                        str = QObject::tr("删除时基表超时");
                    }
                    m_bFlagDel = false;
                }
                if(m_bTimeOut)
                {
                    m_bTimeOut = false;
                }

                m_pDataProcess->setStatusBarMessage(str);
                break;
            }
        default:
            break;
        }
    }
}

void WScheduleDlg::on_rcvScheduleResponse(char *para1, int)
{
    if(*para1==0x01)
    {
        QString str;
        para1++;
        switch(*para1)
        {
        case CS_ERRTYPE_RIGHT://       = 0x00  ,  //正确
            {
                if(m_bTimer)
                {
                    this->killTimer(m_iTimerId);
                    m_bTimer = false;
                }
                if(m_bTimeOut)
                {
//                    m_pDataProcess->updateLocalSchedule(m_ucScheduleIndex,m_bFlagSchAdd,m_bFlagSchEdit,m_bFlagSchDel);
                }
                if(m_bFlagSchAdd)
                {
                    addSchBtn->setEnabled(true);//在更新本地数据时 检查 数量 后选择 是否有效 更好
                    if(!m_bTimeOut)
                    {
                        str = QObject::tr("添加时段表成功");
                    }
                    else
                    {
                        str = QObject::tr("添加时段表超时");
                    }
                    m_bFlagSchAdd = false;
                }
                if(m_bFlagSchEdit)
                {
                    addSchBtn->setEnabled(true);
                    if(!m_bTimeOut)
                    {
                        str = QObject::tr("编辑时段表成功");
                    }
                    else
                    {

                        str = QObject::tr("编辑时段表超时");
                    }
                    m_bFlagSchEdit = false;
                }
                if(m_bFlagSchDel)
                {
                    if(!m_bTimeOut)
                    {
                        str = QObject::tr("删除时段表成功");
                    }
                    else
                    {
                        str = QObject::tr("删除时段表超时");
                    }
                    m_bFlagSchDel = false;
                }
                if(m_bTimeOut)
                {
                    m_bTimeOut = false;
                }
                m_pDataProcess->setStatusBarMessage(str);
                break;
            }
        default:
            break;
        }
    }
}

void WScheduleDlg::on_tbViewSelect(QModelIndex index)
{
    if(index.isValid())
    {qDebug()<<"on_tbViewSelect";
        QString str = m_pDataProcess->m_ListTimeBaseName[index.row()];
        int num;
        if(str.length()==8)
        {
            num = str.right(2).toInt();
        }
        if(str.length()==7)
        {
            num = str.right(1).toInt();
        }
        m_ucTimeBaseIndex = m_ucBase+num-1;
        //m_ucTimeBaseIndex = index.row();

        //m_pDataProcess->setListTimeBaseNameIndex(index.row());
        if(m_bClusterClick)
        {
            TimeBase_Table *pTimeBase = m_pDataProcess->m_pClusterInfo->tbCTTimeBase+m_ucTimeBaseIndex;
            setInterfaceFromData(pTimeBase);
        }
        else
        {
            TimeBase_Table *pTimeBase = &m_pDataProcess->m_pTscInfo->tbTimeBase[m_ucTimeBaseIndex];
            setInterfaceFromData(pTimeBase);
        }
    }
    else
    {
        editBtn->setEnabled(false);
        delBtn->setEnabled(false);
    }
}

/*
*/
void WScheduleDlg::on_schViewSelect(QModelIndex index)
{
    if(index.isValid())
    {
        editSchBtn->setEnabled(true);
        delSchBtn->setEnabled(true);
        QString str = m_pDataProcess->m_ListScheduleName[index.row()];
        int num;
        if(str.length()==6)
        {
            num = str.right(2).toInt();
        }
        if(str.length()==5)
        {
            num = str.right(1).toInt();
        }
        if(num>0)
        {
            m_ucScheduleIndex = quint8(num-1);
        }

//        m_pDataProcess->setListScheduleNameIndex(index.row());

        Schedule_Table (*pRow)[MAX_SCHEDULE_EVENT_NUM] ;
        if(m_bClusterClick)
        {
            pRow = m_pDataProcess->m_pClusterInfo->tbCTSchedule;
        }
        else
        {
            pRow = m_pDataProcess->m_pTscInfo->tbSchedule;
        }
        m_pDataProcess->setEventModelByIndex(m_ucScheduleIndex,pRow);
    }
    else
    {
        editBtn->setEnabled(false);
        delBtn->setEnabled(false);
    }
}

void WScheduleDlg::on_eventViewSelect(QModelIndex index)
{
    if(index.isValid())
    {
        m_ucEventIndex = index.row();

        delEventBtn->setEnabled(true);

    }
    else
    {
        delEventBtn->setEnabled(false);
    }

}

void WScheduleDlg::on_updatePatternDeligate()
{
    setPatternDeligate();
}

void WScheduleDlg::on_clusterClick(bool b)
{
    m_bClusterClick = b;
    ctBtn->setVisible(b);
    moreBtn->setVisible(b);

}

void WScheduleDlg::on_ctBtn()
{
//    m_pDataProcess->sendClusterPlan();
}

void WScheduleDlg::on_cbAllDay(bool b)
{
    foreach(QCheckBox* cb,monthDayList)
    {
        cb->setChecked(b);
    }
    on_dataChange();
}

void WScheduleDlg::setInterfaceFromData(TimeBase_Table *tbTimeBase)
{
    setCheckBoxEnable(true);
    m_bDataInit = false;
    byte bNo = m_ucTimeBaseIndex+1/*tbTimeBase->bNo*/;
    quint16 uMonth = qFromBigEndian<quint16>(tbTimeBase->uMonth);
    uMonth >>= 1;
    byte bWeekDay = tbTimeBase->bWeekDay;
    bWeekDay >>= 1;
    quint32 lMonthDay = qFromBigEndian<quint32>(tbTimeBase->lMonthDay);
//    qDebug()<<tr("quint32 lMonthDay %1,qint32 lMonthDay%2").arg(lMonthDay).arg((qint32)lMonthDay);
    lMonthDay >>= 1;
    byte bScheduleNo = tbTimeBase->bScheduleNo;
    qDebug()<<"setInterfaceFromData bScheduleNo"<<bScheduleNo;


    byte TEMP = 0x01;



    for(int i=0;i<32;i++)
    {
        if(byte(lMonthDay>>i)&TEMP)
        {

            monthDayList[i]->setChecked(true);
        }
        else
        {
            monthDayList[i]->setChecked(false);
        }
        if(i<12)
        {
            if(byte(uMonth>>i)&TEMP)
            {
                monthList[i]->setChecked(true);
            }
            else
            {
                monthList[i]->setChecked(false);
            }
            if(i<7)
            {
                if(byte(bWeekDay>>i)&TEMP)
                {
                    weekDayList[i]->setChecked(true);
                }
                else
                {
                    weekDayList[i]->setChecked(false);
                }
            }
        }
    }


    if(bNo>byte(SUM_TIMEBASE_INDEX-1))//夏日制
    {
;
        bool bFlag = false;
        for(int i=0;i<11;i++)
        {
            if(!bFlag)
            {
                if(monthList[i]->isChecked())
                {
                    startMonthCB->setCurrentIndex(i);
                    bFlag = true;
                }
            }
            else
            {
                if(!monthList[i]->isChecked())
                {
                    endMonthCB->setCurrentIndex(i-1);
                    break;
                }
            }
        }
    }


    scheduleCB->setEditable(true);
    if(bScheduleNo>0)
    {
        QString strChe = QObject::tr("时间计划");
        strChe+=QString::number(bScheduleNo);
        scheduleCB->setEditText(strChe);
    }
    else
    {
        scheduleCB->clearEditText();
    }
//    int schIndex = scheduleCB->findText(strChe);
//    if(schIndex!=-1)
//    {
//        scheduleCB->setCurrentIndex(schIndex);
//    }
//    else
//    {
//        scheduleCB->setEditText(strChe);
//    }
    m_bDataInit = true;
}



void WScheduleDlg::getDataFromInterface(TimeBase_Table *tbTimeBase)
{
    quint32 lMonthDay = 0;
    quint16 uMonth = 0;
    quint8 bWeekDay = 0;
    quint8 bScheduleNo = 0;
    quint8 TEMP = 0x01;

    bool bSpecialDay = false;
    bool bSumDay = false;

    if(!specialWidget->isHidden())
    {
        bSpecialDay = true;
        qDebug()<<"special day";
    }
    else if(sumRBtn->isChecked())
    {
        bSumDay = true;
        qDebug()<<"sum day";
    }

    for(int i=0;i<32;i++)
    {
        if(bSpecialDay)
        {
            bWeekDay = 0x7f;
            lMonthDay = lMonthDay<<1;
            if(monthDayList[31-i]->isChecked())
            {

                lMonthDay = lMonthDay|TEMP;
            }
            if(i<12)
            {
                uMonth = uMonth<<1;
                if(monthList[11-i]->isChecked())
                {

                    uMonth = uMonth|TEMP;
                }
            }
        }
        else
        {
            lMonthDay = 0x7fffffff;
            if(bSumDay)
            {
                uMonth = 0;
                quint16 temp;
                int startM = startMonthCB->currentIndex();
                int endM = endMonthCB->currentIndex();
                for(int i=startM;i<=endM;i++)
                {
                    temp = 1;
                    temp<<=i;
                    uMonth |= temp;
                }
            }
            else
            {
                uMonth = 0x0fff;
            }

            if(i<7)
            {
                bWeekDay = bWeekDay<<1;
                if(weekDayList[6-i]->isChecked())
                {

                    bWeekDay = bWeekDay|TEMP;
                }
            }
        }
    }
    QString str = scheduleCB->currentText();
    if(str.length()==6)//时段**
    {
        bScheduleNo = str.right(2).toInt();
    }
    else if(str.length()==5)//时段*
    {
        bScheduleNo = str.right(1).toInt();
    }

    tbTimeBase->bNo = m_ucTimeBaseIndex+1;
    tbTimeBase->bScheduleNo = bScheduleNo;
    tbTimeBase->bWeekDay = bWeekDay<<1;
    lMonthDay <<= 1;
qDebug()<<tr("0x%1").arg(lMonthDay,8,16)<<"atoi"<<"getDataFromInterface bScheduleNo"<<bScheduleNo;
    tbTimeBase->lMonthDay = qToBigEndian<quint32>(lMonthDay);
    uMonth <<=1;
    tbTimeBase->uMonth = qToBigEndian<quint16>(uMonth);
//    qDebug()<<tbTimeBase->bNo<<tbTimeBase->bScheduleNo<<tbTimeBase->bWeekDay<<tbTimeBase->lMonthDay<<tbTimeBase->uMonth;

}

//void WTimeBaseDlg::setWidgetsEnable(bool b)
//{
//    for(int i=0;i<32;i++)
//    {
//        monthDayList[i]->setEnabled(b);
//        if(i<12)
//        {
//            monthList[i]->setEnabled(b);
//            if(i<7)
//            {
//                weekDayList[i]->setEnabled(b);
//            }
//        }
//    }
//    selCB->setEnabled(b);
//    sumBtn->setEnabled(b);
//    startMonthCB->setEnabled(b);
//    endMonthCB->setEnabled(b);
//    winRBtn->setEnabled(b);
//    sumRBtn->setEnabled(b);
//    scheduleCB->setEnabled(b);
//}

void WScheduleDlg::setPatternDeligate()
{
    if(m_pDataProcess!=NULL)
    {
        if(patternDeligate!=NULL)
        {
            delete patternDeligate;
            patternDeligate = NULL;
        }
        patternDeligate = new ComboxDeligate(m_pDataProcess->m_ListTimePatternName);
        eventView->setItemDelegateForColumn(2,patternDeligate);
    }
}

void WScheduleDlg::timerEvent(QTimerEvent *e)
{
    m_bTimeOut = true;
    this->killTimer(e->timerId());
    m_bTimer = false;
    char para[2];
    para[0] = 0x01;
    para[1] = 0;
    if(m_bFlagAdd||m_bFlagEdit||m_bFlagDel)
    {

        on_rcvTimeBaseResponse(para,2);
    }
    else if(m_bFlagSchAdd||m_bFlagSchEdit||m_bFlagSchDel)
    {
        on_rcvScheduleResponse(para,2);
    }
}

void WScheduleDlg::startTimeOut()
{
    if(!m_bTimer)
    {
        m_iTimerId = this->startTimer(TIMEOUT5000);
        m_bTimer = true;
    }
}

void WScheduleDlg::clearInterface()
{
    qDebug()<<"clearInterface";
    m_bDataInit = false;
    scheduleCB->clearEditText();
    foreach(QCheckBox*cb,weekDayList)
    {
        cb->setChecked(false);
    }
    foreach(QCheckBox*cb,monthList)
    {
        cb->setChecked(false);
    }
    foreach(QCheckBox*cb,monthDayList)
    {
        cb->setChecked(false);
    }
    m_bDataInit = true;
}

void WScheduleDlg::setCheckBoxEnable(bool b)
{
    cbAllDay->setEnabled(b);
    foreach(QCheckBox*box,weekDayList)
    {
//        box->setCheckable(b);
        box->setEnabled(b);
    }
    foreach(QCheckBox*box,monthList)
    {
//        box->setCheckable(b);
        box->setEnabled(b);
    }
    foreach(QCheckBox*box,monthDayList)
    {
//        box->setCheckable(b);
        box->setEnabled(b);
    }
}

quint8 WScheduleDlg::getBaseNum(QString str)
{
    quint8 num = 0;
    if ( 0 == str.left(6).compare(SUMMERYDAY) )
    {
        num = SUM_TIMEBASE_INDEX;
        tabWidget->setCurrentIndex(0);
    }
    else if( 0 == str.left(6).compare(WINNERDAY))
    {
        num = WIN_TIMEBASE_INDEX;
        tabWidget->setCurrentIndex(0);
    }
    else if( 0 == str.left(6).compare(SPECIALDAY))
    {
        num = SPECIAL_TIMEBASE_INDEX;
        tabWidget->setCurrentIndex(1);
    }
    return num;
}
