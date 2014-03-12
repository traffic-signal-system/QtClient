#ifndef PHASE_H
#define PHASE_H

#include <QLabel>
#include <QHBoxLayout>
#define MAXCOMPHASE 32
#define OVERLAPPHASENUM 8
#define ICONWIDTH 500
class WordIcon : public QLabel
{
    Q_OBJECT
public:
    explicit WordIcon(quint8 id,bool bUsed = false,bool bContent=false,bool bValid=true,QWidget *parent = 0);
    ~WordIcon();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    bool getFlagUsed();//用于方向映射若为true 不响应拖拽
    void setFlagUsed(bool b=true);
    bool getFlagOverlapContent();//用于是否new
    quint8 getId();
    void setFlagDirContent(bool b=true);
    bool getFlagDirContent();
    void setFlagClick(bool b);
    bool getFlagClick();
    void setFlagAmend(bool b);

signals:
    void mouseClick(quint8 id,bool bClick);
    void leaveContent(WordIcon*);

public slots:
    void on_setOverlapFlagValid(bool b=true);//跟随相位 有包含相位 为true
private:
    quint8 m_ucPhaseId;//1-32普通相位 33-40跟随相位
    bool m_bUsed;//是否已经映射方向 true已经映射
    bool m_bValid;//跟随相位 是否有包含相位 true才可拖拽  跟随相位先用false
    bool m_bContent;//true 在包含相位容器里，默认false
    bool m_bDirContent;//方向映射容器 默认false；
    bool m_bMouseIn;//默认false;
    bool m_bDrag;//true 拖拽行为
    bool m_bOverlap;//true 跟随
    bool m_bAmend;//修正

    QPoint m_posStart;//用与 误操作 拖拽
    bool m_bClick;

};

//-----------------------通道图标----------------------------------
/*
 相位类型：ctrlType:
*/
class ChlIcon : public QLabel
{
    Q_OBJECT
public:
    explicit ChlIcon(quint8 id,bool bUsed = false,QWidget *parent = 0);
    ~ChlIcon();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void setFlagUsed(bool b=true);
    quint8 getId();
    quint8 getPhaseId();
    void setChlPhaseId(quint8);
    void setFlagClick(bool b);
signals:
    void mouseClick(quint8 chlId,bool bClick,quint8 phaseId);
    void leaveContent(ChlIcon*);

public slots:

private:
    quint8 m_ucChlId;//1-24
    quint8 m_ucPhaseId;
    bool m_bUsed;//true 已经用于相位 不画图
    bool m_bMouseIn;//默认false;
    bool m_bDrag;//true 拖拽行为
    QPixmap m_pix;//通道图片
    QPoint m_posStart;//用于 误操作 拖拽
    bool m_bClick;//单击

};

//------------------------通道或包含相位 容器---1-OVERLAPPHASNUM 跟随容器--------OVERLAPPHASNUM+1 - ... 修正容器--------------------
class IconContent:public QWidget
{
    Q_OBJECT
public:
    explicit IconContent(bool bType = true,quint8 id=0,QWidget*parent=0);
    ~IconContent();
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void paintEvent(QPaintEvent *);
    bool checkId(quint8 id);//检查包含相位 是否已经包含 true未包含，false已包含
    bool checkIcon(WordIcon*);
    bool checkIcon(ChlIcon*);
    void addComPhase(WordIcon*);
    void addComPhase(quint8 id);
    void addChl(ChlIcon*);
    void setFlagClick(quint8 phaseId,bool b=false);
    quint8 getContentId();
    void clearContent();//清理list
    QList<quint8>&getListData();
//    bool getFlagAmend();
signals:
    void setOverlapValid(bool b);//跟随相位有包含相位 有效 无效
    void mouseClickPhase(quint8 contId,bool bClick,quint8 phaseId);
public slots:
    void on_chlLeaveContent(ChlIcon*);
    void on_phaseLeaveContent(WordIcon*);
    void on_mouseClickPhase(quint8 phaseId,bool bClick);
private:
    bool m_bType;//true 通道; false 包含相位 修正相位
    bool m_bValid;//跟随相位有效性 初始为false
    quint8 m_ucContentId;//1-2*OVERLAPPHASENUM
    QList<quint8> m_ListId;//相位id 或 通道id
    QHBoxLayout *m_hLayout;
    bool m_bAmend;
};

//--------------------方向容器--------------------------------------
/*
 m_ucLoadNo:路标方向 1-16 北向左 北直行 北向右 北人行 东 南 西
001 00 000 方向001-100 北 东 南 西 ( 东北 东南 西南 西北)；
类型00 机动车 01人行；
路标0右0直0左（000一次人行001; 010二次人行）


------------------0730确定------------------------------
  bit0-bit2:表示路标
(机动)
bit0:左 1：为选上，可组合
bit1:直 1：为选上，可组合
bit2:右 1：为选上，可组合
(人行)
000:一次人行 001:二次人行的N01 010:二次人行的N02

bit3-bit4：相位属性 00:机动车 01:人行

bit5-bit7：方向
001:北010:东011:南100:西
 101:东北 110:东南 111:西南 000:西北
*/
class LoadIcon : public QLabel
{
    Q_OBJECT
public:
    explicit LoadIcon(/*QPixmap pix,*/quint8 loadNo = 0,QWidget *parent = 0);
    ~LoadIcon();
    void loadImage();
    void analyseDir();//解析方向号

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);

    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void addPhaseIcon(quint8 id);
    void addPhaseIcon(WordIcon*);

    bool getFlagPed();
    void setFlagValid(bool b=true);
    bool getFlagValid();

    void clearPhaseIcon();
    void setFlagClick(quint8 phaseId,bool b=false);//用于相位
    void setFlagClick(bool bClick);//用于路标

    quint8 getContentId();
    void setLoadNo(quint8 loadNo);
    quint8 getPhaseId();
    quint8 getLoadNum();
    void setLoadNum(quint8 num);

signals:
    void clearContent(quint8,bool b=false);//设置 原始相位的 used
    void mouseDoubleClick(quint8 loadNo);
    void mouseClickPhase(quint8 contId,bool bClick,quint8 phaseId);
    void mouseClickDir(quint8 contId,bool bClick);
public slots:
    void on_phaseLeaveContent(WordIcon*);
    void on_mouseClickPhase(quint8 phaseId,bool bClick);

private:
    quint8 m_ucLoadNo;
    quint8 m_ucNum;//道路数
    int m_iDirect;//0，1，2，3 北 东 南 西
    QImage m_img;//路标
    bool m_bPed;//人行相位
    bool m_bValid;//是否有效 默认false 用于是否显示 、取数据 有相位为true
    bool m_bClick;
    quint8 m_ucPhaseId;

    WordIcon* m_pIcon;
    QLayout *m_pLayout;
};
//-----------------------------------------------------
class phaseWidget:public QWidget
{
    Q_OBJECT
public:
    phaseWidget(quint16 width=100,QWidget*parent=0);
    ~phaseWidget();
    void paintEvent(QPaintEvent *);
    //void setFlagDirection(bool bNorth=true,bool bEast=true,bool bSouth=true,bool bWest=true);
    void setBack(quint8 dir=0);
    void setListAllowGreen(QList<bool> listGreen,QList<QPixmap>listPix,quint16 phase=0);
    void setIconWidth(quint16 w);
    void mouseReleaseEvent(QMouseEvent *);
    void setBackDark(bool b=true);
    quint16 getPhase();
signals:
    void mouseClick(phaseWidget*);
private:
//    QImage m_img;
    QList<bool> m_bListGreen;
    QList<QPixmap> m_ListPix;
    qreal m_rScale;
//    bool m_bClickAble;

    quint16 m_sAllowPhase;
    bool m_bNorth;//true 有路口
    bool m_bEast;
    bool m_bSouth;
    bool m_bWest;
};

//----------------------------------------------
/*
 阶段时间调整 竖杠子类
*/
class DragIcon : public QLabel
{
    Q_OBJECT
public:
    explicit DragIcon(QPixmap pix,QString str,QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void setIconCursor(bool b);

signals:

public slots:

private:
    QPoint startPos;
    QString m_IconStr;

};

//----------------------------------------------------
/*
 阶段时间调整
*/
class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    //void setCursorPos(QPoint pos,QPoint offset,quint8 left,quint8 right);
    void dropEvent(QDropEvent *);

    void paintEvent(QPaintEvent *);

    void setBarPos();//调整 位置

    void setTimeValue(quint8 green=13,quint8 yellow=3,quint8 red=3);
    void setStageTime(quint8 stagetime);//
    void setEditable(bool b=false);

    quint8 getTimeGreen();
    quint8 getTimeYellow();
    quint8 getTimeRed();
signals:
    void colorTimeChange(quint8,quint8,quint8);
public slots:

private:
    quint8 m_ucGreen;//绿色x坐标
    quint8 m_ucYellow;//黄色x坐标
    //quint8 m_ucRed;

    qint16 m_TimeGreen;
    qint16 m_TimeYellow;
    qint16 m_TimeRed;

    DragIcon *m_IconY;
    DragIcon *m_IconR;
    //bool m_bLeftButton;

};

#endif // PHASE_H
