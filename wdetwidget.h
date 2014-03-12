#ifndef WDETWIDGET_H
#define WDETWIDGET_H

#include <QWidget>
#include "detwidget.h"
/*
 ¼ì²âÆ÷½çÃæ
*/
namespace Ui {
    class WDetWidget;
}

class WDetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WDetWidget(QWidget *parent = 0);
    ~WDetWidget();
    void setDataProcess(PDataProcess*p);
public slots:
    void on_statusCheck();
    void on_appBtn();
    void on_readBtn();
    void on_upBtn();
    void on_downBtn();
    void on_flashBtn();

    void on_stopDetStatus(bool b=true);
private:
    Ui::WDetWidget *ui;
    DetWidget *m_DetDlg;
    PDataProcess *m_pDataProcess;
    QList<FlowWidget*> m_ListFlow;

    quint8 m_ucDetBase;//Á÷Á¿Í¼ ¼ì²âÆ÷ºÅ 1-28
};

#endif // WDETWIDGET_H
