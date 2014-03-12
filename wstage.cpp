#include <QDebug>
#include "wstage.h"
#include "ui_wstage.h"
#include "pdataprocess.h"
#include <qendian.h>
#include <QMessageBox>
#define TIMEGREEN 19
#define TIMEYELLOW 3
#define TIMERED 3

WStage::WStage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WStage)
{
    ui->setupUi(this);
    m_pWid = new WDirectionForm(ui->framePhase);
    m_pGroup = new StageGroup(ui->frameGroup);

    m_bInitStageIcon = true;
    m_pStageData = NULL;
    m_bClickPhase = true;
//    m_bClearStageGroup = true;
    m_pConflictBase = NULL;
    m_pOverlapBase = NULL;
    connect(m_pWid,SIGNAL(mouseClick(bool,quint8)),this,SLOT(on_widMouseClick(bool,quint8)));
    connect(m_pGroup,SIGNAL(mouseClick(quint16)),this,SLOT(on_iconMouseClick(quint16)));
    //m_pGroup->addStage();
    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(on_btnAdd()));
    connect(ui->btnDel,SIGNAL(clicked()),this,SLOT(on_btnDel()));
    connect(ui->btnRead,SIGNAL(clicked()),this,SLOT(on_btnRead()));
    connect(ui->btnApp,SIGNAL(clicked()),this,SLOT(on_btnApp()));
    ui->btnApp->setVisible(false);
    ui->btnRead->setVisible(false);
//    changePosition();
}

WStage::~WStage()
{
    delete ui;
}

void WStage::setStageIcons(QList<quint16> list)
{
    m_pGroup->clearGroup();
    m_pWid->clearState();
    if(list.isEmpty())
    {
        m_ucIndex = 0;
        m_ucStageCnt = 0;
        qDebug()<<"list is empty";
        return;
    }
    setFlagInitStageIcon(false);
    foreach(quint16 phase,list)
    {
        m_pGroup->addStage();
        m_pWid->setAllowPhase(phase);
    }
    setFlagInitStageIcon(true);
}

void WStage::setFlagInitStageIcon(bool b)
{
    m_bInitStageIcon = b;
    m_pWid->setFlagInitStageIcon(b);
}

void WStage::setUnClickAble()
{
    m_pWid->setUnClickAble();
}

void WStage::on_iconMouseClick(quint16 phase)
{//qDebug()<<tr("phase:0x%1").arg(phase,4,16);
//    if(m_bInitStageIcon)
//    {
    if(m_bClickPhase)
    {
        m_pWid->setAllowPhase(phase);
    }

    m_pGroup->getStageIndex(m_ucIndex,m_ucStageCnt);
    emit changeStageIndex(m_ucIndex);
//    }
}

/*
 input: listLoadNo 方向编号（用于决定用哪个路标）
        listValid 是否显示（20个）0-15（北东南西 左直右人行）16-19二次过街
        listPhaseId 20个方向对应的相位值；没有相位为0
*/
void WStage::changeNode(QList<quint8> listLoadNo, QList<bool> listValid, QList<quint8> listPhaseId)
{
    m_pWid->changeStage();
    m_pWid->setIconPixmap(listLoadNo);
    m_pWid->setFlagValid(listValid);
    m_pWid->setPhaseId(listPhaseId);
    m_pGroup->clearGroup();

    //--------------
//    m_pWid->setOverlapBase(m_pDataProcess);
//    if(m_bClearStageGroup)
//    {
//        m_bClearStageGroup = true;
//    }

}

//void WStage::setUnClickAble()
//{
//    m_pWid->setUnClickAble();
//}

void WStage::setOverlapConnect(QList<quint8> list)
{
    m_pWid->setOverlapConnect(list);

}

void WStage::setOverlapConnect(Overlap_Table *p)
{
    m_pOverlapBase = p;

    m_pWid->setOverlapBase(p);
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
            setOverlapConnect(list);
        }
    }
}

void WStage::setStageBase(StageTime_Table *p)
{
    m_pStageData = p;
    setStageIcons(getListAllowGreen());
}

QList<quint16> WStage::getListAllowGreen()
{
    QList<quint16> list;
    if(m_pStageData==NULL)
    {
        return list;
    }
    for(int i=0;i<MAX_STAGE_NUM;i++)
    {
        if((m_pStageData+i)->bStageNo!=0)
        {
            quint16 phase = (m_pStageData+i)->uEnablePhase;
            list.append(qFromBigEndian<quint16>(phase));
            qDebug()<<"stage id"<<(m_pStageData+i)->bStageNo<<qFromBigEndian<quint16>(phase);
        }
    }
    return list;
}

void WStage::setLedShow()
{
    m_pWid->setLcdShow(true);
}

void WStage::setChannelMap(QList<quint8> list)
{
    m_ListLoadMap.clear();
    m_ListLoadMap.append(list);
}

void WStage::setData(quint32 green, quint32 yellow, quint32 red, quint32 flash, int time)
{
    int cnt = m_ListLoadMap.count();
    for(int i=0;i<cnt;i++)
    {
        quint8 phaseId = m_ListLoadMap[i];
        DirectionIcon *icon = m_pWid->getIcon(phaseId);

        if(icon!=NULL)
        {
            bool bGreen = (green&0x0001)==1?true:false;
            bool bYellow = (yellow&0x0001)==1?true:false;
            bool bRed = (red&0x0001)==1?true:false;
            bool bFlash = (flash&0x0001)==1?true:false;
            icon->setFlagGreen(bGreen);
            icon->setFlagYellow(bYellow);
            icon->setFlagRed(bRed);
            icon->setFlash(bFlash);
        }
        //qDebug()<<"channel"<<i<<"phaseId"<<phaseId<<tr("green %1").arg(green,8,16);
        green>>=1;
        yellow>>=1;
        red>>=1;
        flash>>=1;
    }
    m_pWid->setLcdNum(time);
}

void WStage::setIconDark(quint8 index)
{
    m_pGroup->setIconDark(index);
}

void WStage::setMouseClick(quint8 index)
{
    m_pGroup->mouseClick(index);
}

void WStage::setFlagClickPhase(bool b)
{
    m_bClickPhase = b;
}

void WStage::setBack(quint8 dir)
{
    m_pWid->setBack(dir);
    m_pGroup->setBack(dir);
}

void WStage::killFlash()
{
    m_pWid->killFlash();
}

void WStage::clearInterface()
{
    m_pWid->clearState();
    m_pGroup->clearGroup();
}

void WStage::changePosition()
{
    ui->frameGroup->move(0,0);
    ui->framePhase->move(0,106);
}

void WStage::setConflictBase(PhaseConflict_Table *p)
{
    m_pConflictBase = p;
    m_pWid->setConflictBase(p);
}

//void WStage::setFlagClearStageGroup(bool b)
//{
//    m_bClearStageGroup = b;
//}

void WStage::on_widMouseClick(bool b,quint8 phaseId)
{
    if(m_pConflictBase!=NULL&&phaseId>0&&phaseId<(MAX_CONFLICT_NUM+1))
    {
        PhaseConflict_Table *pConflict = m_pConflictBase+phaseId-1;
        m_pWid->setConflict(phaseId,pConflict->uConflictPhase,b);
    }

    quint16 phase = m_pWid->getPhase();
    m_pGroup->setListAllowGreen(m_pWid->getListFlagGreen(),m_pWid->getListPixGreen(),phase);
    //改变允许相位值

    if(m_pStageData!=NULL&&m_bInitStageIcon)
    {qDebug()<<"change phase :"<<phase;
        (m_pStageData+m_ucIndex)->uEnablePhase = qToBigEndian<quint16>(phase);
    }
}

void WStage::on_btnAdd()
{
    if(m_pStageData!=NULL&&m_ucStageCnt<MAX_STAGE_NUM)
    {
        if(m_ucIndex<(m_ucStageCnt-1)&&m_ucStageCnt>0)
        {
            int cnt = m_ucStageCnt-1-m_ucIndex;
            memcpy((void*)(m_pStageData+m_ucIndex+2),(void*)(m_pStageData+m_ucIndex+1),cnt*sizeof(StageTime_Table));
            for(int i=0;i<cnt;i++)
            {
                (m_pStageData+m_ucIndex+2+i)->bStageNo += 1;
            }
        }
        else if(m_ucIndex==(m_ucStageCnt-1)&&m_ucStageCnt!=0)//最后位置
        {
            (m_pStageData+m_ucIndex+1)->bStageNo = m_ucIndex+2;
            (m_pStageData+m_ucIndex+1)->bGreenTime = TIMEGREEN;
            (m_pStageData+m_ucIndex+1)->bYellowTime = TIMEYELLOW;
            (m_pStageData+m_ucIndex+1)->bRedTime = TIMERED;
            qDebug()<<"add stage"<<m_ucIndex+2<<"No"<<(m_pStageData+m_ucIndex+1)->bNo;
        }
        else if(m_ucStageCnt==0)
        {
            (m_pStageData)->bStageNo = 1;
            (m_pStageData)->bGreenTime = TIMEGREEN;
            (m_pStageData)->bYellowTime = TIMEYELLOW;
            (m_pStageData)->bRedTime = TIMERED;

            qDebug()<<"add stage 1"<<TIMEGREEN<<TIMEYELLOW<<TIMERED;
        }
    }
    else if(m_ucStageCnt>=MAX_STAGE_NUM)
    {
        QMessageBox::warning(this,tr("警告"),tr("阶段数已达最大值16"));
        return;
    }
    m_pGroup->addStage();//将改变 m_pIcon m_ucIndex m_ucStageCnt
}

void WStage::on_btnDel()
{
    if(m_pStageData!=NULL)
    {
        if(m_ucIndex<(m_ucStageCnt-1)&&m_ucStageCnt>0)
        {
            int cnt = m_ucStageCnt-m_ucIndex;//比实际多 一个空白 当m_ucStageCnt=16时出错 空白值 为下个配时的第一阶段
            memcpy((void*)(m_pStageData+m_ucIndex),(void*)(m_pStageData+m_ucIndex+1),cnt*sizeof(StageTime_Table));
            for(int i=0;i<(cnt-1);i++)
            {
                (m_pStageData+m_ucIndex+i)->bStageNo -= 1;
            }
        }
        else if(m_ucIndex==(m_ucStageCnt-1))
        {
            (m_pStageData+m_ucIndex)->bStageNo = 0;
            (m_pStageData+m_ucIndex)->uEnablePhase = 0;
            (m_pStageData+m_ucIndex)->bGreenTime = 0;
            (m_pStageData+m_ucIndex)->bYellowTime = 0;
            (m_pStageData+m_ucIndex)->bRedTime = 0;
            (m_pStageData+m_ucIndex)->bOption = 0;
        }
    }
    m_pGroup->delIcon();
}

void WStage::on_btnRead()
{
//    on_changeNode();
    emit btnReadStage();
}

void WStage::on_btnApp()
{
    emit btnAppStage();
}

void WStage::on_changeNode()
{//try
    QList<quint8> listPixId;
    listPixId<<0x23<<0x46<<0x67;
    QList<bool> listValid;
    QList<quint8> listPhase;
    QList<quint8> listCom;
    listValid<<false<<true<<true<<true<<true<<true<<false<<true<<false<<true<<false<<true<<true<<true<<true<<true<<false<<false<<false<<true;
    listPhase<<0<<2<<3<<4<<5<<6<<0<<8<<0<<10<<0<<12<<13<<14<<33<<16<<0<<0<<0<<9;
    listCom<<33<<2<<3<<4;

    m_pWid->changeStage();
    m_pWid->setIconPixmap(listPixId);
    m_pWid->setFlagValid(listValid);
    m_pWid->setPhaseId(listPhase);

    //另外
   // m_pWid->setOverlapConnect(listCom);
    //实时界面可增加 去除 可点击
//    QList<quint16> listAllow;
//    listAllow<<0x1002<<0x0214<<0x0808<<0x8200;
//    setStageIcons(listAllow);
}
