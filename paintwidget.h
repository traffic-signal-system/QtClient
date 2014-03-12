#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QLCDNumber>
//#include <QPushButton>
#include <QImage>
#include <QPixmap>
#include <QBitmap>
/*
���� ·����ʾ���桢�׶�ͼ��
*/
class PDataProcess;
class WPhaseStageWidget : public QWidget
{
    Q_OBJECT
public:
    //ʵʱ��ʾ ����1�������ڣ�����2����ɫͨ��������3����ɫͨ��������4����ɫͨ��������5������ͨ��������6�������ȣ�����7��LCD���أ�����8���׶�������ʱ�䣻����9��ģ�⿪�أ�����10������ʱ�䣻����11���̵�ʱ�䣻����12���Ƶ�ʱ�䣻����13�����ʱ��
    explicit WPhaseStageWidget(QWidget *parent,quint16 green,quint16 yellow,quint16 red,quint16 flash=0,quint16 width=400,bool bLcd=false,quint8 time=0,bool simulate=false,quint8 timegreenflash=3,quint8 timegreen=12,quint8 timeyellow=3,quint8 timered=3);

    //���� �׶���ʾ ��ʾ��ͨ�� ����1����ɫͨ��������2��������
    WPhaseStageWidget(PDataProcess *p,quint16 green,quint16 width=150,QWidget *parent=0);

    //ģ������ ����1��������λ������2���׶��̵ƣ�����3:�׶λƵƣ�����4���׶κ�ƣ�����5�������ȣ�����6������ʱ��
    WPhaseStageWidget(QList<quint16> listgreen,QList<quint8> timelistgreen,QList<quint8> timelistyellow,QList<quint8> timelistred,quint16 width=400,quint8 timegreenflash=3,QWidget *parent=0);

    ~WPhaseStageWidget();

    void clearData();
    void clearListData();//������λ ʱ��

    void loadImage();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    void killFlashTimer();


    void setData(quint16 green=0,quint16 yellow=0,quint16 red=0,quint16 flash=0,quint8 time=0,quint8 timegreenflash=2,quint8 timegreen=5,quint8 timeyellow=2,quint8 timered=2);
    void setLcdNumDisplay();

    //ģ����ʾ
    void setListData(QList<quint16> listgreen,QList<quint8> timelistgreen,QList<quint8> timelistyellow,QList<quint8> timelistred);
    void editListData(bool badd,bool breplace,bool bdel,quint8 index,quint16 greenchannel=0x0000,quint8 timegreen=13,quint8 timeyellow=3,quint8 timered=3,quint8 option=0);

    void changeDataToInterface(quint16& bits);//�� �ⲿ����˳�� ת��Ϊ ����˳�� �ⲿ
    void changeInterfaceToData(quint16& bits);
    void setSimulate(bool b);

    void setTimePeriod();//������ʱ����

    //���� ��ʱ ��ʾ �׶�
    void setClickable(bool=true);//���� ѡȡ ·�� ���� ѡ����λ
    quint16 getGreenChannel();//��ȡ���� ��ɫͨ��
    void setGreenChannel(quint16 green);//���ý��� ��ɫͨ������  ����ͼ��
    void setClicked(bool b=true);//���� ͼ����Ա�ѡ�У��ɴ�����Ϣ
    //���ص�ǰ�׶ε� �̵�ʱ�� �Ƶ�ʱ�� ���ʱ��
    quint16 getPhase(quint8 index);
    quint8 getTimeGreen(quint8 index=0xff);//���ص�ǰ�׶�����
    quint8 getTimeYellow(quint8 index=0xff);
    quint8 getTimeRed(quint8 index=0xff);
    quint8 getOption(quint8 index=0xff);



    void setCurIndex(quint8 index);
    quint8 getCurIndex();
    quint8 getStageCount();

    void setIconDark(bool b=false);
    void setIconWidth(quint16 width);
    bool getBeClicked();//���� �Ƿ�ѡ�б�־ m_bClicked;

    void emitBeClicked();

    void setDataProcess(PDataProcess *p);
    void setListPoint(QList<quint8> *listChannel=NULL,QList<quint8>*listCom=NULL,QList<quint8>*listOver=NULL);
    void setRealShowFlag(bool b=false/*,bool blcd=true*/);//�׶���ʱ �������ʾʱ�õ�

signals:
    void beClicked(WPhaseStageWidget*,quint8);//index ��1��,Ϊ�׶κ�

public slots:

private:



    bool m_bRed;//�׶κ��  ����lcd��ɫ
    bool m_bGreen;//�׶��̵�
    bool m_bYellow;//�лƵ� ����lcd��ɫ
    bool m_bFlashGreen;

    bool m_bTimeEvent;
    bool m_bTimerStart;
    bool m_bLcdNum;
    bool m_bFlash;
    bool m_bSimulate;//�׶�ģ��
    bool m_bClickable;//��λ����
    bool m_bClick;//��ѡ��ͼ��
    bool m_bClicked;//��ѡ��Ϊtrue
    bool m_bIcon;//�׶�ͼ����ʾ

    bool m_bNumColor;//��˸ʱ ������˸
    QLCDNumber *m_LcdNumber;


    QList<bool> m_bListGreen;
    QList<bool> m_bListYellow;
    QList<bool> m_bListRed;
    QList<bool> m_bListFlash;
    QList<bool> m_bListFlashChange;
    QList<QPixmap> m_imgList;
    //QList<QImage*> m_imgListGreen;



    quint8 m_ucTime;//�׶��ѹ�����
    quint16 m_usTimePass;//�����ѹ�����

    quint8 m_ucTimeGreenFlash;
    quint8 m_ucTimeGreen;
    quint8 m_ucTimeYellow;
    quint8 m_ucTimeRed;
    quint16 m_usTimePeriod;

//    quint16 m_uiAngleGreen;
//    quint16 m_uiAngleYellow;
//    quint16 m_uiAngleRed;

    quint16 m_usWidth;
    quint16 m_usHeight;
    qreal m_fScale;
    //QTimer *timer1;
    QList<quint16> m_ListPhaseStage;
    QList<bool> m_bListPhaseChange;//����Ƿ���Ҫ ����״̬

    QList<quint8> m_ListTimeGreen;
    QList<quint8> m_ListTimeYellow;
    QList<quint8> m_ListTimeRed;
    QList<quint8> m_ListOption;
    quint8 m_ucStageNo;//�׶κ�
    quint8 m_ucStageCnt;

    quint32 m_uiTimerId;//��ʱ��id

    PDataProcess *m_pDataProcess;
    bool m_bRealShow;//ʵʱ��ʾ ʱ ֻҪ��Ӧͨ��
    QList<quint8> *m_pListChannelMap;
    QList<quint8> *m_pListComMap;
    QList<quint8> *m_pListOverlapMap;

    quint32 m_uiNum;

};

#endif // PAINTWIDGET_H
