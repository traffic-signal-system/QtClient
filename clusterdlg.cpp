#include "clusterdlg.h"
#include "ui_clusterdlg.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>

WClusterDlg::WClusterDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusterDlg)
{
    QWidget *w = new QWidget();
    ui->setupUi(w);
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    hLayout->addStretch();
    hLayout->addWidget(w);
    hLayout->addStretch();

    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();
    this->setAutoFillBackground(true);
    ui->sbPatternNo->setPrefix(tr("群方案"));
    ui->sbPatternNo->setRange(1,16);
    ui->sbStagePattern->setPrefix(tr("配时"));
    ui->sbStagePattern->setRange(0,16);
    ui->sbCtCircle->setRange(0,255);
    ui->sbPatternOffset->setPrefix(tr("节点:"));
    ui->sbPatternOffset->setRange(1,16);

    ui->leNodeName->setToolTip(tr("节点名"));
    ui->leNodeName->setReadOnly(true);
    ui->lePatternOffset->setToolTip(tr("相位差"));
    ui->lePatternCoor->setToolTip(tr("协调相位差"));

    m_pNodeContent = new CtNodeContent();
    ui->ctLayout->addWidget(m_pNodeContent);

//    QPalette p = ui->groupBox->palette();
//    p.setColor(QPalette::Background,QColor(128,64,0));
//    ui->groupBox->setPalette(p);
   // ui->groupBox->setBackgroundRole();

//    m_pModelCtNodeName = new QStringListModel();
//    ui->cbNodeName->setModel(m_pModelCtNodeName);
    m_bClusterMoreBtn = false;
    m_ucKeyIndex = 0;
    m_ucKeyOffset = 0;

    m_pCtPattern = NULL;

    ui->clusterMoreGroup->hide();
    m_bNodeMoreBtn = false;
    ui->nodeMoreGroup->hide();

//    ui->label->hide();
    ui->label_8->hide();
//    ui->leCtId->hide();
    ui->leNodeId->hide();
    ui->leCtId->setReadOnly(true);

    ui->cbCtName->setAutoCompletion(false);

    ui->cbCtName->setEditable(true);
    ui->cbCtDomain->setEditable(true);
    ui->cbCtCtrlMode->setEditable(true);
    connect(ui->leftBtn,SIGNAL(clicked()),this,SLOT(on_leftBtn()));
    connect(ui->rightBtn,SIGNAL(clicked()),this,SLOT(on_rightBtn()));
    connect(ui->ctMoreBtn,SIGNAL(clicked()),this,SLOT(on_clusterMoreBtn()));
    connect(ui->nodeMoreBtn,SIGNAL(clicked()),this,SLOT(on_nodeMoreBtn()));
    connect(ui->cbCtName,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbCtNameChange(int)));
    connect(ui->cbNodeName,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbCtNodeNameChange(int)));
    connect(m_pNodeContent,SIGNAL(offsetChange(quint32)),this,SLOT(on_offsetChange(quint32)));
    connect(ui->leftOneBtn,SIGNAL(clicked()),this,SLOT(on_leftOneBtn()));
    connect(ui->rightOneBtn,SIGNAL(clicked()),this,SLOT(on_rightOneBtn()));

    ui->label_5->setVisible(false);
    ui->cbCtCtrlMode->setVisible(false);
    m_bDlgInit = false;

    ui->btnApp->setVisible(false);
    ui->btnRead->setVisible(false);
    ui->btnAppPattern->setVisible(false);
    ui->btnReadPattern->setVisible(false);
    m_iCurCtIndex = -1;
    ui->horizontalLayout_19->insertStretch(0);
    ui->horizontalLayout_4->insertStretch(0);
}

WClusterDlg::~WClusterDlg()
{
    delete ui;
}

void WClusterDlg::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    ui->cbCtName->setModel(p->m_pModelCTName);
    ui->cbNodeName->setModel(p->m_pModelCTNodeName);
    //ui->cbTimePattern->setModel(p);
    connect(p,SIGNAL(getCtCircle()),this,SLOT(on_getCtCircle()));
    //connect(p,SIGNAL(getCtNodeStage(unsigned int/*,QList<quint8>*/)),this,SLOT(on_getCtNodeStage(unsigned int/*,QList<quint8>*/)));
    connect(p,SIGNAL(getCtNodeStage(quint8)),this,SLOT(on_getCtNodeStage(quint8)));
    connect(ui->appBtn,SIGNAL(clicked()),this,SLOT(on_appBtn()));
    connect(ui->readBtn,SIGNAL(clicked()),this,SLOT(on_readBtn()));
    connect(p,SIGNAL(clickTreeView(QModelIndex)),this,SLOT(on_treeViewClick(QModelIndex)));
    connect(ui->cbCheck,SIGNAL(clicked()),this,SLOT(on_cbCheck()));

    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(on_addCTBtn()));
    connect(ui->btnDel,SIGNAL(clicked()),this,SLOT(on_delCTBtn()));
    connect(ui->btnRead,SIGNAL(clicked()),this,SLOT(on_readCTBtn()));
    connect(ui->btnApp,SIGNAL(clicked()),this,SLOT(on_appCTBtn()));


    ui->cbCtDomain->addItems(p->m_ListCTDomainId);
    //connect(cbClusterName,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ctNameChange(int)));
    connect(ui->cbCtName,SIGNAL(editTextChanged(QString)),this,SLOT(on_ctNameChange(QString)));
    connect(ui->cbCtDomain,SIGNAL(editTextChanged(QString)),this,SLOT(on_ctDomainIdChange(QString)));
    connect(ui->cbCtEnable,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ctEnableChange(int)));
    connect(ui->sbNodeDif,SIGNAL(valueChanged(int)),this,SLOT(on_sbNodeDifChange(int)));

    connect(ui->sbPatternNo,SIGNAL(valueChanged(int)),this,SLOT(on_ctPatternNoChange(int)));
    connect(ui->sbCtCircle,SIGNAL(valueChanged(int)),this,SLOT(on_ctPatternCircle(int)));
    connect(ui->sbStagePattern,SIGNAL(valueChanged(int)),this,SLOT(on_ctPatternStagePattern(int)));
    connect(ui->btnAppPattern,SIGNAL(clicked()),this,SLOT(on_ctPatternAppBtn()));
    connect(ui->btnDelPattern,SIGNAL(clicked()),this,SLOT(on_ctPatternDelBtn()));
    connect(ui->btnReadPattern,SIGNAL(clicked()),this,SLOT(on_ctPatternReadBtn()));
    connect(ui->sbPatternOffset,SIGNAL(valueChanged(int)),this,SLOT(on_ctPatternSbOffsetChange(int)));
    connect(ui->lePatternOffset,SIGNAL(textChanged(QString)),this,SLOT(on_ctPatternLeOffset(QString)));
    connect(ui->lePatternCoor,SIGNAL(textChanged(QString)),this,SLOT(on_ctPatternLeCoor(QString)));
    connect(p,SIGNAL(rcvCtPattern()),this,SLOT(on_rcvCtPattern()));
    connect(p,SIGNAL(ctNameModelChange()),this,SLOT(on_ctNameModelChange()));
}

void WClusterDlg::showCtPatternData()
{
    if(m_pCtPattern==NULL)
    {
        return;
    }
    m_bDlgInit = false;
    ui->sbCtCircle->setValue(m_pCtPattern->ucCycleTime);
    ui->sbStagePattern->setValue(m_pCtPattern->ucStagePatternId);

    int index = ui->sbPatternOffset->value();
    if(index==1)
    {
        on_ctPatternSbOffsetChange(1);
    }
    else
    {
        ui->sbPatternOffset->setValue(1);
    }
//    ui->cbCtCtrlMode
    m_bDlgInit = true;
}

void WClusterDlg::clearCtPatternData()
{m_bDlgInit = false;
    ui->sbCtCircle->clear();
    ui->sbStagePattern->clear();
    ui->leNodeName->clear();
    ui->lePatternOffset->clear();
    ui->lePatternCoor->clear();
    m_bDlgInit = true;
}

//------------slot----------
void WClusterDlg::on_leftBtn()
{
    m_pNodeContent->moveLeftRight(1);
}

void WClusterDlg::on_rightBtn()
{
    m_pNodeContent->moveLeftRight(-1);
}

void WClusterDlg::on_leftOneBtn()
{
    m_pNodeContent->moveLeftRight(1,1);
}

void WClusterDlg::on_rightOneBtn()
{
    m_pNodeContent->moveLeftRight(-1,1);
}

void WClusterDlg::on_clusterMoreBtn()
{
    m_bClusterMoreBtn = !m_bClusterMoreBtn;
    if(m_bClusterMoreBtn)
    {
        ui->ctMoreBtn->setText(tr("<<隐藏"));
        ui->clusterMoreGroup->show();
    }
    else
    {
        ui->ctMoreBtn->setText(tr("更多>>"));
        ui->clusterMoreGroup->hide();
    }
}

void WClusterDlg::on_nodeMoreBtn()
{
    m_bNodeMoreBtn = !m_bNodeMoreBtn;
    if(m_bNodeMoreBtn)
    {
        ui->nodeMoreBtn->setText(tr("<<隐藏"));
        ui->nodeMoreGroup->show();
    }
    else
    {
        ui->nodeMoreBtn->setText(tr("更多>>"));
        ui->nodeMoreGroup->hide();
    }
}

void WClusterDlg::on_cbCtNameChange(int index)
{qDebug()<<"ct current change"<<index;
    if(index!=-1)
    {
        m_iCurCtIndex = index;
    }
    if(m_pDataProcess->m_iTabWidgetIndex==2)
    {
        m_pDataProcess->setTreeSelect(index);
    }
    m_pNodeContent->clearCtNodeList();
    int nameIndex = m_pDataProcess->m_ListCTName.indexOf(ui->cbCtName->currentText());
    if(index<0||nameIndex<0)// -1
    {
        ui->leCtId->clear();
        m_pCtPattern = NULL;
        return;
    }
    m_bDlgInit = false;
    m_pNodeContent->setFlagDragMove();
    QString strId = m_pDataProcess->m_ListCTId[index];
    ui->leCtId->setText(strId);
    m_pDataProcess->m_ucCurClusterId = strId.toInt();
    QString strDomain = m_pDataProcess->m_ListCTDomainId[index];
    ui->cbCtDomain->setEditText(strDomain);
    QString strEnable = m_pDataProcess->m_ListCTEnable[index];
    ui->cbCtEnable->setCurrentIndex(strEnable.toInt());
    m_bDlgInit = true;
    if(index==0)
    {
        clearCtPatternData();
        return;
    }
    m_pNodeContent->clearCtNodeList();
//已经改变    -------为获取周期，先得到时基表里的时段号，再得到时段表里的事件号，得到周期和方案号，在各个节点得到阶段配时号（可以不同）
    quint8 ctId = m_pDataProcess->m_ListCTId[index].toInt();
     m_pDataProcess->m_ucCurClusterId = ctId;
     if(m_pDataProcess->m_mapCluster.contains(ctId))
     {
         m_pDataProcess->m_pClusterInfo = m_pDataProcess->m_mapCluster[ctId];
         m_pDataProcess->getClusterCircle();
     }
     else
     {
         qDebug()<<"m_mapCluster not contain ctId"<<ctId;
         m_pCtPattern = NULL;
         return;
     }
//    m_pDataProcess->m_bFlagReadCluster = true;
     if(ctId>1)
     {
          m_pDataProcess->getCTNodeId(ctId);
          m_ListCtNodeName.clear();
          m_ListCtNodeName.append(m_pDataProcess->m_ListCTNodeName);
     }
    quint8 patternId = ui->sbPatternNo->value();
    if(patternId==1)
    {
        on_ctPatternNoChange(1);
    }
    else
    {
        ui->sbPatternNo->setValue(1);
    }
}

void WClusterDlg::on_getCtCircle()
{/*
//    qDebug()<<"on_getCtCircle";
//    quint8 circle = m_pDataProcess->m_pClusterInfo->iCircle;
//    quint8 ctrlMode = m_pDataProcess->m_pClusterInfo->iControlType;
   // ui->sbCtCircle->setValue(circle);
    //m_pNodeContent->clearCtNodeList();
    m_pNodeContent->setCtCircle(circle);
    //ui->cbCtCtrlMode->setEditText(QString::number(ctrlMode));

    m_ListCtNodeId.clear();
    m_ListCtNodeName.clear();
    m_ListCtNodeIndex.clear();

    m_ListCtNodeId.append(m_pDataProcess->m_ListCTNodeId);
    m_ListCtNodeName.append(m_pDataProcess->m_ListCTNodeName);
    m_ListCtNodeIndex.append(m_pDataProcess->m_ListCTNodeIndex);

//    m_pDataProcess->m_ListCTNodeStagePattern.clear();
    m_pDataProcess->getCTNodeOffset(m_pDataProcess->m_ucCurClusterId);
    int nodeCnt = m_ListCtNodeId.count();
    for(int i=0;i<nodeCnt;i++)
    {
        quint8 nodeId = m_ListCtNodeId[i].toInt();
        m_pDataProcess->getCTNodeStageList(nodeId);
    }*/
}

void WClusterDlg::on_getCtNodeStage(quint8 ctNodeId)
{
    int index = m_ListCtNodeId.indexOf(QString::number(ctNodeId));
    if(index!=-1&&m_pCtPattern!=NULL)
    {
        QString strName = m_ListCtNodeName[index];
        //quint8 offset = m_pDataProcess->m_ListCTNodeOffset[index];
        quint8 offset = m_pCtPattern->sOffsetList[index];
        qDebug()<<"on_getCtNodeStage:offset"<<offset<<"index"<<index<<strName;
        quint8 posIndex = m_ListCtNodeIndex[index];
        if((posIndex&0x80)!=0)
        {
            quint8 kIndex = m_pNodeContent->getCurNodeListCount();//新增加的节点 index为 count
            m_pNodeContent->setKeyData(kIndex,offset);
        }
        qDebug()<<"on_getCtNodeStage:offset"<<offset;
        CtNode *node = new CtNode(m_pNodeContent);
        connect(node,SIGNAL(mouseSelect(quint32)),this,SLOT(on_mouseSelectCtNode(quint32)));
        //connect(node,SIGNAL(offsetChange(quint32,quint8)),this,SLOT(on_offsetChange(quint32,quint8)));
        node->setCtCircle(m_pCtPattern->ucCycleTime);
        node->setCtNodeId(ctNodeId);
        node->setCtNodeText(strName);
        node->setPosIndex(posIndex&=0x7f>9?0:posIndex&=0x7f);//节点分布在10个周期内

        qDebug()<<"on_getCtNodeStage:offset list stage cnt"<<m_pDataProcess->m_ListStageTime.count()/*<<off*/;
        if(m_pDataProcess->m_ListStageTime.count()==0)
            return;
        node->setListTime(m_pDataProcess->m_ListStageTime);
        m_pNodeContent->appendCtNode(node,offset);

        qDebug()<<"append node "<<ctNodeId<<"offset"<<offset;
    }

    int cnt = m_ListCtNodeId.count();
    if(index+1<cnt)
    {
        qDebug()<<"next ctNodeId stageTime";
    }
    else
    {
        qDebug()<<"complete ctNodeId stageTime";
        m_pNodeContent->calOffsetList();
    }
}

void WClusterDlg::on_mouseSelectCtNode(quint32 nodeId)
{

    int index = m_ListCtNodeId.indexOf(QString::number(nodeId));
    if(index!=-1)
    {
        qDebug()<<"node name change"<<index;
        ui->cbNodeName->setCurrentIndex(index);
    }
}

void WClusterDlg::on_cbCtNodeNameChange(int index)
{
    if(index!=-1)
    {
        if(m_ucKeyIndex==index)
        {
            ui->cbCheck->setChecked(true);
        }
        else
        {
            ui->cbCheck->setChecked(false);
        }
        if(m_ListCtNodeId.count()>index)
             ui->leNodeId->setText(m_ListCtNodeId[index]);
        //ui->sbNodeDif->setValue(m_pDataProcess->m_ListCTNodeOffset[index]);
        qDebug()<<"node name changge"<<m_pNodeContent->m_ListRelativeOffset.count()<<index;
        if(m_pNodeContent->m_ListRelativeOffset.count()>index)
        {
            int offset = m_pNodeContent->m_ListRelativeOffset[index]%m_pDataProcess->m_pClusterInfo->iCircle;
    //        qDebug()<<"on cbnode name chagne offset"<<offset;
            if(index!=0)
            {
                qDebug()<<"offsetchange0";
                offset = (offset+m_pNodeContent->m_ListRelativeOffset[0])%m_pDataProcess->m_pClusterInfo->iCircle;
            }/*
            else
            {
                offset = offset%m_pDataProcess->m_pClusterInfo->iCircle;
            }*/
            if(offset<0)
            {
                offset += m_pDataProcess->m_pClusterInfo->iCircle;
            }
            ui->sbNodeDif->setValue(offset);
        }
    }

}

void WClusterDlg::on_offsetChange(quint32 nodeId)
{
    int id = ui->leNodeId->text().toInt();
    if(id==nodeId&&m_pCtPattern!=NULL)
    {
        int index = m_ListCtNodeId.indexOf(ui->leNodeId->text());
        //quint8 circle = m_pDataProcess->m_pClusterInfo->iCircle;
        quint8 circle = m_pCtPattern->ucCycleTime;
        if(index!=-1&&circle!=0)
        {
            qDebug()<<"offsetchange1";
            int  offset = m_pNodeContent->m_ListRelativeOffset[index]%circle;
            if(index!=0)
            {
                offset = (offset+m_pNodeContent->m_ListRelativeOffset[0])%circle;
            }/*
            else
            {
              offset = m_pNodeContent->m_ListRelativeOffset[index];
            }*/
            if(offset<0)
            {
                offset += circle;
            }
            qDebug()<<"offset change"<<offset;
//            if(m_ucKeyIndex==index)
//            {
//                offset = m_ucKeyIndex%circle;
//            }
            ui->sbNodeDif->setValue(offset);
        }
    }
}

void WClusterDlg::on_appBtn()
{
    m_pNodeContent->calPosIndexList();
    m_pDataProcess->m_bFlagClusterSend = true;
    QList<quint8> listCoor;
    quint8 patternId = ui->sbPatternNo->value();
    if(m_pDataProcess->setClusterInfoList(m_ListCtNodeId,m_pNodeContent->m_ListNodePosIndex,m_pNodeContent->m_ListRelativeOffset,listCoor,patternId))
    {
        m_pDataProcess->sendClusterInfoToLib();
    }
//    if(cnt>0)
//    {

////        m_pDataProcess->sendCtNodePatternToTsc(m_pNodeContent->m_ListNodePosIndex,m_pNodeContent->m_ListRelativeOffset);
//    }

   // m_pDataProcess->m_bFlagClusterSend = false;
}

//void WClusterDlg::on_calOffsetList()
//{
//    m_ListRelativeOffset.clear();
//    int cnt =
//}

void WClusterDlg::on_readBtn()
{
//    int index = ui->cbCtName->currentIndex();
//    if(index!=-1)
//      on_cbCtNameChange(index);
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->requireDataBaseTable(CLUSTER_TIMEBASE,m_pDataProcess->m_ucCurClusterId);
    }
}

void WClusterDlg::on_cbCheck()
{
    if(m_pDataProcess->m_pClusterInfo!=NULL)
    {
        int index = ui->cbNodeName->currentIndex();
        quint8 circle = m_pDataProcess->m_pClusterInfo->iCircle;
        if(index!=-1&&circle!=0)
        {
            if(ui->cbCheck->isChecked())
            {
                m_ucKeyIndex = index;
                m_ucKeyOffset = ui->sbNodeDif->value()%circle;
                m_pNodeContent->setKeyData(index,m_ucKeyOffset);
                qDebug()<<"check"<<index<<m_ucKeyOffset;
            }
        }
    }
}

void WClusterDlg::on_treeViewClick(QModelIndex index)
{
    if(index.isValid())
    {
        QString str = m_pDataProcess->m_TscNameIconModel->data(index).toString();
       // bool bFlagShowCluster = m_pDataProcess->m_bFlagShowCluster;
        if(index.parent()!=QModelIndex())//节点
        {
//            QModelIndex pIndex = index.parent();
//            int nameIndex = nodeNameCB->findText(str);
//            nodeNameCB->setCurrentIndex(nameIndex);
//            cbClusterName->setCurrentIndex(pIndex.row());
        }
        else
        {
            int ctIndex = m_pDataProcess->m_ListCTName.indexOf(str);
            if(ctIndex==ui->cbCtName->currentIndex())
            {
                on_cbCtNameChange(ctIndex);
            }
            else
            {
                ui->cbCtName->setCurrentIndex(ctIndex);
            }
        }
    }
}

void WClusterDlg::on_addCTBtn()
{
    quint8 id = m_pDataProcess->getNewClusterId();
    m_pDataProcess->m_ucCurClusterId = id;
    if(id>0)
    {
        m_iCurCtIndex = id-1;
        m_ListCtNodeId.clear();
        m_pNodeContent->clearCtNodeList();
        clearCtPatternData();
        ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
        p->ucClusterId = id;
        ui->leCtId->setText(QString::number(id));
//        leClusterId->setModified(true);

        ui->cbCtName->clearEditText();
        ui->cbCtDomain->clearEditText();
        ui->cbCtEnable->setCurrentIndex(1);

        m_pDataProcess->analyseClusterInfo();
        m_pDataProcess->m_bFlagCTInit = false;
        m_pDataProcess->m_bFlagAddCT = true;
//        m_pDataProcess->m_bFlagUpDateCTNode = false;
        m_pDataProcess->initMapTable();
//        on_ctPatternNoChange(1);
        m_bDlgInit = true;
    }
}

void WClusterDlg::on_delCTBtn()
{
    //quint8 id = leClusterId->text().toInt();
    QString strName = ui->cbCtName->currentText();
    int index = m_pDataProcess->m_ListCTName.indexOf(strName);
    if(index!=-1)
    {

        quint8 id = m_pDataProcess->m_ListCTId[index].toInt();
        if(id>0&&id<MAX_CLUSTER_NUM+1&&m_pDataProcess!=NULL)
        {
            if(QMessageBox::question(this,tr("警告"),tr("确定删除群：%1").arg(strName),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Ok)
            {
                if(m_iCurCtIndex>-1)
                {
                    m_iCurCtIndex--;
                }
                if(m_pDataProcess->m_pClusterInfo!=NULL)
                {
    //                m_pDataProcess->m_pClusterInfo->init();
                    memset(m_pDataProcess->m_pCTProperty+id-1,0,sizeof(ClusterProperty_Table));
                }
                m_pDataProcess->deleteCtId(index);
                if(m_pDataProcess->m_ListCTName.count()==0)
                {
                    m_pCtPattern = NULL;
                }
            }


    //        memset(p,0,sizeof(ClusterProperty_Table));
//            if(m_pDataProcess->sendClusterCommand(CLUSTER_DELETE,id))
//            {
//                qDebug()<<"deal cluster send succ";
//            }
        }
    }

}

void WClusterDlg::on_readCTBtn()
{
    m_pDataProcess->requireClusterInfoTable();
}

void WClusterDlg::on_appCTBtn()
{
    quint8 id = m_pDataProcess->m_ucCurClusterId;
    ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
    p->ucClusterEnable = ui->cbCtEnable->currentIndex();
    m_pDataProcess->sendClusterInfoToLib();
}

//void WClusterDlg::on_ctNameChange(int index)
//{
//    if(index==-1)
//        return;
//    qDebug()<<"ct name change index"<<index;
//    if(m_pDataProcess->m_ListCTId.count()>index&&index!=-1)
//    {
//        quint8 id = m_pDataProcess->m_ListCTId[index].toInt();
//        ClusterProperty_Table *p = m_pDataProcess->m_pClusterInfo->tbCTProperty+id-1;
//        leClusterId->setText(QString::number(id));
//        cbClusterDomainId->setEditText(QString::number(p->ucDomainId));
//        if(p->ucClusterEnable==0)
//        {
//            cbClusterEnable->setCurrentIndex(0);
//        }
//        else
//        {
//            cbClusterEnable->setCurrentIndex(1);
//        }
//    }
//}

void WClusterDlg::on_ctNameChange(QString str)
{
    if(str.isEmpty())//如果未更新 就无法 用已经 有的名字（相当名字无法对调）
        return;
    int ctNameIndex = m_pDataProcess->m_ListCTName.indexOf(str);

    qDebug()<<"on_ctNameChange edit change"<<str<<ctNameIndex;
    if(ctNameIndex<0)
    {
//        quint8 id = m_pDataProcess->m_ListCTId[ctNameIndex].toInt();
//        quint8 id = m_pDataProcess->m_uiCurNodeId;
        quint8 id = ui->leCtId->text().toInt();
        qDebug()<<"ctId"<<id;
        if(id>0&&id<MAX_CLUSTER_NUM+1)//去掉默认群
        {
            if(m_bDlgInit)
            {
//                qDebug()<<"on_ctNameChange id"<<id;
//                qDebug()<<"on_ctNameChange"<<str<<id;
                ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
                QByteArray strArr = str.toLocal8Bit();
                quint8 len = strArr.count();
                if(len>CLUSNAMELEN)
                {
                    len = CLUSNAMELEN;
                }
                p->ucClusterNameLen = len;
                memset(p->ucClusterName,0,CLUSNAMELEN);
                memcpy(p->ucClusterName,strArr.data(),len);
            }
        }
    }

}

void WClusterDlg::on_ctDomainIdChange(QString str)
{
    if(str.isEmpty())
        return;
    qDebug()<<"on_ctDomainIdChange"<<str;
    quint8 id = m_pDataProcess->m_ucCurClusterId;
    if(id>0&&id<MAX_CLUSTER_NUM+1)
    {
        if(m_bDlgInit)
        {
            ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
            p->ucDomainId = str.toInt();

        }
    }
}

void WClusterDlg::on_ctEnableChange(int index)
{
    if(index==-1)
        return;
    qDebug()<<"on_ctEnableChange"<<index;
    quint8 id = m_pDataProcess->m_ucCurClusterId;
    if(id>0&&id<MAX_CLUSTER_NUM+1)
    {
        if(m_bDlgInit)
        {
            ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
            p->ucClusterEnable = index;
        }
    }
}

void WClusterDlg::on_sbNodeDifChange(int dif)
{
    if(m_pDataProcess->m_pClusterInfo!=NULL)
    {
        int index = ui->cbNodeName->currentIndex();
        quint8 circle = m_pDataProcess->m_pClusterInfo->iCircle;
        if(index!=-1&&circle!=0)
        {
            if(ui->cbCheck->isChecked())
            {
                m_ucKeyIndex = index;
                m_ucKeyOffset = dif%circle;
                m_pNodeContent->setKeyData(index,m_ucKeyOffset);
                qDebug()<<"check"<<index<<m_ucKeyOffset;
            }
        }
    }
}

//void WClusterDlg::on_ctPatternAddBtn()
//{

//}

void WClusterDlg::on_ctPatternDelBtn()
{
    if(m_pCtPattern!=NULL)
    {
        memset(m_pCtPattern,0,sizeof(SClusterPattern));
        showCtPatternData();
    }
}

void WClusterDlg::on_ctPatternReadBtn()
{
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->requireDataBaseTable(CLUSTER_TIMEPATTERN,m_pDataProcess->m_ucCurClusterId);
    }
}

void WClusterDlg::on_ctPatternAppBtn()
{
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->sendClusterPattern();
    }
}

void WClusterDlg::on_ctPatternNoChange(int patternNo)
{qDebug()<<"m_pCtPattern->ucPatternId = patternNo";
    clearCtPatternData();
    if(m_pDataProcess!=NULL)
    {
        QString ctIdStr = ui->leCtId->text();
        if(!ctIdStr.isEmpty())
        {
            int ctId = ctIdStr.toInt();
            if(ctId>1)
            {
//                m_pDataProcess->getCTNodeId(ctId);
                m_pNodeContent->clearCtNodeList();
                m_pCtPattern = m_pDataProcess->m_pClusterInfo->tbCTPattern+patternNo-1;
                m_pCtPattern->ucPatternId = patternNo;
                qDebug()<<"m_pCtPattern->ucPatternId = patternNo"<<patternNo;
                showCtPatternData();

                quint8 circle = m_pCtPattern->ucCycleTime;
                if(circle==0)
                {
                    qDebug()<<"cluster circle=0 patternNo"<<patternNo;
                    return;
                }
                m_pNodeContent->setCtCircle(circle);
                quint8 stagePattern = m_pCtPattern->ucStagePatternId;

                qDebug()<<"cluster circle"<<circle<<"patternNo"<<patternNo<<"stagePattern"<<stagePattern;
                if(stagePattern>0&&stagePattern<(MAX_TIMEPATTERN_NUM+1))
                {
                    m_pDataProcess->m_ucCTStageTime = stagePattern;

                    m_ListCtNodeId.clear();
//                    m_ListCtNodeName.clear();
                    m_ListCtNodeIndex.clear();

                    m_ListCtNodeId.append(m_pDataProcess->m_ListCTNodeId);
//                    m_ListCtNodeName.append(m_pDataProcess->m_ListCTNodeName);
                    m_ListCtNodeIndex.append(m_pDataProcess->m_ListCTNodeIndex);

                    m_pDataProcess->getCTNodeOffset(m_pDataProcess->m_ucCurClusterId);
                    int nodeCnt = m_ListCtNodeId.count();
                    for(int i=0;i<nodeCnt;i++)
                    {
                        quint8 nodeId = m_ListCtNodeId[i].toInt();
                        if(m_pDataProcess->getCTNodeStageList(nodeId))
                        {
                            on_getCtNodeStage(nodeId);
                        }
                    }
                }
            }


        }
    }
}

void WClusterDlg::on_ctPatternCircle(int time)
{
    if(m_pCtPattern!=NULL)
    {
        if(m_bDlgInit)
        {
            m_pCtPattern->ucCycleTime = time;
//            if(m_pCtPattern->ucPatternId==0
            qDebug()<<"pattern circle changge time"<<time;
        }
    }
}

void WClusterDlg::on_ctPatternStagePattern(int stageId)
{
    if(m_pCtPattern!=NULL)
    {
        if(m_bDlgInit)
        {
            m_pCtPattern->ucStagePatternId = stageId;
        }
    }
}

void WClusterDlg::on_ctPatternCtlMode()
{
    if(m_pCtPattern!=NULL)
    {
        if(m_bDlgInit)
        {

        }
    }
}

void WClusterDlg::on_ctPatternSbOffsetChange(int value)
{
    if(m_pCtPattern!=NULL)
    {
        m_bDlgInit = false;
        int cnt = m_ListCtNodeName.count();
        ui->leNodeName->clear();
        qDebug()<<"on_ctPatternSbOffsetChange"<<value<<"cnt"<<cnt;
        if((value-1)<cnt&&value>0)
        {
            ui->leNodeName->setText(m_ListCtNodeName[value-1]);
        }
        quint8 num = m_pCtPattern->sOffsetList[value-1];
        ui->lePatternOffset->setText(QString::number(num));
        num = m_pCtPattern->ucCoordPhaseList[value-1];
        ui->lePatternCoor->setText(QString::number(num));
        m_bDlgInit = true;
    }
}

void WClusterDlg::on_ctPatternLeOffset(QString str)
{
    if(m_pCtPattern!=NULL)
    {
        if(m_bDlgInit)
        {
            int num = ui->sbPatternOffset->value();
            m_pCtPattern->sOffsetList[num-1] = str.toInt();
        }
    }
}

void WClusterDlg::on_ctPatternLeCoor(QString str)
{
    if(m_pCtPattern!=NULL)
    {
        if(m_bDlgInit)
        {
            int num = ui->sbPatternOffset->value();
            m_pCtPattern->ucCoordPhaseList[num-1] = str.toInt();
        }
    }
}

void WClusterDlg::on_rcvCtPattern()
{
//    quint8 patternId = ui->sbPatternNo->value();
//    if(patternId==1)
//    {
//        on_ctPatternNoChange(1);
//    }
//    else
//    {
//        ui->sbPatternNo->setValue(1);
//    }
}

void WClusterDlg::on_ctNameModelChange()
{
    if(m_pDataProcess->m_bFlagAddCT)
    {
        m_pDataProcess->m_bFlagAddCT = false;
    }
    int index = ui->cbCtName->currentIndex();
    if(index==m_iCurCtIndex)
    {
        on_cbCtNameChange(index);
    }
    else if(m_iCurCtIndex<ui->cbCtName->count()&&m_iCurCtIndex>-1)
    {
        ui->cbCtName->setCurrentIndex(m_iCurCtIndex);
    }
}
