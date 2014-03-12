//author: sun
//date:2011.09.29


#include "PDataProcess.h"

#include <QDebug>
//#include <cassert>
#include <QIcon>
#include <QDateTime>
#include <qendian.h>
#include <QApplication>
#include <QMap>
#include <qmath.h>
#include "DTable.h"
//#include "WMainwindow.h"
#include "CClientService.h"
#include "ace/Date_Time.h"
const int RCV_BUFF_SIZE = 8192;

PDataProcess::PDataProcess(/*WMainWindow *mainwin, */CClientService *cltsvc, QObject *parent) :
    QObject(parent),/*
    m_MainWin(mainwin),*/
    m_ClientServ(cltsvc)
{
    m_pSendMsgHead = new SUtcsFrameHead;//10.20
    m_pRcvMsgHead = new SUtcsFrameHead;
    m_iheadSize = sizeof(SUtcsFrameHead);

    m_bFlagTscNameList = false;//1107 add
    m_bFlagTscIdList = false;
//    m_bFlagModuleName = false;
    m_bFlagTimeBaseName = false;
    m_bFlagScheduleName = false;
    m_bEventInit = false;
//    m_bFlagTimePatternName = false;
//    m_bFlagStageTimeName = false;
    //m_bFlagEventLog = false;
    m_bFlagShowTimeBase = false;
    m_bFlagShowSchedule = false;
    m_bFlagShowCluster = false;
    m_bFlagShowStatus = true;
    m_bFlagShowDetector = false;
    m_bFlagShowVip = false;
    m_bFlagShowEventLog = false;

    m_uiCurNodeId = 1;//初始值
    m_iCurTscNameLisIndex = 0;
    m_ucScheduleNo = 0;
    m_bFlagClusterSend = false;
     m_pStageTime = NULL;
    m_bFlagTscTable = false;
    m_bFlagCTInit = false;

    m_bFlagDetSend = false;
    m_bFlagDetRead = false;
    m_bFlagDetAutoReport = false;

    m_bFlagNodeNameFocus = false;
    //------------------------------------------
   // m_pTscInfo = new STscInfo;
    m_pTscInfo = NULL;



    m_TscNameIconModel = new QStandardItemModel;//new TreeModel;


    //m_TscNameIconModel->setHeaderData(0,Qt::Vertical,tr("Info"));
    m_TscNameModel = new QStringListModel;
    //m_TscNameModel->setStringList(m_TscNameList);
    m_TscIdModel = new QStringListModel;
    m_TscClusterIdModel = new QStandardItemModel();
    m_TscProcotolModel = new QStandardItemModel();

    m_pModelModuleName = new QStringListModel();

    m_pModelTimeBaseName = new QStandardItemModel();
    m_pModelEvent = NULL;
    createScheduleModel();
    m_pSchedule = new Schedule_Table[MAX_SCHEDULE_EVENT_NUM];

    m_pModelScheduleName = new QStringListModel;

//    m_pModelTimePatternName = new QStringListModel;

//    m_pModelStageTimeName = new QStringListModel;

    m_pModelEventLog = new QStandardItemModel(0,3);
    m_pModelEventLog->setHeaderData(0,Qt::Horizontal,QObject::tr(" 节点名 "));
    m_pModelEventLog->setHeaderData(1,Qt::Horizontal,QObject::tr("记 录 时 间"));
    m_pModelEventLog->setHeaderData(2,Qt::Horizontal,QObject::tr("事  件  描  述"));

    m_pModelTscIp = new QStandardItemModel(0,3);
    m_pModelTscIp->setHeaderData(0,Qt::Horizontal,QObject::tr("                ip地址                "));
    m_pModelTscIp->setHeaderData(1,Qt::Horizontal,QObject::tr("        端口       "));
    m_pModelTscIp->setHeaderData(2,Qt::Horizontal,QObject::tr("       版本      "));

    m_EventNameModel = new QStringListModel();
    ckNodeNameDeligate = NULL;
    m_uiEventLogStart = 0;
    m_uiEventLogEnd = 0;
    m_iEventIndex = -1;
    m_iTabWidgetIndex = 1;//节点参数
//    nodeIcon.addFile(":/Files/images/trafficlightsign.png");

//    ctIcon.addFile(":/Files/images/Cluster.png");

//    dmtIcon.addFile(":/Files/images/Domain.png");

//    vipIcon.addFile(":/Files/images/Vip.png");
    //-------------vip-----------------------
    m_pVipInfo = new SVipInfo;
    m_pModelVipId = new QStandardItemModel;
    m_bFlagVipInit = false;
//    m_bFlagShowVip = false;
    m_pVip = NULL;
    m_ucCurVipId = 0;
    m_bFlagVipStateCheck = false;
    m_iCurVipNodeId = 0;
    //---------------------------------
    timer = new QTimer(this);
    //m_nodeIcon(":/images/trafficlightsign.png");

//    m_cRcvData = new char[8192];
    m_iComplete = 0;
    m_iDataLong = 0;
    m_bComplete = true;
    m_bFlagNodeIdChanged = true;
//    m_bFlagInit = false;
    m_bFlagOnLine = true;

    m_bFlagCluster = false;
    m_bFlagReadCluster = false;
    //---------------cluster------------
    m_pCTProperty = new ClusterProperty_Table[MAX_CLUSTER_NUM];
    m_pClusterInfo = NULL;//new SClusterInfo;
    m_pModelCTName = new QStringListModel;
    m_pModelCTNodeName = new QStringListModel;
    m_bFlagSendCTPlan = false;
    m_bFlagUpDateCTNode = false;
    m_bFlagAddCT = false;
    //---------------------------
    m_bFlagAutoReport = false;
    m_bFlagSingle = false;//try
    m_bFlagCtNode = false;

    //-------交通流量统计-----
    m_pModelTraffic = new QStandardItemModel(0,7);


    m_pModelTraffic->setHeaderData(0,Qt::Horizontal,QObject::tr(" 节点名 "));
    m_pModelTraffic->setHeaderData(1,Qt::Horizontal,QObject::tr("检测器ID"));
    m_pModelTraffic->setHeaderData(2,Qt::Horizontal,QObject::tr("记录时间"));
    m_pModelTraffic->setHeaderData(3,Qt::Horizontal,QObject::tr(" 车流量 "));
    m_pModelTraffic->setHeaderData(4,Qt::Horizontal,QObject::tr("平均占有率"));
    m_pModelTraffic->setHeaderData(5,Qt::Horizontal,QObject::tr("最大占有率"));
    m_pModelTraffic->setHeaderData(6,Qt::Horizontal,QObject::tr("最小占有率"));

    //-----------------------

    m_iCmdType = CS_CMDTYPE_LOCAL_DATABASE_READ;

    m_setData = new QSettings(tr("data.ini"),QSettings::IniFormat);
    m_bFlagReadIni = false;


    connect(m_ClientServ, SIGNAL(received(QByteArray )), this, SLOT(dealMessage(QByteArray )));
    connect(m_ClientServ,SIGNAL(sendToService(QByteArray,bool)),this,SIGNAL(sendToService(QByteArray ,bool )));
    connect(m_ClientServ,SIGNAL(connected(bool)),this,SLOT(on_connect(bool)));
//    connect(m_ClientServ, SIGNAL(received(QByteArray )), this, SIGNAL(received(QByteArray)));
    connect(this,SIGNAL(readCmdArr(QByteArray)),this,SLOT(dealMessage(QByteArray)));

    connect(timer,SIGNAL(timeout()),timer,SLOT(stop()));

    connect(m_TscNameIconModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(on_treeviewDataChange(QStandardItem*)));

    //connect(m_TscNameIconModel,SIGNAL())
    connect(m_pModelEvent,SIGNAL(itemChanged(QStandardItem*)),SLOT(on_schEventChange()));
    connect(m_ClientServ,SIGNAL(rcvTscInfo(QString)),this,SLOT(on_rcvTscIpInfo(QString)));

}

PDataProcess::~PDataProcess()
{
    qDebug()<<"~PDataProcess";
    if(m_pSendMsgHead!=NULL)
    {
        delete m_pSendMsgHead;
        m_pSendMsgHead = NULL;
    }
    if(m_pRcvMsgHead!=NULL)
    {
        delete m_pRcvMsgHead;
        m_pRcvMsgHead = NULL;
    }

    clearTscInfoList();
    m_ListTimeBaseName.clear();
    m_ListScheduleName.clear();

    m_ListChannelMap.clear();
    m_ListComMap.clear();
    m_ListOverlapMap.clear();

//    if(m_pTscInfo!=NULL)
//    {
//        delete m_pTscInfo;
//        m_pTscInfo = NULL;
//    }
//    if(m_pClusterInfo!=NULL)
//    {
//        delete m_pClusterInfo;
//        m_pClusterInfo = NULL;
//    }
    if(m_pCTProperty!=NULL)
    {
        delete[] m_pCTProperty;
        m_pCTProperty = NULL;
    }
    if(m_TscNameModel!=NULL)
    {
        delete m_TscNameModel;
        m_TscNameModel = NULL;
    }

    if(m_TscNameIconModel!=NULL)
    {
        delete m_TscNameIconModel;
        m_TscNameIconModel = NULL;
    }
    if(m_TscIdModel!=NULL)
    {
        delete m_TscIdModel;
        m_TscIdModel = NULL;
    }
    if(m_TscClusterIdModel!=NULL)
    {
        delete m_TscClusterIdModel;
        m_TscClusterIdModel = NULL;
    }
    if(m_TscProcotolModel!=NULL)
    {
        delete m_TscProcotolModel;
        m_TscProcotolModel = NULL;
    }

    if(m_pModelModuleName!=NULL)
    {
        delete m_pModelModuleName;
        m_pModelModuleName = NULL;
    }
    if(m_pModelTimeBaseName!=NULL)
    {
        delete m_pModelTimeBaseName;
        m_pModelTimeBaseName = NULL;
    }
    if(m_pModelEvent!=NULL)
    {
        delete m_pModelEvent;
        m_pModelEvent = NULL;
    }
    if(m_EventNameModel!=NULL)
    {
        delete m_EventNameModel;
        m_EventNameModel = NULL;
    }
    if(ckNodeNameDeligate!=NULL)
    {
        delete ckNodeNameDeligate;
        ckNodeNameDeligate = NULL;
    }
    if(m_pModelScheduleName!=NULL)
    {
        delete m_pModelScheduleName;
        m_pModelScheduleName = NULL;
    }
    if(m_pSchedule!=NULL)
    {
        delete[] m_pSchedule;
        m_pSchedule = NULL;
    }
//    if(m_pModelTimePatternName!=NULL)
//    {
//        delete m_pModelTimePatternName;
//        m_pModelTimePatternName = NULL;
//    }
//    if(m_pModelStageTimeName!=NULL)
//    {
//        delete m_pModelStageTimeName;
//        m_pModelStageTimeName = NULL;
//    }
    if(m_pModelTscIp!=NULL)
    {
        delete m_pModelTscIp;
        m_pModelTscIp = NULL;
    }
    if(m_pModelEventLog!=NULL)
    {
        delete m_pModelEventLog;
        m_pModelEventLog = NULL;
    }
    if(m_pModelTraffic!=NULL)
    {
        delete m_pModelTraffic;
        m_pModelTraffic = NULL;
    }
    if(timer!=NULL)
    {
        delete timer;
        timer = NULL;
    }
//    if(m_cRcvData!=NULL)
//    {
//        delete[] m_cRcvData;
//        m_cRcvData = NULL;
//    }
    if(m_pModelCTName!=NULL)
    {
        delete m_pModelCTName;
        m_pModelCTName = NULL;
    }
    if(m_pModelCTNodeName!=NULL)
    {
        delete m_pModelCTNodeName;
        m_pModelCTNodeName = NULL;
    }
    if(m_pVipInfo!=NULL)
    {
        delete m_pVipInfo;
        m_pVipInfo = NULL;
    }
    if(m_pModelVipId!=NULL)
    {
        delete m_pModelVipId;
        m_pModelVipId = NULL;
    }
    deleteMapData();

    delete m_setData;
}

void PDataProcess::htonlHead(int type,int num,int size)
{
    memset(m_pSendMsgHead,0,m_iheadSize);
    m_pSendMsgHead->uiCommandType = qToBigEndian<quint32>(type);
    m_pSendMsgHead->uiIdNum = qToBigEndian<quint32>(num);
    m_pSendMsgHead->uiDataSize = qToBigEndian<quint32>(size);

}

bool PDataProcess::sendMessage(const QByteArray &byteArr)
{
//    assert(NULL != m_ClientServ);

    bool b = false;
    int cnt = m_ClientServ->sendData(byteArr);
    if(byteArr.length() == cnt)
    {
        b = true;
    }
    qDebug()<<"check send:"<<tr("应发送")<<byteArr.length()<<";"<<tr("已经发送")<<cnt;
    return b;
}

bool PDataProcess::sendMessage(int type, int num, int size, QByteArray &byteArr)
{
    htonlHead(type,num,size);
    byteArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    int sendLen = m_iheadSize+size;
    int sendCnt = m_ClientServ->sendData(byteArr);

    qDebug()<<"check send:"<<tr("应发送")<<sendLen<<";"<<tr("已经发送")<<sendCnt;

    if(sendLen==sendCnt)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PDataProcess::requireTscInfoTable()
{
    //int type = CS_CMDTYPE_LOCAL_DATABASE_READ;//              = 0x60, 读本地数据库
    int type = CS_CMDTYPE_NODE_REQUEST;    // = 0x30, //节点操作请求
    int num = 0;
    int size = 2;
    htonlHead(type,num,size);
    QByteArray sendArr;
    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);
    //sendArr.append(char(LOCAL_TABLE_NODE));//               = 0x52,  节点表
    sendArr.append(char(NODE_READ));//   = 0x13,   //节点读取
    sendArr.append(char(DATA_TYPE_PARA));
    int sendLen = m_iheadSize + size;
    if(sendLen==m_ClientServ->sendData(sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PDataProcess::dealTscInfoTable(char *para1,int len)
{
    qDebug()<<"rcv TscInfoTable :";//解析节点表

    QString str;
    if(*para1==0x01)
    {
        //qDebug()<<"TscInfoTable error";
        str = tr("读取节点属性表失败");
    }
    if(*para1==0x00&&len>1)
    {
        str = tr("读取节点属性表成功");
        clearTscInfoList();
        para1++;
//        quint16 rowCnt = ntohs(*((quint16*)para1));//行号
        quint16 rowCnt = qFromBigEndian<quint16>(*((quint16*)para1));//行号
//        qDebug()<<"TscInfoTable rowCnt:"<<rowCnt;
        para1++;


        for(int i=0;i<rowCnt;i++)
        {
            para1++;
//            quint32 tscId = ntohl(*((quint32*)para1));
            quint32 tscId = qFromBigEndian<quint32>(*((quint32*)para1));
            bool b = false;
            if(tscId>0&&tscId<(MAX_TSC_NUM+1))
            {
                b = true;
            }

            //qDebug()<<"id:"<<tscId;

            para1 += sizeof(quint32);
            byte clusterId = *para1;
//            m_TscClusterIdList.append(clusterId);
            quint8 ctNodeIndex = *(++para1);
//            m_TscCtNodeIndex.append(ctNodeIndex);

            byte nameLen = *(++para1);
            para1++;
            QString tscName(QString::fromLocal8Bit((const char*)para1,(int)nameLen));
//            m_TscNameList.append(tscName);

            para1 += nameLen;
            byte ipLen = *para1;
            para1++;
            QString tscIp(QString::fromAscii((const char*)para1,ipLen));
//            m_TscIpList.append(tscIp);

            para1 += ipLen;
//            quint16 tscPort = ntohs(*((quint16*)para1));
            quint16 tscPort = qFromBigEndian<quint16>(*((quint16*)para1));
//            m_TscPortList.append(tscPort);

            para1 += sizeof(quint16);
            byte versionLen = *para1;
            para1++;
            QString tscVersion(QString::fromLocal8Bit((const char*)para1,(int)versionLen));
//            m_TscVersionList.append(tscVersion);

            para1 += versionLen;
            byte tscLinkType = *para1;
//            m_TscLinkTypeList.append(tscLinkType);

            para1++;
            byte tscProtocol = *para1;
//            m_TscProtocolList.append(tscProtocol);
            if(b)
            {
                m_TscIdList.append(QString::number(tscId));
                m_TscClusterIdList.append(clusterId);
                m_TscCtNodeIndex.append(ctNodeIndex);
                m_TscNameList.append(tscName);
                m_TscIpList.append(tscIp);
                m_TscPortList.append(tscPort);
                m_TscVersionList.append(tscVersion);
//                qDebug()<<tscName<<tr("tscVersion 版本号")<<tscVersion;
                m_TscLinkTypeList.append(tscLinkType);
                m_TscProtocolList.append(tscProtocol);
            }
        }
    }
    emit statusBarMessage(str);
//    if(m_bFlagReadCluster)
//    {//群时空图读取 先 读取 节点index，再取选定的群所有节点，然后读取群时基
//        getCTNodeId(m_ucCurClusterId);
//        requireDataBaseTable(CLUSTER_TIMEBASE,m_ucCurClusterId);
//        m_bFlagReadCluster = false;
//        return;
//    }
    m_bFlagTscNameList = true;
    m_bFlagTscIdList = true;
    initMapTable();
//    setModelItem();
//    m_iTscCnt = 0;

}

bool PDataProcess::sendTscInfoTable()
{
    quint16 cnt = m_TscIdList.count();
    quint16 cnt1 = m_TscClusterIdList.count();
    quint16 cnt2 = m_TscNameList.count();
    quint16 cnt3 = m_TscIpList.count();
    quint16 cnt4 = m_TscPortList.count();
//    int cnt5 = m_TscVersionList.count();
//    int cnt6 = m_TscLinkTypeList.count();
//    quint16 cnt7 = m_TscProtocolList.count();
    if(!(cnt==cnt1&&cnt1==cnt2&&cnt2==cnt3&&cnt3==cnt4))
    {
        qDebug()<<"list cnt error";
        return false;
    }
   #ifdef SINGLEMODE

        cnt = 1;

#else

        for(int i=0;i<cnt;i++)
        {
            if(!validTscName(m_TscNameList[i],i))
            {
                setStatusBarMessage(tr("节点名重复:%1").arg(m_TscNameList[i]),LBFIRST,Qt::red);
                return false;
            }
            if(!validTscIp(m_TscIpList[i],i))
            {
                setStatusBarMessage(tr("ip重复:%1").arg(m_TscIpList[i]),LBFIRST,Qt::red);
                return false;
            }

        }
  #endif
    int type = CS_CMDTYPE_NODE_REQUEST; //
    int num = 0;
    int size = 1+1+2;//tableName + Para1 + row1

    QByteArray sendArr;
//    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
//    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(NODE_WRITE));
    sendArr.append(char(DATA_TYPE_PARA));


    QByteArray dataArr;
    for(int i=0;i<cnt;i++)
    {
        QString nameStr = m_TscNameList[i];
        if(nameStr.isEmpty())
        {
            continue;
        }
        quint32 id = m_TscIdList[i].toInt();
        quint32 sendId = qToBigEndian<quint32>(id);
        dataArr.append((char*)&sendId,4);
        size+=4;

        quint8 clusterId = m_TscClusterIdList[i];
#ifdef SINGLEMODE
            clusterId = 1;
#endif
        dataArr.append(clusterId);
        size+=1;

        quint8 sequence = 0;
        dataArr.append(sequence);
        size+=1;

        QString name = m_TscNameList[i];
        QByteArray nameArr = name.toLocal8Bit();
        quint8 nameCnt = nameArr.count();
        dataArr.append(nameCnt);
        dataArr.append(nameArr);
        size+=(nameCnt+1);

        QString ip = m_TscIpList[i];
        QByteArray ipArr = ip.toLocal8Bit();
        quint8 ipCnt = ipArr.count();
        dataArr.append(ipCnt);
        dataArr.append(ipArr);
        size+=(ipCnt+1);

        quint16 port = m_TscPortList[i];
        quint16 bigPort = qToBigEndian<quint16>(port);
        dataArr.append((char*)&bigPort,sizeof(bigPort));
        size+=sizeof(bigPort);

        QString version = tr("版本号");
        QByteArray versionArr = version.toLocal8Bit();
        quint8 versionCnt = versionArr.count();
        dataArr.append(versionCnt);
        dataArr.append(versionArr);
        size+=(versionCnt+1);

        quint8 type = 0;
        dataArr.append(type);
        size+=1;

        quint8 protocol = 0;
        dataArr.append(protocol);
        size+=1;

    }
quint16 sendCnt = qToBigEndian<quint16>(cnt);
qDebug()<<"size"<<size;
    sendArr.append((char*)(&sendCnt),2);
    sendArr.append(dataArr);
    if(sendMessage(type,num,size,sendArr))
    {
        setStatusBarMessage(tr("发送节点信息表成功"));
        return true;
    }
    else
    {
        setStatusBarMessage(tr("发送节点信息表失败"));
        return false;
    }
}

void PDataProcess::requireAllTscTable()
{

    if(m_ListNewTscId.contains(m_uiCurNodeId))
    {
        m_ListNewTscId.removeOne(m_uiCurNodeId);
    }
    int cnt = m_ListNewTscId.count();
    if(cnt>0)
    {qDebug()<<"require all tsc table"<<cnt;
        quint32 id = m_ListNewTscId.first();
        int index = m_TscIdList.indexOf(QString::number(id));
        emit setNodeParaCbTscId(index);
    }
    else
    {   emit changeNodeId();//为了一开始界面显示，不需点击节点就可以显示 主动上报
//        m_bFlagInit = true;
        m_ListNewTscId.clear();
        emit statusBarMessage(tr("节点初始化完成,开始读取群信息"),1);
        requinreAllClusterTable();
        m_bFlagNodeIdChanged = false;
    }
}

void PDataProcess::requinreAllClusterTable()
{
    if(m_ListNewCtId.contains(m_ucCurClusterId))
    {
        m_ListNewCtId.removeOne(m_ucCurClusterId);
    }
    if(!m_ListNewCtId.isEmpty())
    {
        quint8 ctId = m_ListNewCtId.first();
        m_ucCurClusterId = ctId;
        m_pClusterInfo = m_mapCluster[ctId];
        requireDataBaseTable(CLUSTER_TIMEBASE,m_ucCurClusterId);
    }
    else
    {
        setStatusBarMessage(tr("初始化完成"),1);
    }
}

void PDataProcess::initMapTable()
{
    //----------------------清除删除掉的id-----------
#ifdef SINGLEMODE

//        if(m_TscIdList.count()>0)
        {
            m_TscIdList.clear();
            if(m_TscNameList.count()>0)
            {
                QString name = m_TscNameList.first();
                m_TscNameList.clear();
                m_TscNameList.append(name);
//                quint8 dbChoice = m_TscDbList[0];
//                m_TscDbList.clear();
//                m_TscDbList.append(dbChoice);

            }

            m_TscIdList.append(QString::number(1));
//            m_TscNameList.append(tr("默认节点"));
//            m_TscIpList.append(tr("192.168.1.1"));
//            m_TscPortList.append(5435);
            m_ListCTId.clear();
            m_ListCTId.append(QString::number(1));
        }

#endif
    QList<quint32> oldNodeIdList = m_mapTsc.keys();
    foreach(quint32 oldNodeId,oldNodeIdList)
    {
        if(!m_TscIdList.contains(QString::number(oldNodeId)))
        {
            m_mapTsc.remove(oldNodeId);
        }
    }
    QList<quint32> oldCtIdList = m_mapCluster.keys();
    qDebug()<<"m_ListCTId cnt"<<m_ListCTId<<"oldCtId"<<oldCtIdList;
    foreach(quint32 oldCtId,oldCtIdList)
    {
        if(!m_ListCTId.contains(QString::number(oldCtId)))
        {
            qDebug()<<"m_ListCTId not contain ct-old--------------remove--------------------------------------------------"<<oldCtId;
            m_mapCluster.remove(oldCtId);
        }
        else
        {
            qWarning()<<"m_ListCTId contain oldCtid"<<oldCtId;
        }
    }

    //-----------------添加新id map--------------
    int cnt = m_TscIdList.count();
    m_ListNewTscId.clear();
    for(int i=0;i<cnt;i++)
    {
        quint32 id = m_TscIdList[i].toInt();
        if(id>0)
        {
            if(!m_mapTsc.contains(id))
            {qDebug()<<"m_mapTsc not contain ct-new----------------------------------------------------------------"<<id;
                m_ListNewTscId.append(id);
                STscInfo *tsc = new STscInfo;
                SVipData *vd = new SVipData;
                m_mapTsc.insert(id,tsc);
                m_mapVip.insert(id,vd);
            }
        }
    }

    int ctCnt = m_ListCTId.count();
    m_ListNewCtId.clear();
    QList<quint32> listCt = m_mapCluster.keys();
    for(int i=0;i<ctCnt;i++)
    {
        quint32 ctId = m_ListCTId[i].toInt();
        if(ctId>0&&ctId!=1)//群 表信息 没有默认群的表； 群属性表 有默认群
        {
            if(!m_mapCluster.contains(ctId))
            { qDebug()<<"m_mapCluster not contain ct-new----------------------------------------------------------------"<<ctId<<"listct"<<listCt<<m_mapCluster.count();
                m_ListNewCtId.append(ctId);
                SClusterInfo* ct = new SClusterInfo;
                m_mapCluster.insert(ctId,ct);
            }
        }
    }

    setModelItem();
    if(m_bFlagAddCT)
    {
        emit ctNameModelChange();
    }
    //-----------------读取新数据--------
    if(m_ListNewTscId.isEmpty())
    {qDebug()<<"m_ListNewCtId cnt"<<m_ListNewCtId.count();
        requinreAllClusterTable();
    }
    else
    {
        quint32 newNodeId = m_ListNewTscId.first();
        int nodeIndex = m_TscIdList.indexOf(QString::number(newNodeId));
        if(nodeIndex!=0)
        {
            requireAllTscTable();
        }
    }
}

void PDataProcess::deleteMapData()
{
//    qDebug()<<"delete tscmap0";
    int mapTscCnt = m_mapTsc.count();
    if(mapTscCnt>0)
    {
        foreach(STscInfo*tsc,m_mapTsc)
        {
//            qDebug()<<"delete tscmap1";
            delete tsc;
//            qDebug()<<"delete tscmap2";
        }
        m_mapTsc.clear();
    }
//    qDebug()<<"delete tscmap3";
    int mapVipCnt = m_mapVip.count();
    if(mapVipCnt>0)
    {
        foreach(SVipData*data,m_mapVip)
        {
            delete data;
        }
        m_mapVip.clear();
    }

    int mapCtCnt = m_mapCluster.count();
    if(mapCtCnt>0)
    {
        foreach(SClusterInfo*ctInfo,m_mapCluster)
        {
            delete ctInfo;
        }
        m_mapCluster.clear();
    }
//    qDebug()<<"delete tscmap4";
}

quint8 PDataProcess::getCtNodeIndexByNodeId(quint32 id,quint8 newCtId)
{
    int index = m_TscIdList.indexOf(QString::number(id));
    if(index!=-1)
    {
        quint8 ctId = m_TscClusterIdList[index];
        if(ctId==newCtId)//群不变
        {
            return m_TscCtNodeIndex[index];
        }
    }
    return 0;
}

STscInfo* PDataProcess::getTscInfoByIndex(quint32 index)
{

    //memset(m_pTscInfo,0,sizeof(STscInfo));

    quint8 nodeId = m_TscIdList.at(index).toInt();
    if(m_mapTsc.contains(nodeId))
    {
        m_pTscInfo = m_mapTsc[nodeId];
        m_bFlagOnLine = true;//try
        shutdownAutoReport();
        m_uiCurNodeId = nodeId;
        emit changeNodeId();//
        if(m_iTabWidgetIndex==1)
        {
            emit nodeChangeIndex(index);
        }

        QString statusStr;
        if(!m_bFlagCluster&&m_TscIdList.count()>0)
        {
            int index = m_TscIdList.indexOf(QString::number(m_uiCurNodeId));
            statusStr.append(tr("当前节点:%1 ").arg(m_TscNameList[index]));
//            if(m_bFlagOnLine)
//            {
//                statusStr.append(tr("在线  "));
//            }
//            else
//            {
//                statusStr.append(tr("离线  "));
//            }
            emit statusBarMessage(statusStr,LBTHIRD);
        }
    }
    else
    {
        qDebug()<<"m_pTscInfo is NULL";
        return NULL;
    }
    //m_pTscInfo = m_TscMap[m_TscIdList.at(index).toInt()];
    m_pTscInfo->uiId = m_TscIdList.at(index).toInt();
    m_pTscInfo->ucClusterId = m_TscClusterIdList.at(index);
    QString name = m_TscNameList[index];
    memset(m_pTscInfo->sDeviceName,0,MAXNAMELEN);
    memcpy(m_pTscInfo->sDeviceName,name.toLocal8Bit().data(),name.toLocal8Bit().count());
    QString ip = m_TscIpList.at(index);
    memset( m_pTscInfo->sDeviceIp,0,MAXNAMELEN);
    memcpy( m_pTscInfo->sDeviceIp,ip.toAscii().data(),ip.toAscii().count());
    //m_pTscInfo->sDeviceIp.SetData(m_TscIpList.at(index).toAscii(),m_TscIpList.at(index).length());
    m_pTscInfo->uiPort = m_TscPortList.at(index);
//    QString version = m_TscVersionList.at(index);
//    memset(m_pTscInfo->sVersion,0,MAXNAMELEN);
//    memcpy(m_pTscInfo->sVersion,version.toLocal8Bit(),version.toLocal8Bit().count());
//    //m_pTscInfo->sVersion.SetData(m_TscVersionList.at(index).toLocal8Bit(),m_TscVersionList.at(index).length());
//    m_pTscInfo->ucLinkType = m_TscLinkTypeList.at(index);
//    m_pTscInfo->ucProtocolType = m_TscProtocolList.at(index);
    qDebug()<<"getTscInfoByIndex";
    return m_pTscInfo;

}

STscInfo* PDataProcess::getTscInfoByName(QString name)
{
    if(m_TscNameList.contains(name))
    {
//        memset(m_pTscInfo,0,sizeof(STscInfo));
//        int index = m_TscNameList.indexOf(name);
//        m_pTscInfo->uiId = m_TscIdList.at(index).toInt();
//        m_pTscInfo->ucClusterId = m_TscClusterIdList.at(index);
//        m_pTscInfo->sDeviceName.SetString(m_TscNameList.at(index).toLocal8Bit());
//        m_pTscInfo->sDeviceIp.SetData(m_TscIpList.at(index).toAscii(),m_TscIpList.at(index).length());
//        m_pTscInfo->uiPort = m_TscPortList.at(index);
//        m_pTscInfo->sVersion.SetData(m_TscVersionList.at(index).toLocal8Bit(),m_TscVersionList.at(index).length());
//        m_pTscInfo->ucLinkType = m_TscLinkTypeList.at(index);
//        m_pTscInfo->ucProtocolType = m_TscProtocolList.at(index);
        return m_pTscInfo;
    }
    else
    {
        return NULL;
    }
}

bool PDataProcess::requireTscTable( qint32 tableName,unsigned int tscId)
{
qDebug()<<"requireTscTable------------------"<<tableName;
    int type = m_iCmdType;//CS_CMDTYPE_TSC_PARA_READ;// = CS_CMDTYPE_LOCAL_DATABASE_READ;//              = 0x60, 读本地数据库
    int num = 1;
    int size = 5;
    htonlHead(type,num,size);
    QByteArray sendArr;
    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);

    quint32 nodeId;
    if(tscId==0)
    {
        nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    }
    else
    {
        m_uiCurNodeId = tscId;
        qDebug()<<"tscId"<<tscId;
        nodeId = qToBigEndian<quint32>(tscId);

    }

    sendArr.append((char*)&nodeId,4);
    sendArr.append(char(tableName));//      具体表名
    //sendArr.append(char(DATA_TYPE_PARA));
    int sendLen = m_iheadSize + size;
    if(sendLen==m_ClientServ->sendData(sendArr))
    {
        m_ucTableName = tableName;
        if(m_bFlagOnLine)
        {qDebug()<<"set timeout 5000";
//            m_iTimerId = this->startTimer(TIMEOUT5000);
        }
//        else
//        {qDebug()<<"set timeout 100";
//            m_iTimerId = this->startTimer(TIMEOUT100);
//        }
        m_bFlagTscTable = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool PDataProcess::requireTscEvent(int index)
{
    int type = CS_CMDTYPE_TSC_PARA_READ;// = CS_CMDTYPE_LOCAL_DATABASE_READ;//              = 0x60, 读本地数据库
    int num = 1;
    int size = 5;
    htonlHead(type,num,size);
    QByteArray sendArr;
    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);

    quint32 nodeId;

    if(index==-1)
    {
        m_iEventIndex = -1;
        nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    }
    else
    {
        if(index<m_TscIdList.count())
        {
            m_iEventIndex = index;
            quint32 id = m_TscIdList[index].toInt();
            nodeId = qToBigEndian<quint32>(id);
        }
        else
        {
            m_iEventIndex = -1;
            return false;
        }
    }


    sendArr.append((char*)&nodeId,4);
    sendArr.append(char(TSC_TABLE_EVENTLOG));//      具体表名
    //sendArr.append(char(DATA_TYPE_PARA));
    int sendLen = m_iheadSize + size;
    if(sendLen==m_ClientServ->sendData(sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PDataProcess::requireTscSysPara()
{
//    int type = CS_CMDTYPE_TSC_PARA_READ;
//    int num = 1;
//    int size = 5;
//    htonlHead(type,num,size);
//    QByteArray sendArr;
//    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);

//    quint32 nodeId;

//    if(index==-1)
//    {
//        m_iEventIndex = -1;
//        nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
//    }
//    else
//    {
//        if(index<m_TscIdList.count())
//        {
//            m_iEventIndex = index;
//            quint32 id = m_TscIdList[index].toInt();
//            nodeId = qToBigEndian<quint32>(id);
//        }
//        else
//        {
//            m_iEventIndex = -1;
//            return false;
//        }
//    }


//    sendArr.append((char*)&nodeId,4);
//    sendArr.append(char(TSC_TABLE_EVENTLOG));//      具体表名
//    //sendArr.append(char(DATA_TYPE_PARA));
//    int sendLen = m_iheadSize + size;
//    if(sendLen==m_ClientServ->sendData(sendArr))
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
    return false;
}

bool PDataProcess::requireClusterInfoTable()
{
    int type = CS_CMDTYPE_LOCAL_DATABASE_READ;    // = 0x30, //节点操作请求
    int num = 0;
    int size = 1;
    htonlHead(type,num,size);
    QByteArray sendArr;
    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);
    sendArr.append(char(CLUSTER_PROPERTY));//   = 0x13,   //群读取
    int sendLen = m_iheadSize + size;
    if(sendLen==m_ClientServ->sendData(sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 tableName:数据表名
 id:节点 群 域 vip
*/
bool PDataProcess::requireDataBaseTable(quint32 tableName,quint32 id)
{
    int type = CS_CMDTYPE_LOCAL_DATABASE_READ;//              = 0x60, 读本地数据库
    int num = 1;
    int size = 4+1;
    htonlHead(type,num,size);
    QByteArray sendArr;
    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);

    quint32 nodeId = qToBigEndian<quint32>(id);
    sendArr.append((char*)&nodeId,4);
    sendArr.append(char(tableName));//      具体表名
    //sendArr.append(char(DATA_TYPE_PARA));
    int sendLen = m_iheadSize + size;
    if(sendLen==m_ClientServ->sendData(sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//模块表解析 按 网络字节序 存储
void PDataProcess::dealTscModuleTable(unsigned char *para1, int)
{
    QString strBar;
    if(*para1==0)
    {
        strBar = tr("读取模块表成功");
        quint8 cnt = *(++para1);//模块数
        m_pTscInfo->iModuleTableNum = cnt;
        Module_Table *moduleBase = m_pTscInfo->tbModule;

        int size = sizeof(Module_Table);
        memset(moduleBase,0,size*MAX_MODULE_NUM);
    //    m_ListModuleName.clear();


        for(quint8 i=0;i<cnt;i++)
        {

            para1++;//指向数据
            quint8 no = *para1;

            (moduleBase+no-1)->bNo = no;
            para1++;
            quint8 nodeLen = *para1;
            if(nodeLen>DEVICENODELEN)
            {
                qDebug()<<"module error nodeLen"<<nodeLen;
                return;
            }
            para1++;
            int nodeCnt = nodeLen;
            checkZero(para1,nodeCnt);
            (moduleBase+no-1)->bNodeLen = nodeCnt;
            memcpy((moduleBase+no-1)->sDeviceNode,para1,nodeLen);
            QString deviceStr = QString::fromAscii((char*)para1,nodeCnt);
    //        m_ListModuleName.append(deviceStr);

            para1+=nodeLen;

            quint8 vendorLen = *para1;
            if(vendorLen>VENDORLEN)
            {
                qDebug()<<"module error vendorLen"<<vendorLen;
                return;
            }
            para1++;
            int vendorCnt = vendorLen;
            checkZero(para1,vendorCnt);
            (moduleBase+no-1)->bVendorLen = vendorCnt;
            memcpy((moduleBase+no-1)->sVendor,para1,vendorCnt);
            para1+=vendorLen;
            quint8 modelLen = *para1;
            if(modelLen>MODULEMODELLEN)
            {
                qDebug()<<"module error modelLen"<<modelLen;
                return;
            }
             para1++;
             int modelCnt = modelLen;
             checkZero(para1,modelCnt);
             (moduleBase+no-1)->bModuleModelLen = modelCnt;
             memcpy((moduleBase+no-1)->sModuleModel,para1,modelCnt);
             para1+=modelLen;
             quint8 versionLen = *para1;
             if(versionLen>VERSIONLEN)//
             {
                 qDebug()<<"module error versionLen"<<versionLen;
//                 para1++;
//                 memcpy((moduleBase+no-1)->sVersion,para1,VERSIONLEN);
                 //return;
             }
             else
             {
//                 para1++;
//                 memcpy((moduleBase+no-1)->sVersion,para1,versionLen);
             }
             para1++;
             int versionCnt = versionLen;
             checkZero(para1,versionCnt);
             (moduleBase+no-1)->bVersionLen = versionCnt;
             memcpy((moduleBase+no-1)->sVersion,para1,versionCnt);
             para1+=versionLen;
             (moduleBase+no-1)->bModuleType = *para1;
        }
        analyseModuleTable();
    //    emit rcvModuleTable();
    //    m_bFlagModuleName = true;
    //    setModelItem();
//        QString str = tr("TSC_TABLE_MODULE succ");
//        emit statusBarMessage(str);
    }
    else
    {
        strBar = tr("读取模块表失败");
    }
    setStatusBarMessage(strBar);
    if(m_bFlagNodeIdChanged)
    {
        requireTscTable(TSC_TABLE_PHASECONFLICT);
    }

}

void PDataProcess::analyseModuleTable()
{
    Module_Table *moduleBase = m_pTscInfo->tbModule;
    int cnt = m_pTscInfo->iModuleTableNum;
    qDebug()<<"analysemoduletable cnt"<<cnt;
    m_ListModuleName.clear();
    for(int i=0;i<cnt;i++)
    {
        QString deviceStr = QString::fromAscii((moduleBase+i)->sDeviceNode,strlen((moduleBase+i)->sDeviceNode));
        m_ListModuleName.append(deviceStr);
    }
    emit rcvModuleTable();
    //    m_bFlagModuleName = true;
       // setModelItem();

    m_pModelModuleName->setStringList(m_ListModuleName);
}

void PDataProcess::checkZero(unsigned char *p, int &c)
{
    int cnt = c;
    for(int i=0;i<cnt;i++)
    {
        if(*(p+i)==0x00)
        {
            c--;
        }
    }
}

//发送模块表
bool PDataProcess::sendModuleToLib()
{
    if(m_pTscInfo==NULL)
    {
        return false;
    }
    QByteArray sendArr;
    if(getDataFromTableModule(m_pTscInfo,sendArr))
    {
        if(sendMessage(sendArr))
        {
            setStatusBarMessage(tr("发送模块表成功"));
            return true;
        }
        else
        {
            setStatusBarMessage(tr("发送模块表失败"));
            return false;
        }
    }


}

bool PDataProcess::getDataFromTableModule(STscInfo*pTsc,QByteArray &sendArr,bool bType)
{
    Module_Table *moduleBase = pTsc->tbModule;
    int cnt = 0;
    int tabSize = sizeof(Module_Table);
    int type = CS_CMDTYPE_TSC_PARA_WRITE; //0x12写信号机
    if(!bType)
    {
       type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;
    int size = 4+1+1+1;//nodeId+tableName + Para1 + row1

//    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_MODULE));
    sendArr.append(char(DATA_TYPE_PARA));


    QByteArray dataArr;
    for(int i=0;i<MAX_MODULE_NUM;i++)
    {
        Module_Table *p = moduleBase+i;
        quint8 bNo = p->bNo;
        if(bNo!=0)
        {
            cnt++;
            dataArr.append(bNo);
            size++;

            quint8 deviceLen = p->bNodeLen;
            dataArr.append(deviceLen);
            size++;
            dataArr.append(p->sDeviceNode,deviceLen);
            size+=deviceLen;

            quint8 vendorLen = p->bVendorLen;
            dataArr.append(vendorLen);
            size++;
            dataArr.append(p->sVendor,vendorLen);
            size+=vendorLen;

            quint8 modelLen = p->bModuleModelLen;
            dataArr.append(modelLen);
            size++;
            dataArr.append(p->sModuleModel,modelLen);
            size+=modelLen;

            quint8 versionLen = p->bVersionLen;
            dataArr.append(versionLen);
            size++;
            dataArr.append(p->sVersion,versionLen);
            size+=versionLen;

            dataArr.append(p->bModuleType);
            size++;
        }
    }

    sendArr.append(char(cnt));
    sendArr.append(dataArr);

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }


}

//时基表解析 按 网络字节序 存储
void PDataProcess::dealTscTimeBaseTable(char *p,int)
{
    QString statusStr;
    if(*p==0x01)
    {
        qDebug()<<"TscInfoTable error";
        statusStr = tr("读取时基表失败");
    }
    if(*p==0x00)
    {
        statusStr = tr("读取时基表成功");
        m_ListTimeBaseName.clear();
        int sizeCnt = sizeof(TimeBase_Table);
        memset(m_pTscInfo->tbTimeBase,0,sizeCnt*MAX_TIMEBASE_NUM);
        byte no;

        int rowCnt = *(++p);
        int index;//用于数组存储
        //
        m_pTscInfo->iTimeBaseTableNum = rowCnt;
        p++;
        TimeBase_Table *base = m_pTscInfo->tbTimeBase;
        for(int i=0;i<rowCnt;i++)
        {
            no = *p;//1~40
            index = no-1;
            memcpy(base+index,p,sizeCnt);
            p+=sizeCnt;
            qDebug()<<"dealTscTimeBaseTable base+index schedule"<<(base+index)->bScheduleNo;
        }
        analyseTimeBaseTable();
    }

    emit statusBarMessage(statusStr);
    //if(m_bFlagNodeIdChanged)//每次收到 时基表 都 再要求 时段表
    if(!m_bFlagReadIni)
    {
        requireTscTable(TSC_TABLE_SCHEDULE);
    }
}

void PDataProcess::analyseTimeBaseTable(TimeBase_Table *timebase)
{
    if(timebase==NULL)
    {
        timebase = m_pTscInfo->tbTimeBase;
    }
    setTimeBaseModel(timebase);
    emit changeSpecialModel();
}

void PDataProcess::addTimebaseIndex(TimeBase_Table *p,quint8 base, quint8 cnt)
{
//    TimeBase_Table *p = m_pTscInfo->tbTimeBase;
    for(int i=base;i<cnt+base;i++)
    {
        if((p+i)->bNo==0)
        {
            qDebug()<<"add timebase"<<i+1<<"base:"<<base;
            (p+i)->bNo = i+1;
            setTimeBaseModel(p,base,cnt,i+1);
            return;
        }
    }
    QString str = tr("时基表已满");
    setStatusBarMessage(str,LBFIRST);
}

void PDataProcess::setTimeBaseModel(TimeBase_Table *timebase,quint8 base, quint8 count, quint8 id)
{
    m_ListTimeBaseName.clear();
    m_pModelTimeBaseName->clear();
    int subIndex;//用于分别显示的序号
    QString strId;
    QString str;
    if(timebase==NULL)
    {
        timebase = m_pTscInfo->tbTimeBase;
    }
//    for(int index=base;index<count+base;index++)
   for(int index=0;index<MAX_TIMEBASE_NUM;index++)
    {
        quint8 no = /*index+1*/timebase[index].bNo;
        if(no>0)
        {
            qDebug()<<" setTimeBaseModel timebase no"<<no;
            if(no>byte(WIN_TIMEBASE_INDEX))
            {
                str = QObject::tr("冬日制");
                subIndex = no-WIN_TIMEBASE_INDEX;
            }
            else if(no>byte(SUM_TIMEBASE_INDEX))
            {
                str = QObject::tr("夏日制");
                subIndex = no-SUM_TIMEBASE_INDEX;
            }
            else
            {
                str = QObject::tr("特殊日");
                subIndex = no-SPECIAL_TIMEBASE_INDEX;
            }
            str += QObject::tr("时基表");
            str += QString::number(subIndex);

            m_ListTimeBaseName.append(str);
            if(id==no)
            {
                strId = str;
            }
        }
    }
    int cnt = m_ListTimeBaseName.count();
    m_pModelTimeBaseName->clear();
    for(int i=0;i<cnt;i++)
    {
        QStandardItem *item = new QStandardItem(m_ListTimeBaseName[i]);
        m_pModelTimeBaseName->setItem(i,item);
    }
    if(cnt>0)
    {
        int nameIndex = 0;
        if(id>0)
        {
            nameIndex = m_ListTimeBaseName.indexOf(strId);
        }
        nameIndex = nameIndex==-1?0:nameIndex;

        emit clickTimebaseIndex(m_pModelTimeBaseName->index(nameIndex,0));
    }
    else
    {
        emit clickTimebaseIndex(QModelIndex());
    }
}

/*
 发送整个时基表 添加 编辑 时 用tbTimeBase取代index
 删除时 跳过index
*/

bool PDataProcess::sendTimeBaseToLib(bool bCluster)
{
    QString strBar;
    int tabSize = sizeof(TimeBase_Table);
    int type = CS_CMDTYPE_TSC_PARA_WRITE; //;
    if(bCluster)
    {
       type = CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    }
    int num = 1;

    QByteArray sendArr;
    quint32 id;
    if(bCluster)
    {
        strBar = tr("发送群时基表");
        id = qToBigEndian<quint32>(m_ucCurClusterId);
        sendArr.append((char*)&id,4);//节点Id
        sendArr.append(char(CLUSTER_TIMEBASE));
    }
    else
    {
        strBar = tr("发送时基表");
        id = qToBigEndian<quint32>(m_uiCurNodeId);
        sendArr.append((char*)&id,4);//节点Id
        sendArr.append(char(TSC_TABLE_TIMEBASE));
    }

    sendArr.append(char(DATA_TYPE_PARA));
    int cnt = 0;
    QByteArray dataArr;
    TimeBase_Table* p;
    if(bCluster)
    {
        p = m_pClusterInfo->tbCTTimeBase;
    }
    else
    {
        p = m_pTscInfo->tbTimeBase;
    }
    for(int i=0;i<MAX_TIMEBASE_NUM;i++)
    {
        if(timebaseValid(p+i))
        {
            //群时间增加 群号
            if(bCluster)
            {
                dataArr.append(m_ucCurClusterId);
            }
            dataArr.append((char*)(p+i),tabSize);
            cnt++;
        }
    }


    if(bCluster)
    {
        tabSize+=1;
    }
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data
    sendArr.append(char(cnt));
    sendArr.append(dataArr);
    if(sendMessage(type,num,size,sendArr))
    {
        strBar.append(tr("成功"));
        setStatusBarMessage(strBar);
        return true;
    }
    else
    {
        strBar.append(tr("失败"));
        setStatusBarMessage(strBar);
        return false;
    }
}

bool PDataProcess::getDataFromTableTimeBase(STscInfo *pTsc,QByteArray &sendArr,bool bType)
{
    int tabSize = sizeof(TimeBase_Table);
    int type = CS_CMDTYPE_TSC_PARA_WRITE; //;
    if(!bType)
    {
       type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }

    int num = 1;
    quint32 id = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&id,4);//节点Id
    sendArr.append(char(TSC_TABLE_TIMEBASE));

    sendArr.append(char(DATA_TYPE_PARA));
    int cnt = 0;
    QByteArray dataArr;
    TimeBase_Table* p = pTsc->tbTimeBase;

    for(int i=0;i<MAX_TIMEBASE_NUM;i++)
    {
        if(timebaseValid(p+i))
        {
            dataArr.append((char*)(p+i),tabSize);
            cnt++;
        }
    }
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data
    sendArr.append(char(cnt));
    sendArr.append(dataArr);
    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PDataProcess::timebaseValid(TimeBase_Table*p)
{
    //TimeBase_Table *p = m_pTscInfo->tbTimeBase+i;
    quint8 no = p->bNo;
    if(no>0&&no<(MAX_TIMEBASE_NUM+1))
    {
        if((no-1)<SUM_TIMEBASE_INDEX)
        {
            return p->lMonthDay>0?true:false;
        }
        else /*if(i<WIN_TIMEBASE_INDEX)*/
        {
            return p->bWeekDay>0?true:false;
        }
    }
    return false;
}

//bool PDataProcess::sendTimeBaseToLib(byte index,bool bAdd, bool bEdit, bool bDel,  TimeBase_Table *tbTimeBase)
//{
//    int tabSize = sizeof(TimeBase_Table);
//    int cnt = m_pTscInfo->iTimeBaseTableNum;
//    if(bAdd)
//    {
//        cnt++;
//    }
//    if(bDel)
//    {
//        cnt--;
//    }

//    qDebug()<<"send cnt:"<<cnt;
//    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
//    int num = 1;
//    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

//    QByteArray sendArr;
//    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
//    sendArr.append((char*)&nodeId,4);//节点Id

//    sendArr.append(char(TSC_TABLE_TIMEBASE));
//    sendArr.append(char(DATA_TYPE_PARA));
//    sendArr.append(char(cnt));
//    TimeBase_Table* p = m_pTscInfo->tbTimeBase;
//    if(bAdd||bEdit)
//    {


//        for(byte i=0;i<MAX_TIMEBASE_NUM;i++)
//        {
//            if(i==index)
//            {
//                qDebug()<<"index edit/add"<<index;
//                sendArr.append((char*)tbTimeBase,tabSize);
//            }
//            else
//            {
//                if((p+i)->bNo!=0)
//                {
//                    qDebug()<<"append str i:"<<i;
//                    sendArr.append((char*)(p+i),tabSize);
//                }
//            }
//        }
//    }
//    if(bDel)
//    {
//        for(byte i=0;i<MAX_TIMEBASE_NUM;i++)
//        {
//            if(i==index)
//            {
//                continue;
//            }
//            else
//            {
//                if(i==0)
//                {
//                    qDebug()<<"i=0 id"<<(p+i)->bNo;
//                }
//                if((p+i)->bNo!=0)
//                {
//                    qDebug()<<"i:"<<i;
//                    sendArr.append((char*)(p+i),tabSize);
//                }
//            }
//        }
//    }

//    return sendMessage(type,num,size,sendArr);

//}

bool PDataProcess::sendTimeBaseToTsc(quint32 id)
{
    int tabSize = sizeof(TimeBase_Table);
    int cnt = m_pTscInfo->iTimeBaseTableNum;

    qDebug()<<"send cnt:"<<cnt;
    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 1;
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(id);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_TIMEBASE));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    TimeBase_Table* p = m_pTscInfo->tbTimeBase;
    for(byte i=0;i<MAX_TIMEBASE_NUM;i++)
    {
        if((p+i)->bNo!=0)
        {
            qDebug()<<"append str i:"<<i;
            sendArr.append((char*)(p+i),tabSize);
        }
    }

    return sendMessage(type,num,size,sendArr);
}

/*
 更新本地时基表
*/
//void PDataProcess::updateLocalTimeBase(byte index, bool bAdd,bool bEdit,bool bDel, TimeBase_Table *tbTimeBase)
//{
//    TimeBase_Table *p = &m_pTscInfo->tbTimeBase[index];
//    QString str;
//    int speCnt = 0;
//    int sumCnt = 0;
//    int winCnt = 0;
//    byte listIndex;//获得数量
//    listIndex = 0;
//    for(quint8 i=0;i<=index;i++)
//    {
//        if(m_pTscInfo->tbTimeBase[i].bNo!=0)
//        {
//            listIndex++;
//        }
//    }

//    if(bDel)
//    {
//        memset(p,0,sizeof(TimeBase_Table));
//        m_ListTimeBaseName.removeAt(m_ucListTimeBaseNameIndex);
//        m_bFlagTimeBaseName = true;
//        m_pTscInfo->iTimeBaseTableNum--;
//        setModelItem();

//    }
//    else if(bAdd||bEdit)
//    {
//        memcpy(p,tbTimeBase,sizeof(TimeBase_Table));
//        if(bAdd)
//        {
//            m_pTscInfo->iTimeBaseTableNum++;
//            byte subIndex;
//            if(index+1>=byte(WIN_TIMEBASE_INDEX))
//            {
//                str = QObject::tr("冬日制");
//                subIndex = index+1-WIN_TIMEBASE_INDEX;
//            }
//            else if(index+1>=byte(SUM_TIMEBASE_INDEX))
//            {
//                str = QObject::tr("夏日制");
//                subIndex = index+1-SUM_TIMEBASE_INDEX;
//            }
//            else
//            {
//                str = QObject::tr("特殊日");
//                subIndex = index+1-SPECIAL_TIMEBASE_INDEX;
//            }
//            str += QObject::tr("时基表");
//            str += QString::number(subIndex);
//            m_ListTimeBaseName.insert(listIndex,str);
//            m_bFlagTimeBaseName = true;
//            setModelItem();
//        }

//    }
//}

void PDataProcess::dealTscScheduleTable(char *p, int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取时段表失败");
    }
    else if(*p==0x00)
    {
        strBar = tr("读取时段表成功");
        m_pTscInfo->initScheduleTable();
        byte cntRow = *(++p);
        m_pTscInfo->iScheduleTableNum = (int)cntRow;
        byte cntCol = *(++p);
        qDebug()<<"row"<<cntRow<<"col"<<cntCol;
        byte schNo = 0;
        byte eventNo = 0;
        int tabSize = sizeof(Schedule_Table);
        Schedule_Table (*pSch)[MAX_SCHEDULE_EVENT_NUM];
        pSch = m_pTscInfo->tbSchedule;
        p++;//指向时段表数据开头

        char *pLocal;
        Schedule_Table* pRow;
        for(byte r=0;r<cntRow;r++)
        {
            pLocal = p + r*cntCol*tabSize;//定位 pLocal 指针

            schNo = *pLocal;

            pRow = *(pSch + (schNo-1));
            //qDebug()<<"row"<<r<<schNo;
            for(byte c=0;c<cntCol;c++)
            {

                if(*pLocal!=0x00)
                {
                    //qDebug()<<quint8(*pLocal);
                    Schedule_Table *pCol = pRow + c;
                    memcpy(pCol,pLocal,tabSize);//时段表里的事件 按 顺序存储
                    pLocal += tabSize;
                }
                else
                {
                    break;
                }
            }

        }
        analyseScheduleTable();
    }
    setStatusBarMessage(strBar);
    if(m_bFlagNodeIdChanged)
    {
        requireTscTable(TSC_TABLE_TIMEPATTERN);
    }
}

void PDataProcess::analyseScheduleTable(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM])
{
    if(tbSch==NULL)
    {
        tbSch = m_pTscInfo->tbSchedule;
    }
    setListScheduleName(tbSch);
//    m_bFlagScheduleName = true;
//    setModelItem();
    if(m_bFlagCluster)
    {
        m_pModelEvent->setHeaderData(3,Qt::Horizontal,QObject::tr("群周期"));
    }
    else
    {
    }
    m_pModelScheduleName->setStringList(m_ListScheduleName);
    if(m_pModelScheduleName->rowCount()>0)
    {
        emit clickSchIndex(m_pModelScheduleName->index(0));
        QString str = m_ListScheduleName[0];
        quint8 schId = 0;
        if(str.count()==5)
        {
            schId = str.right(1).toInt();
        }
        else if(str.count()==6)
        {
            schId = str.right(2).toInt();
        }
        if(schId>0)
        {
            setEventModelByIndex(schId-1,tbSch);
        }
    }
    else
    {
        setEventModelByIndex(0,tbSch);
    }
}

bool PDataProcess::sendScheduleToLib(bool bCluster)
{
    QString strBar;
    int cnt = 0;//m_pTscInfo->iScheduleTableNum;
    int tabSize;
    if(bCluster)
    {
        tabSize= sizeof(SClusterSchedule);
    }
    else
    {
        tabSize= sizeof(Schedule_Table);
    }
    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM];
    if(bCluster)
    {
        p = m_pClusterInfo->tbCTSchedule;
        strBar = tr("发送群时段表");
    }
    else
    {
        p = m_pTscInfo->tbSchedule;
        strBar = tr("发送时段表");
    }

    quint32 type = /*CS_CMDTYPE_LOCAL_DATABASE_WRITE;//*/CS_CMDTYPE_TSC_PARA_WRITE;//0x12写信号机
    if(bCluster)
    {
       type = CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    }
    quint32 num = 1;


    QByteArray sendArr;
    quint32 id;
    if(bCluster)
    {
        id = qToBigEndian<quint32>(m_ucCurClusterId);
        sendArr.append((char*)&id,4);//节点Id
        sendArr.append(char(CLUSTER_SCHEDULE));
    }
    else
    {
        id = qToBigEndian<quint32>(m_uiCurNodeId);
        sendArr.append((char*)&id,4);//节点Id
        sendArr.append(char(TSC_TABLE_SCHEDULE));
    }
    sendArr.append(char(DATA_TYPE_PARA));
    QByteArray dataArr;


    Schedule_Table* pSch;

    for(byte i=0;i<MAX_SCHEDULE_NUM;i++)
    {
        pSch = *(p+i);
        if(pSch->bNo!=0x00&&pSch->bEventNo!=0)
        {
            cnt++;
            if(bCluster)
            {
                for(int j=0;j<MAX_SCHEDULE_EVENT_NUM;j++)
                {
                    if((pSch+j)->bEventNo==0)
                    {
                        dataArr.append((char)0);
                    }
                    else
                    {

                        dataArr.append(m_ucCurClusterId);
                    }
                    dataArr.append((pSch+j)->bNo);
                    dataArr.append((pSch+j)->bEventNo);
                    dataArr.append((pSch+j)->bHour);
                    dataArr.append((pSch+j)->bMinute);
                    dataArr.append((pSch+j)->bTimePatternNo);
                    dataArr.append((pSch+j)->bControlMode);
                  //  dataArr.append((pSch+j)->bAssistantOut);//去除
                }
            }
            else
            {
                dataArr.append((char*)(*(p+i)),tabSize*MAX_SCHEDULE_EVENT_NUM);
            }
        }
    }

    quint32 size = 4+1+1+1+1+cnt*tabSize*MAX_SCHEDULE_EVENT_NUM;//nodeId+tableName + Para1 + row+col + data
    sendArr.append(char(cnt));
    sendArr.append(char(MAX_SCHEDULE_EVENT_NUM));
    sendArr.append(dataArr);

    qDebug()<<"size:"<<size<<"----------------------cnt:"<<cnt;
    if(sendMessage(type,num,size,sendArr))
    {
        strBar.append(tr("成功"));
        setStatusBarMessage(strBar);
        return true;
    }
    else
    {
        strBar.append(tr("失败"));
        setStatusBarMessage(strBar);
        return false;
    }
}

bool PDataProcess::getDataFromTableSchedule(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int cnt = 0;//m_pTscInfo->iScheduleTableNum;
    int tabSize = sizeof(Schedule_Table);

    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM];
    p = pTsc->tbSchedule;
    quint32 type = CS_CMDTYPE_TSC_PARA_WRITE;//0x12写信号机
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    quint32 num = 1;


    quint32 id;

    id = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&id,4);//节点Id
    sendArr.append(char(TSC_TABLE_SCHEDULE));
    sendArr.append(char(DATA_TYPE_PARA));
    QByteArray dataArr;
    Schedule_Table* pSch;

    for(byte i=0;i<MAX_SCHEDULE_NUM;i++)
    {
        pSch = *(p+i);
        if(pSch->bNo!=0x00&&pSch->bEventNo!=0)
        {
            cnt++;
            dataArr.append((char*)(*(p+i)),tabSize*MAX_SCHEDULE_EVENT_NUM);
        }
    }

    quint32 size = 4+1+1+1+1+cnt*tabSize*MAX_SCHEDULE_EVENT_NUM;//nodeId+tableName + Para1 + row+col + data
    sendArr.append(char(cnt));
    sendArr.append(char(MAX_SCHEDULE_EVENT_NUM));
    sendArr.append(dataArr);
    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
*/
//bool PDataProcess::sendScheduleToLib(byte index, bool bAdd, bool bEdit, bool bDel/*, Schedule_Table *tbSchedule*/)
//{
//    int cnt = m_pTscInfo->iScheduleTableNum;
//    int tabSize = sizeof(Schedule_Table);
//    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM];
//    p = m_pTscInfo->tbSchedule;
//    //qDebug()<<"sendschtolib"<<m_pTscInfo->tbSchedule[0]->bNo<<m_pTscInfo->tbSchedule[1]->bNo;
//    if(bAdd)
//    {
//        cnt++;
//    }
//    else if(bDel)
//    {
//        cnt--;
//    }
//    quint32 type = CS_CMDTYPE_TSC_PARA_WRITE;//0x12写信号机
//    quint32 num = 1;
//    quint32 size = 4+1+1+1+1+cnt*tabSize*MAX_SCHEDULE_EVENT_NUM;//nodeId+tableName + Para1 + row+col + data

//    //qDebug()<<"size:"<<size<<"cnt:"<<cnt;

//    QByteArray sendArr;
//    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
//    sendArr.append((char*)&nodeId,4);//节点Id

//    sendArr.append(char(TSC_TABLE_SCHEDULE));
//    sendArr.append(char(DATA_TYPE_PARA));
//    sendArr.append(char(cnt));
//    sendArr.append(char(MAX_SCHEDULE_EVENT_NUM));

//    Schedule_Table* pSch;

//    if(bAdd||bEdit)
//    {
//        for(byte i=0;i<MAX_SCHEDULE_NUM;i++)
//        {
//            if(i==index)
//            {
//                //qDebug()<<"index edit/add"<<index;
//                if(bDel)//??
//                {
//                    memset(m_pSchedule,0,tabSize*MAX_SCHEDULE_EVENT_NUM);
//                    for(int j=0;j<MAX_SCHEDULE_EVENT_NUM;j++)
//                    {
//                        m_pSchedule[j].bNo = index+1;
//                    }
//                }
//                sendArr.append((char*)m_pSchedule,tabSize*MAX_SCHEDULE_EVENT_NUM);
//            }
//            else
//            {
//                //quint8* no = (quint8*)(*(p+i));
//                pSch = *(p+i);
//                //qDebug()<<"no:"<<i<<*no<<pSch->bNo;
//                if(pSch->bNo!=0x00&&pSch->bEventNo!=0)
//                {
//                    //qDebug()<<"append str i:"<<i;
//                    sendArr.append((char*)(*(p+i)),tabSize*MAX_SCHEDULE_EVENT_NUM);
//                }
//            }
//        }
//    }
//    else if(bDel)
//    {
//       // memset(m_pSchedule,0,tabSize*MAX_SCHEDULE_EVENT_NUM);
//        for(byte i=0;i<MAX_SCHEDULE_NUM;i++)
//        {
//            if(i==index)
//            {
//                //m_pSchedule[]
//                continue;
//            }
//            else
//            {
//                //quint8* no = (quint8*)(*(p+i));
//                pSch = *(p+i);
//                //qDebug()<<"no:"<<i<<*no<<pSch->bNo;
//                if(pSch->bNo!=0x00&&pSch->bEventNo!=0)
//                //if(*(p+i)!=0x00)
//                {

//                    sendArr.append((char*)(*(p+i)),tabSize*MAX_SCHEDULE_EVENT_NUM);
//                }
//            }
//        }
//    }

//    return sendMessage(type,num,size,sendArr);
//}

bool PDataProcess::sendScheduleToTsc(quint32 id)
{
    int cnt = m_pTscInfo->iScheduleTableNum;
    int tabSize = sizeof(Schedule_Table);
    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM];
    p = m_pTscInfo->tbSchedule;

    quint32 type = CS_CMDTYPE_TSC_PARA_WRITE;//0x12写信号机
    quint32 num = 1;
    quint32 size = 4+1+1+1+1+cnt*tabSize*MAX_SCHEDULE_EVENT_NUM;//nodeId+tableName + Para1 + row+col + data


    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(id);
    sendArr.append((char*)&nodeId,4);//节点Id
    sendArr.append(char(TSC_TABLE_SCHEDULE));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    sendArr.append(char(MAX_SCHEDULE_EVENT_NUM));

    Schedule_Table* pSch;

    for(byte i=0;i<MAX_SCHEDULE_NUM;i++)
    {
        pSch = *(p+i);
        if(pSch->bNo!=0x00&&pSch->bEventNo!=0)
        {
            sendArr.append((char*)(*(p+i)),tabSize*MAX_SCHEDULE_EVENT_NUM);
        }
    }

    return sendMessage(type,num,size,sendArr);
}

//void PDataProcess::updateLocalSchedule(byte index, bool bAdd, bool bEdit,bool bDel/*,Schedule_Table *tbSchedule*/)
//{
//    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM] ;
//    p = &m_pTscInfo->tbSchedule[index];
//    Schedule_Table *pSch = *p;

//    int tabSize = sizeof(Schedule_Table);

//    if(bAdd||bEdit)
//    {
//        memcpy(p,m_pSchedule,tabSize*MAX_SCHEDULE_EVENT_NUM);
//        if(bAdd)
//        {
//            //qDebug()<<"add num++";
//            m_pTscInfo->iScheduleTableNum++;
//            qDebug()<<"m_ucScheduleIndex"<<index<<"No:"<<pSch->bNo;
//        }
//    }
//    else if(bDel)
//    {
//        //qDebug()<<"add num--";
//        memset(p,0,tabSize*MAX_SCHEDULE_EVENT_NUM);
//        m_pTscInfo->iScheduleTableNum--;
//    }
////    setListScheduleName();
//    qDebug()<<m_pTscInfo->tbSchedule[0]->bNo<<m_pTscInfo->tbSchedule[1]->bNo;
//}

/*
 获得时段表的存储位置  添加时段表时
 +1获得时段号
*/
quint8 PDataProcess::getScheduleIndex(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM])
{
    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM] ;
    if(tbSch==NULL)
    {
        p = m_pTscInfo->tbSchedule;
    }
    else
    {
        p = tbSch;
    }
    Schedule_Table *pSch;
    for(quint8 i=0;i<MAX_SCHEDULE_NUM;i++)
    {
        pSch = *(p+i);
       // qDebug()<<"point"<<pSch<<pSch+1;
        if(/*pSch->bNo==0&&*/pSch->bEventNo==0/*&&(pSch+1)->bEventNo==0*/)
        {
            qDebug()<<"add sch index"<<i;
           // pSch->bNo = i+1;
            return i;
        }
    }

    qDebug()<<"add sch index error";
    return 0x80;
}

void PDataProcess::addScheduleNameList(quint8 schId, Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM])
{
    int cnt = m_ListScheduleName.count();
    int index = -1;//查找schId的插入位置
    for(int i=0;i<cnt;i++)
    {
        QString str = m_ListScheduleName[i];
        int nameCnt = str.count();
        qDebug()<<str<<str.count()<<"list cnt"<<cnt;
        quint8 id = 0;
        if(nameCnt==6)
        {
            id = str.right(2).toInt();
        }
        else if(nameCnt==5)
        {
            id = str.right(1).toInt();
        }

        if(id>schId)
        {
            index = i;
            break;
        }
    }

    QString name = tr("时间计划%1").arg(schId);
    if(m_ListScheduleName.contains(name))
    {
        return;
    }
    if(index!=-1)
    {
        m_ListScheduleName.insert(index,name);
    }
    else
    {
        m_ListScheduleName.append(name);
    }

    int nameIndex = m_ListScheduleName.indexOf(name);
    m_pModelScheduleName->removeRows(0,m_pModelScheduleName->rowCount());
    m_pModelScheduleName->setStringList(m_ListScheduleName);
    emit clickSchIndex(m_pModelScheduleName->index(nameIndex));
    setEventModelByIndex(schId-1,tbSch);
}

void PDataProcess::delScheduleNameList(QModelIndex index, Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM])
{
    QString str = m_pModelScheduleName->data(index,Qt::DisplayRole).toString();
    int nameIndex = m_ListScheduleName.indexOf(str);
    m_ListScheduleName.removeOne(str);
    m_pModelScheduleName->removeRow(index.row());
    QString preName;
    if(index.row()>0)//被删 之前还有值
    {
        preName = m_ListScheduleName[nameIndex-1];
    }
    else if(m_ListScheduleName.count()>0)//第一个值 被删
    {
        preName = m_ListScheduleName[nameIndex];
    }
    int preIndex = m_ListScheduleName.indexOf(preName);
    quint8 schId = 0;
    if(preName.count()==6)
    {
        schId = preName.right(2).toInt();
    }
    else if(preName.count()==5)
    {
        schId = preName.right(1).toInt();
    }
//    qDebug()<<"preName"<<preName;
    if(schId>0)
    {
        setEventModelByIndex(schId-1,tbSch);
        clickSchIndex(m_pModelScheduleName->index(preIndex));
    }
    else
    {
        m_pModelEvent->removeRows(0,m_pModelEvent->rowCount());
    }

}

/*
*/
//quint8 PDataProcess::getScheduleListIndex(QString str)
//{
//    m_ListScheduleName.
//}

/*
 添加时段号 到 stringlist
*/
//void PDataProcess::addScheduleNo(quint8 index)
//{
//    QString str = QObject::tr("时段");
//    str+=QString::number(index+1);
//    m_ListScheduleName.append(str);
//    m_pModelScheduleName->setStringList(m_ListScheduleName);
//}

void PDataProcess::createScheduleModel()
{
    if(m_pModelEvent!=NULL)
    {
        delete m_pModelEvent;
    }
    m_pModelEvent = new QStandardItemModel(0,5);
    m_pModelEvent->setHeaderData(0,Qt::Horizontal,QObject::tr("开始时间"));
    //m_pModelEvent->setHeaderData(1,Qt::Horizontal,QObject::tr("开始分"));
    m_pModelEvent->setHeaderData(1,Qt::Horizontal,QObject::tr("控制方式"));
    m_pModelEvent->setHeaderData(2,Qt::Horizontal,QObject::tr("配时方案"));
    m_pModelEvent->setHeaderData(3,Qt::Horizontal,QObject::tr("辅助输出"));
    m_pModelEvent->setHeaderData(4,Qt::Horizontal,QObject::tr("特殊输出"));
    //m_pModelEvent->setHeaderData(6,Qt::Horizontal,QObject::tr("事件号"));
}

/*
*/
void PDataProcess::getDataFromScheduleModel(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM])
{
    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM];
    if(tbSch==NULL)
    {
        p = m_pTscInfo->tbSchedule+m_ucScheduleNo-1;
    }
    else
    {
        p = tbSch+m_ucScheduleNo-1;
    }
    Schedule_Table *pSchedule = *p;
    int tabSize = sizeof(Schedule_Table);
    memset(pSchedule,0,tabSize*MAX_SCHEDULE_EVENT_NUM);
    for(int i=0;i<MAX_SCHEDULE_EVENT_NUM;i++)
    {
        pSchedule[i].bNo = m_ucScheduleNo;
    }
    int cnt = m_pModelEvent->rowCount();

    qDebug()<<"getDataFromScheduleModel m_ucScheduleNo"<<m_ucScheduleNo<<"model cnt"<<cnt;
    QString timeStr;
    QStringList timeList;
    QString ctrlStr;
    quint8 ucCtrlMode;
    for(int i=0;i<cnt;i++)
    {
        timeStr = (m_pModelEvent->data(m_pModelEvent->index(i,0))).toString();
        quint8 hour = 0;
        quint8 minute = 0;
        if(timeStr.isEmpty())
        {
            continue;
        }
        else
        {
            timeList = timeStr.split(':');
            hour = timeList[0].toInt();
            minute = timeList[1].toInt();
        }

        QString patternName = (m_pModelEvent->data(m_pModelEvent->index(i,2))).toString();
        quint8 patternId = 0;
        if(m_bFlagCluster)
        {
            if(patternName.count()==5)
            {
                patternId = patternName.right(2).toInt();
            }
            else if(patternName.count()==4)
            {
                patternId = patternName.right(1).toInt();
            }
        }
        else
        {
            if(patternName.count()==4)
            {
                patternId = patternName.right(2).toInt();
            }
            else if(patternName.count()==3)
            {
                patternId = patternName.right(1).toInt();
            }
        }
        (pSchedule+i)->bEventNo = i+1;
        (pSchedule+i)->bHour = hour;
        (pSchedule+i)->bMinute = minute;
        (pSchedule+i)->bTimePatternNo = patternId;
        ctrlStr = (m_pModelEvent->data(m_pModelEvent->index(i,1))).toString();
        if(ctrlStr==QObject::tr("自主控制"))
        {
            ucCtrlMode = 0x00;
        }
        else if(ctrlStr==QObject::tr("关灯"))
        {
            ucCtrlMode = 0x01;
        }
        else if(ctrlStr==QObject::tr("闪光"))
        {
            ucCtrlMode = 0x02;
        }
        else if(ctrlStr==QObject::tr("全红"))
        {
            ucCtrlMode = 0x03;
        }
        else if(ctrlStr==QObject::tr("感应"))
        {
            ucCtrlMode = 0x06;
        }
        else if(ctrlStr==QObject::tr("单点优化"))
        {
            ucCtrlMode = 0x08;
        }
        else if(ctrlStr==QObject::tr("主从线控"))
        {
            ucCtrlMode = 0x0b;
        }
        else if(ctrlStr==QObject::tr("系统优化"))
        {
            ucCtrlMode = 0x0c;
        }
        else if(ctrlStr==QObject::tr("干预线控"))
        {
            ucCtrlMode = 0x0d;
        }
        else if(ctrlStr==QObject::tr("无电线缆协调"))
        {
            ucCtrlMode = 0x07;
        }
        (pSchedule+i)->bControlMode = ucCtrlMode;
        (pSchedule+i)->bAssistantOut = (m_pModelEvent->data(m_pModelEvent->index(i,3))).toInt();
        (pSchedule+i)->bSpecialOut = (m_pModelEvent->data(m_pModelEvent->index(i,4))).toInt();
        (pSchedule+i)->bNo = m_ucScheduleNo;
        //qDebug()<<"m_ucScheduleNo:"<<m_ucScheduleNo<<(m_pSchedule+i)->bHour;

    }
}

/*
设置scheduleModel的数据，index为时段表的存储位置
 b=true时显示更多 辅助输出特殊输出，默认false
*/
void PDataProcess::setEventModelByIndex(byte index, Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM])
{
    m_bEventInit = false;
    m_ucScheduleNo = index+1;

    Schedule_Table (*pRow)[MAX_SCHEDULE_EVENT_NUM] ;
    if(tbSch==NULL)
    {
        qDebug()<<"set data index"<<index;
        pRow = &m_pTscInfo->tbSchedule[index];
    }
    else
    {
        pRow = tbSch+index;
    }
    QString str;
    qDebug()<<"m_pModelEvent->rowCount()"<<m_pModelEvent->rowCount();
    if(m_pModelEvent->removeRows(0,m_pModelEvent->rowCount()))
    {
        qDebug()<<"clear schedule event----old cnt"<<m_pModelEvent->rowCount()<<"-------new index"<<index;
    }

    //m_pModelEvent->clear();
    int row = 0;
    for(int i=0;i<MAX_SCHEDULE_EVENT_NUM;i++)
    {
        Schedule_Table *p = *pRow;

        if((p+i)->bNo!=0&&(p+i)->bEventNo!=0)
        {
            quint8 hour = (p+i)->bHour;
            quint8 minute = (p+i)->bMinute;
            QString timeStr;
            if(hour<10)
            {
                timeStr = QString::number(0);
            }
            timeStr += QString::number(hour);
            timeStr+=":";
            if(minute<10)
            {
                timeStr += QString::number(0);
            }
            timeStr+=QString::number(minute);


            switch((p+i)->bControlMode)
            {
            case 0x00:
                str = tr("自主控制");
                break;
            case 0x01:
                str = tr("关灯");
                break;
            case 0x02:
                str = tr("闪光");
                break;
            case 0x03:
                str = tr("全红");
                break;
            case 0x06:
                str = tr("感应");
                break;
            case 0x08:
                str = tr("单点优化");
                break;
            case 0x0b:
                str = tr("主从线控");
                break;
            case 0x0c:
                str = tr("系统优化");
                break;
            case 0x0d:
                str = tr("干预线控");
                break;
            default:
                break;
            }

            QString patternStr;
            if(m_bFlagCluster)
            {
                patternStr = tr("群方案");
            }
            else
            {
                patternStr = tr("方案");
            }
            patternStr += QString::number((p+i)->bTimePatternNo);
            m_pModelEvent->insertRow(row);
            m_pModelEvent->setData(m_pModelEvent->index(row,0,QModelIndex()),(QVariant)timeStr);
            m_pModelEvent->setData(m_pModelEvent->index(row,1,QModelIndex()),str);
            m_pModelEvent->setData(m_pModelEvent->index(row,2,QModelIndex()),patternStr);
            //m_pModelEvent->setData(m_pModelEvent->index(i,1,QModelIndex()),(p+i)->bMinute,Qt::DisplayRole);
            m_pModelEvent->setData(m_pModelEvent->index(row,3,QModelIndex()),(p+i)->bAssistantOut);
            m_pModelEvent->setData(m_pModelEvent->index(row,4,QModelIndex()),(p+i)->bSpecialOut);
            row++;
        }

    }
    qDebug()<<"m_pModelEvent->rowCount() new cnt"<<m_pModelEvent->rowCount();
    m_bEventInit = true;
}

/*
*/
void PDataProcess::setListScheduleName(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM])
{
    m_ListScheduleName.clear();
    QString str = QObject::tr("时间计划");
    quint8 schNo;
    Schedule_Table (*p)[MAX_SCHEDULE_EVENT_NUM] ;
    p = tbSch;
    Schedule_Table *pSch;
    int tabSize = sizeof(Schedule_Table);
    for(int i=0;i<MAX_SCHEDULE_NUM;i++)
    {
        for(int j=0;j<MAX_SCHEDULE_EVENT_NUM;j++)
        {
            pSch = *(p+i)+j;
            schNo = pSch->bNo;

            quint8 eventNo = pSch->bEventNo;
            if(schNo!=0&&eventNo!=0)
            {
                qDebug()<<i<<j<<"schNo:"<<schNo;
                m_ListScheduleName.append(str+QString::number(schNo));
                break;
            }
        }
    }

    //m_pTscInfo->iScheduleTableNum = m_ListScheduleName.count();
    qDebug()<<"try1";
}

//void PDataProcess::setListScheduleNameIndex(quint8 index)
//{
//    m_ucListScheduleNameIndex = index;
//}

/*

*/
void PDataProcess::dealTscTimePatternTable(char *p, int)
{/*
    qDebug()<<"enter deal pattern";
    qDebug()<<"time pattern *p"<<(quint8)*p;*/
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取方案表失败");
    }
    else if(*p==0x00)
    {
        strBar = tr("读取方案表成功");
        quint8 cnt = *(++p);
        qDebug()<<"pattern cnt"<<cnt;
        m_pTscInfo->iTimePatternTableNum = cnt;
        int tabSize = sizeof(TimePattern_Table);
        TimePattern_Table *pattern = m_pTscInfo->tbTimePattern;
        memset(pattern,0,tabSize*MAX_TIMEPATTERN_NUM);//0320
        p++;//指向数据
        for(quint8 i=0;i<cnt;i++)
        {
            int patternIndex = *p-1;
            qDebug()<<"pattern id"<<patternIndex+1;
            memcpy(pattern+patternIndex,p,tabSize);

            p+=tabSize;
        }
        analyseTimePatternTable();
    }
    setStatusBarMessage(strBar);
//    if(m_bFlagShowCluster/*&&!m_bFlagClusterSend*/)
//    {
//        requireTscTable(TSC_TABLE_STAGETIME);
//        qDebug()<<"m_uiCurNodeId"<<m_uiCurNodeId;
//    }
    if(m_bFlagNodeIdChanged)
    {
        requireTscTable(TSC_TABLE_STAGETIME);
    }
}

void PDataProcess::analyseTimePatternTable()
{
    setListTimePatternName();
    emit updateTimePatternName();
}

bool PDataProcess::checkPatternData(TimePattern_Table *p)
{
    qDebug()<<"cycle"<<p->bCycle<<p->bStageTimeTableNo;
    return p->bCycle==0?false:true;
}

/*
*/
bool PDataProcess::sendTimePatternToLib(/*quint8 index, bool bAdd, bool bEdit, bool bDel, TimePattern_Table *tbTimePattern*/)
{
    if(m_pTscInfo!=NULL)
    {
        int tabSize = sizeof(TimePattern_Table);
        int cnt = 0;// = m_pTscInfo->iTimePatternTableNum;
        int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
        int num = 1;
        TimePattern_Table* p = m_pTscInfo->tbTimePattern;
        QByteArray dataArr;
        for(int i=0;i<MAX_TIMEPATTERN_NUM;i++)
        {
            if((p+i)->bNo!=0)
            {
                if(checkPatternData(p+i))
                {
                    cnt++;
                    dataArr.append((char*)(p+i),tabSize);
                }
                else
                {
                    (p+i)->bNo = 0;
                }
            }
        }
        int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data
    qDebug()<<"sendTimePatternToLib cnt"<<cnt;
        QByteArray sendArr;
        quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
        sendArr.append((char*)&nodeId,4);//节点Id

        sendArr.append(char(TSC_TABLE_TIMEPATTERN));
        sendArr.append(char(DATA_TYPE_PARA));
        sendArr.append(char(cnt));
        sendArr.append(dataArr);
        if(sendMessage(type,num,size,sendArr))
        {
            setStatusBarMessage(tr("发送方案表成功"));
            return true;
        }
        else
        {
            setStatusBarMessage(tr("发送方案表失败"));
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool PDataProcess::getDataFromTablePattern(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int tabSize = sizeof(TimePattern_Table);
    int cnt = 0;// = m_pTscInfo->iTimePatternTableNum;
    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;
    TimePattern_Table* p = pTsc->tbTimePattern;
    QByteArray dataArr;
    for(int i=0;i<MAX_TIMEPATTERN_NUM;i++)
    {
        if((p+i)->bNo!=0)
        {
            if(checkPatternData(p+i))
            {
                cnt++;
                dataArr.append((char*)(p+i),tabSize);
            }
            else
            {
                (p+i)->bNo = 0;
            }
        }
    }
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_TIMEPATTERN));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    sendArr.append(dataArr);

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
*/
//void PDataProcess::updateLocalTimePattern(quint8 index, bool bAdd, bool bEdit, bool bDel, TimePattern_Table *tbTimePattern)
//{
//    TimePattern_Table *p = &m_pTscInfo->tbTimePattern[index];
//    int tabSize = sizeof(TimePattern_Table);
//    if(bDel)
//    {
//        memset(p,0,tabSize);
//    }
//    else if(bAdd||bEdit)
//    {
//        memcpy(p,tbTimePattern,tabSize);
//    }

//    setListTimePatternName();
//}

/*
*/
//quint8 PDataProcess::getTimePatternIndex()
//{
//    TimePattern_Table *p = m_pTscInfo->tbTimePattern;
//    for(quint8 i=0;i<MAX_TIMEPATTERN_NUM;i++)
//    {
//        if(p->bNo==0)
//        {
//            return i;
//        }
//        p++;
//    }
//    return 0x80;
//}

/*
*/
void PDataProcess::setListTimePatternName()
{
    m_ListTimePatternName.clear();
    TimePattern_Table *p = m_pTscInfo->tbTimePattern;
    quint8 id;
    for(int i=0;i<MAX_TIMEPATTERN_NUM;i++)
    {
        id = p->bNo;
        if(id!=0)
        {
            m_ListTimePatternName.append(QObject::tr("方案")+QString::number(id));
        }
        p++;
    }
    m_pTscInfo->iTimePatternTableNum = m_ListTimePatternName.count();
}

/*
*/
void PDataProcess::dealTscStageTime(char*p,int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取阶段配时失败");
    }
    else if(*p==0x00)
    {
        strBar = tr("读取阶段配时成功");
        byte cntRow = *(++p);
        byte cntCol = *(++p);
//        qDebug()<<"stagetime:"<<cntRow<<cntCol;
        byte stageNo = 0;
        int tabSize = sizeof(StageTime_Table);
        StageTime_Table (*pStage)[MAX_STAGE_NUM];
        pStage = m_pTscInfo->tbStageTime;
        m_pTscInfo->initStageTimeTable();
        p++;//指向时段表数据开头
        for(byte r=0;r<cntRow;r++)
        {

            char *pLocal;
            pLocal = p + r*cntCol*tabSize;
            stageNo = *pLocal;//阶段配时号

            StageTime_Table* pRow = *(pStage + (stageNo-1));
            //定位 pLocal 指针
            for(byte c=0;c<cntCol;c++)
            {

                if(*pLocal!=0x00)
                {
                    StageTime_Table *pCol = pRow + c;
                    memcpy(pCol,pLocal,tabSize);//阶段配时表里的阶段 按 顺序存储
                    pLocal += tabSize;
                }
                else
                {
                    break;
                }
            }

        }
        analyseStageTimeTable();
    }
    setStatusBarMessage(strBar);
//    if(m_bFlagShowCluster)
//    {
//        getCTNodePatternInfo(m_ucCTPlanId);
//        quint8 stageId = m_ListCTNodeStagePattern.back();
//        //QList<quint8> listTime;
//        m_ListStageTime.clear();

//        getCTNodeStageList(stageId,&m_ListStageTime);
//        qDebug()<<"emit getCtNodeStage stageId"<<stageId<<m_ListStageTime.count();

//        emit getCtNodeStage();
//    }
    if(m_bFlagNodeIdChanged)
    {
        requireTscTable(TSC_TABLE_DETECTOR);

    }
}

void PDataProcess::analyseStageTimeTable()
{
    setListStageTimeName();//统计配时数 为vip数据存储
    emit rcvStageTimeTable();
}

/*
 */
bool PDataProcess::sendStageTimeToLib()
{
    if(m_pTscInfo!=NULL)
    {
        int cnt = 0 ;/*= m_pTscInfo->iStageTimeTableNum;*/
        int tabSize = sizeof(StageTime_Table);
        StageTime_Table (*p)[MAX_STAGE_NUM];
        p = m_pTscInfo->tbStageTime;

        quint32 type = CS_CMDTYPE_TSC_PARA_WRITE;//0x12写信号机
        quint32 num = 1;


        QByteArray dataArr;
        for(int i=0;i<MAX_STAGE_PATTERN_NUM;i++)
        {
            StageTime_Table *stage = *(p+i)+0;//行首地址
            if(stage->bStageNo!=0)
            {
                cnt++;
                for(int j=0;j<MAX_STAGE_NUM;j++)
                {
                    (stage+j)->bNo = i+1;
                }
                dataArr.append((char*)stage,tabSize*MAX_STAGE_NUM);
            }
        }
    qDebug()<<"sendStageTimeToLib cnt"<<cnt;
        quint32 size = 4+1+1+1+1+cnt*tabSize*MAX_STAGE_NUM;//nodeId+tableName + Para1 + row+col + data

        QByteArray sendArr;
        quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
        sendArr.append((char*)&nodeId,4);//节点Id

        sendArr.append(char(TSC_TABLE_STAGETIME));
        sendArr.append(char(DATA_TYPE_PARA));
        sendArr.append(char(cnt));
        sendArr.append(char(MAX_STAGE_NUM));
        sendArr.append(dataArr);
        if(sendMessage(type,num,size,sendArr))
        {
            setStatusBarMessage(tr("发送阶段配时成功"));
            return true;
        }
        else
        {
            setStatusBarMessage(tr("发送阶段配时失败"));
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool PDataProcess::getDataFromTableStage(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int cnt = 0 ;/*= m_pTscInfo->iStageTimeTableNum;*/
    int tabSize = sizeof(StageTime_Table);
    StageTime_Table (*p)[MAX_STAGE_NUM];
    p = pTsc->tbStageTime;

    quint32 type = CS_CMDTYPE_TSC_PARA_WRITE;//0x12写信号机
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    quint32 num = 1;


    QByteArray dataArr;
    for(int i=0;i<MAX_STAGE_PATTERN_NUM;i++)
    {
        StageTime_Table *stage = *(p+i)+0;//行首地址
        if(stage->bStageNo!=0)
        {
            cnt++;
            for(int j=0;j<MAX_STAGE_NUM;j++)
            {
                (stage+j)->bNo = i+1;
            }
            dataArr.append((char*)stage,tabSize*MAX_STAGE_NUM);
        }
    }
    quint32 size = 4+1+1+1+1+cnt*tabSize*MAX_STAGE_NUM;//nodeId+tableName + Para1 + row+col + data


    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_STAGETIME));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    sendArr.append(char(MAX_STAGE_NUM));
    sendArr.append(dataArr);

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
*/
//void PDataProcess::updateLocalStageTime(byte index, bool bAdd, bool bEdit, bool bDel)
//{
//    StageTime_Table (*p)[MAX_STAGE_NUM] ;
//    p = &m_pTscInfo->tbStageTime[index];
//    int tabSize = sizeof(StageTime_Table);

//    if(bAdd||bEdit)
//    {
//        memcpy(p,m_pStageTime,tabSize*MAX_STAGE_NUM);
//        if(bAdd)
//        {
//            m_pTscInfo->iStageTimeTableNum++;
//        }
//    }
//    else if(bDel)
//    {
//        memset(p,0,tabSize*MAX_STAGE_NUM);
//        m_pTscInfo->iStageTimeTableNum--;
//    }
//    //setListStageTimeName();
//}

/*
*/
//quint8 PDataProcess::getStageTimeIndex()
//{
//    StageTime_Table (*p)[MAX_STAGE_NUM] ;
//    p = m_pTscInfo->tbStageTime;
//    for(quint8 i=0;i<MAX_STAGE_PATTERN_NUM;i++)
//    {
//        StageTime_Table *pStage = *(p+i);
//        if(pStage->bStageNo==0)
//        {
//            return i;
//        }
//    }


//    return 0x80;
//}

/*
*/
void PDataProcess::setListStageTimeName()
{
    m_ListStageTimeName.clear();
    QString str = QObject::tr("配时");
    quint8 stagePatternId;
    StageTime_Table (*p)[MAX_STAGE_NUM] ;
    p = m_pTscInfo->tbStageTime;
    StageTime_Table *pStage;
    int tabSize = sizeof(StageTime_Table);
    for(int i=0;i<MAX_STAGE_PATTERN_NUM;i++)
    {
        pStage = *(p+i);
        stagePatternId = pStage->bNo;
        quint8 stageNo = pStage->bStageNo;
//        qDebug()<<"stageTimeId:"<<stagePatternId<<stageNo;
        if(stagePatternId!=0&&stageNo!=0)
        {
            m_ListStageTimeName.append(str+QString::number(stagePatternId));
        }
    }
    m_pTscInfo->iStageTimeTableNum = m_ListStageTimeName.count();

    if(m_mapVip.contains(m_uiCurNodeId))
    {
        m_mapVip[m_uiCurNodeId]->listStage.clear();
        StageTime_Table *pVipStage = m_pTscInfo->tbStageTime[0];//配时1
        QList<quint16> list;
        for(int i=0;i<MAX_STAGE_NUM;i++)
        {
            if(pVipStage->bNo!=0&&pVipStage->bStageNo!=0)
            {
                list.append(pVipStage->uEnablePhase);
                pVipStage++;
            }
            else
            {
                break;
            }
        }
//        qDebug()<<"stageTime change list cnt:"<<list.count();
        m_mapVip[m_uiCurNodeId]->listStage.append(list);
    }
    else
    {
        qDebug()<<"m_mapVip not contains"<<m_uiCurNodeId;
    }

//    m_bFlagStageTimeName = true;
//    setModelItem();
}

/*
*/
//void PDataProcess::setStageTime(StageTime_Table *p)
//{
//    m_pStageTime = p;
//}

/*
*/
void PDataProcess::dealTscPhaseConflictTable(unsigned char *p, int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取冲突相位表失败");
    }
    else if(*p==0x00)
    {
        strBar = tr("读取冲突相位表成功");
        PhaseConflict_Table *pBase = m_pTscInfo->tbPhaseConflict;
        int tbSize = sizeof(PhaseConflict_Table);
        memset(pBase,0,MAX_CONFLICT_NUM*tbSize);
        quint8 cnt = *(++p);
        if(cnt>MAX_CONFLICT_NUM)
        {
            cnt = MAX_CONFLICT_NUM;
        }
        for(int i=0;i<cnt;i++)
        {
            quint8 id = *(++p);
            if(id>0&&id<(MAX_CONFLICT_NUM+1))
            {
                PhaseConflict_Table *pConflict = pBase+id-1;
                pConflict->bNo =  id;
                pConflict->uConflictPhase = qFromBigEndian<quint16>(++p);
                p++;
            }
            else
            {
                p+=2;
            }
        }
        emit rcvConflict();
    }
    setStatusBarMessage(strBar);
    if(m_bFlagNodeIdChanged)
    {
        requireTscTable(TSC_TABLE_PHASE);
    }
}

/*
*/
bool PDataProcess::sendPhaseConflictTable()
{
    if(m_pTscInfo!=NULL)
    {
        int tabSize = sizeof(PhaseConflict_Table);
        int cnt = MAX_CONFLICT_NUM;

        int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
        int num = 1;
        int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

        QByteArray sendArr;
        quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
        sendArr.append((char*)&nodeId,4);//节点Id

        sendArr.append(char(TSC_TABLE_PHASECONFLICT));
        sendArr.append(char(DATA_TYPE_PARA));
        sendArr.append(char(cnt));
        PhaseConflict_Table* pBase = m_pTscInfo->tbPhaseConflict;

        for(int i=0;i<MAX_CONFLICT_NUM;i++)
        {
            PhaseConflict_Table* p = pBase+i;
            sendArr.append(char(i+1));
            quint16 conflict = qToBigEndian<quint16>(p->uConflictPhase);
            sendArr.append((char*)&conflict,2);
        }
    //qDebug()<<"sendPhaseConflictTable";
        if(sendMessage(type,num,size,sendArr))
        {
            setStatusBarMessage(tr("发送冲突相位表成功"));
            return true;
        }
        else
        {
            setStatusBarMessage(tr("发送冲突相位表失败"));
            return false;
        }
    }
    else
    {
        return false;
    }

}

bool PDataProcess::getDataFromTableConflict(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int tabSize = sizeof(PhaseConflict_Table);
    int cnt = MAX_CONFLICT_NUM;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data


    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_PHASECONFLICT));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    PhaseConflict_Table* pBase = pTsc->tbPhaseConflict;

    for(int i=0;i<MAX_CONFLICT_NUM;i++)
    {
        PhaseConflict_Table* p = pBase+i;
        sendArr.append(char(i+1));
        quint16 conflict = qToBigEndian<quint16>(p->uConflictPhase);
        sendArr.append((char*)&conflict,2);
    }

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
*/
void PDataProcess::dealTscPhaseTable(char *p, int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取相位表失败");
    }
    else if(*p==0x00)
    {
        quint8 cnt = *(++p);
        qDebug()<<"phase cnt"<<cnt;
        m_pTscInfo->iPhaseTableNum = cnt;
        int tabSize = sizeof(Phase_Table);
        Phase_Table *phaseBase = m_pTscInfo->tbPhase;
        p++;//指向数据
        memcpy(phaseBase,p,cnt*tabSize);
        strBar = tr("读取相位表成功");
    }

    setStatusBarMessage(strBar);
    if(!m_bFlagReadIni)
    {
        requireTscTable(TSC_TABLE_OVERLAP);
    }
}

/*
*/
bool PDataProcess::sendPhaseTableToLib()
{
    if(m_pTscInfo!=NULL)
    {
        int tabSize = sizeof(Phase_Table);
        int cnt = MAX_PHASEMAP_NUM;

        int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
        int num = 1;
        int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

        QByteArray sendArr;
        quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
        sendArr.append((char*)&nodeId,4);//节点Id

        sendArr.append(char(TSC_TABLE_PHASE));
        sendArr.append(char(DATA_TYPE_PARA));
        sendArr.append(char(cnt));
        Phase_Table* p = m_pTscInfo->tbPhase;

        sendArr.append((char*)p,cnt*tabSize);

        if(sendMessage(type,num,size,sendArr))
        {
            setStatusBarMessage(tr("发送普通相位表成功"));
            return true;
        }
        else
        {
            setStatusBarMessage(tr("发送普通相位表失败"));
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool PDataProcess::getDataFromTablePhase(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int tabSize = sizeof(Phase_Table);
    int cnt = MAX_PHASEMAP_NUM;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_PHASE));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    Phase_Table* p = pTsc->tbPhase;

    sendArr.append((char*)p,cnt*tabSize);

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
*/
void PDataProcess::dealTscOverlapTable(char *p, int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取跟随相位表失败");
    }
    else if(*p==0x00)
    {
        strBar = tr("读取跟随相位表成功");
        quint8 cnt = *(++p);
        qDebug()<<"overlap cnt"<<cnt;
        m_pTscInfo->iOverlapTableNum = cnt;
        int tabSize = sizeof(Overlap_Table);
        Overlap_Table *overlapBase = m_pTscInfo->tbOverlap;
        p++;//指向数据
        memcpy(overlapBase,p,cnt*tabSize);
    }
    setStatusBarMessage(strBar);
    if(!m_bFlagReadIni)
    {
        requireTscTable(TSC_TABLE_CHANNEL);
    }
}

/*
*/
bool PDataProcess::sendOverlapToLib()
{
    int tabSize = sizeof(Overlap_Table);
    int cnt = MAX_OVERLAP_NUM;//m_pTscInfo->iOverlapTableNum;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 1;
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_OVERLAP));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    Overlap_Table* p = m_pTscInfo->tbOverlap;

    sendArr.append((char*)p,cnt*tabSize);

    if(sendMessage(type,num,size,sendArr))
    {
        setStatusBarMessage(tr("发送跟随相位表成功"));
        return true;
    }
    else
    {
        setStatusBarMessage(tr("发送跟随相位表失败"));
        return false;
    }
}

bool PDataProcess::getDataFromTableOverlap(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int tabSize = sizeof(Overlap_Table);
    int cnt = MAX_OVERLAP_NUM;//m_pTscInfo->iOverlapTableNum;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_OVERLAP));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    Overlap_Table* p = pTsc->tbOverlap;

    sendArr.append((char*)p,cnt*tabSize);

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
*/
void PDataProcess::dealTscChannelTable(char *p, int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取通道表失败");
    }
    else if(*p==0x00)
    {
        strBar = tr("读取通道表成功");
        quint8 cnt = *(++p);
        qDebug()<<"channel cnt"<<cnt;
        m_pTscInfo->iChannelTableNum = cnt;
        int tabSize = sizeof(Channel_Table);
        Channel_Table *channelBase = m_pTscInfo->tbChannel;
        p++;//指向数据
        if(cnt>MAX_CHANNEL_NUM)
        {
            cnt = MAX_CHANNEL_NUM;
        }
        memcpy(channelBase,p,cnt*tabSize);
    }
    setStatusBarMessage(strBar);
    if(!m_bFlagReadIni)
    {
        requireTscTable(TBL_TABLE_PHASE2DIREC);
    }
}

/*
*/
bool PDataProcess::sendChannelToLib()
{
    int tabSize = sizeof(Channel_Table);
    int cnt = 0;//MAX_CHANNEL_NUM;//m_pTscInfo->iChannelTableNum;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 1;

    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_CHANNEL));
    sendArr.append(char(DATA_TYPE_PARA));

    QByteArray dataArr;
    Channel_Table* p = m_pTscInfo->tbChannel;
    for(int i=0;i<MAX_CHANNEL_NUM;i++)
    {
        quint8 phase = (p+i)->bControlSource;
        if(phase!=0)
        {
            dataArr.append((char*)(p+i),tabSize);
            cnt++;
        }
    }

    sendArr.append(char(cnt));

    sendArr.append(dataArr/*(char*)p,cnt*tabSize*/);


    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    if(sendMessage(type,num,size,sendArr))
    {
        setStatusBarMessage(tr("发送通道表成功"));
        return true;
    }
    else
    {
        setStatusBarMessage("发送通道表失败");
        return false;
    }
}

bool PDataProcess::getDataFromTableChannel(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int tabSize = sizeof(Channel_Table);
    int cnt = 0;//MAX_CHANNEL_NUM;//m_pTscInfo->iChannelTableNum;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_CHANNEL));
    sendArr.append(char(DATA_TYPE_PARA));

    QByteArray dataArr;
    Channel_Table* p = pTsc->tbChannel;
    for(int i=0;i<MAX_CHANNEL_NUM;i++)
    {
        quint8 phase = (p+i)->bControlSource;
        if(phase!=0)
        {
            dataArr.append((char*)(p+i),tabSize);
            cnt++;
        }
    }

    sendArr.append(char(cnt));

    sendArr.append(dataArr/*(char*)p,cnt*tabSize*/);


    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
*/
void PDataProcess::dealTscPhaseMapTable(char *p, int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取相位映射表失败");
    }
    else if(*p==0x00)
    {
        strBar = tr("读取相位映射表成功");
        quint8 cnt = *(++p);
        qDebug()<<"phase map cnt"<<cnt;
        m_pTscInfo->iPhaseMapTableNum = cnt;
        int tabSize = sizeof(PhaseMap_Table);
        PhaseMap_Table *phaseMapBase = m_pTscInfo->tbPhaseMap;
        p++;//指向数据

        memset(phaseMapBase,0,tabSize*MAX_PHASEMAP_NUM);
        memcpy(phaseMapBase,p,cnt*tabSize);
    }
    setStatusBarMessage(strBar);
    if(m_pTscInfo!=NULL)
    {
        analysePhaseMapTable(m_pTscInfo->tbPhaseMap,m_pTscInfo->tbChannel);
    }

    if(m_bFlagNodeIdChanged)
    {
        requireTscTable(TSC_TABLE_TIMEBASE);

    }
    //m_bFlagNodeIdChanged = false;
}

void PDataProcess::analysePhaseMapTable(PhaseMap_Table *map,Channel_Table* channel)
{
    if(map==NULL)
    {
        map = m_pTscInfo->tbPhaseMap;
    }
    if(channel==NULL)
    {
        channel = m_pTscInfo->tbChannel;
    }
    setListMapData(map,channel);
}
/*
*/
bool PDataProcess::sendPhaseMapToLib()
{
    if(m_pTscInfo!=NULL)
    {

        int tabSize = sizeof(PhaseMap_Table);
        int cnt = 0;/*MAX_PHASEMAP_NUM;*/

        int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
        int num = 1;

        QByteArray sendArr;
        quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
        sendArr.append((char*)&nodeId,4);//节点Id

        sendArr.append(char(TBL_TABLE_PHASE2DIREC));
        sendArr.append(char(DATA_TYPE_PARA));
        PhaseMap_Table* p = m_pTscInfo->tbPhaseMap;

        QByteArray dataArr;
        for(int i=0;i<MAX_PHASEMAP_NUM;i++)
        {
            if((p+i)->bPhaseIconId!=0)
            {
                dataArr.append((char*)(p+i),tabSize);
                cnt++;
            }
        }
        sendArr.append(char(cnt));
        sendArr.append(dataArr);

        int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

        if(sendMessage(type,num,size,sendArr))
        {
            setStatusBarMessage(tr("发送相位映射表成功"));
            return true;
        }
        else
        {
            setStatusBarMessage(tr("发送相位映射表失败"));
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool PDataProcess::getDataFromTablePhaseMap(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{int tabSize = sizeof(PhaseMap_Table);
    int cnt = 0;/*MAX_PHASEMAP_NUM;*/

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;

    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TBL_TABLE_PHASE2DIREC));
    sendArr.append(char(DATA_TYPE_PARA));
    PhaseMap_Table* p = pTsc->tbPhaseMap;

    QByteArray dataArr;
    for(int i=0;i<MAX_PHASEMAP_NUM;i++)
    {
        if((p+i)->bPhaseIconId!=0)
        {
            dataArr.append((char*)(p+i),tabSize);
            cnt++;
        }
    }
    sendArr.append(char(cnt));
    sendArr.append(dataArr);

    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
*/
void PDataProcess::setListMapData(PhaseMap_Table *map,Channel_Table* channel)
{
//    PhaseMap_Table *map = m_pTscInfo->tbPhaseMap;//方向
//    Channel_Table* channel = m_pTscInfo->tbChannel;
    QList<quint8> chlList;
//    m_ListOverlapMap.clear();
//    m_ListComMap.clear();
    m_ListChannelMap.clear();
    for(int i=0;i<16;i++)
    {
       // m_ListLoadNum<<(map+i)->bLaneNum;
        qDebug()<<"load num:"<<i<<(map+i)->bLaneNum;
        quint8 comphaseId = (map+i)->bCommonPhaseNo;
        quint8 overlapId = (map+i)->bOverlapPhaseNo;
        //qDebug()<<"rcv phase id:"<<comphaseId<<overlapId;
        quint8 phaseBase = (channel+i)->bControlType==4?32:0;//1-32为普通相位 32-40为跟随相位
        quint8 phaseId = (channel+i)->bControlSource;
        chlList<<phaseId+phaseBase;//通道1-16对应的相位
        //m_ListLoadMap.append(phaseId+phaseBase);//1-16通道对应 的相位
//        m_ListPhaseMap.append(phaseId);
        if(overlapId!=0)
        {
           // m_ListPhaseMap<<overlapId+32;//方向1-16对应的相位值 不区分 普通 跟随
            m_ListOverlapMap<<overlapId;//方向1-16对应的跟随相位
            m_ListComMap<<0;
        }
        else
        {
           // m_ListPhaseMap<<comphaseId;//
            m_ListOverlapMap<<0;
            m_ListComMap<<comphaseId;//方向1-16对应的普通相位

        }
    }

    //方向对应通道1-16 方向 对应的 通道值
    for(int i=0;i<16;i++)
    {
        quint8 id;
        if(m_ListComMap[i]!=0)
        {
            id = m_ListComMap[i];
            if(chlList.contains(id))
            {
                for(int chlIndex=0;chlIndex<16;chlIndex++)
                {
                    if(chlList[chlIndex]==id)
                    {
                        if(!m_ListChannelMap.contains(chlIndex+1))
                        {
                            m_ListChannelMap<<chlIndex+1;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            else
            {
                m_ListChannelMap<<0;
            }
        }
        else if(m_ListOverlapMap[i]!=0)
        {
            id = m_ListOverlapMap[i];
            if(chlList.contains(id+32))
            {
                for(int chlIndex=0;chlIndex<16;chlIndex++)
                {
                    if(chlList[chlIndex]==id+32)
                    {
                        if(!m_ListChannelMap.contains(chlIndex+1))
                        {
                            m_ListChannelMap<<chlIndex+1;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            else
            {
                m_ListChannelMap<<0;
            }
        }
        else
        {
            m_ListChannelMap<<0;
        }
    }
    //--------------------

    m_ListLoadNum.clear();//20个
    m_ListLoadMap.clear();//
    m_ListPhaseMap.clear();//20个
    m_ListLoadNo.clear();
    m_ListValid.clear();//20个
    for(int i=0;i<20;i++)
    {
        m_ListLoadNum.append(0);
        m_ListPhaseMap.append(0);
        m_ListValid.append(false);
    }
    for(int i=0;i<MAX_CHANNEL_NUM;i++)
    {
        quint8 phaseId = (channel+i)->bControlSource;
        phaseId += (channel+i)->bControlType==4?32:0;
        m_ListLoadMap.append(phaseId);
    }

    m_ucDir = 0;
    for(int i=0;i<MAX_PHASEMAP_NUM;i++)
    {
        quint8 loadNo = (map+i)->bPhaseIconId;
        if(loadNo>0x1f)
        {
            quint8 dir = (loadNo>>5);
            if(dir>0&&dir<5)
            {
                quint8 d = qPow(2,(4-dir)*2+1);
                m_ucDir |= d;
            }
            m_ListLoadNo.append(loadNo);
        }

        quint8 overlap = (map+i)->bOverlapPhaseNo;
        quint8 com = (map+i)->bCommonPhaseNo;
        quint8 num = (map+i)->bLaneNum;
        int index = getListIconIndex(loadNo);
        qDebug()<<"analyse phase overlap"<<overlap<<index<<loadNo;
        if(index>-1&&index<20)
        {
            m_ListLoadNum[index] = num;
            if(com>0&&com<(MAX_PHASE_NUM+1))
            {
                m_ListPhaseMap[index] = com;
            }
            else if(overlap>0&&overlap<(MAX_OVERLAP_NUM+1))
            {
                m_ListPhaseMap[index] = overlap+32;
            }
//            m_ListPhaseMap[index] = overlap!=0?overlap+32:com;
            m_ListValid[index] = true;
            qDebug()<<"valid-----------------"<<index<<true;
        }
    }
    qDebug()<<tr("m_ucDir 0x%1").arg(m_ucDir,2,16);


    //qDebug()<<"m_ListChannelMap"<<&m_ListChannelMap;
    if(m_mapVip.contains(m_uiCurNodeId))
    {
//        m_mapVip[m_uiCurNodeId]->listChannelMap.clear();
//        m_mapVip[m_uiCurNodeId]->listComMap.clear();
//        m_mapVip[m_uiCurNodeId]->listOverlapMap.clear();
        m_mapVip[m_uiCurNodeId]->init();
        m_mapVip[m_uiCurNodeId]->m_ListLoadMap.append(m_ListLoadMap);
        m_mapVip[m_uiCurNodeId]->m_ListLoadNo.append(m_ListLoadNo);
        m_mapVip[m_uiCurNodeId]->m_ListLoadNum.append(m_ListLoadNum);
        m_mapVip[m_uiCurNodeId]->m_ListPhaseMap.append(m_ListPhaseMap);
        m_mapVip[m_uiCurNodeId]->m_ListValid.append(m_ListValid);

        m_mapVip[m_uiCurNodeId]->listChannelMap.append(m_ListChannelMap);
        m_mapVip[m_uiCurNodeId]->listComMap.append(m_ListComMap);
        m_mapVip[m_uiCurNodeId]->listOverlapMap.append(m_ListOverlapMap);
        m_mapVip[m_uiCurNodeId]->m_ucDir = m_ucDir;
    }
  //  qDebug()<<"m_ListChannelMap"<<&m_ListChannelMap;
    emit rcvPhase();
}

int PDataProcess::getListIconIndex(quint8 loadNo)
{
    if(loadNo>31)
    {
        int listIndex = -1;
        int dir = (loadNo>>5)-1;
        if((loadNo&0x18)!=0)//人行
        {
            if((loadNo&0x07)!=2)//0,1
            {
                listIndex = dir*4+3;
            }
            else//2次
            {
                listIndex = dir+MAX_PHASEMAP_NUM;
            }
        }
        else
        {
            switch(loadNo&0x07)
            {
            case 1:
                listIndex = dir*4;
                break;
            case 2:
            case 3:
            case 6:
            case 7:
                listIndex = dir*4+1;
                break;
            case 4:
                listIndex = dir*4+2;
                break;
            default:
                break;
            }
        }
        if(listIndex<20)//所有路标20
        {
            return listIndex;
        }
        else
        {
            return -1;
        }
    }
    else if(loadNo>0&&loadNo<17)
    {
        return loadNo-1;
    }
    else
    {
        return -1;
    }

}

void PDataProcess::changeNode()
{
    analyseModuleTable();
//    qDebug()<<"changeNode2";
    analysePhaseMapTable();
//    qDebug()<<"changeNode3";
    analyseTimeBaseTable();
//    qDebug()<<"changeNode4";
    analyseScheduleTable();
//    qDebug()<<"changeNode5";
    analyseTimePatternTable();
//    qDebug()<<"changeNode6";
    analyseStageTimeTable();
    analyseDetectorTable();
//    qDebug()<<"changeNode7";
}

/*
*/
void PDataProcess::setBeginCheck(bool &b)
{
    m_bBeginCheck = b;
}

/*
*/
bool PDataProcess::sendCheckTimeToTsc(quint32 t)
{qDebug()<<"check time-------------=========================================================------------------";
    int type = CS_CMDTYPE_TSC_CONTROL_COMMAND; //= 0x17,	//TSC控制命令
    int num = 1;
    int size = 4+1+1+4;//nodeId4+tableName1 + Para1 1 + data4
//    if(t!=0)
//        t+=3600*8;
    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_COMMAND_UTC_TIME));
    sendArr.append(char(DATA_TYPE_PARA));
    quint32 time = qToBigEndian<quint32>(t);
    qDebug()<<"sendCheckTimeToTsc time"<<time<<"t"<<t;
    sendArr.append((char*)&time,4);//时间


    return sendMessage(type,num,size,sendArr);
}

/*
*/
bool PDataProcess::requireAutoReport(quint8 cmd, quint16 t,quint32 id)
{
    int type = CS_CMDTYPE_TSC_AUTOREPORT_TAILOR; //= 0x17,	//TSC控制命令
    int num = 1;
    int size = 4+1+1+4;//nodeId4+tableName1 + Para1 1 + 行数1+订制值1+时间间隔2

    bool b = false;
    if(t!=0)
    {
        b = true;
    }
    switch(cmd)
    {
        case 0xf8:
            m_bFlagAutoReport = b;
            break;
        case TSC_STATUS_DETECTORSTS:
            m_bFlagDetAutoReport = b;
            break;
        default:
            break;
    }

    QByteArray sendArr;
    quint32 nodeId ;
    if(id==0)
    {
        nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    }
    else
    {
        nodeId = qToBigEndian<quint32>(id);
    }

    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_COMMAND_REPORTSELF));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(1));//行数
    sendArr.append(char(cmd));//订制值
//    quint16 time = htons(t);
    quint16 time = qToBigEndian<quint16>(t);
    sendArr.append((char*)&time,2);//间隔时间


    return sendMessage(type,num,size,sendArr);
}

void PDataProcess::shutdownAutoReport()
{qDebug()<<"shutdownAutoReport---------------------------------------------------------";
    if(m_bFlagAutoReport)
    {
        qDebug()<<"shutdownAutoReport real";
        requireAutoReport(0xf8,0);
        emit cbFlashStatus(false);
    }
    if(m_bFlagDetAutoReport)
    {
        qDebug()<<"shutdownAutoReport det";
        requireAutoReport(TSC_STATUS_DETECTORSTS,0);
        emit cbDetStatus(false);
    }
}

/*
*/
bool PDataProcess::requireTscTime()
{
    int type = CS_CMDTYPE_TSC_PARA_READ ;//(0x10)
    int num = 1;
    int size = 4+1;//nodeId4+cmd1

    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_COMMAND_UTC_TIME ));//(0X86)

    if( sendMessage(type,num,size,sendArr))
    {
//        this->setStatusBarMessage(tr("发送要求信号机时间成功"));
        return true;
    }
    else
    {
        this->setStatusBarMessage(tr("发送要求信号机时间失败"));
        return false;
    }
}

/*
*/
bool PDataProcess::sendCtrolCmd(quint32 t, quint8 cmd, quint8 para2)
{qDebug()<<"sendCtrolCmd--------------------------------";
    int type = t; 	//TSC控制命令
    int num = 1;
    int size = 4+1+1+1;//nodeId4+tableName1 +cmd 1+ Para1 1 + para2 1

    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(cmd));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(para2));



    return sendMessage(type,num,size,sendArr);
}

/*
*/
void PDataProcess::dealTscDetectorTable(unsigned char *para1, int)
{
    QString strBar;
    if(*para1==0)
    {
        strBar = tr("读取检测器表成功");
        int cnt = *(++para1);
        m_pTscInfo->iDetectorTableNum = cnt;
        Detector_Table *p = m_pTscInfo->tbDetector;
        int tbSize = sizeof(Detector_Table);

        memset(p,0,tbSize*MAX_DETECTOR_NUM);
        for(int i=0;i<MAX_DETECTOR_NUM;i++)
        {
            (p+i)->bNo = i+1;
        }

        para1++;
        for(int i=0;i<cnt;i++)
        {
            int index = *para1-1;//检测器号
            memcpy(p+index,para1,tbSize);
            para1+=tbSize;
        }
    }
    else
    {
        strBar = tr("读取检测器表失败");
    }
    analyseDetectorTable();
    setStatusBarMessage(strBar);

    if(m_bFlagNodeIdChanged)
    {
        requireAllTscTable();
    }

}

void PDataProcess::analyseDetectorTable()
{
    if(m_bFlagShowDetector)
    emit rcvDet();
}

/*
*/
bool PDataProcess::sendDetectorToLib()
{
    int tabSize = sizeof(Detector_Table);
    int cnt = MAX_DETECTOR_NUM;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 1;
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data

    QByteArray sendArr;
    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_DETECTOR));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    Detector_Table* p = m_pTscInfo->tbDetector;

    sendArr.append((char*)p,cnt*tabSize);

    if(sendMessage(type,num,size,sendArr))
    {
        setStatusBarMessage(tr("发送检测器表成功"));
        return true;
    }
    else
    {
        setStatusBarMessage(tr("发送检测器表失败"));
        return false;
    }
}

bool PDataProcess::getDataFromTableDet(STscInfo *pTsc, QByteArray &sendArr, bool bType)
{
    int tabSize = sizeof(Detector_Table);
    int cnt = MAX_DETECTOR_NUM;

    int type = CS_CMDTYPE_TSC_PARA_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    if(!bType)
    {
        type = CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE;
    }
    int num = 1;
    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data


    quint32 nodeId = qToBigEndian<quint32>(m_uiCurNodeId);
    sendArr.append((char*)&nodeId,4);//节点Id

    sendArr.append(char(TSC_TABLE_DETECTOR));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    Detector_Table* p = pTsc->tbDetector;

    sendArr.append((char*)p,cnt*tabSize);
    htonlHead(type,num,size);
    sendArr.insert(0,(const char*)m_pSendMsgHead,m_iheadSize);
    if(cnt>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
*/
void PDataProcess::dealTscDetAlarmTalbe(unsigned char *para1, int len)
{
    if(*para1==0)
    {
        para1++;
        quint8 cnt = *para1;
        para1++;
        int tbSize = sizeof(DetectorAlarm_Table);
        DetectorAlarm_Table *p = m_pTscInfo->tbDetectorAlarm;
        memset((char*)p,0,tbSize*MAX_DETECTOR_NUM);

        if(len==(cnt*tbSize+2))
        {
            memcpy((unsigned char*)p,para1,tbSize*cnt);
            emit rcvDetAlarm();
        }
        else
        {
            qDebug()<<"data len err"<<len<<"cnt:"<<cnt<<tbSize;
        }
    }
}

/*
*/
void PDataProcess::dealTscEventLogTalbe(unsigned char *para1, int len)
{
    QString strBar;
    if(*para1==0)
    {
        strBar = tr("读取日志事件表成功");
        para1++;
        quint32 cnt = 0;

        memcpy(&cnt,para1,4);//日志条数 4个字节
        cnt = qFromBigEndian<quint32>(cnt);
        //quint8 cnt = *para1;
        para1+=4;
        int tbSize = sizeof(EventLog_Table);
        EventLog_Table *pBase = m_pTscInfo->tbEventLog;
        memset((unsigned char*)pBase,0,tbSize*MAX_EVENTLOG_NUM);

        QString nodeName;
        int idIndex;
        if(m_iEventIndex == -1)
        {
            idIndex  = m_TscIdList.indexOf(QString::number(m_uiCurNodeId));
        }
        else
        {
            idIndex = m_iEventIndex;
        }
        if(idIndex!=-1)
        {
            nodeName = m_TscNameList[idIndex];
        }
        if(len==(cnt*tbSize+5))
        {
            qDebug()<<"deal event log";
            //memcpy((unsigned char*)pBase,para1,tbSize*cnt);
//            m_pModelEventLog->removeRows(0,m_pModelEventLog->rowCount(QModelIndex()),QModelIndex());
            QStringList list;
            int eventLogCnt = 0;
            for(quint32 i=0;i<cnt;i++)
            {
                EventLog_Table *p = (EventLog_Table*)para1+i;
                list.clear();
//                list<<tr("事件%1").arg(p->bEventTypeNo);
                list<<nodeName;

                //qDebug()<<i<<p->bEventTypeNo;
                quint8 type = p->bEventNo;
                quint32 time = qFromBigEndian<quint32>(p->lEventTime);
                time-=3600*8;
                if(m_uiEventLogEnd>0)
                {
//                    qDebug()<<time-m_uiEventLogStart<<m_uiEventLogEnd-time;
                    if(time<m_uiEventLogStart||time>m_uiEventLogEnd)
                    {//qDebug()<<"contine";
                        continue;
                    }
                }

                QDateTime date = QDateTime::fromTime_t(time);
//                QDateTime newDate = date.addSecs(-3600*8);
                list<<date.toString("yyyy-MM-dd hh:mm:ss");

                quint32 data = p->lEventData;
                quint8 *dp = (quint8*)(&data);
                QString valueStr;
                switch(type)
                {
                case 0:
                    {
                        valueStr = QObject::tr("信号灯%1").arg(*dp);
                        switch(*(dp+1))
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("长亮");
                            break;
                        case 2:
                            valueStr += QObject::tr("长灭");
                            break;
                        case 3:
                            valueStr += QObject::tr("可控硅击穿");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 1:
                    {
                        valueStr = QObject::tr("绿冲突 ");
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("绿灯%1").arg(*(dp+1))+QObject::tr("长亮");
                            break;
                        case 1:
                            valueStr += QObject::tr("没有红灯亮的相位组");
                            break;
                        case 2:
                            valueStr += QObject::tr("根据相位冲突表判别的相位冲突");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 2:
                    {
                        valueStr = QObject::tr("检测器%1").arg(*dp);
                        switch(*(dp+1))
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("线圈开路");
                            break;
                        case 2:
                            valueStr += QObject::tr("线圈短路");
                            break;
                        case 3:
                            valueStr += QObject::tr("通道停振");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 3:
                    {
                        valueStr = QObject::tr("电压:%1V").arg(*(dp+1));
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("偏低");
                            break;
                        case 2:
                            valueStr += QObject::tr("偏高");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 4:
                    {
                        valueStr = QObject::tr("温度:%1度").arg(qint8(*(dp+1)-127));
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("偏低,需要加热");
                            break;
                        case 2:
                            valueStr += QObject::tr("偏高,需要散热");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 5:
                    {
                        valueStr = QObject::tr("电源板");
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("与主板通信异常:");
                            switch(*(dp+1))
                            {
                            case 0:
                                valueStr += QObject::tr("长时间没有数据通信");
                                break;
                            case 1:
                                valueStr += QObject::tr("长时间数据错误,地址错误");
                                break;
                            case 2:
                                valueStr += QObject::tr("长时间数据错误,校验错误");
                                break;
                            default:
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 6:
                    {
                        valueStr = QObject::tr("灯控板%1").arg(*(dp+2));
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("与主板通信异常:");
                            switch(*(dp+1))
                            {
                            case 0:
                                valueStr += QObject::tr("长时间没有数据通信");
                                break;
                            case 1:
                                valueStr += QObject::tr("长时间数据错误,地址错误");
                                break;
                            case 2:
                                valueStr += QObject::tr("长时间数据错误,校验错误");
                                break;
                            default:
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 7:
                    {
                        valueStr = QObject::tr("检测器接口板%1").arg(*(dp+2));
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("与主板通信异常:");
                            switch(*(dp+1))
                            {
                            case 0:
                                valueStr += QObject::tr("长时间没有数据通信");
                                break;
                            case 1:
                                valueStr += QObject::tr("长时间数据错误,地址错误");
                                break;
                            case 2:
                                valueStr += QObject::tr("长时间数据错误,校验错误");
                                break;
                            default:
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 8:
                    {
                        valueStr = QObject::tr("黄闪器");
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("正常");
                            break;
                        case 1:
                            valueStr += QObject::tr("与主板通信异常:");
                            switch(*(dp+1))
                            {
                            case 0:
                                valueStr += QObject::tr("长时间没有数据通信");
                                break;
                            case 1:
                                valueStr += QObject::tr("长时间数据错误,地址错误");
                                break;
                            case 2:
                                valueStr += QObject::tr("长时间数据错误,校验错误");
                                break;
                            default:
                                break;
                            }
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 9:
                    {
                        valueStr += QObject::tr("程序重启");
                        break;
                    }
                case 10:
                    {
                        valueStr += QObject::tr("时间修改为:");
                        quint32 t = qFromBigEndian<quint32>(p->lEventData);
                        QDateTime newDate = QDateTime::fromTime_t(t);
                        valueStr += newDate.toString("yyyy-MM-dd hh:mm:ss");
                        break;
                    }
                case 11:
                    {
                        valueStr += QObject::tr("门");
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("关");
                            break;
                        case 1:
                            valueStr += QObject::tr("开");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 12:
                    {
                        valueStr += QObject::tr("信号机手动控制:");
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("手动");
                            break;
                        case 1:
                            valueStr += QObject::tr("去掉手动");
                            break;
                        case 2:
                            valueStr += QObject::tr("黄闪");
                            break;
                        case 3:
                            valueStr += QObject::tr("去掉黄闪");
                            break;
                        case 4:
                            valueStr += QObject::tr("全红");
                            break;
                        case 5:
                            valueStr += QObject::tr("去掉全红");
                            break;
                        case 6:
                            valueStr += QObject::tr("步进");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 13:
                    {
                        valueStr += QObject::tr("灯控板输出信息异常");
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("正常灯色异常");
                            break;
                        case 1:
                            valueStr += QObject::tr("闪烁灯色异常");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 14:
                    {
                        valueStr += QObject::tr("灯控板输出信息异常");
                        switch(*dp)
                        {
                        case 0:
                            valueStr += QObject::tr("广播地址错误");
                            break;
                        case 1:
                            valueStr += QObject::tr("某个等组亮多于一盏");
                            break;
                        case 2:
                            valueStr += QObject::tr("黄闪");
                            break;
                        case 3:
                            valueStr += QObject::tr("多于8个绿灯亮");
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                case 15:
                {
                    valueStr += QObject::tr("控制方式切换");
                    switch(*dp)
                    {
                    case 0:
                        valueStr += QObject::tr("广播地址错误");
                        break;
                    case 1:
                        valueStr += QObject::tr("多时段");
                        break;
                    case 2:
                        valueStr += QObject::tr("系统优化，即联网");
                        break;
                    case 3:
                        valueStr += QObject::tr("无电线缆协调");
                        break;
                    case 4:
                        valueStr += QObject::tr("有线电缆协调");
                        break;
                    case 5:
                        valueStr += QObject::tr("主从线控");
                        break;
                    case 6:
                        valueStr += QObject::tr("手动控制");
                        break;
                    case 7:
                        valueStr += QObject::tr("单点全感应");
                        break;
                    case 8:
                        valueStr += QObject::tr("单点主线优先半感应");
                        break;
                    case 9:
                        valueStr += QObject::tr("单点次线优先半感应");
                        break;
                    case 10:
                        valueStr += QObject::tr("自适应");
                        break;
                    case 11:
                        valueStr += QObject::tr("面板控制");
                        break;
                    default:
                        break;
                    }
                    break;
                }
                default:
                    valueStr += QObject::tr("无法解析%1").arg(type);
                    break;
                }
                list<<valueStr;
                //qDebug()<<list[0]<<list[1]<<i<<list[2];
                bool bContain = true;
                if(!m_ListEventLogSearch.isEmpty())
                {//qDebug()<<"!m_ListEventLogSearch.isEmpty()"<<m_ListEventLogSearch<<"str"<<m_ListEventLogSearch.count();
                    bContain = false;
                    QString strWord = list[2];
                    foreach(QString search,m_ListEventLogSearch)
                    {
                        if(strWord.contains(search))
                        {
                            bContain = true;
                        }
                    }
                }
                if(bContain)
                {
                    m_pModelEventLog->insertRows(eventLogCnt,1,QModelIndex());
                    m_pModelEventLog->setData(m_pModelEventLog->index(eventLogCnt,0,QModelIndex()),list.value(0),Qt::DisplayRole);
                    m_pModelEventLog->setData(m_pModelEventLog->index(eventLogCnt,1,QModelIndex()),list.value(1),Qt::DisplayRole);
                    m_pModelEventLog->setData(m_pModelEventLog->index(eventLogCnt,2,QModelIndex()),list.value(2),Qt::DisplayRole);
                    eventLogCnt++;

                }

            }

        }
        else
        {
            strBar = tr("读取日志事件表成功，解析失败");
            qDebug()<<"data len err"<<len<<"cnt:"<<cnt<<tbSize;
        }
    }
    else
    {
        strBar = tr("读取日志事件表失败");
    }
    setStatusBarMessage(strBar);
}

/*
*/
void PDataProcess::sendEventLogToLib()
{
}

void PDataProcess::clearEventLogModel()
{
    m_pModelEventLog->removeRows(0,m_pModelEventLog->rowCount(QModelIndex()),QModelIndex());
}

/*
*/
void PDataProcess::deleteCtId(int index)
{
    if(index<m_ListCTId.count())
    {
        m_ListCTId.removeAt(index);
        m_ListCTDomainId.removeAt(index);
        m_ListCTName.removeAt(index);
        m_ListCTEnable.removeAt(index);
        setCtNameModel(m_ListCTName);

    }
}

void PDataProcess::setCtNameModel(QStringList list)
{
    m_pModelCTName->setStringList(list);
    if(m_bFlagShowCluster&&!m_bFlagAddCT)
    {
        emit ctNameModelChange();
    }
}

/*
*/
void PDataProcess::dealClusterInfo(unsigned char *para1, int)
{
    qDebug()<<"deal clusterInfo";

    ClusterProperty_Table *pBase = m_pCTProperty;
    int tbSize = sizeof(ClusterProperty_Table);
    memset(pBase,0,tbSize*MAX_CLUSTER_NUM);

    QString strBar;
    if(*para1==0)
    {
        strBar = tr("读取群属性表成功");
        para1++;
        quint8 cnt = *para1;


        para1++;//指向数据
        for(quint8 i=0;i<cnt;i++)
        {
            quint8 id = *para1;
            if(id>0&&id<(MAX_CLUSTER_NUM+1))
            {
                ClusterProperty_Table *p = pBase+id-1;
                p->ucClusterId = id;

                quint8 domainId = *(++para1);
                p->ucDomainId = domainId;
                quint8 len = *(++para1);
                if(len>CLUSNAMELEN)
                {
                    len = CLUSNAMELEN;
                    qDebug()<<"cluster name len err"<<len;
                }
                p->ucClusterNameLen = len;
                para1++;

                //------------------------
                memcpy(p->ucClusterName,para1,len);
                para1+=len;
                quint8 enable = *para1;
                p->ucClusterEnable = enable;
                para1++;
                memcpy(p->ucNodeIdList,para1,MAX_CLUSTER_NODE_NUM);
                para1+=MAX_CLUSTER_NODE_NUM;
                memcpy(p->ucNodeIndexList,para1,MAX_CLUSTER_NODE_NUM);
                para1+=MAX_CLUSTER_NODE_NUM;

            }
//                m_ListCTId.append(QString::number(id));
//                m_ListCTDomainId.append(QString::number(domainId));
//                m_ListCTName.append(QString::fromLocal8Bit((char*)p->ucClusterName,len));
//                m_ListCTEnable.append(QString::number(enable));
//            }
        }
        analyseClusterInfo();

        if(/*!m_bFlagClusterSend&&*/!m_bFlagCTInit)
        {
            requireTscInfoTable();
            m_bFlagCTInit = true;
        }
        else// /*(/*!m_bFlagClusterSend&&*/m_bFlagCTInit)*/
        {
            m_bFlagCTInit = false;

            m_bFlagUpDateCTNode = false;
//            setModelItem();
            initMapTable();
        }
    }
    else if(*para1==1)
    {
        strBar = tr("读取群属性表失败");
        analyseClusterInfo();
        requireTscInfoTable();
        qDebug()<<"read cluster info error"<<QString::number(*(++para1));
    }
    setStatusBarMessage(strBar);
}

void PDataProcess::analyseClusterInfo()
{
    m_ListCTId.clear();
    m_ListCTDomainId.clear();
    m_ListCTName.clear();
    m_ListCTEnable.clear();
    for(int i=0;i<MAX_CLUSTER_NUM;i++)
    {
        ClusterProperty_Table *p = m_pCTProperty+i;
        quint32 id = p->ucClusterId;
        if(i==(MAX_CLUSTER_NUM-1))
        {
            if(m_ListCTName.count()==0&&id==0)
            {
                p = m_pCTProperty;
                id = 1;
                p->ucClusterId = 1;
                p->ucDomainId = 1;
                QString name = tr("默认群");
                quint8 nameLen = name.toLocal8Bit().count();
                p->ucClusterNameLen = nameLen;
                memcpy(p->ucClusterName,name.toLocal8Bit(),nameLen);
                p->ucClusterEnable = 1;
            }
        }
        if(id!=0)
        {
            quint8 domainId = p->ucDomainId;
            quint8 enable = p->ucClusterEnable;

            m_ListCTId.append(QString::number(id));
            m_ListCTDomainId.append(QString::number(domainId));
            m_ListCTName.append(QString::fromLocal8Bit((char*)p->ucClusterName,p->ucClusterNameLen));
            m_ListCTEnable.append(QString::number(enable));
        }

    }
    setCtNameModel(m_ListCTName);
//    m_pModelCTName->setStringList(m_ListCTName);

}

/*
*/
bool PDataProcess::sendClusterInfoToLib()
{
    ClusterProperty_Table *pBase = m_pCTProperty;

    int cnt = 0;

    int type = CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 0;
    int size = 3;//nodeId+tableName + Para1 + row + data

    QByteArray sendArr;
    sendArr.append(char(CLUSTER_PROPERTY));
    sendArr.append(char(DATA_TYPE_PARA));

    QStringList nameList;//群名 重名 空名 检测
    //QString strMessage;//信息显示

    QByteArray dataArr;
    for(int i=0;i<MAX_CLUSTER_NUM;i++)
    {
        ClusterProperty_Table *p = pBase+i;
        quint8 id = p->ucClusterId;
        //qDebug()<<"cluster id"<<id;
        if(id>0&&id<MAX_CLUSTER_NUM+1)
        {
            cnt++;
            quint8 len = p->ucClusterNameLen;
            QString name = QString::fromLocal8Bit((char*)p->ucClusterName,len);
            if(name.isEmpty()||len==0)
            {qDebug()<<"sendClusterInfoToLib name empty";
//                setStatusBarMessage(tr("群Id%1群名为空").arg(id));
//                return false;
                p->ucClusterId = 0;
                continue;
            }
            dataArr.append(p->ucClusterId);
            dataArr.append(p->ucDomainId);
            dataArr.append(len);
            dataArr.append((char*)p->ucClusterName,len);
qDebug()<<"sendClusterInfoToLib ctName"<<name<<id;
            if(nameList.indexOf(name)==-1)
            {
                nameList.append(name);
            }
            else
            {
                this->setStatusBarMessage(tr("群名重复：%1").arg(name));
                return false;
            }
            dataArr.append(p->ucClusterEnable);
            size += (4+len);
            dataArr.append((char*)p->ucNodeIdList,MAX_CLUSTER_NODE_NUM);
            size += MAX_CLUSTER_NODE_NUM;
            dataArr.append((char*)p->ucNodeIndexList,MAX_CLUSTER_NODE_NUM);
            size += MAX_CLUSTER_NODE_NUM;
        }
    }

    sendArr.append(char(cnt));
    sendArr.append(dataArr);

    if(sendMessage(type,num,size,sendArr))
    {
        setStatusBarMessage(tr("发送群属性表成功"));
        return true;
    }
    else
    {
        setStatusBarMessage(tr("发送群属性表失败"));
        return false;
    }
}


QString PDataProcess::getCtNameById(quint8 id)
{
    int index = m_ListCTId.indexOf(QString::number(id));
    if(index!=-1)
    {
        return m_ListCTName[index];
    }

    return QObject::tr("群%1").arg(id);
}

quint8 PDataProcess::getCtIdByName(QString str)
{
    int index = m_ListCTName.indexOf(str);
    if(index!=-1)
    {
        return m_ListCTId[index].toInt();
    }
    return 1;
}
/*
*/
quint8 PDataProcess::getNewClusterId()
{
    ClusterProperty_Table *p = m_pCTProperty;
    for(quint8 i=0;i<(MAX_CLUSTER_NUM+1);i++)
    {
        if((p+i)->ucClusterId==0)
        {
            qDebug()<<"ct new id"<<i+1;
            return i+1;
        }
    }
    return 0;
}

quint8 PDataProcess::getCurClusterId()
{
    return m_ucCurClusterId;
}

bool PDataProcess::getClusterState()
{
    return m_bFlagCluster;
}

bool PDataProcess::sendClusterCommand(quint8 cmd, quint8 id)
{
    int type = CS_CMDTYPE_CLUSTER_REQUEST;// (0x38)
    int num = 0;
    int size = 1+1+1;

//    htonlHead(type,num,size);
    QByteArray sendArr;
    //sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);
    sendArr.append(char(cmd));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(id));

    return sendMessage(type,num,size,sendArr);
}

/*
*/
void PDataProcess::dealClusterTimeBase(unsigned char *p, int)
{
    QString statusStr;
    if(*p==0x01)
    {
        qDebug()<<"cluster timebase error";
        statusStr = tr("读取群时基错误");
    }
    if(*p==0x00)
    {
        statusStr = tr("读取群时基成功");


        //byte no;

        QString str;
        int rowCnt = *(++p);
        //int index;//用于数组存储
        int tbSize = sizeof(TimeBase_Table);
        quint8 ctId = *(++p);//指向数据 群id
        TimeBase_Table *timebase = NULL;
        if(m_mapCluster.contains(ctId))
        {
            timebase = m_mapCluster[ctId]->tbCTTimeBase;
        }
        else
        {
            qDebug()<<"m_mapCluster no contain"<<ctId;
            return;
        }

        memset(timebase,0,tbSize*MAX_TIMEBASE_NUM);

        //存放在群时基表里
        for(int i=0;i<rowCnt;i++)
        {
            quint8 no = *(++p);//时基表号
            if(no>0)
            {
                quint8 index = no-1;
                memcpy(timebase+index,p,tbSize);
            }
            p+=tbSize;
        }


        analyseTimeBaseTable(timebase);

        emit statusBarMessage(statusStr);

        //QDate date = QDate::currentDate();
//        ACE_Date_Time tvTime(ACE_OS::gettimeofday());
//        m_ucCTScheduleId = GetClusterScheduleId( (BYTE)tvTime.month()
//                                                 , (BYTE)tvTime.day()
//                                                 , (BYTE)tvTime.weekday()
//                                                 ,timebase);
//        if(m_ucCTScheduleId==0)
//        {
//            m_ucCTScheduleId = 1;
//            qDebug()<<"m_ucCTScheduleId error 0";
//        }

    }

    requireDataBaseTable(CLUSTER_SCHEDULE,m_ucCurClusterId);
}

//void PDataProcess::analyseClusterTimeBase(TimeBase_Table *timebase)
//{
//    setTimeBaseModel(timebase);
//    emit changeSpecialModel();
//}

/*
*/
bool PDataProcess::sendClusterTimeBase(byte index,bool bAdd, bool bEdit, bool bDel,  TimeBase_Table *tbTimeBase)
{
    int tabSize = sizeof(TimeBase_Table);
    int cnt = m_pTscInfo->iTimeBaseTableNum;
    if(bAdd)
    {
        cnt++;
    }
    if(bDel)
    {
        cnt--;
    }

    qDebug()<<"send cnt:"<<cnt;
    int type = CS_CMDTYPE_LOCAL_DATABASE_WRITE; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 1;
    int size = 4+1+1+1+cnt*(tabSize+1);//nodeId+tableName + Para1 + row + data

    QByteArray sendArr;
    quint32 ctId = qToBigEndian<quint32>(m_ucCurClusterId);
    sendArr.append((char*)&ctId,4);//节点Id

    sendArr.append(char(CLUSTER_TIMEBASE));
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(cnt));
    TimeBase_Table* p = m_pTscInfo->tbTimeBase;
    if(bAdd||bEdit)
    {


        for(byte i=0;i<MAX_TIMEBASE_NUM;i++)
        {
            if(i==index)
            {
                qDebug()<<"index edit/add"<<index;
                sendArr.append(m_ucCurClusterId);
                sendArr.append((char*)tbTimeBase,tabSize);
            }
            else
            {
                if((p+i)->bNo!=0)
                {
                    qDebug()<<"append str i:"<<i;
                    sendArr.append(m_ucCurClusterId);
                    sendArr.append((char*)(p+i),tabSize);
                }
            }
        }
    }
    if(bDel)
    {
        for(byte i=0;i<MAX_TIMEBASE_NUM;i++)
        {
            if(i==index)
            {
                continue;
            }
            else
            {
                if(i==0)
                {
                    qDebug()<<"i=0 id"<<(p+i)->bNo;
                }
                if((p+i)->bNo!=0)
                {
                    qDebug()<<"i:"<<i;
                    sendArr.append(m_ucCurClusterId);
                    sendArr.append((char*)(p+i),tabSize);
                }
            }
        }
    }

    return sendMessage(type,num,size,sendArr);
}

quint8 PDataProcess::GetClusterScheduleId(quint8 ucMonth
                                       , quint8 ucDay
                                       , quint8 ucWeek
                                       , TimeBase_Table sClusterTimebase[MAX_TIMEBASE_NUM])
{
        //按日 节假日 特定月 + 特定日 + 周全选
        for (int i=0; i<MAX_TIMEBASE_NUM; i++ )
        {
                if ( sClusterTimebase[i].bNo != 0 )
                {qDebug()<<"i"<<i<<sClusterTimebase[i].bNo;
                        if ( (sClusterTimebase[i].uMonth>>ucMonth) & 0x1
                                && ( (qFromBigEndian<quint16>(sClusterTimebase[i].uMonth) & 0x1ffe) != 0x1ffe ) )
                        {
                                if ( (qFromBigEndian<quint32>(sClusterTimebase[i].lMonthDay)>>ucDay) & 0x1
                                        && ( (qFromBigEndian<quint32>(sClusterTimebase[i].lMonthDay) & 0xfffffffe) != 0xfffffffe) )
                                {
                                        if ( (sClusterTimebase[i].bWeekDay & 0xfe) == 0xfe )
                                        {
                                                return sClusterTimebase[i].bScheduleNo;
                                        }
                                }
                        }
                }
                else
                {
                        break;  //没有该天的时间方案
                }
        }

        //按周：全月   + 全日   + 特定周
        for (int i=0; i<MAX_TIMEBASE_NUM; i++ )
        {
                if ( sClusterTimebase[i].bNo != 0 )
                {//qDebug()<<"i"<<i<<sClusterTimebase[i].bNo<<tr("%1;%2;%3").arg(qFromBigEndian<quint16>(sClusterTimebase[i].usMonthFlag),4,16).arg(qFromBigEndian<quint32>(sClusterTimebase[i].uiDayFlag),8,16).arg(sClusterTimebase[i].bWeek,2,16)<<ucWeek<<sClusterTimebase[i].ucScheduleId<<(sClusterTimebase[i].bWeek>>(ucWeek));
                        if ( (qFromBigEndian<quint16>(sClusterTimebase[i].uMonth) & 0x1ffe) == 0x1ffe )
                        {
                                if ( (qFromBigEndian<quint32>(sClusterTimebase[i].lMonthDay) & 0xfffffffe) == 0xfffffffe )
                                {
                                        if ( ((sClusterTimebase[i].bWeekDay>>(ucWeek+1)) & 0x01)==1
                                                && ( ( sClusterTimebase[i].bWeekDay & 0xfe) != 0xfe ) )
                                        {//qDebug()<<"i:return schid"<<i<<sClusterTimebase[i].ucScheduleId<<(sClusterTimebase[i].bWeek>>(ucWeek+1));
                                                return sClusterTimebase[i].bScheduleNo;
                                        }
                                }
                        }
                }
                else
                {
                        break;  //没有该天的时间方案
                }
        }

        //按月：特定月 + 全日   + 全周
        for (int i=0; i<MAX_TIMEBASE_NUM; i++ )
        {
                if ( sClusterTimebase[i].bNo != 0 )
                {
                        if ( (qFromBigEndian<quint16>(sClusterTimebase[i].uMonth)>>ucMonth) &0x1
                                && ((qFromBigEndian<quint16>(sClusterTimebase[i].uMonth) & 0x1ffe) != 0x1ffe ) )
                        {
                                if ( (qFromBigEndian<quint32>(sClusterTimebase[i].lMonthDay) & 0xfffffffe) == 0xfffffffe )
                                {
                                        if ( (sClusterTimebase[i].bWeekDay & 0xfe) == 0xfe )
                                        {
                                                return sClusterTimebase[i].bScheduleNo;
                                        }
                                }
                        }
                }
                else
                {
                        break;  //没有该天的时间方案
                }
        }

        //其他：特定月 + 特定日 + 特定周
        for (int i=0; i<MAX_TIMEBASE_NUM; i++ )
        {
                if ( sClusterTimebase[i].bNo != 0 )
                {
                        if ( (sClusterTimebase[i].uMonth>>ucMonth) &0x1 )//月份正确 b1:1月 b12:12
                        {
                                if ( ( (sClusterTimebase[i].bWeekDay>>(ucWeek+1)) & 0x1 ) //b1：周日 b2：周1
                                        && ( (sClusterTimebase[i].lMonthDay>>ucDay) & 0x1 ) )  //b1:1号 b2
                                {
                                        return sClusterTimebase[i].bScheduleNo;
                                }
                        }
                }
                else
                {
                        //break;  //没有该天的时间方案
                }
        }

        return 0;
}


/*
*/
void PDataProcess::dealClusterSchedule(unsigned char *p, int)
{
    QString statusStr;
    if(*p==0x01)
    {
        statusStr = tr("读取群时段失败");
    }
    else if(*p==0x00)
    {
        statusStr = tr("读取群时段成功");
        byte cntRow = *(++p);
//        m_pTscInfo->iScheduleTableNum = (int)cntRow;
        byte cntCol = *(++p);//二维
        byte schNo = 0;
        byte eventNo = 0;
        int tabSize;
        tabSize = sizeof(SClusterSchedule);
        Schedule_Table (*pSch)[MAX_SCHEDULE_EVENT_NUM];

        p++;//数据开头
        quint8 ctId = *p;
        if(m_mapCluster.contains(ctId))
        {
            m_mapCluster[ctId]->initScheduleTable();
            pSch = m_mapCluster[ctId]->tbCTSchedule;
        }
        else
        {
            qDebug()<<"m_mapCluster not contain"<<ctId;
            return;
        }

        unsigned char *pLocal;//传输数据的指针
        Schedule_Table* pRow;//本地表的指针
        for(byte r=0;r<cntRow;r++)
        {
            pLocal = p + r*cntCol*tabSize;//定位 数据 指针
            schNo = *(pLocal+1);//时段号

            pRow = *(pSch + (schNo-1));//本地存储指针
            //qDebug()<<"row"<<r<<schNo;
            for(byte c=0;c<cntCol;c++)
            {

                if(*(pLocal+2)!=0x00)//事件号
                {
                    //qDebug()<<quint8(*pLocal);
                    Schedule_Table *pCol = pRow + c;
                    //memcpy(pCol,pLocal,tabSize);//时段表里的事件 按 顺序存储
                    pLocal++;//跳过群号
                    pCol->bNo = schNo;
                    pLocal++;
                    pCol->bEventNo = *pLocal;
                    pLocal++;
                    pCol->bHour = *pLocal;
                    pLocal++;
                    pCol->bMinute = *pLocal;
                    pLocal++;
                    pCol->bTimePatternNo = *pLocal;
                    pLocal++;
                    pCol->bControlMode = *pLocal;
                    pLocal++;
//                    pCol->bAssistantOut = *pLocal;//用于群周期
//                    pLocal++;//没有周期时 去除
                }
                else
                {
                    break;
                }
            }

            //m_bFlagScheduleName = true;

        }
        analyseScheduleTable(pSch);
//        m_ucCTPlanId = GetClusterTimePatternId(m_ucCTScheduleId,
//                                               m_mapCluster[ctId]->tbCTSchedule[m_ucCTScheduleId-1],
//                                               &m_mapCluster[ctId]->iControlType,
//                                               &m_mapCluster[ctId]->iCircle);
//        if(m_ucCTPlanId==0)
//        {
//            m_ucCTPlanId = 1;
//            qDebug()<<"m_ucCTPlanId error 0";
//        }

    }

    emit statusBarMessage(statusStr);
    requireDataBaseTable(CLUSTER_TIMEPATTERN,m_ucCurClusterId);

    //m_bFlagCluster = false;
}

/*
*/


/*
*时间比较
*return: 0:time2比time1小   1：time2比time1大,或相等
*/
bool PDataProcess::CompareTime(quint8 ucHour1, quint8 ucMin1, quint8 ucHour2, quint8 ucMin2)
{
        if ( ucHour2 > ucHour1 )
        {
                return 1;
        }
        else if ( ucHour2 == ucHour1 )
        {
                if ( ucMin2 >= ucMin1 )
                {
                        return 1;
                }
        }

        return 0;
}

/*
*根据时段表号，获取当前的配时方案号
*input:  ucScheduleId     - 时段表号
*        sClusterSchedule - 群时段表
*output: pCtrl  - 控制方式
*        pCycle - 周期
*返回值：配时方案号
*/
quint8 PDataProcess::GetClusterTimePatternId( BYTE ucScheduleId
                                            , Schedule_Table sClusterSchedule[MAX_SCHEDULE_EVENT_NUM]
                                            , BYTE* pCtrl
                                            , BYTE* /*pCycle*/ )
{
        bool bLastTem           = false;
        int  iIndex             = 0;
        BYTE ucCurTimePatternId = 0;
        BYTE ucCtrlTmp          = 0;
        //ACE_Date_Time tvTime(ACE_OS::gettimeofday());
        QTime tvTime = QTime::currentTime();

        for ( iIndex = 0; iIndex<MAX_SCHEDULE_EVENT_NUM; iIndex++)
        {
                if ( sClusterSchedule[iIndex].bNo != 0 && sClusterSchedule[iIndex].bEventNo != 0 )
                {
                        if ( sClusterSchedule[iIndex+1].bNo == ucScheduleId )
                        {
                                if ( ( CompareTime( sClusterSchedule[iIndex].bHour
                                                      , sClusterSchedule[iIndex].bMinute
                                                      , (BYTE)tvTime.hour(),(BYTE)tvTime.minute()) )
                                        && ( !CompareTime( sClusterSchedule[iIndex+1].bHour
                                           , sClusterSchedule[iIndex+1].bMinute
                                           , (BYTE)tvTime.hour(),(BYTE)tvTime.minute()
                                           )) )
                                {
                                        ucCurTimePatternId = sClusterSchedule[iIndex].bTimePatternNo;
                                        *pCtrl             = sClusterSchedule[iIndex].bControlMode;
                                        //*pCycle            = sClusterSchedule[iIndex].ucCycle;
                                        break;
                                }
                        }
                }
                else
                {
                        bLastTem = true;
                        break;
                }
        }

        if ( bLastTem && (iIndex != 0 )) //最后一段的时间阶段
        {
                ucCurTimePatternId = sClusterSchedule[iIndex-1].bTimePatternNo;
                *pCtrl             = sClusterSchedule[iIndex-1].bControlMode;
               // *pCycle            = sClusterSchedule[iIndex-1].ucCycle;
        }

        return ucCurTimePatternId;
}

void PDataProcess::dealClusterPattern(unsigned char *p, int)
{
    QString statusStr;
    if(*p==0x01)
    {
        qDebug()<<"cluster pattern error";
        statusStr = tr("读取群方案失败");
    }
    if(*p==0x00)
    {
        statusStr = tr("读取群方案成功");
        //byte no;
        QString str;
        int rowCnt = *(++p);
        //int index;//用于数组存储
        int tbSize = sizeof(SClusterPattern);
        quint8 ctId = *(++p);//指向数据 群id
        SClusterPattern *pattern = NULL;
        if(m_mapCluster.contains(ctId))
        {
            pattern = m_mapCluster[ctId]->tbCTPattern;
            memset(pattern,0,tbSize*MAX_TIMEPATTERN_NUM);
        }
        else
        {
            qDebug()<<"m_mapCluster no contain"<<ctId;
            return;
        }
        for(int i=0;i<rowCnt;i++)
        {
            quint8 patternId = *(p+1);
            if(patternId>0)
            {
                memcpy(pattern+patternId-1,p,tbSize);
            }
            p+=tbSize;
        }
        analyseClusterPatternTable();
    }

    emit statusBarMessage(statusStr);

    requinreAllClusterTable();
}

void PDataProcess::analyseClusterPatternTable()
{
    m_ListTimePatternName.clear();
    SClusterPattern *p = m_pClusterInfo->tbCTPattern;
    quint8 id;
    for(int i=0;i<MAX_TIMEPATTERN_NUM;i++)
    {
        id = p->ucPatternId;
        if(id!=0)
        {
            m_ListTimePatternName.append(QObject::tr("群方案")+QString::number(id));
        }
        p++;
    }
    //m_pTscInfo->iTimePatternTableNum = m_ListTimePatternName.count();
    emit updateTimePatternName();
    emit rcvCtPattern();
//    getClusterCircle();
}

bool PDataProcess::checkCtPatternData(SClusterPattern*p)
{
    return p->ucCycleTime==0?false:true;
}

bool PDataProcess::sendClusterPattern()
{
    int tabSize = sizeof(SClusterPattern);
    int type =/* CS_CMDTYPE_TSC_PARA_WRITE; //*/CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 1;

    QByteArray sendArr;
    quint32 id;
    id = qToBigEndian<quint32>(m_ucCurClusterId);
    sendArr.append((char*)&id,4);//节点Id
    sendArr.append(char(CLUSTER_TIMEPATTERN));

    sendArr.append(char(DATA_TYPE_PARA));
    int cnt = 0;
    QByteArray dataArr;
    SClusterPattern* p = m_pClusterInfo->tbCTPattern;

    for(int i=0;i<MAX_TIMEPATTERN_NUM;i++)
    {
        if((p+i)->ucPatternId>0)
        {
            if(checkCtPatternData(p+i))
            {
                (p+i)->ucClusterId = m_ucCurClusterId;
                dataArr.append((char*)(p+i),tabSize);
                cnt++;
            }
            else
            {
                (p+i)->ucPatternId = 0;
            }
        }
    }

    int size = 4+1+1+1+cnt*tabSize;//nodeId+tableName + Para1 + row + data
    sendArr.append(char(cnt));
    sendArr.append(dataArr);
    if(sendMessage(type,num,size,sendArr))
    {
        setStatusBarMessage(tr("发送群方案成功"));
        return true;
    }
    else
    {
        setStatusBarMessage(tr("发送群方案失败"));
        return false;
    }
}

void PDataProcess::getClusterCircle()
{
    ACE_Date_Time tvTime(ACE_OS::gettimeofday());
    m_ucCTScheduleId = GetClusterScheduleId( (BYTE)tvTime.month()
                                             , (BYTE)tvTime.day()
                                             , (BYTE)tvTime.weekday()
                                             ,m_pClusterInfo->tbCTTimeBase);
    if(m_ucCTScheduleId==0)
    {
        m_ucCTScheduleId = 1;
        qDebug()<<"m_ucCTScheduleId error 0";
    }

    m_ucCTPlanId = GetClusterTimePatternId(m_ucCTScheduleId,
                                           m_pClusterInfo->tbCTSchedule[m_ucCTScheduleId-1],
                                           &m_pClusterInfo->iControlType,
                                           &m_pClusterInfo->iCircle);
    if(m_ucCTPlanId==0)
    {
        m_ucCTPlanId = 1;
        qDebug()<<"m_ucCTPlanId error 0";
    }

    if(m_ucCTPlanId>0&&m_ucCTPlanId<(MAX_TIMEPATTERN_NUM+1))
    {
        SClusterPattern *pattern = m_pClusterInfo->tbCTPattern+m_ucCTPlanId-1;
        m_ucCTCircle = pattern->ucCycleTime;
        m_pClusterInfo->iCircle = m_ucCTCircle;
        m_ucCTStageTime = pattern->ucStagePatternId;
        qDebug()<<"m_ucCTScheduleId"<<m_ucCTScheduleId<<"m_ucCTPlanId"<<m_ucCTPlanId<<"circle"<<m_pClusterInfo->iCircle;
        QString statusStr;
        int index = m_ListCTId.indexOf(QString::number(m_ucCurClusterId));
        statusStr.append(tr("当前群:%1,时段号:%2,方案号:%3,周期:%4,配时:%5  ").arg(m_ListCTName[index]).arg(m_ucCTScheduleId).arg(m_ucCTPlanId).arg(m_pClusterInfo->iCircle).arg(m_ucCTStageTime));
        quint8 enable = (m_pCTProperty+m_ucCurClusterId-1)->ucClusterEnable;
        statusStr.append(enable==0?tr("有效"):tr("无效"));
        emit statusBarMessage(statusStr,LBTHIRD);
    }
}

/*
 得到一个群里的所有节点，和顺序号
*/
void PDataProcess::getCTNodeId(quint8 ctId)
{
    if(ctId==0)
    {
        return;
    }
    m_ListCTNodeId.clear();
    m_ListCTNodeIndex.clear();
    m_ListCTNodeName.clear();
    int cnt = m_TscClusterIdList.count();//所有节点数
    ClusterProperty_Table* p = m_pCTProperty+ctId-1;
    for(int i=0;i<MAX_CLUSTER_NODE_NUM;i++)
    {
        for(int j=0;j<MAX_CLUSTER_NODE_NUM;j++)
        {
            quint8 nodeId = p->ucNodeIdList[j];
            quint8 ctIndex = p->ucNodeIndexList[j];
            if(nodeId>0)
            {
                int index = m_TscIdList.indexOf(QString::number(nodeId));
                if(index!=-1)
                {
                    if(m_TscClusterIdList[index]==ctId)
                    {
                        if(!m_ListCTNodeId.contains(QString::number(nodeId)))
                        {qDebug()<<"m_ListCTNodeId append"<<nodeId;
                            m_ListCTNodeId.append(QString::number(nodeId));
                            m_ListCTNodeName.append(m_TscNameList[index]);
                            m_ListCTNodeIndex.append(ctIndex);
                        }
                    }
                }
            }
        }
    }
//    for(int i=0;i<cnt;i++)
//    {
//        if(m_TscClusterIdList[i]==ctId)
//        {
//            m_ListCTNodeId.append(m_TscIdList[i]);
//            m_ListCTNodeName.append(m_TscNameList[i]);
//            m_ListCTNodeIndex.append(m_TscCtNodeIndex[i]);
//        }
//    }
    int count = m_ListCTNodeName.count();
    if(count>0)
    {
        m_pModelCTNodeName->setStringList(m_ListCTNodeName);
    }

}

//void PDataProcess::getCTNodePatternInfo(quint8 patternId)
//{
//    if(patternId>0&&patternId<MAX_TIMEPATTERN_NUM+1)
//    {
//        TimePattern_Table* p = m_pTscInfo->tbTimePattern+patternId-1;
//        m_ListCTNodeStagePattern.append(p->bStageTimeTableNo);//阶段配时号
//        m_ListCTNodeOffset.append(p->bOffset);
//        qDebug()<<"m_ListCTNodeStagePattern"<<p->bStageTimeTableNo<<m_ListCTNodeOffset<<p->bOffset;
//    }
//}

void PDataProcess::getCTNodeOffset(quint8 ctId)
{
    if(m_mapCluster.contains(ctId))
    {
        SClusterPattern *pattern = m_mapCluster[ctId]->tbCTPattern;
        m_ListCTNodeOffset.clear();
        int nodeCnt = m_ListCTNodeId.count();
        for(int i=0;i<nodeCnt;i++)
        {
            m_ListCTNodeOffset.append(pattern->sOffsetList[i]);
        }
    }
}

bool PDataProcess::getCTNodeStageList(quint8 nodeId)
{
    m_ListStageTime.clear();
    if(m_ucCTStageTime==0)
    {
        qDebug()<<"getCTNodeStageList m_ucCTStageTime==0";
        m_ucCTStageTime = 1;
    }
    if(m_mapTsc.contains(nodeId))
    {
        StageTime_Table (*p)[MAX_STAGE_NUM];
        p = m_mapTsc[nodeId]->tbStageTime+m_ucCTStageTime-1;
        for(int i=0;i<MAX_STAGE_NUM;i++)
        {
            StageTime_Table *stage = *p+i;
            if(stage->bStageNo>0)
            {
                m_ListStageTime.append(stage->bGreenTime);
                m_ListStageTime.append(stage->bYellowTime);
                m_ListStageTime.append(stage->bRedTime);
            }
        }
        if(m_ListStageTime.isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
//    if(stageId>0&&stageId<MAX_STAGE_PATTERN_NUM+1)
//    {
//        StageTime_Table* p = m_pTscInfo->tbStageTime[stageId-1];
//        for(int i=0;i<MAX_STAGE_NUM;i++)
//        {
//            quint8 id = (p+i)->bStageNo;//阶段号
//            if(id!=0)
//            {
//                list->append((p+i)->bGreenTime);
//                list->append((p+i)->bYellowTime);
//                list->append((p+i)->bRedTime);
//            }
//        }
//    }

}

void PDataProcess::changeCtNode(quint8 ctId, quint8 nodeId)
{qDebug()<<"changeCtNode ctId nodeId"<<ctId<<nodeId;
    if(ctId==0||nodeId==0||ctId>MAX_CLUSTER_NUM)
    {
        return;
    }
    //清除原先群里的节点
    for(int i=0;i<MAX_CLUSTER_NUM;i++)
    {
        ClusterProperty_Table *p = m_pCTProperty+i;
        for(int j=0;j<MAX_CLUSTER_NODE_NUM;j++)
        {
            if(p->ucNodeIdList[j]==nodeId)
            {
                p->ucNodeIdList[j]=0;
                p->ucNodeIndexList[j]=0;
            }
        }
    }
    ClusterProperty_Table *p = m_pCTProperty+ctId-1;
    for(int i=0;i<MAX_CLUSTER_NODE_NUM;i++)
    {
        if(p->ucNodeIdList[i]==0)
        {
            p->ucNodeIdList[i] = nodeId;
            qDebug()<<"m_pCTProperty ctId"<<ctId<<"add nodeId"<<i<<nodeId;
            break;
        }
    }
}

bool PDataProcess::setClusterInfoList(QStringList nodeIdList, QList<quint8> indexList, QList<qint16> offsetList,QList<quint8>listCoor,quint8 patternId)
{
    if(m_ucCurClusterId>0&&patternId>0&&m_pClusterInfo!=NULL)
    {
        ClusterProperty_Table *p = m_pCTProperty+m_ucCurClusterId-1;
        memset(p->ucNodeIdList,0,MAX_CLUSTER_NODE_NUM);
        memset(p->ucNodeIndexList,0,MAX_CLUSTER_NODE_NUM);

        SClusterPattern *pattern = m_pClusterInfo->tbCTPattern+patternId-1;
        memset(pattern->sOffsetList,0,MAX_CLUSTER_NODE_NUM);
        memset(pattern->ucCoordPhaseList,0,MAX_CLUSTER_NODE_NUM);
        int cntId = nodeIdList.count();
        int cntIndex = indexList.count();
        int cntOffset = offsetList.count();
        qDebug()<<"nodeIdList"<<nodeIdList<<"indexList"<<indexList<<"offsetList"<<offsetList;
        if(!(cntId!=cntIndex||cntIndex!=cntOffset))
        {
            for(int i=0;i<cntId;i++)
            {
                p->ucNodeIdList[i] = nodeIdList[i].toInt();
                p->ucNodeIndexList[i] = indexList[i];
                pattern->sOffsetList[i] = offsetList[i];
    //            pattern->ucCoordPhaseList[i] = listCoor[i];
            }
            return true;
        }

//        int offset
//        for(int i=0;i<cnt;i++)
//        {

//        }

//        m_pClusterInfo->
    }
    return false;
}

//void PDataProcess::sendCtNodeInfoToLib(QString nodeIdStr, quint8 posIndex)
//{
//    int index = m_TscIdList.indexOf(nodeIdStr);
//    if(index!=-1)
//    {
//        STscNode sNode;
//        sNode.uiId = m_TscIdList[index].toInt();
//        sNode.ucClusterId = m_TscClusterIdList[index];
//        sNode.ucClusterNodeIndex = posIndex;
////        memset(sNode.sDeviceName,0,MAXNAMELEN);
////        memcyp(sNode.sDeviceName,m_TscNameList[index].toLocal8Bit().data(),m_TscNameList[index].toLocal8Bit().length());
//        memcpy(sNode.sDeviceName,m_TscNameList[index].toLocal8Bit().data(),m_TscNameList[index].toLocal8Bit().length());
////        memset(sNode.sDeviceIp,0,MAXNAMELEN);
////        memcyp(sNode.sDeviceIp,m_TscIpList[index].toLocal8Bit().data(),m_TscIpList[index].toLocal8Bit().length());
//        memcpy(sNode.sDeviceIp,m_TscIpList[index].toLocal8Bit().data(),m_TscIpList[index].toLocal8Bit().length());
//        sNode.uiPort = m_TscPortList[index];
////        memset(sNode.sVersion,0,MAXNAMELEN);
////        memcyp(sNode.sVersion,m_TscVersionList[index].toLocal8Bit().data(),m_TscVersionList[index].toLocal8Bit().length());
//        memcpy(sNode.sVersion,m_TscVersionList[index].toLocal8Bit().data(),m_TscVersionList[index].toLocal8Bit().length());
//        sNode.ucLinkType = m_TscLinkTypeList[index];
//        sNode.ucProtocolType = m_TscProtocolList[index];

//        sendNodeCommand(NODE_UPDATE,&sNode);
//    }
//}

//void PDataProcess::dealCtNodeInforResponse(unsigned char *para1, int)
//{
//    if(*para1==1)
//    {
//        if(*(++para1)==0)
//        {
//            if(m_ucCTNodeSendIndex<m_ListCTNodeId.count())
//            {
//                requireTscTable(TSC_TABLE_TIMEPATTERN,m_ListCTNodeId[m_ucCTNodeSendIndex].toInt());
//                qDebug()<<"require pattern"<<m_ListCTNodeId[m_ucCTNodeSendIndex];
//            }
//        }
//    }
//}

/*
*/
//void PDataProcess::sendCtNodePatternToTsc(QList<quint8> indexList,QList<qint16> offsetList)
//{
//    m_ListCTNodeIndex.clear();
//    m_ListCTNodeOffset.clear();
//    m_ListCTNodeIndex.append(indexList);
//    m_ListCTNodeOffset.append(offsetList);
//    //sendCtNodeInfoToLib(m_ListCTNodeId[0],m_ListCTNodeIndex[0]);
//    //requireTscTable(TSC_TABLE_TIMEPATTERN,m_ListCTNodeId[0].toInt());
//    m_ucCTNodeSendIndex = 0;
//    sendCtNodeInfoToLib(m_ListCTNodeId[m_ucCTNodeSendIndex],m_ListCTNodeIndex[m_ucCTNodeSendIndex]);
//}

//void PDataProcess::dealClusterPattern(unsigned char *rcv, int len)
//{
//    *(rcv+3) = (quint8)CS_CMDTYPE_TSC_PARA_WRITE;
//    quint32 nodeId;
//    memcpy(&nodeId,rcv+12,4);
//    nodeId = ntohl(nodeId);
//    int index = m_ListCTNodeId.indexOf(QString::number(nodeId));
//    if(index!=-1&&m_ucCTPlanId!=0)
//    {
//        quint8 cnt = *(rcv+18);
//        TimePattern_Table* p = (TimePattern_Table*)(rcv+19);
//        for(int i=0;i<cnt;i++)
//        {
//            if(m_ucCTPlanId == p->bNo)
//            {
//                p->bOffset = m_ListCTNodeOffset[index];
//                qDebug()<<"offset:"<<m_ListCTNodeOffset[index];
//            }
//            p++;
//        }
//        QByteArray sendArr((char*)rcv,len);
//        m_ClientServ->sendData(sendArr);
//    }

//}

//void PDataProcess::dealClusterPatternResponse(unsigned char*para1,int len)
//{
//    if(len>1)
//    {
//        if(*para1==1)
//        {
//            if(*(++para1)==0)
//            {
//                if(m_ucCTNodeSendIndex<m_ListCTNodeId.count()-1)
//                {
//                    m_ucCTNodeSendIndex++;
//                    sendCtNodeInfoToLib(m_ListCTNodeId[m_ucCTNodeSendIndex],m_ListCTNodeIndex[m_ucCTNodeSendIndex]);
//                    qDebug()<<"send ct node info"<<m_ListCTNodeId[m_ucCTNodeSendIndex];
//                    //requireTscTable(TSC_TABLE_TIMEPATTERN,m_ListCTNodeId[m_ucCTNodeSendIndex].toInt());
//                }
//                else
//                {
//                    m_bFlagClusterSend = false;
//                    qDebug()<<"send cluster pattern success";
//                    int index = m_ListCTId.indexOf(QString::number(m_ucCurClusterId));
//                    QString str;
//                    if(index!=-1)
//                    {
//                        str.append(m_ListCTName[index]);
//                        str.append(tr(" 群设置完成"));
//                        emit statusBarMessage(str,LBTHIRD);
//                    }
//                }
//            }
//        }
//    }

//}

void PDataProcess::sendClusterPlan()
{
//    getCTNodeId(m_ucCurClusterId);
//    m_bFlagSendCTPlan = true;
//    int cnt = m_ListCTNodeId.count();
//    if(cnt>0)
//    {
//        m_ucSendCTPlanIndex = 0;
//        sendTimeBaseToTsc(m_ListCTNodeId[0].toInt());
//    }
}

bool PDataProcess::requireVipInfoTable()
{
    int type = CS_CMDTYPE_LOCAL_DATABASE_READ;    // = 0x30, //节点操作请求
    int num = 0;
    int size = 1;
    htonlHead(type,num,size);
    QByteArray sendArr;
    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);
    sendArr.append(char(LOCAL_VIP));//   = 0x13,   //群读取
    int sendLen = m_iheadSize + size;
    if(sendLen==m_ClientServ->sendData(sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PDataProcess::sendVipCmd(quint8 cmd)
{
    int type = CS_CMDTYPE_VIP_REQUEST; //CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 0;
    int size = 3;//cmd para1 vipId

    QByteArray sendArr;

    sendArr.append((char*)&cmd);//
    sendArr.append(char(DATA_TYPE_PARA));
    sendArr.append(char(m_ucCurVipId));

    return sendMessage(type,num,size,sendArr);
}

void PDataProcess::dealVipInfo(unsigned char *para1, int len)
{
    //qDebug()<<"dealvipinfo"<<*para1<<len;
    QString strBar;
    if(*para1==0&&len>2)
    {
        int cnt = *(++para1);
        int tbSize = sizeof(VipProperty_Table);
        if(len==cnt*tbSize+2)
        {
            strBar = tr("读取vip属性表成功");
            para1++;
            VipProperty_Table *p = m_pVipInfo->tbVipProperty;
            memset(p,0,tbSize*MAX_VIP_NUM);
            for(int i=0;i<cnt;i++)
            {
                quint8 vipId = *para1;
                if(vipId>0&&vipId<MAX_VIP_NUM+1)
                {
                    memcpy(p+vipId-1,para1,tbSize);
                }
                else
                {
                    qDebug()<<"dealvipinfo id error"<<vipId<<i;
                }
                para1+=tbSize;
            }
            setVipList();


        }
        else
        {
            qDebug()<<"dealvipinfo len error cnt"<<cnt<<"tbSize"<<tbSize;
        }
    }
    else
    {//错误的原因是没有数据
        strBar = tr("读取vip属性表失败");
        setVipList();
        qDebug()<<"dealvipinfo error";
    }
    setStatusBarMessage(strBar);
    if(m_bFlagNodeIdChanged)
    {
        this->requireClusterInfoTable();
    }
}

void PDataProcess::setVipList()
{
    qDebug()<<"setviplist";
    VipProperty_Table *p = m_pVipInfo->tbVipProperty;
    m_ListVipId.clear();
    m_pModelVipId->clear();
    int modelIndex = 0;

    m_bFlagVipInit = false;
    for(int i=0;i<MAX_VIP_NUM;i++)
    {
        quint8 vipId = (p+i)->ucVipLineId;
        //如果没有设置vip 用vip1；
        if(i==(MAX_VIP_NUM-1))
        {
            if(m_ListVipId.count()==0&&vipId==0)
            {
                vipId = 1;
                (p+i)->ucVipLineId = 1;
            }
        }

        if(vipId!=0)
        {
            m_ListVipId.append(vipId);
            QStandardItem *item = new QStandardItem(tr("Vip%1").arg(vipId));
            m_pModelVipId->appendRow(item);
        }
    }

    if(m_bFlagCTInit)//群已经初始化
    {
        setModelItem();
    }
    emit vipIdModelChange();
}

bool PDataProcess::sendVipInfoToLib()
{
    VipProperty_Table *pBase = m_pVipInfo->tbVipProperty;
    int tbSize = sizeof(VipProperty_Table);

    int cnt = 0;

    int type = CS_CMDTYPE_LOCAL_DATABASE_WRITE;//= 0x62, //写本地数据库
    int num = 0;
    int size = 3;//nodeId+tableName + Para1 + row + data

    QByteArray sendArr;
    sendArr.append(char(LOCAL_VIP));
    sendArr.append(char(DATA_TYPE_PARA));

    QByteArray dataArr;
    for(int i=0;i<MAX_VIP_NUM;i++)
    {
        VipProperty_Table *p = pBase+i;
        quint8 id = p->ucVipLineId;
        //qDebug()<<"cluster id"<<id;
        if(id>0&&id<MAX_VIP_NUM+1)
        {
            cnt++;
            dataArr.append((char*)p,tbSize);
            size += tbSize;
        }
    }
    sendArr.append(char(cnt));
    sendArr.append(dataArr);
    if(sendMessage(type,num,size,sendArr))
    {
        setStatusBarMessage(tr("发送vip属性表成功"));
        return true;
    }
    else
    {
        setStatusBarMessage(tr("发送vip属性表失败"));
        return false;
    }
}


quint8 PDataProcess::getVipId()
{
    VipProperty_Table *p = m_pVipInfo->tbVipProperty;
    for(int i=0;i<MAX_VIP_NUM;i++)
    {
        quint8 id = (p+i)->ucVipLineId;
        qDebug()<<"get vip Id i"<<i<<id;
        if(id==0)
        {
            (p+i)->ucVipLineId = i+1;
            return i+1;
        }
    }
    return 0;
}

void PDataProcess::cbVipIdChange(quint8 id)
{
    qDebug()<<"cbVipChange"<<id;
    if(id>0&&id<MAX_VIP_NUM+1)
    {
        m_ucCurVipId = id;
        m_pVip = m_pVipInfo->tbVipProperty+id-1;
        m_ListVipNodeId.clear();
        m_ListVipNodeStage.clear();
        m_ListVipNodeTime.clear();
        for(int i=0;i<MAX_VIP_NODE_COUNT;i++)
        {
            quint32 nodeId = qFromBigEndian<quint16>(m_pVip->usNodeIdList[i]);
            quint8 stageIndex = m_pVip->sStageIdList[i];
            quint16 offset = qFromBigEndian<quint16>(m_pVip->usTimeDifList[i]);
            qDebug()<<"vip node id"<<nodeId;
            if(nodeId>0)
            {
                m_ListVipNodeId.append(nodeId);
                m_ListVipNodeStage.append(stageIndex);
                m_ListVipNodeTime.append(offset);
            }
            else
            {
                break;
            }
        }
        //if(m_bFlagShowVip)
        {
            emit vipNodeListChange();
        }
        //m_ucVipNodeIndex = 0;
    }
    else
    {
        m_pVip = NULL;
    }
}

void PDataProcess::requireVipData()
{
    int cnt = m_ListVipNodeId.count();
    qDebug()<<cnt<<m_ListVipNodeId<<m_mapVip.count();
    for(int i=0;i<cnt;i++)
    {
        if(m_mapVip.contains(m_ListVipNodeId[i]))
        {
            qDebug()<<"stagecnt"<<m_ListVipNodeId[i]<<m_mapVip[m_ListVipNodeId[i]]->listStage.count();
        }
        else
        {
            qDebug()<<"no contains";
        }
    }

}

void PDataProcess::rcvVipNodeState(unsigned char *para1, int len, quint32 id)
{
    if(m_bFlagShowVip)
    {
//        requireAutoReport(0xf8,0,id);
//        m_bFlagVipStateCheck = false;
        qDebug()<<"rcvVipNodeState------------"<<id;
        if(len==25)//25字节
        {
            unsigned char p[24];
            memcpy(p,para1+1,len-1);

            QString statusStr;
            int index = m_TscIdList.indexOf(QString::number(id));
            if(index!=-1)
            {
                statusStr.append(m_TscNameList[index]);
            }
            bool bManual = false;
            switch(p[0]&0xf0)
            {
            case 0x60://手动
                bManual = true;
                statusStr.append(tr("手动"));
                break;

            case 0x10://多时段
                statusStr.append(tr("多时段"));
                break;

            case 0x20://系统优化
                statusStr.append(tr("系统优化"));
                break;
            case 0x30://无电线缆协调
                statusStr.append(tr("无电线缆协调"));
                break;

            case 0x70://感应
                statusStr.append(tr("感应"));
                break;
            case 0xa0://自适应
                statusStr.append(tr("自适应"));
                break;
            case 0xb0://面板控制
                statusStr.append(tr("面板控制"));
                break;
            default:
                statusStr.append(tr("未知控制"));
                break;
            }
    //        quint8 timeStage = p[3];
    //        m_ucStageNum = p[4];
            quint8 stageIndex = p[5];
            statusStr.append(tr("阶段号：%1").arg(stageIndex));
            setStatusBarMessage(statusStr,LBTHIRD);
            qDebug()<<"emit vipNodeState(id,bManual,stageIndex)"<<id<<bManual<<stageIndex;
            emit vipNodeState(id,bManual,stageIndex,true);
        }
        else
        {
            qDebug()<<"auto report len err"<<len;
        }
    }
    else
    {
        emit vipNodeState(id,false,0,false);
    }

}

/*
*/
void PDataProcess::rcvResponseInfo(QString tableName, char *para1)
{
    QString str;
    if(para1!=NULL)
    {
        if(*para1==0x01)
        {
            switch(*(para1+1))
            {
            case 0x00:
                str = QObject::tr("正确");
                break;
            case 0x01:
                str = QObject::tr("数据包格式错误");
                break;
            case 0x02:
                str = QObject::tr("登陆失败用户名错误");
                break;
            case 0x03:
                str = QObject::tr("登陆失败密码错误");
                break;
            case 0x04:
                str = QObject::tr("登陆失败需要用户名及密码验证");
                break;
            case 0x05:
                str = QObject::tr("登陆失败并发用户数过多");
                break;
            case 0x06:
                str = QObject::tr("登陆失败该用户已经登陆");
                break;
            case 0x07:
                str = QObject::tr("操作命令错误");
                break;
            case 0x08:
                str = QObject::tr("数据帧长度错误");
                break;
            case 0x09:
                str = QObject::tr("命令值错误");
                break;
            case 0x0a:
                str = QObject::tr("无此节点信息");
                break;
            case 0x0b:
                str = QObject::tr("发送给信号机时出现异常");
                break;
            case 0x0c:
                str = QObject::tr("同时存在多个用户操作，稍后重发");
                break;
            case 0x0d:
                str = QObject::tr("tsc返回错误消息长度太长");
                break;
            case 0x0e:
                str = QObject::tr("tsc返回错误消息类型错误");
                break;
            case 0x0f:
                str = QObject::tr("tsc返回错误设置的对象值");
                break;
            case 0x10:
                str = QObject::tr("tsc返回错误消息长度太短");
                break;
            case 0x11:
                str = QObject::tr("tsc返回错误其他错误");
                break;
            default:
                break;
            }
            emit statusBarMessage(QObject::tr("写")+tableName+str);
        }
    }
    else
    {
        emit statusBarMessage(tableName);
    }
}

void PDataProcess::startBroadCast(bool b)
{
    qDebug()<<"pdataprocess startboardcast b"<<b;
    m_ClientServ->startBroadCast(b);
}

/*
 时间 输入值为 控件显示时间，发送时+3600*8
*/
bool PDataProcess::requireTrafficStatistics(quint32 nodeId,quint32 dTime, quint32 startTime, quint32 endTime)
{
    if(nodeId==0&&startTime==0)
    {
        return false;
    }

    int type = CS_CMDTYPE_LOCAL_DATABASE_READ;//              = 0x60, 读本地数据库
    int num = 0;
    int size = 0;
    QByteArray sendArr;
    if(nodeId>0)
    {
        num = 1;
        size += 4;
//        size = 4+1+1+8;//id+cmd+para0+time
//        nodeId = 123;
        quint32 id = qToBigEndian<quint32>(nodeId);
        sendArr.append((char*)&id,4);
    }

    sendArr.append(char(LOCAL_TABLE_TRAFFICSTATISTICS));//      具体表名
    size++;

    sendArr.append(char(DATA_TYPE_PARA));
    size++;

    quint32 distime = qToBigEndian<quint32>(dTime);
    qDebug()<<"distime:"<<distime<<dTime;
    sendArr.append((char*)&distime,4);
    size+=4;
    if(startTime!=0)
    {
        size += 8;
//        startTime += 3600*8;
//        endTime += 3600*8;
        quint32 sTime = qToBigEndian<quint32>(startTime);
        quint32 eTime = qToBigEndian<quint32>(endTime);
        sendArr.append((char*)&sTime,4);
        sendArr.append((char*)&eTime,4);
    }
//    QDateTime t = QDateTime::fromTime_t(endTime);
//    QDateTime t1 = QDateTime::fromTime_t(startTime);
//    qDebug()<<"endTime"<<t.toString("yyyy-MM-dd hh:mm:ss")<<"startTime"<<startTime<<t1.toString("yyyy-MM-dd hh:mm:ss");

    if(sendMessage(type,num,size,sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 时间 输入值为 控件显示时间，发送时+3600*8
*/
bool PDataProcess::deleteTrafficStatistics(quint32 nodeId,quint32 disTime, quint32 startTime, quint32 endTime)
{
    if(nodeId==0&&startTime==0)
    {
        return false;
    }
    int type = CS_CMDTYPE_LOCAL_DATABASE_WRITE;//              = 0x62, 写本地数据库
    int num = 0;
    int size = 0;
    QByteArray sendArr;
    if(nodeId>0)
    {
        num = 1;

        size += 4;
        quint32 id = qToBigEndian<quint32>(nodeId);
        sendArr.append((char*)&id,4);
//        size = 4+1+1+8;//id+cmd+para0+time
    }

    if(startTime!=0)
    {
        sendArr.append(char(LOCAL_TABLE_TRAFFICSTATISTICS));//      具体表名
        size++;

        size += sizeof(quint32)*3+sizeof(quint8);
        sendArr.append(char(DATA_TYPE_PARA));
        sendArr.append((char*)&disTime,sizeof(quint32));
//        startTime += 3600*8;
//        endTime += 3600*8;
        quint32 sTime = qToBigEndian<quint32>(startTime);
        quint32 eTime = qToBigEndian<quint32>(endTime);
        sendArr.append((char*)&sTime,4);
        sendArr.append((char*)&eTime,4);
    }
    if(sendMessage(type,num,size,sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PDataProcess::dealTrafficStatistics(unsigned char *p, int)
{
    QString strBar;
    if(*p==0x01)
    {
        strBar = tr("读取交通流量统计失败");
    }
    else if(*p==0x00)
    {
        int emitcnt = 0;
        p++;
        strBar = tr("读取交通流量统计成功");

        quint32 bigMaxTime = 0;
        memcpy(&bigMaxTime,p,4);
        quint32 maxTime = qFromBigEndian<quint32>(bigMaxTime);
        p+=4;
        quint32 bigMinTime = 0;
        memcpy(&bigMinTime,p,4);
        quint32 minTime = qFromBigEndian<quint32>(bigMinTime);
        p+=4;
        quint32 bigVolume = 0;
        memcpy(&bigVolume,p,4);
        quint32 volume = qFromBigEndian<quint32>(bigVolume);
        p+=4;
        emit trafficMaxMinTime(maxTime,minTime,volume);

        quint32 bigCnt = 0;
        memcpy(&bigCnt,p,4);
        quint32 cnt = qFromBigEndian<quint32>(bigCnt);
        p+=4;//指向数据
        qDebug()<<"TrafficStatistics cnt"<<cnt;
        TrafficStatistics_Table *pTraffic = NULL;
        int modelCnt = m_pModelTraffic->rowCount();

        quint32 preNodeId = 0;
        quint8 preDetId = 0;
        QMap<quint32,quint32> mapData;

        QString strLine;//图形 名称
        for(quint32 i=0;i<cnt;i++)
        {
            quint32 bigNodeId = 0;
            memcpy(&bigNodeId,p,4);
            p+=4;
            quint32 nodeId = qFromBigEndian<quint32>(bigNodeId);

//            quint8 bigDetId = 0;
//            memcpy(&bigDetId,p,4);
//            p+=4;
            quint8 detId = *p;
            p++;

            quint32 bigTime = 0;
            memcpy(&bigTime,p,4);
            p+=4;
            quint32 time = qFromBigEndian<quint32>(bigTime)/*-3600*8*/;
            QDateTime t = QDateTime::fromTime_t(time);
            QString strTime = t.toString("yyyy-MM-dd hh:mm:ss");

            quint32 bigVol = 0;
            memcpy(&bigVol,p,4);
            p+=4;
            quint32 vol = qFromBigEndian<quint32>(bigVol);

            quint8 avgOcc = *p;
            p++;
            quint8 maxOcc = *p;
            p++;
            quint8 minOcc = *p;
            p++;

            int index = m_TscIdList.indexOf(QString::number(nodeId));
            QString strName;
            if(index!=-1)
            {
                strName = m_TscNameList[index];
            }
            else
            {
                strName = tr("节点ID%1").arg(nodeId);
            }
            QStringList list;
            list.append(strName);
            list.append(QString::number(detId));
            list.append(strTime);
            list.append(QString::number(vol));
            list.append(QString::number(avgOcc));
            list.append(QString::number(maxOcc));
            list.append(QString::number(minOcc));
            m_pModelTraffic->insertRow(modelCnt);
            m_pModelTraffic->setData(m_pModelTraffic->index(modelCnt,0),list.value(0),Qt::DisplayRole);
            m_pModelTraffic->setData(m_pModelTraffic->index(modelCnt,1),list.value(1),Qt::DisplayRole);
            m_pModelTraffic->setData(m_pModelTraffic->index(modelCnt,2),list.value(2),Qt::DisplayRole);
            m_pModelTraffic->setData(m_pModelTraffic->index(modelCnt,3),list.value(3),Qt::DisplayRole);
            m_pModelTraffic->setData(m_pModelTraffic->index(modelCnt,4),list.value(4),Qt::DisplayRole);
            m_pModelTraffic->setData(m_pModelTraffic->index(modelCnt,5),list.value(5),Qt::DisplayRole);
            m_pModelTraffic->setData(m_pModelTraffic->index(modelCnt,6),list.value(6),Qt::DisplayRole);
            modelCnt++;

            //----------图形显示--------------

            if((preNodeId!=nodeId||preDetId!=detId)&&i!=0)
            {
                QMap<quint32,quint32> map(mapData);
                emit trafficData(strLine,map);
                emitcnt++;
                qDebug()<<"emitcnt--------------"<<emitcnt<<strLine<<"mapData cnt"<<mapData.count();
                mapData.clear();
                preNodeId = nodeId;
                preDetId = detId;
            }
            else if(i==0)
            {
                preNodeId = nodeId;
                preDetId = detId;
                strLine.append(list[0]);
                strLine.append(tr(":det"));
                strLine.append(list[1]);
            }
            mapData.insert(time,vol);
            if(i==(cnt-1))
            {
                emitcnt++;
                qDebug()<<"emitcnt--------------"<<emitcnt<<"mapData cnt"<<mapData.count();
                QMap<quint32,quint32> map(mapData);
                emit trafficData(strLine,map);
            }
            strLine.clear();
            strLine.append(list[0]);
            strLine.append(tr(":det"));
            strLine.append(list[1]);
        }
    }
    emit completeTraffic();
    setStatusBarMessage(strBar);
}

void PDataProcess::btnSaveDataIni(int nodeIdIndex, QList<quint32>&tbList)
{
    quint32 nodeId = m_TscIdList[nodeIdIndex].toInt();
    if(m_mapTsc.contains(nodeId))
    {
        STscInfo* pTsc = m_mapTsc[nodeId];
        foreach(quint32 tb,tbList)
        {
            QByteArray dataArr;
            QString strName;
            if(getDataFromTable(tb,pTsc,dataArr,strName))
            {
                m_setData->setValue(strName,(QVariant)dataArr);
                setStatusBarMessage(strName.append(tr("保存成功")));
            }
            else
            {
                setStatusBarMessage(strName.append(tr("保存失败")));
            }
        }


    }
}

void PDataProcess::btnReadDataIni(int nodeIdIndex, QList<quint32> &tbList)
{
    quint32 nodeId = m_TscIdList[nodeIdIndex].toInt();
    if(m_mapTsc.contains(nodeId))
    {
        m_pTscInfo = m_mapTsc[nodeId];
        m_uiCurNodeId = nodeId;
        foreach(quint32 tb,tbList)
        {
            QString strName;
            if(getIniTableName(tb,strName))
            {
                QByteArray arr = m_setData->value(strName).toByteArray();
                dealMessage(arr);
                if(sendIniDataToServer(tb))
                {
                    setStatusBarMessage(strName.append(tr("录入成功")));
                }
                else
                {
                    setStatusBarMessage(strName.append(tr("录入失败")));
                }
            }
        }
    }
}

bool PDataProcess::getDataFromTable(quint32 cmd,STscInfo *pTsc, QByteArray &arr, QString &str)
{
    bool b = false;
    switch(cmd)
    {
    case TSC_TABLE_MODULE://        = 0x85,  //模块表
        str = tr("TSC_TABLE_MODULE");
        b = getDataFromTableModule(pTsc,arr,false);
        break;
    case TSC_TABLE_TIMEBASE://      = 0x8D,  //
        str = tr("TSC_TABLE_TIMEBASE");
        b = getDataFromTableTimeBase(pTsc,arr,false);
        break;
    case TSC_TABLE_SCHEDULE://      = 0x8E,  //时段表
        str = tr("TSC_TABLE_SCHEDULE");
        b = getDataFromTableSchedule(pTsc,arr,false);
        break;
    case TSC_TABLE_PHASE://         = 0x95,  //相位表
        str = tr("TSC_TABLE_PHASE");
        b = getDataFromTablePhase(pTsc,arr,false);
        break;
    case TSC_TABLE_PHASECONFLICT:// = 0x97,  //相位冲突表
        str = tr("TSC_TABLE_PHASECONFLICT");
        b = getDataFromTableConflict(pTsc,arr,false);
        break;
    case TSC_TABLE_DETECTOR://      = 0x9F,  //检测器表
        str = tr("TSC_TABLE_DETECTOR");
        b = getDataFromTableDet(pTsc,arr,false);
        break;
    case TSC_TABLE_CHANNEL://       = 0xB0,  //通道表
        str = tr("TSC_TABLE_CHANNEL");
        b = getDataFromTableChannel(pTsc,arr,false);
        break;
    case TSC_TABLE_TIMEPATTERN://   = 0xC0,  //配时方案表
        str = tr("TSC_TABLE_TIMEPATTERN");
        b = getDataFromTablePattern(pTsc,arr,false);
        break;
    case TSC_TABLE_STAGETIME://     = 0xC1,  //阶段配时表
        str = tr("TSC_TABLE_STAGETIME");
        b = getDataFromTableStage(pTsc,arr,false);
        break;
    case TSC_TABLE_OVERLAP://       = 0xC8,   //跟随相位表
        str = tr("TSC_TABLE_OVERLAP");
        b = getDataFromTableOverlap(pTsc,arr,false);
        break;
    case TBL_TABLE_PHASE2DIREC://   = 0xfa
        str = tr("TBL_TABLE_PHASE2DIREC");
        b = getDataFromTablePhaseMap(pTsc,arr,false);
        break;
    default:
        break;
    }
    return b;
}

bool PDataProcess::getIniTableName(quint32 cmd, QString &str)
{
    switch(cmd)
    {
    case TSC_TABLE_MODULE://        = 0x85,  //模块表
        str = tr("TSC_TABLE_MODULE");
        break;
    case TSC_TABLE_TIMEBASE://      = 0x8D,  //
        str = tr("TSC_TABLE_TIMEBASE");
        break;
    case TSC_TABLE_SCHEDULE://      = 0x8E,  //时段表
        str = tr("TSC_TABLE_SCHEDULE");
        break;
    case TSC_TABLE_PHASE://         = 0x95,  //相位表
        str = tr("TSC_TABLE_PHASE");
        break;
    case TSC_TABLE_PHASECONFLICT:// = 0x97,  //相位冲突表
        str = tr("TSC_TABLE_PHASECONFLICT");
        break;
    case TSC_TABLE_DETECTOR://      = 0x9F,  //检测器表
        str = tr("TSC_TABLE_DETECTOR");
        break;
    case TSC_TABLE_CHANNEL://       = 0xB0,  //通道表
        str = tr("TSC_TABLE_CHANNEL");
        break;
    case TSC_TABLE_TIMEPATTERN://   = 0xC0,  //配时方案表
        str = tr("TSC_TABLE_TIMEPATTERN");
        break;
    case TSC_TABLE_STAGETIME://     = 0xC1,  //阶段配时表
        str = tr("TSC_TABLE_STAGETIME");
        break;
    case TSC_TABLE_OVERLAP://       = 0xC8,   //跟随相位表
        str = tr("TSC_TABLE_OVERLAP");
        break;
    case TBL_TABLE_PHASE2DIREC://   = 0xfa
        str = tr("TBL_TABLE_PHASE2DIREC");
        break;
    default:
        break;
    }
    return !str.isEmpty();
}
void PDataProcess::setFlagReadIni(bool b)
{
    m_bFlagReadIni = b;
}

bool PDataProcess::sendIniDataToServer(quint32 cmd)
{
    bool b = false;
    switch(cmd)
    {
    case TSC_TABLE_MODULE://        = 0x85,  //模块表
        b = sendModuleToLib();
        break;
    case TSC_TABLE_TIMEBASE://      = 0x8D,  //
        b = sendTimeBaseToLib();
        break;
    case TSC_TABLE_SCHEDULE://      = 0x8E,  //时段表
        b = sendScheduleToLib();
        break;
    case TSC_TABLE_PHASE://         = 0x95,  //相位表
        b = sendPhaseTableToLib();
        break;
    case TSC_TABLE_PHASECONFLICT:// = 0x97,  //相位冲突表
        b = sendPhaseConflictTable();
        break;
    case TSC_TABLE_DETECTOR://      = 0x9F,  //检测器表
        b = sendDetectorToLib();
        break;
    case TSC_TABLE_CHANNEL://       = 0xB0,  //通道表
        b = sendChannelToLib();
        break;
    case TSC_TABLE_TIMEPATTERN://   = 0xC0,  //配时方案表
        b = sendTimePatternToLib();
        break;
    case TSC_TABLE_STAGETIME://     = 0xC1,  //阶段配时表
        b = sendStageTimeToLib();
        break;
    case TSC_TABLE_OVERLAP://       = 0xC8,   //跟随相位表
        b = sendOverlapToLib();
        break;
    case TBL_TABLE_PHASE2DIREC://   = 0xfa
        b = sendPhaseMapToLib();
        break;
    default:
        break;
    }
    return b;
}

void PDataProcess::setTreeSelect(int index)
{
    emit nodeChangeIndex(index);
}

/*
 获得m_tscIdList里没有的id编号
*/

quint32 PDataProcess::getNewNodeId()
{
    for(quint32 i=1;i<MAX_TSC_NUM;i++)
    {
        if(!m_TscIdList.contains(QString::number(i)))
        {
            return i;
        }
    }
    return 0;
}

quint32 PDataProcess::getCurrentNodeId()
{
    return m_uiCurNodeId;
}

void PDataProcess::setCurrentNodeId(quint32 nodeId)
{
    shutdownAutoReport();//改变节点前先清理主动上报状态
    m_uiCurNodeId = nodeId;
}

/*
检查节点名称是否可用
*/
bool PDataProcess::validTscName(QString strName,int index)
{
    QStringList tscNameList(m_TscNameList);
//    foreach(QString str,m_TscNameList)
//    {
//        tscNameList.append(str);
//    }


    if(index<tscNameList.count())
    {
        tscNameList.removeAt(index);
    }
//    qDebug()<<m_TscNameList.count()<<tscNameList.count();
    return (!tscNameList.contains(strName))&&(!strName.isEmpty());
//    return false;
}

bool PDataProcess::validTscIp(QString strIp,int index)
{
    QStringList tscIpList(m_TscIpList);

    if(index<tscIpList.count())
    {
        tscIpList.removeAt(index);
    }
    qDebug()<<m_TscIpList.count()<<tscIpList.count();

    return (!tscIpList.contains(strIp))&&numCheck(strIp);
}

bool PDataProcess::numCheck(QString str, bool b)
{
   char* arr = str.toAscii().data();
   int cnt = str.toAscii().count();
   for(int i=0;i<cnt;i++)
   {
       if(arr[i]<0x30||arr[i]>0x39)
       {
           if(b)
           {
               if(arr[i]!=0x2e)
               {
                   return false;
               }
               else
               {
                   continue;
               }
           }
           return false;
       }
   }
   return true&&(!str.isEmpty());
}

quint8 PDataProcess::getTimeBaseIndex(bool bSpe, bool bSum)//取得存储位置
{
    byte cnt = 0;
    byte base = 0;
    if(bSpe)
    {
        qDebug()<<"special day";
        cnt = byte(SUM_TIMEBASE_INDEX);
        base = 0;
    }
    else
    {
        cnt = byte(WIN_TIMEBASE_INDEX-SUM_TIMEBASE_INDEX);
        if(bSum)
        {
            base = byte(SUM_TIMEBASE_INDEX);
        }
        else
        {
            base = byte(WIN_TIMEBASE_INDEX);
        }
    }


    for(byte i=0;i<cnt;i++)
    {
        if(m_pTscInfo->tbTimeBase[base+i].bNo==0)
        {
            return base+i;
        }
    }
    return 0x80;//没有合适内存 表已满
}

/*
*/
//void PDataProcess::setListTimeBaseNameIndex(quint8 index)
//{
//    m_ucListTimeBaseNameIndex = index;
//}

//void PDataProcess::setFlagCluster(bool &b)
//{
//    m_bFlagCluster = b;
//}


/*
CS_CMDTYPE_NODE_REQUEST     = 0x30, //节点操作请求
参数1：
    NODE_ADD    = 0x10,   //新增节点
    NODE_DELETE = 0x11,   //删除节点
    NODE_UPDATE = 0x12,   //修改节点
    NODE_READ   = 0x13,   //节点读取
    NODE_WRITE  = 0x14    //节点写
参数2：
    STscNode*
*/
bool PDataProcess::sendNodeCommand(int cmd, STscNode *node)
{
    int nameLen = strlen(node->sDeviceName);
    int ipLen = strlen(node->sDeviceIp);
    int verLen = strlen(node->sVersion);

    int type = CS_CMDTYPE_NODE_REQUEST;
    int num = 0;
    int size = 2+10+3+nameLen+ipLen+verLen;//cmd+para1+10+3len+...
    if(cmd==NODE_DELETE)
    {
        size = 1+1+4;//cmd+para1+nodeId;
    }

    int sendLen = m_iheadSize + size;
    //qDebug()<<"send NodeCommand";

    htonlHead(type,num,size);
    QByteArray sendArr;
    sendArr.append((const char*)m_pSendMsgHead,m_iheadSize);

    //qDebug()<<"after head arrLen"<<sendArr.length();

    sendArr.append(char(cmd));

    //qDebug()<<"after cmd arrLen"<<sendArr.length();

    sendArr.append(char(DATA_TYPE_PARA));

    //qDebug()<<"arrLen"<<sendArr.length();

    //qDebug()<<"uiId"<<sizeof(node->uiId);
    unsigned int id = qToBigEndian<quint32>(node->uiId);

    sendArr.append((char*)&id,sizeof(unsigned int));

    //qDebug()<<"after uiid arrLen"<<sendArr.length();

    if(cmd==NODE_DELETE)
    {
        if(sendLen==m_ClientServ->sendData(sendArr))
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    sendArr.append(node->ucClusterId);
    sendArr.append(node->ucClusterNodeIndex);
    //qDebug()<<"after clusterid arrLen"<<sendArr.length();

    sendArr.append(char(nameLen));

    //qDebug()<<"after namelen arrLen"<<sendArr.length();

    sendArr.append(node->sDeviceName,nameLen);

    //qDebug()<<"after name arrLen"<<sendArr.length();

    sendArr.append(char(ipLen));

    //qDebug()<<"after iplen arrLen"<<sendArr.length();

    sendArr.append(node->sDeviceIp,ipLen);

    //qDebug()<<"send ip:"<<node->sDeviceIp.GetData();
//    unsigned short port = htons(node->uiPort);
    unsigned short port = qToBigEndian<quint16>(node->uiPort);

    sendArr.append((char*)&port,sizeof(unsigned short));

    //qDebug()<<"after port arrLen"<<sendArr.length();

    sendArr.append(char(verLen));

    //qDebug()<<"after verlen arrLen"<<sendArr.length();

    sendArr.append(node->sVersion,verLen);

    //qDebug()<<"after ver arrLen"<<sendArr.length();

    sendArr.append(node->ucLinkType);

    //qDebug()<<"after linktype arrLen"<<sendArr.length();

    sendArr.append(node->ucProtocolType);

    //qDebug()<<"after protype arrLen"<<sendArr.length();

    if(sendLen==m_ClientServ->sendData(sendArr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PDataProcess::dealNodeCommandAdd(char* para1,int )
{
    if(*para1==0x01)
    {
        switch(*(++para1))
        {
        case CS_ERRTYPE_RIGHT://添加节点成功
            {
                emit receivedNodeCommand(NODE_ADD,true);
                break;
            }

        default:
            break;
        }
    }
}

void PDataProcess::dealNodeCommandEdit(char* para1,int)
{
    if(*para1==0x01)
    {
        switch(*(++para1))
        {
        case CS_ERRTYPE_RIGHT://修改节点成功
            {
                emit receivedNodeCommand(NODE_UPDATE,true);
                break;
            }

        default:
            break;
        }
    }
}

void PDataProcess::dealNodeCommandDel(char* para1,int)
{
    if(*para1==0x01)
    {
        switch(*(++para1))
        {
        case CS_ERRTYPE_RIGHT://删除节点成功
            {
                emit receivedNodeCommand(NODE_DELETE,true);
                break;
            }

        default:
            break;
        }
    }
}

void PDataProcess::addNode(STscNode *tscNode)
{
    m_iCurTscNameLisIndex = m_TscNameList.count();
    m_TscIdList.append(QString::number(tscNode->uiId));
    m_TscClusterIdList.append(tscNode->ucClusterId);
    m_TscNameList.append(QString::fromLocal8Bit(tscNode->sDeviceName,strlen(tscNode->sDeviceName)));
    m_TscIpList.append(QString::fromAscii(tscNode->sDeviceIp,strlen(tscNode->sDeviceIp)));
    m_TscPortList.append(tscNode->uiPort);
    m_TscVersionList.append(tscNode->sVersion);
    m_TscLinkTypeList.append(tscNode->ucLinkType);
    m_TscProtocolList.append(tscNode->ucProtocolType);

    m_bFlagTscNameList = true;
    m_bFlagTscIdList = true;
    qDebug()<<"addnode";
    setModelItem();//List有更改就 更改model
}

void PDataProcess::editNode(STscNode *tscNode,int listIndex)
{
    m_iCurTscNameLisIndex = listIndex;

    m_TscNameList.replace(listIndex,QString::fromLocal8Bit(tscNode->sDeviceName,strlen(tscNode->sDeviceName)));
    m_TscClusterIdList.replace(listIndex,tscNode->ucClusterId);
    m_TscIpList.replace(listIndex,QString::fromAscii(tscNode->sDeviceIp,strlen(tscNode->sDeviceIp)));
    m_TscPortList.replace(listIndex,tscNode->uiPort);
    m_TscProtocolList.replace(listIndex,tscNode->ucProtocolType);
    qDebug()<<"editnode";
    m_bFlagTscNameList = true;
    setModelItem();//List有更改就 更改model
}

void PDataProcess::delNode(int listIndex)
{
    if(listIndex == m_TscNameList.count()-1)
    {
        m_iCurTscNameLisIndex = listIndex - 1;//显示前一个
    }
    else
    {
        m_iCurTscNameLisIndex = listIndex;//显示后一个
        //qDebug()<<"del Index:"<<m_iCurTscNameLisIndex;
    }

    qDebug()<<"deal listindex"<<listIndex;

    m_TscIdList.removeAt(listIndex);
    m_TscClusterIdList.removeAt(listIndex);
    m_TscNameList.removeAt(listIndex);
    m_TscIpList.removeAt(listIndex);
    m_TscPortList.removeAt(listIndex);
//    m_TscVersionList.removeAt(listIndex);
//    m_TscLinkTypeList.removeAt(listIndex);
//    m_TscProtocolList.removeAt(listIndex);

    m_bFlagTscNameList = true;
    m_bFlagTscIdList = true;
    setModelItem();//List有更改就 更改model
}

bool PDataProcess::addNode()
{
    quint32 id = getNewNodeId();
    if(id!=0)
    {
        m_TscIdList.append(QString::number(id));
        m_TscClusterIdList.append(1);
        m_TscNameList.append(tr(""));
        m_TscIpList.append(tr(""));

        m_TscPortList.append(5435);
        m_iCurTscNameLisIndex = m_TscIdList.count()-1;
        m_bFlagTscNameList = true;
        m_bFlagTscIdList = true;
//        setModelItem();//List有更改就 更改model

        initMapTable();
        return true;
    }
    else
    {
       return false;
    }


}

void PDataProcess::setServiceInfo(QString addr, QString port)
{
    m_strAddress.clear();
    m_strPort.clear();
    m_strAddress.append(addr);
    m_strPort.append(port);
}

void PDataProcess::setModelItem()
{
    if(m_bFlagTscNameList||!m_bFlagCTInit||!m_bFlagVipInit||m_bFlagCtNode)
    {
        m_bFlagVipInit = false;//为了列表
        //m_TscNameModel->clear();
        //m_TscNameModel->removeRows(0,m_TscNameModel->rowCount());
       //qDebug()<<"m_TscNameModel->rowCount()"<<m_TscNameModel->columnCount();
//qDebug()<<"m_TscNameIconModel->rowCount()"<<m_TscNameIconModel->rowCount();
        m_TscNameIconModel->removeRows(0,m_TscNameIconModel->rowCount());


        int nameListCnt = m_TscNameList.count();

        QIcon nodeIcon(":/Files/images/trafficlightsign.png");
        QIcon ctIcon(":/Files/images/Cluster.png");
        QIcon dmtIcon(":/Files/images/Domain.png");
        QIcon vipIcon(":/Files/images/Vip.png");
        int ctNameCnt = m_ListCTName.count();

        int vipCnt = m_ListVipId.count();

        QStandardItem *parentItem = m_TscNameIconModel->invisibleRootItem();
        switch(m_iTabWidgetIndex)
        {
        case 0:
            break;
        case 1://显示全节点
            {
                foreach(QString str,m_TscNameList)
                {
                    QStandardItem *tscItem = new QStandardItem(nodeIcon,str);
                    parentItem->appendRow(tscItem);
                }
//                m_bFlagTscNameList = false;
                QString title = tr("节点列表");
                m_TscNameIconModel->setHeaderData(0,Qt::Horizontal,title);
            }
            break;
        case 2:
            {
                m_ListClusterIndex.clear();
                for (int i = 0; i < ctNameCnt; ++i)
                {
                    QStandardItem *item = new QStandardItem(ctIcon,m_ListCTName[i]);
                    parentItem->appendRow(item);
                    //item->setDragEnabled(true);

                    item->setDropEnabled(true);

                    QModelIndex ctIndex = m_TscNameIconModel->index(i,0,QModelIndex());
                    m_ListClusterIndex.append(ctIndex);
                }
                for(int i=0;i<nameListCnt;i++)//所有节点
                {

                    quint8 ctId = m_TscClusterIdList[i];//从节点处 得到 群id

                    int ctIdIndex = -1;
                    if(ctId>0)
                    {
                        ctIdIndex = m_ListCTId.indexOf(QString::number(ctId));
                    }
                    //quint8 ctIdIndex = m_ListCTId.indexOf(QString::number(ctId));//得到 ctname index

                    if(ctIdIndex==-1)
                    {
                        ctIdIndex = 0;
                    }
                    if(ctIdIndex<m_ListClusterIndex.count())
                    {
                        parentItem = m_TscNameIconModel->itemFromIndex(m_ListClusterIndex[ctIdIndex]);

                        QStandardItem* item = new QStandardItem(nodeIcon,m_TscNameList[i]);

                        item->setDragEnabled(true);
                        //item->setDropEnabled(true);
                        parentItem->appendRow(item);
                    }
                    else
                    {
                        qDebug()<<"ctidindex:"<<ctIdIndex<<"m_ListClusterIndex.count()"<<m_ListClusterIndex.count();
                    }
                }
            }
            break;
        case 3:
            {
                foreach(QString str,m_TscNameList)
                {
                    QStandardItem *tscItem = new QStandardItem(nodeIcon,str);
                    parentItem->appendRow(tscItem);
                }
                for(int i=0;i<vipCnt;i++)
                {
                    quint8 vipId = m_ListVipId[i];

                    if(vipId>0&&vipId<MAX_VIP_NUM+1)
                    {
                        QStandardItem *item = new QStandardItem(vipIcon,tr("Vip%1").arg(vipId));
                        parentItem->appendRow(item);
                        item->setDropEnabled(true);
                        VipProperty_Table *p = m_pVipInfo->tbVipProperty+vipId-1;
                        for(int j=0;j<MAX_VIP_NODE_COUNT;j++)
                        {
                            quint16 nodeId = qFromBigEndian<quint16>(p->usNodeIdList[j]);

                            if(nodeId>0)
                            {
                                int nodeIndex = m_TscIdList.indexOf(QString::number(nodeId));

                                if(nodeIndex!=-1)
                                {
                                    QString nodeStr = m_TscNameList[nodeIndex];

                                    QStandardItem *vItem = new QStandardItem(nodeIcon,nodeStr);
                                    item->appendRow(vItem);
                                }
                            }
                        }
//                        QModelIndex ctIndex = m_TscNameIconModel->index(i,0,QModelIndex());
//                        m_ListClusterIndex.append(ctIndex);
                    }
                }
            }
            break;
        default:
            break;
        }
/*
        m_ListClusterIndex.clear();
        for (int i = 0; i < ctNameCnt; ++i)
        {
            QStandardItem *item = new QStandardItem(ctIcon,m_ListCTName[i]);
            parentItem->appendRow(item);
            //item->setDragEnabled(true);

            item->setDropEnabled(true);

            QModelIndex ctIndex = m_TscNameIconModel->index(i,0,QModelIndex());
            m_ListClusterIndex.append(ctIndex);
        }
        for(int i=0;i<vipCnt;i++)
        {
            quint8 vipId = m_ListVipId[i];

            if(vipId>0&&vipId<MAX_VIP_NUM+1)
            {
                QStandardItem *item = new QStandardItem(vipIcon,tr("Vip%1").arg(vipId));
                parentItem->appendRow(item);
                item->setDropEnabled(true);
                VipProperty_Table *p = m_pVipInfo->tbVipProperty+vipId-1;
                for(int j=0;j<MAX_VIP_NODE_COUNT;j++)
                {
                    quint16 nodeId = qFromBigEndian<quint16>(p->usNodeIdList[j]);

                    if(nodeId>0)
                    {
                        int nodeIndex = m_TscIdList.indexOf(QString::number(nodeId));

                        if(nodeIndex!=-1)
                        {
                            QString nodeStr = m_TscNameList[nodeIndex];

                            QStandardItem *vItem = new QStandardItem(nodeIcon,nodeStr);
                            item->appendRow(vItem);
                        }
                    }
                }
                QModelIndex ctIndex = m_TscNameIconModel->index(i,0,QModelIndex());
                m_ListClusterIndex.append(ctIndex);
            }
        }
        //QStandardItem *parentName = m_TscNameModel->invisibleRootItem();

        for(int i=0;i<nameListCnt;i++)//所有节点
        {

            quint8 ctId = m_TscClusterIdList[i];//从节点处 得到 群id

            int ctIdIndex = -1;
            if(ctId>0)
            {
                ctIdIndex = m_ListCTId.indexOf(QString::number(ctId));
            }
            //quint8 ctIdIndex = m_ListCTId.indexOf(QString::number(ctId));//得到 ctname index

            if(ctIdIndex==-1)
            {
                ctIdIndex = 0;
            }
            if(ctIdIndex<m_ListClusterIndex.count())
            {
                parentItem = m_TscNameIconModel->itemFromIndex(m_ListClusterIndex[ctIdIndex]);

                QStandardItem* item = new QStandardItem(nodeIcon,m_TscNameList[i]);

                item->setDragEnabled(true);
                //item->setDropEnabled(true);
                parentItem->appendRow(item);
            }
            else
            {
                qDebug()<<"ctidindex:"<<ctIdIndex<<"m_ListClusterIndex.count()"<<m_ListClusterIndex.count();
            }
//
        }*/
        if(m_bFlagTscNameList)
        {
            m_TscNameModel->setStringList(m_TscNameList);
            m_EventNameModel->setStringList(m_TscNameList);
            if(ckNodeNameDeligate!=NULL)
            {
                delete ckNodeNameDeligate;
            }

            ckNodeNameDeligate = new CheckGroupDeligate(m_TscNameList);
            if(m_iCurTscNameLisIndex>=0)
            {
                //qDebug()<<"listIndex:"<<m_iCurTscNameLisIndex;
                emit resetNodeNameModel(m_iCurTscNameLisIndex);
            }
        }

        m_bFlagTscNameList = false;
        m_bFlagCTInit = true;
        m_bFlagVipInit = true;//列表完成
    }


    if(m_bFlagTscIdList)
    {
        m_TscIdModel->setStringList(m_TscIdList);
        m_bFlagTscIdList = false;
    }

//    if(m_bFlagModuleName)
//    {
//        qDebug()<<"setmodulemodelname";
//        m_pModelModuleName->setStringList(m_ListModuleName);
//        m_bFlagModuleName = false;
//    }


    if(m_bFlagScheduleName)
    {
        if(m_bFlagCluster)
        {
            m_pModelEvent->setHeaderData(3,Qt::Horizontal,QObject::tr("群周期"));
        }
        else
        {
            //m_pModelEvent->setHeaderData(3,Qt::Horizontal,QObject::tr("辅助输出"));
        }
        m_pModelScheduleName->setStringList(m_ListScheduleName);
        m_bFlagScheduleName = false;
    }
//    if(m_bFlagTimePatternName)
//    {
//        qDebug()<<"m_pModelTimePatternName cnt"<<m_pModelTimePatternName->rowCount();
//        m_pModelTimePatternName->removeRows(0,m_pModelTimePatternName->rowCount());
//        m_pModelTimePatternName->setStringList(m_ListTimePatternName);
//        m_bFlagTimePatternName = false;
//        emit updateTimePatternName();
//    }
//    if(m_bFlagStageTimeName)
//    {
//        m_pModelStageTimeName->removeRows(0,m_pModelStageTimeName->rowCount());
//        m_pModelStageTimeName->setStringList(m_ListStageTimeName);
//        m_bFlagStageTimeName = false;
//        emit updateStageTimeName();//0406
//    }
//    if(m_bFlagEventLog)
//    {
//        m_bFlagEventLog = false;
//        m_pModelEventLog->removeRows(0,m_pModelEventLog->rowCount(QModelIndex()),QModelIndex());
//    }
}
/*
b=true 开启计时器
false  关闭计时器
*/
void PDataProcess::timerManage(bool b)
{
    qDebug()<<"enter timer mangae";
    if(!(timer->isActive())&&b)
    {
        qDebug()<<"start timer";
        timer->start(TIMEOUT5000);
    }
    else if(timer->isActive()&&!b)
    {
        qDebug()<<"stop timer";
        timer->stop();
    }
}

void PDataProcess::timerEvent(QTimerEvent *e)
{
    if(m_iTimerId==e->timerId())
    {
        if(m_bFlagOnLine)
            qDebug()<<"-------------------------------------------------------";
        m_bFlagOnLine = false;
        qDebug()<<"timeout"<<m_uiCurNodeId<<tr("0x%1").arg(m_ucTableName,2,16);
        this->killTimer(m_iTimerId);
        this->requireDataBaseTable(m_ucTableName,m_uiCurNodeId);
    }
}

void PDataProcess::setStatusBarMessage(QString str, quint8 index)
{
    emit statusBarMessage(str,index);
}

void PDataProcess::dealMessage(QByteArray byteArr)
{

    QByteArray temp;
    bool bTemp = false;

    emit recvMessage(byteArr,false);//1115try
    int rcvLen = byteArr.count();
    //qDebug()<<"dealmessage rcv len:"<<rcvLen;
    char* rcv = byteArr.data();
    //emit receivedDP(byteArr);
    if(m_bComplete)
    {

        memcpy(m_pRcvMsgHead,rcv,m_iheadSize);
        m_iHeadType = qFromBigEndian<quint32>(m_pRcvMsgHead->uiCommandType);
        m_iHeadNum = qFromBigEndian<quint32>(m_pRcvMsgHead->uiIdNum);//
        //qDebug()<<"m_iHeadNum:"<<m_iHeadNum<<m_pRcvMsgHead->uiIdNum<<rcvLen;
        if(m_iHeadNum>255)
        {
            return;
        }
        m_iHeadSize = qFromBigEndian<quint32>(m_pRcvMsgHead->uiDataSize);
        m_iDataLong = m_iHeadSize+12;
        qDebug()<<"must rcv len"<<m_iDataLong<<"real rcv"<<rcvLen;
    }
    else
    {
        qDebug()<<"m_bComplete false";
    }
    if(rcvLen<m_iDataLong)
    {
        qDebug()<<"dealmessage rcv m_iDataLong:"<<m_iDataLong<<rcvLen;
        m_cRcvData.append(rcv,rcvLen);
//        memcpy(m_cRcvData+m_iComplete,rcv,rcvLen);
        m_iComplete += rcvLen;
    }
    else
    {
        if(rcvLen>(m_iDataLong-m_iComplete))
        {
            qDebug()<<"+++++++++++++++++++++++++++++rcvLen>(m_iDataLong-m_iComplete++++++++++==============++++++++++++++++++++++++++++++++++++++++++++++";
//            memcpy(m_cRcvData+m_iComplete,rcv,(m_iDataLong-m_iComplete));
            m_cRcvData.append(rcv,(m_iDataLong-m_iComplete));
            temp.append(rcv+m_iDataLong-m_iComplete,rcvLen-(m_iDataLong-m_iComplete));
            bTemp = true;
        }
        else//相等
        {
//            memcpy(m_cRcvData+m_iComplete,rcv,m_iDataLong);
            m_cRcvData.append(rcv,m_iDataLong);
        }
        m_iComplete = m_iDataLong;
    }

    if(m_iDataLong==m_iComplete)
    {
        m_cRcvData.append('\0');
        m_iComplete = 0;
        m_bComplete = true;
        qDebug()<<"dealmessage rcv m_iDataLong:"<<m_iDataLong;
    }
    else
    {
        m_bComplete = false;
        return;
    }
    quint32 nodeId = 0;
    memcpy(&nodeId,m_cRcvData.data()+m_iheadSize,sizeof(nodeId));
   // if()
    if(m_bFlagVipStateCheck)
    {
        qDebug()<<"dealMessage-----------------m_iCurVipNodeId"<<m_iCurVipNodeId;
        m_iCurVipNodeId = qFromBigEndian<quint32>(nodeId);
    }

    byte cmd = *(m_cRcvData.data()+m_iheadSize+m_iHeadNum*4);
    qDebug()<<"dealmessage m_iHeadType cmd"<<m_iHeadType<<cmd;
    char *para1 = m_cRcvData.data()+m_iheadSize+m_iHeadNum*4+1;//指向参数1
    int len = m_iHeadSize-1-m_iHeadNum*4;

    if(m_bFlagTscTable)
    {
        if(cmd!=TSC_COMMAND_REPORTSELF&&cmd!=TSC_STATUS_DETECTORSTS&&cmd!=TSC_STATUS_DETECTORWARN_TABLE)
        {
            m_bFlagTscTable = false;
            this->killTimer(m_iTimerId);
        }
    }

    switch(m_iHeadType)
    {

    case CS_CMDTYPE_USR_RESPONSE://用户操作请求回值
        {

            switch(cmd)
            {
            case USER_ADD:
                {
                    break;
                }
            case USER_DELETE:
                {
                    break;
                }
            case USER_UPDATE:
                {
                    break;
                }
            case USER_READ:
                {
                    emit receivedUserView(para1,len);
                    break;
                }
            case USER_WRITE://用户列表写
                {
                    break;
                }
            case USER_IN:
                {
                    emit receivedUserLogin(para1,len);
                    break;
                }

            case USER_OUT:
                {
                    break;
                }
            default:
                break;
            }

            break;
        }
    case CS_CMDTYPE_NODE_RESPONSE://    = 0x31, //节点操作返回值
        {
            switch(cmd)
            {
            case NODE_ADD://    = 0x10,   //新增节点
                {
                    requireTscInfoTable();
//                    dealNodeCommandAdd(para1,len);
                    break;
                }
            case NODE_DELETE:// = 0x11,   //删除节点
                {
                    requireTscInfoTable();
//                    dealNodeCommandDel(para1,len);
                    break;
                }
            case NODE_UPDATE:// = 0x12,   //修改节点
                {
                    if(m_bFlagClusterSend)
                    {
//                        dealCtNodeInforResponse((unsigned char*)para1,len);
                    }
                    else
                    {
                        if(!m_bFlagCtNode)
                        {
                            dealNodeCommandEdit(para1,len);
                        }
                        else
                        {
                            if(m_bFlagUpDateCTNode)
                            {
                                sendClusterInfoToLib();
                                //sendClusterPattern();
                            }
                            m_bFlagCtNode = false;
                        }
                    }
                    break;
                }
            case NODE_READ://   = 0x13,   //节点读取
                {
                    qDebug()<<"rcv 节点表";
                    dealTscInfoTable(para1,len);
                    break;
                }
            case NODE_WRITE://  = 0x14    //节点写
                {
                    qDebug()<<tr("写节点表");
                    break;
                }

            default:
                break;
            }
            break;
        }

    case CS_CMDTYPE_TSC_PARA_READ_RESPONSE://读信号机参数信息
        m_bFlagOnLine = true;
    case CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE:
        {
//            QString statusStr;
//            if(!m_bFlagCluster&&m_TscIdList.count()>0)
//            {
//                int index = m_TscIdList.indexOf(QString::number(m_uiCurNodeId));
//                statusStr.append(tr("当前节点:%1 ").arg(m_TscNameList[index]));
//                if(m_bFlagOnLine)
//                {
//                    statusStr.append(tr("在线  "));
//                }
//                else
//                {
//                    statusStr.append(tr("离线  "));
//                }
//                emit statusBarMessage(statusStr,LBTHIRD);
//            }

            switch(cmd)
            {qDebug()<<"deal switch";
//            case LOCAL_TABLE_USERINFO://用户表
//                {
//                    emit receivedUserView(para1,len);
//                    break;
//                }
//            case LOCAL_TABLE_NODE://节点表
//                {
//                    dealTscInfoTable(para1,len);
//                    break;
//                }
            case TSC_TABLE_MODULE://模块表
                {
                    dealTscModuleTable((unsigned char*)para1,len);
                    break;
                }
            case TSC_TABLE_TIMEBASE://时基表
                {
                    dealTscTimeBaseTable(para1,len);
                    break;
                }
            case TSC_TABLE_SCHEDULE://时段表
                {qDebug()<<"deal TSC_TABLE_SCHEDULE";
                    dealTscScheduleTable(para1,len);
                    break;
                }
            case TSC_TABLE_TIMEPATTERN://配时方案表
                {
                    dealTscTimePatternTable(para1,len);
//                    qDebug()<<"deal time pattern";
//                    if(/*!m_bFlagClusterSend||*/m_bFlagNodeIdChanged)
//                    {
//                        dealTscTimePatternTable(para1,len);
//                    }
//                    else
//                    {
//                        int tbSize = sizeof(TimePattern_Table);
//                        if(len>tbSize)
//                        {
//                            quint8 tbCnt = *(++para1);
//                            if(len==(tbSize*tbCnt+2))
//                            {
////                                dealClusterPattern((unsigned char*)rcv,rcvLen);
//                            }
//                        }
//                    }
                    break;
                }
            case TSC_TABLE_STAGETIME://阶段配时表
                {
                    dealTscStageTime(para1,len);
                    break;
                }
            case TSC_TABLE_PHASECONFLICT://冲突相位表
                {
                    dealTscPhaseConflictTable((unsigned char*)para1,len);
                    break;
                }
            case TSC_TABLE_PHASE://相位表
                {
                    dealTscPhaseTable(para1,len);
                    break;
                }
            case TSC_TABLE_OVERLAP:
                {
                    dealTscOverlapTable(para1,len);
                    break;
                }
            case TSC_TABLE_CHANNEL:
                {
                    dealTscChannelTable(para1,len);
                    break;
                }
            case TBL_TABLE_PHASE2DIREC:
                {
                    if(m_bFlagDetRead)
                    {
                        m_bFlagDetRead = false;
                        requireTscTable(TSC_TABLE_DETECTOR);
                    }
                    if(m_bFlagDetSend)
                    {
                        m_bFlagDetSend = false;
                        requireTscTable(TSC_TABLE_DETECTOR);
                    }

                    dealTscPhaseMapTable(para1,len);
                    break;
                }
            case TSC_COMMAND_UTC_TIME:
                {
                    quint32 time = 0;
                    memcpy(&time,para1+1,4);
//                    quint32 t = ntohl(time);
                      quint32 t = qFromBigEndian<quint32>(time);
                    emit rcvTscTime(t);
                    break;
                }
            case TSC_TABLE_DETECTOR:
                {
                    dealTscDetectorTable((unsigned char*)para1,len);
                    break;
                }
            case TSC_TABLE_EVENTLOG: //(0X92)
                {
                    dealTscEventLogTalbe((unsigned char*)para1,len);
                    break;
                }
            case LOCAL_TABLE_TRAFFICSTATISTICS://交通流量统计
                {
                    dealTrafficStatistics((unsigned char*)para1,len);
                    break;
                }
//------------------------------------------------------------------
            case CLUSTER_PROPERTY:
                dealClusterInfo((unsigned char*)para1,len);
                break;
            case CLUSTER_TIMEBASE:
                dealClusterTimeBase((unsigned char*)para1,len);
                break;
            case CLUSTER_SCHEDULE:
                dealClusterSchedule((unsigned char*)para1,len);
                break;
            case CLUSTER_TIMEPATTERN:
                dealClusterPattern((unsigned char*)para1,len);
                break;
            case LOCAL_VIP:
                dealVipInfo((unsigned char*)para1,len);
                break;
            default:
                break;


            }
            break;
        }

//    case CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE://读本地数据库返回值
//        {
//            switch(cmd)
//            {
//            case CLUSTER_PROPERTY:
//                dealClusterInfo((unsigned char*)para1,len);
//                break;
//            case CLUSTER_TIMEBASE:
//                dealClusterTimeBase((unsigned char*)para1,len);
//                break;
//            case CLUSTER_SCHEDULE:
//                dealClusterSchedule((unsigned char*)para1,len);
//                break;
//            case LOCAL_VIP:
//                dealVipInfo((unsigned char*)para1,len);
//                break;
//            default:
//                break;
//            }
//            break;
//        }
    case CS_CMDTYPE_LOCAL_DATABASE_WRITE_RESPONSE://    = 0x63, //写本地数据库返回值
        {
            switch(cmd)
            {
            case CLUSTER_PROPERTY:
                rcvResponseInfo(tr("群数据库"),para1);

//                requireClusterInfoTable();
                if(*(para1+1)==0)
                {qDebug()<<"write CLUSTER_PROPERTY sueecss and send clusterpattern";
                    if(m_bFlagClusterSend)
                    {
                        m_bFlagClusterSend = false;
                        sendClusterPattern();
                    }
                    analyseClusterInfo();
                    m_bFlagCTInit = false;

                    m_bFlagUpDateCTNode = false;
                    setModelItem();
                    initMapTable();
                }
                else
                {
                    requireClusterInfoTable();
                }


                break;
            case CLUSTER_TIMEBASE://时基表
                {
                    rcvResponseInfo(tr("群时基"),para1);
                    emit receivedTimeBaseResponse(para1,len);
                    //if(*(++para1)==0)
                    {
                        int index = m_ListCTId.indexOf(QString::number(m_ucCurClusterId));
                        QString str;
                        if(index!=-1)
                        {
                            str.append(m_ListCTName[index]);
                            str.append(tr(" 写群时基成功"));
//                            emit statusBarMessage(str/*,LBTHIRD*/);
                            qDebug()<<"==========="<<str;
                        }
                    }
                    break;
                }
            case CLUSTER_SCHEDULE:
                {
                    rcvResponseInfo(tr("群时段"),para1);
                    emit receivedScheduleResponse(para1,len);
                    //if(*(++para1)==0)
                    {
                        int index = m_ListCTId.indexOf(QString::number(m_ucCurClusterId));
                        QString str;
                        if(index!=-1)
                        {
                            str.append(m_ListCTName[index]);
                            str.append(tr(" 写群时段成功"));
//                            emit statusBarMessage(str/*,LBTHIRD*/);
                            qDebug()<<"==========="<<str;
                        }
                    }

                    break;
                }
            case CLUSTER_TIMEPATTERN:
                {rcvResponseInfo(tr("群方案"),para1);
                    qDebug()<<"write CLUSTER_TIMEPATTERN -------";
                    if(*para1==1&&*(para1+1)==0)
                    {
                        analyseClusterPatternTable();
                    }
                    else
                    {
                        requireDataBaseTable(CLUSTER_TIMEPATTERN,m_ucCurClusterId);
                    }
                    break;
                }
            case LOCAL_VIP:
                {rcvResponseInfo(tr("vip属性表"),para1);
                    requireVipInfoTable();
                    //if(*(++para1)==0)
                    {
                        int index = m_ListVipId.indexOf(m_ucCurVipId);
                        QString str;
                        if(index!=-1)
                        {
                            str.append(tr("Vip%1").arg(m_ucCurVipId));
                            str.append(tr(" 紧急路线设置成功"));
                            emit statusBarMessage(str,LBTHIRD);
                            qDebug()<<"==========="<<str;
                        }
                    }
                    break;
                }
            case LOCAL_TABLE_TRAFFICSTATISTICS://交通流量统计
                {
                    rcvResponseInfo(tr("删除交通流量表"),para1);
                    break;
                }
            default:
                break;
            }
            break;
        }
    case CS_CMDTYPE_TSC_PARA_WRITE_RESPONSE://写信号机参数信息
        {
            switch(cmd)
            {
            case TSC_TABLE_MODULE://模块表
                {
                    rcvResponseInfo(tr("模块表"),para1);
                    if(!m_bFlagReadIni)
                    {
                        requireTscTable(TSC_TABLE_MODULE);
                    }
                    break;
                }
            case TSC_TABLE_TIMEBASE://时基表
                {
                    rcvResponseInfo(tr("时基表"),para1);
                    if(m_bFlagSendCTPlan)
                    {
                        quint8 p2 = *(para1+1);
                        if(*para1==1&&p2==0)
                        {qDebug()<<m_ListCTNodeName[m_ucSendCTPlanIndex]<<"timebase succ";
                            sendScheduleToTsc(m_ListCTNodeId[m_ucSendCTPlanIndex].toInt());
                        }
                    }
                    emit receivedTimeBaseResponse(para1,len);
                    break;
                }
            case TSC_TABLE_SCHEDULE:
                {rcvResponseInfo(tr("时段表"),para1);
//                    if(m_bFlagSendCTPlan)
//                    {
//                        quint8 p2 = *(para1+1);
//                        if(*para1==1&&p2==0)
//                        {qDebug()<<m_ListCTNodeName[m_ucSendCTPlanIndex]<<"schedule succ";
//                            m_ucSendCTPlanIndex++;
//                            if(m_ucSendCTPlanIndex<m_ListCTNodeId.count())
//                            {
//                                sendTimeBaseToTsc(m_ListCTNodeId[m_ucSendCTPlanIndex].toInt());
//                            }
//                            else
//                            {
//                                m_bFlagSendCTPlan = false;
//                            }
//                        }
//                    }
                    if(*para1==1&&*(para1+1)==0)
                    {
                        analyseScheduleTable();
                    }
                    else
                    {
                        requireTscTable(TSC_TABLE_SCHEDULE);
                    }

                    emit receivedScheduleResponse(para1,len);
                    break;
                }
            case TSC_TABLE_TIMEPATTERN:
                {rcvResponseInfo(tr("方案表"),para1);
                    if(!m_bFlagClusterSend)
                    {
                        setListTimePatternName();
                       // sendStageTimeToLib();//成功写方案表后 再发送 配时表
                     //   emit receivedTimePatternResponse(para1,len);
                    }
                    else
                    {
                        qDebug()<<"ct pattern response"<<len;
//                        dealClusterPatternResponse((unsigned char*)para1,len);
                    }
                    break;
                }
            case TSC_TABLE_STAGETIME://阶段配时表
                {
                    rcvResponseInfo(tr("阶段配时表"),para1);
                    emit receivedStageTimeResponse(para1,len);
                    break;
                }
            case TSC_TABLE_PHASECONFLICT:
                {
                    rcvResponseInfo(tr("冲突相位表"),para1);
                    if(*(para1+1)!=0)
                    {
                        requireTscTable(TSC_TABLE_PHASECONFLICT);
                    }
                    break;
                }
            case TSC_TABLE_PHASE://相位表
                {
                    rcvResponseInfo(tr("普通相位表"),para1);
                    if(*(para1+1)==0&&!m_bFlagReadIni)
                    {
                        sendOverlapToLib();
                    }
                    break;
                }
            case TSC_TABLE_OVERLAP:
                {
                    rcvResponseInfo(tr("跟随相位表"),para1);
                    if(*(para1+1)==0&&!m_bFlagReadIni)
                    {
                        sendChannelToLib();
                    }
                    break;
                }
            case TSC_TABLE_CHANNEL:
                {
                    rcvResponseInfo(tr("通道表"),para1);
                    if(*(para1+1)==0&&!m_bFlagReadIni)
                    {
                        sendPhaseMapToLib();
                    }
                    break;
                }
            case TBL_TABLE_PHASE2DIREC:
                {
                    rcvResponseInfo(tr("相位映射表"),para1);

                    if(m_bFlagDetSend)
                    {
//                        m_bFlagDetSend = false;
                        sendDetectorToLib();

//                        requireTscTable(TBL_TABLE_PHASE2DIREC);
                    }
                    else if(*(para1+1)==0&&!m_bFlagReadIni)
                    {
                        requireTscTable(TSC_TABLE_PHASE);
                    }
                    break;
                }
            case TSC_TABLE_DETECTOR:
                {
                    rcvResponseInfo(tr("检测器表"),para1);
//                    if(*(para1+1)==0)
//                    {
//                        //sendOverlapToLib();
//                    }
                    if(m_bFlagDetSend)
                    {
                        requireTscTable(TBL_TABLE_PHASE2DIREC);
                    }
                    else if(!m_bFlagReadIni)
                    {
                        requireTscTable(TSC_TABLE_DETECTOR);
                    }
                    break;
                }
            default:
                break;
            }
            break;
        }
    case CS_CMDTYPE_TSC_AUTOREPORT_TAILOR_RESPONSE:
        {
            switch(cmd)
            {
            case TSC_COMMAND_REPORTSELF://订制主动上报时的返回值
                {
                    rcvResponseInfo(tr("try订制主动上报"),para1);
                    break;
                }
            default:
                break;
            }
        }
    case CS_CMDTYPE_TSC_AUTOREPORT://主动上报具体值
        {
            switch(cmd)
            {
            case 0xf8://订制值信号控制状态
                if(!m_bFlagVipStateCheck)
                {
                    rcvResponseInfo(QObject::tr("状态主动上报"),para1);
                    //qDebug()<<"rev auto report"<<len;
                    quint32 rcvId = qFromBigEndian<quint32>(nodeId);
                    emit rcvAutoReport((unsigned char*)para1,len,rcvId);
                }
                else//vip节点状态
                {
                    rcvVipNodeState((unsigned char*)para1,len,m_iCurVipNodeId);
                }
                break;
            case TSC_STATUS_DETECTORSTS:
                rcvResponseInfo(QObject::tr("检测器主动上报"),para1);
                qDebug()<<"rev auto report detector status"<<len;
                emit rcvDetAutoReport((unsigned char*)para1,len);
                break;
            case TSC_STATUS_DETECTORWARN_TABLE:
                rcvResponseInfo(QObject::tr("主动上报"),para1);
                qDebug()<<"rev auto report detector alaram"<<len;
                dealTscDetAlarmTalbe((unsigned char*)para1,len);
                break;
            default:
                break;
            }
        }
    case CS_CMDTYPE_TSC_CONTROL_COMMAND_RESPONSE:
        {
            switch(cmd)
            {
            case TSC_COMMAND_SWITCH_CONTROL:
                rcvResponseInfo(QObject::tr("手动控制"),para1);
                if(*(++para1)==0)
                {
                    emit rcvManualCtrl(true);
                }
                else
                {
                    emit rcvManualCtrl(false);
                }
                break;
            case TSC_COMMAND_SWITCH_SYSTEMCONTROL:
                rcvResponseInfo(QObject::tr("自主控制"),para1);
                break;
            case TSC_COMMAND_UTC_TIME:
                statusBarMessage(tr("校时成功"));
//                requireTscTime();
                break;

            default:
                break;
            }
            break;
        }
    case CS_CMDTYPE_CLUSTER_RESPONSE:// (0x39)群操作返回值
        {
            switch(cmd)
            {
            case CLUSTER_DELETE:
                rcvResponseInfo(QObject::tr("删除群"),para1);
                if(*(++para1)==0)
                {
                    requireClusterInfoTable();
                }
                break;
            default:
                break;
            }
            break;
        }

    default:
        break;
    }
    m_cRcvData.clear();
    if(bTemp)
    {
        dealMessage(temp);
    }
}

void PDataProcess::on_connect(bool b)
{
    QString str;

    if(b)
    {
        str.append(tr("服务端地址:"));
        str.append(m_strAddress);
        str.append(tr("端口:"));
        str.append(m_strPort);
        str.append(tr("连接成功  "));
    }
    else
    {
        str.append(tr("请检查服务端及网络，并重启客户端。连接失败"));
    }
    emit statusBarMessage(str,LBFOURTH);
}

void PDataProcess::on_rcvTscIpInfo(QString str)
{
    QStringList list;
    list = str.split(",");
    int cnt = list.count();
    if(cnt>=3)
    {
        int oldCnt = m_pModelTscIp->rowCount();
        m_pModelTscIp->insertRow(oldCnt);
        m_pModelTscIp->setData(m_pModelTscIp->index(oldCnt,0),list[0]);
        m_pModelTscIp->setData(m_pModelTscIp->index(oldCnt,1),list[1]);
        m_pModelTscIp->setData(m_pModelTscIp->index(oldCnt,2),list[2]);
    }
}

void PDataProcess::on_treeviewDataChange(QStandardItem*item)//add item
{
    if(m_bFlagVipInit)
    {qDebug()<<"treeviewdatachange";
        QStandardItem *pItem = item->parent();
        if(pItem!=0)
        {

            QString pStr = pItem->text();
            QString itemStr = item->text();
            int cnt = pStr.count();
            quint8 vipId = 0;
            if(pStr.left(3).compare(tr("Vip"))==0)//vip
            {
                if(cnt==4)
                {
                    vipId = pStr.right(1).toInt();
                }
                else if(cnt==5)
                {
                    vipId = pStr.right(2).toInt();
                }
                if(vipId>0&&vipId<MAX_VIP_NUM+1)
                {
                    VipProperty_Table *p = m_pVipInfo->tbVipProperty+vipId-1;
                    int indexName = m_TscNameList.indexOf(itemStr);
                    quint32 vipNodeId = 0;
                    if(indexName!=-1)
                    {
                        vipNodeId = m_TscIdList.at(indexName).toInt();
                        //qDebug()<<"vip node id"<<vipNodeId;
                    }
                    for(int j=0;j<MAX_VIP_NODE_COUNT;j++)
                    {
                        quint16 id = qFromBigEndian<quint16>(p->usNodeIdList[j]);
                        //qDebug()<<"p->usNodeIdList[j]"<<id;
                        if(id==vipNodeId)
                        {
                            qDebug()<<"alread has";
                            m_bFlagVipInit = false;
                            setModelItem();
                            return;
                        }
                    }
                    if(m_bFlagShowVip&&m_ucCurVipId==vipId)
                    {
                        emit vipItemChange(vipNodeId,true);//add item
                    }


                    memset(p->usNodeIdList,0,MAX_VIP_NODE_COUNT*sizeof(unsigned short));
                    memset(p->sStageIdList,0,MAX_VIP_NODE_COUNT*sizeof(byte));
                    memset(p->usTimeDifList,0,MAX_VIP_NODE_COUNT*sizeof(unsigned short));
                    int count = pItem->rowCount();
                    for(int i=0;i<count;i++)
                    {
                        QModelIndex index = m_TscNameIconModel->index(i,0,pItem->index());
                        QString str = m_TscNameIconModel->data(index).toString();
                        qDebug()<<"pStr:"<<pStr<<str;
                        int nodeIndex = m_TscNameList.indexOf(str);
                        if(nodeIndex!=-1)
                        {
                            quint16 nodeId = qToBigEndian<quint16>((quint16)m_TscIdList[nodeIndex].toInt());
                            p->usNodeIdList[i] = nodeId;
                            p->sStageIdList[i] = 1;//默认阶段1；
                        }
                    }
                    return;
                }
            }
            else//群或者域
            {
                int index = m_ListCTName.indexOf(pStr);
                if(index!=-1)
                {
                    quint8 ctId = m_ListCTId[index].toInt();
                    int indexNode = m_TscNameList.indexOf(itemStr);
                    if(indexNode!=-1)
                    {
                        quint32 nodeId = m_TscIdList[indexNode].toInt();
                        //更改群属性里的节点
                        changeCtNode(ctId,nodeId);

                        m_TscClusterIdList[indexNode] = ctId;
                        STscNode node;
                        node.uiId = m_TscIdList[indexNode].toInt();
                        memcpy(node.sDeviceIp,m_TscIpList[indexNode].toAscii(),m_TscIpList[indexNode].toAscii().count());
                        memcpy(node.sDeviceName,m_TscNameList[indexNode].toLocal8Bit(),m_TscNameList[indexNode].toLocal8Bit().count());
                        memcpy(node.sVersion,m_TscVersionList[indexNode].toAscii(),m_TscVersionList[indexNode].toAscii().count());
                        node.ucClusterId = ctId;
                        node.ucClusterNodeIndex = m_TscCtNodeIndex[indexNode];
                        node.ucLinkType = m_TscLinkTypeList[indexNode];
                        node.ucProtocolType = m_TscProtocolList[indexNode];
                        node.uiPort = m_TscPortList[indexNode];

                        m_bFlagCtNode = true;
                        //m_bFlagTscNameList = true;
                        setModelItem();
                        m_bFlagUpDateCTNode = true;
                        sendNodeCommand(NODE_UPDATE,&node);
                        //返回正确值 后再发送 群属性表
                        return;
                    }
                }
            }
        }
        requireTscInfoTable();
    }
//    QStandardItem *pItem = m_TscNameIconModel->invisibleRootItem();
//    int cnt = pItem->rowCount();
//    qDebug()<<"treeViewDataChange"<<item->text()<<cnt<<" parent row"<<pItem->row()<<item->row()<<item->column();
//    QStandardItem *p = item->parent();
//    if(p!=0)
//    qDebug()<<"item parent"<<item->parent()->text()<<m_TscNameIconModel->indexFromItem(p).row()<<p->rowCount()<<p->row();

}

void PDataProcess::on_treeViewClick(QModelIndex index)
{
    //qDebug()<<"treeview click"<<QApplication::mouseButtons();
    if(m_iTabWidgetIndex==1)
    {
        emit clickTreeView(index);
    }
    else
    {
        QModelIndex pIndex = index.parent();
        QString str = m_TscNameIconModel->data(index).toString();
        emit clickTreeView(index);
        if(m_bFlagShowTimeBase || m_bFlagShowSchedule)
        {


            //QString strStatus;
            qDebug()<<"treeview click:"<<str;
            if(pIndex==QModelIndex()&&m_ListCTName.indexOf(str)>0)
            {
                m_bFlagCluster = true;
                m_ucCurClusterId = m_ListCTId[m_ListCTName.indexOf(str)].toInt();
                int ctIdIndex = m_ListCTName.indexOf(str);
                if(ctIdIndex>0)//非默认群
                {
                    //strStatus.append(tr("当前群:%1").arg(str));
                    m_ucCurClusterId = m_ListCTId[ctIdIndex].toInt();
                    if(m_mapCluster.contains(m_ucCurClusterId))
                    {
                        m_pClusterInfo = m_mapCluster[m_ucCurClusterId];
                        analyseTimeBaseTable(m_pClusterInfo->tbCTTimeBase);
                        analyseScheduleTable(m_pClusterInfo->tbCTSchedule);
                        analyseClusterPatternTable();
                    }

    //                requireDataBaseTable(CLUSTER_TIMEBASE,m_ucCurClusterId);//timebase cluster

                    emit clusterClick(true);
                }
            }
            else if(m_TscNameList.indexOf(str)!=-1)
            {

                int tscIdIndex = m_TscNameList.indexOf(str);
                if(tscIdIndex!=-1)
                {
                   // strStatus.append(tr("当前节点:%1").arg(str));
                    m_uiCurNodeId = m_TscIdList[tscIdIndex].toInt();
                }
                m_bFlagCluster = false;
                emit clusterClick(false);
                //requireTscTable(TSC_TABLE_TIMEBASE);
            }
    //        strStatus.append(tr(" 当前页面:%1").arg(m_strPage));
    //        emit statusBarMessage(strStatus,false);
        }

        if(str.left(3).compare(tr("Vip"))==0)
        {
            qDebug()<<"on_treeViewClick"<<str;
            emit clickVipId(str);
        }
    }

}

void PDataProcess::on_treeViewRightClick(QModelIndex index)
{
    if(QApplication::mouseButtons().testFlag(Qt::LeftButton))
    {
        qDebug()<<"leftbutton";
    }
    else if(QApplication::mouseButtons().testFlag(Qt::RightButton))
    {
        qDebug()<<"right button"<<index.row()<<index.column();
        QModelIndex pIndex = index.parent();

        if(pIndex.isValid())
        {
            QString nodeStr = m_TscNameIconModel->data(index).toString();//removeat 之前
            int indexName = m_TscNameList.indexOf(nodeStr);
            quint32 nodeId = 0;
            if(indexName!=-1)
            {
                nodeId = m_TscIdList[indexName].toInt();
            }
            QString str = m_TscNameIconModel->data(index.parent()).toString();
            int cnt = str.count();
            qDebug()<<"right button str"<<str;
            if(str.left(3).compare(tr("Vip"))==0)
            {qDebug()<<"rightbutton 0";
                int rowIndex = index.row();
                m_TscNameIconModel->removeRow(rowIndex,index.parent());
//                if(rowIndex<m_ListVipNodeId)
//                {
//                    m_ListVipNodeId.removeAt(rowIndex);
//                    m_ListVipNodeStage.removeAt(rowIndex);
//                    m_ListVipNodeTime.removeAt(rowIndex);
//                }
                quint8 vipId = 0;
                if(cnt==4)
                {
                     vipId = str.right(1).toInt();
                }
                else if(cnt==5)
                {
                    vipId = str.right(2).toInt();
                }
                qDebug()<<"rightbutton 2"<<vipId;
                if(vipId>0&&vipId<MAX_VIP_NUM+1)
                {
                    if(m_bFlagShowVip)
                    {
                        if(indexName!=-1&&m_ucCurVipId==vipId)
                        {qDebug()<<"rightbutton 1";
                            quint32 id = m_TscIdList.at(indexName).toInt();
                            emit vipItemChange(id,false);//del item
                        }
                    }
                    QStandardItem *pItem = m_TscNameIconModel->itemFromIndex(pIndex);
                    VipProperty_Table *p = m_pVipInfo->tbVipProperty+vipId-1;
                    memset(p->usNodeIdList,0,MAX_VIP_NODE_COUNT*sizeof(unsigned short));
                    memset(p->sStageIdList,0,MAX_VIP_NODE_COUNT*sizeof(byte));
                    memset(p->usTimeDifList,0,MAX_VIP_NODE_COUNT*sizeof(unsigned short));
                    int count = pItem->rowCount();
                    for(int i=0;i<count;i++)
                    {
                        QModelIndex nIndex = m_TscNameIconModel->index(i,0,pIndex);
                        QString str = m_TscNameIconModel->data(nIndex).toString();
                        //qDebug()<<"pStr:"<<pStr<<str;
                        int nodeIndex = m_TscNameList.indexOf(str);
                        if(nodeIndex!=-1)
                        {
                            quint16 nodeId = qToBigEndian<quint16>((quint16)m_TscIdList[nodeIndex].toInt());
                            p->usNodeIdList[i] = nodeId;
                            p->sStageIdList[i] = 1;
                        }
                    }
                    sendVipInfoToLib();

                }
            }
            int parIndex = m_ListCTName.indexOf(str);
            if(parIndex>0)//（非默认群）群里的群节点
            {
                quint8 ctId = m_ListCTId[parIndex].toInt();
                changeCtNode(1,nodeId);//归到默认群
                m_TscClusterIdList[indexName] = 1;//节点归到默认群里
                STscNode node;
                node.uiId = m_TscIdList[indexName].toInt();
                memcpy(node.sDeviceIp,m_TscIpList[indexName].toAscii(),m_TscIpList[indexName].toAscii().count());
                memcpy(node.sDeviceName,m_TscNameList[indexName].toLocal8Bit(),m_TscNameList[indexName].toLocal8Bit().count());
                memcpy(node.sVersion,m_TscVersionList[indexName].toAscii(),m_TscVersionList[indexName].toAscii().count());
                node.ucClusterId = 1;
                node.ucClusterNodeIndex = m_TscCtNodeIndex[indexName];
                node.ucLinkType = m_TscLinkTypeList[indexName];
                node.ucProtocolType = m_TscProtocolList[indexName];
                node.uiPort = m_TscPortList[indexName];

                m_bFlagCtNode = true;
                //m_bFlagTscNameList = true;
                setModelItem();
                m_bFlagUpDateCTNode = true;
                sendNodeCommand(NODE_UPDATE,&node);
            }
        }

    }
}

void PDataProcess::on_schEventChange()
{
    if(!m_bEventInit)
    {
        return;
    }
    qDebug()<<"on_schEventChange getDataFromScheduleModel";
    Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM];

    if(m_bFlagCluster)
    {
        tbSch = m_pClusterInfo->tbCTSchedule;
    }
    else
    {
        tbSch = m_pTscInfo->tbSchedule;
    }
    getDataFromScheduleModel(tbSch);
}

void PDataProcess::on_setFlagShowInterfase(int index)
{
    m_bFlagNodeNameFocus = false;
    shutdownAutoReport();
    m_bFlagShowTimeBase = false;
    m_bFlagShowSchedule = false;
    m_bFlagShowCluster = false;
    m_bFlagShowStatus = false;
    m_bFlagShowDetector = false;
    m_bFlagShowVip = false;
    m_bFlagShowEventLog = false;
//    QString name;
//    int indexId = m_TscIdList.indexOf(QString::number(m_uiCurNodeId));
//    //qDebug()<<"toolbutton click";
//    if(indexId!=-1)
//    {
//        name = tr("%1").arg(m_TscNameList[indexId]);
//    }
    QString strStatus;
//    strStatus.append(tr("当前节点:"));
//    strStatus.append(name);
    strStatus.append(tr(" 当前页面:"));
    QString page;
    switch(index)
    {
    case 0:
        page = tr("用户管理");
        break;
    case 1:
        page = tr("节点信息");
        break;
    case 2:
        page = tr("相位灯组");
        break;
    case 3:
        page = tr("阶段配时");
        emit rcvStageTimeTable();
        break;
    case 4:
        page = tr("检测器");
        m_bFlagShowDetector = true;
        if(m_pTscInfo!=NULL)
        {
            analyseDetectorTable();
        }
        break;
    case 5:
        page = tr("状态及控制");
        m_bFlagShowStatus = true;
        if(m_pTscInfo!=NULL)
        {
            emit changeNodeId();
        }
        break;
    case 6:
        page = tr("时基表");
        m_bFlagShowTimeBase = true;
        break;
    case 7:
        page = tr("群设置");
        m_bFlagShowCluster = true;
        break;
    case 8:
        page = tr("VIP设置及查看");
        m_bFlagShowVip = true;
        break;
    case 9:
        page = tr("事件日志");
        emit eventlogShow();
//        requireTscEvent();
        m_bFlagShowEventLog = true;
        break;
    case 10:
        page = tr("系统参数");

        break;
    case 11:
        page = tr("冲突相位");
        break;
    case 12:
        page = tr("时段表");
        m_bFlagShowSchedule = true;
        break;
    default:
        break;
    }
    strStatus.append(page);
    emit statusBarMessage(strStatus,LBSECOND);
    m_strPage.clear();
    m_strPage.append(page);
}

void PDataProcess::on_tabWidgetIndexChange(int index)
{
    m_iTabWidgetIndex = index;
//    emit tabWidgetChange(index);
    QString title;

    switch(index)
    {
    case 0:
        break;
    case 1:
        m_bFlagTscNameList = true;
        title = tr("节点列表");
        break;
    case 2:
        m_bFlagCTInit = false;
        title = tr("群列表");
        break;
    case 3:
        m_bFlagVipInit = false;
        title = tr("VIP列表");
        break;
    default:
        break;
    }
    m_TscNameIconModel->setHeaderData(0,Qt::Horizontal,title);
   setModelItem();
}

bool PDataProcess::appendTscData(int ID, TscProperty *pProperty)
{
    if(!m_TscMap.contains(ID))
        return false;

    m_TscMap.insert(ID, pProperty);
    return true;
}

bool PDataProcess::appendClusterData(int ID, ClusterProperty *pProperty)
{
    if(!m_ClusterMap.contains(ID))
        return false;

    m_ClusterMap.insert(ID, pProperty);
    return true;
}

bool PDataProcess::appendDomainData(int ID, DomainProperty *pProperty)
{
    if(!m_DomainMap.contains(ID))
        return false;

    m_DomainMap.insert(ID, pProperty);
    return true;
}

bool PDataProcess::appendVipData(int ID, VipProperty *pProperty)
{
    if(!m_VipMap.contains(ID))
        return false;

    m_VipMap.insert(ID, pProperty);
    return true;
}

bool PDataProcess::appendSystemData(int ID, SysProperty *pProperty)
{
    if(!m_SysMap.contains(ID))
        return false;

    m_SysMap.insert(ID, pProperty);
    return true;
}


TscProperty *PDataProcess::getTstData(int ID)
{
    if(!m_TscMap.contains(ID))
        return NULL;

    return m_TscMap[ID];
}

ClusterProperty *PDataProcess::getClusterData(int ID)
{
    if(!m_ClusterMap.contains(ID))
        return NULL;

    return m_ClusterMap[ID];
}

DomainProperty *PDataProcess::getDomainData(int ID)
{
    if(!m_DomainMap.contains(ID))
        return NULL;

    return m_DomainMap[ID];
}

VipProperty *PDataProcess::getVipData(int ID)
{
    if(!m_VipMap.contains(ID))
        return NULL;

    return m_VipMap[ID];
}

SysProperty *PDataProcess::getSystemData(int ID)
{
    if(!m_SysMap.contains(ID))
        return NULL;

    return m_SysMap[ID];
}

bool PDataProcess::deleteTscData(int ID)
{
    if(!m_TscMap.contains(ID))
        return false;

    m_TscMap.remove(ID);
    return true;
}


bool PDataProcess::deleteClusterData(int ID)
{
    if(!m_ClusterMap.contains(ID))
        return false;

    m_ClusterMap.remove(ID);
    return true;
}


bool PDataProcess::deleteDomainData(int ID)
{
    if(!m_DomainMap.contains(ID))
        return false;

    m_DomainMap.remove(ID);
    return true;
}


bool PDataProcess::deleteVipData(int ID)
{
    if(!m_VipMap.contains(ID))
        return false;
    m_VipMap.remove(ID);

    m_VipMap.remove(ID);
    return true;
}


bool PDataProcess::deleteSystemData(int ID)
{
    if(!m_SysMap.contains(ID))
        return false;

    m_SysMap.remove(ID);
    return true;
}

//--------private------------
void PDataProcess::clearTscInfoList()
{
    m_TscIdList.clear();
    m_TscClusterIdList.clear();
    m_TscCtNodeIndex.clear();
    m_TscNameList.clear();
    m_TscIpList.clear();
    m_TscPortList.clear();
    m_TscVersionList.clear();
    m_TscLinkTypeList.clear();
    m_TscProtocolList.clear();

//    m_ListTimeBaseName.clear();
//    m_ListScheduleName.clear();
}


void PDataProcess::readCmd(QByteArray cmdArr)
{
    emit readCmdArr(cmdArr);
}


