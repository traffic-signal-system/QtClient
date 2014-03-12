#include "WUserEditDlg.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QDateTime>
#include <QFileDialog>
#include <QObject>
#include <QPicture>
#include <QPalette>
#include <QMatrix>
#include <QPainter>
#include <QMessageBox>
#include <QDir>
//#include "DTable.h"



ImageDlg::ImageDlg(QWidget *parent):QDialog(parent)
{
   //p = NULL;

    bPaint = false;
    this->setMinimumHeight(100);
    this->setBackgroundRole(QPalette::WindowText);
}

void ImageDlg::setPixPath(QString path)
{
    if(path!=NULL)
    {
        bPaint = true;
        p.load(path);
        this->update();
    }

}

void ImageDlg::paintEvent(QPaintEvent *)
{
     QPainter paint(this);

    if(bPaint)
    {

        p.scaled(100,100);

        paint.drawPixmap(0,0,100,100,p);
    }
    else
    {
        QBrush brush(Qt::white);
        paint.setBrush(brush);
        //paint.drawPixmap(0,0,100,100,QPixmap::QPixmap(100,100));
        paint.drawRect(0,0,100,100);

    }

}

WUserEditDlg::WUserEditDlg(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("�༭�û�"));
   QLabel *userIDLabel = new QLabel(tr("�û�ID��"));
   userIDLabel->setAlignment(Qt::AlignRight);
   userIDLineEdit = new QLineEdit;
   QLabel *userNameLabel = new QLabel(tr("�û�����"));
   userNameLabel->setAlignment(Qt::AlignRight);
   userNameLineEdit = new QLineEdit;
   QLabel *userPwdLabel = new QLabel(tr("�û����룺"));
   userPwdLabel->setAlignment(Qt::AlignRight);

   userPwdLineEdit = new QLineEdit;

   QLabel *checkPwdLabel = new QLabel(tr("����ȷ�ϣ�"));
   checkPwdLabel->setAlignment(Qt::AlignRight);

   checkPwdLineEdit = new QLineEdit;

   userPwdLineEdit->setEchoMode(QLineEdit::Password);
   checkPwdLineEdit->setEchoMode(QLineEdit::Password);
   //QLabel *userTypeLabel = new QLabel(tr("�û����ͣ�"));
   QLabel *userTypeLabel = new QLabel(tr("�û�Ȩ�ޣ�"));
   userTypeLabel->setAlignment(Qt::AlignRight);
    userRightsBtn = new QPushButton(tr("Ȩ����ʾ"));
//   userTypeComboBox = new QComboBox;
//   userTypeComboBox->addItem(tr("����Ա"));
//   userTypeComboBox->addItem(tr("�߼��û�"));
//   userTypeComboBox->addItem(tr("��ͨ�û�"));

   QLabel *userValidTimeLabel = new QLabel(tr("����ʱ�䣺"));
   userValidTimeLabel->setAlignment(Qt::AlignRight);

   //QLineEdit *userValidTimeLineEdit = new QLineEdit;
   edit = new QDateEdit;
   edit->setDisplayFormat("yyyy-MM-dd");
   edit->setCalendarPopup(true);
   edit->setDateTime(QDateTime::currentDateTime());


   QLabel *imageLabel = new QLabel(tr("ͷ��"));
   imageLabel->setAlignment(Qt::AlignRight);

   imageLineEdit = new QLineEdit;
   browseBtn = new QPushButton(tr("���"));



   image = new ImageDlg;

   okBtn = new QPushButton(tr("ȷ��"));
   cancelBtn = new QPushButton(tr("ȡ��"));

   QGridLayout *gLayout = new QGridLayout;
   int row = 0;
   gLayout->addWidget(userIDLabel,row,0);
   gLayout->addWidget(userIDLineEdit,row,1);
   gLayout->addWidget(userNameLabel,++row,0);
   gLayout->addWidget(userNameLineEdit,row,1);
   gLayout->addWidget(userPwdLabel,++row,0);
   gLayout->addWidget(userPwdLineEdit,row,1);

   gLayout->addWidget(checkPwdLabel,++row,0);
   gLayout->addWidget(checkPwdLineEdit,row,1);

   gLayout->addWidget(userTypeLabel,++row,0);
   //gLayout->addWidget(userTypeComboBox,row,1);
   gLayout->addWidget(userRightsBtn,row,1);
   gLayout->addWidget(userValidTimeLabel,++row,0);
   gLayout->addWidget(edit,row,1);
   gLayout->addWidget(imageLabel,++row,0);
   gLayout->addWidget(imageLineEdit,row,1,1,2);
   gLayout->addWidget(browseBtn,row,3);


   gLayout->addWidget(image,++row,1,5,1);



   QHBoxLayout *hLayout = new QHBoxLayout;
   hLayout->setSpacing(10);
   hLayout->addStretch();
   hLayout->addWidget(okBtn);
   hLayout->addWidget(cancelBtn);
   hLayout->addStretch();

   QVBoxLayout *vLayout = new QVBoxLayout(this);

   vLayout->addLayout(gLayout);
   vLayout->addLayout(hLayout);

   userRightsDlg = new WRoleRightsDlg;
   bCreate = false;
   memset(rights,0,sizeof(rights));

   connect(userRightsBtn,SIGNAL(clicked()),this,SLOT(on_userRightsBtn()));

   connect(browseBtn,SIGNAL(clicked()),this,SLOT(on_browseBtn()));
   connect(cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));
   connect(okBtn,SIGNAL(clicked()),this,SLOT(on_okBtn()));
}

WUserEditDlg::~WUserEditDlg()
{
    qDebug()<<"~WUserEditDlg";
}

void WUserEditDlg::setDataProcess(PDataProcess*dp)
{
    m_pDataProcess = dp;
}

void WUserEditDlg::setCreateFlag(bool b)
{
    if(b)
    {
        setWindowTitle(tr("������û�"));
        userIDLineEdit->setEnabled(true);
    }
    else
    {
        setWindowTitle(tr("�༭�û�"));
        userIDLineEdit->setEnabled(false);//ID���ɱ༭
    }
    bCreate = b;
    userRightsDlg->setCreateFlag(b);
}
void WUserEditDlg::sendMessage()
{
    int type = CS_CMDTYPE_USR_REQUEST;//�û���������
    int num = 0;
    int size = 1+1+sizeof(SUtcsAllUserInfo);

    SUtcsAllUserInfo userInfo;

    QByteArray sendArr;
    if(bCreate)
    {
        sendArr.append(char(USER_ADD));
    }
    else
    {
        sendArr.append(char(USER_UPDATE));
    }
    sendArr.append(char(DATA_TYPE_PARA));//����1
    sendArr.append((char*)(&userInfo),sizeof(SUtcsAllUserInfo));
    m_pDataProcess->sendMessage(type,num,size,sendArr);

}


void WUserEditDlg::on_browseBtn()
{

    QString path = QFileDialog::getOpenFileName(this,QObject::tr("ͷ��ѡ��"),QDir::currentPath()/*"/home/kwq/practice/"*/,QObject::tr("Images (*.png *.xpm *.jpg)"));
    imageLineEdit->setText(path);
    if(path!=NULL)
    {
        image->setPixPath(path);
    }

}

void WUserEditDlg::on_okBtn()
{
    if(userNameLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("�������"),tr("�������û���"),QMessageBox::Ok);
        return;
    }
    if(userPwdLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("�������"),tr("����������"),QMessageBox::Ok);
        return;
    }
    if(strcmp(userPwdLineEdit->text().toLatin1().data(),checkPwdLineEdit->text().toLatin1().data())==0)
    {
        sendMessage();
        accept();
    }
    else
    {
        QMessageBox::information(this,tr("���벻һ��"),tr("��������������"),QMessageBox::Ok);
        checkPwdLineEdit->clear();
    }
}

void WUserEditDlg::on_userRightsBtn()
{
    if(!bCreate)
    {
        userRightsDlg->setRoleRights(rights);
    }
    userRightsDlg->show();
}
