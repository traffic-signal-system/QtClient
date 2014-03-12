#ifndef WSYSTEMPARA_H
#define WSYSTEMPARA_H

#include <QWidget>
#include "pdataprocess.h"

namespace Ui {
    class WSystemPara;
}

class WSystemPara : public QWidget
{
    Q_OBJECT

public:
    explicit WSystemPara(QWidget *parent = 0);
    ~WSystemPara();
    void setDataProcess(PDataProcess*p);
    void addTableName(int index,QList<quint32>&list);
    void timerEvent(QTimerEvent *);
public slots:
    void on_bcBtnClick();

    void on_btnSave();
    void on_btnRead();

private:
    Ui::WSystemPara *ui;
//    bool m_bFlag;
    PDataProcess *m_pDataProcess;
    QList<QCheckBox*> m_listCbSave;
    QList<QCheckBox*> m_listCbRead;
};

#endif // WSYSTEMPARA_H
