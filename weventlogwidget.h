#ifndef WEVENTLOGWIDGET_H
#define WEVENTLOGWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QLineEdit>
#include "pdataprocess.h"
#include "CommClass.h"
#include <QMenu>
#include <QMouseEvent>
/*
 日志事件界面
*/
class WEventLogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WEventLogWidget(QWidget *parent = 0);
    ~WEventLogWidget();
    void setDataProcess(PDataProcess*p);
    void mousePressEvent(QMouseEvent *);
signals:

public slots:
    void on_readBtn();
    void on_sort(int);
    void on_cbNameChange(int index);
    void on_changeNode();
    void on_eventlogShow();
    void on_cbTimeChange();

private:
    QTableView *m_pView;
    QPushButton *readBtn;
    QComboBox *cbName;
    PDataProcess *m_pDataProcess;
    QStandardItemModel *m_pModel;
    bool m_bSort;

    QDateTimeEdit *dateStart;
    QDateTimeEdit *dateEnd;
    QLineEdit *leWord;
    QCheckBox *cbStart;
    QCheckBox *cbEnd;
//    QTableView *nameView;
//    QStandardItemModel *model;
    QLineEdit *leName;
    QMenu *menu;

};

#endif // WEVENTLOGWIDGET_H
