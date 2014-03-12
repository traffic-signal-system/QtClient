//author: sun
//date:2011.09.29

#ifndef DCOMMON_H
#define DCOMMON_H

#define SINGLEMODE  //单机版

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
#define TRAFFICUNIT 20 //每个 间隔时间的长度
#define TRAFFICX 500 //
#define TRAFFICWIDTH 680
#define TRAFFICHEIGHT 250
#define TRAFFICDISY 15//图形坐上角 离 0点y值
#define TRAFFICDISX 30
#define UNITPAGECNT 9

#define TIMEOUT5000 8000//超时时间
#define TIMEOUT100 50//超时时间
#define TIMEOUT600 600//单击鼠标
#define MAXNAMELEN 32//名字 最大长度
#define LBFOURTH 3//连接服务端状态
#define LBSECOND 1//初始化 当前页面 操作信息
#define LBTHIRD 2//当前群 节点状态
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

#define SPECIAL_TIMEBASE_INDEX   0   //用于时基表存储位置0~19特殊日时基表 0522edit
#define SUM_TIMEBASE_INDEX     20    //20~29夏日制时基表
#define WIN_TIMEBASE_INDEX     30    //30~39冬日制时基表

#define MAX_TIMEPATTERN_NUM    16
#define MAX_CONFLICT_NUM       16
#define MAX_CHANNEL_NUM        16
#define MAX_CHANNELNUM_BOARD   4
#define MAX_OVERLAP_NUM        8
#define MAX_DETECTOR_NUM       48
#define MAX_DETECTORSTATUS_NUM 8
#define MAX_PATTERN_NUM        32
#define MAX_STAGE_NUM          16//二维
#define MAX_STAGE_PATTERN_NUM  16//一维阶段
#define MAX_SCHEDULE_NUM       16
#define MAX_SCHEDULE_EVENT_NUM 48
#define MAX_PLAN_NUM           40
#define MAX_LANE_TYPE_NUM       4
#define MAX_LANES_NUM_DIRECTION 8
#define MAX_PHASE_COLOR_NUM     4   // include NULL color
#define MAX_DIRECTION_NUM       4
#define MAX_NAME_LEN           32
#define MAX_PHASEMAP_NUM       16//16个方向不能增加,二次过街另加 不能变 将影响 解析getListIconIndex
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

//共同数据（与服务端相同）：
/*
*系统参数表
*/
typedef enum
{
        TSC_MAX_MODULE       = 0x82,  //公共模块表最大行数  16
        TSC_MAX_TIMEBASE     = 0x89,  //时基调度表最大行数  40
        TSC_MAX_SCHEDULE_ONE = 0x8A,  //时段表最大行数      16
        TSC_MAX_SCHEDULE_TWO = 0x8B,  //时段表的最大时段数  48
        TSC_MAX_EVENTTYPE    = 0x8F,  //事件类型表最大行数   255
        TSC_MAX_EVENTLOG     = 0x90,  //事件日志表的最大行数 255
        TSC_MAX_PHASE        = 0x93,  //相位表最大行数       16
        TSC_MAX_PHASESTS     = 0X94,  //相位状态组最大数量    2
        TSC_MAX_DETECTOR     = 0x98,  //车辆检测器最大数量    48
        TSC_MAX_DETECTORSTS  = 0x99,  //检测器状态组的最大数量 6
        TSC_MAX_CHANNEL      = 0xAE,  //信号机支持的最大通道数量 16
        TSC_MAX_CHANNELSTS   = 0xAF,  //通道状态组数              2
        TSC_MAX_TIMEPATTERN      = 0xB2,  //配时方案数            32
        TSC_MAX_SCHEDULETIME_ONE = 0xB3,  //最大阶段配时表数      16
        TSC_MAX_SCHEDULETIME_TWO = 0xB4,  //最大阶段数            16
        TSC_MAX_OVERLAPPHASE     = 0xC6,  //跟随相位表最大行数     8
        TSC_MAX_OVERLAPPHASESTS  = 0xC7  //跟随相位状态表最大行数 1
} TscConfig;

typedef enum
{
    TSC_TABLE_MODULE        = 0x85,  //模块表
    TSC_TABLE_TIMEBASE      = 0x8D,  //时基表
    TSC_TABLE_SCHEDULE      = 0x8E,  //时段表
    TSC_TABLE_EVENTTYPE     = 0x91,  //事件类型表
    TSC_TABLE_EVENTLOG      = 0x92,  //事件日志表
    TSC_TABLE_PHASE         = 0x95,  //相位表
    TSC_TABLE_PHASECONFLICT = 0x97,  //相位冲突表
    TSC_TABLE_DETECTOR      = 0x9F,  //检测器表
    TSC_TABLE_START_FLASH   = 0xA3 ,  //启动时的闪光控制时间
    TSC_TABLE_START_ALLRED  = 0xA4,  //启动时的全红控制时间
    TSC_TABLE_CHANNEL       = 0xB0,  //通道表
    TSC_TABLE_TIMEPATTERN   = 0xC0,  //配时方案表
    TSC_TABLE_STAGETIME     = 0xC1,  //阶段配时表
    TSC_TABLE_OVERLAP       = 0xC8,   //跟随相位表
    TBL_TABLE_PHASE2DIREC   = 0xfa
} TscTableType;


typedef enum
{
    TSC_COMMAND_CURTSC_CTRL          = 0xA5, //当前的信号机控制状态
    TSC_COMMAND_SWITCH_MANUALCONTROL = 0xB5, //手动控制方案
    TSC_COMMAND_SWITCH_SYSTEMCONTROL = 0xB6, //系统控制方案
    TSC_COMMAND_SWITCH_CONTROL       = 0xB7, //控制方式
    TSC_COMMAND_SWITCH_STAGE         = 0xBA, //阶段状态
    TSC_COMMAND_GOSTEP               = 0xBB, //步进指令

    TSC_COMMAND_UTC_TIME             = 0x86,  //公共时间
    TSC_COMMAND_LOCAL_TIME           = 0x88,  //本地时间
    TSC_COMMAND_REPORTSELF           = 0xf7   //主动上报命令定制
} TscCommandType;



typedef enum
{
    TSC_STATUS_CHANNEL               = 0xB1, //通道输出状态
    TSC_STATUS_OVERLAP               = 0xC9, //跟随相位状态
    TSC_STATUS_PHASE                 = 0x96, //相位输出状态
    TSC_STATUS_CURTSC_FLASHCTRL      = 0xA6, //当前的闪光控制模式
    TSC_STATUS_ACTIVESCHEDULE_NO     = 0x8c, //活动时段表的编号
    TSC_STATUS_ALARM2                = 0xA7, //信号机报警
    TSC_STATUS_ALARM1                = 0xA8, //信号机报警
    TSC_STATUS__ALARM_SUMMARY        = 0xA9, //信号机报警摘要
    TSC_STATUS_ACTIVEDETECTOR_NUM    = 0x9C, //活动检测器总数
    TSC_STATUS_DETECTORSTS           = 0xA0, //检测器状态
    TSC_STATUS_DETECTORDATA          = 0xA1, //交通检测数据
    TSC_STATUS_DETECTORWARN_TABLE    = 0xA2, //车辆检测器警告
    TSC_STATUS_CURPATTERN_SCHTIMES   =0xBF, //当前方案各阶段时长
    TSC_STATUS_CURPATTERN_GREENTIMES = 0xC0, //当前方案各关键相位绿灯时长
    TSC_STATUS_EXTEND                = 0xF8, //信号机扩展状态

    TSC_STATUS_UTC_TIME              = 0x86,  //公共时间
    TSC_STATUS_LOCAL_TIME            = 0x88,  //本地时间
} TscStatusType;



typedef enum
{
    NODE_ADD    = 0x10,   //新增节点
    NODE_DELETE = 0x11,   //删除节点
    NODE_UPDATE = 0x12,   //修改节点
    NODE_READ   = 0x13,   //节点读取
    NODE_WRITE  = 0x14    //节点写
}TscOperate;

typedef enum
{
    CLUSTER_ADD            = 0x20 ,  //新增群
    CLUSTER_DELETE         = 0x21 ,  //删除群
    CLUSTER_UPDATE         = 0x22 ,  //修改群
    CLUSTER_PROPERTY       = 0x23 ,  //群属性表
    CLUSTER_TIMEBASE       = 0x24 ,  //群时基表
    CLUSTER_SCHEDULE       = 0x25 ,  //群时段表
    CLUSTER_TIMEPATTERN    = 0x26///群方案表
   // CLUSTER_SET_TIME       = 0x26    //群校时
}ClusterOperate;


typedef enum
{
    DOMAIN_ADD    = 0x30,   //新增域
    DOMAIN_DELETE = 0x31,   //删除域
    DOMAIN_UPDATE = 0x32,   //修改域
    DOMAIN_READ   = 0x33,   //域读取
    DOMAIN_WRITE  = 0x34    //域写
}DomainOperate;

/*
*vip操作指令
*/
typedef enum
{
        VIP_START = 0x38 ,  //vip 启动
        VIP_STOP  = 0x39    //vip 结束
}VipOperate;

typedef enum
{
    USER_ADD    = 0x40,   //新增用户
    USER_DELETE = 0x41,   //删除用户
    USER_UPDATE = 0x42,   //修改用户
    USER_READ   = 0x43,   //用户列表读取
    USER_WRITE  = 0x44,   //用户列表写
    USER_IN     = 0x45,   //用户登陆
    USER_OUT    = 0x46    //用户退出
} UserOperate;


//typedef enum
//{
//    LOCAL_TABLE_DAILYSTATISTICS    = 0x50,  //车流量统计表
//    LOCAL_TABLE_DEVICE_OPERATE_LOG = 0x52,  //设备操作日志
//    LOCAL_TABLE_USER_OPERATE_LOG   = 0x53   //用户操作日志

//}DatabaseOperate;

/*
*本地数据库表名
*/
typedef enum
{
        LOCAL_TABLE_USERINFO           = 0x50,  //用户表
        LOCAL_TABLE_USER_OPERATE_LOG   = 0x51,  //用户操作日志
        LOCAL_TABLE_NODE               = 0x52,  //节点表
        LOCAL_TABLE_CLUSTER            = 0x53,  //群表
        LOCAL_TABLE_DOMAIN             = 0x54,  //域表
        LOCAL_TABLE_DEVICE_OPERATE_LOG = 0x55,  //设备操作日志
        LOCAL_TABLE_TRAFFICSTATISTICS  = 0x56,   //车流量统计表
        LOCAL_TABLE_CFG_PARA           = 0x57,   //软件参数配置表
        LOCAL_VIP                      = 0x58    //vip控制表
}DatabaseOperate;


typedef enum
{
    LOG_TYPE_TSC             = 0x60, //信号机内部日志
    LOG_TYPE_DAILYSTATISTICS = 0x61, //车流量统计表
    LOG_TYPE_DEVICE          = 0x62, //设备操作日志
    LOG_TYPE_USER            = 0x63  //用户操作日志
}LogType;


typedef enum
{
    DATA_TYPE_PARA = 0,  //参数
    DATA_TYPE_ERR  = 1   //错误类型
}DataType;


typedef enum
{
    CS_ERRTYPE_RIGHT       = 0x00  ,  //正确
    CS_ERRTYPE_PACK        = 0x01  ,  //数据包格式错误
    CS_ERRTYPE_USER        = 0x02  ,  //登陆失败用户名错误
    CS_ERRTYPE_PWD         = 0x03  ,  //登陆失败密码错误
    CS_ERRTYPE_NEEDLOGIN   = 0x04,//登陆失败需要用户名及密码验证
    CS_ERRTYPE_MORELOGIN   = 0x05  ,  //登陆失败并发用户数过多
    CS_ERRTYPE_HAVELOGIN   = 0x06  ,  //登陆失败该用户已经登陆
    CS_ERRTYPE_OPERATE_CMD = 0x07  ,  //操作命令错误
    CS_ERRTYPE_FRAME_LEN   = 0x08  ,  //数据帧长度错误
    CS_ERRTYPE_CMD_TYPE    = 0x09  ,  //命令值错误
    CS_ERRTYPE_NO_NODE     = 0x0A  ,  //无此节点信息
    CS_ERRTYPR_SEND_TSC    = 0x0B  ,  //发送给信号机时出现异常
    CS_ERRTYPE_SYN_WRITE   = 0x0C//同时存在多个用户操作，稍后重发

        //to be continue
}ErrorType;



typedef enum
{
    //信号机操作命令 0x10-0x2f
            CS_CMDTYPE_TSC_PARA_READ                  = 0x10,   //TSC参数读
            CS_CMDTYPE_TSC_PARA_READ_RESPONSE         = 0x11,   //TSC参数读返回值
            CS_CMDTYPE_TSC_PARA_WRITE                 = 0x12,   //TSC参数写
            CS_CMDTYPE_TSC_PARA_WRITE_RESPONSE        = 0x13,   //TSC参数写返回值
            CS_CMDTYPE_TSC_AUTOREPORT_TAILOR          = 0x14,   //TSC主动上报定制  开启取消
            CS_CMDTYPE_TSC_AUTOREPORT_TAILOR_RESPONSE = 0x15,   //TSC主动上报定制返回值
            CS_CMDTYPE_TSC_AUTOREPORT		      = 0x16,   //TSC主动上报
            CS_CMDTYPE_TSC_CONTROL_COMMAND            = 0x17,	//TSC控制命令
            CS_CMDTYPE_TSC_CONTROL_COMMAND_RESPONSE   = 0x18,	//TSC控制命令返回值
            CS_CMDTYPE_TSC_STATUS_REQUEST             = 0x19,	//TSC状态查询
            CS_CMDTYPE_TSC_STATUS_RESPONSE            = 0x1A,	//TSC返回状态值

            //节点操作命令0X30-0X37
            CS_CMDTYPE_NODE_REQUEST     = 0x30, //节点操作请求
            CS_CMDTYPE_NODE_RESPONSE    = 0x31, //节点操作返回值

            //群操作命令0x38-0x3f
            CS_CMDTYPE_CLUSTER_REQUEST  = 0x38, //群操作请求
            CS_CMDTYPE_CLUSTER_RESPONSE = 0x39, //群操作返回值

            //域操作命令0x40-0x47
            CS_CMDTYPE_DOMAIN_REQUEST   = 0x40,	//域操作请求
            CS_CMDTYPE_DOMAIN_RESPONSE	= 0x47,	//域操作返回值

            //VIP操作命令0x48-0x4f
            CS_CMDTYPE_VIP_REQUEST      = 0x48,	//VIP操作请求
            CS_CMDTYPE_VIP_RESPONSE		= 0x49,	//VIP操作返回值

            //用户操作命令0x50-0x47
            CS_CMDTYPE_USR_REQUEST      = 0x50,	//用户操作请求
            CS_CMDTYPE_USR_RESPONSE	    = 0x51,	//用户操作请求回值

            //本地数据库操作请求 0x60-0x67 主要处理本地数据库数据
            CS_CMDTYPE_LOCAL_DATABASE_READ           = 0x60, //读本地数据库
            CS_CMDTYPE_LOCAL_DATABASE_READ_RESPONSE  = 0x61, //读本地数据库返回值
            CS_CMDTYPE_LOCAL_DATABASE_WRITE          = 0x62, //写本地数据库
            CS_CMDTYPE_LOCAL_DATABASE_WRITE_RESPONSE = 0x63, //写本地数据库返回值

            //数据库数据清除处理0x68-0x6f 主要针对日志
            CS_CMDTYPE_TABLE_CLEAR         = 0x68,   //数据清除
            CS_CMDTYPE_TABLE_CLEAR_RESPONS = 0x69,   //数据清除返回

            //其他0x70-
            CS_CMDTYPE_UPDATE_NOTICE = 0x70  //数据库更新
}CommandType;





#endif // DCOMMON_H
