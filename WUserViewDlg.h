#ifndef WUSERVIEWDLG_H
#define WUSERVIEWDLG_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include "WUserEditDlg.h"

/*
 �û��鿴����
*/
class WUserViewDlg:public QDialog
{
    Q_OBJECT
public:
    WUserViewDlg(QWidget* parent=0);
    //~WUserViewDlg();

    void setModelData();
    void setDataProcess(PDataProcess *dp);
    void requireAllUserTable();//��ȡ��������ݿ��û��б�
    void requireOnlineUserTable();//��ȡ��������ݿ������û��б�
    void initViewData();

private slots:
    void on_addUserBtn();
    void on_editUserBtn();
    void on_quitUserBtn();
    void on_delUserBtn();
    void on_refreshBtn();
    void dealReceivedMessage(char*,int);

private:
    QPushButton* addUserBtn;
    QPushButton* editUserBtn;
    QPushButton* delUserBtn;
    QPushButton* quitUserBtn;
    QPushButton* refreshBtn;

    QStandardItemModel *model;
    QTableView* userView;

    WUserEditDlg *editUserDlg;
    PDataProcess *m_pDataProcess;
};

#endif // WUSERVIEWDLG_H
