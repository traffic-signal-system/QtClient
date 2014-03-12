#ifndef PHASE_H
#define PHASE_H

#include <QLabel>
#include <QHBoxLayout>
#define MAXCOMPHASE 32
#define OVERLAPPHASENUM 8
#define ICONWIDTH 500
class WordIcon : public QLabel
{
    Q_OBJECT
public:
    explicit WordIcon(quint8 id,bool bUsed = false,bool bContent=false,bool bValid=true,QWidget *parent = 0);
    ~WordIcon();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    bool getFlagUsed();//���ڷ���ӳ����Ϊtrue ����Ӧ��ק
    void setFlagUsed(bool b=true);
    bool getFlagOverlapContent();//�����Ƿ�new
    quint8 getId();
    void setFlagDirContent(bool b=true);
    bool getFlagDirContent();
    void setFlagClick(bool b);
    bool getFlagClick();
    void setFlagAmend(bool b);

signals:
    void mouseClick(quint8 id,bool bClick);
    void leaveContent(WordIcon*);

public slots:
    void on_setOverlapFlagValid(bool b=true);//������λ �а�����λ Ϊtrue
private:
    quint8 m_ucPhaseId;//1-32��ͨ��λ 33-40������λ
    bool m_bUsed;//�Ƿ��Ѿ�ӳ�䷽�� true�Ѿ�ӳ��
    bool m_bValid;//������λ �Ƿ��а�����λ true�ſ���ק  ������λ����false
    bool m_bContent;//true �ڰ�����λ�����Ĭ��false
    bool m_bDirContent;//����ӳ������ Ĭ��false��
    bool m_bMouseIn;//Ĭ��false;
    bool m_bDrag;//true ��ק��Ϊ
    bool m_bOverlap;//true ����
    bool m_bAmend;//����

    QPoint m_posStart;//���� ����� ��ק
    bool m_bClick;

};

//-----------------------ͨ��ͼ��----------------------------------
/*
 ��λ���ͣ�ctrlType:
*/
class ChlIcon : public QLabel
{
    Q_OBJECT
public:
    explicit ChlIcon(quint8 id,bool bUsed = false,QWidget *parent = 0);
    ~ChlIcon();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void setFlagUsed(bool b=true);
    quint8 getId();
    quint8 getPhaseId();
    void setChlPhaseId(quint8);
    void setFlagClick(bool b);
signals:
    void mouseClick(quint8 chlId,bool bClick,quint8 phaseId);
    void leaveContent(ChlIcon*);

public slots:

private:
    quint8 m_ucChlId;//1-24
    quint8 m_ucPhaseId;
    bool m_bUsed;//true �Ѿ�������λ ����ͼ
    bool m_bMouseIn;//Ĭ��false;
    bool m_bDrag;//true ��ק��Ϊ
    QPixmap m_pix;//ͨ��ͼƬ
    QPoint m_posStart;//���� ����� ��ק
    bool m_bClick;//����

};

//------------------------ͨ���������λ ����---1-OVERLAPPHASNUM ��������--------OVERLAPPHASNUM+1 - ... ��������--------------------
class IconContent:public QWidget
{
    Q_OBJECT
public:
    explicit IconContent(bool bType = true,quint8 id=0,QWidget*parent=0);
    ~IconContent();
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void paintEvent(QPaintEvent *);
    bool checkId(quint8 id);//��������λ �Ƿ��Ѿ����� trueδ������false�Ѱ���
    bool checkIcon(WordIcon*);
    bool checkIcon(ChlIcon*);
    void addComPhase(WordIcon*);
    void addComPhase(quint8 id);
    void addChl(ChlIcon*);
    void setFlagClick(quint8 phaseId,bool b=false);
    quint8 getContentId();
    void clearContent();//����list
    QList<quint8>&getListData();
//    bool getFlagAmend();
signals:
    void setOverlapValid(bool b);//������λ�а�����λ ��Ч ��Ч
    void mouseClickPhase(quint8 contId,bool bClick,quint8 phaseId);
public slots:
    void on_chlLeaveContent(ChlIcon*);
    void on_phaseLeaveContent(WordIcon*);
    void on_mouseClickPhase(quint8 phaseId,bool bClick);
private:
    bool m_bType;//true ͨ��; false ������λ ������λ
    bool m_bValid;//������λ��Ч�� ��ʼΪfalse
    quint8 m_ucContentId;//1-2*OVERLAPPHASENUM
    QList<quint8> m_ListId;//��λid �� ͨ��id
    QHBoxLayout *m_hLayout;
    bool m_bAmend;
};

//--------------------��������--------------------------------------
/*
 m_ucLoadNo:·�귽�� 1-16 ������ ��ֱ�� ������ ������ �� �� ��
001 00 000 ����001-100 �� �� �� �� ( ���� ���� ���� ����)��
����00 ������ 01���У�
·��0��0ֱ0��000һ������001; 010�������У�


------------------0730ȷ��------------------------------
  bit0-bit2:��ʾ·��
(����)
bit0:�� 1��Ϊѡ�ϣ������
bit1:ֱ 1��Ϊѡ�ϣ������
bit2:�� 1��Ϊѡ�ϣ������
(����)
000:һ������ 001:�������е�N01 010:�������е�N02

bit3-bit4����λ���� 00:������ 01:����

bit5-bit7������
001:��010:��011:��100:��
 101:���� 110:���� 111:���� 000:����
*/
class LoadIcon : public QLabel
{
    Q_OBJECT
public:
    explicit LoadIcon(/*QPixmap pix,*/quint8 loadNo = 0,QWidget *parent = 0);
    ~LoadIcon();
    void loadImage();
    void analyseDir();//���������

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);

    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void addPhaseIcon(quint8 id);
    void addPhaseIcon(WordIcon*);

    bool getFlagPed();
    void setFlagValid(bool b=true);
    bool getFlagValid();

    void clearPhaseIcon();
    void setFlagClick(quint8 phaseId,bool b=false);//������λ
    void setFlagClick(bool bClick);//����·��

    quint8 getContentId();
    void setLoadNo(quint8 loadNo);
    quint8 getPhaseId();
    quint8 getLoadNum();
    void setLoadNum(quint8 num);

signals:
    void clearContent(quint8,bool b=false);//���� ԭʼ��λ�� used
    void mouseDoubleClick(quint8 loadNo);
    void mouseClickPhase(quint8 contId,bool bClick,quint8 phaseId);
    void mouseClickDir(quint8 contId,bool bClick);
public slots:
    void on_phaseLeaveContent(WordIcon*);
    void on_mouseClickPhase(quint8 phaseId,bool bClick);

private:
    quint8 m_ucLoadNo;
    quint8 m_ucNum;//��·��
    int m_iDirect;//0��1��2��3 �� �� �� ��
    QImage m_img;//·��
    bool m_bPed;//������λ
    bool m_bValid;//�Ƿ���Ч Ĭ��false �����Ƿ���ʾ ��ȡ���� ����λΪtrue
    bool m_bClick;
    quint8 m_ucPhaseId;

    WordIcon* m_pIcon;
    QLayout *m_pLayout;
};
//-----------------------------------------------------
class phaseWidget:public QWidget
{
    Q_OBJECT
public:
    phaseWidget(quint16 width=100,QWidget*parent=0);
    ~phaseWidget();
    void paintEvent(QPaintEvent *);
    //void setFlagDirection(bool bNorth=true,bool bEast=true,bool bSouth=true,bool bWest=true);
    void setBack(quint8 dir=0);
    void setListAllowGreen(QList<bool> listGreen,QList<QPixmap>listPix,quint16 phase=0);
    void setIconWidth(quint16 w);
    void mouseReleaseEvent(QMouseEvent *);
    void setBackDark(bool b=true);
    quint16 getPhase();
signals:
    void mouseClick(phaseWidget*);
private:
//    QImage m_img;
    QList<bool> m_bListGreen;
    QList<QPixmap> m_ListPix;
    qreal m_rScale;
//    bool m_bClickAble;

    quint16 m_sAllowPhase;
    bool m_bNorth;//true ��·��
    bool m_bEast;
    bool m_bSouth;
    bool m_bWest;
};

//----------------------------------------------
/*
 �׶�ʱ����� ��������
*/
class DragIcon : public QLabel
{
    Q_OBJECT
public:
    explicit DragIcon(QPixmap pix,QString str,QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void setIconCursor(bool b);

signals:

public slots:

private:
    QPoint startPos;
    QString m_IconStr;

};

//----------------------------------------------------
/*
 �׶�ʱ�����
*/
class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    //void setCursorPos(QPoint pos,QPoint offset,quint8 left,quint8 right);
    void dropEvent(QDropEvent *);

    void paintEvent(QPaintEvent *);

    void setBarPos();//���� λ��

    void setTimeValue(quint8 green=13,quint8 yellow=3,quint8 red=3);
    void setStageTime(quint8 stagetime);//
    void setEditable(bool b=false);

    quint8 getTimeGreen();
    quint8 getTimeYellow();
    quint8 getTimeRed();
signals:
    void colorTimeChange(quint8,quint8,quint8);
public slots:

private:
    quint8 m_ucGreen;//��ɫx����
    quint8 m_ucYellow;//��ɫx����
    //quint8 m_ucRed;

    qint16 m_TimeGreen;
    qint16 m_TimeYellow;
    qint16 m_TimeRed;

    DragIcon *m_IconY;
    DragIcon *m_IconR;
    //bool m_bLeftButton;

};

#endif // PHASE_H
