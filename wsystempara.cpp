#include "wsystempara.h"
#include "ui_wsystempara.h"

WSystemPara::WSystemPara(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WSystemPara)
{
    ui->setupUi(this);
    ui->groupBox->setVisible(false);

    m_listCbSave.append(ui->cbModule);
    m_listCbSave.append(ui->cbPhase);
    m_listCbSave.append(ui->cbConflict);
    m_listCbSave.append(ui->cbParttern);
    m_listCbSave.append(ui->cbStage);
    m_listCbSave.append(ui->cbDet);
    m_listCbSave.append(ui->cbTimeBase);
    m_listCbSave.append(ui->cbSchedule);

    m_listCbRead.append(ui->cbModule_2);
    m_listCbRead.append(ui->cbPhase_2);
    m_listCbRead.append(ui->cbConflict_2);
    m_listCbRead.append(ui->cbParttern_2);
    m_listCbRead.append(ui->cbStage_2);
    m_listCbRead.append(ui->cbDet_2);
    m_listCbRead.append(ui->cbTimeBase_2);
    m_listCbRead.append(ui->cbSchedule_2);
    ui->groupBox_2->hide();
//    m_bFlag = false;
}

WSystemPara::~WSystemPara()
{
    delete ui;
}

void WSystemPara::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    ui->tbViewTscIp->setModel(m_pDataProcess->m_pModelTscIp);
    connect(ui->bcBtn,SIGNAL(clicked()),this,SLOT(on_bcBtnClick()));
    ui->combSave->setModel(m_pDataProcess->m_EventNameModel);
    ui->combRead->setModel(m_pDataProcess->m_EventNameModel);
    connect(ui->btnSave,SIGNAL(clicked()),this,SLOT(on_btnSave()));
    connect(ui->btnRead,SIGNAL(clicked()),this,SLOT(on_btnRead()));
}

void WSystemPara::addTableName(int index, QList<quint32> &list)
{
    switch(index)
    {
    case SAVE_INI_MODEL:
        list.append(TSC_TABLE_MODULE);
        break;
    case SAVE_INI_PHASE:
        list.append(TSC_TABLE_PHASE);
        list.append(TSC_TABLE_OVERLAP);
        list.append(TSC_TABLE_CHANNEL);
        list.append(TBL_TABLE_PHASE2DIREC);
        break;
    case SAVE_INI_CONFLICT:
        list.append(TSC_TABLE_PHASECONFLICT);
        break;
    case SAVE_INI_PATTERN:
        list.append(TSC_TABLE_TIMEPATTERN);
        break;
    case SAVE_INI_STAGE:
        list.append(TSC_TABLE_STAGETIME);
        break;
    case SAVE_INI_DET:
        list.append(TSC_TABLE_DETECTOR);
        break;
    case SAVE_INI_TIMEBASE:
        list.append(TSC_TABLE_TIMEBASE);
        break;
    case SAVE_INI_SCHEDULE:
        list.append(TSC_TABLE_SCHEDULE);
        break;
    default:
        break;
    }
}

void WSystemPara::timerEvent(QTimerEvent *e)
{
    this->killTimer(e->timerId());
    ui->btnRead->setEnabled(true);
    if(NULL!=m_pDataProcess)
    {
        m_pDataProcess->setFlagReadIni(false);
    }
}

void WSystemPara::on_bcBtnClick()
{
//    m_bFlag = !m_bFlag;
    m_pDataProcess->m_pModelTscIp->removeRows(0,m_pDataProcess->m_pModelTscIp->rowCount());
    m_pDataProcess->startBroadCast();
}

void WSystemPara::on_btnSave()
{
    int index = ui->combSave->currentIndex();
    if(0<=index&&NULL!=m_pDataProcess)
    {
        QList<quint32> listSave;
        int cntSave = m_listCbSave.count();
        for(int i=0;i<cntSave;i++)
        {
            if(m_listCbSave[i]->isChecked())
            {
                addTableName(i,listSave);
            }
        }
        m_pDataProcess->btnSaveDataIni(index,listSave);
    }
}

void WSystemPara::on_btnRead()
{
    int index = ui->combRead->currentIndex();
    if(0<=index&&NULL!=m_pDataProcess)
    {
        m_pDataProcess->setFlagReadIni(true);
        QList<quint32> listRead;
        int cntRead = m_listCbRead.count();
        for(int i=0;i<cntRead;i++)
        {
            if(m_listCbRead[i]->isChecked())
            {
                addTableName(i,listRead);
            }
        }
        m_pDataProcess->btnReadDataIni(index,listRead);
        this->startTimer(3000);//¿ªÆô¶¨Ê±Æ÷
        ui->btnRead->setEnabled(false);
    }
}
