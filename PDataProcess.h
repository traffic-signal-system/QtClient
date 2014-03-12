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
 ���ݽ��� ������תվ
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

    bool requireTscInfoTable();//����������ڵ��
    void dealTscInfoTable(char *para1,int len);//���� ����˽ڵ��
    bool sendTscInfoTable();

    void requireAllTscTable();//�����½ڵ� �����ݱ�m_mapTsc,m_mapVip;
    void requinreAllClusterTable();//��ȡȺ��Ϣ

    void initMapTable();//������нڵ�󣬳�ʼ�� ӳ���
    void deleteMapData();

    quint8 getCtNodeIndexByNodeId(quint32 id,quint8 newCtid);
    STscInfo *getTscInfoByIndex(quint32 index);
    STscInfo *getTscInfoByName(QString name);
    quint32 getNewNodeId();//��ýڵ�Id
    quint32 getCurrentNodeId();//��õ�ǰ�ڵ�Id;
    void setCurrentNodeId(quint32 nodeId);//

    bool validTscName(QString strName,int index);//�ڵ�����Ч������
    bool validTscIp(QString strIp,int index);
    bool numCheck(QString str,bool b=true);//�ַ���� ���֣�b true ��С����; ���� true ��Ч false ��Ч
    bool sendNodeCommand(int cmd,STscNode*);
    void dealNodeCommandAdd(char* para1,int len);
    void dealNodeCommandEdit(char* para1,int len);
    void dealNodeCommandDel(char* para1,int len);
    void addNode(STscNode* tscNode);//������List�������
    void editNode(STscNode* tscNode,int listIndex);//�޸ĸ���List��Ӧ����
    void delNode(int listIndex);//ɾ������List��Ӧ����
    bool addNode();

    bool requireTscTable(qint32 tableName,unsigned int tscId=0);//��tsc�źŻ���
    bool requireTscEvent(int index=-1);
    bool requireTscSysPara();//�������ڶ�ȡϵͳ����

    bool requireClusterInfoTable();
    bool requireDataBaseTable(quint32 tableName,quint32 id);//����������ݿ��

    //ģ���
    void dealTscModuleTable(unsigned char *para1,int len);
    void analyseModuleTable();
    void checkZero(unsigned char *p,int &cnt);
    bool sendModuleToLib();
    bool getDataFromTableModule(STscInfo*pTsc,QByteArray &arr,bool bType=true);
    //-------ʱ��--------
    void dealTscTimeBaseTable(char *para1,int len);//���� ʱ����
    void analyseTimeBaseTable(TimeBase_Table *timebase=NULL);
    void addTimebaseIndex(TimeBase_Table *p,quint8 base,quint8 cnt);
    void setTimeBaseModel(TimeBase_Table*timebase=NULL,quint8 base=0,quint8 cnt=20,quint8 id=0);
    bool sendTimeBaseToLib(bool bCluster=false);
    bool getDataFromTableTimeBase(STscInfo*pTsc,QByteArray &arr,bool bType=true);//bType true ���͵� ����˵ģ�false д��ini��
    bool timebaseValid(TimeBase_Table* p);
//    bool sendTimeBaseToLib(byte index=0,bool bAdd=false,bool bEdit=false,bool bDel=false,TimeBase_Table* tbTimeBase=NULL);//����ʱ������������ݿ�
    bool sendTimeBaseToTsc(quint32 id);//��Ⱥʱ���·������ڵ�
//    void updateLocalTimeBase(byte index,bool bAdd,bool bEdit,bool bDel,TimeBase_Table* tbTimeBase = NULL);//���͵�����˷�����ȷֵ�� ���±��ش洢ʱ����
    quint8 getTimeBaseIndex(bool,bool);//���ʱ����Ĵ洢λ��
//    void setListTimeBaseNameIndex(quint8 index);//list��λ��
//    void setFlagCluster(bool&b);


    //ʱ�α�
    void dealTscScheduleTable(char *para1,int len);//���� ʱ�α�
    void analyseScheduleTable(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    bool sendScheduleToLib(bool bCluster=false);
    bool getDataFromTableSchedule(STscInfo*pTsc,QByteArray &arr,bool bType=true);
//    bool sendScheduleToLib(byte ,bool,bool,bool/*,Schedule_Table*tbSchedule=NULL*/);
    bool sendScheduleToTsc(quint32 id);//Ⱥʱ���·������ڵ�
//    void updateLocalSchedule(byte,bool,bool,bool/*,Schedule_Table*tbSchedule=NULL*/);
    quint8 getScheduleIndex(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);//���ʱ�α�Ĵ洢λ��
    void addScheduleNameList(quint8 schId,Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    void delScheduleNameList(QModelIndex index,Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    //quint8 getScheduleListIndex(QString str);
//    void addScheduleNo(quint8 index);//����ʱ������� combo ��ʾ ����ӵ�ʱ��
    void createScheduleModel();
    void getDataFromScheduleModel(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL);
    void setEventModelByIndex(byte index,Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]=NULL/*,bool b=false*/);//index Ϊ�洢λ�� b=trueʱ��ʾ���� ��������������
    void setListScheduleName(Schedule_Table (*tbSch)[MAX_SCHEDULE_EVENT_NUM]);
//    void setListScheduleNameIndex(quint8 index);
//��ʱ������
    void dealTscTimePatternTable(char*para1,int len);
    void analyseTimePatternTable();
    bool checkPatternData(TimePattern_Table*p);
    bool sendTimePatternToLib();
    bool getDataFromTablePattern(STscInfo *pTsc, QByteArray &arr, bool bType=true);
//    void updateLocalTimePattern(quint8 index,bool bAdd,bool bEdit,bool bDel,TimePattern_Table*tbTimePattern=NULL);
//    quint8 getTimePatternIndex();//��÷�����Ĵ洢λ�� �����
    void setListTimePatternName();//�Ӵ洢λ�� ��� ������ ����+No
//�׶���ʱ��
    void dealTscStageTime(char*para1,int len);
    void analyseStageTimeTable();
    bool sendStageTimeToLib();
    bool getDataFromTableStage(STscInfo *pTsc, QByteArray &arr, bool bType=true);
//    void updateLocalStageTime(byte, bool, bool, bool);
//    quint8 getStageTimeIndex();
    void setListStageTimeName();
//    void setStageTime(StageTime_Table*p);//��ʱ�׶� ����ָ��
    //��ͻ��λ��
    void dealTscPhaseConflictTable(unsigned char*para1,int len);
    bool sendPhaseConflictTable();
    bool getDataFromTableConflict(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
//��λ��
    void dealTscPhaseTable(char*para1,int len);
    bool sendPhaseTableToLib();
    bool getDataFromTablePhase(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
 //������λ��
    void dealTscOverlapTable(char*para1,int len);
    bool sendOverlapToLib();
    bool getDataFromTableOverlap(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    //ͨ����
    void dealTscChannelTable(char*para1,int len);
    bool sendChannelToLib();
    bool getDataFromTableChannel(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    //��λӳ���
    void dealTscPhaseMapTable(char*para1,int len);
    void analysePhaseMapTable(PhaseMap_Table *map=NULL,Channel_Table* channel=NULL);//��λ ͨ�� ����
    bool sendPhaseMapToLib();
    bool getDataFromTablePhaseMap(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    void setListMapData(PhaseMap_Table *map,Channel_Table* channel);//������ɺ� ��������
    int getListIconIndex(quint8 dirId);

    void changeNode();//���Ľڵ�ʱ ���·�������



    //ʵʱ����
    void setBeginCheck(bool&b);
    bool sendCheckTimeToTsc(quint32 time);//Уʱ
    bool requireAutoReport(quint8 type,quint16 time,quint32 nodeId=0);
    void shutdownAutoReport();
    bool requireTscTime();
    bool sendCtrolCmd(quint32 type,quint8 cmd,quint8 para2);

    //���������
    void dealTscDetectorTable(unsigned char*para1,int len);
    void analyseDetectorTable();
    bool sendDetectorToLib();
    bool getDataFromTableDet(STscInfo *pTsc, QByteArray &sendArr, bool bType=true);
    void dealTscDetAlarmTalbe(unsigned char*para1,int len);

    //��־�¼�
    void dealTscEventLogTalbe(unsigned char*para1,int len);
    void sendEventLogToLib();
    void clearEventLogModel();

    //Ⱥ
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
    void getCTNodeId(quint8 ctId);//��Ⱥ�� �� ���� �ڵ� id name index
//    void getCTNodePatternInfo(quint8 patternId);//�ɷ����� �� ��λ�� �׶���ʱ��
    void getCTNodeOffset(quint8 ctId);
    bool getCTNodeStageList(quint8 nodeId);//�ɽ׶���ʱ�� ȡ�� �����׶�ʱ��
    void changeCtNode(quint8 ctId,quint8 nodeId);//����Ⱥ

    bool setClusterInfoList(QStringList nodeIdList,QList<quint8> indexList,QList<qint16> offsetList,QList<quint8>listCoor,quint8 patternId);

//    void sendCtNodeInfoToLib(QString nodeIdStr,quint8 index);//����idֵ ����
//    void dealCtNodeInforResponse(unsigned char* para1,int len);
//    void sendCtNodePatternToTsc(QList<quint8> indexList,QList<qint16> offsetList);//����index����λ����˿�

//    void dealClusterPattern(unsigned char*rcv,int len);
//    void dealClusterPatternResponse(unsigned char*para1,int len);
    //------����Ⱥ�ƻ���----
    void sendClusterPlan();

    //-------vip-------------------------
    bool requireVipInfoTable();
    bool sendVipCmd(quint8 cmd);
    void dealVipInfo(unsigned char*,int);
    void setVipList();
    bool sendVipInfoToLib();
    quint8 getVipId();
    void cbVipIdChange(quint8 id);
    void requireVipData();//��ȡ ���ڵ� ������ ��ǰ��ʱ�ţ���λӳ�䣬�׶���ʱ��

    void rcvVipNodeState(unsigned char *para1,int len,quint32 id);

    void rcvResponseInfo(QString tableName,char*para1=NULL);//����ֵ ��ʾ��״̬��

    void startBroadCast(bool b=true);

    //��ͨ����ͳ��
    bool requireTrafficStatistics(quint32 nodeId=0,quint32 disTime=5*60,quint32 startTime=0,quint32 endTime=0);
    bool deleteTrafficStatistics(quint32 nodeId=0,quint32 disTime=5*60,quint32 startTime=0,quint32 endTime=0);
    void dealTrafficStatistics(unsigned char* para1,int len);

    //�����ȡ�ڵ㷽��
    void btnSaveDataIni(int nodeIdIndex,QList<quint32>& tbList);
    void btnReadDataIni(int nodeIdIndex,QList<quint32>& tbList);
    bool getDataFromTable(quint32 cmd,STscInfo *pTsc,QByteArray &arr,QString &str);
    bool getIniTableName(quint32 cmd,QString &str);
    void setFlagReadIni(bool b);
    bool sendIniDataToServer(quint32 cmd);

    void setTreeSelect(int index);//����Ⱥ vip ���� tree select
    void setServiceInfo(QString addr,QString port);
    void setModelItem();
    void timerManage(bool);
    void timerEvent(QTimerEvent *);
    void setClientService(CClientService* client);
    void setStatusBarMessage(QString str,quint8 index=0);
    void readCmd(QByteArray);//1116try���ڶ�ȡcmd.txt����

//    void rcvTscIpInfo(QString);
//    void getParameterData(Command, CommanType);//�������������ֵ��ȡ��������

//    void packMessage();    //�����Ϣ
//    void valueUpdate(IDs, TscPropertyType, ParameterData);      //���½ڵ�P�����ݼ�������ʾ
//    void valueUpdate(IDs, ClusterPropertyType, ParameterData);  //����Ⱥ�����ݼ�������ʾ
//    void valueUpdate(IDs, DomainPropertyType, ParameterData);   //����������ݼ�������ʾ
//    void valueUpdate(IDs, VipPropertyType, ParameterData);      //����VIP�����ݼ�������ʾ
//    void valueUpdate(SystemType, ParameterData);                //����ϵͳ���ݼ�������ʾ

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

    void nodeChangeIndex(int index);//�ڵ���Ϣ name����ʱ tree select��Ⱥ vip

    void receivedUserLogin(char*rcv,int len);//rcv�Ӳ���1��ʼ������
    void receivedUserView(char*rcv,int len);
    void receivedNodeCommand(int,bool);
    void receivedTimeBaseResponse(char*para1,int len);//д�����ʱ������ֵ
    void receivedScheduleResponse(char*para1,int len);
    void receivedTimePatternResponse(char*para1,int len);
    void receivedStageTimeResponse(char*para1,int len);

    void sendToService(QByteArray byteArr,bool);//1115try
    void recvMessage(QByteArray,bool);

    void clickTreeView(QModelIndex);//treeView click trigger the signal

    void resetNodeNameModel(int);//list�ı����Ϣ intΪlist indxe 0 ��

    void readCmdArr(QByteArray);//1116try

    void rcvModuleTable();
    void changeSpecialModel();//ʱ��
    void clickTimebaseIndex(QModelIndex index);
    void clickSchIndex(QModelIndex index);

    void updateTimePatternName();
    void rcvStageTimeTable();//�������setmodelitem�� ��wtimeset ��cbStagePatternId��ʾ��ǰ ��ʱ��

    void rcvConflict();
    void rcvPhase();//�ڽ����� ��ͨ��λ��������λ��ͨ������λӳ�������źŸ��������
    void rcvDet();//�յ����������
    void rcvDetAlarm();//�յ��������������
    void rcvAutoReport(unsigned char*para1,int len,quint32);
    void changeNodeId();
    void rcvManualCtrl(bool);//�ֶ����� �ɹ�ʧ��
    void rcvTscStatus(unsigned char*para1,int len);//�źŻ�״ֵ̬0xf5
    void rcvTscTime(quint32 time);
    void cbFlashStatus(bool);//
    void eventlogShow();//�¼���־ ������ʾ

    //�����״ֵ̬�����ϱ�
    void rcvDetAutoReport(unsigned char*para1,int len);
    void cbDetStatus(bool);//���ڵ� �ر������ϱ�

    //ʱ��ͼ �õ������ţ�Ⱥ���ں�
    void getCtCircle();
    void getCtNodeStage(quint8 nodeId);
    void rcvCtPattern();//�յ�Ⱥ������ ʹ���� ��ʾ����1��
    void ctNameModelChange();//���� Ⱥ���� ��ʾ ��ǰȺ
    //vip�Ÿı�� �����ڵ� �ı�
    void vipNodeListChange();
    void vipNodeState(quint32 id,bool bManual,quint8 stageId,bool bVipShow);
    void clickVipId(QString str);

    //--------vip----------
    void vipIdModelChange();
    //---------treeview------
    void vipItemChange(quint32 id,bool b);//b true add,false del;
    //-----------ʱ����--���Ⱥ�ͽڵ�ʱ����------------
    void clusterClick(bool b);
//    void tabWidgetChange(int);
    //-----------------��ͨ����ͳ��-----------------------
    void trafficMaxMinTime(quint32 max,quint32 min,quint32 maxY);//���� ���ʱ�� ��Сʱ�� �������
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
    //void on_timerout();//ʱ�䳬ʱʱ �ر�
    //ʱ�� �¼���
    void on_schEventChange();


private :
//    WMainWindow *m_MainWin;
    CClientService *m_ClientServ;
    SUtcsFrameHead *m_pSendMsgHead;
    SUtcsFrameHead *m_pRcvMsgHead;
    int m_iheadSize;

    QMap<int, TscProperty *> m_TscMap;              //�ڵ����ݻ������ӳ��
    QMap<int, ClusterProperty *> m_ClusterMap;      //Ⱥ���ݻ������ӳ��
    QMap<int, DomainProperty *> m_DomainMap;        //�����ݻ������ӳ��
    QMap<int, VipProperty *> m_VipMap;             //VIP���ݻ������ӳ��
    QMap<int, SysProperty *> m_SysMap;             //ϵͳ���ݻ������ӳ��

    //1101
//    TscProperty       *m_TscDataBuffer;
//    ClusterProperty   *m_ClusterDataBuffer;
//    DomainProperty    *m_DomainDataBuffer;
//    VipProperty       *m_VipDataBuffer;
//    SysProperty       *m_SystemDataBuffer;

    //---------------------------------
public:
    //�ڵ����
    STscInfo *m_pTscInfo;
    QMap<quint32,STscInfo*> m_mapTsc;
    QMap<quint32,SVipData*> m_mapVip;
    QMap<quint32,SClusterInfo*> m_mapCluster;
//    int m_iTscCnt;//�Ѿ���ɵ� �ڵ���
    QStringList m_TscIdList;
    QList<quint32> m_ListNewTscId;
    QList<quint8> m_ListNewCtId;
    QList<byte> m_TscClusterIdList;
    QList<quint8> m_TscCtNodeIndex;//Ⱥ���ڵ� ˳�� 1��
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
    QStandardItemModel *m_TscClusterIdModel;//����Ⱥ�б�
    QStandardItemModel *m_TscProcotolModel;
    bool m_bFlagTscNameList;//m_TscNameList�Ƿ��и��±�־
    bool m_bFlagTscIdList;

    QStringList m_ListModuleName;
//    bool m_bFlagModuleName;
    QStringListModel *m_pModelModuleName;

    //ʱ����
    QStringList m_ListTimeBaseName;
//    quint8 m_ucListTimeBaseNameIndex;
    QStandardItemModel *m_pModelTimeBaseName;
//    quint8 m_ucBase;//ʱ�������
//    quint8 m_ucCount;//ʱ��������

    bool m_bFlagTimeBaseName;//m_ListTimeBaseName�Ƿ��и��±�־
    bool m_bFlagShowTimeBase;//mainwindow click6 ������ʾʱ��true���ڶ�ȡ��ʱ�α���� false��
    bool m_bFlagShowSchedule;
    bool m_bFlagShowCluster;//Ⱥʱ��ͼ����
    bool m_bFlagShowStatus;//ʵʱ����
    bool m_bFlagShowDetector;//���������
    bool m_bFlagShowVip;
    bool m_bFlagShowEventLog;

    //ʱ�α�
    QStandardItemModel *m_pModelEvent;//ʱ�α���� �¼��б�
    QStringList m_ListScheduleName;//ʱ�α���
    QStringListModel *m_pModelScheduleName;
    bool m_bFlagScheduleName;//ʱ�α� �� �б䶯
    Schedule_Table *m_pSchedule;//���ڴ�� ���� �༭�� �¼�
    quint8 m_ucScheduleNo;//������ �洢λ��+1
//    quint8 m_ucListScheduleNameIndex;
    bool m_bEventInit;//ʱ�α�� ��� �¼� ��ʼ�����Ϊtrue

    //������
    QStringList m_ListTimePatternName;
//    QStringListModel *m_pModelTimePatternName;
//    bool m_bFlagTimePatternName;

    //�׶���ʱ��
    QStringList m_ListStageTimeName;
//    QStringListModel *m_pModelStageTimeName;
//    bool m_bFlagStageTimeName;
    StageTime_Table *m_pStageTime;//ָ��wstage��m_pStageTime;
    quint8 m_ucStageTimeNo;

    //��λ ������λ ͨ�� ��λӳ��
    //QList<quint8> m_ListChannel;

    QList<quint8> m_ListComMap;//����1-16��Ӧ�� ��ͨ��λֵ �����Ӧ������λʱ ֵΪ0
    QList<quint8> m_ListOverlapMap;//����1-16��Ӧ�� ������λֵ �����Ӧ��ͨ��λʱ ֵΪ0
    QList<quint8> m_ListChannelMap;//(�����Ӧ��ͨ��)

    QList<quint8> m_ListPhaseMap;//����1-16(20) ��Ӧ����λֵ ������ ��ͨ ���� ֻ�� �����й� 20���������� û����0������ phaseMap idֵ�����õ� ����ֵ
    QList<quint8> m_ListLoadNum;//����1-16 ����·���Ӧ�ĳ����� ����������� 20������
    QList<quint8> m_ListLoadMap;//1-CHANNELNUMͨ�� ��Ӧ����λֵ(1-40) index0-23��Ӧͨ��1-24   ʵʱ��ʾʱ�õ� �洢ͨ��1-MAX_CHANNEL_NUM()����Ӧ����λֵ
    QList<quint8> m_ListLoadNo;//�洢 ����Id���������� ·�ֻ꣨��洢ֱ��·�꼴�ɣ�
    QList<bool> m_ListValid;//�洢20��·�����ʾ���
    quint8 m_ucDir;//������ʾ����ͼ

    //�����
    bool m_bFlagDetSend;
    bool m_bFlagDetRead;

    //ʵʱ��ʾ����
    bool m_bBeginCheck;
    bool m_bFlagAutoReport;
    bool m_bFlagDetAutoReport;
    //�ڵ���Ϣ
    bool m_bFlagNodeNameFocus;//�޸Ľڵ���ʱΪtrue tree�����н��㡣Ĭ��false

    //�¼���־
    //bool m_bFlagEventLog;
    int m_iEventIndex;
    QStandardItemModel *m_pModelEventLog;
    QStringListModel *m_EventNameModel;
    CheckGroupDeligate* ckNodeNameDeligate;

    //�źŻ�����
    QStandardItemModel *m_pModelTscIp;

    quint32 m_uiCurNodeId;//��ǰ��ʾ�ڵ�Id ��1��
    quint8 m_ucCurClusterId;
    quint8 m_ucCurVipId;
    bool m_bFlagNodeIdChanged;//�ڵ���ʱ Ϊtrue���ڸ��� �� �����Ϊfalse ��ʼֵΪtrue;
//    bool m_bFlagInit;//��ʼֵΪfalse ����ȡ�ڵ��� ��ʼ���������� ��ɺ� Ϊtrue
    bool m_bFlagOnLine;//��ʼΪtrue TIMEOUT=5000����ʱ����Ϊfalse TIMEOUT=100;
    int m_iCurTscNameLisIndex;//��ǰ m_TscNameList��index ��0��

    QString m_strPage;
    //--------------Ⱥ------------------
    bool m_bFlagUpDateCTNode;//�ڵ��� Ⱥ�ڵ�ı�ʱ Ϊtrue���������ݵ�����˺���Ϊfalse
    ClusterProperty_Table *m_pCTProperty;


    SClusterInfo *m_pClusterInfo;
    QStringList m_ListCTId;
    QStringList m_ListCTDomainId;
    QStringList m_ListCTName;
    QStringList m_ListCTEnable;

    QStringListModel *m_pModelCTName;
    bool m_bFlagCTInit;//��һ�γ�ʼ��ʱ �Ż���Ҫ�� �ڵ���Ϣ��
    //-------�·�Ⱥ�ƻ���
    bool m_bFlagAddCT;
    bool m_bFlagSendCTPlan;
    quint8 m_ucSendCTPlanIndex;

    //------------Ⱥʱ��ͼ---------
    quint8 m_ucCTScheduleId;
    quint8 m_ucCTPlanId;//Ⱥ���跽����
    quint8 m_ucCTCircle;//Ⱥ����
    quint8 m_ucCTStageTime;//��ʱ��
    QStringList m_ListCTNodeId;//һ��Ⱥ��� �ڵ�
    QStringList m_ListCTNodeName;
    QStringListModel *m_pModelCTNodeName;
    QList<quint8> m_ListCTNodeIndex;//
//    QList<quint8> m_ListCTNodeStagePattern;//�׶���ʱ��
    QList<qint16> m_ListCTNodeOffset;//��λ��
    QList<quint8> m_ListStageTime;

    quint8 m_ucCTNodeSendIndex;//Ⱥ��tsc���ͷ����������λ��ʱ  �ѷ��͵�˳��
    bool m_bFlagCluster;//treeview���Ⱥʱ ��true �� timebase����m_bFlagCluster������
    bool m_bFlagClusterSend;
    bool m_bFlagReadCluster;//Ⱥʱ��ͼ ��ȡʱ �ȶ�ȡ �ڵ���Ϣ�� ��� index

    //------------------vip--------------
    SVipInfo *m_pVipInfo;
    bool m_bFlagVipInit;//���ڸ����б�ʱ ����Ӧ���

    QList<quint8> m_ListVipId;
    QStandardItemModel *m_pModelVipId;
    QList<quint16> m_ListVipNodeId;
    QList<quint8> m_ListVipNodeStage;
    QList<quint16> m_ListVipNodeTime;

    bool m_bFlagVipStateCheck;//���vip�ڵ��״̬
    quint32 m_iCurVipNodeId;//��ǰ��vip�ڵ�id
    //QMap<quint32,SVipData*> m_mapVip;
    VipProperty_Table *m_pVip;
    //quint8 m_ucVipNodeIndex;//���� vip ���ڵ��ȡʱ ����� �Ľڵ㣻

    //��ͨ����ͳ��
    QStandardItemModel *m_pModelTraffic;

    //------tree view-----------
    QModelIndexList m_ListClusterIndex;//Ⱥ vip �� ModelIndex
    QModelIndexList m_ListNodeIndex;
    //------------------
//    QIcon nodeIcon;

//    QIcon ctIcon;

//    QIcon dmtIcon;

//    QIcon vipIcon;
    //-----------------------


    QTimer *timer;//���ճ�ʱ
    qint32 m_iTimerId;
    quint8 m_ucTableName;
    bool m_bFlagTscTable;//��ȡtsc��ͷ������� �����־
    //QIcon m_nodeIcon;
    QByteArray m_cRcvData;
    int m_iComplete;
    int m_iDataLong;
    bool m_bComplete;
    int m_iHeadType;
    int m_iHeadNum;
    int m_iHeadSize;
    //-----------����˵�ַ �˿ڣ�
    QString m_strAddress;
    QString m_strPort;
    bool m_bFlagSingle;//true ������;false �����
    bool m_bFlagCtNode;//��tree�޸�Ⱥ��ڵ�ʱ��sendnodecommand����ֵ ������
    qint32 m_iCmdType;//����� tsc

    quint32 m_uiEventLogStart;
    quint32 m_uiEventLogEnd;
    QStringList m_ListEventLogSearch;

    int m_iTabWidgetIndex;

private:
    QSettings *m_setData;
    bool m_bFlagReadIni;

};

#endif // PDATAPROCESS_H
