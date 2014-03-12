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
    void setUnClickAble();//点击相位图标 不改颜色
    void changeNode(QList<quint8> listLoadNo,QList<bool> listValid,QList<quint8> listPhaseId);
//    void setUnClickAble();//不能点击方向图标改变
    void setOverlapConnect(QList<quint8>);
    void setOverlapConnect(Overlap_Table*);
    void setStageBase(StageTime_Table*p);//更改配时 指针
    QList<quint16> getListAllowGreen();
    void setLedShow();
    void setChannelMap(QList<quint8>list);//通道对应相位
    void setData(quint32 green,quint32 yellow,quint32 red,quint32 flash,int time);
    void setIconDark(quint8 index);//阶段顺序
    void setMouseClick(quint8 index);
    void setFlagClickPhase(bool b=false);//实时界面时 点击图标 不改变 大图 的相位（大图相位为 主动上报决定）
    void setBack(quint8 dir=0);//设置背景图
    void killFlash();
    void clearInterface();//清除 界面 阶段组，阶段具体显示
    void changePosition();//阶段组 位于 上面
    void setConflictBase(PhaseConflict_Table *p);

//    void setOverlapBase(Overlap_Table*p);

//    void setFlagClearStageGroup(bool b=false);

signals:
    void changeStageIndex(quint8 index);
    void btnReadStage();
    void btnAppStage();
public slots:
    void on_iconMouseClick(quint16);//阶段图标
    void on_widMouseClick(bool,quint8);//配时界面
    void on_btnAdd();
    void on_btnDel();
    void on_btnRead();
    void on_btnApp();
    void on_changeNode();//更改节点时 设置图片 icon有效性 设置相位 跟随关联
private:
    Ui::WStage *ui;
    WDirectionForm *m_pWid;
    StageGroup* m_pGroup;
    StageTime_Table *m_pStageData;//指向具体某配时的第一阶段指针
    quint8 m_ucIndex;//阶段index 0起；
    quint8 m_ucStageCnt;
    bool m_bInitStageIcon;//初始化配时阶段时 不响应 图标点击
    bool m_bClickPhase;//默认为true 图标点击时 传递 允许相位，false不传递
    QList<quint8> m_ListLoadMap;//通道对应相位
    PhaseConflict_Table *m_pConflictBase;
    Overlap_Table *m_pOverlapBase;

//    bool m_bClearStageGroup;//更换节点时 是否清除 默认是 true，阶段配时界面 设为 false；
};

#endif // WSTAGE_H
