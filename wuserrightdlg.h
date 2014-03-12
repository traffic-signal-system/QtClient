#ifndef WUSERRIGHTDLG_H
#define WUSERRIGHTDLG_H

#include <QDialog>

#include <QCheckBox>
#include <QPushButton>
#include <QList>
/*
 �û�Ȩ��
*/
class WRoleRightsDlg : public QDialog
{
    Q_OBJECT
public:
    explicit WRoleRightsDlg(QWidget *parent = 0);
    ~WRoleRightsDlg();
    void setRoleRights(char*);//����Ϊ�����û�Ȩ�� �ӷ���˶�ȡ
    void setRoleRights();//������û�ʱ�ӽ����ȡ checkboxѡ��
    char* getRoleRights();

    void displayRoleRights();//��ʾ�û�ӵ�е�Ȩ��
    void setCreateFlag(bool b=true);//�����½��û�Ȩ�ޱ�־


signals:

public slots:
    void on_okBtn();
    void on_allChenk();

private:
    QList<QCheckBox*> checkboxList;
    //QList<QCheckBox*>::Iterator it;
    char rights[32];

    QCheckBox *rightCB;
    QCheckBox *allRightsCB;//������checkboxList

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

    bool bCreate;//�½�Ȩ�ޱ�־
    bool bAllCheck;//ȫѡ��־


};

#endif // WUSERRIGHTDLG_H
