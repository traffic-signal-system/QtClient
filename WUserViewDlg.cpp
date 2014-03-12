#include "WUserViewDlg.h"
#include <QHBoxLayout>
#include <QGridLayout>

WUserViewDlg::WUserViewDlg(QWidget *parent):QDialog(parent)
{
    addUserBtn = new QPushButton(tr("添加用户"));
    editUserBtn = new QPushButton(tr("编辑用户"));
    delUserBtn = new QPushButton(tr("删除用户"));
    quitUserBtn = new QPushButton(tr("强制下线"));
    refreshBtn = new QPushButton(tr("刷    新"));

    model = new QStandardItemModel();

    userView = new QTableView;
    userView->setMinimumSize(550,200);
    userView->setModel(model);
    userView->setSelectionBehavior(QAbstractItemView::SelectRows);

    editUserDlg = new WUserEditDlg(this);
    m_pDataProcess = NULL;

    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
    model->setHeaderData(2,Qt::Horizontal,tr("类型"));
    model->setHeaderData(3,Qt::Horizontal,tr("过期时间"));
    model->setHeaderData(4,Qt::Horizontal,tr("是否在线"));


    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch();
    hLayout->addWidget(addUserBtn);
    hLayout->addWidget(editUserBtn);
    hLayout->addWidget(delUserBtn);
    hLayout->addWidget(quitUserBtn);
    hLayout->addWidget(refreshBtn);
    hLayout->addStretch();

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addStretch();
    hLayout1->addWidget(userView);
    hLayout1->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(hLayout1);
    mainLayout->addStretch();
//    QGridLayout *gLayout = new QGridLayout(this);
//    gLayout->addLayout(hLayout,0,0);
//    gLayout->addWidget(userView);


    connect(addUserBtn,SIGNAL(clicked()),this,SLOT(on_addUserBtn()));
    connect(editUserBtn,SIGNAL(clicked()),this,SLOT(on_editUserBtn()));
    connect(delUserBtn,SIGNAL(clicked()),this,SLOT(on_delUserBtn()));
    connect(quitUserBtn,SIGNAL(clicked()),this,SLOT(on_quitUserBtn()));
    connect(refreshBtn,SIGNAL(clicked()),this,SLOT(on_refreshBtn()));
}

void WUserViewDlg::initViewData()
{
    if(m_pDataProcess!=NULL)
    {
        requireAllUserTable();
//        requireOnlineUserTable();
    }
}

void WUserViewDlg::setModelData()
{
    //model->setData();
}

void WUserViewDlg::setDataProcess(PDataProcess *dp)
{
    m_pDataProcess = dp;
    editUserDlg->setDataProcess(dp);
    connect(dp,SIGNAL(receivedUserView(char*,int)),this,SLOT(dealReceivedMessage(char*,int)));
}

void WUserViewDlg::requireAllUserTable()
{
    int type = CS_CMDTYPE_USR_REQUEST;//用户操作请求 CS_CMDTYPE_LOCAL_DATABASE_READ;
    int num = 0;
    int size = 3;//数据长度
    QByteArray sendArr;
    //sendArr.append(char(LOCAL_TABLE_USERINFO));//命令值
    sendArr.append(char(USER_READ));
    sendArr.append(char(0));//参数1

    m_pDataProcess->sendMessage(type,num,size,sendArr);
}

void WUserViewDlg::requireOnlineUserTable()
{
//    int type = CS_CMDTYPE_LOCAL_DATABASE_READ;
//    int num = 0;
//    int size = 12+3;
//    QByteArray sendArr;
//    sendArr.append(char(0));//参数1
//    sendArr.append(char(LOCAL_TABLE_USERINFO));//参数2
//    m_pDataProcess->sendMessage(type,num,size,sendarr);
}


void WUserViewDlg::on_addUserBtn()
{

    editUserDlg->show();
    editUserDlg->setCreateFlag(true);
}

void WUserViewDlg::on_editUserBtn()
{
    editUserDlg->show();
    editUserDlg->setCreateFlag(false);
}

void WUserViewDlg::on_quitUserBtn()
{
}

void WUserViewDlg::on_delUserBtn()
{
}

void WUserViewDlg::dealReceivedMessage(char* para1,int len)
{
    qDebug()<<"deal userview data";
    char *rcv = new char[len];
    memcpy(rcv,para1,len);
    //int userNum = *rcv;
    //SUtcsAllUserInfo *userInfo = (SUtcsAllUserInfo *)++rcv;
    delete[] rcv;

}

void WUserViewDlg::on_refreshBtn()
{
    this->initViewData();
}
