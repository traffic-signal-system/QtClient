//author: sun
//date:2011.09.29

#ifndef DTABLE_H
#define DTABLE_H
#include <QList>
#include <QDebug>
#include "DCommon.h"

typedef unsigned char byte;

class ctNodeColTime_Table//群属节点 阶段时间
{
public:
    unsigned char ucGreenTime;
    unsigned char ucYellowTime;
    unsigned char ucRedTime;
};



//-------------------------------------------------------------------------------------
// phase status table property
class PhaseStatus_Table{
    public:
        byte bNo;
        byte bRedStatus;
        byte bYellowStatus;
        byte bGreenStatus;
};



//-------------------------------------------------------------------------------------



//// detector data property
//class DetectorData_Table{
//    public:
//        byte bNo;
//        byte bTotalFlux;
//        byte bBigVehicleFlux;
//        byte bSmallVehicleFlux;
//        byte bVelocity;
//        byte bSpeed;
//        byte bVehicleLength;
//};


//-------------------------------------------------------------------------------------
// channel status table property
class ChannelStatus_Table{
    public:
        byte bNo;
        byte bRedStatus;
        byte bYellowStatus;
        byte bGreenStatus;
};





//-------------------------------------------------------------------------------------
// overlap status table property
class OverlapStatus_Table{
    public:
        byte bGroupNo;
        byte bRedStatus;
        byte bYellowStatus;
        byte bGreenStatus;
};



//-------------------------------------------------------------------------------------
// module status table property
class ModuleStatus_Table {
public:
    char sDeviceNode[DEVICENODELEN];
    char sVendor[VENDORLEN];
    char sModuleModel[MODULEMODELLEN];
    char sVersion[VERSIONLEN];
    byte ucModuleType;
};



//-------------------------------------------------------------------------------------
// tsc status table property
class TscStatus_Table{ //Default struct?????
public:
//    int iTscId;
//    int uiElapseTime;
//    bool bIsActivate;
//    bool bIsAbort;
//    unsigned long ulErrorWord;
//    Msg_Oper_Para_Type uiReadType; // =TSC_UNIT_STATUS_PARA read unit status, else read statistics

//    Tsc_Control_Status_Struct   tControlStatus;
//    PhaseStatus_Table_Struct    vPhaseStatus[MAX_PHASE_GROUPS];
//    ChannelStatus_Table_Struct  vChannelStatus[MAX_CHANNEL_GROUPS];
//    OverlapStatus_Table_Struct  vOverlapStatus[MAX_OVERLAP_GROUPS];
};


//-------------------------------------------------------------------------------------
// timer table property
class Timer_Table{
public:
    byte bNo;
    unsigned short usPhase;
    byte bOverlap;
    byte bType;
};

//-------------------------------------------------------------------------------------
// time status table property
class TimerStatus_Table{
public:
    byte bNo;
    byte bStatus;
};



//-------------------------------------------------------------------------------------
// symbol table property
class Symbol_Table{
public:
    byte bNo;
    byte bControlType;
    byte bSymbolNo;
    byte bSymbolProperty;
};

//-------------------------------------------------------------------------------------
// symbol status table property
class SymbolStatus_Table{
public:
    byte bNo;
    byte bStatus;
    byte bSymbolNo;
};

//-------------------------------------------------------------------------------------
// TSC PROPERTY
class TscProperty
{
public :
    int iId;
    char sName[TSCNAMELEN];
    int iClusterId;
    int iDomainId;
    unsigned long ulIp;
    unsigned long ulPort;
    ProtocolType eProtoclType;
    //int iTimeBaseTableNum;
    //int iTimePatternTableNum;
   // int iScheduleTableNum;
//    int iPhaseTableNum;
//    int iOverlapTableNum;
//    int iChannelTableNum;
    //int iStageTableNum;
//    int iDetectorTableNum;
    unsigned long ulLocalTime;
    int iBootFlashTime;
    int iBootRedTime;
    int iFlashFrquency;

    //TimeBase_Table      tbTimeBase[MAX_TIMEBASE_NUM];
//    Phase_Table         tbPhase[MAX_PHASE_NUM];
    //Schedule_Table      tbSchedule[MAX_SCHEDULE_NUM];
    //TimePattern_Table   tbTimePattern[MAX_TIMEPATTERN_NUM];
    //StageTime_Table     tbStage[MAX_STAGE_NUM];
//    Overlap_Table       tbOverlap[MAX_OVERLAP_NUM];
//    Channel_Table       tbChannel[MAX_CHANNEL_NUM];
//    Detector_Table      tbDetector[MAX_DETECTOR_NUM];
//    DetectorStatus_Table    tbDetectorStatus[MAX_DETECTORSTATUS_NUM];
//    TrafficStatistics_Table tbTrafficStatistics[MAX_DETECTOR_NUM];
//    DetectorAlarm_Table     tbDetectorAlarm[MAX_DETECTOR_NUM];
//    PhaseMap_Table          tbPhaseMap[MAX_PHASEMAP_NUM];
//    Module_Table            tbModule[MAX_MODULE_NUM];
    ModuleStatus_Table      tbModuleStatus[MAX_MODULE_NUM];
    Timer_Table             tbTimer[MAX_TIMER_NUM];
    TimerStatus_Table       tbTimerStatus[MAX_TIMER_NUM];
    Symbol_Table            tbSymbol[MAX_SYMBOL_NUM];
    SymbolStatus_Table      tbSymbolStatus[MAX_SYMBOL_NUM];
//    EventLog_Table          tbEventLog[MAX_EVENTLOG_NUM];

    TscStatus_Table         tbTscStatus;
};





class DomainProperty
{
public :
    int iId;
    char sName[DOMAINNAMELEN];
    int iClusterNum;
    int iClusterIdList[MAX_CLUSTER_NUM];
    int iClusterRelativity[MAX_CLUSTER_NUM];
};

class VipProperty
{
public :
    int iId;
};

class SysProperty
{
public :
    int iId;
};
//-----------------------------



//---------------------------

#pragma pack(1)
//-------------------------------------------------------------------------------------
//DbString

template <class TD, class TC>
class DbArray
{
public:
        DbArray(void)
        {
                m_uCount = 0;
                m_pData = NULL;
        };
        ~DbArray(void)
        {
                if (NULL != m_pData)
                {
                        //ACE_OS::free(m_pData);
                    delete[] m_pData;

                }
                m_pData     = NULL;
                m_uCount    = 0;
        };
        DbArray(const TD* pData, TC uCount)
        {
                m_uCount   = 0;
                m_pData    = NULL;

                if (0 == uCount || NULL == pData)
                {
                        return;
                }

                //m_pData = (TD*)ACE_OS::malloc(uCount*sizeof(TD));
                m_pData = new TD[uCount];

                if (NULL != pData)
                {
                        m_uCount = uCount;
                        //ACE_OS::memcpy(m_pData, pData, uCount*sizeof(TD));
                        memcpy(m_pData,pData,uCount*sizeof(TD));
                }
        };
        DbArray(DbArray& dbArray)
        {
                m_uCount   = 0;
                m_pData    = NULL;

                TC  uCount;
                TD* pData;

                pData = GetData(uCount);
                if (0 == uCount || NULL == pData)
                {
                        return;
                }

                //m_pData = (TD*)ACE_OS::malloc(uCount*sizeof(TD));
                m_pData = new TD[uCount];

                if (NULL != pData)
                {
                        m_uCount = uCount;
                        //ACE_OS::memcpy(m_pData, pData, uCount*sizeof(TD));
                        memcpy(m_pData,pData,uCount*sizeof(TD));
                }
        };
        TD* GetData(TC& uCount)
        {
                uCount = m_uCount;
                return m_pData;
        };
        TD* GetData()
        {
                return m_pData;
        }
        TC GetCount()
        {
                return m_uCount;
        };
        bool SetData(const TD* pData, TC uCount)
        {
                if (NULL != m_pData)
                {
                        //ACE_OS::free(m_pData);
                    delete[] m_pData;
                }

                m_pData = NULL;
                m_uCount = 0;

                if (0 == uCount || NULL == pData)
                {
                        return true;
                }

                //m_pData = (TD*)ACE_OS::malloc(uCount*sizeof(TD));
                m_pData = new TD[uCount];

                if (NULL != m_pData)
                {
                        m_uCount = uCount;
                        //ACE_OS::memcpy(m_pData, pData, uCount*sizeof(TD));
                        memcpy(m_pData,pData,uCount*sizeof(TD));
                }
                else
                {
                        return false;
                }

                return true;
        };
        bool SetString(const char* sString)
        {
                if (1 != sizeof(TD))
                {
                        return false;
                }

                TC   uCount;
                //uCount = (TC)(ACE_OS::strlen(sString) + 1);
                uCount = strlen(sString)+1;
                if (!AllocData(uCount))
                {
                        return false;
                }

                //ACE_OS::strcpy(m_pData, sString);
                memcpy(m_pData,sString,uCount);
                return true;
        };
        bool AllocData(TC uCount)
        {
                if (NULL != m_pData)
                {
                        //ACE_OS::free(m_pData);
                    delete[] m_pData;
                }

                m_pData = NULL;
                m_uCount = 0;

                if (0 == uCount)
                {
                        return true;
                }

                //m_pData = (TD*)ACE_OS::malloc(uCount*sizeof(TD));
                m_pData = new TD[uCount];

                if (NULL != m_pData)
                {
                        m_uCount = uCount;
                        //ACE_OS::memset(m_pData, 0, sizeof(TD)*uCount);
                        memset(m_pData,0,sizeof(TD)*uCount);
                }
                else
                {
                        return false;
                }

                return true;
        };

        DbArray &operator = (DbArray& dbArray)
        {
                if (NULL != m_pData)
                {
                        //ACE_OS::free(m_pData);
                    delete[] m_pData;
                }

                m_pData = NULL;
                m_uCount = 0;


                TC  uCount;
                TD* pData = dbArray.GetData(uCount);

                if (0 == uCount || NULL == pData)
                {
                        return *this;
                }

                //m_pData = (TD*)ACE_OS::malloc(uCount*sizeof(TD));
                m_pData = new TD[uCount];

                if (NULL != m_pData)
                {
                        m_uCount = uCount;
                        //ACE_OS::memcpy(m_pData, pData, uCount*sizeof(TD));
                        memcpy(m_pData,pData,uCount*sizeof(TD));
                }

                return *this;
        };
private:
        TC      m_uCount;
        TD*     m_pData;
};


typedef DbArray<char, unsigned char>       DbString;
class SUtcsFrameHead
{
public:
    int uiCommandType;
    int uiIdNum;
    int uiDataSize;

    SUtcsFrameHead()
    {

        memset(this,0,sizeof(SUtcsFrameHead));
    }

};
//------------------------------------

class SUtcsAllUserInfo//用户列表
{
public:
    int iUserID;
    char cUserName[32];
    char cUserPwd[32];
    char ctUserRole[32];//1025更改，对应具体权限
    unsigned int iUserExpired;//过期时间
//    int iLogTime;//登陆时间
//    char addrIp[32];

    SUtcsAllUserInfo()
    {
        memset(this,0,sizeof(SUtcsAllUserInfo));

    }
};
//-----------------------------------------
class STscNode
{
public:
    unsigned int uiId;//节点ID  4
    unsigned char ucClusterId;//群ID 1
    unsigned char ucClusterNodeIndex;//群属节点 排列顺序
    char sDeviceName[MAXNAMELEN];//节点名称
    char sDeviceIp[MAXNAMELEN];//节点IP
    unsigned short uiPort;//节点端口
    char sVersion[MAXNAMELEN];//设备版本号 5
    unsigned char ucLinkType;//连接类型 1
    unsigned char ucProtocolType;//协议版本 1
    STscNode()
    {
        init();
    }
    void init()
    {
        memset(this,0,sizeof(STscNode));
    }

};

//-------------------------------------
// module table property
class Module_Table{
    public:
        byte bNo;
        byte bNodeLen;
        char sDeviceNode[DEVICENODELEN];
        byte bVendorLen;
        char sVendor[VENDORLEN];//制造商
        byte bModuleModelLen;
        char sModuleModel[MODULEMODELLEN];//型号规格
        byte bVersionLen;
        char sVersion[VERSIONLEN];//版本
        byte bModuleType;//1其它 2硬件 3软件
};

//-------------------------------------------------------------------------------------
// timebase table property
class TimeBase_Table{
    public:
        //unsigned int uiNodeId;//1109xie add;9字节
        byte bNo;
        unsigned short uMonth;
        byte bWeekDay;
        unsigned long lMonthDay;
        byte bScheduleNo;
        TimeBase_Table()
        {
            memset(this,0,sizeof(TimeBase_Table));
        }
};

//-------------------------------------------------------------------------------------
// schedule table property
class Schedule_Table{
    public:
        byte bNo;                   //时段表号
        byte bEventNo;              // 事件号
        byte bHour;                 //开始时
        byte bMinute;               //开始分
        byte bControlMode;          //控制方式 0-自主控制；1-关灯；2-闪光；3-全红；6-感应；8-单点优化；11-主从控制；12-系统优化；13-干预线控
        byte bTimePatternNo;        //配时方案号
        byte bAssistantOut;         //辅助输出
        byte bSpecialOut;           //特殊输出

//        Schedule_Table()
//        {
//            memset(this,0,sizeof(Schedule_Table));
//        }
};

//-------------------------------------------------------------------------------------
// time table property
class TimePattern_Table{
    public:
        byte bNo;               //方案号
        byte bCycle;            //周期时长
        byte bOffset;           //相位差
        byte bCoordinatePhase;  //协调相位
        byte bStageTimeTableNo; //阶段配时表号

        TimePattern_Table()
        {
            memset(this,0,sizeof(TimePattern_Table));
        }
};

//-------------------------------------------------------------------------------------
// stagetime table property
class StageTime_Table{
    public:
        byte bNo;                        //配时号
        byte bStageNo;                   //阶段号
        unsigned short uEnablePhase;
        byte bGreenTime;
        byte bYellowTime;
        byte bRedTime;
        byte bOption;
};

//-------------------------------------------------------------------------------------
// phase table property
class Phase_Table{
    public:
        byte bNo;
        byte bPedestrianGreenTime;
        byte bPedestrianClearTime;
        byte bMinGreenTime;
        byte bDelayGreenUnit;
        byte bMaxGreenTime1;
        byte bMaxGreenTime2;
        byte bFixedGreenTime;
        byte bGreenFlashTime;
        byte bPhaseType;
        byte bPhaseOption;
        byte bPhaseExtend;
};

//-------------------------------------------------------------------------------------
// overlap table property
class Overlap_Table{
    public:
        byte bNo;
        byte bType;
        byte bIncludedPhaseLen;
        byte bIncludedPhase[INCLUDEPHASELEN];
        byte bModifierPhaseLen;
        byte bModifierPhase[MODIFIERPHASELEN];
        byte bTailGreen;
        byte bTailYellow;
        byte bTailRed;
};

//-------------------------------------------------------------------------------------
// phasemap table property
class PhaseMap_Table{
    public:
        byte bPhaseIconId;
        byte bCommonPhaseNo;
        byte bOverlapPhaseNo;
        byte bLaneNum;
};

//-------------------------------------------------------------------------------------
// channel table property
class Channel_Table{
    public:
        byte bNo;
        byte bControlSource;
        byte bControlMode;
        byte bControlType;//1:其它 2：机动车 3：行人 4：跟随
};

// detector table property
class Detector_Table{
    public:
        byte bNo;
        byte bCallPhase;
        byte bProperty;//类型参数
        byte bDirection;//方向
        byte bDelayTime;//请求有效时间
        byte bOption;//选项参数
        unsigned short uLaneSaturation;//对应关键车道饱和流量
        byte bSaturationOccupancy;//饱和占有率
};

//-------------------------------------------------------------------------------------
// phase conflict table property
class PhaseConflict_Table{
    public:
        byte bNo;
        unsigned short uConflictPhase;
};

//-------------------------------------------------------------------------------------
// detector status table property
class DetectorStatus_Table{
    public:
        byte bNo;
        byte bStatus;
        byte bAlarm;
};

//-------------------------------------------------------------------------------------


// detector alarm property
class DetectorAlarm_Table{
    public:
        byte bNo;
        byte bAlarmStatus;
        byte bCoilAlarmStatus;
};

//-------------------------------------------------------------------------------------
// event log table property
class EventLog_Table{
    public:
        byte bEventTypeNo;
        byte bEventNo;
        unsigned long lEventTime;
        unsigned long lEventData;
};

//-------------------------------------------------------------------------------------
// event type table property

class EventType_Table{
    public:
        byte bNo;
        unsigned long lClearTime;
        byte bEventLen;
        char sEventType[EVENT_TYPE_LEN];
        byte bLogRowNum;
};



//----------------------------------------
// traffic statistics table property
class TrafficStatistics_Table{
    public:
//        byte bNo;
//        byte bVolume;
//        byte bLongSizeVolume;
//        byte bSmallSizeVolume;
//        byte bOccupancy;
//        byte bVelocity;
//        byte bVehicleLength;
    quint32 uiDeviceId;//设备id
    quint8 uiDetectorId;      //传感器id
    quint32 uiRecordTime;    //记录时间
    quint32 uiSumVolume;     //车流量总量
    byte    ucAvgOccupancy;  //平均占有率
    byte    ucMaxOccupancy;  //最大占有率
    byte    ucMinOccupancy;  //最小占有率

};


////-------------------------------------------------------------------------------------
class STscInfo//节点参数
{
public:
    unsigned int uiId;//节点ID
    unsigned char ucClusterId;//群ID
    char sDeviceName[MAXNAMELEN];//节点名称 5字节
    char sDeviceIp[MAXNAMELEN];//节点IP
    unsigned short uiPort;//节点端口
    char sVersion[MAXNAMELEN];//设备版本号
    unsigned char ucLinkType;//连接类型
    unsigned char ucProtocolType;//协议版本

    int iTimeBaseTableNum;//时基表数
    int iScheduleTableNum;//时段表数
    int iTimePatternTableNum;//配时方案数
    int iStageTimeTableNum;//阶段配时数
    int iPhaseTableNum;//普通相位
    int iOverlapTableNum;//跟随相位
    int iChannelTableNum;//通道数
    int iPhaseMapTableNum;//方向表
    int iModuleTableNum;//模块数
    int iDetectorTableNum;//检测器

    Module_Table            tbModule[MAX_MODULE_NUM];
    TimeBase_Table          tbTimeBase[MAX_TIMEBASE_NUM];
    Schedule_Table          tbSchedule[MAX_SCHEDULE_NUM][MAX_SCHEDULE_EVENT_NUM];
    TimePattern_Table       tbTimePattern[MAX_TIMEPATTERN_NUM];
    StageTime_Table         tbStageTime[MAX_STAGE_PATTERN_NUM][MAX_STAGE_NUM];
    Phase_Table             tbPhase[MAX_PHASE_NUM];
    Overlap_Table           tbOverlap[MAX_OVERLAP_NUM];
    Channel_Table           tbChannel[MAX_CHANNEL_NUM];
    PhaseMap_Table          tbPhaseMap[MAX_PHASEMAP_NUM];
    PhaseConflict_Table     tbPhaseConflict[MAX_CONFLICT_NUM];
    Detector_Table          tbDetector[MAX_DETECTOR_NUM];
    DetectorStatus_Table    tbDetectorStatus[MAX_DETECTORSTATUS_NUM];
    DetectorAlarm_Table     tbDetectorAlarm[MAX_DETECTOR_NUM];
    EventLog_Table          tbEventLog[MAX_EVENTLOG_NUM];
//    TrafficStatistics_Table tbTrafficStatistics[MAX_DETECTOR_NUM];

    STscInfo()
    {
        memset(this,0,sizeof(STscInfo));
        initScheduleTable();
        initPhaseTable();
        initOverlapTable();
        //initPhaseMapTable();
        initChannelTable();

    }
    ~STscInfo()
    {
        qDebug()<<"~STscInfo";
    }
    void initScheduleTable()
    {
        for(int i=0;i<MAX_SCHEDULE_NUM;i++)
        {
            for(int j=0;j<MAX_SCHEDULE_EVENT_NUM;j++)
            {
                tbSchedule[i][j].bNo = i+1;
                tbSchedule[i][j].bEventNo = 0;
                tbSchedule[i][j].bHour = 0;
                tbSchedule[i][j].bMinute = 0;
                tbSchedule[i][j].bControlMode = 0;
                tbSchedule[i][j].bTimePatternNo = 0;
                tbSchedule[i][j].bAssistantOut = 0;
                tbSchedule[i][j].bSpecialOut = 0;
            }
        }
    }
    void initStageTimeTable()
    {
        for(int i=0;i<MAX_STAGE_PATTERN_NUM;i++)
        {
            for(int j=0;j<MAX_STAGE_NUM;j++)
            {
                tbStageTime[i][j].bNo = i+1;
                tbStageTime[i][j].bGreenTime = 0;
                tbStageTime[i][j].bOption = 0;
                tbStageTime[i][j].bRedTime = 0;
                tbStageTime[i][j].bStageNo = 0;
                tbStageTime[i][j].bYellowTime = 0;
                tbStageTime[i][j].uEnablePhase = 0;
            }
        }
    }

    void initPhaseTable()
    {
        for(int i=0;i<MAX_PHASE_NUM;i++)
        {
            tbPhase[i].bNo = i+1;//相位Id
        }
    }
    void initOverlapTable()
    {
        for(int i=0;i<MAX_OVERLAP_NUM;i++)
        {
            tbOverlap[i].bNo = i+1;//跟随相位Id
        }
    }
    void initPhaseMapTable()
    {
        for(int i=0;i<MAX_PHASEMAP_NUM;i++)
        {
            tbPhaseMap[i].bPhaseIconId = i+1;//相位映射 路标
        }
    }
    void initChannelTable()
    {
        for(int i=0;i<MAX_CHANNEL_NUM;i++)
        {
            tbChannel[i].bNo = i+1;
        }
    }


};

//-----------------------------------------
//cluster property talbe
class ClusterProperty_Table
{
public:
    byte ucClusterId;       //群号
    byte ucDomainId;        //所属域号
    byte ucClusterNameLen;  //群名称长度
    byte ucClusterName[CLUSNAMELEN];
    byte ucClusterEnable;   //是否有效
    byte ucNodeIdList[MAX_CLUSTER_NODE_NUM];   //节点列表
    byte ucNodeIndexList[MAX_CLUSTER_NODE_NUM];   //节点长度

};
//-------------------------------------------
class SClusterTimebase
{
public:
    byte   ucClusterId;   //群号
    byte   bNo;      //调度计划号
    unsigned short  uMonth;   //调度月
    byte   bWeek;    //调度日（按周）
    unsigned long   lMonthDay;     //调度日（按月）
    byte   bScheduleId;  //时段号

};

//----------------------------------------------
class SClusterSchedule
{
public:
    byte   ucClusterId;   //群号
    byte ucScheduleId;    //时段表号
    byte ucEventId;       //时段事件号
    byte ucBeginHour;     //开始执行时刻的整点数
    byte ucBeginMinute;   //开始执行的整分数
    byte ucTimePatternNo; //配时方案号
    byte ucControlMode;   //控制方式
//    byte ucCycle;         //群周期

};
//-----------------------------------------
class SClusterPattern
{
public:
    byte ucClusterId;  //群号
    byte ucPatternId; //方案号
    byte ucCycleTime; //周期时长
    byte sOffsetList[MAX_CLUSTER_NODE_NUM];;    //各个节点的相位差
    byte ucCoordPhaseList[MAX_CLUSTER_NODE_NUM]; //各个节点的协调相位
    byte ucStagePatternId;  //对应的阶段配时表号

};

//----------------------------------------------
class SClusterInfo
{
public:
    byte ucClusterId;       //群号
    byte ucDomainId;        //所属域号
    byte ucClusterNameLen;  //群名称长度
    byte ucClusterName[MAXNAMELEN];
    byte ucClusterEnable;   //是否有效

    int iTscNum;//节点数
//    int iTscIdList[MAX_TSC_NUM];//群节点id
    int iKeyTscId;//关键节点id
    byte iCircle;//周期
    int iScheduleNo;//时段号
    byte iControlType;//控制方式
    int iStrategyType;//策略

    //ClusterProperty_Table       tbCTProperty[MAX_CLUSTER_NUM];
    TimeBase_Table            tbCTTimeBase[MAX_TIMEBASE_NUM];
    Schedule_Table            tbCTSchedule[MAX_SCHEDULE_NUM][MAX_SCHEDULE_EVENT_NUM];
    SClusterPattern           tbCTPattern[MAX_TIMEPATTERN_NUM];
    SClusterInfo()
    {
        init();
    }

    void init()
    {
        memset(this->tbCTTimeBase,0,sizeof(TimeBase_Table)*MAX_TIMEBASE_NUM);
        memset(this->tbCTPattern,0,sizeof(SClusterPattern)*MAX_TIMEPATTERN_NUM);
        initScheduleTable();
    }

    void initScheduleTable()
    {
        for(int i=0;i<MAX_SCHEDULE_NUM;i++)
        {
            for(int j=0;j<MAX_SCHEDULE_EVENT_NUM;j++)
            {
                tbCTSchedule[i][j].bNo = i+1;
                tbCTSchedule[i][j].bEventNo = 0;
                tbCTSchedule[i][j].bHour = 0;
                tbCTSchedule[i][j].bMinute = 0;
                tbCTSchedule[i][j].bControlMode = 0;
                tbCTSchedule[i][j].bTimePatternNo = 0;
                tbCTSchedule[i][j].bAssistantOut = 0;
                tbCTSchedule[i][j].bSpecialOut = 0;
            }
        }
    }
};

class ClusterProperty
{
public:
    int iId;
    char sName[CLUSNAMELEN];
    int iDomainId;
    int iTscNum;
    int iTscIdList[MAX_TSC_NUM];
    int iKeyTscId;
    int iTscRelativity[MAX_TSC_NUM];
    int iTscPhaseDifference[MAX_TSC_NUM];
    int iCircle;
    int iScheduleNo;
    int iControlType;
    int iStrategyType;
};
//-----------------------------------------

class VipProperty_Table
{
public:
    byte ucVipLineId;   //线路号
    byte ucValidity;    //有效性
    byte ucDirection;   //方向
    byte ucControl;     //控制方式
    unsigned int uiStartTime;   //开始时间
    unsigned int uiEndTime;     //结束时间
    unsigned short usNodeIdList[MAX_VIP_NODE_COUNT];   //节点id序列
    byte sStageIdList[MAX_VIP_NODE_COUNT];  //节点阶段序列
    unsigned short usTimeDifList[MAX_VIP_NODE_COUNT];  //节点时间差序列

};
//---------------------------------------------------------
class SVipInfo
{
public:
    VipProperty_Table tbVipProperty[MAX_VIP_NUM];
    SVipInfo()
    {
        init();
    }
    ~SVipInfo()
    {
        qDebug()<<"~SVipInfo";
    }

    void init()
    {
        memset(this,0,sizeof(VipProperty_Table)*MAX_VIP_NUM);
    }
};

class SVipData
{
public:
    byte bStagePatternId;//配时号
    QList<quint8> listChannelMap;
    QList<quint8> listComMap;
    QList<quint8> listOverlapMap;
    QList<quint16> listStage;
    QList<quint8> listStageTime;//

    QList<quint8> m_ListPhaseMap;//方向1-16(20) 对应的相位值 不区分 普通 跟随 只跟 数字有关 20个方向填满 没有填0；根据 phaseMap id值解析得到 方向值
    QList<quint8> m_ListLoadNum;//方向1-16 各个路标对应的车道数 检测器界面用 20个方向
    QList<quint8> m_ListLoadMap;//1-CHANNELNUM通道 对应的相位值(1-40) index0-23对应通道1-24   实时显示时用到 存储通道1-MAX_CHANNEL_NUM()所对应的相位值
    QList<quint8> m_ListLoadNo;//存储 方向Id，用来决定 路标（只需存储直行路标即可）
    QList<bool> m_ListValid;
    quint8 m_ucDir;

    SVipData()
    {
        bStagePatternId = 0;
        m_ucDir = 0;
    }
    ~SVipData()
    {
        init();
        qDebug()<<"~SVipData";
    }
    void init()
    {
        bStagePatternId = 0;
        m_ucDir = 0;
        listChannelMap.clear();
        listComMap.clear();
        listOverlapMap.clear();
        listStage.clear();
        listStageTime.clear();
        m_ListPhaseMap.clear();
        m_ListLoadNum.clear();
        m_ListLoadMap.clear();
        m_ListLoadNo.clear();
        m_ListValid.clear();
    }
};

#pragma pack()



#endif // DTABLE_H
