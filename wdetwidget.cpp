#include "wdetwidget.h"
#include "ui_detector.h"

WDetWidget::WDetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WDetWidget)
{
    m_ucDetBase = 1;
    QWidget *w = new QWidget();
    ui->setupUi(w);
    //w->setFixedSize(770,700);
    m_DetDlg = new DetWidget(ui->dlgFram,ui->groupBox);
    //ui->gLoadLayout->addWidget(m_DetDlg);
    ui->vFlowLayout->setSpacing(0);
    for(int i=0;i<4;i++)
    {
        FlowWidget *flow = new FlowWidget;
        flow->setDetNo(m_ucDetBase+i);
        m_ListFlow<<flow;
        ui->vFlowLayout->addWidget(flow);
    }
    ui->vFlowLayout->addSpacing(2);
    m_DetDlg->setFlowList(m_ListFlow);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addStretch();
    vLayout->addWidget(w);
    vLayout->addStretch();
    //this->setLayout(vLayout);
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addStretch();
    hLayout->addLayout(vLayout);
    hLayout->addStretch();
    //w->resize(620,690);
    connect(ui->detStatus,SIGNAL(clicked()),this,SLOT(on_statusCheck()));
    connect(ui->readBtn,SIGNAL(clicked()),this,SLOT(on_readBtn()));
    connect(ui->appBtn,SIGNAL(clicked()),this,SLOT(on_appBtn()));
    connect(ui->upBtn,SIGNAL(clicked()),this,SLOT(on_upBtn()));
    connect(ui->downBtn,SIGNAL(clicked()),this,SLOT(on_downBtn()));
    connect(ui->flashBtn,SIGNAL(clicked()),this,SLOT(on_flashBtn()));

    ui->groupBox_2->hide();
    ui->dlgFram->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->sbTime->hide();
    ui->flashBtn->hide();
    ui->upBtn->hide();
    ui->downBtn->hide();
}

WDetWidget::~WDetWidget()
{
    if(ui->detStatus->isChecked())
    {
        ui->detStatus->click();
    }
    delete ui;
}

void WDetWidget::setDataProcess(PDataProcess *p)
{
    m_DetDlg->setDataProcess(p);
    m_pDataProcess = p;
    connect(m_DetDlg,SIGNAL(stopDetStatus()),this,SLOT(on_stopDetStatus(bool)));
    connect(p,SIGNAL(cbDetAutoReport(bool)),ui->detStatus,SLOT(setChecked(bool)));
    connect(p,SIGNAL(cbDetStatus(bool)),this,SLOT(on_stopDetStatus(bool)));
}

//----------------------------------------------
void WDetWidget::on_statusCheck()
{qDebug()<<"on_statusCheck";
    if(ui->detStatus->isChecked())
    {
        quint8 time = ui->sbTime->value();
        m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORSTS,time);
    }
    else
    {
        m_pDataProcess->requireAutoReport(TSC_STATUS_DETECTORSTS,0);
    }
    m_pDataProcess-> m_bFlagDetAutoReport = ui->detStatus->isChecked();
}

void WDetWidget::on_readBtn()
{
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->m_bFlagDetRead = true;
        m_pDataProcess->requireTscTable(TBL_TABLE_PHASE2DIREC);
    }
//    m_pDataProcess->requireTscTable(TSC_TABLE_DETECTOR);
}

void WDetWidget::on_appBtn()
{
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->m_bFlagDetSend = true;
        m_pDataProcess->sendPhaseMapToLib();
    }
//    m_pDataProcess->sendDetectorToLib();
}

void WDetWidget::on_upBtn()
{
    if(m_ucDetBase>4)
    {
        m_ucDetBase-=4;
        for(int i=0;i<4;i++)
        {
            m_ListFlow[i]->setDetNo(m_ucDetBase+i);
            m_ListFlow[i]->clearData();
        }
    }
}

void WDetWidget::on_downBtn()
{
    if(m_ucDetBase<MAX_DETECTORNUM-4-1)//25
    {
        m_ucDetBase+=4;
        for(int i=0;i<4;i++)
        {
            m_ListFlow[i]->setDetNo(m_ucDetBase+i);
            m_ListFlow[i]->clearData();
        }
    }
}

void WDetWidget::on_flashBtn()
{
    for(int i=0;i<4;i++)
    {
        m_ListFlow[i]->clearData();
    }
}

void WDetWidget::on_stopDetStatus(bool b)
{
    if(ui->detStatus->isChecked())
    {
        ui->detStatus->click();
    }
    if(!b)
    {
        on_flashBtn();
    }
}
