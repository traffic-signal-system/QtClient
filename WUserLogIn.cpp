//author: sun
//date:2011.09.29

#include "WUserLogIn.h"
#include "CClientService.h"
#include <QMessageBox>


WUserLogIn::WUserLogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLogIn),
    cltsvc(NULL)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);

    frameHead = NULL;
    ui->loginButton->setEnabled(false);

    bConnected = false;
    //bEnterMainWin = false;
    bLogIn = false;
    ACE_INET_Addr srvr(3000,ACE_LOCALHOST);
    const char *ip = srvr.get_host_addr();
    ui->serverIpLineEdit->setText(QString::fromAscii(ip));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(On_loginButton_clicked()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(On_exitButton_clicked()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(On_connectButton_clicked()));
    ui->groupBox->hide();

}

WUserLogIn::~WUserLogIn()
{
    qDebug()<<"~WUserLogIn";
    delete ui;
}


void WUserLogIn::On_exitButton_clicked(void)
{
    qDebug()<<"exit Btn";
//    if(cltsvc)
//        cltsvc->disconnect();

    reject();
}

void WUserLogIn::On_connectButton_clicked(void)
{
//    accept();
    if(!bConnected)
    {
        QString strIp   = ui->serverIpLineEdit->text();
        QString strPort = ui->portLineEdit->text();
        m_pDataProcess->setServiceInfo(strIp,strPort);
        if(cltsvc->connectTo(strIp, strPort))
        {
            bConnected = true;
            //ui->connectButton->setEnabled(false);
            ui->connectButton->setText(tr("断开连接"));
            ui->loginButton->setEnabled(true);
            ui->loginButton->click();
        }
        else
        {
            QMessageBox::warning(this,tr("连接失败"),tr("请检查服务端地址及端口"),QMessageBox::Ok);
        }
        qDebug() << "ip:" << strIp << " port:" << strPort;
    }
    else
    {
        bConnected = false;
        ui->loginButton->setEnabled(false);
        cltsvc->disconnect();
        ui->connectButton->setText(tr("连接"));
    }

}

void WUserLogIn::On_loginButton_clicked(void)
{
    //bEnterMainWin = true;
    QByteArray sendArray;
    if(!bLogIn)
    {
        //用户登录
        QByteArray nameArray = ui->userNameEdit->text().toLocal8Bit();
        QByteArray pwdArray  = ui->passwordEdit->text().toAscii();
        byte nameLen = (byte)nameArray.length();
        byte pwdLen = (byte)pwdArray.length();


        int type = CS_CMDTYPE_USR_REQUEST;
        int num = 0;
        int size = nameLen+pwdLen+4;
    //    frameHead = m_pDataProcess->htonlHead(type,num,size);

    //    sendArray.append((const char*)frameHead,sizeof(SUtcsFrameHead));
        sendArray.append(byte(USER_IN));
        sendArray.append((char)DATA_TYPE_PARA);//参数1
        sendArray.append(nameLen);
        sendArray.append(nameArray);
        sendArray.append(pwdLen);
        sendArray.append(pwdArray);
        //cltsvc->sendData(sendArray);
        if(!m_pDataProcess->sendMessage(type,num,size,sendArray))
        {
            QMessageBox::warning(this,tr("发送消息失败"),tr("发送失败"),QMessageBox::Ok);
        }
//        else
//        {
//            bLogIn = true;
//            ui->loginButton->setText(tr("注销"));
//        }
    }
    else
    {
        //用户注销
        int type = CS_CMDTYPE_USR_REQUEST;
        int num = 0;
        int size = 2;
        sendArray.append(byte(USER_OUT));//command
        sendArray.append((char)DATA_TYPE_PARA);//para 1;

        if(m_pDataProcess->sendMessage(type,num,size,sendArray))
        {
            ui->userNameEdit->clear();
            ui->passwordEdit->clear();
            bLogIn = false;
            ui->loginButton->setText(tr("登录"));
        }
    }


    //try
//    accept();
}

void WUserLogIn::setConnected()
{
    //ui->connectButton->setEnabled(false);
}

void WUserLogIn::setClientService(CClientService *svc)
{
    cltsvc = svc;
    connect(cltsvc, SIGNAL(connected(bool)), this, SLOT(setConnectStatus(bool)));

}

void WUserLogIn::setDataProcess(PDataProcess *dp)
{
    m_pDataProcess = dp;
    connect(m_pDataProcess, SIGNAL(receivedUserLogin(char*,int)), this, SLOT(checkLogInStatus(char*,int)));
}

void WUserLogIn::setConnectStatus(bool bStatus)
{
   // if (bStatus)
        //ui->connectButton->setEnabled(false);
    ui->connectButton->setText(tr("连接"));
    bConnected = bStatus;
}

void WUserLogIn::checkLogInStatus(char*received,int len)
{
    qDebug()<<"deal login data";
    QString errStr;
    char *rcv = new char[len];
    memcpy(rcv,received,len);
    byte code = *(rcv+1);
    qDebug()<<"rcv"<<rcv;
    switch(code)
    {
    case CS_ERRTYPE_RIGHT:
        bLogIn = true;
        ui->loginButton->setText(tr("注销"));
        accept();
        qDebug()<<"accept";
        return;
    case CS_ERRTYPE_PACK:
        errStr = QObject::tr("数据格式错误！");
        break;
    case CS_ERRTYPE_USER:
        errStr = QObject::tr("用户名错误！");
        break;
    case CS_ERRTYPE_PWD:
        errStr = QObject::tr("密码错误！");
        break;
    case CS_ERRTYPE_NEEDLOGIN:
        errStr = QObject::tr("请用用户名及密码登陆！");
        break;
    case CS_ERRTYPE_MORELOGIN:
        errStr = QObject::tr("超出服务最大用户数！");
        break;
    case CS_ERRTYPE_HAVELOGIN:
        errStr = QObject::tr("此用户已登陆！");
        break;

    default:
        errStr = QObject::tr("未知错误！");
        break;
    }
    QMessageBox::warning(this,tr("登陆失败"),errStr,QMessageBox::Ok);
    delete[] rcv;

}
