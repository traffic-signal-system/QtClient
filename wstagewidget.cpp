#include "wstagewidget.h"
#include "ui_wstagewidget.h"

WStageWidget::WStageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WStageWidget)
{
    QWidget *w = new QWidget;
    ui->setupUi(w);
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hMainLayout = new QHBoxLayout(this);
    vLayout->addStretch();
    vLayout->addWidget(w);
    vLayout->addStretch();

    hMainLayout->addStretch();
    hMainLayout->addLayout(vLayout);
    hMainLayout->addStretch();
    init();
    m_pPattern = NULL;
    m_pStageTime = NULL;
    m_pDataProcess = NULL;
    m_ucStageNoIndex = 0;
    m_bDlgInit = true;
    //m_ucStageIdIndex = 0;
    connect(m_pStage,SIGNAL(changeStageIndex(quint8)),this,SLOT(on_stageIndexChange(quint8)));

}

WStageWidget::~WStageWidget()
{
    delete ui;
}

void WStageWidget::init()
{
    m_pStage = new WStage(ui->stageGroupBox);
//    m_pStage->setFlagClearStageGroup();
    m_pCol = new ColorWidget(ui->stageFrameColor);
    ui->patternSbNo->setPrefix(tr("方案"));
    ui->patternSbNo->setRange(1,MAX_TIMEPATTERN_NUM);
    ui->patternSbStageNo->setPrefix(tr("配时"));
    ui->patternSbStageNo->setRange(0,MAX_STAGE_PATTERN_NUM);
    ui->stageSbNo->setPrefix(tr("配时"));
    ui->stageSbNo->setRange(1,MAX_STAGE_PATTERN_NUM);
//    ui->stageSbTime->setRange(1,255);
    ui->stageLeId->setReadOnly(true);
//    ui->patternFromMore->setVisible(false);
    ui->stageFromMore->setVisible(false);
    ui->patternBtnMore->setText(tr("更多>>"));
    ui->stageBtnMore->setText(tr("更多>>"));
    connect(ui->patternBtnMore,SIGNAL(clicked()),this,SLOT(on_patternBtnMore()));
    connect(ui->stageBtnMore,SIGNAL(clicked()),this,SLOT(on_stageBtnMore()));
    connect(m_pStage,SIGNAL(btnReadStage()),this,SLOT(on_btnReadStage()));
    connect(m_pStage,SIGNAL(btnAppStage()),this,SLOT(on_btnAppStage()));
    ui->patternBtnMore->hide();
    ui->label_5->hide();
    ui->patternSbCoordinate->hide();
    ui->stageBtnMore->hide();
//    ui->patternFromMore->setVisible(true);
}

void WStageWidget::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;

    connect(ui->patternSbNo,SIGNAL(valueChanged(int)),this,SLOT(on_patternSbNoChange(int)));
    connect(ui->patternSbCircle,SIGNAL(valueChanged(int)),this,SLOT(on_patternSbCircleChange(int)));
    connect(ui->patternSbStageNo,SIGNAL(valueChanged(int)),this,SLOT(on_patternSbStageNoChange(int)));
    connect(ui->patternSbOffset,SIGNAL(valueChanged(int)),this,SLOT(on_patternSbOffsetChange(int)));
    connect(ui->patternSbCoordinate,SIGNAL(valueChanged(int)),this,SLOT(on_patternSbCoordinateChange(int)));
    connect(ui->patternBtnDel,SIGNAL(clicked()),this,SLOT(on_patternBtnDel()));
    connect(ui->patternBtnApp,SIGNAL(clicked()),this,SLOT(on_patternBtnApp()));
    connect(ui->patternBtnRead,SIGNAL(clicked()),this,SLOT(on_patternBtnRead()));
    connect(ui->stageSbNo,SIGNAL(valueChanged(int)),this,SLOT(on_stageSbNoChange(int)));
    connect(ui->stageSbTime,SIGNAL(valueChanged(int)),this,SLOT(on_stageSbTimeChange(int)));
    connect(ui->stageCbOption,SIGNAL(currentIndexChanged(int)),this,SLOT(on_stageCbOptionChange(int)));
    connect(m_pCol,SIGNAL(colorTimeChange(quint8,quint8,quint8)),this,SLOT(on_stageColorChange(quint8,quint8,quint8)));

    connect(ui->btnStageApp,SIGNAL(clicked()),this,SLOT(on_btnAppStage()));
    connect(ui->btnStageRead,SIGNAL(clicked()),this,SLOT(on_btnReadStage()));
    connect(p,SIGNAL(rcvPhase()),this,SLOT(on_rcvPhase()));
    connect(p,SIGNAL(rcvStageTimeTable()),this,SLOT(on_rcvStageTimeTable()));
    connect(p,SIGNAL(updateTimePatternName()),this,SLOT(on_rcvTimePatternTable()));
}

void WStageWidget::showPatternData()
{
    if(m_pPattern!=NULL)
    {
        m_bDlgInit = false;
        ui->patternSbCircle->setValue(m_pPattern->bCycle);
        ui->patternSbStageNo->setValue(m_pPattern->bStageTimeTableNo);
        ui->patternSbOffset->setValue(m_pPattern->bOffset);
        ui->patternSbCoordinate->setValue(m_pPattern->bCoordinatePhase);
        m_bDlgInit = true;
    }
}

void WStageWidget::clearPatternData()
{
    m_bDlgInit = false;
    ui->patternSbCircle->cleanText();
    ui->patternSbStageNo->cleanText();
    ui->patternSbOffset->cleanText();
    ui->patternSbCoordinate->cleanText();
    m_bDlgInit = true;
}

void WStageWidget::showStageData()
{
    if(m_pStageTime!=NULL)
    {
        m_bDlgInit = false;
        quint8 green = m_pStageTime->bGreenTime;
        quint8 yellow = m_pStageTime->bYellowTime;
        quint8 red = m_pStageTime->bRedTime;
        ui->stageSbTime->setValue(green+yellow+red);
        m_pCol->setTimeValue(green,yellow,red);
        m_bDlgInit = true;
    }
}

void WStageWidget::clearStageData()
{
    ui->stageLeId->clear();
    ui->stageSbTime->clear();
    ui->stageCbOption->clearEditText();
}

void WStageWidget::setFlagPattern(bool b)
{
    m_bShowPattern = b;
    ui->patternGroupBox->setVisible(b);
}

void WStageWidget::on_patternBtnMore()
{
    if(!ui->patternFromMore->isVisible())
    {
        ui->patternFromMore->setVisible(true);
        ui->patternBtnMore->setText(tr("<<隐藏"));
    }
    else
    {
        ui->patternFromMore->setVisible(false);
        ui->patternBtnMore->setText(tr("更多>>"));
    }
}

void WStageWidget::on_patternSbNoChange(int patternNo)
{
    if(m_pDataProcess!=NULL)
    {
        if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            clearPatternData();
            m_pPattern = m_pDataProcess->m_pTscInfo->tbTimePattern+patternNo-1;
            if(m_pPattern->bNo==0)
            {
                m_pPattern->bNo = patternNo;
            }
            showPatternData();
        }
        else
        {
            m_pPattern = NULL;
        }
    }
}

void WStageWidget::on_patternSbCircleChange(int time)
{
    if(m_bDlgInit&&m_pPattern!=NULL)
    {
        m_pPattern->bNo = ui->patternSbNo->value();
        m_pPattern->bCycle = time;
    }
}

void WStageWidget::on_patternSbStageNoChange(int stageNo)
{
    if(m_bDlgInit&&m_pPattern!=NULL)
    {
        m_pPattern->bNo = ui->patternSbNo->value();
        m_pPattern->bStageTimeTableNo = stageNo;
    }
}

void WStageWidget::on_patternSbOffsetChange(int time)
{
    if(m_bDlgInit&&m_pPattern!=NULL)
    {
        m_pPattern->bNo = ui->patternSbNo->value();
        m_pPattern->bOffset = time;
    }
}

void WStageWidget::on_patternSbCoordinateChange(int time)
{
    if(m_bDlgInit&&m_pPattern!=NULL)
    {
        m_pPattern->bNo = ui->patternSbNo->value();
        m_pPattern->bCoordinatePhase = time;
    }
}

void WStageWidget::on_patternBtnDel()
{
    if(m_pPattern!=NULL)
    {
        memset(m_pPattern,0,sizeof(TimePattern_Table));
        showPatternData();
    }
}

void WStageWidget::on_patternBtnApp()
{
    m_pDataProcess->sendTimePatternToLib();
}

void WStageWidget::on_patternBtnRead()
{
    m_pDataProcess->requireTscTable(TSC_TABLE_TIMEPATTERN);
}

void WStageWidget::on_stageBtnMore()
{
    if(!ui->stageFromMore->isVisible())
    {
        ui->stageFromMore->setVisible(true);
        ui->stageBtnMore->setText(tr("<<隐藏"));
    }
    else
    {
        ui->stageFromMore->setVisible(false);
        ui->stageBtnMore->setText(tr("更多>>"));
    }
}

void WStageWidget::on_stageSbNoChange(int stageNo)
{
    if(m_pDataProcess!=NULL&&stageNo>0&&stageNo<(MAX_STAGE_PATTERN_NUM+1))
    {qDebug()<<"stage no change"<<stageNo;
        if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            clearStageData();
            m_ucStageNoIndex = stageNo - 1;
            StageTime_Table (*p)[MAX_STAGE_NUM];
    //        m_pStage->setConflictBase( m_pDataProcess->m_pTscInfo->tbPhaseConflict);
            p = m_pDataProcess->m_pTscInfo->tbStageTime;
            m_pStage->setStageBase(*(p+m_ucStageNoIndex));
            //m_pStageTime = m_pDataProcess->m_pTscInfo->tbStageTime+m_ucStageNoIndex;
        }
    }
}

void WStageWidget::on_stageSbTimeChange(int time)
{
    if(m_bDlgInit)
    {
        m_pCol->setStageTime(time);
    }
}

void WStageWidget::on_stageColorChange(quint8 green, quint8 yellow, quint8 red)
{
    if(m_bDlgInit&&m_pStageTime!=NULL)
    {
        qDebug()<<"green:"<<green<<"yellow:"<<yellow<<"red"<<red;
        m_pStageTime->bGreenTime = green;
        m_pStageTime->bYellowTime = yellow;
        m_pStageTime->bRedTime = red;
    }
}

void WStageWidget::on_stageCbOptionChange(int)
{
    if(m_bDlgInit)
    {

    }
}

void WStageWidget::on_stageIndexChange(quint8 index)
{
    if(m_pDataProcess!=NULL&&index<MAX_STAGE_PATTERN_NUM)
    {
        if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            clearStageData();
            StageTime_Table (*p)[MAX_STAGE_NUM];
            p = m_pDataProcess->m_pTscInfo->tbStageTime+m_ucStageNoIndex;
            m_pStageTime = *p+index;
            //m_ucStageIdIndex = index;
            ui->stageLeId->setText(tr("阶段%1").arg(index+1));
            showStageData();
        }
        else
        {
            m_pStageTime = NULL;
        }
    }
}

void WStageWidget::on_btnReadStage()
{
    m_pDataProcess->requireTscTable(TSC_TABLE_STAGETIME);
}

void WStageWidget::on_btnAppStage()
{
    m_pDataProcess->sendStageTimeToLib();
}

void WStageWidget::on_rcvPhase()
{
    if(m_pDataProcess!=NULL)
    {
        m_pStage->changeNode(m_pDataProcess->m_ListLoadNo,m_pDataProcess->m_ListValid,m_pDataProcess->m_ListPhaseMap);
        m_pStage->setBack(m_pDataProcess->m_ucDir);
        if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            m_pStage->setOverlapConnect(m_pDataProcess->m_pTscInfo->tbOverlap);
            m_pStage->setConflictBase( m_pDataProcess->m_pTscInfo->tbPhaseConflict);
        }
    }
}

void WStageWidget::on_rcvStageTimeTable()
{
    ui->stageSbNo->setValue(1);
    on_stageSbNoChange(1);
}

void WStageWidget::on_rcvTimePatternTable()
{
    qDebug()<<"on_rcvTimePatternTable";
    ui->patternSbNo->setValue(1);
    on_patternSbNoChange(1);
}
