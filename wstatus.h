#ifndef WSTATUS_H
#define WSTATUS_H
//#include "paintwidget.h"
#include "wstage.h"
#include <QWidget>


/*
 实时显示界面
*/
namespace Ui{
    class Status;
}

class PDataProcess;

class WStatus : public QWidget
{
    Q_OBJECT
public:
    explicit WStatus(QWidget *parent = 0);
    ~WStatus();
    void setDataProcess(PDataProcess *p);
    quint32 makeNum(quint8 a,quint8 b,quint8 c,quint8 d);
    void changeNode();
    QStringList getComPhaseList(QList<quint8>&list);

//    void addStage();//添加 配时阶段图标
//    void setIconDark(quint8 stageId);

signals:

public slots:
    void on_checkBtn();
    void on_ctrlTypeChange();
    void on_lightModeChange();
    void on_cbPhaseChange(int index);
    void on_nextStepBtn();
    void on_nextStageBtn();
    void on_cbFlashStatus(bool);//初始状态不能选上
    void on_rcvAutoReport(unsigned char*para1,int len,quint32 id);
    void on_rcvManualCtrl(bool b);
    void on_rcvTscStatus(unsigned char*para1,int len);//信号机状态值
    void on_rcvTscTime(quint32 t);
    void on_selectStageIndex(quint8 index);
    void on_nodeChange();
    void on_cbService(bool);//勾选 为用本地时间，否则用服务器时间
private:
    Ui::Status *ui;
    WStage *m_pStatus;//显示阶段
//    WPhaseStageWidget *m_pStatus;
//    QList<WPhaseStageWidget*> m_ListStage;

    bool m_bBeginCheck;//用于校时按钮
    //bool m_bSendCheck;//用于校时按钮
    quint8 m_ucStageTimeId;//阶段配时号
    PDataProcess *m_pDataProcess;
    quint8 m_ucStageNum;//总阶段数
    quint8 m_ucCurStage;//当前阶段号初始值为0
    quint8 m_ucTime;//阶段总时间
    quint8 m_ucTimePassed;//阶段已运行时间
    quint32 m_uiCurNodeId;//当前节点id
    quint8 m_ucTimeStage;//当前配时号
    bool m_bChange;//是否需要重载阶段图标 标志位

    bool m_bManual;//手动控制

    qint32 m_iTimeOffset;//电脑时间-信号机时间
    bool m_bRcvTscTime;
    bool m_bFirst;//用于状态转换
//    bool m_bDefault;//用于 手动控制 标准时 true（其它为false），为true时，不响应 自动上报 的类型；

};

#endif // WSTATUS_H
