//author: sun
//date:2011.09.29

#ifndef DTABLE_H
#define DTABLE_H
#include <QList>
#include <QDebug>
#include "DCommon.h"

typedef unsigned char byte;

class ctNodeColTime_Table//Ⱥ���ڵ� �׶�ʱ��
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

class SUtcsAllUserInfo//�û��б�
{
public:
    int iUserID;
    char cUserName[32];
    char cUserPwd[32];
    char ctUserRole[32];//1025���ģ���Ӧ����Ȩ��
    unsigned int iUserExpired;//����ʱ��
//    int iLogTime;//��½ʱ��
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
    unsigned int uiId;//�ڵ�ID  4
    unsigned char ucClusterId;//ȺID 1
    unsigned char ucClusterNodeIndex;//Ⱥ���ڵ� ����˳��
    char sDeviceName[MAXNAMELEN];//�ڵ�����
    char sDeviceIp[MAXNAMELEN];//�ڵ�IP
    unsigned short uiPort;//�ڵ�˿�
    char sVersion[MAXNAMELEN];//�豸�汾�� 5
    unsigned char ucLinkType;//�������� 1
    unsigned char ucProtocolType;//Э��汾 1
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
        char sVendor[VENDORLEN];//������
        byte bModuleModelLen;
        char sModuleModel[MODULEMODELLEN];//�ͺŹ��
        byte bVersionLen;
        char sVersion[VERSIONLEN];//�汾
        byte bModuleType;//1���� 2Ӳ�� 3���
};

//-------------------------------------------------------------------------------------
// timebase table property
class TimeBase_Table{
    public:
        //unsigned int uiNodeId;//1109xie add;9�ֽ�
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
        byte bNo;                   //ʱ�α��
        byte bEventNo;              // �¼���
        byte bHour;                 //��ʼʱ
        byte bMinute;               //��ʼ��
        byte bControlMode;          //���Ʒ�ʽ 0-�������ƣ�1-�صƣ�2-���⣻3-ȫ�죻6-��Ӧ��8-�����Ż���11-���ӿ��ƣ�12-ϵͳ�Ż���13-��Ԥ�߿�
        byte bTimePatternNo;        //��ʱ������
        byte bAssistantOut;         //�������
        byte bSpecialOut;           //�������

//        Schedule_Table()
//        {
//            memset(this,0,sizeof(Schedule_Table));
//        }
};

//-------------------------------------------------------------------------------------
// time table property
class TimePattern_Table{
    public:
        byte bNo;               //������
        byte bCycle;            //����ʱ��
        byte bOffset;           //��λ��
        byte bCoordinatePhase;  //Э����λ
        byte bStageTimeTableNo; //�׶���ʱ���

        TimePattern_Table()
        {
            memset(this,0,sizeof(TimePattern_Table));
        }
};

//-------------------------------------------------------------------------------------
// stagetime table property
class StageTime_Table{
    public:
        byte bNo;                        //��ʱ��
        byte bStageNo;                   //�׶κ�
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
        byte bControlType;//1:���� 2�������� 3������ 4������
};

// detector table property
class Detector_Table{
    public:
        byte bNo;
        byte bCallPhase;
        byte bProperty;//���Ͳ���
        byte bDirection;//����
        byte bDelayTime;//������Чʱ��
        byte bOption;//ѡ�����
        unsigned short uLaneSaturation;//��Ӧ�ؼ�������������
        byte bSaturationOccupancy;//����ռ����
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
    quint32 uiDeviceId;//�豸id
    quint8 uiDetectorId;      //������id
    quint32 uiRecordTime;    //��¼ʱ��
    quint32 uiSumVolume;     //����������
    byte    ucAvgOccupancy;  //ƽ��ռ����
    byte    ucMaxOccupancy;  //���ռ����
    byte    ucMinOccupancy;  //��Сռ����

};


////-------------------------------------------------------------------------------------
class STscInfo//�ڵ����
{
public:
    unsigned int uiId;//�ڵ�ID
    unsigned char ucClusterId;//ȺID
    char sDeviceName[MAXNAMELEN];//�ڵ����� 5�ֽ�
    char sDeviceIp[MAXNAMELEN];//�ڵ�IP
    unsigned short uiPort;//�ڵ�˿�
    char sVersion[MAXNAMELEN];//�豸�汾��
    unsigned char ucLinkType;//��������
    unsigned char ucProtocolType;//Э��汾

    int iTimeBaseTableNum;//ʱ������
    int iScheduleTableNum;//ʱ�α���
    int iTimePatternTableNum;//��ʱ������
    int iStageTimeTableNum;//�׶���ʱ��
    int iPhaseTableNum;//��ͨ��λ
    int iOverlapTableNum;//������λ
    int iChannelTableNum;//ͨ����
    int iPhaseMapTableNum;//�����
    int iModuleTableNum;//ģ����
    int iDetectorTableNum;//�����

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
            tbPhase[i].bNo = i+1;//��λId
        }
    }
    void initOverlapTable()
    {
        for(int i=0;i<MAX_OVERLAP_NUM;i++)
        {
            tbOverlap[i].bNo = i+1;//������λId
        }
    }
    void initPhaseMapTable()
    {
        for(int i=0;i<MAX_PHASEMAP_NUM;i++)
        {
            tbPhaseMap[i].bPhaseIconId = i+1;//��λӳ�� ·��
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
    byte ucClusterId;       //Ⱥ��
    byte ucDomainId;        //�������
    byte ucClusterNameLen;  //Ⱥ���Ƴ���
    byte ucClusterName[CLUSNAMELEN];
    byte ucClusterEnable;   //�Ƿ���Ч
    byte ucNodeIdList[MAX_CLUSTER_NODE_NUM];   //�ڵ��б�
    byte ucNodeIndexList[MAX_CLUSTER_NODE_NUM];   //�ڵ㳤��

};
//-------------------------------------------
class SClusterTimebase
{
public:
    byte   ucClusterId;   //Ⱥ��
    byte   bNo;      //���ȼƻ���
    unsigned short  uMonth;   //������
    byte   bWeek;    //�����գ����ܣ�
    unsigned long   lMonthDay;     //�����գ����£�
    byte   bScheduleId;  //ʱ�κ�

};

//----------------------------------------------
class SClusterSchedule
{
public:
    byte   ucClusterId;   //Ⱥ��
    byte ucScheduleId;    //ʱ�α��
    byte ucEventId;       //ʱ���¼���
    byte ucBeginHour;     //��ʼִ��ʱ�̵�������
    byte ucBeginMinute;   //��ʼִ�е�������
    byte ucTimePatternNo; //��ʱ������
    byte ucControlMode;   //���Ʒ�ʽ
//    byte ucCycle;         //Ⱥ����

};
//-----------------------------------------
class SClusterPattern
{
public:
    byte ucClusterId;  //Ⱥ��
    byte ucPatternId; //������
    byte ucCycleTime; //����ʱ��
    byte sOffsetList[MAX_CLUSTER_NODE_NUM];;    //�����ڵ����λ��
    byte ucCoordPhaseList[MAX_CLUSTER_NODE_NUM]; //�����ڵ��Э����λ
    byte ucStagePatternId;  //��Ӧ�Ľ׶���ʱ���

};

//----------------------------------------------
class SClusterInfo
{
public:
    byte ucClusterId;       //Ⱥ��
    byte ucDomainId;        //�������
    byte ucClusterNameLen;  //Ⱥ���Ƴ���
    byte ucClusterName[MAXNAMELEN];
    byte ucClusterEnable;   //�Ƿ���Ч

    int iTscNum;//�ڵ���
//    int iTscIdList[MAX_TSC_NUM];//Ⱥ�ڵ�id
    int iKeyTscId;//�ؼ��ڵ�id
    byte iCircle;//����
    int iScheduleNo;//ʱ�κ�
    byte iControlType;//���Ʒ�ʽ
    int iStrategyType;//����

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
    byte ucVipLineId;   //��·��
    byte ucValidity;    //��Ч��
    byte ucDirection;   //����
    byte ucControl;     //���Ʒ�ʽ
    unsigned int uiStartTime;   //��ʼʱ��
    unsigned int uiEndTime;     //����ʱ��
    unsigned short usNodeIdList[MAX_VIP_NODE_COUNT];   //�ڵ�id����
    byte sStageIdList[MAX_VIP_NODE_COUNT];  //�ڵ�׶�����
    unsigned short usTimeDifList[MAX_VIP_NODE_COUNT];  //�ڵ�ʱ�������

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
    byte bStagePatternId;//��ʱ��
    QList<quint8> listChannelMap;
    QList<quint8> listComMap;
    QList<quint8> listOverlapMap;
    QList<quint16> listStage;
    QList<quint8> listStageTime;//

    QList<quint8> m_ListPhaseMap;//����1-16(20) ��Ӧ����λֵ ������ ��ͨ ���� ֻ�� �����й� 20���������� û����0������ phaseMap idֵ�����õ� ����ֵ
    QList<quint8> m_ListLoadNum;//����1-16 ����·���Ӧ�ĳ����� ����������� 20������
    QList<quint8> m_ListLoadMap;//1-CHANNELNUMͨ�� ��Ӧ����λֵ(1-40) index0-23��Ӧͨ��1-24   ʵʱ��ʾʱ�õ� �洢ͨ��1-MAX_CHANNEL_NUM()����Ӧ����λֵ
    QList<quint8> m_ListLoadNo;//�洢 ����Id���������� ·�ֻ꣨��洢ֱ��·�꼴�ɣ�
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
