//author: kang
//date:2011.09.29


#include "CClientService.h"
#include <qendian.h>

CClient_Svc_Handler::CClient_Svc_Handler()
{

}

int CClient_Svc_Handler::open(void*)
{
    ACE_OS::printf("\nConnection established\n");

    //注册相应事件
    ACE_Reactor::instance()->register_handler(this,
        ACE_Event_Handler::READ_MASK);
    return 0;
}

int CClient_Svc_Handler::handle_input(ACE_HANDLE)
{
    qDebug()<<"handle input";
    //char buff[RCV_BUFF_SIZE];
    memset(data,0,RCV_BUFF_SIZE);
    int rev = peer().recv(data,RCV_BUFF_SIZE-1);
    if(rev == 0)
    {
        //delete this;
        return -1;
    }
    else if(rev==-1)
    {
        qDebug()<<"connect is false";
        cltsvc->emitConnectSignal(false);
        return -1;
    }
    else
    {
        ACE_OS::printf("<<rev:\t %s\n",data);
        qDebug() << "received:"<<rev;
        if (cltsvc/*&&m_bFlagComplete*/)
        {

            data[rev] = '\0';

           // qDebug() << "emitReceivedSignal"<<"len:"<<rev<<" data:"<<data;
            cltsvc->emitReceivedSignal(data, rev);
//            m_iComplete = 0;
//            m_iDataLong = 0;

        }
        return 0;
    }
}

int CClient_Svc_Handler::sendData(const char *msg, int len)
{
    ACE_OS::printf("<<send:\t %s\n",msg);
    qDebug()<<"send msg"<<len;
    return peer().send(msg,len);//strlen(msg));
}


void CClient_Svc_Handler::setClientService(CClientService *svr)
{
    cltsvc = svr;
}

/******************************************/
void handlerThread::run()
{
    qDebug()<<"thread run";
    ACE_Reactor::instance()->run_reactor_event_loop();
}

void handlerThread::stop()
{
    ACE_Reactor::instance()->end_reactor_event_loop();
    qDebug()<<"thread quit";
    this->quit();

}


/******************************************/
void bcThread::run()
{
    qDebug()<<"broadcast run true";
    ACE_INET_Addr addr(9999),remote;

    udp.open(addr);

    this->sendMess();

    char buf[64];
    while(true)
    {
       int size = udp.recv(buf,64,remote);
       buf[size] = 0;
       if(size>0)
       {
           qDebug()<<"size>0"<<":"<<remote.get_host_addr()<<":"<<remote.get_port_number();


//           memcpy(&ip,buf,4);
//           quint32 hostIp = qFromBigEndian<quint32>(ip);
           QString strIp;
           quint8 ip1 = *(buf+0);
           quint8 ip2 = *(buf+1);
           quint8 ip3 = *(buf+2);
           quint8 ip4 = *(buf+3);

           strIp.append(QString::number(ip1));
           strIp.append(".");
           strIp.append(QString::number(ip2));
           strIp.append(".");
           strIp.append(QString::number(ip3));
           strIp.append(".");
           strIp.append(QString::number(ip4));

           QString str;
           str.append(strIp);
           str.append(",");
           quint32 port = 0;
           memcpy(&port,buf+4,4);
           quint32 hostPort = qFromBigEndian<quint32>(port);
           str.append(QString::number(hostPort));
           str.append(",");

           QString version;

           version.append(QString::number(*(buf+8)));
           version.append(".");
           version.append(QString::number(*(buf+9)));
           version.append(".");
           version.append(QString::number(*(buf+10)));

           str.append(version);
           emit rcvTscInfo(str);
       }
    }
    qDebug()<<"broadcast run m_bFlag false";
}

void bcThread::stop()
{
    qDebug()<<"broadcast stop false";
//    m_bFlag = false;

    this->quit();
}

void bcThread::sendMess()
{
    udp.send("123456",6,8808);
}

/*******************************************/

CClientService::CClientService(QObject *parent) :
        QObject(parent)
{
    clientHandler = NULL;
    qDebug()<<"new handler";

    bConnected = false;
    connect(this,SIGNAL(connected(bool)),this,SLOT(slot_Disconn(bool)));
    connect(&bcthread,SIGNAL(rcvTscInfo(QString)),this,SLOT(on_rcvTscInfo(QString)));
}

CClientService::~CClientService()
{
    qDebug()<<"~CClientService";
    thread.stop();
    bcthread.stop();
    if(clientHandler!=NULL)
    {
        this->disconnect();

    }
}

bool CClientService::connectTo(QString IP, QString port)
{
    if(clientHandler==NULL)
    {
        clientHandler = new CClient_Svc_Handler();
        clientHandler->setClientService(this);
    }

        ACE_INET_Addr addr(port.toInt(),IP.toLatin1().data());
        clientHandler = new CClient_Svc_Handler();
        clientHandler->setClientService(this);
        qDebug()<<"clientHandler:"<<clientHandler<<addr.get_addr();
        CClient_Connector connector;
        if(-1==connector.connect(clientHandler,addr))
        {
            bConnected = false;
            emit connected(false);
            return false;
        }
        else
        {
            qDebug()<<"connect succ";
            bConnected = true;
            thread.start();
            emit connected(true);
            return true;
        }

}

int CClientService::sendData(const QByteArray &byteArr)
{
    if(bConnected)
    {
        int send = clientHandler->sendData(byteArr.data(), byteArr.size());
        if(send)
        {
            emit sendToService( byteArr,true);//1115try
        }
        return send;
    }
    else
    {
        return 0;
    }
}

bool CClientService::disconnect()
{

    if(clientHandler!=NULL)
    {
        if(bConnected)
        {
            //qDebug()<<"disconnect";
            qDebug()<<"stop thread";
            //thread.stop();
            bConnected = false;


            //connector.close();
            qDebug()<<"delete connector";
            //delete connector;
            qDebug()<<"handler close"<<clientHandler;
            //clientHandler->handle_close(clientHandler);
            delete clientHandler;
            clientHandler = NULL;
        }
    }

    return true;
}

void CClientService::slot_Disconn(bool b)
{
    if(!b)
    {qDebug()<<"on emit connect false";
       // disconnect();
        bConnected = false;
        if(thread.isRunning())
        {
            thread.stop();
            qDebug()<<clientHandler<<"thread:"<<thread.isRunning();
        }
        //clientHandler = NULL;

    }
}

void CClientService::on_rcvTscInfo(QString str)
{
    qDebug()<<"CClientService on_rcvTscInfo"<<str;
    emit rcvTscInfo(str);
}

void CClientService::emitReceivedSignal(char *pData, int len)
{
    QByteArray byteArray(pData, len);
    emit received(byteArray);
}

void CClientService::startBroadCast(bool b)
{
    qDebug()<<"CClientService::startBroadCast b"<<b<<"bcthread.isRunning()"<<bcthread.isRunning();

    if(!bcthread.isRunning())
    {
        bcthread.start();
    }
    else
    {
       bcthread.sendMess();
    }
//    else
//    {
//        bcthread.stop();
//    }
}

void CClientService::emitConnectSignal(bool b)
{
    emit connected(b);
}
