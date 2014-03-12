#ifndef WUSERRIGHTDLG_H
#define WUSERRIGHTDLG_H

#include <QDialog>

#include <QCheckBox>
#include <QPushButton>
#include <QList>
/*
 用户权限
*/
class WRoleRightsDlg : public QDialog
{
    Q_OBJECT
public:
    explicit WRoleRightsDlg(QWidget *parent = 0);
    ~WRoleRightsDlg();
    void setRoleRights(char*);//更改为设置用户权限 从服务端读取
    void setRoleRights();//添加新用户时从界面读取 checkbox选择
    char* getRoleRights();

    void displayRoleRights();//显示用户拥有的权限
    void setCreateFlag(bool b=true);//设置新建用户权限标志


signals:

public slots:
    void on_okBtn();
    void on_allChenk();

private:
    QList<QCheckBox*> checkboxList;
    //QList<QCheckBox*>::Iterator it;
    char rights[32];

    QCheckBox *rightCB;
    QCheckBox *allRightsCB;//不放入checkboxList

    QCheckBox *userEditCB;
    QCheckBox *userAddCB;
    QCheckBox *userPwdCB;
    QCheckBox *userTypeCB;

    QCheckBox *nodeAddCB;
    QCheckBox *nodeEditCB;
    QCheckBox *nodeDelCB;
    QCheckBox *nodeParaSetCB;
    QCheckBox *nodeCtlCB;

    QCheckBox *clusterAddCB;
    QCheckBox *clusterEditCB;
    QCheckBox *clusterDelCB;
    QCheckBox *clusterParaSetCB;
    QCheckBox *clusterCtlCB;

    QCheckBox *domainAddCB;
    QCheckBox *domainEditCB;
    QCheckBox *domainDelCB;
    QCheckBox *domainParaSetCB;
    QCheckBox *domainCtlCB;

    QCheckBox *vipAddCB;
    QCheckBox *vipEditCB;
    QCheckBox *vipDelCB;
    QCheckBox *vipParaSetCB;
    QCheckBox *vipCtlCB;

    QCheckBox *userLogDelCB;
    QCheckBox *eventLogDelCB;
    QCheckBox *traficLogDelCB;
    QCheckBox *deviceLogDelCB;

    QPushButton *okBtn;
    QPushButton *cancelBtn;

    bool bCreate;//新建权限标志
    bool bAllCheck;//全选标志


};

#endif // WUSERRIGHTDLG_H
