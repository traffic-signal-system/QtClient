#ifndef VIP_H
#define VIP_H

#include <QWidget>
#include <QList>
#include <QHBoxLayout>


/*
 vip ��������� �ڵ㼰����
*/
class VipNode : public QWidget
{
    Q_OBJECT
public:
    explicit VipNode(QWidget *parent = 0);
    ~VipNode();

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *);

    void setNodeId(quint32 id,QString name);
    void setColorGreen(bool);//Ϊtrueʱ ���� �ܿ� �׶�,ͼ��Ϊ��ɫ
    quint32 getNodeId();
    void setStageIndex(quint8 index);
    quint8 getStageIndex();
    void setTimeOffset(quint16 t);
    quint16 getTimeOffset();
    void setIconDark(bool b);
    void setCurStage(quint8 stage);

signals:
    void mouseSelect(VipNode*);

public slots:
    //void on_mouseSelect(VipNode*);

private:
    quint32 m_nodeId;
    QString m_strName;
    quint8 m_ucStageIndex;//�ڼ��׶� 1 ��
    quint8 m_ucCurStage;
    quint16 m_usTime;//ʱ����
    QColor m_color;
    QPoint m_pos;
};

class VipNodeContent : public QWidget
{
    Q_OBJECT
public:
    explicit VipNodeContent(QWidget *parent = 0);
    ~VipNodeContent();
    void paintEvent(QPaintEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
    void addIcon(VipNode*);
    void addIcon(quint32 id,QString name);
    void delIcon(quint32 id);
    void getVipData(/*QList<quint32>&listId,QList<quint8>&listStage,QList<quint16>&listTime*/);
    void clearNode();
    void setVipNodeGreen(quint32 id,bool b,quint8 stageId=0);
    QList<quint32> getIdList();
    QList<quint8> getStageList();
    QList<quint16> getTimeList();
signals:
    void mouseSelect(VipNode*);
public slots:
    void on_mouseSelect(VipNode*);
private:
    quint16 m_usLen;//�ܳ��ȴ����ʱ��

    QList<VipNode*> m_ListNode;
    QList<quint32> m_ListNodeId;
    QList<quint8> m_ListStageIndex;
    QList<quint16> m_ListTimeOffset;
    QHBoxLayout *m_Layout;

};

#endif // VIP_H
