//author: sun
//date:2011.09.29


#include "WDetectormoniter.h"
#include "ui_detectormonitor.h"
#include <QDebug>

WDetectormoniter::WDetectormoniter(QWidget *parent) :
    WPage(parent),
    ui(new Ui::DetectorMonitor)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(On_pushButton_clicked()));
}

WDetectormoniter::~WDetectormoniter()
{
    delete ui;
}

void WDetectormoniter::On_pushButton_clicked(void)
{
//    QByteArray b;
//    char temp[10] = {0};
//    b.append(temp,10);
//    b.append("0123456789");
//    qDebug() << "sending length: " << QString::number(b.size());
//    m_pDataProcess->sendMessage(b);
    QByteArray b;
    QByteArray num;
    bool ok;

    QString strtest = ui->testLineEdit->text().trimmed();
    QStringList strList = strtest.split(' ');
    for (int i =0; i<strList.size(); i++)
    {
        QString temp = strList[i];
        num = temp.toLatin1();

        b.append(num.toInt(&ok,16));
    }



    if (0>=b.size())
        return;

    m_pDataProcess->sendMessage(b);
}
