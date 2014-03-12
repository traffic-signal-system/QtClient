#include "wconflct.h"
#include "ui_wconflct.h"

WConflct::WConflct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WConflct)
{
    ui->setupUi(this);
    m_pWid = new WDirectionForm(ui->framePhase,true);
    m_pDataProcess = NULL;
    m_pConflict = NULL;
    m_bDataInit = false;
    connect(m_pWid,SIGNAL(leftClick(bool,quint8)),this,SLOT(on_leftClick(bool,quint8)));
    connect(m_pWid,SIGNAL(rightClick(bool,quint8)),this,SLOT(on_rightClick(bool,quint8)));
}

WConflct::~WConflct()
{
    delete ui;
}

void WConflct::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    connect(p,SIGNAL(rcvPhase()),this,SLOT(on_rcvPhase()));
    connect(p,SIGNAL(rcvConflict()),this,SLOT(on_rcvConflict()));
    connect(ui->btnApp,SIGNAL(clicked()),this,SLOT(on_btnApp()));
    connect(ui->btnRead,SIGNAL(clicked()),this,SLOT(on_btnRead()));
}

void WConflct::changeNode()
{
    if(m_pDataProcess!=NULL)
    {
        quint32 id = m_pDataProcess->m_uiCurNodeId;
        if(m_pDataProcess->m_mapVip.contains(id))
        {
            SVipData* data = m_pDataProcess->m_mapVip[id];
            m_pWid->changeStage();
            m_pWid->setIconPixmap(data->m_ListLoadNo);
            m_pWid->setFlagValid(data->m_ListValid);
            m_pWid->setPhaseId(data->m_ListPhaseMap);
            m_pWid->setBack(data->m_ucDir);

            setComPhaseList(data->m_ListPhaseMap);
            createCheckArray(m_listPhaseId);
        }
        if(m_pDataProcess->m_mapTsc.contains(id))
        {
            STscInfo* tsc = m_pDataProcess->m_mapTsc[id];
            setOverlapConnect(tsc->tbOverlap);
//            m_pStatus->setBack(m_pDataProcess->m_ucDir);
        }

        setChectArrayData();
    }
}

void WConflct::setOverlapConnect(Overlap_Table *p)
{
    for(int i=0;i<MAX_OVERLAP_NUM;i++)
    {
        quint8 cnt = (p+i)->bIncludedPhaseLen;
        if(cnt!=0)
        {
            QList<quint8> list;
            list.append((p+i)->bNo+MAXCOMPHASE);
            for(int j=0;j<INCLUDEPHASELEN;j++)
            {
                quint8 com = (p+i)->bIncludedPhase[j];
                if(com>0&&com<MAXCOMPHASE)
                {
                    list.append(com);
                }
            }
            m_pWid->setOverlapConnect(list);
        }
    }
}

void WConflct::setComPhaseList(QList<quint8> list)
{
    m_listPhaseId.clear();
    foreach(quint8 id,list)
    {
        if(id>0&&id<(MAX_PHASE_NUM+1))
        {
            m_listPhaseId.append(id);
        }
    }
    qSort(m_listPhaseId);
}

void WConflct::createCheckArray(QList<quint8> list)
{
    foreach(QLabel*lb,m_listLabel)
    {
        lb->close();
    }
    m_listLabel.clear();
    foreach(QLabel*lb,m_listLabel1)
    {
        lb->close();
    }
    m_listLabel1.clear();
    foreach(QCheckBox*cb,m_listCheck)
    {
        cb->close();
    }
    m_listCheck.clear();

    QLabel *lbSpace = new QLabel();
    lbSpace->setAttribute(Qt::WA_DeleteOnClose);
    m_listLabel.append(lbSpace);
    int cnt = list.count();
    for(int i=0;i<cnt;i++)
    {
        QLabel *lb = new QLabel(QString::number(list[i]));
        lb->setAttribute(Qt::WA_DeleteOnClose);
        QLabel *lb1 = new QLabel(QString::number(list[i]));
        lb1->setAttribute(Qt::WA_DeleteOnClose);
        m_listLabel.append(lb);
        m_listLabel1.append(lb1);;
        for(int j=0;j<cnt;j++)
        {
            QCheckBox *cb = new QCheckBox();
            if(i==j)
            {
                cb->setEnabled(false);
            }
//            cb->setVisible(false);
            cb->setAttribute(Qt::WA_DeleteOnClose);
            m_listCheck.append(cb);
            connect(cb,SIGNAL(clicked()),this,SLOT(on_checkBoxChange()));
        }
    }

    for(int row=0;row<(cnt+1);row++)
    {
        for(int col=0;col<(cnt+1);col++)
        {
            if(row==0)
            {
//                ui->gridLayout->addWidget(m_listLabel[col],row,col);
            }
            else if(col==0)
            {
//                ui->gridLayout->addWidget(m_listLabel1[row-1],row,col);
            }
            else
            {
//                ui->gridLayout->addWidget(m_listCheck[(row-1)*cnt+(col-1)],row,col);
            }
        }
    }
}

void WConflct::setChectArrayData()
{
//    m_bDataInit =false;
//    if(m_pDataProcess!=NULL)
//    {
//        if(m_pDataProcess->m_pTscInfo!=NULL)
//        {
//            PhaseConflict_Table *p = m_pDataProcess->m_pTscInfo->tbPhaseConflict;
//            int cnt = m_listPhaseId.count();
//            for(int i=0;i<MAX_CONFLICT_NUM;i++)
//            {
//                quint8 phaseId = i+1;
//                int rowIndex = m_listPhaseId.indexOf(phaseId);
//                if(rowIndex!=-1)
//                {
//                    quint16 conflict = (p+i)->uConflictPhase;
//                    for(int j=0;j<MAX_CONFLICT_NUM;j++)
//                    {
//                        quint8 colId = j+1;
//                        int colIndex = m_listPhaseId.indexOf(colId);
//                        if(colIndex!=-1)
//                        {
//                            int index = rowIndex*cnt+colIndex;
//                            if(index<m_listCheck.count())
//                            {

//                                if(((conflict>>j)&0x0001)==1)
//                                {
//                                    m_listCheck[index]->setChecked(true);
//                                }
//                                else
//                                {
//                                    m_listCheck[index]->setChecked(false);
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    m_bDataInit = true;
}

void WConflct::on_rcvPhase()
{
    changeNode();
}

void WConflct::on_rcvConflict()
{
     setChectArrayData();
}

void WConflct::on_leftClick(bool b, quint8 phase)
{
    if(b&&phase>0&&phase<(MAX_CONFLICT_NUM+1))
    {
        if(m_pDataProcess!=NULL)
        {
            if(m_pDataProcess->m_pTscInfo!=NULL)
            {
                m_pConflict = m_pDataProcess->m_pTscInfo->tbPhaseConflict+phase-1;
                m_pWid->setConflict(phase,m_pConflict->uConflictPhase);
            }
        }
    }
    else
    {
        m_pConflict = NULL;
    }
}

void WConflct::on_rightClick(bool b, quint8 phase)
{
    if(m_pConflict!=NULL&&phase>0&&phase<(MAX_CONFLICT_NUM+1))
    {

        quint16 conflict = 1;
        conflict<<=(phase-1);
        if(b)
        {
            m_pConflict->uConflictPhase += conflict;
            qDebug()<<tr("conflict %1").arg(conflict,16,2)<<b<<phase;
        }
        else
        {
            conflict = ~conflict;
            qDebug()<<tr("conflict %1").arg(conflict,16,2)<<b<<phase;
            m_pConflict->uConflictPhase &= conflict;
        }
        setChectArrayData();
    }
}

void WConflct::on_btnApp()
{
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->sendPhaseConflictTable();
    }
}

void WConflct::on_btnRead()
{
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->requireTscTable(TSC_TABLE_PHASECONFLICT);
    }
}

void WConflct::on_checkBoxChange()
{
    if(m_bDataInit&&m_pDataProcess!=NULL)
    {
        if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            PhaseConflict_Table* pBase = m_pDataProcess->m_pTscInfo->tbPhaseConflict;
            memset(pBase,0,sizeof(PhaseConflict_Table)*MAX_CONFLICT_NUM);
            int cnt = m_listPhaseId.count();
            quint8 greenId = 0;
            for(int i=0;i<cnt;i++)
            {
                quint8 phaseId = m_listPhaseId[i];
                if(phaseId>0&&phaseId<(MAX_CONFLICT_NUM+1))
                {
                    for(int j=0;j<cnt;j++)
                    {
                        int colId = m_listPhaseId[j];
                        if(colId>0&&colId<(MAX_CONFLICT_NUM+1))
                        {
                            quint16 temp = 1;
                            temp<<=(colId-1);
                            QCheckBox *cb = m_listCheck[i*cnt+j];
                            if(cb->hasFocus())
                            {
                                greenId = phaseId;
                            }
                            if(cb->isChecked())
                            {
                                (pBase+phaseId-1)->uConflictPhase |= temp;
                            }
                            else
                            {
                               quint16 num = ~temp;
                               (pBase+phaseId-1)->uConflictPhase &= num;
                            }
                        }
                    }
                }

            }
            if(greenId>0)
            {
                m_pWid->setConflictGreen(greenId);
            }
        }

    }
}
