//author: sun
//date:2011.09.29


#include <QtGui/QApplication>
#include "WMainwindow.h"
#include "WUserLogIn.h"
#include <QTextCodec>
#include <QFrame>

#include "PDataProcess.h"
#include "CClientService.h"



int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    CClientService clientservice;

    QApplication a(argc, argv);    
    PDataProcess processor(&clientservice);
    WMainWindow w;
    w.setProcessor(&processor);
//    QFrame *f = new QFrame(&w);

//    f->setFrameStyle(QFrame::Panel|QFrame::Raised);

    WUserLogIn wLogIn(&w);
    wLogIn.setClientService(&clientservice);
    wLogIn.setDataProcess(&processor);

    w.setUserLogIn(&wLogIn);

    //WTimeBaseDlg *tb = new WTimeBaseDlg;//1102try


    if(QDialog::Accepted == wLogIn.exec())
    {
//        wLogIn.On_connectButton_clicked();
        w.show();
        processor.requireVipInfoTable();
    }
    else
    {
        wLogIn.hide();
        //qDebug()<<"wLogIn"<<wLogIn;
        //delete wLogIn;

       qApp->quit();
       return 0;
    }

    return a.exec();
}

