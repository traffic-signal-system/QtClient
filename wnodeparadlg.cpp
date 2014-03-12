#include "wnodeparadlg.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
//#include <QSpacerItem>
#include <QLayoutItem>
#include <QList>
#include <QImage>
#include <QBrush>
#include <QPalette>
#include <QDebug>

#include <QStandardItemModel>
#include <QMessageBox>
#include <CommClass.h>
#include <QtEndian>

WNodeParaDlg::WNodeParaDlg(QWidget *parent) :
    QDialog(parent)
{
    initDlg();
    m_pTscInfo = NULL;
    m_pTscNode = new STscNode;
    m_bAddNode = false;
    m_bDelNode = false;
    m_bEditNode = false;
    //-----------------------
    m_bFlagDec1 = false;
    m_bFlagUse1 = false;
    m_bFlagDec2 = false;
    m_bFlagUse2 = false;

    m_pVip = NULL;
    m_pModule = NULL;

    connect(editNodeBtn,SIGNAL(clicked()),this,SLOT(on_editNodeBtn()));
    connect(addNodeBtn,SIGNAL(clicked()),this,SLOT(on_addNodeBtn()));//1103try
    connect(delNodeBtn,SIGNAL(clicked()),this,SLOT(on_delNodeBtn()));
    connect(appNodeBtn,SIGNAL(clicked()),this,SLOT(on_appNodeBtn()));
    connect(readNodeBtn,SIGNAL(clicked()),this,SLOT(on_readNodeBtn()));
    connect(moduleView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_moduleViewClick(QModelIndex)));
    connect(moduleNoSB,SIGNAL(valueChanged(int)),this,SLOT(on_moduleNoChange(int)));
    connect(addModuleBtn,SIGNAL(clicked()),this,SLOT(on_moduleAddBtn()));
    connect(delModuleBtn,SIGNAL(clicked()),this,SLOT(on_moduleDelBtn()));

    connect(dec1Btn,SIGNAL(clicked()),this,SLOT(on_dec1Btn()));
    connect(dec2Btn,SIGNAL(clicked()),this,SLOT(on_dec2Btn()));
}

WNodeParaDlg::~WNodeParaDlg()
{
    qDebug()<<"~WNodeParaDlg";
    if(m_pTscNode!=NULL)
    {
        delete m_pTscNode;
        m_pTscNode = NULL;
    }
}

void WNodeParaDlg::initDlg()
{
    nodeNameCB = new QComboBox;
    nodeNameCB->setEditable(true);
    nodeNameCB->setAutoCompletion(false);
//    nodeNameCB->setDuplicatesEnabled(true);
//    nodeNameCB->setAutoCompletionCaseSensitivity(Qt::CaseSensitive);
//    nodeNameCB->set
    //nodeIdCB = new QComboBox;
    nodeIdLE = new QLineEdit;
    nodeIdLE->setReadOnly(true);

    nodeClusterCB = new QComboBox;
    nodeIpLE = new QLineEdit;
    nodePortLE = new QLineEdit;
    nodeProtocolCB = new QComboBox;


    //nodeNameCB->setMaximumWidth(width);
    nodeNameCB->setFixedSize(100,20);
    int cbWidth = nodeNameCB->width();
    int cbHeight = nodeNameCB->height();

    nodeIdLE->setFixedSize(cbWidth,cbHeight);
    nodeClusterCB->setFixedSize(cbWidth,cbHeight);
    nodeIpLE->setFixedSize(cbWidth,cbHeight);
    nodePortLE->setFixedSize(cbWidth,cbHeight);
    nodeProtocolCB->setFixedSize(cbWidth,cbHeight);

    editNodeBtn = new QPushButton(tr("编辑节点"));
    addNodeBtn = new QPushButton(tr("添加节点"));
    delNodeBtn = new QPushButton(tr("删除节点"));
    appNodeBtn = new QPushButton(tr("应用"));
    readNodeBtn = new QPushButton(tr("读取"));
//    editNodeBtn->setVisible(false);

//    appNodeBtn->setEnabled(false);
    //nodeIpLE->setEnabled(false);
    //nodePortLE->setEnabled(false);
    editNodeBtn->setEnabled(false);
//    delNodeBtn->setEnabled(false);
editNodeBtn->setVisible(false);
//    nodeIpLE->setReadOnly(true);
    nodePortLE->setReadOnly(true);

    QLabel *nodeNameLB = new QLabel(tr("节点名:"));
    QLabel *nodeIdLB = new QLabel(tr("节点ID:"));
    QLabel *nodeClusterLB = new QLabel(tr("  所属群:"));
    QLabel *nodeIpLB = new QLabel(tr("节点IP:"));
    QLabel *nodePortLB = new QLabel(tr("  端口:"));
    QLabel *nodeProtocolLB = new QLabel(tr("协议类型:"));


    timeBaseLE = new QLineEdit;
    scheduleLE = new QLineEdit;
    timePatternLE = new QLineEdit;
    stageTimeLE = new QLineEdit;
    channelLE = new QLineEdit;
    phaseLE = new QLineEdit;
    overlapLE = new QLineEdit;
    detectorLE = new QLineEdit;
    stYellowTimeLE = new QLineEdit;
    stRedTimeLE = new QLineEdit;
    yellowFrequenceLE = new QLineEdit;
    nodeTimeLE = new QLineEdit;

    QList<QLineEdit*> leList;
    leList.append(timeBaseLE);
    leList.append(scheduleLE);
    leList.append(timePatternLE);
    leList.append(stageTimeLE);
    leList.append(channelLE);
    leList.append(phaseLE);
    leList.append(overlapLE);
    leList.append(detectorLE);
    leList.append(stYellowTimeLE);
    leList.append(stRedTimeLE);
    leList.append(yellowFrequenceLE);
    leList.append(nodeTimeLE);

    int leCnt = leList.count();
    for(int i=0;i<leCnt-1;i++)
    {
        leList[i]->setMaximumWidth(60);
        leList[i]->setMinimumWidth(60);
    }
    nodeTimeLE->setMinimumWidth(80);
    nodeTimeLE->setMaximumWidth(120);

    QLabel *timeBaseLB = new QLabel(tr("    时基表数:"));
    QLabel *scheduleLB = new QLabel(tr("    时段表数:"));
    QLabel *timePatternLB = new QLabel(tr("    方案表数:"));
    QLabel *stageTimeLB = new QLabel(tr("阶段配时表数:"));
    QLabel *channelLB = new QLabel(tr("      通道数:"));
    QLabel *phaseLB = new QLabel(tr("  普通相位数:"));
    QLabel *overlapLB = new QLabel(tr("  跟随相位数:"));
    QLabel *detectorLB = new QLabel(tr("    检测器数:"));
    QLabel *stYellowTimeLB = new QLabel(tr("启动黄闪时间:"));
    QLabel *stRedTimeLB = new QLabel(tr("启动红灯时间:"));
    QLabel *yellowFrequenceLB = new QLabel(tr("    黄闪频率:"));
    QLabel *nodeTimeLB = new QLabel(tr("  信号机时间:"));

    timeBaseBtn = new QPushButton(tr("查看"));
    scheduleBtn = new QPushButton(tr("查看"));
    timePatternBtn = new QPushButton(tr("查看"));
    stageTimeBtn = new QPushButton(tr("查看"));
    channelBtn = new QPushButton(tr("查看"));
    phaseBtn = new QPushButton(tr("查看"));
    overlapBtn = new QPushButton(tr("查看"));
    detectorBtn = new QPushButton(tr("查看"));
    stYellowTimeBtn = new QPushButton(tr("查看"));
    stRedTimeBtn = new QPushButton(tr("查看"));
    yellowFrequenceBtn = new QPushButton(tr("查看"));
    nodeTimeBtn = new QPushButton(tr("查看"));

    QList<QPushButton*> btnList;
    btnList.append(timeBaseBtn);
    btnList.append(scheduleBtn);
    btnList.append(timePatternBtn);
    btnList.append(stageTimeBtn);
    btnList.append(channelBtn);
    btnList.append(phaseBtn);
    btnList.append(overlapBtn);
    btnList.append(detectorBtn);
    btnList.append(stYellowTimeBtn);
    btnList.append(stRedTimeBtn);
    btnList.append(yellowFrequenceBtn);
    btnList.append(nodeTimeBtn);

    int btnCnt = btnList.count();
    for(int j=0;j<btnCnt;j++)
    {
        btnList[j]->setMaximumWidth(40);
    }


    //moduleModel = new QStandardItemModel;
    moduleView = new QListView;
    moduleView->setVisible(false);
    //moduleView->setModel(moduleModel);

    moduleNoSB = new QSpinBox;
    moduleNoSB->setMinimum(0);
    moduleNoSB->setMaximum(16);
    deviceNode1LE = new QLineEdit;
    deviceNode2LE = new QLineEdit;
    deviceNode3LE = new QLineEdit;
    vendorLE = new QLineEdit;
    moduleModelLE = new QLineEdit;
    versionLE = new QLineEdit;
    moduleTypeCB = new QComboBox;
    QStringList listType;
    listType<<tr("其它")<<tr("硬件")<<tr("软件");
    moduleTypeCB->addItems(listType);
    addModuleBtn = new QPushButton(tr("添加模块"));
    delModuleBtn = new QPushButton(tr("移除模块"));

    btnAppModule = new QPushButton(tr("应用"));
    btnReadModule = new QPushButton(tr("读取"));

    QLabel *moduleNoLB = new QLabel(tr("  模块号:"));
    QLabel *deviceNodeLB = new QLabel(tr("模块设备:"));
    QLabel *sep1LB = new QLabel(tr("-"));
    QLabel *sep2LB = new QLabel(tr("-"));
    QLabel *vendorLB = new QLabel(tr("  制造商:"));
    QLabel *moduleModelLB = new QLabel(tr("  型  号:"));
    QLabel *versionLB = new QLabel(tr("  版  本:"));
    QLabel *moduleTypeLB = new QLabel(tr("  类  型:"));

    //-------------群参数---------------------
    QLabel *lbClusterName = new QLabel(tr(" 群 名:"));
    QLabel *lbClusterId = new QLabel(tr(" 群 ID:"));
    QLabel *lbClusterDomainId = new QLabel(tr(" 所属域:"));
    QLabel *lbClusterEnable = new QLabel(tr(" 有效性:"));

    cbClusterName = new QComboBox;
    leClusterId = new QLineEdit;
    cbClusterDomainId = new QComboBox;
    cbClusterEnable = new QComboBox;

    leClusterId->setReadOnly(true);
    QStringList listCtEnable;
    listCtEnable<<QObject::tr("有效")<<QObject::tr("无效");
    cbClusterEnable->addItems(listCtEnable);
    cbClusterName->setEditable(true);
    cbClusterDomainId->setEditable(true);
    //cbClusterDomainId->setEditable(true);

    cbClusterName->setFixedSize(cbWidth,cbHeight);
    leClusterId->setFixedSize(cbWidth,cbHeight);
    cbClusterDomainId->setFixedSize(cbWidth,cbHeight);
    cbClusterEnable->setFixedSize(cbWidth,cbHeight);

    addCtBtn = new QPushButton(tr("添加"));
    delCtBtn = new QPushButton(tr("删除"));
    readCtBtn = new QPushButton(tr("读取"));
    appCtBtn = new QPushButton(tr("应用"));

    QGroupBox *ctGroup = new QGroupBox(tr("群参数"));
    QHBoxLayout *ctNameLT = new QHBoxLayout;
    QHBoxLayout *ctIdLT = new QHBoxLayout;
    QHBoxLayout *ctDomainLT = new QHBoxLayout;
    QHBoxLayout *ctEnableLT = new QHBoxLayout;
    QHBoxLayout *ctParaHLT = new QHBoxLayout;
    QHBoxLayout *ctBtnHLT = new QHBoxLayout;
    QVBoxLayout *ctMainVLT = new QVBoxLayout;

    ctNameLT->addWidget(lbClusterName);
    ctNameLT->addWidget(cbClusterName);
    ctIdLT->addWidget(lbClusterId);
    ctIdLT->addWidget(leClusterId);
    ctDomainLT->addWidget(lbClusterDomainId);
    ctDomainLT->addWidget(cbClusterDomainId);
    ctEnableLT->addWidget(lbClusterEnable);
    ctEnableLT->addWidget(cbClusterEnable);

    ctParaHLT->addLayout(ctNameLT);
    ctParaHLT->addLayout(ctIdLT);
    ctParaHLT->addLayout(ctDomainLT);
    ctParaHLT->addLayout(ctEnableLT);

    ctBtnHLT->addStretch();
    ctBtnHLT->addWidget(addCtBtn);
    ctBtnHLT->addWidget(delCtBtn);
    ctBtnHLT->addWidget(readCtBtn);
    ctBtnHLT->addWidget(appCtBtn);
    ctBtnHLT->addStretch();

    ctMainVLT->addLayout(ctParaHLT);
    ctMainVLT->addLayout(ctBtnHLT);
    QHBoxLayout *ctMainHLT = new QHBoxLayout(ctGroup);
    ctMainHLT->addStretch();
    ctMainHLT->addLayout(ctMainVLT);
    ctMainHLT->addStretch();

    //------------------vip参数-----------------------------
    QLabel *lbVipId = new QLabel(tr("Vip号:"));
    QLabel *lbVipEnable = new QLabel(tr("有效性:"));
    QLabel *lbVipDir = new QLabel(tr("方向:"));
    QLabel *lbVipCtrlMode = new QLabel(tr("控制方式:"));
    QLabel *lbVipStart = new QLabel(tr("开始时间:"));
    QLabel *lbVipEnd = new QLabel(tr("结束时间:"));
    QLabel *lbVipNode = new QLabel(tr("节点序列:"));

//    QStringList listNode;
//    QStandardItemModel *model = new QStandardItemModel;
//    for(int i=0;i<10;i++)
//    {
//        listNode<<tr("节点%1").arg(i+1);
//       QStandardItem *item = new QStandardItem(listNode[i]);
//       item->setCheckable(true);
//       item->setWhatsThis(tr("adfdf"));
//       model->appendRow(item);

//    }

//    CheckGroupDeligate *checkGroupDg = new CheckGroupDeligate(listNode);


    cbVipId = new QComboBox;
    cbVipEnable = new QComboBox;
    cbVipDir = new QComboBox;
    cbVipCtrlMode = new QComboBox;
    edVipStart = new QDateTimeEdit;
    edVipEnd = new QDateTimeEdit;
    cbVipNode = new QComboBox();


    cbVipId->setEditable(true);
    //cbVipNode->setModel(model);


//    lbVipId->setFixedSize(cbWidth-35,cbHeight);
//    lbVipEnable->setFixedSize(cbWidth-35,cbHeight);
//    lbVipDir->setFixedSize(cbWidth-35,cbHeight);
//    lbVipCtrlMode->setFixedSize(cbWidth-30,cbHeight);
//    lbVipStart->setFixedSize(cbWidth-30,cbHeight);
//    lbVipEnd->setFixedSize(cbWidth-30,cbHeight);
//    lbVipNode->setFixedSize(cbWidth-30,cbHeight);
    cbVipId->setFixedSize(cbWidth,cbHeight);
    cbVipEnable->setFixedSize(cbWidth,cbHeight);
    cbVipDir->setFixedSize(cbWidth,cbHeight);
    cbVipCtrlMode->setFixedSize(cbWidth,cbHeight);
    cbVipNode->setFixedSize(cbWidth,cbHeight);
    edVipStart->setFixedSize(cbWidth+70,cbHeight);
    edVipEnd->setFixedSize(cbWidth+70,cbHeight);

    addVipBtn = new QPushButton(tr("添加"));
    delVipBtn = new QPushButton(tr("删除"));
    readVipBtn = new QPushButton(tr("读取"));
    appVipBtn = new QPushButton(tr("应用"));

    QStringList listEnable;
    listEnable<<tr("有效")<<tr("无效");
    QStringList listDir;
    listDir<<tr("上行")<<tr("下行");
    QStringList listCtrlMode;
    listCtrlMode<<tr("自动")<<tr("手动");



    cbVipEnable->addItems(listEnable);
    cbVipDir->addItems(listDir);
    cbVipCtrlMode->addItems(listCtrlMode);

    QGroupBox *vipGroup = new QGroupBox(tr("Vip参数"));
    QHBoxLayout *hVip1Layout = new QHBoxLayout;
    QHBoxLayout *hVip2Layout = new QHBoxLayout;
    QHBoxLayout *hVipBtnLayout = new QHBoxLayout;
    QVBoxLayout *vVipLayout = new QVBoxLayout(vipGroup);

    hVip1Layout->addStretch();
    hVip1Layout->addWidget(lbVipId);
    hVip1Layout->addWidget(cbVipId);
    hVip1Layout->addWidget(lbVipEnable);
    hVip1Layout->addWidget(cbVipEnable);
    hVip1Layout->addWidget(lbVipDir);
    hVip1Layout->addWidget(cbVipDir);
    hVip1Layout->addWidget(lbVipCtrlMode);
    hVip1Layout->addWidget(cbVipCtrlMode);
    hVip1Layout->addStretch();

    hVip2Layout->addStretch();
    hVip2Layout->addWidget(lbVipStart);
    hVip2Layout->addWidget(edVipStart);
    hVip2Layout->addWidget(lbVipEnd);
    hVip2Layout->addWidget(edVipEnd);
    hVip2Layout->addWidget(lbVipNode);
    hVip2Layout->addWidget(cbVipNode);
    hVip2Layout->addStretch();

    hVipBtnLayout->addStretch();
    hVipBtnLayout->addWidget(addVipBtn);
    hVipBtnLayout->addWidget(delVipBtn);
    hVipBtnLayout->addWidget(readVipBtn);
    hVipBtnLayout->addWidget(appVipBtn);
    hVipBtnLayout->addStretch();

    vVipLayout->addLayout(hVip1Layout);
    vVipLayout->addLayout(hVip2Layout);
    vVipLayout->addLayout(hVipBtnLayout);

    lbVipNode->hide();
    cbVipNode->hide();

    //-------------------------------------------------
//    lightLB = new QLabel(tr("灯控板"));
//    lightLB->setMaximumWidth(20);
//    lightLB->setMinimumHeight(60);
//    lightLB->setWordWrap(true);
    dec1Btn = new QPushButton(tr("未\n启\n用\n "));
    //dec1Btn->setStyle();
    dec1Btn->setMaximumWidth(20);
    dec1Btn->setMinimumHeight(60);
    dec2Btn = new QPushButton(tr("未\n启\n用\n "));
    dec2Btn->setMaximumWidth(20);
    dec2Btn->setMinimumHeight(60);
    sendBtn = new QPushButton(tr("发送"));

    btnHostBoard = new QPushButton(tr("主\n \n \n板"));
    btnPower = new QPushButton(tr("电\n源\n板\n "));
    btnLight1 = new QPushButton(tr("灯\n控\n板\n1"));
    btnLight2 = new QPushButton(tr("灯\n控\n板\n2"));
    btnLight3 = new QPushButton(tr("灯\n控\n板\n3"));
    btnLight4 = new QPushButton(tr("灯\n控\n板\n4"));
    btnLight5 = new QPushButton(tr("灯\n控\n板\n5"));
    btnLight6 = new QPushButton(tr("灯\n控\n板\n6"));


    btnHostBoard->setMaximumWidth(20);
    btnHostBoard->setMinimumHeight(60);

    btnPower->setMaximumWidth(20);
    btnPower->setMinimumHeight(60);

    btnLight1->setMaximumWidth(20);
    btnLight1->setMinimumHeight(60);

    btnLight2->setMaximumWidth(20);
    btnLight2->setMinimumHeight(60);

    btnLight3->setMaximumWidth(20);
    btnLight3->setMinimumHeight(60);

    btnLight4->setMaximumWidth(20);
    btnLight4->setMinimumHeight(60);

    btnLight5->setMaximumWidth(20);
    btnLight5->setMinimumHeight(60);

    btnLight6->setMaximumWidth(20);
    btnLight6->setMinimumHeight(60);

    cbDet1 = new QCheckBox;
    cbDet2 = new QCheckBox;
    cbHostBoard = new QCheckBox;
    cbPower = new QCheckBox;
    cbLight1 = new QCheckBox;
    cbLight2 = new QCheckBox;
    cbLight3 = new QCheckBox;
    cbLight4 = new QCheckBox;
    cbLight5 = new QCheckBox;
    cbLight6 = new QCheckBox;


    QGroupBox *decGroup = new QGroupBox(tr(""));
    decGroup->setMinimumWidth(200);

//    QHBoxLayout *hLayoutClick = new QHBoxLayout(decGroup);
//    hLayoutClick->setSpacing(10);
//    hLayoutClick->addStretch();
////    hLayoutClick->addWidget(lightLB);
//    hLayoutClick->addWidget(dec1Btn);
//    hLayoutClick->addWidget(dec2Btn);
//    hLayoutClick->addStretch();
    QGridLayout*moduleGrid = new QGridLayout();
    moduleGrid->setSizeConstraint(QLayout::SetFixedSize);
    QHBoxLayout *hModule = new QHBoxLayout();
    moduleGrid->addWidget(btnLight6,0,0);//,2,1);
    moduleGrid->addWidget(btnLight5,0,1);//,2,1);
    moduleGrid->addWidget(btnLight4,0,2);//,2,1);
    moduleGrid->addWidget(btnLight3,0,3);//,2,1);
    moduleGrid->addWidget(btnLight2,0,4);//,2,1);
    moduleGrid->addWidget(btnLight1,0,5);//,2,1);
    moduleGrid->addWidget(btnPower,0,6);//,2,1);
    moduleGrid->addWidget(btnHostBoard,0,7);//,2,1);
    moduleGrid->addWidget(dec1Btn,0,8);//,2,1);
    moduleGrid->addWidget(dec2Btn,0,9);//,2,1);


//    moduleGrid->addWidget(cbLight6,1,0);
//    moduleGrid->addWidget(cbLight5,1,1);
//    moduleGrid->addWidget(cbLight4,1,2);
//    moduleGrid->addWidget(cbLight3,1,3);
//    moduleGrid->addWidget(cbLight2,1,4);
//    moduleGrid->addWidget(cbLight1,1,5);
//    moduleGrid->addWidget(cbPower,1,6);
//    moduleGrid->addWidget(cbHostBoard,1,7);
//    moduleGrid->addWidget(cbDet1,1,8);
//    moduleGrid->addWidget(cbDet2,1,9);
    hModule->addStretch();
    hModule->addLayout(moduleGrid);
    hModule->addStretch();

    //--------------------------------------------------
    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(nodeNameLB);
    vLayout1->addWidget(nodeIpLB);
    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(nodeNameCB);
    vLayout2->addWidget(nodeIpLE);
    QVBoxLayout *vLayout3 = new QVBoxLayout;
    vLayout3->addWidget(nodeIdLB);
    vLayout3->addWidget(nodePortLB);

    QVBoxLayout *vLayout4 = new QVBoxLayout;
    vLayout4->addWidget(nodeIdLE);
    vLayout4->addWidget(nodePortLE);

    QVBoxLayout *vLayout5 = new QVBoxLayout;
    vLayout5->addWidget(nodeClusterLB);
    vLayout5->addWidget(nodeProtocolLB);

    QVBoxLayout *vLayout6 = new QVBoxLayout;
    vLayout6->addWidget(nodeClusterCB);
    vLayout6->addWidget(nodeProtocolCB);

    QHBoxLayout *topHLayout = new QHBoxLayout;


    //topHLayout->setSizeConstraint(QLayout::SetFixedSize);
    QHBoxLayout *bottomHLayout = new QHBoxLayout;
    bottomHLayout->addStretch();
    bottomHLayout->addStretch();
    bottomHLayout->addWidget(editNodeBtn);
    bottomHLayout->addWidget(addNodeBtn);
    bottomHLayout->addWidget(delNodeBtn);
    bottomHLayout->addWidget(appNodeBtn);
    bottomHLayout->addWidget(readNodeBtn);

    bottomHLayout->addStretch();

    QGroupBox* nodeGroup = new QGroupBox(tr("节点参数"));
    QVBoxLayout *nodeVLayout = new QVBoxLayout(nodeGroup);
    nodeVLayout->addLayout(topHLayout);
    nodeVLayout->addSpacing(15);
    nodeVLayout->addLayout(bottomHLayout);



    int row = 0;
    int lbCol = 0;
    int leCol = 1;
//    int btnCol = 2;
    QGridLayout *midLeftGLayout = new QGridLayout;
    midLeftGLayout->setMargin(15);

    midLeftGLayout->addWidget(channelLB,row,lbCol);//通道表
    midLeftGLayout->addWidget(channelLE,row++,leCol);
//    midLeftGLayout->addWidget(channelBtn,row++,btnCol);

    midLeftGLayout->addWidget(phaseLB,row,lbCol);//普通相位表
    midLeftGLayout->addWidget(phaseLE,row++,leCol);
//    midLeftGLayout->addWidget(phaseBtn,row++,btnCol);

    midLeftGLayout->addWidget(overlapLB,row,lbCol);//跟随相位表
    midLeftGLayout->addWidget(overlapLE,row++,leCol);
//    midLeftGLayout->addWidget(overlapBtn,row++,btnCol);

    midLeftGLayout->addWidget(timeBaseLB,row,lbCol);//时基表
    midLeftGLayout->addWidget(timeBaseLE,row++,leCol);
//    midLeftGLayout->addWidget(timeBaseBtn,row++,btnCol);

    midLeftGLayout->addWidget(scheduleLB,row,lbCol);//时段表
    midLeftGLayout->addWidget(scheduleLE,row++,leCol);
//    midLeftGLayout->addWidget(scheduleBtn,row++,btnCol);

    midLeftGLayout->addWidget(timePatternLB,row,lbCol);//方案表
    midLeftGLayout->addWidget(timePatternLE,row++,leCol);
//    midLeftGLayout->addWidget(timePatternBtn,row,btnCol);







    row = 0;
    QGridLayout *midRightGLayout = new QGridLayout;
    midRightGLayout->setMargin(15);
    //midRightGLayout->setColumnStretch(2,0);

    midRightGLayout->addWidget(stageTimeLB,row,lbCol);//阶段配时表
    midRightGLayout->addWidget(stageTimeLE,row++,leCol);
//    midRightGLayout->addWidget(stageTimeBtn,row++,btnCol);

    midRightGLayout->addWidget(detectorLB,row,lbCol);
    midRightGLayout->addWidget(detectorLE,row++,leCol);
//    midRightGLayout->addWidget(detectorBtn,row++,btnCol);

    midRightGLayout->addWidget(stYellowTimeLB,row,lbCol);
    midRightGLayout->addWidget(stYellowTimeLE,row++,leCol);
//    midRightGLayout->addWidget(stYellowTimeBtn,row++,btnCol);

    midRightGLayout->addWidget(stRedTimeLB,row,lbCol);
    midRightGLayout->addWidget(stRedTimeLE,row++,leCol);
//    midRightGLayout->addWidget(stRedTimeBtn,row++,btnCol);

    midRightGLayout->addWidget(yellowFrequenceLB,row,lbCol);
    midRightGLayout->addWidget(yellowFrequenceLE,row++,leCol);
//    midRightGLayout->addWidget(yellowFrequenceBtn,row++,btnCol);

    midRightGLayout->addWidget(nodeTimeLB,row,lbCol);
    midRightGLayout->addWidget(nodeTimeLE,row++,leCol);
//    midRightGLayout->addWidget(nodeTimeBtn,row,btnCol);

    QGroupBox *paraGroup = new QGroupBox;
    //QVBoxLayout *paraVLayout = new QVBoxLayout(paraGroup);
    QHBoxLayout *midHLayout = new QHBoxLayout(paraGroup);
    //midHLayout->setSpacing(55);
    midHLayout->addStretch();
    midHLayout->addLayout(midLeftGLayout);
    midHLayout->addSpacing(30);
    midHLayout->addLayout(midRightGLayout);
    midHLayout->addStretch();

    QGroupBox *moduleGB = new QGroupBox(tr("信号机模块组:"));

    //QVBoxLayout *moduleVLayout = new QVBoxLayout(moduleGB);
    QHBoxLayout *moduleVLayout = new QHBoxLayout(moduleGB);
    QHBoxLayout *moduleHLayout = new QHBoxLayout();
    moduleHLayout->setMargin(15);

    QGridLayout *rightGLayout = new QGridLayout;
//rightGLayout->setColumnStretch(1,0);
    rightGLayout->addWidget(moduleNoLB,0,0);
    rightGLayout->addWidget(moduleNoSB,0,1);

    rightGLayout->addWidget(deviceNodeLB,1,0);
    rightGLayout->addWidget(deviceNode1LE,1,1);
    rightGLayout->addWidget(sep1LB,2,0);
    rightGLayout->addWidget(deviceNode2LE,2,1);
    rightGLayout->addWidget(sep2LB,3,0);
    rightGLayout->addWidget(deviceNode3LE,3,1);

    //---------------------------------------
//    deviceNodeLB->hide();
//    deviceNode1LE->hide();
//    sep1LB->hide();
//    deviceNode2LE->hide();
//    sep2LB->hide();
//    deviceNode3LE->hide();
    //---------------------------------------

    rightGLayout->addWidget(vendorLB,4,0);
    rightGLayout->addWidget(vendorLE,4,1);

    rightGLayout->addWidget(moduleModelLB,5,0);
    rightGLayout->addWidget(moduleModelLE,5,1);

    rightGLayout->addWidget(versionLB,6,0);
    rightGLayout->addWidget(versionLE,6,1);

    rightGLayout->addWidget(moduleTypeLB,7,0);
    rightGLayout->addWidget(moduleTypeCB,7,1);

    QHBoxLayout *subHLayout = new QHBoxLayout;
    subHLayout->setSpacing(15);
    //subHLayout->addStretch();
//    subHLayout->addWidget(addModuleBtn);
//    subHLayout->addWidget(delModuleBtn);
    subHLayout->addWidget(btnAppModule);
    subHLayout->addWidget(btnReadModule);
    subHLayout->addStretch();

//    rightGLayout->addLayout(subHLayout,8,0,1,6);

    QVBoxLayout *vModule = new QVBoxLayout(decGroup);
    vModule->addLayout(hModule);
    vModule->addLayout(subHLayout);

    moduleView->setMaximumWidth(120);
    moduleHLayout->addStretch();
    moduleHLayout->addWidget(moduleView);
    moduleHLayout->addLayout(rightGLayout);
    moduleHLayout->addStretch();


    moduleVLayout->addWidget(decGroup);
//    moduleVLayout->addLayout(subHLayout);
//    moduleVLayout->addLayout(moduleHLayout);


//    QGridLayout *mainGLayout = new QGridLayout(this);
//    mainGLayout->setSpacing(15);
//    //mainGLayout->addLayout(topGLayout,0,0);
//    mainGLayout->addLayout(topHLayout,0,0);
//    mainGLayout->addLayout(midHLayout,1,0);
//    mainGLayout->addWidget(moduleGB,2,0);
//    //mainGLayout->addLayout(moduleHLayout,2,0);
//    mainGLayout->addLayout(bottomHLayout,3,0);

//    paraVLayout->addLayout(topHLayout);
//    paraVLayout->addSpacing(20);
//    paraVLayout->addLayout(midHLayout);

    //moduleGB->setMaximumWidth(550);
//    QGroupBox *pGropBc = new QGroupBox;
    m_pBcForm = new BroadCastForm();
   QHBoxLayout *bcLayout = new QHBoxLayout;
   bcLayout->addStretch();
   bcLayout->addWidget(m_pBcForm);
   bcLayout->addStretch();

    QHBoxLayout *mainHLayout = new QHBoxLayout();
    mainHLayout->addStretch();
//    mainHLayout->addLayout(mainVLayout);
    mainHLayout->addWidget(nodeGroup);
    mainHLayout->addWidget(moduleGB);
    mainHLayout->addStretch();

    QVBoxLayout* mainVLayout = new QVBoxLayout(this);
//    mainVLayout->setSpacing(25);
    //mainVLayout->addLayout(nodeVLayout);
//    mainVLayout->addLayout(midHLayout);
//    mainVLayout->addSpacing(20);
//    mainVLayout->addWidget(nodeGroup);

//    mainVLayout->addWidget(ctGroup);//群参数
//    mainVLayout->addWidget(vipGroup);//vip参数
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->addSpacing(30);
    mainVLayout->addLayout(bcLayout);
//    mainVLayout->addWidget(paraGroup);//参数组
    //mainVLayout->addLayout(midHLayout);
//    mainVLayout->addWidget(decGroup);//灯控板
    //--------------------
    //moduleGB->hide();
    ctGroup->hide();
    vipGroup->hide();
//    mainVLayout->addSpacing(30);
//    mainVLayout->addWidget(moduleGB);
//    mainVLayout->addStretch();
    //mainVLayout->addLayout(bottomHLayout);




    mainVLayout->setSizeConstraint(QLayout::SetMinimumSize);

//系统参数
    timeBaseLE->setText("40");
    scheduleLE->setText("16");
    timePatternLE->setText("16");
    stageTimeLE->setText("16");
    channelLE->setText("24");
    phaseLE->setText("16");
    overlapLE->setText("8");
    detectorLE->setText("48");
    stYellowTimeLE->setText("3");
    stRedTimeLE->setText("3");
    yellowFrequenceLE->setText("");
    nodeTimeLE->setText("");

#ifdef SINGLEMODE
    topHLayout->addWidget(nodeNameLB);
    topHLayout->addWidget(nodeNameCB);
     topHLayout->addSpacing(20);
    topHLayout->addWidget(nodeIpLB);
    topHLayout->addWidget(nodeIpLE);

    addNodeBtn->setVisible(false);
    delNodeBtn->setVisible(false);



#else

    topHLayout->addStretch();
    topHLayout->addLayout(vLayout1);
    topHLayout->addLayout(vLayout2);
    topHLayout->addSpacing(10);
    topHLayout->addLayout(vLayout3);
    topHLayout->addLayout(vLayout4);
    topHLayout->addSpacing(10);
    topHLayout->addLayout(vLayout5);
    topHLayout->addLayout(vLayout6);
    topHLayout->addStretch();
    moduleVLayout->addLayout(moduleHLayout);
#endif

}

void WNodeParaDlg::setDataProcess(PDataProcess *dp)
{
    m_pDataProcess = dp;


    m_pBcForm->setDataProcess(dp);
    nodeNameCB->setModel(m_pDataProcess->m_TscNameModel);
    nodeClusterCB->setModel(dp->m_pModelCTName);
    //nodeIdCB->setModel(m_pDataProcess->m_TscIdModel);

    connect(nodeNameCB,SIGNAL(currentIndexChanged(int)),this,SLOT(setDlgData(int)));
    connect(m_pDataProcess,SIGNAL(resetNodeNameModel(int)),nodeNameCB,SLOT(setCurrentIndex(int)));

    connect(m_pDataProcess,SIGNAL(receivedNodeCommand(int,bool)),this,SLOT(dealRcvNodeCmd(int,bool)));
    connect(m_pDataProcess->timer,SIGNAL(timeout()),this,SLOT(on_timeout()));

    //--------------获取节点数据---------
    connect(dp,SIGNAL(setNodeParaCbTscId(int)),nodeNameCB,SLOT(setCurrentIndex(int)));

    //----------群----------

    connect(addCtBtn,SIGNAL(clicked()),this,SLOT(on_addCTBtn()));
    connect(delCtBtn,SIGNAL(clicked()),this,SLOT(on_delCTBtn()));
    connect(readCtBtn,SIGNAL(clicked()),this,SLOT(on_readCTBtn()));
    connect(appCtBtn,SIGNAL(clicked()),this,SLOT(on_appCTBtn()));

 //   cbClusterName->setModel(dp->m_pModelCTName);
    cbClusterDomainId->addItems(dp->m_ListCTDomainId);
    connect(cbClusterName,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ctNameChange(int)));
    connect(cbClusterName,SIGNAL(editTextChanged(QString)),this,SLOT(on_ctNameChange(QString)));
    connect(cbClusterDomainId,SIGNAL(editTextChanged(QString)),this,SLOT(on_ctDomainIdChange(QString)));
    connect(cbClusterEnable,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ctEnableChange(int)));
    //--------vip------------
    //cbVipId->setModel(m_pDataProcess->m_pModelVipId);
    connect(cbVipId,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipIdChange(int)));
    connect(cbVipEnable,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipEnableChange(int)));
    connect(cbVipDir,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipDirChange(int)));
    connect(cbVipCtrlMode,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbVipCtrlChange(int)));
    connect(edVipStart,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_edVipStartChange(QDateTime)));
    connect(edVipEnd,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_edVipEndChange(QDateTime)));

    connect(addVipBtn,SIGNAL(clicked()),this,SLOT(on_addVipBtn()));
    connect(delVipBtn,SIGNAL(clicked()),this,SLOT(on_delVipBtn()));
    connect(readVipBtn,SIGNAL(clicked()),this,SLOT(on_readVipBtn()));
    connect(appVipBtn,SIGNAL(clicked()),this,SLOT(on_appVipBtn()));

    //-----------------
    connect(m_pDataProcess,SIGNAL(clickTreeView(QModelIndex)),this,SLOT(on_treeViewClick(QModelIndex)));
    //connect(nodeIdCB,SIGNAL(currentIndexChanged(int)),this,SLOT(setDlgData(int)));
    moduleView->setModel(dp->m_pModelModuleName);

    connect(dp,SIGNAL(rcvModuleTable()),this,SLOT(on_rcvModuleTable()));

    connect(btnAppModule,SIGNAL(clicked()),this,SLOT(on_btnAppModule()));
    connect(btnReadModule,SIGNAL(clicked()),this,SLOT(on_btnReadModule()));

    connect(nodeNameCB,SIGNAL(editTextChanged(QString)),this,SLOT(on_nodeNameCBChange(QString)));

    connect(nodeClusterCB,SIGNAL(editTextChanged(QString)),this,SLOT(on_nodeClusterCBChange(QString)));
    connect(nodeIpLE,SIGNAL(textChanged(QString)),this,SLOT(on_nodeIpLEChange(QString)));
//    connect(nodePortLE,SIGNAL(textChanged(QString)),this,SLOT(on_dataChange()));
}

/*
 对于不存在的群，在节点信息那将显示 群id
*/
void WNodeParaDlg::setDlgData(int index)
{qDebug()<<"currentindex"<<index;
    qDebug()<<"setDlgData:"<<index;
    if(index==-1)
        return;
//    if(!m_bEditNode)
//    {
//        editNodeBtn->setEnabled(true);
//    }
//    if(!m_bDelNode)
//    {
//        delNodeBtn->setEnabled(true);
//    }
    m_bInit = false;
    m_iListIndex = index;
    m_pTscInfo = m_pDataProcess->getTscInfoByIndex(index);
    if(m_pTscInfo==NULL)
    {
        return;
    }

    //nodeNameCB->setCurrentIndex(index);
    nodeIdLE->setText(QString::number(m_pTscInfo->uiId));

//    quint32 nodeId = m_pTscInfo->uiId;
//    m_pDataProcess->setCurrentNodeId(nodeId);

    byte clusterId = m_pTscInfo->ucClusterId;
    QString strClusterId;
    //strClusterId = m_pDataProcess->m_pTscInfo->tb
    strClusterId = m_pDataProcess->getCtNameById(clusterId);
    //strClusterId = QString::number(int(clusterId));
//    nodeClusterCB->setEditable(true);
    int ctIndex = m_pDataProcess->m_ListCTName.indexOf(strClusterId);
    if(ctIndex!=-1)
    {
        nodeClusterCB->setCurrentIndex(ctIndex);
//        nodeClusterCB->setEditText(strClusterId);
    }
    else
    {
        nodeClusterCB->setEditable(true);
        nodeClusterCB->setEditText(tr("群%1").arg(clusterId));
//        nodeClusterCB->setEditable(false);
    }

    char *cIp = m_pTscInfo->sDeviceIp;
    //char ipLen = m_pTscInfo->sDeviceIp.GetCount();
    nodeIpLE->setText(QString::fromAscii((const char*)cIp/*,int(ipLen)*/));
    nodePortLE->setText(QString::number(m_pTscInfo->uiPort));
    nodeProtocolCB->setEditable(true);
    nodeProtocolCB->setEditText(QString::number(int(m_pTscInfo->ucProtocolType)));

//    每次都从新读取
//    if(/*m_pDataProcess->m_bFlagInit*/!m_pDataProcess->m_ListNewTscId.contains(nodeId))
//    {
//        m_pDataProcess->changeNode();


//        return;//所有节点完成初始化后 改变节点时 只要分析更改后的m_pTscInfo 里的数据表就可以
//    }
    m_pDataProcess->setStatusBarMessage(tr("开始读取数据"),LBSECOND);
    m_pDataProcess->m_bFlagOnLine = true;
    if(/*!m_pDataProcess->m_bFlagClusterSend||*/!m_pDataProcess->m_bFlagShowCluster)
    {
        m_pDataProcess->requireTscTable(TSC_TABLE_MODULE);//起始表
    }
    m_pDataProcess->m_bFlagNodeIdChanged = true;

    m_bInit = true;
    qDebug()<<"setDlgData:---------";
}

void WNodeParaDlg::clearModuleDlg()
{
    deviceNode1LE->clear();
    deviceNode2LE->clear();
    deviceNode3LE->clear();
    vendorLE->clear();
    moduleModelLE->clear();
    versionLE->clear();
}

void WNodeParaDlg::getVipDataPoint()
{
    QString str = cbVipId->currentText();
    quint8 id = 0;
    if(str.count()==4)
    {
        id = str.right(1).toInt();
    }
    else if(str.count()==5)
    {
        id = str.right(2).toInt();
    }
    if(id>0)
    {
        m_pVip = m_pDataProcess->m_pVipInfo->tbVipProperty+id-1;
    }
    else
    {
        m_pVip = NULL;
    }
}

void WNodeParaDlg::setVipInterfaceData()
{
    if(m_pVip!=NULL)
    {
        //quint8 id = m_pVip->ucVipLineId;
        if(m_pVip->ucValidity==0)
        {
            cbVipEnable->setCurrentIndex(0);
        }
        else
        {
            cbVipEnable->setCurrentIndex(1);
        }
        if(m_pVip->ucDirection==0)
        {
            cbVipDir->setCurrentIndex(0);
        }
        else
        {
            cbVipDir->setCurrentIndex(1);
        }
        if(m_pVip->ucControl==0)
        {
            cbVipCtrlMode->setCurrentIndex(0);
        }
        else
        {
            cbVipCtrlMode->setCurrentIndex(1);
        }
        quint32 start = qFromBigEndian<quint32>(m_pVip->uiStartTime);
        quint32 end = qFromBigEndian<quint32>(m_pVip->uiEndTime);
        QDateTime time = QDateTime::fromTime_t(start);
        edVipStart->setDateTime(time);
        time = QDateTime::fromTime_t(end);
        edVipEnd->setDateTime(time);
    }
}

void WNodeParaDlg::getVipInterfaceData()
{
//    getVipDataPoint();
//    if(m_pVip!=0)
//    {
//        quint32 start = edVipStart->dateTime().toTime_t();
//        m_pVip->
//    }
}

void WNodeParaDlg::setModuleData(int index)
{
    if(index>-1&&index<MAX_MODULE_NUM&&m_pDataProcess!=NULL)
    {
        if(m_pDataProcess->m_pTscInfo==NULL)
        {
            return;
        }
        m_bInit = false;
        Module_Table* p = m_pDataProcess->m_pTscInfo->tbModule+index;

        QString devStr = QString::fromAscii(p->sDeviceNode,p->bNodeLen);
        QStringList devList = devStr.split('-');
        //qDebug()<<"device count:"<<devList.count();
        if(devList.count()==3)
        {
            deviceNode1LE->setText(devList[0]);
            deviceNode2LE->setText(devList[1]);
            deviceNode3LE->setText(devList[2]);
        }

        QString vendorStr = QString::fromAscii(p->sVendor,p->bVendorLen);
        vendorLE->setText(vendorStr);

        QString modelStr = QString::fromAscii(p->sModuleModel,p->bModuleModelLen);
        moduleModelLE->setText(modelStr);

        QString versionStr = QString::fromAscii(p->sVersion,p->bVersionLen);
        versionLE->setText(versionStr);
        moduleTypeCB->setCurrentIndex(p->bModuleType-1);
        m_bInit = true;
    }
}

//-----------------slot-----------------
void WNodeParaDlg::on_editNodeBtn()
{
    m_bEditNode = true;
    addNodeBtn->setEnabled(false);
    delNodeBtn->setEnabled(false);
    m_iListIndex = nodeNameCB->currentIndex();

    nodeNameCB->setEditable(true);
    nodeNameCB->hidePopup();

    //nodeIdLE->setEditable(false);
    //nodeIdLE->setEnabled(false);
    nodeClusterCB->setEditable(true);
    nodeIpLE->setReadOnly(false);
    nodePortLE->setReadOnly(false);
    nodeProtocolCB->setEditable(true);

    appNodeBtn->setEnabled(true);

    editNodeBtn->setEnabled(false);
    delNodeBtn->setEnabled(false);
    //addNodeBtn->setEnabled(false);

}

void WNodeParaDlg::on_addNodeBtn()
{
//    editNodeBtn->setEnabled(false);
//    delNodeBtn->setEnabled(false);
//    addNodeBtn->setEnabled(false);

//    m_iListIndex = nodeNameCB->count();

//    m_bAddNode = true;
//    nodeNameCB->setEditable(true);
//    nodeNameCB->hidePopup();
//    //nodeIdLE-setEditable(true);
//    nodeClusterCB->setEditable(true);
//    nodeIpLE->setReadOnly(false);
//    nodePortLE->setReadOnly(false);
//    nodePortLE->setText(tr("5435"));
//    nodeProtocolCB->setEditable(true);

//    appNodeBtn->setEnabled(true);
//    quint32 id = m_pDataProcess->getNewNodeId();
//    nodeIdLE->setText(QString::number(id));
//    //nodeIdLE->setEnabled(false);

//    //nodeNameCB->clear();
//    nodeNameCB->setEditText(QObject::tr(""));
//    nodeIpLE->clear();
//    m_bAddNode = true;
    if(m_pDataProcess->addNode())
    {

    }


}

void WNodeParaDlg::on_delNodeBtn()
{
    QString id = nodeIdLE->text();
    int index = m_pDataProcess->m_TscIdList.indexOf(id);
    if(index!=-1)
    {
        QString name = m_pDataProcess->m_TscNameList[index];
        if(QMessageBox::question(this,tr("警告"),tr("确定删除节点：%1").arg(name),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Ok)
        {
            m_pDataProcess->delNode(index);
        }
    }
//    m_iListIndex = nodeNameCB->currentIndex();
//    //qDebug()<<"deal Node Index:"<<m_iListIndex;
//    m_pTscNode->uiId = (unsigned int)(nodeIdLE->text().toInt());
//    if(m_pDataProcess->sendNodeCommand(NODE_DELETE,m_pTscNode))
//    {
//        m_pDataProcess->timerManage(true);
//        m_bDelNode = true;
////        addNodeBtn->setEnabled(false);
//        editNodeBtn->setEnabled(false);
////        delNodeBtn->setEnabled(false);
//    }
}

void WNodeParaDlg::on_appNodeBtn()
{
#ifdef  SINGLEMODE
           m_pDataProcess->m_TscIdList.clear();
           m_pDataProcess->m_TscClusterIdList.clear();
           m_pDataProcess->m_TscNameList.clear();
           m_pDataProcess->m_TscIpList.clear();
           m_pDataProcess->m_TscPortList.clear();


           m_pDataProcess->m_TscIdList.append(QString::number(1));
           m_pDataProcess->m_TscClusterIdList.append(1);
           m_pDataProcess->m_TscNameList.append(nodeNameCB->currentText());
           m_pDataProcess->m_TscIpList.append(nodeIpLE->text());
           m_pDataProcess->m_TscPortList.append(5435);

   #endif

    if(m_pDataProcess->sendTscInfoTable())
    {
        m_pDataProcess->m_bFlagNodeNameFocus = false;
    }
    else
    {

    }
}

void WNodeParaDlg::on_readNodeBtn()
{
    m_pDataProcess->requireTscInfoTable();
}

void WNodeParaDlg::dealRcvNodeCmd(int cmd, bool)
{
    m_pDataProcess->timerManage(false);
    QString str;
    switch(cmd)
    {
    case NODE_ADD:
        {
            m_bAddNode = false;
            addNodeBtn->setEnabled(true);
            m_pDataProcess->addNode(m_pTscNode);
            str = QObject::tr("添加节点成功！");
            break;
        }
    case NODE_UPDATE:
        {
            m_bEditNode = false;
            addNodeBtn->setEnabled(true);
            m_pDataProcess->editNode(m_pTscNode,m_iListIndex);
            str = QObject::tr("修改节点成功！");
            break;
        }
    case NODE_DELETE:
        {
            m_bDelNode = false;
            addNodeBtn->setEnabled(true);
            m_pDataProcess->delNode(m_iListIndex);
            str = QObject::tr("删除节点成功！");
            break;
        }
    default:
        {
            str = QObject::tr("节点操作返回信息出错！");
            break;
        }
    }

    //QMessageBox::information(this,tr("节点操作"),str,QMessageBox::Ok);
    m_pDataProcess->rcvResponseInfo(str);

}

void WNodeParaDlg::on_dataChange()
{
    QString id = nodeIdLE->text();
    int index =nodeNameCB->currentIndex();
    if(m_bInit&&index!=-1)
    {
        QString nodeName = nodeNameCB->currentText();
        QString  ctName = nodeClusterCB->currentText();
        QString strIp = nodeIpLE->text();
        QString port = nodePortLE->text();

//        if(!m_pDataProcess->validTscName(nodeName,index))
//        {
//            QMessageBox::warning(this,tr("节点信息错误"),tr("节点名错误"),QMessageBox::Ok);

//            return;
//        }


//        if(!m_pDataProcess->validTscIp(strIp,index))
//        {
//            QMessageBox::warning(this,tr("节点信息错误"),tr("节点Ip错误"),QMessageBox::Ok);
//            return;
//        }

        int ctIndex = m_pDataProcess->m_ListCTName.indexOf(ctName);
        QString ctId = tr("1");
        if(ctIndex!=-1)
        {
            ctId = m_pDataProcess->m_ListCTId[ctIndex];
        }

        m_pDataProcess->m_TscClusterIdList.replace(index,ctId.toInt());
        m_pDataProcess->m_TscIpList.replace(index,strIp);
        m_pDataProcess->m_TscPortList.replace(index,port.toInt());
        qDebug()<<"nodeNameCB->currentText()"<<nodeName<<"m_pDataProcess->m_TscNameList[index]"<<m_pDataProcess->m_TscNameList[index];
        if(!nodeName.compare(m_pDataProcess->m_TscNameList[index])==0)
        {
            m_pDataProcess->m_TscNameList.replace(index,nodeName);
            m_pDataProcess->m_bFlagTscNameList = true;
            m_pDataProcess->setModelItem();
        }

    }
}

void WNodeParaDlg::on_nodeNameCBChange(QString str)
{
    int index = nodeNameCB->currentIndex();
    qDebug()<<"on_nodeNameCBChange edit change"<<str<<"index"<<nodeNameCB->currentIndex();
    if(m_bInit&&!str.isEmpty())
    {
//        int index = nodeNameCB->currentIndex();
//        qDebug()<<"on_nodeNameCBChange"<<str<<"index"<<index;
        if(index==-1)
        {
            return;
        }
        if(!str.compare(m_pDataProcess->m_TscNameList[index])==0)
        {
//            if(!m_pDataProcess->validTscName(str,index))
//            {
//                QMessageBox::warning(this,tr("节点信息错误"),tr("节点名错误"),QMessageBox::Ok);

//                return;
//            }
            m_pDataProcess->m_bFlagNodeNameFocus = true;
            m_pDataProcess->m_TscNameList.replace(index,str);
            m_pDataProcess->m_bFlagTscNameList = true;
            m_pDataProcess->m_iCurTscNameLisIndex = index;
            m_pDataProcess->setModelItem();
        }
    }

}

void WNodeParaDlg::on_nodeClusterCBChange(QString str)
{
    if(m_bInit)
    {
        int index = m_iListIndex;
        int ctIndex = m_pDataProcess->m_ListCTName.indexOf(str);
        quint8 ctId = m_pDataProcess->m_ListCTId[ctIndex].toInt();
        m_pDataProcess->m_TscClusterIdList.replace(index,ctId);
    }
}

void WNodeParaDlg::on_nodeIpLEChange(QString str)
{
    if(m_bInit&&!str.isEmpty())
    {
        int index = m_iListIndex;
//        if(!m_pDataProcess->validTscIp(str,index))
//        {
//            QMessageBox::warning(this,tr("节点信息错误"),tr("节点Ip错误"),QMessageBox::Ok);
//            return;
//        }
        m_pDataProcess->m_TscIpList.replace(index,str);
    }
}

void WNodeParaDlg::on_addCTBtn()
{
    quint8 id = m_pDataProcess->getNewClusterId();
    if(id>0)
    {
        ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
        p->ucClusterId = id;
        leClusterId->setText(QString::number(id));
        leClusterId->setModified(true);

        cbClusterName->clearEditText();
        cbClusterDomainId->clearEditText();
        cbClusterEnable->setCurrentIndex(0);
    }
}

void WNodeParaDlg::on_delCTBtn()
{
    quint8 id = leClusterId->text().toInt();
    if(id>0&&id<MAX_CLUSTER_NUM+1)
    {
//        ClusterProperty_Table *p = m_pDataProcess->m_pClusterInfo->tbCTProperty+id-1;
//        memset(p,0,sizeof(ClusterProperty_Table));
        if(m_pDataProcess->sendClusterCommand(CLUSTER_DELETE,id))
        {
            qDebug()<<"deal cluster send succ";
        }
    }
}

void WNodeParaDlg::on_readCTBtn()
{
    m_pDataProcess->requireClusterInfoTable();
}

void WNodeParaDlg::on_appCTBtn()
{
    m_pDataProcess->sendClusterInfoToLib();
}

void WNodeParaDlg::on_ctNameChange(int index)
{
    if(index==-1)
        return;
    qDebug()<<"ct name change index"<<index;
    if(m_pDataProcess->m_ListCTId.count()>index&&index!=-1)
    {
        quint8 id = m_pDataProcess->m_ListCTId[index].toInt();
        ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
        leClusterId->setText(QString::number(id));
        cbClusterDomainId->setEditText(QString::number(p->ucDomainId));
        if(p->ucClusterEnable==0)
        {
            cbClusterEnable->setCurrentIndex(0);
        }
        else
        {
            cbClusterEnable->setCurrentIndex(1);
        }
    }
}

void WNodeParaDlg::on_ctNameChange(QString str)
{
    if(str.isEmpty())
        return;
    qDebug()<<"on_ctNameChange"<<str;
    quint8 id = leClusterId->text().toInt();
    if(id>0&&id<MAX_CLUSTER_NUM+1)
    {
        qDebug()<<"on_ctNameChange id"<<id;
        ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
        QByteArray strArr = str.toLocal8Bit();
        quint8 len = strArr.count();
        p->ucClusterNameLen = len;
        memcpy(p->ucClusterName,strArr.data(),len);
    }
}

void WNodeParaDlg::on_ctDomainIdChange(QString str)
{
    if(str.isEmpty())
        return;
    qDebug()<<"on_ctDomainIdChange"<<str;
    quint8 id = leClusterId->text().toInt();
    if(id>0&&id<MAX_CLUSTER_NUM+1)
    {
        ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
        p->ucDomainId = str.toInt();
    }
}

void WNodeParaDlg::on_ctEnableChange(int index)
{
    if(index==-1)
        return;
    qDebug()<<"on_ctEnableChange"<<index;
    quint8 id = leClusterId->text().toInt();
    if(id>0&&id<MAX_CLUSTER_NUM+1)
    {
        ClusterProperty_Table *p = m_pDataProcess->m_pCTProperty+id-1;
        p->ucClusterEnable = index;
    }
}
//----------------vip------------------
void WNodeParaDlg::on_addVipBtn()
{
    quint8 vipId = m_pDataProcess->getVipId();
    if(vipId!=0)
    {
        m_pVip = m_pDataProcess->m_pVipInfo->tbVipProperty+vipId-1;
        cbVipId->setEditText(tr("Vip%1").arg(vipId));
    }
    else
    {
        m_pVip = NULL;
    }
}

void WNodeParaDlg::on_delVipBtn()
{
    getVipDataPoint();
    if(m_pVip!=NULL)
    {
        int tbSize = sizeof(VipProperty_Table);
        memset(m_pVip,0,tbSize);
        m_pDataProcess->sendVipInfoToLib();
    }
}

void WNodeParaDlg::on_readVipBtn()
{
    m_pDataProcess->requireVipInfoTable();
}

void WNodeParaDlg::on_appVipBtn()
{

    m_pDataProcess->sendVipInfoToLib();
}

void WNodeParaDlg::on_cbVipIdChange(int index)
{
    if(index==-1)
        return;
    getVipDataPoint();
    setVipInterfaceData();
    QString str = cbVipId->currentText();
    int cnt = str.count();
    quint8 id = 0;
    if(cnt=4)
    {
        id = str.right(1).toInt();
    }
    else if(cnt==5)
    {
        id = str.right(2).toInt();
    }
    m_pDataProcess->cbVipIdChange(id);
}

void WNodeParaDlg::on_cbVipEnableChange(int index)
{
    if(m_pVip!=NULL)
    {
        m_pVip->ucValidity = index;
    }
}

void WNodeParaDlg::on_cbVipDirChange(int index)
{
    if(m_pVip!=NULL)
    {
        m_pVip->ucDirection = index;
    }
}

void WNodeParaDlg::on_cbVipCtrlChange(int index)
{
    if(m_pVip!=NULL)
    {
        m_pVip->ucControl = index;
    }
}

void WNodeParaDlg::on_edVipStartChange(QDateTime t)
{
    if(m_pVip!=NULL)
    {
        m_pVip->uiStartTime = qToBigEndian<quint32>(t.toTime_t());
    }
}

void WNodeParaDlg::on_edVipEndChange(QDateTime t)
{
    if(m_pVip!=NULL)
    {
        m_pVip->uiEndTime = qToBigEndian<quint32>(t.toTime_t());
    }
}

void WNodeParaDlg::on_timeout()
{
    qDebug()<<"timeout";
    //m_pDataProcess->timerManage(false);
    m_bAddNode = false;
    m_bDelNode = false;
    m_bEditNode = false;
    addNodeBtn->setEnabled(true);
}

void WNodeParaDlg::on_treeViewClick(QModelIndex index)
{
    if(index.isValid())
    {
        if(m_pDataProcess->m_iTabWidgetIndex==1||m_pDataProcess->m_iTabWidgetIndex==2)
        {
            QString nodeName = index.data().toString();
//            qDebug()<<"nodeName on_treeViewClick"<<nodeName;
            int nodeIndex = m_pDataProcess->m_TscNameList.indexOf(nodeName);
            if(nodeIndex>-1)
            {
                int cbIndex = nodeNameCB->currentIndex();
                if(cbIndex==nodeIndex)
                {
                    setDlgData(nodeIndex);
                }
                else
                {
                    nodeNameCB->setCurrentIndex(nodeIndex);
                }
            }
        }
//        QString str = m_pDataProcess->m_TscNameIconModel->data(index).toString();
//        bool bFlagShowCluster = m_pDataProcess->m_bFlagShowCluster;
//        //QString strStatus;
//        if(index.parent()!=QModelIndex()&&!bFlagShowCluster)//节点
//        {
//            m_pDataProcess->m_bFlagCluster = false;
//            QModelIndex pIndex = index.parent();
//            int nameIndex = nodeNameCB->findText(str);
//            if(nameIndex!=-1)
//            {
//                //strStatus.append(tr("当前节点:%1 ").arg(str));
//                int curIndex = nodeNameCB->currentIndex();
//                if(curIndex==nameIndex)
//                {
//                    setDlgData(nameIndex);
//                }
//                else
//                {
//                    nodeNameCB->setCurrentIndex(nameIndex);
//                }
//                cbClusterName->setCurrentIndex(pIndex.row());
//            }
//        }
//        else if(m_pDataProcess->m_ListCTName.indexOf(str)!=-1)//群
//        {
//            int ctIndex = cbClusterName->findText(str);
//            if(ctIndex!=-1)
//            {
//                //strStatus.append(tr("当前群:%1  ").arg(str));
//                cbClusterName->setCurrentIndex(index.row());
//            }
//        }
        //strStatus.append(tr(" 当前页面:%1  ").arg(m_pDataProcess->m_strPage));
         //m_pDataProcess->setStatusBarMessage(strStatus,3);

    }
}

void WNodeParaDlg::on_moduleViewClick(QModelIndex i)
{
    Module_Table *p = m_pDataProcess->m_pTscInfo->tbModule;
    int j = i.row();
    //qDebug()<<"click moduleview index:"<<j;
    int index = 0;
    for(int k=0;index<MAX_MODULE_NUM;index++)
    {
        if((p+index)->bNo!=0)
        {

            if(k==j)
                break;
            k++;
        }
    }
    //qDebug()<<"index:"<<index;
    moduleNoSB->setValue(index+1);
}

void WNodeParaDlg::on_moduleNoChange(int no)
{
    clearModuleDlg();
    if(no==0&&no>MAX_MODULE_NUM)
    {
        deviceNode1LE->setEnabled(false);
        deviceNode2LE->setEnabled(false);
        deviceNode3LE->setEnabled(false);
        vendorLE->setEnabled(false);
        moduleModelLE->setEnabled(false);
        versionLE->setEnabled(false);
        addModuleBtn->setEnabled(false);
        delModuleBtn->setEnabled(false);
        m_pModule = NULL;
        return;
//        moduleTypeCB;
    }
    else if(!deviceNode1LE->isEnabled())
    {
        deviceNode1LE->setEnabled(true);
        deviceNode2LE->setEnabled(true);
        deviceNode3LE->setEnabled(true);
        vendorLE->setEnabled(true);
        moduleModelLE->setEnabled(true);
        versionLE->setEnabled(true);
        addModuleBtn->setEnabled(true);
        //delModuleBtn->setEnabled(true);
    }
    Module_Table *p = m_pDataProcess->m_pTscInfo->tbModule+no-1;
    m_pModule = p;
    if(p->bNo==0)
    {
        delModuleBtn->setEnabled(false);
    }
    else
    {
        delModuleBtn->setEnabled(true);
    }
    QString devStr = QString::fromAscii(p->sDeviceNode,p->bNodeLen);
    QStringList devList = devStr.split('-');
    //qDebug()<<"device count:"<<devList.count();
    if(devList.count()==3)
    {
        deviceNode1LE->setText(devList[0]);
        deviceNode2LE->setText(devList[1]);
        deviceNode3LE->setText(devList[2]);
    }

    QString vendorStr = QString::fromAscii(p->sVendor,p->bVendorLen);
    vendorLE->setText(vendorStr);

    QString modelStr = QString::fromAscii(p->sModuleModel,p->bModuleModelLen);
    moduleModelLE->setText(modelStr);

    QString versionStr = QString::fromAscii(p->sVersion,p->bVersionLen);
    versionLE->setText(versionStr);

    moduleTypeCB->setCurrentIndex(p->bModuleType-1);
}

void WNodeParaDlg::on_moduleAddBtn()
{
    QString dev1Str;
    QString dev2Str;
    QString dev3Str;
    QString vendorStr;
    QString modelStr;
    QString versionStr;
    dev1Str = deviceNode1LE->text();
    dev2Str = deviceNode2LE->text();
    dev3Str = deviceNode3LE->text();
    vendorStr = vendorLE->text();
    modelStr = moduleModelLE->text();
    versionStr = versionLE->text();

    if(dev1Str.isEmpty()||dev2Str.isEmpty()
                        ||dev3Str.isEmpty()
                        ||vendorStr.isEmpty()
                        ||modelStr.isEmpty()
                        ||versionStr.isEmpty())
    {
        qDebug()<<"module lineEdit is empty";
        return;
    }

    QString devStr = dev1Str+tr("-")+dev2Str+tr("-")+dev3Str;
    int no = moduleNoSB->value();
    Module_Table *p = m_pDataProcess->m_pTscInfo->tbModule+no-1;
    p->bNo = no;
    p->bNodeLen = devStr.count();
    memcpy(p->sDeviceNode,devStr.toAscii().data(),devStr.count());
    p->bVendorLen = vendorStr.count();
    //p->sVendor = vendorStr.toAscii().data();
    memcpy(p->sVendor,vendorStr.toAscii().data(),vendorStr.count());

    p->bModuleModelLen = modelStr.count();
    //p->sModuleModel = modelStr.toAscii().data();
    memcpy(p->sModuleModel,modelStr.toAscii().data(),modelStr.count());

    p->bVersionLen = versionStr.count();
    //p->sVersion = versionStr.toAscii().data();
    memcpy(p->sVersion,versionStr.toAscii().data(),versionStr.count());

    p->bModuleType = moduleTypeCB->currentIndex()+1;

    m_pDataProcess->sendModuleToLib();
}

void WNodeParaDlg::on_moduleDelBtn()
{
    int value = moduleNoSB->value();
    Module_Table *p = m_pDataProcess->m_pTscInfo->tbModule+value-1;
    int tableSize = sizeof(Module_Table);
    memset(p,0,tableSize);
    m_pDataProcess->sendModuleToLib();
}

void WNodeParaDlg::on_btnAppModule()
{
    if(m_pDataProcess!=NULL)
        m_pDataProcess->sendModuleToLib();
}

void WNodeParaDlg::on_btnReadModule()
{
    if(m_pDataProcess!=NULL)
        m_pDataProcess->requireTscTable(TSC_TABLE_MODULE);
}

void WNodeParaDlg::on_dec1Btn()
{
    Module_Table *p = m_pDataProcess->m_pTscInfo->tbModule;
    if(m_bFlagUse1)
    {
        m_bFlagDec1 = !m_bFlagDec1;
        if(m_bFlagDec1)
        {
            dec1Btn->setText(tr("接\n口\n板\n"));

            QString str = tr("DET-0-1");
            (p+0)->bNodeLen = str.count();
            memset((p+0)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+0)->sDeviceNode,str.toAscii().data(),str.count());

            str = tr("DET-2-0");
            (p+2)->bNodeLen = str.count();
            memset((p+2)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+2)->sDeviceNode,str.toAscii().data(),str.count());
        }
        else
        {
            dec1Btn->setText(tr("未\n启\n用\n"));
            m_bFlagUse1 = false;

            QString str = tr("DET-0-0");
            (p+0)->bNodeLen = str.count();
            memset((p+0)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+0)->sDeviceNode,str.toAscii().data(),str.count());

            str = tr("DET-2-0");
            (p+2)->bNodeLen = str.count();
            memset((p+2)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+2)->sDeviceNode,str.toAscii().data(),str.count());
        }
    }
    else
    {
        dec1Btn->setText(tr("检\n测\n器\n板"));

        QString str = tr("DET-0-0");
        (p+0)->bNodeLen = str.count();
        memset((p+0)->sDeviceNode,0,DEVICENODELEN);
        memcpy((p+0)->sDeviceNode,str.toAscii().data(),str.count());

        str = tr("DET-2-1");
        (p+2)->bNodeLen = str.count();
        memset((p+2)->sDeviceNode,0,DEVICENODELEN);
        memcpy((p+2)->sDeviceNode,str.toAscii().data(),str.count());

        m_bFlagUse1 = true;
        m_bFlagDec1 = false;
    }
    m_pDataProcess->analyseModuleTable();
    if(m_bFlagDec1)
    {
        moduleNoSB->setValue(1);
//        setModuleData(0);
    }
    else
    {
        moduleNoSB->setValue(3);
//        setModuleData(2);
    }
//    m_pDataProcess->sendModuleToLib();
}

/*
 m_bFlagUse2 = true;
 m_bFlagDec2 = true;接口板2       m_bFlagDec2 = false;检测板2

*/
void WNodeParaDlg::on_dec2Btn()
{
    Module_Table *p = m_pDataProcess->m_pTscInfo->tbModule;
    if(m_bFlagUse2)
    {
        m_bFlagDec2 = !m_bFlagDec2;
        if(m_bFlagDec2)
        {
            dec2Btn->setText(tr("接\n口\n板\n"));

            QString str = tr("DET-1-17");
            (p+1)->bNodeLen = str.count();
            memset((p+1)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+1)->sDeviceNode,str.toAscii().data(),str.count());

            str = tr("DET-3-0");
            (p+3)->bNodeLen = str.count();
            memset((p+3)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+3)->sDeviceNode,str.toAscii().data(),str.count());

        }
        else
        {
            dec2Btn->setText(tr("未\n启\n用\n"));
            m_bFlagUse2 = false;

            QString str = tr("DET-1-0");
            (p+1)->bNodeLen = str.count();
            memset((p+1)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+1)->sDeviceNode,str.toAscii().data(),str.count());

            str = tr("DET-3-0");
            (p+3)->bNodeLen = str.count();
            memset((p+3)->sDeviceNode,0,DEVICENODELEN);
            memcpy((p+3)->sDeviceNode,str.toAscii().data(),str.count());
        }
    }
    else
    {
        dec2Btn->setText(tr("检\n测\n器\n板"));
        m_bFlagUse2 = true;
        m_bFlagDec2 = false;

        QString str = tr("DET-1-0");

        (p+1)->bNodeLen = str.count();
        memset((p+1)->sDeviceNode,0,DEVICENODELEN);
        memcpy((p+1)->sDeviceNode,str.toAscii().data(),str.count());

        str = tr("DET-3-17");
        (p+3)->bNodeLen = str.count();
        memset((p+3)->sDeviceNode,0,DEVICENODELEN);
        memcpy((p+3)->sDeviceNode,str.toAscii().data(),str.count());
    }
     m_pDataProcess->analyseModuleTable();
     if(m_bFlagDec2)
     {
         moduleNoSB->setValue(2);
//         setModuleData(1);
     }
     else
     {
         moduleNoSB->setValue(4);
//         setModuleData(3);
     }
//    m_pDataProcess->sendModuleToLib();
}

void WNodeParaDlg::on_rcvModuleTable()
{
    Module_Table *p = m_pDataProcess->m_pTscInfo->tbModule;
    int cnt = m_pDataProcess->m_pTscInfo->iModuleTableNum;
    m_bFlagUse1 = false;
    m_bFlagUse2 = false;
    m_bFlagDec1 = false;
    m_bFlagDec2 = false;
    qDebug()<<"rcv model cnt:"<<cnt;
    for(int i=0;i<cnt;i++)
    {
        int strLen = (p+i)->bNodeLen;
        //qDebug()<<"strLen---------------------------------------------"<<strLen;
        if(strLen>2)
        {
            QString str = QString::fromAscii((p+i)->sDeviceNode,strLen);
            QStringList strList = str.split('-');

            int index = strList[1].toInt();//0,1,接口板  2，3检测器板
            int m = strList[2].toInt();//0  不启用 ;1,17启用
            //qDebug()<<tr("接口：")<<index<<tr("外接：")<<m;
            if(index==0)
            {
                if(m!=0)
                {
                    m_bFlagUse1 = true;
                    m_bFlagDec1 = true;
                    dec1Btn->setText(tr("接\n口\n板\n"));
                    //qDebug()<<tr("接\n口\n板\n1");
                }
            }
            else if(index==1)
            {
                if(m!=0)
                {
                    m_bFlagUse2 = true;
                    m_bFlagDec2 = true;
                    dec2Btn->setText(tr("接\n口\n板\n"));
                   // qDebug()<<tr("接\n口\n板\n2");
                }
            }
            else if(index==2)
            {
                if(m!=0)
                {
                    m_bFlagUse1 = true;
                    m_bFlagDec1 = false;
                    dec1Btn->setText(tr("检\n测\n器\n板"));
                    //qDebug()<<tr("检\n测\n器\n板\n1");
                }

            }
            else if(index==3)
            {
                if(m!=0)
                {
                    m_bFlagUse2 = true;
                    m_bFlagDec2 = false;
                    dec2Btn->setText(tr("检\n测\n器\n板"));
                    //qDebug()<<tr("检\n测\n器\n板\n2");
                }

            }

        }
    }
    if(!m_bFlagUse1)
    {
        dec1Btn->setText(tr("未\n启\n用\n"));
        //qDebug()<<tr("\n未\n启\n用\n1");
    }
    if(!m_bFlagUse2)
    {
        dec2Btn->setText(tr("未\n启\n用\n"));
        qDebug()<<tr("未启用2");
    }
}
