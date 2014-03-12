#ifndef DETWIDGET_H
#define DETWIDGET_H

#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QBoxLayout>
#include <QGridLayout>


#include <QWidget>
#include <QList>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include <QPixmap>
#include "pdataprocess.h"
/*
 �������������� ����� ·�� ������ �������������  ��������
*/
class DetIcon : public QDialog
{
    Q_OBJECT
public:
    explicit DetIcon(QWidget *parent = 0);
    ~DetIcon();


    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void setDetectorNo(quint8 no);
    quint8 getDetectorNo();
    void setRadius(int r);
    void setDetStatus(bool b,quint8 detAlarm=0,quint8 coilAlarm=0);//�����״̬ �г� �޳� �쳣
    void emitLeaveContent();
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void clearState();


signals:
    void leaveContent(DetIcon*);
    void mouseStatus(bool b,bool btype,quint8 index,QPoint p);//b true������ btype trueΪ����� index�������/������ p����λ����������
public slots:

private:

    quint8 m_ucDetNo;
    int m_iRadius;
    QPoint m_posStart;
    bool m_bGreen;//true �г� ��ɫ false �޳� ��ɫ
    bool m_bRed;//true �쳣 ��ɫ false ���� �׻���
    int m_iTimer;
    bool m_bIncludeMouse;
    bool m_bSend;
    bool m_bTimer;
    bool m_bDrag;//��ק��־ trueΪ��ק falseΪ���
    //QPoint m_Point;
};

//-----------------------------------------------

class DetContent : public QDialog
{
    Q_OBJECT
public:
    explicit DetContent(QWidget *parent = 0);
    ~DetContent();
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);

    void setDirNo(quint8 no);//���� ����� ��ȡ�� ������
    quint8 getDirNo();
    void setData(quint8 dir=1,quint8 type=0,quint8 index=0,quint8 phase=0);//dir������ ��type��·�ꣻindex������˳�� phase��������λ
    //void addIcon(DetIcon*i,QPoint p=QPoint(0,0));
    void addIcon(DetIcon*i,quint8 pos=0,bool b=true);//b Ϊfalseʱ ����Ҫ������Ϣ �Ͽ�ԭ����
    //void mousePressEvent(QMouseEvent *);
    void setContentData();//���� ��· �������Ϣ
    void setDetBase(PDataProcess *p);
    void changeListIcon(quint8 dir,quint8 pos,DetIcon*i,bool b=true);//b Ϊtrue ��������
    void setIconData(quint8 iconNo,quint8 index=0);//iconNo������� index����λ�� 0-3 Ϊm_ListIcon�洢λ��
    void timerEvent(QTimerEvent *);
signals:
    void removeIcon(DetIcon*);
    void mouseStatus(bool b,bool btype,quint8 index,QPoint p);//b true������ btype trueΪ����� index�������/������ p����λ����������
    void detChangePos(int detNo);
public slots:
    void on_IconLeave(DetIcon*);
private:
    quint8 m_ucDirNo;
    quint8 m_ucPhase;//������λ
    quint8 m_ucDirection;//1 ���� 2 ����  3 �ϣ� 4 ����
    qint16 m_sDegree;//��ת�ĽǶ�
    quint8 m_ucType;//·������ 1��; 2ֱ; 3��; 4����; 0�ޣ����ڳ�ʼ��ʱ�� ���е� �������
    bool m_bPed;//true ���У�false ������
    quint8 m_ucLoadIndex;//����˳��� ����������ʱ�룩 0��
    //quint8 m_ucPosIndex;//Զ��˳��� �ӽ���Զ 0��
    Detector_Table *m_pDetBase;

    //QPixmap *m_pPix;
    QImage m_img;
    bool m_bImg;

    QBoxLayout *m_pLayout;
    QGridLayout *m_pGLayout;

    QList<DetIcon*> m_ListIcon;//0-3��ż���� �ɽ���Զ

    bool m_bIncludeMouse;
    bool m_bSend;
    PDataProcess* m_pDataProcess;
//    QPoint m_posStart;

};

//---------------------------------------------------
class DetParaDlg : public QWidget
{
    Q_OBJECT
public:
    DetParaDlg(QWidget *parent = 0);
    ~DetParaDlg();
    void init();
    void setDataProcess(PDataProcess *p);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void closeEvent(QCloseEvent *);
    void setData(quint8 detNo=0,quint8 loadNo=0);
    void clearInterface();
    void showData(bool b);//true ��ʾ ����� ��false ��ʾ ����
    void getDataFromInterfase();//
//    void mousePressEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);
//    QWidget *detWidget;
//    QWidget *typeWidget;
//    QWidget *optionWidget;
public slots:
    void on_confirmBtn();
    void on_cancelBtn();
    void on_cbDetNoChange(int index);
    void on_cbDirNoChange(int index);
    //void on_cbHightLight(int);
    void on_dataChange();
    void on_detChangePos(int detNo);
    void on_btnMore();


signals:
    void closeDlg();
    void mouseStatus(bool b);



private:
    QComboBox *cbDetNo;
    QComboBox *cbPhase;
    QGroupBox *gbAdvanced;
    QPushButton *btnMore;
    QList<QRadioButton*> listTypeRadio;
    QList<QCheckBox*> listTypeCheck;
    QComboBox *cbDir;
    QSpinBox *sbValidTime;
    QList<QCheckBox*> listOptionCheck;
    QLineEdit *leSaturation;
    QSpinBox *sbOccupancy;
    QComboBox *cbDirLoad;
    QSpinBox *sbLoadNum;

    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    QGroupBox *m_gbDet;
    QGroupBox *m_gbLoad;

    PDataProcess *m_pDataProcess;

    bool m_bClick;
    quint8 m_ucDirNo;
    quint8 m_ucDetNo;

    bool m_bInit;//���ݳ�ʼ�� cleraInterfase on_DetNoChange on_cbDirNoChangeΪ��ʼǰΪfalse������Ϊtrue
    bool m_bDataChange;//�����и���Ϊ true ��on_confirmBtn on_cbDetNoChange ʱ�������ݵ�lib
};

//-------------------------------------------

class FlowWidget;
class DetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetWidget(QWidget *dlgParent=0,QWidget *parent = 0);
    ~DetWidget();
    void init();
    void paintEvent(QPaintEvent *);
    void setDataProcess(PDataProcess *p);
    void mouseDoubleClickEvent(QMouseEvent *);
    void rankDetector();//���м����λ��
    void mouseMoveEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    void setFlowList(QList<FlowWidget*>&list);

//    void enterEvent(QEvent *);
//    void leaveEvent(QEvent *);

signals:
    void stopDetStatus();

public slots:
    void on_rcvDetector();
    void on_removeIcon(DetIcon*);
    void on_rcvDetStatus(unsigned char*para1,int len);
    void on_rcvDetAlarm();
    void on_mouseStatus(bool b,bool btype,quint8 index,QPoint p);
    void on_dlgMouseStatus(bool b);
    void on_closeDetParaDlg();

private:
   QList<DetIcon*> m_ListIcon;//�������
   QList<DetContent*> m_ListLoad;//��·��
   QList<QLabel*> m_ListGroup;//��������� �� �� �� �� ·�꣬�� �м�� û�õļ����

   QList<quint8> *m_pListLoadNum;//�ĸ����� 4��·�꣨��ֱ�����У� �� ������ ָ�� PDataProcess
   QList<quint8> *m_pListPhase;//1-16�����Ӧ�� ��λֵ
   QList<bool> m_ListDetStatus;//����� �Ƿ� �г� trueΪ�г�
   QList<bool> m_ListDetAlarm;//���������״̬ true Ϊ����
   bool m_bDetAlarm;
   PDataProcess *m_pDataProcess;
   Detector_Table *m_pDetBase;

   bool m_bFlagShow;
   bool m_bAutoStatus;//���� �ڽ�������ʱ �Ƿ���Ҫ ���� �����ϱ�
   bool m_bAutoAlarm;

   DetParaDlg *m_pDetPara;
   qint8 m_cMouseCnt;

   QList<FlowWidget*> m_pListFlow;
};

//-----------------------------------------------------------------------------------
class FlowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowWidget(QWidget *parent = 0);
    ~FlowWidget();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void setStatus(bool b);
    void setDetNo(quint8 detNo);
    quint8 getDetNo();
    void clearData();
    void timerEvent(QTimerEvent *);

signals:

public slots:
private:
    const QColor m_cstCol;
    quint8 m_ucDetNo;//�������
    QPixmap pix;
    QPixmap pixTemp;
    bool m_bStatusPre;//��ǰ״̬
    bool m_bStatus;//����״̬ true �г� false �޳�
    bool m_bLine;//��ʼ��ʱ ������
    bool m_bData;//�Ƿ��� ����� ���� ���� �������� �ػ�
    quint32 m_uiNum;//����

    bool bClick;//try
    int m_iTimerId;
    bool bTimer;

};

#endif // DETWIDGET_H
