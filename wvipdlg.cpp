#include "wvipdlg.h"
#include "ui_wvipdlg.h"
#include <qendian.h>
#include <QThread>


WVipDlg::WVipDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WVipDlg)
{
    QWidget *w = new QWidget();
    ui->setupUi(w);
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    vLayout->addStretch();
    vLayout->addWidget(w);
    vLayout->addStretch();
    hLayout->addStretch();
    hLayout->addLayout(vLayout);
    hLayout->addStretch();
//    m_pStage = new WPhaseStageWidget(this,0,0,0,0,390,false);
    m_pStage = new WStage(ui->frameStage);
    m_pStage->setUnClickAble();
    m_pStage->changePosition();
//    m_pStage->setClickable(false);
    //ui->layoutStage->addWidget(m_pStage);
    m_pContent = new VipNodeContent(ui->frameContent);
//    ui->layoutContent->addWidget(m_pContent);
    QPalette p = ui->groupBox->palette();
    p.setColor(QPalette::Background,QColor(128,64,0));
    ui->groupBox->setPalette(p);
    ui->cbNodeName->setEditable(true);
    m_pVip = NULL;
    ui->sbStage->setRange(1,16);
    ui->sbTimeOffset->setRange(0,65535);

    m_ucStageIndex = 0;
    m_pCurVipNode = NULL;
    m_pVipData = NULL;
    m_bFlagStartBtn = false;
    m_bStartCheckState = false;
    m_bDlgInit = false;

    ui->cbVipId->setEditable(true);
    ui->cbVipId->setEditable(true);
    for(int i=0;i<MAX_VIP_NUM;i++)
    {
        m_bListFlagManual.append(false);
    }

    connect(m_pStage,SIGNAL(changeStageIndex(quint8)),this,SLOT(on_iconSelect(quint8)));
    //------------------
//    ui->label_2->setVisible(false);
//    ui->label_3->setVisible(false);
//    ui->label_4->setVisible(false);
//    ui->cbVipEnable->setVisible(false);
//    ui->cbVipDir->setVisible(false);
//    ui->cbVipCtrl->setVisible(false);
    ui->rbDir1->setVisible(false);
    ui->rbDir2->setVisible(false);
    ui->readBtn->setVisible(false);
    ui->appBtn->setVisible(false);
}

WVipDlg::~WVipDlg()
{
    delete ui;
}

void WVipDlg::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    ui->cbVipId->setModel(p->m_pModelVipId);

    connect(ui->cbVipId,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipIdChange(int)));
    connect(ui->cbVipEnable,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipEnableChange(int)));
    connect(ui->cbVipDir,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipDirChange(int)));
    connect(ui->cbVipCtrl,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipCtrlChange(int)));
    connect(ui->edVipStart,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_edVipStartChange(QDateTime)));
    connect(ui->edVipEnd,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_edVipEndChange(QDateTime)));
    connect(p,SIGNAL(vipNodeListChange()),this,SLOT(on_vipNodeListChange()));
    connect(p,SIGNAL(vipItemChange(quint32,bool)),this,SLOT(on_vipItemChange(quint32,bool)));
    connect(m_pContent,SIGNAL(mouseSelect(VipNode*)),this,SLOT(on_mouseSelectNode(VipNode*)));
//    connect(ui->preBtn,SIGNAL(clicked()),this,SLOT(on_preBtn()));
//    connect(ui->nextBtn,SIGNAL(clicked()),this,SLOT(on_nextBtn()));
    connect(ui->readBtn,SIGNAL(clicked()),this,SLOT(on_readBtn()));
    connect(ui->appBtn,SIGNAL(clicked()),this,SLOT(on_appBtn()));
    connect(ui->sbStage,SIGNAL(valueChanged(int)),this,SLOT(on_sbStageChange(int)));
    connect(ui->sbTimeOffset,SIGNAL(valueChanged(int)),this,SLOT(on_sbTimeChange(int)));

    connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(on_startBtn()));
    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(on_addVipBtn()));
    connect(ui->btnDel,SIGNAL(clicked()),this,SLOT(on_delVipBtn()));
    connect(ui->btnRead,SIGNAL(clicked()),this,SLOT(on_readVipBtn()));
    connect(ui->btnApp,SIGNAL(clicked()),this,SLOT(on_appVipBtn()));
    connect(ui->cbVipStateCheck,SIGNAL(clicked(bool)),this,SLOT(on_cbVipStateCheck(bool)));
    connect(p,SIGNAL(vipNodeState(quint32,bool,quint8,bool)),this,SLOT(on_rcvVipNodeState(quint32,bool,quint8,bool)));

    connect(ui->cbVipEnable_2,SIGNAL(clicked(bool)),this,SLOT(on_cbVipEnable2(bool)));
//    connect(ui->rbDir1,SIGNAL(clicked()),this,SLOT(on_rbDirChange()));
//    connect(ui->rbDir2,SIGNAL(clicked()),this,SLOT(on_rbDirChange()));
    connect(ui->cbDir,SIGNAL(clicked(bool)),this,SLOT(on_cbDirChange(bool)));
    connect(ui->cbManual,SIGNAL(clicked(bool)),this,SLOT(on_cbManual(bool)));
    connect(p,SIGNAL(clickVipId(QString)),this,SLOT(on_treeViewClickVipId(QString)));

    connect(p,SIGNAL(vipIdModelChange()),this,SLOT(on_vipIdModelChange()));
}

void WVipDlg::getVipDataPoint()
{
    m_strCurVip = ui->cbVipId->currentText();
    quint8 id = 0;
    if(m_strCurVip.count()==4)
    {
        id = m_strCurVip.right(1).toInt();
    }
    else if(m_strCurVip.count()==5)
    {
        id = m_strCurVip.right(2).toInt();
    }
    if(id>0)
    {
        m_pVip = m_pDataProcess->m_pVipInfo->tbVipProperty+id-1;
    }
    else
    {
        m_pVip = NULL;
    }
}

void WVipDlg::setVipInterfaceData()
{
    if(m_pVip!=NULL)
    {
        m_bDlgInit = false;
        bool bEnable = false;
        quint8 id = m_pVip->ucVipLineId;
        if(m_pVip->ucValidity==0)
        {
            ui->cbVipEnable->setCurrentIndex(0);
            ui->cbVipEnable_2->setChecked(true);
            bEnable = true;
        }
        else
        {
            ui->cbVipEnable->setCurrentIndex(1);

            ui->cbVipEnable_2->setChecked(false);
            ui->startBtn->setEnabled(false);
        }
        if(m_pVip->ucDirection==0)
        {
            ui->cbVipDir->setCurrentIndex(0);
            ui->rbDir1->setChecked(true);
            ui->cbDir->setChecked(true);
        }
        else
        {
            ui->cbVipDir->setCurrentIndex(1);
            ui->rbDir2->setChecked(true);
            ui->cbDir->setChecked(false);
        }

        if(m_pVip->ucControl==0)
        {
            ui->cbVipCtrl->setCurrentIndex(0);
            ui->startBtn->setEnabled(false);
            qDebug()<<"ui->startBtn->setEnabled(false)";
            ui->cbManual->setChecked(false);
        }
        else
        {
            ui->cbVipCtrl->setCurrentIndex(1);
            if(bEnable)
            {
                m_bFlagStartBtn = m_bListFlagManual[id-1];
                if(m_bFlagStartBtn)
                {
                    ui->startBtn->setText(tr("结束Vip路线"));
                }
                else
                {
                    ui->startBtn->setText(tr("开始Vip路线"));
                }
                qDebug()<<"ui->startBtn->setEnabled(true)";
                ui->startBtn->setEnabled(true);
            }
            else
            {
                qDebug()<<"ui->startBtn->setEnabled(false)";
                ui->startBtn->setEnabled(false);
            }
            ui->cbManual->setChecked(true);
        }
        quint32 start = qFromBigEndian<quint32>(m_pVip->uiStartTime);
        quint32 end = qFromBigEndian<quint32>(m_pVip->uiEndTime);
        QDateTime time = QDateTime::fromTime_t(start);
        ui->edVipStart->setDateTime(time);
        time = QDateTime::fromTime_t(end);
        ui->edVipEnd->setDateTime(time);
        m_bDlgInit = true;
    }
}

void WVipDlg::getVipInterfaceData()
{
    if(m_pVip!=NULL)
    {
        QList<quint32> listId;
        QList<quint8> listStage;
        QList<quint16> listTime;
        m_pContent->getVipData(/*listId,listStage,listTime*/);
        listId = m_pContent->getIdList();
        listStage = m_pContent->getStageList();
        listTime = m_pContent->getTimeList();
        int cnt = listId.count();
        qDebug()<<"getvipinterfacedata node cnt"<<cnt;
        for(int i=0;i<MAX_VIP_NODE_COUNT;i++)
        {
            quint16 id = 0;
            quint8 stage = 0;
            quint16 time = 0;
            if(i<cnt)
            {

                quint16 idn = (quint16)(listId[i]);
                id = qToBigEndian<quint16>(idn);
                //quint8 stagen = listStage[i];
                stage = listStage[i];
                time = qToBigEndian<quint16>(listTime[i]);
                qDebug()<<"idn"<<idn;
            }
            m_pVip->usNodeIdList[i] = id;
            m_pVip->sStageIdList[i] = stage;
            m_pVip->usTimeDifList[i] = time;
        }
    }
}

//void WVipDlg::setGreenChannel()
//{
//    int cnt =  m_pVipData->listStage.count();
//    quint16 green = 0;
//    if(cnt>m_ucStageIndex-1)
//    {
//        green = qFromBigEndian<quint16>(m_pVipData->listStage[m_ucStageIndex-1]);
////        m_pStage->setListPoint(&m_pVipData->listChannelMap,&m_pVipData->listComMap,&m_pVipData->listOverlapMap);

//    }
////    m_pStage->setGreenChannel(green);

//}

//void WVipDlg::addStage(/*quint8 stageindex, quint16 greenchannel*/)
//{
//    int cnt = m_pVipData->listStage.count();
//    int width = 100;
//    if(cnt>5)
//    {
//        width = 500/cnt;
//    }
//    qDebug()<<"m_pVipData list stage cnt"<<cnt;
//    for(int i=0;i<cnt;i++)
//    {
////        WPhaseStageWidget *w = new WPhaseStageWidget(m_pDataProcess,qFromBigEndian<quint16>(m_pVipData->listStage[i]),width);
////        w->setListPoint(&m_pVipData->listChannelMap,&m_pVipData->listComMap,&m_pVipData->listOverlapMap);
////        w->setAttribute(Qt::WA_DeleteOnClose);
////        w->setCurIndex(i+1);
////        m_ListStage.insert(i,w);
////        ui->layoutStageContent->addWidget(w);
////        connect(w,SIGNAL(beClicked(WPhaseStageWidget*,quint8)),this,SLOT(setIconState(WPhaseStageWidget*,quint8)));
//    }
//}

//void WVipDlg::clearStageGroup()
//{
//    int cnt = m_ListStage.count();
//    for(int i=0;i<cnt;i++)
//    {
//        disconnect(m_ListStage[i]);
//        m_ListStage[i]->close();
//    }
//    m_ListStage.clear();
//}

void WVipDlg::showCurVip()
{
    int index = ui->cbVipId->currentIndex();
    if(index!=-1)
    {
        on_cbVipIdChange(index);
    }
}

//--------------slot---------
void WVipDlg::on_vipItemChange(quint32 id, bool b)
{
    if(b)
    {
        QString name;
        int index = m_pDataProcess->m_TscIdList.indexOf(QString::number(id));
        if(index!=-1)
        {
            name.append(m_pDataProcess->m_TscNameList[index]);
        }

        m_pContent->addIcon(id,name);
    }
    else
    {
        qDebug()<<"on_vipItemChange delect vip node"<<id;
        if(m_pCurVipNode!=NULL)
        {
            if(m_pCurVipNode->getNodeId()==id)
            {
                qDebug()<<"kkkkkkk";
                m_pStage->clearInterface();
                qDebug()<<"error";
            }
        }

        m_pContent->delIcon(id);
    }
}

void WVipDlg::on_cbVipIdChange(int index)
{
    if(index==-1)
        return;
//    clearStageGroup();
//    m_pDataProcess->setTreeSelect(index);
    if(m_pDataProcess->m_iTabWidgetIndex==3)
    {
        m_pDataProcess->setTreeSelect(index);
    }
    m_pStage->clearInterface();
    if(m_pDataProcess->m_bFlagVipInit||m_strCurVip.isEmpty())
    {
        qDebug()<<"vipid change";
        getVipDataPoint();
        setVipInterfaceData();
        QString str = ui->cbVipId->currentText();
        int cnt = str.count();
        quint8 id = 0;
        if(cnt=4)
        {
            id = str.right(1).toInt();
        }
        else if(cnt==5)
        {
            id = str.right(2).toInt();
        }
        m_pDataProcess->cbVipIdChange(id);
        m_pCurVipNode = NULL;
        m_pVipData = NULL;
    }
    else
    {
        ui->cbVipId->setEditText(m_strCurVip);
//        int curIndex = ui->cbVipId->findText(m_strCurVip);
//        qDebug()<<"str empty and vipinit false"<<curIndex<<m_strCurVip<<"cnt:"<<ui->cbVipId->count();
//        if(curIndex!=-1)
//        {
//            ui->cbVipId->setCurrentIndex(curIndex);
//        }
//        else if(ui->cbVipId->count()>0)
//        {
//            m_strCurVip.clear();
//            ui->cbVipId->setCurrentIndex(0);
//        }
    }

}

//只有原先是有效的 换成手动时才能显示按钮，若是无效 需先发送vip属性
void WVipDlg::on_cbVipEnableChange(int index)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
        //int index = ui->cbVipEnable->currentIndex();
        m_pVip->ucValidity = index;

        if(m_pVip->ucControl!=0&&index==0)
        {qDebug()<<"startBtn show";
//            ui->startBtn->setVisible(true);
        }
        else
        {
//            ui->startBtn->setVisible(false);
        }
    }
}

void WVipDlg::on_cbVipEnable2(bool b)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
        m_pVip->ucValidity = b?0:1;
        ui->cbVipEnable->setCurrentIndex(b?0:1);
        on_appVipBtn();
    }
}

void WVipDlg::on_cbVipDirChange(int index)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
        m_pVip->ucDirection = index;
    }
}

void WVipDlg::on_cbDirChange(bool b)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
        m_pVip->ucDirection = b?0:1;
        ui->cbVipDir->setCurrentIndex(b?0:1);
        on_appVipBtn();
    }
}

void WVipDlg::on_cbVipCtrlChange(int index)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
        m_pVip->ucControl = index;
    }
}

void WVipDlg::on_cbManual(bool b)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
        m_pVip->ucControl = b?1:0;
        ui->cbVipCtrl->setCurrentIndex(b?1:0);
        on_appVipBtn();
    }
}

void WVipDlg::on_edVipStartChange(QDateTime t)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
       m_pVip->uiStartTime = qToBigEndian<quint32>(t.toTime_t());
    }
}

void WVipDlg::on_edVipEndChange(QDateTime t)
{
    if(m_pVip!=NULL&&m_bDlgInit)
    {
       m_pVip->uiEndTime = qToBigEndian<quint32>(t.toTime_t());
    }
}

void WVipDlg::on_startBtn()
{
    m_bFlagStartBtn = !m_bFlagStartBtn;
    quint8 vipId = m_pDataProcess->m_ucCurVipId;
    if(m_bFlagStartBtn)
    {
       ui->startBtn->setText(tr("结束Vip路线"));
       ui->startBtn->setDown(true);
       m_pDataProcess->sendVipCmd(VIP_START);
       if(vipId>0)
         m_bListFlagManual[vipId-1] = true;
    }
    else
    {
        ui->startBtn->setText(tr("开始Vip路线"));
        ui->startBtn->setDown(false);
        m_pDataProcess->sendVipCmd(VIP_STOP);
        if(vipId>0)
            m_bListFlagManual[vipId-1] = false;
    }
}

void WVipDlg::on_addVipBtn()
{
    quint8 vipId = m_pDataProcess->getVipId();
    if(vipId!=0)
    {
        m_pVip = m_pDataProcess->m_pVipInfo->tbVipProperty+vipId-1;
        ui->cbVipId->setEditText(tr("Vip%1").arg(vipId));
        ui->cbVipCtrl->setCurrentIndex(0);
        ui->cbVipDir->setCurrentIndex(0);
        ui->cbVipEnable->setCurrentIndex(0);
        QDateTime d = QDateTime::currentDateTime();
        ui->edVipStart->setDateTime(d);
        ui->edVipEnd->setDateTime(d);
        m_pContent->clearNode();
        m_pStage->clearInterface();

    }
    else
    {
        m_pVip = NULL;
    }
}

void WVipDlg::on_delVipBtn()
{
    getVipDataPoint();
    if(m_pVip!=NULL)
    {
        int tbSize = sizeof(VipProperty_Table);
        memset(m_pVip,0,tbSize);
        m_strCurVip.clear();
        int index = ui->cbVipId->currentIndex();
        if(index>-1)
        {
            m_pDataProcess->m_pModelVipId->removeRow(index);
        }
//        m_pDataProcess->sendVipInfoToLib();
    }
}

void WVipDlg::on_readVipBtn()
{
    m_pDataProcess->requireVipInfoTable();
}

void WVipDlg::on_appVipBtn()
{
    on_appBtn();
//    m_pDataProcess->sendVipInfoToLib();
}


//--------------------------------
void WVipDlg::on_vipNodeListChange()
{
    m_pContent->clearNode();
    int cnt = m_pDataProcess->m_ListVipNodeId.count();
    qDebug()<<"vip list node cnt"<<cnt;
    ui->cbNodeName->clear();
    //ui->cbNodeName->addItems(*m_pDataProcess->m_ListVipNodeId);
    for(int i=0;i<cnt;i++)
    {

        VipNode* node = new VipNode;
        quint32 id = m_pDataProcess->m_ListVipNodeId[i];
        QString name;
        int index = m_pDataProcess->m_TscIdList.indexOf(QString::number(id));
        if(index!=-1)
        {
            name.append(m_pDataProcess->m_TscNameList[index]);
        }
        qDebug()<<"vip addicon name"<<id<<name;
        node->setNodeId(id,name);
        node->setStageIndex(m_pDataProcess->m_ListVipNodeStage[i]);
        node->setTimeOffset(m_pDataProcess->m_ListVipNodeTime[i]);
        m_pContent->addIcon(node);
    }
}

void WVipDlg::on_mouseSelectNode(VipNode *node)
{
    m_pCurVipNode = node;
    quint32 id = node->getNodeId();
    quint8 stage = node->getStageIndex();
    if(stage==0)
    {
        stage = 1;
    }
    quint16 offset = node->getTimeOffset();
    if(m_pDataProcess->m_mapVip.contains(id))
    {
        SVipData *vipData = m_pDataProcess->m_mapVip[id];
        m_pVipData = vipData;

//        clearStageGroup();
//        addStage();
        m_pStage->changeNode(vipData->m_ListLoadNo,vipData->m_ListValid,vipData->m_ListPhaseMap);
        m_pStage->setUnClickAble();
        m_pStage->setChannelMap(vipData->m_ListLoadMap);
         m_pStage->setBack(vipData->m_ucDir);
        if(m_pDataProcess->m_mapTsc.contains(id))
        {
            STscInfo* tsc = m_pDataProcess->m_mapTsc[id];
            m_pStage->setOverlapConnect(tsc->tbOverlap);
            StageTime_Table (*p)[MAX_STAGE_NUM];
            p = tsc->tbStageTime;
            m_pStage->setStageBase(*p+0);
//            on_iconSelect(stage-1);
//            m_pStage->setIconDark(stage-1);
            m_pStage->setMouseClick(stage-1);
//            m_pStatus->setBack(m_pDataProcess->m_ucDir);
        }
        int cnt = vipData->listStage.count();
        qDebug()<<"stage cnt"<<cnt;
        if(cnt>0)
        {
            if(stage<cnt+1)
            {

            }
            else
            {
                stage = 1;
            }

            m_ucStageIndex = stage;
//            setIconState(m_ListStage[m_ucStageIndex-1],m_ucStageIndex);
 //           setGreenChannel();
//            quint16 green = vipData->listStage[stage-1];
//            m_pStage->setListPoint(&vipData->listChannelMap,&vipData->listComMap,&vipData->listOverlapMap);
//            m_pStage->setGreenChannel(green);
        }

    }
    int index = m_pDataProcess->m_TscIdList.indexOf(QString::number(id));
    if(index!=-1)
    {
        QString nodeName = m_pDataProcess->m_TscNameList[index];
        ui->cbNodeName->setEditText(nodeName);
        ui->sbStage->setValue(stage);
        ui->sbTimeOffset->setValue(offset);
    }
}

//void WVipDlg::on_preBtn()
//{
//    if(m_pCurVipNode==NULL)
//        return;

//    int cnt = m_pVipData->listStage.count();
//    qDebug()<<"stage cnt"<<cnt;
//    if(m_ucStageIndex>1)
//    {
//        m_ucStageIndex--;
//    }
//    else
//    {
//        if(cnt>1)
//        {
//            m_ucStageIndex = cnt;
//        }
//        else if(cnt==1)
//        {
//            m_ucStageIndex = 1;
//        }
//    }
//    setIconState(m_ListStage[m_ucStageIndex-1],m_ucStageIndex);
////    m_pCurVipNode->setStageIndex(m_ucStageIndex);
////    ui->sbStage->setValue(m_ucStageIndex);
////    setGreenChannel();
//}

//void WVipDlg::on_nextBtn()
//{
//    if(m_pCurVipNode==NULL)
//        return;
//    int cnt = m_pVipData->listStage.count();
//    if(m_ucStageIndex<cnt)
//    {
//        m_ucStageIndex++;
//    }
//    else
//    {

//        if(m_ucStageIndex==cnt)
//        {
//            m_ucStageIndex = 1;
//        }
//    }
//    setIconState(m_ListStage[m_ucStageIndex-1],m_ucStageIndex);
////    m_pCurVipNode->setStageIndex(m_ucStageIndex);
////    ui->sbStage->setValue(m_ucStageIndex);
////    setGreenChannel();
//}

void WVipDlg::on_readBtn()
{
    m_pDataProcess->requireVipInfoTable();
}

void WVipDlg::on_appBtn()
{
    getVipInterfaceData();
    m_pDataProcess->sendVipInfoToLib();
}

void WVipDlg::on_sbStageChange(int stage)
{
    if(m_pCurVipNode!=NULL&&stage>0)
    {
        m_pCurVipNode->setStageIndex(stage);
        m_pStage->setMouseClick(stage-1);
    }
}

void WVipDlg::on_sbTimeChange(int offset)
{
    if(m_pCurVipNode!=NULL)
    {
        m_pCurVipNode->setTimeOffset(offset);
    }
}

//void WVipDlg::setIconState(WPhaseStageWidget *p, quint8 stageindex)
//{
//    int cnt = m_ListStage.count();
//    for(int i=0;i<cnt;i++)
//    {
//        if(p==m_ListStage[i])
//        {
//            m_ListStage[i]->setIconDark(false);
//        }
//        else
//        {
//            m_ListStage[i]->setIconDark(true);
//        }
//    }
//    m_ucStageIndex = stageindex;
//    m_pCurVipNode->setStageIndex(m_ucStageIndex);
//    ui->sbStage->setValue(m_ucStageIndex);
//    setGreenChannel();
//}

void WVipDlg::on_iconSelect(quint8 index)
{
    m_ucStageIndex = index+1;
    m_pCurVipNode->setStageIndex(m_ucStageIndex);
    ui->sbStage->setValue(m_ucStageIndex);
}

void WVipDlg::on_cbVipStateCheck(bool b)
{
    qDebug()<<"on_cbVipStateCheck"<<b;
    m_bStartCheckState = b;
    if(b)
    {
        on_rcvVipNodeState();
    }
    else
    {
        m_pContent->getVipData();
        QList<quint32> list = m_pContent->getIdList();
        foreach(quint32 id,list)
        {
            m_pDataProcess->requireAutoReport(0xf8,0,id);
        }

        m_pDataProcess->m_bFlagVipStateCheck = false;
    }

}

void WVipDlg::on_rcvVipNodeState(quint32 id, bool bManual, quint8 stageId,bool bVipShow)
{
    if(bVipShow)
    {
        m_pContent->getVipData();
        QList<quint32> list = m_pContent->getIdList();
        QList<quint8> listStageIndex = m_pContent->getStageList();
        int index = 0;
        bool bGreen = false;
        if(list.contains(id))
        {
            index = list.indexOf(id);
            if(bManual&&stageId==listStageIndex[index])
            {
                bGreen = true;
            }
            m_pContent->setVipNodeGreen(id,bGreen,stageId);
        }
        else
        {
            foreach(quint32 nodeId,list)
            {
                m_pDataProcess->requireAutoReport(0xf8,10,nodeId);

            }
            m_pDataProcess->m_bFlagVipStateCheck = true;
        }

//        qDebug()<<"list.contains(id)"<<list.contains(id)<<"index"<<index<<id;
//        if(index<(list.count()-1))
//        {
//            index++;
//        }
//        else
//        {
//            //index = 0;
//            return;
//        }
//        if(list.count()>index&&m_bStartCheckState)
//        {
//            qDebug()<<"requireAutoReport--------------------------------------20----------"<<list[index]<<"index"<<index<<list;
//            m_pDataProcess->requireAutoReport(0xf8,10,list[index]);
//            m_pDataProcess->m_bFlagVipStateCheck = true;
//        }
    }
    else
    {
        ui->cbVipStateCheck->setChecked(false);
        on_cbVipStateCheck(false);
    }

}

void WVipDlg::on_treeViewClickVipId(QString str)
{
    int index = ui->cbVipId->findText(str);
    if(index==ui->cbVipId->currentIndex())
    {
        on_cbVipIdChange(index);
    }
    else if(index!=-1)
    {
        ui->cbVipId->setCurrentIndex(index);
    }
}

void WVipDlg::on_vipIdModelChange()
{
    QString str = ui->cbVipId->currentText();
    qDebug()<<"on_vipIdModelChange"<<str<<"m_strCurVip"<<m_strCurVip;
    if(str.compare(m_strCurVip)==0)
    {
        qDebug()<<"on_vipIdModelChange true";
        on_cbVipIdChange(0);//0并不代表 是第一 个，又重新 取得 vipid
    }
    else
    {
        qDebug()<<"on_vipIdModelChange false";
    }
}
