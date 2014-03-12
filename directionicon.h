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
    void init();//为新节点
    void initState();//为新的阶段
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
    quint32 getPhase();//考虑24相位
    void setFlagClickAble(bool b);
    void setFlagInclude(bool b);
    void setPedSmall(bool b);
    bool getFlagGreen();//为获取图标信息
    bool getFlagValid();//为图标的一次过街 大小
    QPixmap getGreenPix();

signals:
    void includePhaseTurn(bool b);
    void mouseClick();//改变允许相位时
public slots:
    void on_includePhaseTurn(bool b);
private:
    quint8 m_ucDirId;//1-20 固定图标，图片可变，位置及大小不变（除了人行）
    quint8 m_ucPhaseId;
    bool m_bValid;
    bool m_bGreen;
    bool m_bYellow;
    bool m_bRed;
    bool m_bFlash;
    bool m_bFlashMode;//true 前半秒空 false后半秒空
    bool m_bClick;
    bool m_bClickAble;
    QPixmap m_PixGreen;
    QPixmap m_PixYellow;
    QPixmap m_PixRed;
    QPixmap m_PixNull;
    int m_iTimerId;
    bool m_bTimer;
    bool m_bInclude;//包含相位标志
    quint8 m_ucIncludeNum;//包含相位数量
    quint8 m_ucDir;//方向 0北，1东，2南，3西

};

#endif // DIRECTIONICON_H
