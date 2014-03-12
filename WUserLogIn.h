//author: sun
//date:2011.09.29

#ifndef WUSERLOGIN_H
#define WUSERLOGIN_H

#include <QDialog>
#include "ui_usrlogin.h"

#include "DCommon.h"
#include "pdataprocess.h"


/*
 用户名登录界面
*/
namespace Ui {
    class UserLogIn;
}

class CClientService;

class WUserLogIn : public QDialog
{
    Q_OBJECT
public:
    explicit WUserLogIn(QWidget *parent = 0);

    ~WUserLogIn();

    void setClientService(CClientService *svc);
    void setDataProcess(PDataProcess *dp);


private :

signals:

public slots:

    void On_connectButton_clicked(void);
private slots:
    void setConnected();
    void On_exitButton_clicked(void);
    void On_loginButton_clicked(void);
    void setConnectStatus(bool bStatus);
    void checkLogInStatus(char*rcv,int len);

private :
    Ui::UserLogIn *ui;

    CClientService *cltsvc;
    PDataProcess *m_pDataProcess;
    SUtcsFrameHead *frameHead;

    bool bConnected;
    //bool bEnterMainWin;
    bool bLogIn;

};

#endif // WUSERLOGIN_H
