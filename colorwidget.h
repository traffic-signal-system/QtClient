#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include "dragicon.h"
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QPaintEvent>
//#include <QFrame>

/*
 阶段时间调整
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

    void setBarPos();//调整 位置

    void setTimeValue(quint8 green=13,quint8 yellow=3,quint8 red=3);
    void setStageTime(quint8 stagetime);//
    void setEditable(bool b=false);

    quint8 getTimeGreen();
    quint8 getTimeYellow();
    quint8 getTimeRed();
signals:

public slots:

private:
    quint8 m_ucGreen;//绿色x坐标
    quint8 m_ucYellow;//黄色x坐标
    //quint8 m_ucRed;

    quint8 m_TimeGreen;
    quint8 m_TimeYellow;
    quint8 m_TimeRed;

    DragIcon *m_IconY;
    DragIcon *m_IconR;
    //bool m_bLeftButton;

};

#endif // COLORWIDGET_H
