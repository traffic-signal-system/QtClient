//author: kang
//date:2011.09.29


#ifndef CCLIENTSERVICE_H
#define CCLIENTSERVICE_H

#include "ace/Reactor.h"
#include "ace/Svc_Handler.h"
#include "ace/Connector.h"
#include "ace/Synch.h"
#include "ace/SOCK_Connector.h"
#include <QThread>
#include <QDebug>
#include <QObject>

#include <ace/SOCK_Dgram_Bcast.h>

class CClientService;

class CClient_Svc_Handler:
    public ACE_Svc_Handler <ACE_SOCK_STREAM,ACE_NULL_SYNCH>
{
public:
    CClient_Svc_Handler();
    int open(void*);

    int handle_input(ACE_HANDLE);

    int sendData(const char *msg, int len);

    void setClientService(CClientService *svr);

private:
    enum{RCV_BUFF_SIZE = 8192};
    char data[RCV_BUFF_SIZE];
    //char buff[RCV_BUFF_SIZE];
//    int m_iComplete;
//    int m_iDataLong;
//    bool m_bFlagComplete;
    CClientService *cltsvc;

};


typedef ACE_Connector<CClient_Svc_Handler,ACE_SOCK_CONNECTOR> CClient_Connector;


/**********************************************/

class handlerThread:public QThread
{
    Q_OBJECT
public:
    void run();
    void stop();
};

class bcThread:public QThread
{
    Q_OBJECT
signals:
    void rcvTscInfo(QString str);
public:
    void run();
    void stop();
    void sendMess();
    ACE_SOCK_Dgram_Bcast udp;
};

/*********************************************/


class CClientService: public QObject
{
    Q_OBJECT
public:
    CClientService(QObject *parent = 0);
    ~CClientService();
    bool connectTo (QString IP="localhost", QString port="3000");
    int  sendData(const QByteArray &byteArr);
    bool disconnect();
    void emitReceivedSignal(char *pData, int len);
    void startBroadCast(bool b);

    void emitConnectSignal(bool b);

public slots:
    void slot_Disconn(bool b);
    void on_rcvTscInfo(QString str);

signals:
    void connected(bool);
    void received(QByteArray byteArr);
    void sendToService(QByteArray byteArr,bool);//try
    void rcvTscInfo(QString);

private:
    CClient_Svc_Handler *clientHandler;
    //CClient_Connector *connector;
    handlerThread thread;
    bool bConnected;
    bcThread bcthread;

};



#endif // CCLIENTSERVICE_H
