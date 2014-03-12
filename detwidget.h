#ifndef DETWIDGET_H
#define DETWIDGET_H

#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QBoxLayout>
#include <QGridLayout>


#include <QWidget>
#include <QList>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include <QPixmap>
#include "pdataprocess.h"
/*
 检测器界面的子类 检测器 路标 参数框 单个检测器流量  流量容器
*/
class DetIcon : public QDialog
{
    Q_OBJECT
public:
    explicit DetIcon(QWidget *parent = 0);
    ~DetIcon();


    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void setDetectorNo(quint8 no);
    quint8 getDetectorNo();
    void setRadius(int r);
    void setDetStatus(bool b,quint8 detAlarm=0,quint8 coilAlarm=0);//检测器状态 有车 无车 异常
    void emitLeaveContent();
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void clearState();


signals:
    void leaveContent(DetIcon*);
    void mouseStatus(bool b,bool btype,quint8 index,QPoint p);//b true鼠标进入 btype true为检测器 index检测器号/车道号 p所处位置右上坐标
public slots:

private:

    quint8 m_ucDetNo;
    int m_iRadius;
    QPoint m_posStart;
    bool m_bGreen;//true 有车 绿色 false 无车 白色
    bool m_bRed;//true 异常 红色 false 正常 白或绿
    int m_iTimer;
    bool m_bIncludeMouse;
    bool m_bSend;
    bool m_bTimer;
    bool m_bDrag;//拖拽标志 true为拖拽 false为点击
    //QPoint m_Point;
};

//-----------------------------------------------

class DetContent : public QDialog
{
    Q_OBJECT
public:
    explicit DetContent(QWidget *parent = 0);
    ~DetContent();
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);

    void setDirNo(quint8 no);//设置 方向号 以取得 车道数
    quint8 getDirNo();
    void setData(quint8 dir=1,quint8 type=0,quint8 index=0,quint8 phase=0);//dir：方向 ；type：路标；index：车道顺序； phase：请求相位
    //void addIcon(DetIcon*i,QPoint p=QPoint(0,0));
    void addIcon(DetIcon*i,quint8 pos=0,bool b=true);//b 为false时 不需要触发消息 断开原容器
    //void mousePressEvent(QMouseEvent *);
    void setContentData();//设置 道路 检测器信息
    void setDetBase(PDataProcess *p);
    void changeListIcon(quint8 dir,quint8 pos,DetIcon*i,bool b=true);//b 为true 设置数据
    void setIconData(quint8 iconNo,quint8 index=0);//iconNo检测器号 index所处位置 0-3 为m_ListIcon存储位置
    void timerEvent(QTimerEvent *);
signals:
    void removeIcon(DetIcon*);
    void mouseStatus(bool b,bool btype,quint8 index,QPoint p);//b true鼠标进入 btype true为检测器 index检测器号/车道号 p所处位置右上坐标
    void detChangePos(int detNo);
public slots:
    void on_IconLeave(DetIcon*);
private:
    quint8 m_ucDirNo;
    quint8 m_ucPhase;//请求相位
    quint8 m_ucDirection;//1 北； 2 东；  3 南； 4 西；
    qint16 m_sDegree;//旋转的角度
    quint8 m_ucType;//路标类型 1左; 2直; 3右; 4人行; 0无（用于初始化时放 所有的 检测器）
    bool m_bPed;//true 人行；false 机动车
    quint8 m_ucLoadIndex;//车道顺序号 从右至左（逆时针） 0起
    //quint8 m_ucPosIndex;//远近顺序号 从近及远 0起；
    Detector_Table *m_pDetBase;

    //QPixmap *m_pPix;
    QImage m_img;
    bool m_bImg;

    QBoxLayout *m_pLayout;
    QGridLayout *m_pGLayout;

    QList<DetIcon*> m_ListIcon;//0-3存放检测器 由近及远

    bool m_bIncludeMouse;
    bool m_bSend;
    PDataProcess* m_pDataProcess;
//    QPoint m_posStart;

};

//---------------------------------------------------
class DetParaDlg : public QWidget
{
    Q_OBJECT
public:
    DetParaDlg(QWidget *parent = 0);
    ~DetParaDlg();
    void init();
    void setDataProcess(PDataProcess *p);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void closeEvent(QCloseEvent *);
    void setData(quint8 detNo=0,quint8 loadNo=0);
    void clearInterface();
    void showData(bool b);//true 显示 检测器 ；false 显示 车道
    void getDataFromInterfase();//
//    void mousePressEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);
//    QWidget *detWidget;
//    QWidget *typeWidget;
//    QWidget *optionWidget;
public slots:
    void on_confirmBtn();
    void on_cancelBtn();
    void on_cbDetNoChange(int index);
    void on_cbDirNoChange(int index);
    //void on_cbHightLight(int);
    void on_dataChange();
    void on_detChangePos(int detNo);
    void on_btnMore();


signals:
    void closeDlg();
    void mouseStatus(bool b);



private:
    QComboBox *cbDetNo;
    QComboBox *cbPhase;
    QGroupBox *gbAdvanced;
    QPushButton *btnMore;
    QList<QRadioButton*> listTypeRadio;
    QList<QCheckBox*> listTypeCheck;
    QComboBox *cbDir;
    QSpinBox *sbValidTime;
    QList<QCheckBox*> listOptionCheck;
    QLineEdit *leSaturation;
    QSpinBox *sbOccupancy;
    QComboBox *cbDirLoad;
    QSpinBox *sbLoadNum;

    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    QGroupBox *m_gbDet;
    QGroupBox *m_gbLoad;

    PDataProcess *m_pDataProcess;

    bool m_bClick;
    quint8 m_ucDirNo;
    quint8 m_ucDetNo;

    bool m_bInit;//数据初始化 cleraInterfase on_DetNoChange on_cbDirNoChange为开始前为false结束后为true
    bool m_bDataChange;//数据有更改为 true 在on_confirmBtn on_cbDetNoChange 时发送数据到lib
};

//-------------------------------------------

class FlowWidget;
class DetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetWidget(QWidget *dlgParent=0,QWidget *parent = 0);
    ~DetWidget();
    void init();
    void paintEvent(QPaintEvent *);
    void setDataProcess(PDataProcess *p);
    void mouseDoubleClickEvent(QMouseEvent *);
    void rankDetector();//排列检测器位置
    void mouseMoveEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    void setFlowList(QList<FlowWidget*>&list);

//    void enterEvent(QEvent *);
//    void leaveEvent(QEvent *);

signals:
    void stopDetStatus();

public slots:
    void on_rcvDetector();
    void on_removeIcon(DetIcon*);
    void on_rcvDetStatus(unsigned char*para1,int len);
    void on_rcvDetAlarm();
    void on_mouseStatus(bool b,bool btype,quint8 index,QPoint p);
    void on_dlgMouseStatus(bool b);
    void on_closeDetParaDlg();

private:
   QList<DetIcon*> m_ListIcon;//检测器数
   QList<DetContent*> m_ListLoad;//道路数
   QList<QLabel*> m_ListGroup;//用于区域块 北 东 南 西 路标，及 中间放 没用的检测器

   QList<quint8> *m_pListLoadNum;//四个方向 4种路标（左直右人行） 各 车道数 指向 PDataProcess
   QList<quint8> *m_pListPhase;//1-16方向对应的 相位值
   QList<bool> m_ListDetStatus;//检测器 是否 有车 true为有车
   QList<bool> m_ListDetAlarm;//检测器报警状态 true 为报警
   bool m_bDetAlarm;
   PDataProcess *m_pDataProcess;
   Detector_Table *m_pDetBase;

   bool m_bFlagShow;
   bool m_bAutoStatus;//用于 在结束程序时 是否需要 结束 主动上报
   bool m_bAutoAlarm;

   DetParaDlg *m_pDetPara;
   qint8 m_cMouseCnt;

   QList<FlowWidget*> m_pListFlow;
};

//-----------------------------------------------------------------------------------
class FlowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowWidget(QWidget *parent = 0);
    ~FlowWidget();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void setStatus(bool b);
    void setDetNo(quint8 detNo);
    quint8 getDetNo();
    void clearData();
    void timerEvent(QTimerEvent *);

signals:

public slots:
private:
    const QColor m_cstCol;
    quint8 m_ucDetNo;//检测器号
    QPixmap pix;
    QPixmap pixTemp;
    bool m_bStatusPre;//先前状态
    bool m_bStatus;//现在状态 true 有车 false 无车
    bool m_bLine;//初始化时 画底线
    bool m_bData;//是否是 检测器 设置 数据 以区别于 重画
    quint32 m_uiNum;//流量

    bool bClick;//try
    int m_iTimerId;
    bool bTimer;

};

#endif // DETWIDGET_H
