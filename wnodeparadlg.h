#ifndef WNODEPARADLG_H
#define WNODEPARADLG_H

#include <QDialog>

#include <QComboBox>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QStandardItem>
//#include <QList>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include "pdataprocess.h"
//#include "WPage.h"
#include <QSpinBox>
#include <QLabel>
#include <QDateTimeEdit>
#include <QTableView>
#include "broadcastform.h"

/*
 节点参数界面
*/
class WNodeParaDlg : public QDialog
{
    Q_OBJECT
public:
    explicit WNodeParaDlg(QWidget *parent = 0);
    ~WNodeParaDlg();
    void initDlg();
    void setDataProcess(PDataProcess *dp);
    void clearModuleDlg();

    void getVipDataPoint();
    void setVipInterfaceData();//界面显示数据
    void getVipInterfaceData();//界面数据 存到 内存

    void setModuleData(int index);

signals:

public slots:
    void setDlgData(int index);//on nodeNameCB changed
    void on_editNodeBtn();
    void on_addNodeBtn();
    void on_delNodeBtn();
    void on_appNodeBtn();
    void on_readNodeBtn();
    void dealRcvNodeCmd(int,bool);

    void on_dataChange();//节点信息
    void on_nodeNameCBChange(QString str);
    void on_nodeClusterCBChange(QString str);
    void on_nodeIpLEChange(QString str);

    //-----------群----------------
    void on_addCTBtn();
    void on_delCTBtn();
    void on_readCTBtn();
    void on_appCTBtn();

    void on_ctNameChange(int index);
    void on_ctNameChange(QString str);
    void on_ctDomainIdChange(QString str);
    void on_ctEnableChange(int index);
    //-------------vip--------------
    void on_addVipBtn();
    void on_readVipBtn();
    void on_delVipBtn();
    void on_appVipBtn();

    void on_cbVipIdChange(int index);
    void on_cbVipEnableChange(int index);
    void on_cbVipDirChange(int index);
    void on_cbVipCtrlChange(int index);
    void on_edVipStartChange(QDateTime);
    void on_edVipEndChange(QDateTime);

    //------------------------------
    void on_timeout();

    void on_treeViewClick(QModelIndex);

    void on_moduleViewClick(QModelIndex);
    void on_moduleNoChange(int);

    void on_moduleAddBtn();
    void on_moduleDelBtn();
    void on_btnAppModule();
    void on_btnReadModule();

    void on_dec1Btn();
    void on_dec2Btn();

    void on_rcvModuleTable();
private:
    QComboBox *nodeNameCB;
    QComboBox *nodeIdCB;
    QLineEdit *nodeIdLE;
    QComboBox *nodeClusterCB;
    QLineEdit *nodeIpLE;
    QLineEdit *nodePortLE;
    QComboBox *nodeProtocolCB;



    QPushButton *addNodeBtn;
    QPushButton *appNodeBtn;
    QPushButton *editNodeBtn;
    QPushButton *delNodeBtn;
    QPushButton *readNodeBtn;

    QLineEdit *timeBaseLE;
    QLineEdit *scheduleLE;
    QLineEdit *timePatternLE;
    QLineEdit *stageTimeLE;
    QLineEdit *channelLE;
    QLineEdit *phaseLE;
    QLineEdit *overlapLE;
    QLineEdit *detectorLE;
    QLineEdit *stYellowTimeLE;
    QLineEdit *stRedTimeLE;
    QLineEdit *yellowFrequenceLE;
    QLineEdit *nodeTimeLE;

    QPushButton *timeBaseBtn;
    QPushButton *scheduleBtn;
    QPushButton *timePatternBtn;
    QPushButton *stageTimeBtn;
    QPushButton *channelBtn;
    QPushButton *phaseBtn;
    QPushButton *overlapBtn;
    QPushButton *detectorBtn;
    QPushButton *stYellowTimeBtn;
    QPushButton *stRedTimeBtn;
    QPushButton *yellowFrequenceBtn;
    QPushButton *nodeTimeBtn;
//-------------------新增群设置----------------
    QComboBox *cbClusterName;
    QLineEdit *leClusterId;
    QComboBox *cbClusterDomainId;
    QComboBox *cbClusterEnable;

    QPushButton *addCtBtn;
    QPushButton *delCtBtn;
    QPushButton *readCtBtn;
    QPushButton *appCtBtn;

//    bool m_bAddCtName;
//    bool m_bAddCtDomainId;

    //------------新增vip设置----------------
    QComboBox *cbVipId;
    QComboBox *cbVipEnable;
    QComboBox *cbVipDir;
    QComboBox *cbVipCtrlMode;
    QDateTimeEdit *edVipStart;
    QDateTimeEdit *edVipEnd;
    QComboBox *cbVipNode;
    //QLineEdit *cbVipNode;
    //QTableView *cbVipNode;
    QPushButton *addVipBtn;
    QPushButton *delVipBtn;
    QPushButton *readVipBtn;
    QPushButton *appVipBtn;
    VipProperty_Table *m_pVip;
    //-------------------------------

    //QStandardItemModel *moduleModel;
    QListView *moduleView;
    QSpinBox *moduleNoSB;
    QLineEdit *deviceNode1LE;
    QLineEdit *deviceNode2LE;
    QLineEdit *deviceNode3LE;
    QLineEdit *vendorLE;
    QLineEdit *moduleModelLE;
    QLineEdit *versionLE;
    QComboBox *moduleTypeCB;

    QLabel *lightLB;//灯控板
    QPushButton *btnHostBoard;//主板
    QPushButton *btnPower;//电源板
    QPushButton *btnLight1;
    QPushButton *btnLight2;
    QPushButton *btnLight3;
    QPushButton *btnLight4;
    QPushButton *btnLight5;
    QPushButton *btnLight6;

    QCheckBox *cbHostBoard;
    QCheckBox *cbPower;
    QCheckBox *cbLight1;
    QCheckBox *cbLight2;
    QCheckBox *cbLight3;
    QCheckBox *cbLight4;
    QCheckBox *cbLight5;
    QCheckBox *cbLight6;
    QCheckBox *cbDet1;
    QCheckBox *cbDet2;


    QPushButton *dec1Btn;//接口板1 检测板1
    QPushButton *dec2Btn;//接口板2 检测板2
    bool m_bFlagDec1;
    bool m_bFlagUse1;
    bool m_bFlagDec2;
    bool m_bFlagUse2;
    QPushButton *sendBtn;//发送

    QPushButton *delModuleBtn;
    QPushButton *addModuleBtn;

    QPushButton *btnAppModule;
    QPushButton *btnReadModule;

    STscInfo *m_pTscInfo;
    PDataProcess *m_pDataProcess;

    STscNode *m_pTscNode;
    bool m_bAddNode;
    bool m_bDelNode;
    bool m_bEditNode;
    int m_iListIndex;

    bool m_bInit;//true 为 初始化完成 false在编辑
    Module_Table *m_pModule;
    BroadCastForm *m_pBcForm;



};

#endif // WNODEPARADLG_H
