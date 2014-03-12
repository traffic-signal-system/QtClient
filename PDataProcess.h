//author: sun
//date:2011.09.29

#ifndef PDATAPROCESS_H
#define PDATAPROCESS_H

#include <QObject>
#include <QMap>
#include "DTable.h"
#include "CommClass.h"
#include <QList>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QStringList>
#include <QTimer>
#include <QModelIndex>
#include <QModelIndexList>
#include <QMap>
#include <QSettings>


//class WMainWindow;
class CClientService;

//enum NodeType
//{
//    TSC,
//    CLUSTER,
//    DOMAIN,
//    VIP,
//    SYSTEM
//};


/*
 数据交互 界面中转站
*/
class PDataProcess : public QObject
{
    Q_OBJECT
public:
    explicit PDataProcess(/*WMainWindow *mainwin, */CClientService *cltsvc, QObject *parent = 0);
    ~PDataProcess();

    void htonlHead(int,int,int);
    bool sendMessage(const QByteArray &byteArr);
    bool sendMessage(int type,int num,int size,QByteArray &byteArr);

    bool requireTscInfoTable();//读服务端数节点表
    void dealTscInfoTable(char *para1,int len);//处理 服务端节点表
    bool sendTscInfoTable();

    void requireAllTscTable();//所有新节点 的数据表，m_mapTsc,m_mapVip;
    void requinreAllClusterTable();//读取群信息

    void initMapTable();//完成所有节点后，初始化 映射表
    void deleteMapData();

    quint8 getCtNodeIndexByNodeId(quint32 id,quint8 newCtid);
    STscInfo *getTscInfoByIndex(quint32 index);
    STscInfo *getTscInfoByName(QString name);
    quint32 getNewNodeId();//获得节点Id
    quint32 getCurrentNodeId();//获得当前节点Id;
    void setCurrentNodeId(quint32 nodeId);//

    bool validTscName(QString strName,int index);//节点名有效返回真
    bool validTscIp(QString strIp,int index);
    bool numCheck(QString str,bool b=true);//字符检测 数字，b true 有小数点; 返回 true 有效 false 无效
    bool sendNodeCommand(int cmd,STscNode*);
    void dealNodeCommandAdd(char* para1,int len);
    void dealNodeCommandEdit(char* para1,int len);
    void dealNodeCommandDel(char* para1,int len);
    void addNode(STscNode* tscNode);//往各个List添加数据
    void editNode(STscNode* tscNode,int listIndex);//修改各个List对应数据
    void delNode(int listIndex);//删除各个List对应数据
    bool addNode();

    bool requireTscTable(qint32 tableName,unsigned int tscId=0);//读tsc信号机表
    bool requireTscEvent(int index=-1);
    bool requireTscSysPara();//本想用于读取系统参数

    bool requireClusterInfoTable();
    bool requireDataBaseTable(quint32 tableName,quint32 id);//读服务端数据库表

    //模块表
    void dealTscModuleTable(unsigned char *para1,int len);
    void analyseModuleTable();
    void checkZero(unsigned char *p,int &cnt);
    bool sendModuleToLib();
    bool getDataFromTableModule(STscInfo*pTsc,QByteArray &arr,bool bType=true);
    //-------时基--------
    void dealTscTimeBaseTable(char *para1,int len);//处理 时基表
    void analyseTimeBaseTable(TimeBase_Table *timebase=NULL);
    void addTimebaseIndex(TimeBase_Table *p,quint8 base,quint8 cnt);
    void setTimeBaseModel(TimeBase_Table*timebase=NULL,quint8 base=0,quint8 cnt=20,quint8 id=0);
    bool sendTimeBaseToLib(bool bCluster=false);
    bool getDataFromTableTimeBase(STscInfo*pTsc,QByteArray &arr,bool bType=true);//bType true 发送到 服务端的，false 写入ini的
    bool timebaseValid(TimeBase_Table* p);
//    bool sendTimeBaseToLib(byte index=0,bool bAdd=false,bool bEdit=false,bool bDel=false,TimeBase_Table* tbTimeBase=NULL);//发送时基表到服务端数据库
    bool sendTimeBaseToTsc(quint32 id);//将群时基下发单个节点
//    void updateLocalTimeBase(byte index,bool bAdd,bool bEdit,bool bDel,TimeBase_Table* tbTimeBase = NULL);//发送到服务端返回正确值后 更新本地存储时基表
    quint8 getTimeBaseIndex(bool,bool);//获得时基表的存储位置
//    void setListTimeBaseNameIndex(quint8 index);//list的位置
//    void setFlagCluster(bool&b);


    //时段表
    void dealTscScheduleTable(char *para1,int len);//处理 时段表
    void analyseScheduleTable(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    bool sendScheduleToLib(bool bCluster=false);
    bool getDataFromTableSchedule(STscInfo*pTsc,QByteArray &arr,bool bType=true);
//    bool sendScheduleToLib(byte ,bool,bool,bool/*,Schedule_Table*tbSchedule=NULL*/);
    bool sendScheduleToTsc(quint32 id);//群时段下发单个节点
//    void updateLocalSchedule(byte,bool,bool,bool/*,Schedule_Table*tbSchedule=NULL*/);
    quint8 getScheduleIndex(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);//获得时段表的存储位置
    void addScheduleNameList(quint8 schId,Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    void delScheduleNameList(QModelIndex index,Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    //quint8 getScheduleListIndex(QString str);
//    void addScheduleNo(quint8 index);//用于时基表界面 combo 显示 新添加的时段
    void createScheduleModel();
    void getDataFromScheduleModel(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    void setEventModelByIndex(byte index,Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL/*,bool b=false*/);//index 为存储位置 b=true时显示更多 辅助输出特殊输出
    void setListScheduleName(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]);
//    void setListScheduleNameIndex(quint8 index);
//配时方案表
    void dealTscTimePatternTable(char*para1,int len);
    void analyseTimePatternTable();
    bool checkPatternData(TimePattern_Table*p);
    bool sendTimePatternToLib();
    bool getDataFromTablePattern(STscInfo *pTsc, QByteArray &arr, bool bType=true);
//    void updateLocalTimePattern(quint8 index,bool bAdd,bool bEdit,bool bDel,TimePattern_Table*tbTimePattern=NULL);
//    quint8 getTimePatternIndex();//获得方案表的存储位置 新添加
    void setListTimePatternName();//从存储位置 获得 方案名 方案+No
//阶段配时表
    void dealTscStageTime(char*para1,int len);
    void analyseStageTimeTable();
    bool sendStageTimeToLib();
    bool getDataFromTableStage(STscInfo *pTsc, QByteArray &arr, bool bType=true);
//    void updateLocalStageTime(byte, bool, bool, bool);
//    quint8 getStageTimeIndex();
    void setListStageTimeName();
//    void setStageTime(StageTime_Table*p);//配时阶段 数组指针
    //冲突相位表
    void dealTscPhaseConflictTable(unsigned char*para1,int len);
    bool sendPhaseConflictTable();
    bool getDataFromTableConflict(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
//相位表
    void dealTscPhaseTable(char*para1,int len);
    bool sendPhaseTableToLib();
    bool getDataFromTablePhase(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
 //跟随相位表
    void dealTscOverlapTable(char*para1,int len);
    bool sendOverlapToLib();
    bool getDataFromTableOverlap(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    //通道表
    void dealTscChannelTable(char*para1,int len);
    bool sendChannelToLib();
    bool getDataFromTableChannel(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    //相位映射表
    void dealTscPhaseMapTable(char*para1,int len);
    void analysePhaseMapTable(PhaseMap_Table *map=NULL,Channel_Table* channel=NULL);//相位 通道 方向
    bool sendPhaseMapToLib();
    bool getDataFromTablePhaseMap(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    void setListMapData(PhaseMap_Table *map,Channel_Table* channel);//表传输完成后 处理数据
    int getListIconIndex(quint8 dirId);

    void changeNode();//更改节点时 从新分析数据



    //实时界面
    void setBeginCheck(bool&b);
    bool sendCheckTimeToTsc(quint32 time);//校时
    bool requireAutoReport(quint8 type,quint16 time,quint32 nodeId=0);
    void shutdownAutoReport();
    bool requireTscTime();
    bool sendCtrolCmd(quint32 type,quint8 cmd,quint8 para2);

    //检测器界面
    void dealTscDetectorTable(unsigned char*para1,int len);
    void analyseDetectorTable();
    bool sendDetectorToLib();
    bool getDataFromTableDet(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    void dealTscDetAlarmTalbe(unsigned char*para1,int len);

    //日志事件
    void dealTscEventLogTalbe(unsigned char*para1,int len);
    void sendEventLogToLib();
    void clearEventLogModel();

    //群
    void deleteCtId(int index);
    void setCtNameModel(QStringList list);
    void dealClusterInfo(unsigned char*para1,int len);
    void analyseClusterInfo();
    bool sendClusterInfoToLib();
    QString getCtNameById(quint8 id);
    quint8 getCtIdByName(QString str);
    quint8 getNewClusterId();
    quint8 getCurClusterId();
    bool getClusterState();
    bool sendClusterCommand(quint8 cmd,quint8 id);
    void dealClusterTimeBase(unsigned char*para1,int len);
//    void analyseClusterTimeBase(TimeBase_Table *timebase);
    bool sendClusterTimeBase(byte index,bool bAdd, bool bEdit, bool bDel,  TimeBase_Table *tbTimeBase=NULL);

    quint8 GetClusterScheduleId(quint8 ucMonth
                              , quint8 ucDay
                              , quint8 ucWeek
                              , TimeBase_Table sClusterTimebase[MAX_TIMEBASE_NUM]);
    void dealClusterSchedule(unsigned char*para1,int len);

    bool CompareTime(quint8 ucHour1,quint8 ucMin1,quint8 ucHour2,quint8 ucMin2);
    quint8 GetClusterTimePatternId( quint8 ucScheduleId
                                   , Schedule_Table sClusterSchedule[MAX_SCHEDULE_EVENT_NUM]
                                   , quint8* pCtrl
                                   , quint8* pCycle );
    void dealClusterPattern(unsigned char *rcv, int len);
    void analyseClusterPatternTable();
    bool checkCtPatternData(SClusterPattern*);
    bool sendClusterPattern();
    void getClusterCircle();
    void getCTNodeId(quint8 ctId);//由群号 得 所属 节点 id name index
//    void getCTNodePatternInfo(quint8 patternId);//由方案号 得 相位差 阶段配时号
    void getCTNodeOffset(quint8 ctId);
    bool getCTNodeStageList(quint8 nodeId);//由阶段配时号 取得 各个阶段时间
    void changeCtNode(quint8 ctId,quint8 nodeId);//更改群

    bool setClusterInfoList(QStringList nodeIdList,QList<quint8> indexList,QList<qint16> offsetList,QList<quint8>listCoor,quint8 patternId);

//    void sendCtNodeInfoToLib(QString nodeIdStr,quint8 index);//根据id值 发送
//    void dealCtNodeInforResponse(unsigned char* para1,int len);
//    void sendCtNodePatternToTsc(QList<quint8> indexList,QList<qint16> offsetList);//发送index和相位差的人口

//    void dealClusterPattern(unsigned char*rcv,int len);
//    void dealClusterPatternResponse(unsigned char*para1,int len);
    //------发送群计划表----
    void sendClusterPlan();

    //-------vip-------------------------
    bool requireVipInfoTable();
    bool sendVipCmd(quint8 cmd);
    void dealVipInfo(unsigned char*,int);
    void setVipList();
    bool sendVipInfoToLib();
    quint8 getVipId();
    void cbVipIdChange(quint8 id);
    void requireVipData();//读取 各节点 的数据 当前配时号，相位映射，阶段配时表；

    void rcvVipNodeState(unsigned char *para1,int len,quint32 id);

    void rcvResponseInfo(QString tableName,char*para1=NULL);//返回值 显示于状态栏

    void startBroadCast(bool b=true);

    //交通流量统计
    bool requireTrafficStatistics(quint32 nodeId=0,quint32 disTime=5*60,quint32 startTime=0,quint32 endTime=0);
    bool deleteTrafficStatistics(quint32 nodeId=0,quint32 disTime=5*60,quint32 startTime=0,quint32 endTime=0);
    void dealTrafficStatistics(unsigned char* para1,int len);

    //保存读取节点方案
    void btnSaveDataIni(int nodeIdIndex,QList<quint32>& tbList);
    void btnReadDataIni(int nodeIdIndex,QList<quint32>& tbList);
    bool getDataFromTable(quint32 cmd,STscInfo *pTsc,QByteArray &arr,QString &str);
    bool getIniTableName(quint32 cmd,QString &str);
    void setFlagReadIni(bool b);
    bool sendIniDataToServer(quint32 cmd);

    void setTreeSelect(int index);//用于群 vip 触发 tree select
    void setServiceInfo(QString addr,QString port);
    void setModelItem();
    void timerManage(bool);
    void timerEvent(QTimerEvent *);
    void setClientService(CClientService* client);
    void setStatusBarMessage(QString str,quint8 index=0);
    void readCmd(QByteArray);//1116try用于读取cmd.txt命令

//    void rcvTscIpInfo(QString);
//    void getParameterData(Command, CommanType);//依据命令和命令值获取参数数据

//    void packMessage();    //打包消息
//    void valueUpdate(IDs, TscPropertyType, ParameterData);      //更新节点P的数据及界面显示
//    void valueUpdate(IDs, ClusterPropertyType, ParameterData);  //更新群的数据及界面显示
//    void valueUpdate(IDs, DomainPropertyType, ParameterData);   //更新域的数据及界面显示
//    void valueUpdate(IDs, VipPropertyType, ParameterData);      //更新VIP的数据及界面显示
//    void valueUpdate(SystemType, ParameterData);                //更新系统数据及界面显示

    bool appendTscData(int ID, TscProperty *pProperty);
    bool appendClusterData(int ID, ClusterProperty *pProperty);
    bool appendDomainData(int ID, DomainProperty *pProperty);
    bool appendVipData(int ID, VipProperty *pProperty);
    bool appendSystemData(int ID, SysProperty *pProperty);

    bool deleteTscData(int ID);
    bool deleteClusterData(int ID);
    bool deleteDomainData(int ID);
    bool deleteVipData(int ID);
    bool deleteSystemData(int ID);

    TscProperty *getTstData(int ID);
    ClusterProperty *getClusterData(int ID);
    DomainProperty *getDomainData(int ID);
    VipProperty *getVipData(int ID);
    SysProperty *getSystemData(int ID);



signals:
    void statusBarMessage(QString,quint8 index=0);

    void setNodeParaCbTscId(int);

    void nodeChangeIndex(int index);//节点信息 name更改时 tree select；群 vip

    void receivedUserLogin(char*rcv,int len);//rcv从参数1开始到结束
    void receivedUserView(char*rcv,int len);
    void receivedNodeCommand(int,bool);
    void receivedTimeBaseResponse(char*para1,int len);//写服务端时基表返回值
    void receivedScheduleResponse(char*para1,int len);
    void receivedTimePatternResponse(char*para1,int len);
    void receivedStageTimeResponse(char*para1,int len);

    void sendToService(QByteArray byteArr,bool);//1115try
    void recvMessage(QByteArray,bool);

    void clickTreeView(QModelIndex);//treeView click trigger the signal

    void resetNodeNameModel(int);//list改变后发消息 int为list indxe 0 起

    void readCmdArr(QByteArray);//1116try

    void rcvModuleTable();
    void changeSpecialModel();//时基
    void clickTimebaseIndex(QModelIndex index);
    void clickSchIndex(QModelIndex index);

    void updateTimePatternName();
    void rcvStageTimeTable();//用于完成setmodelitem后 让wtimeset 的cbStagePatternId显示当前 配时号

    void rcvConflict();
    void rcvPhase();//在接收完 普通相位表、跟随相位表、通道表、相位映射表后发送信号给界面更新
    void rcvDet();//收到检测器数据
    void rcvDetAlarm();//收到检测器警报数据
    void rcvAutoReport(unsigned char*para1,int len,quint32);
    void changeNodeId();
    void rcvManualCtrl(bool);//手动控制 成功失败
    void rcvTscStatus(unsigned char*para1,int len);//信号机状态值0xf5
    void rcvTscTime(quint32 time);
    void cbFlashStatus(bool);//
    void eventlogShow();//事件日志 界面显示

    //检测器状态值主动上报
    void rcvDetAutoReport(unsigned char*para1,int len);
    void cbDetStatus(bool);//换节点 关闭主动上报

    //时空图 得到方案号，群周期后
    void getCtCircle();
    void getCtNodeStage(quint8 nodeId);
    void rcvCtPattern();//收到群方案后 使界面 显示方案1；
    void ctNameModelChange();//用于 群界面 显示 当前群
    //vip号改变后 所属节点 改变
    void vipNodeListChange();
    void vipNodeState(quint32 id,bool bManual,quint8 stageId,bool bVipShow);
    void clickVipId(QString str);

    //--------vip----------
    void vipIdModelChange();
    //---------treeview------
    void vipItemChange(quint32 id,bool b);//b true add,false del;
    //-----------时基表--点击群和节点时触发------------
    void clusterClick(bool b);
//    void tabWidgetChange(int);
    //-----------------交通流量统计-----------------------
    void trafficMaxMinTime(quint32 max,quint32 min,quint32 maxY);//触发 最大时间 最小时间 最大流量
    void trafficData(QString str,QMap<quint32,quint32> mapData);
    void completeTraffic();


public slots:
    void dealMessage(QByteArray str);
    void on_connect(bool);
    void on_rcvTscIpInfo(QString);
//-----------------treeview-----------
    void on_treeviewDataChange(QStandardItem*);
    void on_treeViewClick(QModelIndex index);
    void on_setFlagShowInterfase(int index);//mainwindow windowstack change
    void on_tabWidgetIndexChange(int);
    void on_treeViewRightClick(QModelIndex);
//    void on_treeViewClick(QModelIndex);
    //void on_timerout();//时间超时时 关闭
    //时段 事件表
    void on_schEventChange();


private :
//    WMainWindow *m_MainWin;
    CClientService *m_ClientServ;
    SUtcsFrameHead *m_pSendMsgHead;
    SUtcsFrameHead *m_pRcvMsgHead;
    int m_iheadSize;

    QMap<int, TscProperty *> m_TscMap;              //节点数据缓存管理映射
    QMap<int, ClusterProperty *> m_ClusterMap;      //群数据缓存管理映射
    QMap<int, DomainProperty *> m_DomainMap;        //域数据缓存管理映射
    QMap<int, VipProperty *> m_VipMap;             //VIP数据缓存管理映射
    QMap<int, SysProperty *> m_SysMap;             //系统数据缓存管理映射

    //1101
//    TscProperty       *m_TscDataBuffer;
//    ClusterProperty   *m_ClusterDataBuffer;
//    DomainProperty    *m_DomainDataBuffer;
//    VipProperty       *m_VipDataBuffer;
//    SysProperty       *m_SystemDataBuffer;

    //---------------------------------
public:
    //节点参数
    STscInfo *m_pTscInfo;
    QMap<quint32,STscInfo*> m_mapTsc;
    QMap<quint32,SVipData*> m_mapVip;
    QMap<quint32,SClusterInfo*> m_mapCluster;
//    int m_iTscCnt;//已经完成的 节点数
    QStringList m_TscIdList;
    QList<quint32> m_ListNewTscId;
    QList<quint8> m_ListNewCtId;
    QList<byte> m_TscClusterIdList;
    QList<quint8> m_TscCtNodeIndex;//群属节点 顺序 1起
    QStringList m_TscNameList;
    QList<QString> m_TscIpList;
    QList<quint16> m_TscPortList;
    QList<QString> m_TscVersionList;
    QList<byte> m_TscLinkTypeList;
    QList<byte> m_TscProtocolList;
    void clearTscInfoList();

    QStandardItemModel *m_TscNameIconModel;
    QStringListModel *m_TscNameModel;
    QStringListModel *m_TscIdModel;
    QStandardItemModel *m_TscClusterIdModel;//用于群列表
    QStandardItemModel *m_TscProcotolModel;
    bool m_bFlagTscNameList;//m_TscNameList是否有更新标志
    bool m_bFlagTscIdList;

    QStringList m_ListModuleName;
//    bool m_bFlagModuleName;
    QStringListModel *m_pModelModuleName;

    //时基表
    QStringList m_ListTimeBaseName;
//    quint8 m_ucListTimeBaseNameIndex;
    QStandardItemModel *m_pModelTimeBaseName;
//    quint8 m_ucBase;//时基表基数
//    quint8 m_ucCount;//时基表数量

    bool m_bFlagTimeBaseName;//m_ListTimeBaseName是否有更新标志
    bool m_bFlagShowTimeBase;//mainwindow click6 界面显示时置true，在读取到时段表后置 false；
    bool m_bFlagShowSchedule;
    bool m_bFlagShowCluster;//群时空图界面
    bool m_bFlagShowStatus;//实时界面
    bool m_bFlagShowDetector;//检测器界面
    bool m_bFlagShowVip;
    bool m_bFlagShowEventLog;

    //时段表
    QStandardItemModel *m_pModelEvent;//时段表里的 事件列表
    QStringList m_ListScheduleName;//时段表名
    QStringListModel *m_pModelScheduleName;
    bool m_bFlagScheduleName;//时段表 号 有变动
    Schedule_Table *m_pSchedule;//用于存放 新增 编辑的 事件
    quint8 m_ucScheduleNo;//方案号 存储位置+1
//    quint8 m_ucListScheduleNameIndex;
    bool m_bEventInit;//时段表号 里的 事件 初始化完成为true

    //方案表
    QStringList m_ListTimePatternName;
//    QStringListModel *m_pModelTimePatternName;
//    bool m_bFlagTimePatternName;

    //阶段配时表
    QStringList m_ListStageTimeName;
//    QStringListModel *m_pModelStageTimeName;
//    bool m_bFlagStageTimeName;
    StageTime_Table *m_pStageTime;//指向wstage的m_pStageTime;
    quint8 m_ucStageTimeNo;

    //相位 跟随相位 通道 相位映射
    //QList<quint8> m_ListChannel;

    QList<quint8> m_ListComMap;//方向1-16对应的 普通相位值 方向对应跟随相位时 值为0
    QList<quint8> m_ListOverlapMap;//方向1-16对应的 跟随相位值 方向对应普通相位时 值为0
    QList<quint8> m_ListChannelMap;//(方向对应的通道)

    QList<quint8> m_ListPhaseMap;//方向1-16(20) 对应的相位值 不区分 普通 跟随 只跟 数字有关 20个方向填满 没有填0；根据 phaseMap id值解析得到 方向值
    QList<quint8> m_ListLoadNum;//方向1-16 各个路标对应的车道数 检测器界面用 20个方向
    QList<quint8> m_ListLoadMap;//1-CHANNELNUM通道 对应的相位值(1-40) index0-23对应通道1-24   实时显示时用到 存储通道1-MAX_CHANNEL_NUM()所对应的相位值
    QList<quint8> m_ListLoadNo;//存储 方向Id，用来决定 路标（只需存储直行路标即可）
    QList<bool> m_ListValid;//存储20个路标的显示与否
    quint8 m_ucDir;//用于显示背景图

    //检测器
    bool m_bFlagDetSend;
    bool m_bFlagDetRead;

    //实时显示界面
    bool m_bBeginCheck;
    bool m_bFlagAutoReport;
    bool m_bFlagDetAutoReport;
    //节点信息
    bool m_bFlagNodeNameFocus;//修改节点名时为true tree不具有焦点。默认false

    //事件日志
    //bool m_bFlagEventLog;
    int m_iEventIndex;
    QStandardItemModel *m_pModelEventLog;
    QStringListModel *m_EventNameModel;
    CheckGroupDeligate* ckNodeNameDeligate;

    //信号机搜索
    QStandardItemModel *m_pModelTscIp;

    quint32 m_uiCurNodeId;//当前显示节点Id 从1起
    quint8 m_ucCurClusterId;
    quint8 m_ucCurVipId;
    bool m_bFlagNodeIdChanged;//节点变更时 为true；在更新 完 表后，置为false 初始值为true;
//    bool m_bFlagInit;//初始值为false ；读取节点表后 开始读所有数据 完成后 为true
    bool m_bFlagOnLine;//开始为true TIMEOUT=5000，超时后置为false TIMEOUT=100;
    int m_iCurTscNameLisIndex;//当前 m_TscNameList的index 从0起

    QString m_strPage;
    //--------------群------------------
    bool m_bFlagUpDateCTNode;//节点树 群节点改变时 为true，发送数据到服务端后置为false
    ClusterProperty_Table *m_pCTProperty;


    SClusterInfo *m_pClusterInfo;
    QStringList m_ListCTId;
    QStringList m_ListCTDomainId;
    QStringList m_ListCTName;
    QStringList m_ListCTEnable;

    QStringListModel *m_pModelCTName;
    bool m_bFlagCTInit;//第一次初始化时 才会再要求 节点信息表
    //-------下发群计划表
    bool m_bFlagAddCT;
    bool m_bFlagSendCTPlan;
    quint8 m_ucSendCTPlanIndex;

    //------------群时空图---------
    quint8 m_ucCTScheduleId;
    quint8 m_ucCTPlanId;//群所需方案号
    quint8 m_ucCTCircle;//群周期
    quint8 m_ucCTStageTime;//配时号
    QStringList m_ListCTNodeId;//一个群里的 节点
    QStringList m_ListCTNodeName;
    QStringListModel *m_pModelCTNodeName;
    QList<quint8> m_ListCTNodeIndex;//
//    QList<quint8> m_ListCTNodeStagePattern;//阶段配时号
    QList<qint16> m_ListCTNodeOffset;//相位差
    QList<quint8> m_ListStageTime;

    quint8 m_ucCTNodeSendIndex;//群向tsc发送方案表里的相位差时  已发送的顺序
    bool m_bFlagCluster;//treeview点击群时 置true 对 timebase界面m_bFlagCluster的引用
    bool m_bFlagClusterSend;
    bool m_bFlagReadCluster;//群时空图 读取时 先读取 节点信息表 里的 index

    //------------------vip--------------
    SVipInfo *m_pVipInfo;
    bool m_bFlagVipInit;//用于更新列表时 不响应点击

    QList<quint8> m_ListVipId;
    QStandardItemModel *m_pModelVipId;
    QList<quint16> m_ListVipNodeId;
    QList<quint8> m_ListVipNodeStage;
    QList<quint16> m_ListVipNodeTime;

    bool m_bFlagVipStateCheck;//检查vip节点的状态
    quint32 m_iCurVipNodeId;//当前的vip节点id
    //QMap<quint32,SVipData*> m_mapVip;
    VipProperty_Table *m_pVip;
    //quint8 m_ucVipNodeIndex;//用于 vip 各节点读取时 已完成 的节点；

    //交通流量统计
    QStandardItemModel *m_pModelTraffic;

    //------tree view-----------
    QModelIndexList m_ListClusterIndex;//群 vip 的 ModelIndex
    QModelIndexList m_ListNodeIndex;
    //------------------
//    QIcon nodeIcon;

//    QIcon ctIcon;

//    QIcon dmtIcon;

//    QIcon vipIcon;
    //-----------------------


    QTimer *timer;//接收超时
    qint32 m_iTimerId;
    quint8 m_ucTableName;
    bool m_bFlagTscTable;//读取tsc表和服务器表 区别标志
    //QIcon m_nodeIcon;
    QByteArray m_cRcvData;
    int m_iComplete;
    int m_iDataLong;
    bool m_bComplete;
    int m_iHeadType;
    int m_iHeadNum;
    int m_iHeadSize;
    //-----------服务端地址 端口；
    QString m_strAddress;
    QString m_strPort;
    bool m_bFlagSingle;//true 单机版;false 网络版
    bool m_bFlagCtNode;//在tree修改群里节点时，sendnodecommand返回值 不处理
    qint32 m_iCmdType;//服务端 tsc

    quint32 m_uiEventLogStart;
    quint32 m_uiEventLogEnd;
    QStringList m_ListEventLogSearch;

    int m_iTabWidgetIndex;

private:
    QSettings *m_setData;
    bool m_bFlagReadIni;

};

#endif // PDATAPROCESS_H
