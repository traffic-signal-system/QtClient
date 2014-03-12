#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QLCDNumber>
//#include <QPushButton>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
/*
用于 路口显示界面、阶段图标
*/
class PDataProcess;
class WPhaseStageWidget : public QWidget
{
    Q_OBJECT
public:
    //实时显示 参数1：父窗口；参数2：绿色通道；参数3：黄色通道；参数4：红色通道；参数5：闪动通道；参数6：界面宽度；参数7：LCD开关；参数8：阶段已运行时间；参数9：模拟开关；参数10：绿闪时间；参数11：绿灯时间；参数12：黄灯时间；参数13：红灯时间
    explicit WPhaseStageWidget(QWidget *parent,quint16 green,quint16 yellow,quint16 red,quint16 flash=0,quint16 width=400,bool bLcd=false,quint8 time=0,bool simulate=false,quint8 timegreenflash=3,quint8 timegreen=12,quint8 timeyellow=3,quint8 timered=3);

    //用于 阶段显示 显示绿通道 参数1：绿色通道；参数2：界面宽度
    WPhaseStageWidget(PDataProcess *p,quint16 green,quint16 width=150,QWidget *parent=0);

    //模拟运行 参数1：允许相位；参数2：阶段绿灯；参数3:阶段黄灯；参数4：阶段红灯；参数5：界面宽度；参数6：绿闪时间
    WPhaseStageWidget(QList<quint16> listgreen,QList<quint8> timelistgreen,QList<quint8> timelistyellow,QList<quint8> timelistred,quint16 width=400,quint8 timegreenflash=3,QWidget *parent=0);

    ~WPhaseStageWidget();

    void clearData();
    void clearListData();//清理相位 时间

    void loadImage();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    void killFlashTimer();


    void setData(quint16 green=0,quint16 yellow=0,quint16 red=0,quint16 flash=0,quint8 time=0,quint8 timegreenflash=2,quint8 timegreen=5,quint8 timeyellow=2,quint8 timered=2);
    void setLcdNumDisplay();

    //模拟显示
    void setListData(QList<quint16> listgreen,QList<quint8> timelistgreen,QList<quint8> timelistyellow,QList<quint8> timelistred);
    void editListData(bool badd,bool breplace,bool bdel,quint8 index,quint16 greenchannel=0x0000,quint8 timegreen=13,quint8 timeyellow=3,quint8 timered=3,quint8 option=0);

    void changeDataToInterface(quint16& bits);//将 外部数据顺序 转换为 界面顺序 外部
    void changeInterfaceToData(quint16& bits);
    void setSimulate(bool b);

    void setTimePeriod();//计算配时周期

    //用于 配时 显示 阶段
    void setClickable(bool=true);//设置 选取 路标 开关 选择相位
    quint16 getGreenChannel();//读取界面 绿色通道
    void setGreenChannel(quint16 green);//设置界面 绿色通道数据  用于图标
    void setClicked(bool b=true);//设置 图标可以被选中，可触发消息
    //返回当前阶段的 绿灯时间 黄灯时间 红灯时间
    quint16 getPhase(quint8 index);
    quint8 getTimeGreen(quint8 index=0xff);//返回当前阶段数据
    quint8 getTimeYellow(quint8 index=0xff);
    quint8 getTimeRed(quint8 index=0xff);
    quint8 getOption(quint8 index=0xff);



    void setCurIndex(quint8 index);
    quint8 getCurIndex();
    quint8 getStageCount();

    void setIconDark(bool b=false);
    void setIconWidth(quint16 width);
    bool getBeClicked();//返回 是否被选中标志 m_bClicked;

    void emitBeClicked();

    void setDataProcess(PDataProcess *p);
    void setListPoint(QList<quint8> *listChannel=NULL,QList<quint8>*listCom=NULL,QList<quint8>*listOver=NULL);
    void setRealShowFlag(bool b=false/*,bool blcd=true*/);//阶段配时 大界面显示时用到

signals:
    void beClicked(WPhaseStageWidget*,quint8);//index 从1起,为阶段号

public slots:

private:



    bool m_bRed;//阶段红灯  用于lcd红色
    bool m_bGreen;//阶段绿灯
    bool m_bYellow;//有黄灯 用于lcd黄色
    bool m_bFlashGreen;

    bool m_bTimeEvent;
    bool m_bTimerStart;
    bool m_bLcdNum;
    bool m_bFlash;
    bool m_bSimulate;//阶段模拟
    bool m_bClickable;//相位配置
    bool m_bClick;//可选中图标
    bool m_bClicked;//被选中为true
    bool m_bIcon;//阶段图标显示

    bool m_bNumColor;//闪烁时 数字闪烁
    QLCDNumber *m_LcdNumber;


    QList<bool> m_bListGreen;
    QList<bool> m_bListYellow;
    QList<bool> m_bListRed;
    QList<bool> m_bListFlash;
    QList<bool> m_bListFlashChange;
    QList<QPixmap> m_imgList;
    //QList<QImage*> m_imgListGreen;



    quint8 m_ucTime;//阶段已过秒数
    quint16 m_usTimePass;//周期已过秒数

    quint8 m_ucTimeGreenFlash;
    quint8 m_ucTimeGreen;
    quint8 m_ucTimeYellow;
    quint8 m_ucTimeRed;
    quint16 m_usTimePeriod;

//    quint16 m_uiAngleGreen;
//    quint16 m_uiAngleYellow;
//    quint16 m_uiAngleRed;

    quint16 m_usWidth;
    quint16 m_usHeight;
    qreal m_fScale;
    //QTimer *timer1;
    QList<quint16> m_ListPhaseStage;
    QList<bool> m_bListPhaseChange;//检查是否需要 过度状态

    QList<quint8> m_ListTimeGreen;
    QList<quint8> m_ListTimeYellow;
    QList<quint8> m_ListTimeRed;
    QList<quint8> m_ListOption;
    quint8 m_ucStageNo;//阶段号
    quint8 m_ucStageCnt;

    quint32 m_uiTimerId;//计时器id

    PDataProcess *m_pDataProcess;
    bool m_bRealShow;//实时显示 时 只要对应通道
    QList<quint8> *m_pListChannelMap;
    QList<quint8> *m_pListComMap;
    QList<quint8> *m_pListOverlapMap;

    quint32 m_uiNum;

};

#endif // PAINTWIDGET_H
