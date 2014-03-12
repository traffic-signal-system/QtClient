#include "wuserrightdlg.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
WRoleRightsDlg::WRoleRightsDlg(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("用户权限"));

    QGroupBox *rightGB = new QGroupBox(tr("权限"));
    QHBoxLayout *rightLT = new QHBoxLayout(rightGB);
    rightCB = new QCheckBox(tr("权限修改"));

    allRightsCB = new QCheckBox(tr("全选"));

    rightLT->addWidget(rightCB);
    rightLT->addWidget(allRightsCB);
    rightLT->addStretch();
    //allRightsCB->hide();

    QGroupBox *userInfoGB = new QGroupBox(tr("用户信息"));
    QHBoxLayout *userInfoLT = new QHBoxLayout(userInfoGB);
    userEditCB = new QCheckBox(tr("用户编辑"));
    userAddCB = new QCheckBox(tr("添加用户"));
    userPwdCB = new QCheckBox(tr("密码修改"));
    userTypeCB = new QCheckBox(tr("角色更改"));
    userInfoLT->addWidget(userEditCB);
    userInfoLT->addWidget(userAddCB);
    userInfoLT->addWidget(userPwdCB);
    userInfoLT->addWidget(userTypeCB);
    userInfoLT->addStretch();


    QGroupBox *nodeGB = new QGroupBox(tr("节点管理"));
    QHBoxLayout *nodeLT = new QHBoxLayout(nodeGB);
    nodeAddCB = new QCheckBox(tr("节点添加"));
    nodeEditCB = new QCheckBox(tr("节点修改"));
    nodeDelCB = new QCheckBox(tr("节点删除"));
    nodeParaSetCB = new QCheckBox(tr("节点参数表配置"));
    nodeCtlCB = new QCheckBox(tr("节点控制"));
    nodeLT->addWidget(nodeAddCB);
    nodeLT->addWidget(nodeEditCB);
    nodeLT->addWidget(nodeDelCB);
    nodeLT->addWidget(nodeParaSetCB);
    nodeLT->addWidget(nodeCtlCB);
    nodeLT->addStretch();


    QGroupBox *clusterGB = new QGroupBox(tr("群管理"));
    QHBoxLayout *clusterLT = new QHBoxLayout(clusterGB);
    clusterAddCB = new QCheckBox(tr("群添加"));
    clusterEditCB = new QCheckBox(tr("群修改"));
    clusterDelCB = new QCheckBox(tr("群删除"));
    clusterParaSetCB = new QCheckBox(tr("群参数表配置"));
    clusterCtlCB = new QCheckBox(tr("群控制"));
    clusterLT->addWidget(clusterAddCB);
    clusterLT->addWidget(clusterEditCB);
    clusterLT->addWidget(clusterDelCB);
    clusterLT->addWidget(clusterParaSetCB);
    clusterLT->addWidget(clusterCtlCB);
    clusterLT->addStretch();


    QGroupBox *domainGB = new QGroupBox(tr("域管理"));
    QHBoxLayout *domainLT = new QHBoxLayout(domainGB);
    domainAddCB = new QCheckBox(tr("域添加"));
    domainEditCB = new QCheckBox(tr("域修改"));
    domainDelCB = new QCheckBox(tr("域删除"));
    domainParaSetCB = new QCheckBox(tr("域参数表配置"));
    domainCtlCB = new QCheckBox(tr("域控制"));
    domainLT->addWidget(domainAddCB);
    domainLT->addWidget(domainEditCB);
    domainLT->addWidget(domainDelCB);
    domainLT->addWidget(domainParaSetCB);
    domainLT->addWidget(domainCtlCB);
    domainLT->addStretch();


    QGroupBox *vipGB = new QGroupBox(tr("VIP管理"));
    QHBoxLayout *vipLT = new QHBoxLayout(vipGB);
    vipAddCB = new QCheckBox(tr("VIP添加"));
    vipEditCB = new QCheckBox(tr("VIP修改"));
    vipDelCB = new QCheckBox(tr("VIP删除"));
    vipParaSetCB = new QCheckBox(tr("VIP参数表配置"));
    vipCtlCB = new QCheckBox(tr("VIP管理"));
    vipLT->addWidget(vipAddCB);
    vipLT->addWidget(vipEditCB);
    vipLT->addWidget(vipDelCB);
    vipLT->addWidget(vipParaSetCB);
    vipLT->addWidget(vipCtlCB);
    vipLT->addStretch();


    QGroupBox *logGB = new QGroupBox(tr("日志管理"));
    QHBoxLayout *logLT = new QHBoxLayout(logGB);
    userLogDelCB = new QCheckBox(tr("用户日志删除"));
    eventLogDelCB = new QCheckBox(tr("事件日志删除"));
    traficLogDelCB = new QCheckBox(tr("交通统计数据删除"));
    deviceLogDelCB = new QCheckBox(tr("设备日志删除"));
    logLT->addWidget(userLogDelCB);
    logLT->addWidget(eventLogDelCB);
    logLT->addWidget(traficLogDelCB);
    logLT->addWidget(deviceLogDelCB);
    logLT->addStretch();

    okBtn = new QPushButton(tr("确定"));
    cancelBtn = new QPushButton(tr("取消"));
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setSpacing(15);
    hLayout->addStretch();
    hLayout->addWidget(okBtn);
    hLayout->addWidget(cancelBtn);

    checkboxList.append(rightCB);

    checkboxList.append(userEditCB);
    checkboxList.append(userAddCB);
    checkboxList.append(userPwdCB);
    checkboxList.append(userTypeCB);

    checkboxList.append(nodeAddCB);
    checkboxList.append(nodeEditCB);
    checkboxList.append(nodeDelCB);
    checkboxList.append(nodeParaSetCB);
    checkboxList.append(nodeCtlCB);

    checkboxList.append(clusterAddCB);
    checkboxList.append(clusterEditCB);
    checkboxList.append(clusterDelCB);
    checkboxList.append(clusterParaSetCB);
    checkboxList.append(clusterCtlCB);

    checkboxList.append(domainAddCB);
    checkboxList.append(domainEditCB);
    checkboxList.append(domainDelCB);
    checkboxList.append(domainParaSetCB);
    checkboxList.append(domainCtlCB);

    checkboxList.append(vipAddCB);
    checkboxList.append(vipEditCB);
    checkboxList.append(vipDelCB);
    checkboxList.append(vipParaSetCB);
    checkboxList.append(vipCtlCB);

    checkboxList.append(userLogDelCB);
    checkboxList.append(eventLogDelCB);
    checkboxList.append(traficLogDelCB);
    checkboxList.append(deviceLogDelCB);

    memset(rights,0,sizeof(rights));


    int miniWidth = traficLogDelCB->width()*0.2;
    rightCB->setMinimumWidth(miniWidth);

    userEditCB->setMinimumWidth(miniWidth);
    userAddCB->setMinimumWidth(miniWidth);
    userPwdCB->setMinimumWidth(miniWidth);
    userTypeCB->setMinimumWidth(miniWidth);

    nodeAddCB->setMinimumWidth(miniWidth);
    nodeEditCB->setMinimumWidth(miniWidth);
    nodeDelCB->setMinimumWidth(miniWidth);
    nodeParaSetCB->setMinimumWidth(miniWidth);
    nodeCtlCB->setMinimumWidth(miniWidth);

    clusterAddCB->setMinimumWidth(miniWidth);
    clusterEditCB->setMinimumWidth(miniWidth);
    clusterDelCB->setMinimumWidth(miniWidth);
    clusterParaSetCB->setMinimumWidth(miniWidth);
    clusterCtlCB->setMinimumWidth(miniWidth);

    domainAddCB->setMinimumWidth(miniWidth);
    domainEditCB->setMinimumWidth(miniWidth);
    domainDelCB->setMinimumWidth(miniWidth);
    domainParaSetCB->setMinimumWidth(miniWidth);
    domainCtlCB->setMinimumWidth(miniWidth);

    vipAddCB->setMinimumWidth(miniWidth);
    vipEditCB->setMinimumWidth(miniWidth);
    vipDelCB->setMinimumWidth(miniWidth);
    vipParaSetCB->setMinimumWidth(miniWidth);
    vipCtlCB->setMinimumWidth(miniWidth);

    userLogDelCB->setMinimumWidth(miniWidth);
    eventLogDelCB->setMinimumWidth(miniWidth);
    traficLogDelCB->setMinimumWidth(miniWidth);
    deviceLogDelCB->setMinimumWidth(miniWidth);


    QGridLayout *gLayout = new QGridLayout(this);
    gLayout->addWidget(rightGB);
    gLayout->addWidget(userInfoGB);
    gLayout->addWidget(nodeGB);
    gLayout->addWidget(clusterGB);
    gLayout->addWidget(domainGB);
    gLayout->addWidget(vipGB);
    gLayout->addWidget(logGB);
    gLayout->addLayout(hLayout,7,0);

    bCreate = false;
    bAllCheck = false;

    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));
    connect(okBtn,SIGNAL(clicked()),this,SLOT(on_okBtn()));
    connect(allRightsCB,SIGNAL(clicked()),this,SLOT(on_allChenk()));
}

WRoleRightsDlg::~WRoleRightsDlg()
{
    qDebug()<<"~WUserRightsDlg";
}

void WRoleRightsDlg::setRoleRights(char *p)
{
    memcpy(rights,p,sizeof(rights));
}

void WRoleRightsDlg::setRoleRights()
{
    memset(rights,0,sizeof(rights));
    int count = checkboxList.count();
    for(int i=0;i<count;i++)
    {
        if(checkboxList[i]->isChecked())
        {
            rights[i] = 0x01;
        }
    }
}

char* WRoleRightsDlg::getRoleRights()
{
    return rights;
}

void WRoleRightsDlg::displayRoleRights()
{
    int count = checkboxList.count();
    bool bEditAble = checkboxList[0]->isChecked()?true:false;
    if(bEditAble)
    {
        for(int i=0;i<count;i++)
        {
            checkboxList[i]->setEnabled(true);
            if(rights[i]!=0)
            {
                checkboxList[i]->setCheckState(Qt::Checked);
            }
            else
            {
                checkboxList[i]->setCheckState(Qt::Unchecked);
            }
        }
    }
    else
    {
        allRightsCB->hide();
        for(int i=0;i<count;i++)
        {
            checkboxList[i]->setEnabled(false);
            if(rights[i]!=0)
            {
                checkboxList[i]->setCheckState(Qt::Checked);
            }
            else
            {
                checkboxList[i]->setCheckState(Qt::Unchecked);
            }
        }
    }

}

void WRoleRightsDlg::setCreateFlag(bool b)
{
    bCreate = b;
}

void WRoleRightsDlg::on_okBtn()
{
//    if(bCreate)
//    {
        setRoleRights();
   // }
    accept();
}

void WRoleRightsDlg::on_allChenk()
{

    bAllCheck = !bAllCheck;
    int count = checkboxList.count();
    if(bAllCheck)
    {
        for(int i=1;i<count;i++)
        {
            checkboxList[i]->setCheckState(Qt::Checked);
        }
    }
    else
    {
        for(int i=1;i<count;i++)
        {
            checkboxList[i]->setCheckState(Qt::Unchecked);
        }
    }

}
