#ifndef WVIPDLG_H
#define WVIPDLG_H

#include <QWidget>
#include "DTable.h"
//#include "paintwidget.h"
#include "Vip.h"
#include "wstage.h"
#include "pdataprocess.h"
#include <QDateTime>

/*
 vip����
*/
namespace Ui {
    class WVipDlg;
}

class WVipDlg : public QWidget
{
    Q_OBJECT

public:
    explicit WVipDlg(QWidget *parent = 0);
    ~WVipDlg();
    void setDataProcess(PDataProcess*p);

    void getVipDataPoint();
    void setVipInterfaceData();//������ʾ����
    void getVipInterfaceData();//�������� �浽 �ڴ�
//    void setGreenChannel();

//    void addStage();//������н׶ε�ͼ��
//    void clearStageGroup();
    void showCurVip();//Ϊ�˵�һ����ʾ����ʱ �ڵ�����������ʾ

public slots:
    void on_cbVipIdChange(int index);
    void on_cbVipEnableChange(int index);
    void on_cbVipEnable2(bool b);

    void on_cbVipDirChange(int index);
    void on_cbDirChange(bool);

    void on_cbVipCtrlChange(int index);
    void on_cbManual(bool b);

    void on_edVipStartChange(QDateTime);
    void on_edVipEndChange(QDateTime);
    void on_startBtn();
    void on_addVipBtn();
    void on_readVipBtn();
    void on_delVipBtn();
    void on_appVipBtn();

    void on_vipNodeListChange();//
    void on_vipItemChange(quint32,bool);
    void on_mouseSelectNode(VipNode*);

//    void on_preBtn();
//    void on_nextBtn();
    void on_readBtn();
    void on_appBtn();

    void on_sbStageChange(int);
    void on_sbTimeChange(int);


    //void setIconState(WPhaseStageWidget*,quint8);
    void on_iconSelect(quint8 index);
    void on_cbVipStateCheck(bool);
    void on_rcvVipNodeState(quint32 id=0,bool bManual=false,quint8 stageId=0,bool bVipShow=true);
    void on_treeViewClickVipId(QString str);

    void on_vipIdModelChange();

private:
    Ui::WVipDlg *ui;
    VipProperty_Table *m_pVip;
    //WPhaseStageWidget* m_pStage;
    WStage *m_pStage;
    VipNodeContent* m_pContent;
    PDataProcess *m_pDataProcess;
    quint8 m_ucStageIndex;//�ڼ��׶� 1��
    VipNode *m_pCurVipNode;
    SVipData* m_pVipData;
    bool m_bFlagStartBtn;
    QList<bool> m_bListFlagManual;//�������е�vip·�� �ֶ���ť״̬ ����

//    QList<WPhaseStageWidget*> m_ListStage;
    QString m_strCurVip;
    bool m_bStartCheckState;

    bool m_bDlgInit;
};

#endif // WVIPDLG_H
