#ifndef WCONFLCT_H
#define WCONFLCT_H

#include <QWidget>
#include "wdirectionform.h"
#include "pdataprocess.h"

namespace Ui {
    class WConflct;
}

class WConflct : public QWidget
{
    Q_OBJECT

public:
    explicit WConflct(QWidget *parent = 0);
    ~WConflct();
    void setDataProcess(PDataProcess *p);
    void changeNode();
    void setOverlapConnect(Overlap_Table *p);
    void setComPhaseList(QList<quint8>list);
    void createCheckArray(QList<quint8>list);
    void setChectArrayData();
public slots:
    void on_rcvPhase();
    void on_rcvConflict();
    void on_leftClick(bool,quint8);
    void on_rightClick(bool,quint8);
    void on_btnApp();
    void on_btnRead();
    void on_checkBoxChange();

private:
    Ui::WConflct *ui;
    WDirectionForm *m_pWid;
    PDataProcess *m_pDataProcess;
    PhaseConflict_Table* m_pConflict;
    QList<quint8> m_listPhaseId;
    QList<QLabel*> m_listLabel;
    QList<QLabel*> m_listLabel1;
    QList<QCheckBox*> m_listCheck;
    bool m_bDataInit;//数据初始化时（setCheckArrarData 为false)不响应
//    QGridLayout *m_LayoutCheck;
};

#endif // WCONFLCT_H
