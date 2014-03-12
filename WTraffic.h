#ifndef WTRAFFIC_H
#define WTRAFFIC_H

#include <QWidget>
#include "pdataprocess.h"

namespace Ui {
    class WTraffic;
}
class trafficLine;
class WTraffic : public QWidget
{
    Q_OBJECT

public:
    explicit WTraffic(QWidget *parent = 0);
    ~WTraffic();
    void setDataProcess(PDataProcess*p);

public slots:
    void on_cbDevicedCheck(bool b);
    void on_cbTimeCheck(bool b);
    void on_btnQuery();
    void on_btnDelete();

private:
    Ui::WTraffic *ui;
    PDataProcess *m_pDataProcess;
    trafficLine *m_pGrgph;
};

class trafficLine : public QWidget
{
    Q_OBJECT
public:
    trafficLine(QWidget *parent = 0);
    ~trafficLine();
    void paintEvent(QPaintEvent*);
    void setDataProcess(PDataProcess *p);
    void setDisTime(quint32 dis);
//    void setMaxX(quint32 colum);
    void clearData();
public slots:
    void on_setMaxMinY(quint32 maxTime,quint32 minTime,quint32 maxY);
    void on_setLineData(QString strName,QMap<quint32,quint32> mapData);
    void on_completeTraffic();
    void on_btnUp();
    void on_btnDown();
    void on_btnLeft();
    void on_btnRight();
    void on_btnLeftBig();
    void on_btnRightBig();
    void on_btnPageUp();
    void on_btnPageDown();
private:
    QStringList m_listName;//�ߵ�����
    QList<QPainterPath> m_listPath;//�ߵ�·��
    QList<QColor> m_listCol;//ÿ���߶�Ӧ����ɫ
//    QPixmap m_pix;
    quint32 m_uiMaxX;//
    quint32 m_uiMaxY;//���ʱ��
    quint32 m_uiMinTime;
    quint32 m_uiDisTime;//���ʱ��
    PDataProcess *m_pDataProcess;
    int m_iCnt;
    qreal m_rScale;//�Ŵ� ��С
    qreal m_rTranslate;//������
    QString m_strTimeMsg;
    int m_iPageIndex;

};

#endif // WTRAFFIC_H
