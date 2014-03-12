#ifndef WSTATUS_H
#define WSTATUS_H
//#include "paintwidget.h"
#include "wstage.h"
#include <QWidget>


/*
 ʵʱ��ʾ����
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

//    void addStage();//��� ��ʱ�׶�ͼ��
//    void setIconDark(quint8 stageId);

signals:

public slots:
    void on_checkBtn();
    void on_ctrlTypeChange();
    void on_lightModeChange();
    void on_cbPhaseChange(int index);
    void on_nextStepBtn();
    void on_nextStageBtn();
    void on_cbFlashStatus(bool);//��ʼ״̬����ѡ��
    void on_rcvAutoReport(unsigned char*para1,int len,quint32 id);
    void on_rcvManualCtrl(bool b);
    void on_rcvTscStatus(unsigned char*para1,int len);//�źŻ�״ֵ̬
    void on_rcvTscTime(quint32 t);
    void on_selectStageIndex(quint8 index);
    void on_nodeChange();
    void on_cbService(bool);//��ѡ Ϊ�ñ���ʱ�䣬�����÷�����ʱ��
private:
    Ui::Status *ui;
    WStage *m_pStatus;//��ʾ�׶�
//    WPhaseStageWidget *m_pStatus;
//    QList<WPhaseStageWidget*> m_ListStage;

    bool m_bBeginCheck;//����Уʱ��ť
    //bool m_bSendCheck;//����Уʱ��ť
    quint8 m_ucStageTimeId;//�׶���ʱ��
    PDataProcess *m_pDataProcess;
    quint8 m_ucStageNum;//�ܽ׶���
    quint8 m_ucCurStage;//��ǰ�׶κų�ʼֵΪ0
    quint8 m_ucTime;//�׶���ʱ��
    quint8 m_ucTimePassed;//�׶�������ʱ��
    quint32 m_uiCurNodeId;//��ǰ�ڵ�id
    quint8 m_ucTimeStage;//��ǰ��ʱ��
    bool m_bChange;//�Ƿ���Ҫ���ؽ׶�ͼ�� ��־λ

    bool m_bManual;//�ֶ�����

    qint32 m_iTimeOffset;//����ʱ��-�źŻ�ʱ��
    bool m_bRcvTscTime;
    bool m_bFirst;//����״̬ת��
//    bool m_bDefault;//���� �ֶ����� ��׼ʱ true������Ϊfalse����Ϊtrueʱ������Ӧ �Զ��ϱ� �����ͣ�

};

#endif // WSTATUS_H
