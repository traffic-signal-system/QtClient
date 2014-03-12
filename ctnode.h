#ifndef CTNODE_H
#define CTNODE_H

#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

//class ctNodeColTime_Table//群属节点 阶段时间
//{
//public:
//    unsigned char ucGreenTime;
//    unsigned char ucYellowTime;
//    unsigned char ucRedTime;
//};

/*
 群界面的子类 节点及容器
*/

class CtNode : public QLabel
{
    Q_OBJECT
public:
    explicit CtNode(QWidget *parent = 0);
    ~CtNode();
    void calGreenTime();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void timerEvent(QTimerEvent *);
    void setCtNodeId(quint32 id);
    quint32 getCtNodeId();
    void setListTime(QList<quint8>);//设置 阶段配时 时间
    void setOffSet(qint32 t);//设置 相位差对应的长度

    void setStageIndex(quint8 index);//设置所需 阶段
    void setCtNodeText(QString str);//设置节点名
    void getPoint(QPoint&first,QPoint&second);//取得 绿波的 两个点 全局坐标
    void setPosIndex(quint8 index);
    quint8 getPosIndex();
    void setCtCircle(quint8);


signals:
    void mouseSelect(quint32);
   // void offsetChange(quint32,quint8);
public slots:
private:
    quint32 m_uiCtNodeId;
    QList<unsigned char> m_ListTime;//所有阶段 的时间
    QList<quint8> m_ListNewTime;//时间对应的长度
    quint8 m_ucCount;//阶段数
    quint16 m_ucCircle;//阶段周期
    quint8 m_ucCtCircle;//群周期
    qint32 m_iOffSet;//相位差相对0点
    quint8 m_ucTimeOffset;//时间相位差
    quint8 m_ucPosIndex;//位于哪个周期(所有节点的左下角坐标都为正时 除以 周期长度)
    QPoint m_pos;//按下左键时的位置
    quint8 m_ucStageIndex;//所需阶段号
    bool m_bFlag;//关键节点为true

    //QPixmap m_pix;
};

//-----------------------------------------------

class CtNodeContent:public QWidget
{
    Q_OBJECT
public:
    explicit CtNodeContent(QWidget *parent = 0);
    ~CtNodeContent();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
    void setCtCircle(quint8);//设置群周期
    void setOffset(QPoint p,CtNode*node);//p点为 在content中的坐标点
    void setOffset(int x,CtNode*node);//x为相位差
    void getLineCtNode(CtNode**f,CtNode**s);//获取周期内 前后两节点指针
    void moveLeftRight(int b,int len=0);//b取 1向左 -1向右
    void appendCtNode(CtNode*node,int t);
    void clearCtNodeList();
    void calOffsetList(quint32 nodeId=0);
    void calPosIndexList();//计算 index 及 m_ListRelativeOffset相位差在一周期内
    void setKeyData(quint8 index,quint8 offset);
    quint8 getCurNodeListCount();
    int getLeftNodePos(int left);
    void setFlagDragMove(bool b=false);

    QList<qint16> m_ListRelativeOffset;//相对 index0 的时间相位差
    QList<quint8> m_ListNodePosIndex;//计算在哪个周期 0 起

signals:
//    void mouseSelectCtNode(quint32 ctNodeId);
    void offsetChange(quint32);
public slots:
//    void on_mouseSelectCtNode(quint32 ctNodeId);
private:

    QList<CtNode*> m_ListCtNode;//跟 cluster里的m_ListCtNodeId 顺序一致
    qint16 m_siCtCircle;//群周期
    qint16 m_siClick;//无用
    bool m_bUpdate;//用于再一次重画（当dropEvent时）
    QHBoxLayout *m_Layout;
    quint8 m_ucKeyIndex;
    quint8 m_ucKeyOffset;
    bool m_bFlagDragMove;//drop 时为true， 点击 左右移动后为false
    //CtNode* m_pNode;//用于存放 在拖动节点 的index
    int m_iLeft;
    int m_iRight;
    int m_iDif;

};

#endif // CTNODE_H
