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

public slots:

private:
    quint8 m_ucGreen;//��ɫx����
    quint8 m_ucYellow;//��ɫx����
    //quint8 m_ucRed;

    quint8 m_TimeGreen;
    quint8 m_TimeYellow;
    quint8 m_TimeRed;

    DragIcon *m_IconY;
    DragIcon *m_IconR;
    //bool m_bLeftButton;

};

#endif // COLORWIDGET_H
