//author: sun
//date:2011.09.29

#ifndef DCOMMON_H
#define DCOMMON_H

#define SINGLEMODE  //������

#define SAVE_INI_MODEL 0
#define SAVE_INI_PHASE 1
#define SAVE_INI_CONFLICT 2
#define SAVE_INI_PATTERN 3
#define SAVE_INI_STAGE 4
#define SAVE_INI_DET 5
#define SAVE_INI_TIMEBASE 6
#define SAVE_INI_SCHEDULE 7

#define READ_INI_MODEL 0
#define READ_INI_PHASE 1
#define READ_INI_CONFLICT 2
#define READ_INI_PATTERN 3
#define READ_INI_STAGE 4
#define READ_INI_DET 5
#define READ_INI_TIMEBASE 6
#define READ_INI_SCHEDULE 7

//#define QT_NO_DEBUG_OUTPUT
#define TRAFFICY 200//
#define TRAFFICUNIT 20 //ÿ�� ���ʱ��ĳ���
#define TRAFFICX 500 //
#define TRAFFICWIDTH 680
#define TRAFFICHEIGHT 250
#define TRAFFICDISY 15//ͼ�����Ͻ� �� 0��yֵ
#define TRAFFICDISX 30
#define UNITPAGECNT 9

#define TIMEOUT5000 8000//��ʱʱ��
#define TIMEOUT100 50//��ʱʱ��
#define TIMEOUT600 600//�������
#define MAXNAMELEN 32//���� ��󳤶�
#define LBFOURTH 3//���ӷ����״̬
#define LBSECOND 1//��ʼ�� ��ǰҳ�� ������Ϣ
#define LBTHIRD 2//��ǰȺ �ڵ�״̬
#define LBFIRST 0
#define MAX_CLUSTER_NODE_NUM 16
#define MAX_DETECTORNUM 32

#define DEVICENODELEN   16
#define VENDORLEN       32
#define MODULEMODELLEN  16
#define VERSIONLEN      4//0409
#define EVENT_TYPE_LEN 64
#define MODIFIERPHASELEN 16
#define INCLUDEPHASELEN 16

#define TSCNAMELEN      64
#define CLUSNAMELEN     64
#define DOMAINNAMELEN   64

#define MAX_LOGIN_NUM          64
#define MAX_RECV_FRAME_NUM    256
#define MAX_ONLINE_TIME        48*360   // not over 2 days
#define MAX_OBJECT_NUM         16       // maxium objects exchange with TSC a time
#define MAX_MODULE_NUM         16
#define MAX_PHASE_NUM          16
#define MAX_TIMEBASE_NUM       40

#define SPECIAL_TIMEBASE_INDEX   0   //����ʱ����洢λ��0~19������ʱ���� 0522edit
#define SUM_TIMEBASE_INDEX     20    //20~29������ʱ����
#define WIN_TIMEBASE_INDEX     30    //30~39������ʱ����

#define MAX_TIMEPATTERN_NUM    16
#define MAX_CONFLICT_NUM       16
#define MAX_CHANNEL_NUM        16
#define MAX_CHANNELNUM_BOARD   4
#define MAX_OVERLAP_NUM        8
#define MAX_DETECTOR_NUM       48
#define MAX_DETECTORSTATUS_NUM 8
#define MAX_PATTERN_NUM        32
#define MAX_STAGE_NUM          16//��ά
#define MAX_STAGE_PATTERN_NUM  16//һά�׶�
#define MAX_SCHEDULE_NUM       16
#define MAX_SCHEDULE_EVENT_NUM 48
#define MAX_PLAN_NUM           40
#define MAX_LANE_TYPE_NUM       4
#define MAX_LANES_NUM_DIRECTION 8
#define MAX_PHASE_COLOR_NUM     4   // include NULL color
#define MAX_DIRECTION_NUM       4
#define MAX_NAME_LEN           32
#define MAX_PHASEMAP_NUM       16//16������������,���ι������ ���ܱ� ��Ӱ�� ����getListIconIndex
#define MAX_TIMER_NUM          32
#define MAX_SYMBOL_NUM         16
#define MAX_EVENTLOG_NUM       256

#define MAX_TSC_NUM            256
#define MAX_CLUSTER_NUM        64
#define MAX_DOMAIN_NUM         64
#define MAX_VIP_NUM            16
#define MAX_VIP_NODE_COUNT     16//0317
#define MAX_SYSTEM_NUM         1

typedef unsigned char byte;


enum ProtocolType
{
    GBT_20999
} ;

//��ͬ���ݣ���������ͬ����
/*
*ϵͳ������
*/
typedef enum
{
        TSC_MAX_MODULE       = 0x82,  //����ģ����������  16
        TSC_MAX_TIMEBASE     = 0x89,  //ʱ�����ȱ��������  40
        TSC_MAX_SCHEDULE_ONE = 0x8A,  //ʱ�α��������      16
        TSC_MAX_SCHEDULE_TWO = 0x8B,  //ʱ�α�����ʱ����  48
        TSC_MAX_EVENTTYPE    = 0x8F,  //�¼����ͱ��������   255
        TSC_MAX_EVENTLOG     = 0x90,  //�¼���־���������� 255
        TSC_MAX_PHASE        = 0x93,  //��λ���������       16
        TSC_MAX_PHASESTS     = 0X94,  //��λ״̬���������    2
        TSC_MAX_DETECTOR     = 0x98,  //����������������    48
        TSC_MAX_DETECTORSTS  = 0x99,  //�����״̬���������� 6
        TSC_MAX_CHANNEL      = 0xAE,  //�źŻ�֧�ֵ����ͨ������ 16
        TSC_MAX_CHANNELSTS   = 0xAF,  //ͨ��״̬����              2
        TSC_MAX_TIMEPATTERN      = 0xB2,  //��ʱ������            32
        TSC_MAX_SCHEDULETIME_ONE = 0xB3,  //���׶���ʱ����      16
        TSC_MAX_SCHEDULETIME_TWO = 0xB4,  //���׶���            16
        TSC_MAX_OVERLAPPHASE     = 0xC6,  //������λ���������     8
        TSC_MAX_OVERLAPPHASESTS  = 0xC7  //������λ״̬��������� 1
} TscConfig;

typedef enum
{
    TSC_TABLE_MODULE        = 0x85,  //ģ���
    TSC_TABLE_TIMEBASE      = 0x8D,  //ʱ����
    TSC_TABLE_SCHEDULE      = 0x8E,  //ʱ�α�
    TSC_TABLE_EVENTTYPE     = 0x91,  //�¼����ͱ�
    TSC_TABLE_EVENTLOG      = 0x92,  //�¼���־��
    TSC_TABLE_PHASE         = 0x95,  //��λ��
    TSC_TABLE_PHASECONFLICT = 0x97,  //��λ��ͻ��
    TSC_TABLE_DETECTOR      = 0x9F,  //�������
    TSC_TABLE_START_FLASH   = 0xA3 ,  //����ʱ���������ʱ��
    TSC_TABLE_START_ALLRED  = 0xA4,  //����ʱ��ȫ�����ʱ��
    TSC_TABLE_CHANNEL       = 0xB0,  //ͨ����
    TSC_TABLE_TIMEPATTERN   = 0xC0,  //��ʱ������
    TSC_TABLE_STAGETIME     = 0xC1,  //�׶���ʱ��
    TSC_TABLE_OVERLAP       = 0xC8,   //������λ��
    TBL_TABLE_PHASE2DIREC   = 0xfa
} TscTableType;


typedef enum
{
    TSC_COMMAND_CURTSC_CTRL          = 0xA5, //��ǰ���źŻ�����״̬
    TSC_COMMAND_SWITCH_MANUALCONTROL = 0xB5, //�ֶ����Ʒ���
    TSC_COMMAND_SWITCH_SYSTEMCONTROL = 0xB6, //ϵͳ���Ʒ���
    TSC_COMMAND_SWITCH_CONTROL       = 0xB7, //���Ʒ�ʽ
    TSC_COMMAND_SWITCH_STAGE         = 0xBA, //�׶�״̬
    TSC_COMMAND_GOSTEP               = 0xBB, //����ָ��

    TSC_COMMAND_UTC_TIME             = 0x86,  //����ʱ��
    TSC_COMMAND_LOCAL_TIME           = 0x88,  //����ʱ��
    TSC_COMMAND_REPORTSELF           = 0xf7   //�����ϱ������
} TscCommandType;



typedef enum
{
    TSC_STATUS_CHANNEL               = 0xB1, //ͨ�����״̬
    TSC_STATUS_OVERLAP               = 0xC9, //������λ״̬
    TSC_STATUS_PHASE                 = 0x96, //��λ���״̬
    TSC_STATUS_CURTSC_FLASHCTRL      = 0xA6, //��ǰ���������ģʽ
    TSC_STATUS_ACTIVESCHEDULE_NO     = 0x8c, //�ʱ�α�ı��
    TSC_STATUS_ALARM2                = 0xA7, //�źŻ�����
    TSC_STATUS_ALARM1                = 0xA8, //�źŻ�����
    TSC_STATUS__ALARM_SUMMARY        = 0xA9, //�źŻ�����ժҪ
    TSC_STATUS_ACTIVEDETECTOR_NUM    = 0x9C, //����������
    TSC_STATUS_DETECTORSTS           = 0xA0, //�����״̬
    TSC_STATUS_DETECTORDATA          = 0xA1, //��ͨ�������
    TSC_STATUS_DETECTORWARN_TABLE    = 0xA2, //�������������
    TSC_STATUS_CURPATTERN_SCHTIMES   =0xBF, //��ǰ�������׶�ʱ��
    TSC_STATUS_CURPATTERN_GREENTIMES = 0xC0, //��ǰ�������ؼ���λ�̵�ʱ��
    TSC_STATUS_EXTEND                = 0xF8, //�źŻ���չ״̬

    TSC_STATUS_UTC_TIME              = 0x86,  //����ʱ��
    TSC_STATUS_LOCAL_TIME            = 0x88,  //����ʱ��
} TscStatusType;



typedef enum
{
    NODE_ADD    = 0x10,   //�����ڵ�
    NODE_DELETE = 0x11,   //ɾ���ڵ�
    NODE_UPDATE = 0x12,   //�޸Ľڵ�
    NODE_READ   = 0x13,   //�ڵ��ȡ
    NODE_WRITE  = 0x14    //�ڵ�д
}TscOperate;

typedef enum
{
    CLUSTER_ADD            = 0x20 ,  //����Ⱥ
    CLUSTER_DELETE         = 0x21 ,  //ɾ��Ⱥ
    CLUSTER_UPDATE         = 0x22 ,  //�޸�Ⱥ
    CLUSTER_PROPERTY       = 0x23 ,  //Ⱥ���Ա�
    CLUSTER_TIMEBASE       = 0x24 ,  //Ⱥʱ����
    CLUSTER_SCHEDULE       = 0x25 ,  //Ⱥʱ�α�
    CLUSTER_TIMEPATTERN    = 0x26///Ⱥ������
   // CLUSTER_SET_TIME       = 0x26    //ȺУʱ
}ClusterOperate;


typedef enum
{
    DOMAIN_ADD    = 0x30,   //������
    DOMAIN_DELETE = 0x31,   //ɾ����
    DOMAIN_UPDATE = 0x32,   //�޸���
    DOMAIN_READ   = 0x33,   //���ȡ
    DOMAIN_WRITE  = 0x34    //��д
}DomainOperate;

/*
*vip����ָ��
*/
typedef enum
{
        VIP_START = 0x38 ,  //vip ����
        VIP_STOP  = 0x39    //vip ����
}VipOperate;

typedef enum
{
    USER_ADD    = 0x40,   //�����û�
    USER_DELETE = 0x41,   //ɾ���û�
    USER_UPDATE = 0x42,   //�޸��û�
    USER_READ   = 0x43,   //�û��б��ȡ
    USER_WRITE  = 0x44,   //�û��б�д
    USER_IN     = 0x45,   //�û���½
    USER_OUT    = 0x46    //�û��˳�
} UserOperate;


//typedef enum
//{
//    LOCAL_TABLE_DAILYSTATISTICS    = 0x50,  //������ͳ�Ʊ�
//    LOCAL_TABLE_DEVICE_OPERATE_LOG = 0x52,  //�豸������־
//    LOCAL_TABLE_USER_OPERATE_LOG   = 0x53   //�û�������־

//}DatabaseOperate;

/*
*�������ݿ����
*/
typedef enum
{
        LOCAL_TABLE_USERINFO           = 0x50,  //�û���
        LOCAL_TABLE_USER_OPERATE_LOG   = 0x51,  //�û�������־
        LOCAL_TABLE_NODE               = 0x52,  //�ڵ��
        LOCAL_TABLE_CLUSTER            = 0x53,  //Ⱥ��
        LOCAL_TABLE_DOMAIN             = 0x54,  //���
        LOCAL_TABLE_DEVICE_OPERATE_LOG = 0x55,  //�豸������־
        LOCAL_TABLE_TRAFFICSTATISTICS  = 0x56,   //������ͳ�Ʊ�
        LOCAL_TABLE_CFG_PARA           = 0x57,   //����������ñ�
        LOCAL_VIP                      = 0x58    //vip���Ʊ�
}DatabaseOperate;


typedef enum
{
    LOG_TYPE_TSC             = 0x60, //�źŻ��ڲ���־
    LOG_TYPE_DAILYSTATISTICS = 0x61, //������ͳ�Ʊ�
    LOG_TYPE_DEVICE          = 0x62, //�豸������־
    LOG_TYPE_USER            = 0x63  //�û�������־
}LogType;


typedef enum
{
    DATA_TYPE_PARA = 0,  //����
    DATA_TYPE_ERR  = 1   //��������
}DataType;


typedef enum
{
    CS_ERRTYPE_RIGHT       = 0x00  ,  //��ȷ
    CS_ERRTYPE_PACK        = 0x01  ,  //���ݰ���ʽ����
    CS_ERRTYPE_USER        = 0x02  ,  //��½ʧ���û�������
    CS_ERRTYPE_PWD         = 0x03  ,  //��½ʧ���������
    CS_ERRTYPE_NEEDLOGIN   = 0x04,//��½ʧ����Ҫ�û�����������֤
    CS_ERRTYPE_MORELOGIN   = 0x05  ,  //��½ʧ�ܲ����û�������
    CS_ERRTYPE_HAVELOGIN   = 0x06  ,  //��½ʧ�ܸ��û��Ѿ���½
    CS_ERRTYPE_OPERATE_CMD = 0x07  ,  //�����������
    CS_ERRTYPE_FRAME_LEN   = 0x08  ,  //����֡���ȴ���
    CS_ERRTYPE_CMD_TYPE    = 0x09  ,  //����ֵ����
    CS_ERRTYPE_NO_NODE     = 0x0A  ,  //�޴˽ڵ���Ϣ
    CS_ERRTYPR_SEND_TSC    = 0x0B  ,  //���͸��źŻ�ʱ�����쳣
    CS_ERRTYPE_SYN_WRITE   = 0x0C//ͬʱ���ڶ���û��������Ժ��ط�

        //to be continue
}ErrorType;



typedef enum
{
    //�źŻ��������� 0x10-0x2f
            CS_CMDTYPE_TSC_PARA_READ                  = 0x10,   //TSC������
            CS_CMDTYPE_TSC_PARA_READ_RESPONSE         = 0x11,   //TSC����������ֵ
            CS_CMDTYPE_TSC_PARA_WRITE                 = 0x12,   //TSC����д
            CS_CMDTYPE_TSC_PARA_WRITE_RESPONSE        = 0x13,   //TSC����д����ֵ
            CS_CMDTYPE_TSC_AUTOREPORT_TAILOR          = 0x14,   //TSC�����ϱ�����  ����ȡ��
            CS_CMDTYPE_TSC_AUTOREPORT_TAILOR_RESPONSE = 0x15,   //TSC�����ϱ����Ʒ���ֵ
            CS_CMDTYPE_TSC_AUTOREPORT		      = 0x16,   //TSC�����ϱ�
            CS_CMDTYPE_TSC_CONTROL_COMMAND            = 0x17,	//TSC��������
            CS_CMDTYPE_TSC_CONTROL_COMMAND_RESPONSE   = 0x18,	//TSC���������ֵ
            CS_CMDTYPE_TSC_STATUS_REQUEST             = 0x19,	//TSC״̬��ѯ
            CS_CMDTYPE_TSC_STATUS_RESPONSE            = 0x1A,	//TSC����״ֵ̬

            //�ڵ��������0X30-0X37
            CS_CMDTYPE_NODE_REQUEST     = 0x30, //�ڵ��������
            CS_CMDTYPE_NODE_RESPONSE    = 0x31, //�ڵ��������ֵ

            //Ⱥ��������0x38-0x3f
            CS_CMDTYPE_CLUSTER_REQUEST  = 0x38, //Ⱥ��������
            CS_CMDTYPE_CLUSTER_RESPONSE = 0x39, //Ⱥ��������ֵ

            //���������0x40-0x47
            CS_CMDTYPE_DOMAIN_REQUEST   = 0x40,	//���������
            CS_CMDTYPE_DOMAIN_RESPONSE	= 0x47,	//���������ֵ

            //VIP��������0x48-0x4f
            CS_CMDTYPE_VIP_REQUEST      = 0x48,	//VIP��������
            CS_CMDTYPE_VIP_RESPONSE		= 0x49,	//VIP��������ֵ

            //�û���������0x50-0x47
            CS_CMDTYPE_USR_REQUEST      = 0x50,	//�û���������
            CS_CMDTYPE_USR_RESPONSE	    = 0x51,	//�û����������ֵ

            //�������ݿ�������� 0x60-0x67 ��Ҫ���������ݿ�����
            CS_CMDTYPE_LOCAL_DATABASE_READ           = 0x60, //���������ݿ�
            CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE  = 0x61, //���������ݿⷵ��ֵ
            CS_CMDTYPE_LOCAL_DATABASE_WRITE          = 0x62, //д�������ݿ�
            CS_CMDTYPE_LOCAL_DATABASE_WRITE_RESPONSE = 0x63, //д�������ݿⷵ��ֵ

            //���ݿ������������0x68-0x6f ��Ҫ�����־
            CS_CMDTYPE_TABLE_CLEAR         = 0x68,   //�������
            CS_CMDTYPE_TABLE_CLEAR_RESPONS = 0x69,   //�����������

            //����0x70-
            CS_CMDTYPE_UPDATE_NOTICE = 0x70  //���ݿ����
}CommandType;





#endif // DCOMMON_H
