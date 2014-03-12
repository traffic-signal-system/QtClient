#ifndef WPHASEWIDGET_H
#define WPHASEWIDGET_H

#include <QWidget>
#include "phase.h"
#include "pdataprocess.h"
#include <QTimer>

namespace Ui {
    class WPhaseWidget;
}

class WPhaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WPhaseWidget(QWidget *parent = 0);
    ~WPhaseWidget();
    void init();
    void createDirection();
    void createComPhase();
    void createOverlapPhase();
    void createChannel();
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
//    void timerEvent(QTimerEvent *);
    //---------dlgChl------------
    void dlgChlInit();
    void showChlDlg(bool b);
    void setChlDlg();//设置 相位类型 闪光模式 交替
//    void getChlDlg();//获取所有通道的 相位
    //------------dlgCom---------
    void dlgComInit();
    void showComDlg(bool b);
    void setComDlg();
//    void getComDlg();
    //--------------dlgOverlap--------
    void dlgOverlapInit();
    void showOverlapDlg(bool b);
    void setOverlapDlg();
//    void getOverlapDlg();
    //-------phase------------
    void clearPreClick();//去除上一次click
    void showPhaseDlg(quint8 id,bool b);
    //-------dir----------------
    void dlgDirInit();
    void showDirDlg(bool b);
    void setStraightLoadNo(quint8 loadNo);
    void setDirDlg();
  //  void getDirDlg();
    int getListIndex(quint8 loadNo);//由loadNo得到list index
    int getListIndexByCbIndex(int index);
    int getDirCbNoIndex(quint8 loadNo);
    void setDataProcess(PDataProcess*p);
    void clearInterface();//清理界面
    void layoutAddChl(ChlIcon*icon);
    void getInterfaceData();//获取界面数据
    void getChannelTableData();//获取所有通道相位 通道类型 只分 跟随 机动车两种  自动 取值（根据所属相位），界面改变无效
    void getPhaseMapTabel();
    void getOverlapTable();//包含相位 修正相位
    void editOverlapPhaseDirect(quint8 overPhaseId);//当 跟随相位 有通道 无方向时，方向取 第一个包含相位 的方向；
   // void setDirIconValid(quint8 index,bool b);
    void timerEvent(QTimerEvent *);
public slots:
    void on_loadClearPhase(quint8);
    //------dlgChl-------
    void on_chlBtnMore();
    void on_mouseClickChl(quint8 chlId,bool bClick,quint8 phaseId);
    void on_chlCbNoChange(int);
    void on_chlCbTypeChange(int);
    void on_chlCbLightChange(int);
    void on_chlCbModeChange(int);
    //------------phase----------
    void on_mouseClickPhase(quint8 phaseId,bool bClick);
    void on_mouseClickComContentPhase(quint8 contId,bool bClick,quint8 phaseId);//包含相位容器
    void on_mouseClickLoadContentPhase(quint8 contId,bool bClick,quint8 phaseId);//方向容器
    //----------comPhase---------
    void on_comBtnMore();
    void on_comCbIdChange(int);
    void on_comSbPedGreenChange(int);
    void on_comSbPedCleanChange(int);
    void on_comSbMinGreenChange(int);
    void on_comSbUnitDelayChange(int);
    void on_comSbMaxGreen1Change(int);
    void on_comSbFlashGreenChange(int);
    void on_comSbMaxGreen2Change(int);
    void on_comSbFixGreenChange(int);
    void on_comCbTypeChange(int);
    void on_comCbOptionChange(int);
//-----------overlapPhase--------------
    void on_overlapCbIdChange(int);
    void on_overlapCbTypeChange(int);
    void on_overlapSbTailGreenChange(int);
    void on_overlapSbTailYellowChange(int);
    void on_overlapSbTailRedChange(int);
    //--------------dir-----------
    void on_dirClearContent(quint8 id,bool b);
    void on_mouseDoubleClick(quint8 loadNo);
    void on_mouseClickDir(quint8 loadNo,bool bClick);
    void on_dirCbNoChange(int index);
    void on_dirCbComChange(int index);
    void on_dirCbOverlapChange(int index);
    void on_dirSbLoadChange(int value);
    void on_dirCbVoidChange();

    void on_rcvPhase();
    void on_btnApp();
    void on_btnRead();

//    void on_rcvPhaseMap();//发送完后 又读取了一次  rcvPhase()信号
private:
    Ui::WPhaseWidget *ui;
    phaseWidget *m_pWidget;
    QList<WordIcon*> m_ListCom;
    QList<IconContent*> m_ListComChl;
    QList<WordIcon*> m_ListOverlap;
    QList<IconContent*> m_ListContentCom;
    QList<IconContent*> m_ListOverlapChl;
    QList<ChlIcon*> m_ListChl;
    QList<LoadIcon*> m_ListDir;
    bool m_bTimer;//true timer在运行
//    int m_iTimeId;
    bool m_bDlgInit;//dlg 完成初始化为 true，数据初始化后 有变化才存储

    quint8 m_ucClickChlId;
    quint8 m_ucClickContComIndex;
    quint8 m_ucClickLoadIndex;
    quint8 m_ucClickPhaseId;
    quint8 m_ucClickDirIndex;//m_ListDir index;
    //-----上一次click发生在-----
    bool m_bChl;
    bool m_bLoadCont;//方向容器
    bool m_bComCont;//跟随容器
    bool m_bPhase;//非容器里
    bool m_bDir;//路标
    bool m_bIconClick;//区别于 combobox
    //----------comPhase-----
    bool m_bComBtnMore;
    bool btry;
    //---------dir-----
    bool m_bDClick;//界面双击 出 路标参数框

    PDataProcess *m_pDataProcess;
    Channel_Table* m_pTbChl;
    Phase_Table* m_pTbCom;
    Overlap_Table* m_pTbOverlap;
//    PhaseMap_Table* m_pTbDirMap;
};

#endif // WPHASEWIDGET_H
