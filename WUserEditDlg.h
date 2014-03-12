#ifndef WUSEREDITDLG_H
#define WUSEREDITDLG_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QDateTime>
#include <QPixmap>
#include <QDebug>
#include <QImage>
#include <QPaintEvent>

#include "pdataprocess.h"
#include "wuserrightdlg.h"


/*
 �û����� �༭
*/
class ImageDlg:public QDialog//����ͼƬ
{
public:
    ImageDlg(QWidget* parent=0);
    void setPixPath(QString path=NULL);
    QPixmap p;

private:
    bool bPaint;
    void paintEvent(QPaintEvent *);
};



class WUserEditDlg : public QDialog
{
    Q_OBJECT
public:
    explicit WUserEditDlg(QWidget *parent = 0);
    ~WUserEditDlg();
    void setDataProcess(PDataProcess *dp);
    void setCreateFlag(bool b=true);
    void sendMessage();
signals:

private slots:
    void on_browseBtn();
    //void on_cancelBtn();
    void on_okBtn();
    void on_userRightsBtn();

private:
    QLineEdit *userIDLineEdit;
    QLineEdit *userNameLineEdit;
    QLineEdit *userPwdLineEdit;
    QLineEdit *checkPwdLineEdit;
//    QComboBox *userTypeComboBox;
    QPushButton *userRightsBtn;

    WRoleRightsDlg* userRightsDlg;
    bool bCreate;//�½��û���־
    char rights[32];//�û�Ȩ��

    QDateEdit *edit;
    QDateTime time;



    QLineEdit *imageLineEdit;
    QPixmap pix;

    QPushButton *browseBtn;
    ImageDlg *image;


    QPushButton *okBtn;
    QPushButton *cancelBtn;

    PDataProcess* m_pDataProcess;
};

#endif // WUSEREDITDLG_H
