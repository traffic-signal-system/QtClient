#ifndef WSTAGE_H
#define WSTAGE_H

#include <QWidget>
#include "wdirectionform.h"

class StageTime_Table;
class Overlap_Table;
class PhaseConflict_Table;

namespace Ui {
    class WStage;
}

class WStage : public QWidget
{
    Q_OBJECT

public:
    explicit WStage(QWidget *parent = 0);
    ~WStage();
    void setStageIcons(QList<quint16> list);
    void setFlagInitStageIcon(bool b);
    void setUnClickAble();//�����λͼ�� ������ɫ
    void changeNode(QList<quint8> listLoadNo,QList<bool> listValid,QList<quint8> listPhaseId);
//    void setUnClickAble();//���ܵ������ͼ��ı�
    void setOverlapConnect(QList<quint8>);
    void setOverlapConnect(Overlap_Table*);
    void setStageBase(StageTime_Table*p);//������ʱ ָ��
    QList<quint16> getListAllowGreen();
    void setLedShow();
    void setChannelMap(QList<quint8>list);//ͨ����Ӧ��λ
    void setData(quint32 green,quint32 yellow,quint32 red,quint32 flash,int time);
    void setIconDark(quint8 index);//�׶�˳��
    void setMouseClick(quint8 index);
    void setFlagClickPhase(bool b=false);//ʵʱ����ʱ ���ͼ�� ���ı� ��ͼ ����λ����ͼ��λΪ �����ϱ�������
    void setBack(quint8 dir=0);//���ñ���ͼ
    void killFlash();
    void clearInterface();//��� ���� �׶��飬�׶ξ�����ʾ
    void changePosition();//�׶��� λ�� ����
    void setConflictBase(PhaseConflict_Table *p);

//    void setOverlapBase(Overlap_Table*p);

//    void setFlagClearStageGroup(bool b=false);

signals:
    void changeStageIndex(quint8 index);
    void btnReadStage();
    void btnAppStage();
public slots:
    void on_iconMouseClick(quint16);//�׶�ͼ��
    void on_widMouseClick(bool,quint8);//��ʱ����
    void on_btnAdd();
    void on_btnDel();
    void on_btnRead();
    void on_btnApp();
    void on_changeNode();//���Ľڵ�ʱ ����ͼƬ icon��Ч�� ������λ �������
private:
    Ui::WStage *ui;
    WDirectionForm *m_pWid;
    StageGroup* m_pGroup;
    StageTime_Table *m_pStageData;//ָ�����ĳ��ʱ�ĵ�һ�׶�ָ��
    quint8 m_ucIndex;//�׶�index 0��
    quint8 m_ucStageCnt;
    bool m_bInitStageIcon;//��ʼ����ʱ�׶�ʱ ����Ӧ ͼ����
    bool m_bClickPhase;//Ĭ��Ϊtrue ͼ����ʱ ���� ������λ��false������
    QList<quint8> m_ListLoadMap;//ͨ����Ӧ��λ
    PhaseConflict_Table *m_pConflictBase;
    Overlap_Table *m_pOverlapBase;

//    bool m_bClearStageGroup;//�����ڵ�ʱ �Ƿ���� Ĭ���� true���׶���ʱ���� ��Ϊ false��
};

#endif // WSTAGE_H
