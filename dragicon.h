#ifndef DRAGICON_H
#define DRAGICON_H

#include <QLabel>
#include <QMouseEvent>
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

#endif // DRAGICON_H
