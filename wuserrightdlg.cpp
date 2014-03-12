#include "wuserrightdlg.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
WRoleRightsDlg::WRoleRightsDlg(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("�û�Ȩ��"));

    QGroupBox *rightGB = new QGroupBox(tr("Ȩ��"));
    QHBoxLayout *rightLT = new QHBoxLayout(rightGB);
    rightCB = new QCheckBox(tr("Ȩ���޸�"));

    allRightsCB = new QCheckBox(tr("ȫѡ"));

    rightLT->addWidget(rightCB);
    rightLT->addWidget(allRightsCB);
    rightLT->addStretch();
    //allRightsCB->hide();

    QGroupBox *userInfoGB = new QGroupBox(tr("�û���Ϣ"));
    QHBoxLayout *userInfoLT = new QHBoxLayout(userInfoGB);
    userEditCB = new QCheckBox(tr("�û��༭"));
    userAddCB = new QCheckBox(tr("����û�"));
    userPwdCB = new QCheckBox(tr("�����޸�"));
    userTypeCB = new QCheckBox(tr("��ɫ����"));
    userInfoLT->addWidget(userEditCB);
    userInfoLT->addWidget(userAddCB);
    userInfoLT->addWidget(userPwdCB);
    userInfoLT->addWidget(userTypeCB);
    userInfoLT->addStretch();


    QGroupBox *nodeGB = new QGroupBox(tr("�ڵ����"));
    QHBoxLayout *nodeLT = new QHBoxLayout(nodeGB);
    nodeAddCB = new QCheckBox(tr("�ڵ����"));
    nodeEditCB = new QCheckBox(tr("�ڵ��޸�"));
    nodeDelCB = new QCheckBox(tr("�ڵ�ɾ��"));
    nodeParaSetCB = new QCheckBox(tr("�ڵ����������"));
    nodeCtlCB = new QCheckBox(tr("�ڵ����"));
    nodeLT->addWidget(nodeAddCB);
    nodeLT->addWidget(nodeEditCB);
    nodeLT->addWidget(nodeDelCB);
    nodeLT->addWidget(nodeParaSetCB);
    nodeLT->addWidget(nodeCtlCB);
    nodeLT->addStretch();


    QGroupBox *clusterGB = new QGroupBox(tr("Ⱥ����"));
    QHBoxLayout *clusterLT = new QHBoxLayout(clusterGB);
    clusterAddCB = new QCheckBox(tr("Ⱥ���"));
    clusterEditCB = new QCheckBox(tr("Ⱥ�޸�"));
    clusterDelCB = new QCheckBox(tr("Ⱥɾ��"));
    clusterParaSetCB = new QCheckBox(tr("Ⱥ����������"));
    clusterCtlCB = new QCheckBox(tr("Ⱥ����"));
    clusterLT->addWidget(clusterAddCB);
    clusterLT->addWidget(clusterEditCB);
    clusterLT->addWidget(clusterDelCB);
    clusterLT->addWidget(clusterParaSetCB);
    clusterLT->addWidget(clusterCtlCB);
    clusterLT->addStretch();


    QGroupBox *domainGB = new QGroupBox(tr("�����"));
    QHBoxLayout *domainLT = new QHBoxLayout(domainGB);
    domainAddCB = new QCheckBox(tr("�����"));
    domainEditCB = new QCheckBox(tr("���޸�"));
    domainDelCB = new QCheckBox(tr("��ɾ��"));
    domainParaSetCB = new QCheckBox(tr("�����������"));
    domainCtlCB = new QCheckBox(tr("�����"));
    domainLT->addWidget(domainAddCB);
    domainLT->addWidget(domainEditCB);
    domainLT->addWidget(domainDelCB);
    domainLT->addWidget(domainParaSetCB);
    domainLT->addWidget(domainCtlCB);
    domainLT->addStretch();


    QGroupBox *vipGB = new QGroupBox(tr("VIP����"));
    QHBoxLayout *vipLT = new QHBoxLayout(vipGB);
    vipAddCB = new QCheckBox(tr("VIP���"));
    vipEditCB = new QCheckBox(tr("VIP�޸�"));
    vipDelCB = new QCheckBox(tr("VIPɾ��"));
    vipParaSetCB = new QCheckBox(tr("VIP����������"));
    vipCtlCB = new QCheckBox(tr("VIP����"));
    vipLT->addWidget(vipAddCB);
    vipLT->addWidget(vipEditCB);
    vipLT->addWidget(vipDelCB);
    vipLT->addWidget(vipParaSetCB);
    vipLT->addWidget(vipCtlCB);
    vipLT->addStretch();


    QGroupBox *logGB = new QGroupBox(tr("��־����"));
    QHBoxLayout *logLT = new QHBoxLayout(logGB);
    userLogDelCB = new QCheckBox(tr("�û���־ɾ��"));
    eventLogDelCB = new QCheckBox(tr("�¼���־ɾ��"));
    traficLogDelCB = new QCheckBox(tr("��ͨͳ������ɾ��"));
    deviceLogDelCB = new QCheckBox(tr("�豸��־ɾ��"));
    logLT->addWidget(userLogDelCB);
    logLT->addWidget(eventLogDelCB);
    logLT->addWidget(traficLogDelCB);
    logLT->addWidget(deviceLogDelCB);
    logLT->addStretch();

    okBtn = new QPushButton(tr("ȷ��"));
    cancelBtn = new QPushButton(tr("ȡ��"));
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
