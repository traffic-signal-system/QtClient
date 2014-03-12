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
    void setFlagPattern(bool b);//是否显示方案表

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
    void on_rcvPhase();//收到此触发消息时，冲突相位 已经完成
    void on_rcvStageTimeTable();
    void on_rcvTimePatternTable();

private:
    Ui::WStageWidget *ui;
    WStage *m_pStage;
    ColorWidget *m_pCol;
    quint8 m_ucStageNoIndex;//配时号
//    quint8 m_ucStageIdIndex;//阶段号
    TimePattern_Table *m_pPattern;
    StageTime_Table *m_pStageTime;//具体某阶段
    PDataProcess *m_pDataProcess;
    bool m_bDlgInit;//完成初始化为true
    bool m_bShowPattern;//是否显示 方案表
};

#endif // WSTAGEWIDGET_H
