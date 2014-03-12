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
    QStringList m_listName;//线的名称
    QList<QPainterPath> m_listPath;//线的路径
    QList<QColor> m_listCol;//每条线对应的颜色
//    QPixmap m_pix;
    quint32 m_uiMaxX;//
    quint32 m_uiMaxY;//最大时间
    quint32 m_uiMinTime;
    quint32 m_uiDisTime;//间隔时间
    PDataProcess *m_pDataProcess;
    int m_iCnt;
    qreal m_rScale;//放大 缩小
    qreal m_rTranslate;//左右移
    QString m_strTimeMsg;
    int m_iPageIndex;

};

#endif // WTRAFFIC_H
