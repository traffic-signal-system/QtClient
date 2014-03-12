//author: sun
//date:2011.09.29

#ifndef WMAINWINDOW_H
#define WMAINWINDOW_H

#include <QMainWindow>

#include "WUserLogIn.h"

#include "wnodeparadlg.h"
/*
 ������ ���
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
//    bool canWriteTable(quint8 cmd);//���ڼ���Ƿ� Ҫд��ı�
//    bool deleteExistTable(quint8 cmd);

private slots:
    void dispDebugWindow();
    void dealReceived(QByteArray byteArr);

    void on_userView();

    void on_nodeParaClick();//1110try �ڵ��������
    void on_timePlanClick();//ʱ�������
    void on_stagePlanClick();//������ �׶���ʱ��
    void on_action8Click();//����� ���Է���
    void on_phaseClick();//��λ����
    void on_statusClick();//ʵʱ����
    void on_detectorClick();//���������
    void on_eventLogClick();//�¼���־
    void on_clusterClick();//Ⱥʱ��ͼ
    void on_vipClick();
    void on_fromBtnClick();//���źŻ� �� �����
    void on_sysparaClick();//ϵͳ����
    void on_conflictClick();
    void on_TrafficClick();
    void on_windowstackChange(int);
    void on_scheduleClick();

    void on_sendMessage(QByteArray byteArr,bool flag);//1115try

    void on_readCmd();//1116try��ȡ�ı��ϵ�������Ϣ������dataprocess��dealRcvMessage

    void on_statusBarMessage(QString,quint8 index=0);//״̬����ʾ��Ϣ
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
    QList<quint8> m_ListBtnIndex;//���ڴ��ÿ��tab�İ�ť 0~btncnt-1
    QList<quint8> m_ListBtnCnt;//ÿ��tab�İ�ť��
//    quint8 m_ucBtnIndex;//0��

//    QList<quint8> m_ListBtnSystem;
//    QList<quint8> m_ListBtnNode;
//    QList<quint8> m_ListBtnCluster;
//    QList<quint8> m_ListBtnVip;
    bool m_bFromService;//Ĭ��true �ӷ���˶�ȡ

};

#endif // WMAINWINDOW_H
