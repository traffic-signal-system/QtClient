#ifndef CTNODE_H
#define CTNODE_H

#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

//class ctNodeColTime_Table//Ⱥ���ڵ� �׶�ʱ��
//{
//public:
//    unsigned char ucGreenTime;
//    unsigned char ucYellowTime;
//    unsigned char ucRedTime;
//};

/*
 Ⱥ��������� �ڵ㼰����
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
    void setListTime(QList<quint8>);//���� �׶���ʱ ʱ��
    void setOffSet(qint32 t);//���� ��λ���Ӧ�ĳ���

    void setStageIndex(quint8 index);//�������� �׶�
    void setCtNodeText(QString str);//���ýڵ���
    void getPoint(QPoint&first,QPoint&second);//ȡ�� �̲��� ������ ȫ������
    void setPosIndex(quint8 index);
    quint8 getPosIndex();
    void setCtCircle(quint8);


signals:
    void mouseSelect(quint32);
   // void offsetChange(quint32,quint8);
public slots:
private:
    quint32 m_uiCtNodeId;
    QList<unsigned char> m_ListTime;//���н׶� ��ʱ��
    QList<quint8> m_ListNewTime;//ʱ���Ӧ�ĳ���
    quint8 m_ucCount;//�׶���
    quint16 m_ucCircle;//�׶�����
    quint8 m_ucCtCircle;//Ⱥ����
    qint32 m_iOffSet;//��λ�����0��
    quint8 m_ucTimeOffset;//ʱ����λ��
    quint8 m_ucPosIndex;//λ���ĸ�����(���нڵ�����½����궼Ϊ��ʱ ���� ���ڳ���)
    QPoint m_pos;//�������ʱ��λ��
    quint8 m_ucStageIndex;//����׶κ�
    bool m_bFlag;//�ؼ��ڵ�Ϊtrue

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
    void setCtCircle(quint8);//����Ⱥ����
    void setOffset(QPoint p,CtNode*node);//p��Ϊ ��content�е������
    void setOffset(int x,CtNode*node);//xΪ��λ��
    void getLineCtNode(CtNode**f,CtNode**s);//��ȡ������ ǰ�����ڵ�ָ��
    void moveLeftRight(int b,int len=0);//bȡ 1���� -1����
    void appendCtNode(CtNode*node,int t);
    void clearCtNodeList();
    void calOffsetList(quint32 nodeId=0);
    void calPosIndexList();//���� index �� m_ListRelativeOffset��λ����һ������
    void setKeyData(quint8 index,quint8 offset);
    quint8 getCurNodeListCount();
    int getLeftNodePos(int left);
    void setFlagDragMove(bool b=false);

    QList<qint16> m_ListRelativeOffset;//��� index0 ��ʱ����λ��
    QList<quint8> m_ListNodePosIndex;//�������ĸ����� 0 ��

signals:
//    void mouseSelectCtNode(quint32 ctNodeId);
    void offsetChange(quint32);
public slots:
//    void on_mouseSelectCtNode(quint32 ctNodeId);
private:

    QList<CtNode*> m_ListCtNode;//�� cluster���m_ListCtNodeId ˳��һ��
    qint16 m_siCtCircle;//Ⱥ����
    qint16 m_siClick;//����
    bool m_bUpdate;//������һ���ػ�����dropEventʱ��
    QHBoxLayout *m_Layout;
    quint8 m_ucKeyIndex;
    quint8 m_ucKeyOffset;
    bool m_bFlagDragMove;//drop ʱΪtrue�� ��� �����ƶ���Ϊfalse
    //CtNode* m_pNode;//���ڴ�� ���϶��ڵ� ��index
    int m_iLeft;
    int m_iRight;
    int m_iDif;

};

#endif // CTNODE_H
