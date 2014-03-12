//author: sun
//date:2011.09.29

#include "WMainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTabWidget>
//#include <QToolBar>
//#include <QAction>

#include "WTree.h"
#include "WWindowstack.h"
#include "PDataProcess.h"

WMainWindow::WMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pDataProcess(NULL)
{
//    this->setAttribute(Qt::WA_DeleteOnClose);
//this->setFixedSize(945,710);
    ui->setupUi(this);
    w_tree        = new WTree(ui->leftWindow);

    w_windowstack = new WWindowstack(ui->rightWindow);
    QVBoxLayout *vlay = new QVBoxLayout(ui->rightWindow);
    vlay->setMargin(0);
    vlay->addWidget(w_windowstack);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(ui->horizontalLayout);
    mainLayout->addStretch();
//    QGridLayout *gLay = new QGridLayout(ui->leftWindow);
//    gLay->addWidget(w_tree);

    QImage img;
    img.load(":Files/images/logo.jpg");
    img.size();
    QBrush * brush = new QBrush;
    brush->setTextureImage(img);
    ui->logoframe->setAutoFillBackground(true);
    QPalette p = ui->logoframe->palette();
    p.setBrush(QPalette::Window,*brush);
    ui->logoframe->setPalette(p);

    ui->diveLine->setVisible(ui->dispDebugWindow->isChecked());
    ui->debugWindow->setVisible(ui->dispDebugWindow->isChecked());

//    userView = new WUserViewDlg(this);
    m_bFromService = true;

    //nodePara = new WNodeParaDlg(ui->rightWindow);//1101try
   // w_windowstack->addWidget(nodePara);
    //w_windowstack->setCurrentIndex(2);

    connect(ui->dispDebugWindow, SIGNAL(triggered()), this, SLOT(dispDebugWindow()));

    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(on_userView()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->action_NodeInfo,SIGNAL(triggered()),this,SLOT(on_nodeParaClick()));//1110try
    connect(ui->action_Plan,SIGNAL(triggered()),this,SLOT(on_timePlanClick()));
    connect(ui->action_Stage,SIGNAL(triggered()),this,SLOT(on_stagePlanClick()));
//    connect(ui->action_8,SIGNAL(triggered()),this,SLOT(on_action8Click()));
    connect(ui->action_Phase,SIGNAL(triggered()),this,SLOT(on_phaseClick()));
    connect(ui->action_Status,SIGNAL(triggered()),this,SLOT(on_statusClick()));
    connect(ui->action_Dec,SIGNAL(triggered()),this,SLOT(on_detectorClick()));
    connect(ui->action_Note,SIGNAL(triggered()),this,SLOT(on_eventLogClick()));
    connect(ui->action_Conflict,SIGNAL(triggered()),this,SLOT(on_conflictClick()));
    connect(ui->action_Schedule,SIGNAL(triggered()),this,SLOT(on_scheduleClick()));
//    connect(ui->action_13,SIGNAL(triggered()),this,SLOT(on_clusterClick()));
//    connect(ui->actionVIP,SIGNAL(triggered()),this,SLOT(on_vipClick()));

    connect(ui->btnUserManage,SIGNAL(clicked()),this,SLOT(on_userView()));
    connect(ui->btnEventLog,SIGNAL(clicked()),this,SLOT(on_eventLogClick()));

    connect(ui->btnNodePara,SIGNAL(clicked()),this,SLOT(on_nodeParaClick()));//1110try
    //connect(ui->moduleBtn,SIGNAL(clicked()),this,SLOT(on_nodeParaClick()));
//    connect(ui->,SIGNAL(clicked()),this,SLOT(on_timePlanClick()));
    //connect(ui->scheduleBtn,SIGNAL(clicked()),this,SLOT(on_timePlanClick()));
    //connect(ui->timePatternBtn,SIGNAL(clicked()),this,SLOT(on_stagePlanClick()));
    connect(ui->btnStage,SIGNAL(clicked()),this,SLOT(on_stagePlanClick()));
//    connect(ui->action_8,SIGNAL(triggered()),this,SLOT(on_action8Click()));
    connect(ui->btnPhase,SIGNAL(clicked()),this,SLOT(on_phaseClick()));
    //connect(ui->overlapBtn,SIGNAL(clicked()),this,SLOT(on_phaseClick()));
    //connect(ui->channelBtn,SIGNAL(clicked()),this,SLOT(on_phaseClick()));
    //connect(ui->phaseMapBtn,SIGNAL(clicked()),this,SLOT(on_phaseClick()));
    connect(ui->btnDetector,SIGNAL(clicked()),this,SLOT(on_detectorClick()));
    connect(ui->btnStatus,SIGNAL(clicked()),this,SLOT(on_statusClick()));

    connect(ui->btnTimePlan,SIGNAL(clicked()),this,SLOT(on_timePlanClick()));
    //connect(ui->detStatusBtn,SIGNAL(clicked()),this,SLOT(on_detectorClick()));
    connect(ui->btnCluster,SIGNAL(clicked()),this,SLOT(on_clusterClick()));
    connect(ui->btnVip,SIGNAL(clicked()),this,SLOT(on_vipClick()));
//    connect(ui->btnDebug, SIGNAL(clicked()), this, SLOT(dispDebugWindow()));
    connect(ui->btnSysPara,SIGNAL(clicked()),this,SLOT(on_sysparaClick()));
    connect(ui->btnConfict,SIGNAL(clicked()),this,SLOT(on_conflictClick()));
    connect(ui->btnTrafficData,SIGNAL(clicked()),this,SLOT(on_TrafficClick()));

    connect(w_windowstack,SIGNAL(currentChanged(int)),this,SLOT(on_windowstackChange(int)));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_tabIndexChange(int)));

//-------------try--------
    ui->btnUserIn->setFlat(true);
    ui->btnUserLog->setFlat(true);
    ui->btnTrafficData->setFlat(true);
//    ui->btnUserManage->setFlat(true);
//    ui->btnSysPara->setFlat(true);
//    ui->btnDebug->setFlat(true);
//    ui->btnFrom->setFlat(true);
    ui->btnTimer->setFlat(true);
    ui->btnFlag->setFlat(true);

    ui->btnUserIn->setEnabled(false);
    ui->btnUserLog->setEnabled(false);
//    ui->btnTrafficData->setEnabled(false);
//    ui->btnUserManage->setFlat(true);
//    ui->btnSysPara->setEnabled(false);
//    ui->btnDebug->setFlat(true);
//    ui->btnFrom->setFlat(true);
    ui->btnTimer->setEnabled(false);
    ui->btnFlag->setEnabled(false);



    //-----------������ӵ� ��˳�����󣨲�Ҫ��ǰ�棩��stackҲ��˳��ź�Ҫ�޸�btncnt--------


    m_btnList.append(ui->btnUserManage);
    m_btnList.append(ui->btnNodePara);
    m_btnList.append(ui->btnPhase);
    m_btnList.append(ui->btnStage);
    m_btnList.append(ui->btnDetector);
    m_btnList.append(ui->btnStatus);
    m_btnList.append(ui->btnTimePlan);
    m_btnList.append(ui->btnCluster);
    m_btnList.append(ui->btnVip);
    m_btnList.append(ui->btnEventLog);
    m_btnList.append(ui->btnSysPara);
    m_btnList.append(ui->btnConfict);
    m_btnList.append(ui->btnTrafficData);

    //m_btnList.append(ui->clusterTimeBaseBtn);//9
    m_ListBtnIndex<<0<<5<<7<<8;//�ȴ�����
    m_ListBtnCnt<<1<<5<<2<<5;
    foreach(QPushButton* btn,m_btnList)
    {
        btn->setFlat(true);
    }
    m_btnList[5]->setDown(true);
    ui->tabWidget->setCurrentIndex(1);

//    ui->logo->setMaximumWidth(110);
//    ui->tabWidget->setMaximumWidth(110);
    //connect(ui->action,SIGNAL(triggered()),userLogIn,SLOT(show()));

//    QToolBar *toolBar = this->addToolBar(tr("�ڵ����"));
//    QAction *acNodeInfo = new QAction(tr("�ڵ���Ϣ"),this);
//    QAction *acTimeBase = new QAction(tr("ʱ����"),this);
//    QAction *acSchedule = new QAction(tr("ʱ�α�"),this);
//    toolBar->addAction(acNodeInfo);
//    toolBar->addAction(acTimeBase);
//    toolBar->addAction(acSchedule);
//    toolBar->setAllowedAreas(Qt::TopToolBarArea);
//    this->addToolBar(Qt::TopToolBarArea,toolBar);
    //toolBar->add
   // QTabWidget *tabWidget = new QTabWidget();
//    ui->menuBar->hide();
    //ui->mainToolBar->hide();
    m_bDebug = false;

    statusLabel4 = new QLabel;
    statusBar()->addPermanentWidget(statusLabel4,2);
    statusLabel4->setText(tr("���ͽ�����Ϣ"));

    statusLabel3 = new QLabel;
    statusBar()->addPermanentWidget(statusLabel3);
    statusLabel3->setText(tr("����״̬"));

    statusLabel2 = new QLabel;
    statusBar()->addPermanentWidget(statusLabel2);
    statusLabel2->setText(tr("Ⱥ���ڵ���Ϣ"));

    statusLabel1 = new QLabel;
    statusBar()->addPermanentWidget(statusLabel1);
    statusLabel1->setText(tr("��ǰҳ��"));

    ui->tabWidget->hide();
    ui->logoframe->hide();
    ui->label->hide();
    ui->logo->hide();
    ui->leftWindow->hide();
    ui->line_2->hide();
    ui->diveLine->hide();
//    this->setFixedWidth(910);
    ui->menu->setVisible(false);
//    ui->menu_3->setVisible(false);
//    ui->menu_6->setVisible(false);
    ui->action->setVisible(false);
    ui->action_2->setVisible(false);
//    ui->action_3->setVisible(false);
    ui->action_4->setVisible(false);
    ui->action_12->setVisible(false);
    ui->action_13->setVisible(false);
//    ui->action_18->setVisible(false);
//    ui->action_19->setVisible(false);
//    ui->action_20->setVisible(false);
//    ui->action_21->setVisible(false);
//    ui->action_22->setVisible(false);
//    ui->action_23->setVisible(false);
//    ui->action_24->setVisible(false);
//    ui->action_25->setVisible(false);
//    ui->action_26->setVisible(false);
//    ui->action_27->setVisible(false);
//    ui->action_28->setVisible(false);
//    ui->action_29->setVisible(false);
//    ui->action_30->setVisible(false);
//    ui->actionVIP_2->setVisible(false);
//    this->setWindowTitle();

}

void WMainWindow::dispDebugWindow()
{
    m_bDebug = !m_bDebug;
    ui->diveLine->setVisible(m_bDebug);
    ui->debugWindow->setVisible(m_bDebug);
}

void WMainWindow::appendDebugString(QString &str)
{
    for (int i=str.size()/2; i>1; i--)
    {
        str.insert(i*2-2,' ');
    }
    ui->debugWindow->append(str);
}

void WMainWindow::dealReceived(QByteArray byteArr)
{
    qDebug() <<"dealing length: "<< byteArr.size();
    static QString str;
    str = QString(byteArr.toHex());
    appendDebugString(str);
}

WMainWindow::~WMainWindow()
{
    qDebug()<<"~MainWindouw";
    delete ui;
    delete w_tree;
    delete w_windowstack;

//    if(nodePara!=NULL)
//    {
//        delete nodePara;
//        nodePara = NULL;
//    }
}

void WMainWindow::setProcessor(PDataProcess *processor)
{
    m_pDataProcess = processor;
    w_windowstack->setProcessor(processor);
//    userView->setDataProcess(processor);

    w_tree->setDataProcess(m_pDataProcess);

    //nodePara->setDataProcess(processor);
    //connect(m_pDataProcess,SIGNAL(received(QByteArray)), this, SLOT(dealReceived(QByteArray)));

    //connect(ui->action_3,SIGNAL(triggered()),nodePara,SLOT(show()));//1101try
    connect(processor,SIGNAL(statusBarMessage(QString,quint8)),this,SLOT(on_statusBarMessage(QString,quint8)));//״̬����ʾ��Ϣ
    connect(m_pDataProcess,SIGNAL(sendToService(QByteArray,bool)),this,SLOT(on_sendMessage(QByteArray,bool)));//1115try
    connect(m_pDataProcess,SIGNAL(recvMessage(QByteArray,bool)),this,SLOT(on_sendMessage(QByteArray,bool)));
    connect(ui->action_16,SIGNAL(triggered()),this,SLOT(on_readCmd()));//1117try ��ȡcmd
    connect(w_windowstack,SIGNAL(currentChanged(int)),m_pDataProcess,SLOT(on_setFlagShowInterfase(int)));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),m_pDataProcess,SLOT(on_tabWidgetIndexChange(int)));
//    connect(ui->btnFrom,SIGNAL(clicked()),this,SLOT(on_fromBtnClick()));

//    bool b = true;
//    if(b)
//    {
//        ui->btnFrom->setText(tr("�����"));
        m_bFromService = true;
        m_pDataProcess->m_iCmdType = CS_CMDTYPE_LOCAL_DATABASE_READ;//CS_CMDTYPE_TSC_PARA_READ;
//    }
//    else
//    {
//        ui->btnFrom->setText(tr("�źŻ�"));
//        m_bFromService = false;
//        m_pDataProcess->m_iCmdType = CS_CMDTYPE_TSC_PARA_READ;
//    }

    //�޸� ��ȡ


}

void WMainWindow::setUserLogIn(WUserLogIn *p)
{
    userLogIn = p;
    connect(ui->action,SIGNAL(triggered()),userLogIn,SLOT(show()));
}

//void WMainWindow::writeDataText(QByteArray byteArr)
//{
//    qDebug()<<"writeDataText------------------------------";
////    QFile file("data.txt");
////    byteArr.append(tr("\n"));//�ַ�ĩβ���˻���
////    if(file.open(QFile::Append | QIODevice::Text/*|QFile::Text*/))
////    {
////        file.write(byteArr.data(),byteArr.length());
////        file.close();
////    }
////    else
////    {
////        qDebug()<<"open file data.txt err--------------------------------------------------------------------";
////    }
//}

//quint8 WMainWindow::getCmd(QByteArray array)
//{
//    char *data = array.data();
//    SUtcsFrameHead rcvMsgHead;
//    quint32 len = 0;
//    memcpy(&rcvMsgHead,data,sizeof(SUtcsFrameHead));
//    len += sizeof(SUtcsFrameHead);
////    data=sizeof(SUtcsFrameHead);
//    quint32 type = qFromBigEndian<quint32>(rcvMsgHead.uiCommandType);
//    quint32 num = qFromBigEndian<quint32>(rcvMsgHead.uiIdNum);//
//    if(CS_CMDTYPE_TSC_PARA_WRITE==type)
//    {
//        len += num*sizeof(quint32);
//        return *(data+len);
//    }
//    else
//    {
//        return 0;
//    }
//}

//QString WMainWindow::getTableStr(quint8 cmd)
//{
//    QString str;
//    switch(cmd)
//    {
//    case TSC_TABLE_MODULE://        = 0x85,  //ģ���
//        str = tr("TSC_TABLE_MODULE");
//        break;
//    case TSC_TABLE_TIMEBASE://      = 0x8D,  //
//        str = tr("TSC_TABLE_TIMEBASE");
//        break;
//    case TSC_TABLE_SCHEDULE://      = 0x8E,  //ʱ�α�
//        str = tr("TSC_TABLE_SCHEDULE");
//        break;
//    case TSC_TABLE_PHASE://         = 0x95,  //��λ��
//        str = tr("TSC_TABLE_PHASE");
//        break;
//    case TSC_TABLE_PHASECONFLICT:// = 0x97,  //��λ��ͻ��
//        str = tr("TSC_TABLE_PHASECONFLICT");
//        break;
//    case TSC_TABLE_DETECTOR://      = 0x9F,  //�������
//        str = tr("TSC_TABLE_DETECTOR");
//        break;
//    case TSC_TABLE_CHANNEL://       = 0xB0,  //ͨ����
//        str = tr("TSC_TABLE_CHANNEL");
//        break;
//    case TSC_TABLE_TIMEPATTERN://   = 0xC0,  //��ʱ������
//        str = tr("TSC_TABLE_TIMEPATTERN");
//        break;
//    case TSC_TABLE_STAGETIME://     = 0xC1,  //�׶���ʱ��
//        str = tr("TSC_TABLE_STAGETIME");
//        break;
//    case TSC_TABLE_OVERLAP://       = 0xC8,   //������λ��
//        str = tr("TSC_TABLE_OVERLAP");
//        break;
//    case TBL_TABLE_PHASE2DIREC://   = 0xfa
//        str = tr("TBL_TABLE_PHASE2DIREC");
//        break;
//    default:
//        break;
//    }
//    return str;
//}

//bool WMainWindow::canWriteTable(quint8 cmd)
//{
//    //quint8 cmd = getCmd(array);
//    switch(cmd)
//    {
//    case TSC_TABLE_MODULE://        = 0x85,  //ģ���
//    case TSC_TABLE_TIMEBASE://      = 0x8D,  //
//    case TSC_TABLE_SCHEDULE://      = 0x8E,  //ʱ�α�
//    case TSC_TABLE_PHASE://         = 0x95,  //��λ��
//    case TSC_TABLE_PHASECONFLICT:// = 0x97,  //��λ��ͻ��
//    case TSC_TABLE_DETECTOR://      = 0x9F,  //�������
//    case TSC_TABLE_CHANNEL://       = 0xB0,  //ͨ����
//    case TSC_TABLE_TIMEPATTERN://   = 0xC0,  //��ʱ������
//    case TSC_TABLE_STAGETIME://     = 0xC1,  //�׶���ʱ��
//    case TSC_TABLE_OVERLAP://       = 0xC8,   //������λ��
//    case TBL_TABLE_PHASE2DIREC://   = 0xfa
//        return true;
//    default:
//        return false;
//    }
//}

//bool WMainWindow::deleteExistTable(quint8 cmd)
//{
//    QFile file("data.txt");
//    if(file.open(QFile::ReadOnly|QFile::Text))
//    {
//        QTextStream stream(&file);

//    }
//}

void WMainWindow::on_userView()
{
    w_windowstack->setWidgetIndex(0);
//    userView->initViewData();
//    userView->show();
}

void WMainWindow::on_nodeParaClick()
{
    w_windowstack->setWidgetIndex(1);
}

void WMainWindow::on_timePlanClick()
{
    w_windowstack->setWidgetIndex(6);

//    m_pDataProcess->requireTscTable(TSC_TABLE_TIMEBASE);
//    m_pDataProcess->requireTscTable(TSC_TABLE_SCHEDULE);
}

void WMainWindow::on_stagePlanClick()
{
    w_windowstack->setWidgetIndex(3);
//    m_pDataProcess->requireTscTable(TSC_TABLE_TIMEPATTERN);
//    m_pDataProcess->requireTscTable(TSC_TABLE_STAGETIME);
}

void WMainWindow::on_action8Click()
{
//    w_windowstack->setWidgetIndex(0);
}

void WMainWindow::on_phaseClick()
{
    w_windowstack->setWidgetIndex(2);
}

void WMainWindow::on_statusClick()
{
    w_windowstack->setWidgetIndex(5);
}

void WMainWindow::on_detectorClick()
{
    w_windowstack->setWidgetIndex(4);
}

void WMainWindow::on_eventLogClick()
{
    w_windowstack->setWidgetIndex(9);
}

void WMainWindow::on_clusterClick()
{
    if(!m_pDataProcess->m_bFlagNodeIdChanged||m_pDataProcess->m_ListCTId.count()==0)
        w_windowstack->setWidgetIndex(7);
}

void WMainWindow::on_vipClick()
{
    w_windowstack->setWidgetIndex(8);
}

void WMainWindow::on_fromBtnClick()
{
//    m_bFromService = !m_bFromService;
//    if(m_bFromService)
//    {
//        ui->btnFrom->setText(tr("�����"));
//        m_pDataProcess->m_iCmdType = CS_CMDTYPE_LOCAL_DATABASE_READ;
//    }
//    else
//    {
//        ui->btnFrom->setText(tr("�źŻ�"));
//        m_pDataProcess->m_iCmdType = CS_CMDTYPE_TSC_PARA_READ;
//    }
}

void WMainWindow::on_sysparaClick()
{
    w_windowstack->setWidgetIndex(10);
    dispDebugWindow();
}

void WMainWindow::on_conflictClick()
{
    w_windowstack->setWidgetIndex(11);
}

void WMainWindow::on_TrafficClick()
{
    w_windowstack->setWidgetIndex(13);
}

//���� ��0-9 ��Ӧlist 0-9
void WMainWindow::on_windowstackChange(int index)
{
    //int cnt = m_btnList.count();
    int tabIndex = ui->tabWidget->currentIndex();
    if(tabIndex<4)
    {
        if(tabIndex==0)
        {
            ui->leftWindow->setVisible(false);
        }
        else
        {
#ifndef SINGLEMODE
            ui->leftWindow->setVisible(true);
#endif
        }
        quint8 btnIndex = 0;
        for(int i=0;i<tabIndex;i++)
        {
            btnIndex+=m_ListBtnCnt[i];
        }
        quint8 cnt = m_ListBtnCnt[tabIndex];
        for(int i=0;i<cnt;i++)
        {
            m_btnList[i+btnIndex]->setDown(false);
        }
        m_btnList[index]->setDown(true);
        m_ListBtnIndex[tabIndex] = index;
    }
//    if(cnt>0)
//    {
//        for(int i=0;i<cnt;i++)
//        {
//            if(m_btnList[i]->isDown())
//            {
//                m_btnList[i]->setDown(false);
//            }
//        }
//        if(index<(cnt+1)&&index>0)//0�Ľ���û����
//        {
//            m_btnList[index-1]->setDown(true);
//        }
//    }
}

void WMainWindow::on_scheduleClick()
{
    w_windowstack->setWidgetIndex(12);
}

void WMainWindow::on_sendMessage(QByteArray byteArr, bool flag )//1115try
{
    //qDebug()<<"send message"<<len;

    {
        //qDebug()<<"data:"<<byteArr.data();
        QByteArray sendArr;
        sendArr.append(byteArr);

        //int len = sendArr.length();
        //qDebug()<<"str Len:"<<sendArr.length();

        QString str;
        str.append(sendArr.toHex());
        int cnt = str.count()/2;
        for (int i=str.size()/2; i>1; i--)
            {
                str.insert(i*2-2,' ');
            }
        //qDebug()<<"str Len:"<<str.length();
        //ui->dispDebugWindow->setText(str);
        QString headStr;

        if(flag)
        {
            headStr = QObject::tr("����:");
            headStr+=QString::number(cnt);
            ui->debugWindow->append(headStr);
//            quint8 cmd = getCmd(byteArr);
//            if(canWriteTable(cmd))
//            {
//                QString str = getTableStr(cmd);
////                m_setData->setValue(str,(QVariant)byteArr);
////                writeDataText(str.toAscii());
////                QByteArray readArr = m_setData->value(str).toByteArray();
//                qDebug()<<"writeDataText:"<<readArr.length();
//            }
        }
        else
        {
            headStr = QObject::tr("����:");
            headStr+=QString::number(cnt);
            ui->debugWindow->append(headStr);
        }
        ui->debugWindow->append(str);
    }
}

void WMainWindow::on_readCmd()
{
    QFile file("cmd.txt");
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QTextStream stream(&file);
        stream.skipWhiteSpace();

        QString cmdStr = stream.readAll();
        //cmdStr.toLatin1()
        QStringList cmdList = cmdStr.split(' ');
        int cnt = cmdList.count();
        qDebug()<<"list cnt:"<<cnt;
        bool ok;
        QByteArray cmdArr;
        for(int i=0;i<cnt;i++)
        {
            cmdArr.append(cmdList[i].toInt(&ok,16));
        }

        //QByteArray cmdArr = cmdStr.toLatin1();
        //qDebug()<<"cmdLen:"<<cmdArr.length()<<":"<<cmdArr.toHex();
        m_pDataProcess->readCmd(cmdArr);
        file.close();
    }
}

void WMainWindow::on_statusBarMessage(QString str,quint8 index)
{
    QString strErr;
    strErr = tr("ʧ��");
    bool b = true;
    if(str.right(2).compare(strErr)==0)
    {
        b = false;
    }
    if(index==0)
    {
        QPalette p = statusLabel4->palette();
        if(!b)
        {
            p.setColor(QPalette::WindowText,Qt::red);
        }
        else
        {
            p.setColor(QPalette::WindowText,Qt::black);
        }
        statusLabel4->setPalette(p);
//        ui->statusBar->showMessage(str,5000);
        statusLabel4->setText(str);
    }
    else if(index==1)
    {
        statusLabel1->setText(str);
    }
    else if(index==2)
    {
        statusLabel2->setText(str);
    }
    else if(index==3)
    {
        QPalette p = statusLabel3->palette();
        if(!b)
        {
            p.setColor(QPalette::WindowText,Qt::red);
        }
        else
        {
            p.setColor(QPalette::WindowText,Qt::black);
        }
        statusLabel3->setPalette(p);
        statusLabel3->setText(str);
    }
}

void WMainWindow::on_tabIndexChange(int index)
{
    if(index<4)//ȥ������ʱ
    {
        qDebug()<<"tab change"<<index;
        quint8 btnIndex = m_ListBtnIndex[index];
        if(btnIndex<w_windowstack->count())
            w_windowstack->setWidgetIndex(btnIndex);
    }

}
