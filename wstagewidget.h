#ifndef WSTAGEWIDGET_H
#define WSTAGEWIDGET_H

#include <QWidget>
#include "wstage.h"
#include "phase.h"
#include "pdataprocess.h"

namespace Ui {
    class WStageWidget;
}

class WStageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WStageWidget(QWidget *parent = 0);
    ~WStageWidget();
    void init();
    void setDataProcess(PDataProcess*p);
    void showPatternData();
    void clearPatternData();
    void showStageData();
    void clearStageData();
    void setFlagPattern(bool b);//�Ƿ���ʾ������

public slots:
    void on_patternBtnMore();
    void on_patternSbNoChange(int);
    void on_patternSbCircleChange(int);
    void on_patternSbStageNoChange(int);
    void on_patternSbOffsetChange(int);
    void on_patternSbCoordinateChange(int);
    void on_patternBtnDel();
    void on_patternBtnApp();
    void on_patternBtnRead();

    void on_stageBtnMore();
    void on_stageSbNoChange(int);
    void on_stageSbTimeChange(int);
    void on_stageCbOptionChange(int);
    void on_stageColorChange(quint8 green,quint8 yellow,quint8 red);

    void on_stageIndexChange(quint8 index);
    void on_btnReadStage();
    void on_btnAppStage();
    void on_rcvPhase();//�յ��˴�����Ϣʱ����ͻ��λ �Ѿ����
    void on_rcvStageTimeTable();
    void on_rcvTimePatternTable();

private:
    Ui::WStageWidget *ui;
    WStage *m_pStage;
    ColorWidget *m_pCol;
    quint8 m_ucStageNoIndex;//��ʱ��
//    quint8 m_ucStageIdIndex;//�׶κ�
    TimePattern_Table *m_pPattern;
    StageTime_Table *m_pStageTime;//����ĳ�׶�
    PDataProcess *m_pDataProcess;
    bool m_bDlgInit;//��ɳ�ʼ��Ϊtrue
    bool m_bShowPattern;//�Ƿ���ʾ ������
};

#endif // WSTAGEWIDGET_H
