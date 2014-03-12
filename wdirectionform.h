#ifndef WDIRECTIONFORM_H
#define WDIRECTIONFORM_H

#include <QWidget>
#include <QGraphicsView>
#include <QLabel>
#define MAXCOMPHASE 32
#define DIRECTIONNUM 16
#define DIRECTIONTOTAL 20
#define DIRICONWIDTH 30
#define DIRICONHEIGHT 100
#include "pdataprocess.h"
//#include <QPainter>
//#include <QRectF>
#include "phase.h"
//---------------------------------------------------
class DirectionIcon : public QLabel
{
    Q_OBJECT
public:
    explicit DirectionIcon(quint8 id,QWidget *parent = 0);
    ~DirectionIcon();
    void init();//为新节点
    void initState();//为新的阶段
    void analyseId();
    void paintEvent(QPaintEvent *);
    void setPhaseId(quint8 phaseId);
    quint8 getPhaseId();
    void setFlagValid(bool b);
    void setFlagGreen(bool b);
    void setIconGreen(bool b);
    void setIconRed(bool b);
    void setFlagYellow(bool b);
    void setFlagRed(bool b);
    void setPixGreen(QPixmap&pix);
    void setPixYellow(QPixmap&pix);
    void setPixRed(QPixmap&pix);
    void setPixNull(QPixmap&pix);
    void setPixConflict(QPixmap&pix);
    void setFlash(bool b);
    void setFlagFlashMode(bool b);
    void timerEvent(QTimerEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
    quint32 getPhase();//考虑24相位
    void setFlagClickAble(bool b);
    void setFlagInclude(bool b);
    void setPedSmall(bool b);
    bool getFlagGreen();//为获取图标信息
    bool getFlagValid();//为图标的一次过街 大小
    bool getFlagClickAble();//图标是否可点击 可点击的 才需设置 冲突相位
    QPixmap getGreenPix();
    //-------冲突相位----------
    void setFlagConflict(bool b=true);
    void setFlagConflictGreen(bool b);
    void setConflictGreen(bool b);//用于界面check选择时 显示绿色图标

    void editConflict(bool);
//    void setConflictBase(PhaseConflict_Table*p);

signals:
    void includePhaseTurn(bool b);
    void mouseClick(bool b,quint8 phaseId);//改变允许相位时

    void leftClick(bool,quint8 phase);
    void rightClick(bool,quint8 phase);
public slots:
    void on_includePhaseTurn(bool b);
private:
    quint8 m_ucDirId;//1-20 固定图标，图片可变，位置及大小不变（除了人行）
    quint8 m_ucPhaseId;
    bool m_bValid;
    bool m_bGreen;
    bool m_bYellow;
    bool m_bRed;//若时冲突相位 也置为true
    bool m_bFlash;//true显示颜色
    bool m_bFlashMode;//true 前半秒空 false后半秒空
    bool m_bClick;
    bool m_bClickAble;
    QPixmap m_PixGreen;
    QPixmap m_PixYellow;
    QPixmap m_PixRed;
    QPixmap m_PixNull;
    QPixmap m_PixConflict;
    int m_iTimerId;
    bool m_bTimer;
    bool m_bInclude;//包含相位标志
    quint8 m_ucIncludeNum;//包含相位数量
    quint8 m_ucDir;//方向 0北，1东，2南，3西

    //-------冲突相位-------
    bool m_bConflict;//冲突相位界面标志 默认为 false
    bool m_bRightClick;//冲突相位右键选取 默认为false
    bool m_bConflictGreen;//选择了绿相位 才能选择红相位 默认false 才能得指针

    int m_iConflict;//在一个阶段内 是冲突相位 （绿时 加1） （NULL 时减1）
    //------------跟随相位 用于 跟随相位 无对应方向时，取 第一个 包含相位方向

    bool m_bClickAll;//总开关

};

//---------------------------------------------------
namespace Ui {
    class WDirectionForm;
}

class WDirectionForm : public QWidget
{
    Q_OBJECT

public:
    explicit WDirectionForm(QWidget *parent = 0,bool bConflict=false);
    ~WDirectionForm();
    void setLayoutDir();
    void setBack(quint8 dir=0);
    QImage getBackImage();
    void setDirIconValid(quint8 index,bool b);
    void loadPixmap();
    int getListIconIndex(quint8 dirId);
    int getListPixIndex(quint8 dirId);
    QList<bool> getListFlagGreen();
    QList<QPixmap> getListPixGreen();
    quint16 getPhase();//允许相位
    DirectionIcon* getIcon(quint8 phaseId);
//    void mouseReleaseEvent(QMouseEvent *);
//    void drawBackground(QPainter*painter,const QRectF&rect);
    void setLcdShow(bool b);
    void setLcdNum(int time);
    void setAllowPhase(quint16 phase);//0722添加冲突相位限制

    void clearState();//更改阶段
    void changeStage();//更改节点
    void setIconPixmap(QList<quint8>);//在更改节点时 可能需要 换 直行 图标
    void setFlagValid(QList<bool>);
    void setPhaseId(QList<quint8>);
    void setOverlapConnect(QList<quint8> listPhase);
    void setUnClickAble();
    void setFlagInitStageIcon(bool b);
    void killFlash();
//---------------冲突相位
    void setConflict(quint8 phase,quint16 conflict,bool b=true);//阶段配时 b有用 b为true时 conflictNum++，
    void setConflictBase(PhaseConflict_Table*p);
    void setConflictGreen(quint8 phaseId,bool b=true);
    //跟随相位
    void setOverlapBase(Overlap_Table *p);

signals:
    void mouseClick(bool b=true,quint8 phaseId=0);//传递相位
    void leftClick(bool,quint8);
    void rightClick(bool,quint8);
public slots:
//    void on_mouseClick(quint8 phase);
    void on_leftClick(bool,quint8);
    void on_rightClick(bool,quint8);

private:
    Ui::WDirectionForm *ui;
    QList<QLayout*> m_ListLayout;
    QList<DirectionIcon*> m_ListDirIcon;
    QList<QPixmap> m_ListPix;
    QImage m_img;
    bool m_bInitStageIcon;//由允许相位 获取 图标时 需emit mouseClick() 完成初始化为 true
    bool m_bConflict;
    PhaseConflict_Table *m_pConflictBase;

    Overlap_Table *m_pOverlapBase;
};

//-----------------------------------------------------------------------
class StageGroup : public QWidget
{
    Q_OBJECT

public:
    explicit StageGroup(QWidget *parent = 0);
    ~StageGroup();
    void addStage(phaseWidget*icon=NULL);
    void setListAllowGreen(QList<bool> listGreen,QList<QPixmap>listPix,quint16 phase=0);
    void clearGroup();
    void delIcon();
    void setBack(quint8 dir=0);
    void setIconWidth();
    void getStageIndex(quint8 &index,quint8 &cnt);//获取当前 阶段 的位置信息
    void setIconDark(quint8 index);
    void mouseClick(quint8 index);

signals:
    void mouseClick(quint16 phase);//传递 点击图标 传递 允许相位
   // void mouseClick(quint8 stageId);

public slots:
    void on_mouseClick(phaseWidget*);//点击图标

private:
//    QWidget *m_pForm;
    QHBoxLayout *m_pLayoutGroup;
    QList<phaseWidget*> m_pListIcon;
    phaseWidget *m_pIcon;
    quint8 m_ucDir;//dir: 0xff  8北 7东北 6东 5东南 4南 3西南 2西 1西北暂时只用4方向 错
    //bool m_bClickPhase;//默认为true 图标点击时 传递 允许相位，false传递 图标 阶段号
};
#endif // WDIRECTIONFORM_H
