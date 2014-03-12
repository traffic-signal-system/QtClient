//author: sun
//date:2011.09.29

#ifndef WMAINWINDOW_H
#define WMAINWINDOW_H

#include <QMainWindow>

#include "WUserLogIn.h"

#include "wnodeparadlg.h"
/*
 主窗口 框架
*/
namespace Ui {
    class MainWindow;
}

class WTree;
class WWindowstack;
class PDataProcess;

class WMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WMainWindow(QWidget *parent = 0);
    ~WMainWindow();

    void appendDebugString(QString &str);
    void setProcessor(PDataProcess *processor);

    void setUserLogIn(WUserLogIn *p);

//    void writeDataText(QByteArray byteArr);
//    quint8 getCmd(QByteArray arry);
//    QString getTableStr(quint8 cmd);
//    bool canWriteTable(quint8 cmd);//用于检测是否 要写入的表
//    bool deleteExistTable(quint8 cmd);

private slots:
    void dispDebugWindow();
    void dealReceived(QByteArray byteArr);

    void on_userView();

    void on_nodeParaClick();//1110try 节点参数界面
    void on_timePlanClick();//时基表界面
    void on_stagePlanClick();//方案表 阶段配时表
    void on_action8Click();//检测器 调试发送
    void on_phaseClick();//相位界面
    void on_statusClick();//实时界面
    void on_detectorClick();//检测器界面
    void on_eventLogClick();//事件日志
    void on_clusterClick();//群时空图
    void on_vipClick();
    void on_fromBtnClick();//从信号机 或 服务端
    void on_sysparaClick();//系统参数
    void on_conflictClick();
    void on_TrafficClick();
    void on_windowstackChange(int);
    void on_scheduleClick();

    void on_sendMessage(QByteArray byteArr,bool flag);//1115try

    void on_readCmd();//1116try读取文本上的命令信息，调用dataprocess的dealRcvMessage

    void on_statusBarMessage(QString,quint8 index=0);//状态栏显示信息
    void on_tabIndexChange(int index);

private:
    Ui::MainWindow *ui;

    WTree *w_tree;
    WWindowstack *w_windowstack;
    PDataProcess *m_pDataProcess;
    WUserLogIn *userLogIn;
//    WUserViewDlg *userView;
    QLabel *statusLabel1;
    QLabel *statusLabel2;
    QLabel *statusLabel3;
    QLabel *statusLabel4;
    bool m_bDebug;
    QList<QPushButton*> m_btnList;
    //WNodeParaDlg *nodePara;
    QList<quint8> m_ListBtnIndex;//用于存放每个tab的按钮 0~btncnt-1
    QList<quint8> m_ListBtnCnt;//每个tab的按钮数
//    quint8 m_ucBtnIndex;//0起

//    QList<quint8> m_ListBtnSystem;
//    QList<quint8> m_ListBtnNode;
//    QList<quint8> m_ListBtnCluster;
//    QList<quint8> m_ListBtnVip;
    bool m_bFromService;//默认true 从服务端读取

};

#endif // WMAINWINDOW_H
