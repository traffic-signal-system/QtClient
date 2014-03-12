#ifndef BROADCASTFORM_H
#define BROADCASTFORM_H

#include <QWidget>
#include "PDataProcess.h"

namespace Ui {
class BroadCastForm;
}

class BroadCastForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit BroadCastForm(QWidget *parent = 0);
    ~BroadCastForm();
    void setDataProcess(PDataProcess*p);

public slots:
    void on_bcBtnClick();
private:
    Ui::BroadCastForm *ui;
    PDataProcess *m_pDataProcess;
};

#endif // BROADCASTFORM_H
