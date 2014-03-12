#ifndef DIRECTIONICON_H
#define DIRECTIONICON_H

#include <QLabel>
#define MAXCOMPHASE 32
#define DIRECTIONNUM 16
#define DIRECTIONTOTAL 20
#define DIRICONWIDTH 30
#define DIRICONHEIGHT 100

class DirectionIcon : public QLabel
{
    Q_OBJECT
public:
    explicit DirectionIcon(quint8 id,QWidget *parent = 0);
    ~DirectionIcon();
    void init();//Ϊ�½ڵ�
    void initState();//Ϊ�µĽ׶�
    void analyseId();
    void setPhaseId(quint8 phaseId);
    quint8 getPhaseId();
    void setFlagValid(bool b);
    void setFlagGreen(bool b);
    void setIconGreen(bool b);
    void setFlagYellow(bool b);
    void setFlagRed(bool b);
    void setPixGreen(QPixmap&pix);
    void setPixYellow(QPixmap&pix);
    void setPixRed(QPixmap&pix);
    void setPixNull(QPixmap&pix);
    void setFlash(bool b);
    void setFlagFlashMode(bool b);
    void timerEvent(QTimerEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
    quint32 getPhase();//����24��λ
    void setFlagClickAble(bool b);
    void setFlagInclude(bool b);
    void setPedSmall(bool b);
    bool getFlagGreen();//Ϊ��ȡͼ����Ϣ
    bool getFlagValid();//Ϊͼ���һ�ι��� ��С
    QPixmap getGreenPix();

signals:
    void includePhaseTurn(bool b);
    void mouseClick();//�ı�������λʱ
public slots:
    void on_includePhaseTurn(bool b);
private:
    quint8 m_ucDirId;//1-20 �̶�ͼ�꣬ͼƬ�ɱ䣬λ�ü���С���䣨�������У�
    quint8 m_ucPhaseId;
    bool m_bValid;
    bool m_bGreen;
    bool m_bYellow;
    bool m_bRed;
    bool m_bFlash;
    bool m_bFlashMode;//true ǰ����� false������
    bool m_bClick;
    bool m_bClickAble;
    QPixmap m_PixGreen;
    QPixmap m_PixYellow;
    QPixmap m_PixRed;
    QPixmap m_PixNull;
    int m_iTimerId;
    bool m_bTimer;
    bool m_bInclude;//������λ��־
    quint8 m_ucIncludeNum;//������λ����
    quint8 m_ucDir;//���� 0����1����2�ϣ�3��

};

#endif // DIRECTIONICON_H
