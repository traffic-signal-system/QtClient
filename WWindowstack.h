//author: sun
//date:2011.09.29


#ifndef WINDOWSTACK_H
#define WINDOWSTACK_H

#include <QStackedWidget>
#include "wnodeparadlg.h"
#include "wtimebasedlg.h"
#include "wstagewidget.h"
#include "wphasewidget.h"
#include "wstatus.h"
#include "wdetwidget.h"
#include "weventlogwidget.h"
#include "clusterdlg.h"
#include "wvipdlg.h"
#include "WUserViewDlg.h"
#include "WUserLogIn.h"
#include "wsystempara.h"
#include "wconflct.h"
#include "WTraffic.h"
#include "wscheduledlg.h"

/*
 ´°¿ÚÈÝÆ÷
*/
namespace Ui {
    class Windowstack;
}

//class WDetectormoniter;
class PDataProcess;

class WWindowstack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit WWindowstack(QWidget *parent = 0);
    ~WWindowstack();

    void setProcessor(PDataProcess *processor);

    void setWidgetIndex(int index);//1110try
signals:

public slots:


private:
//    WDetectormoniter *m_detectormonitor;
    PDataProcess *m_pDataProcess;
    WNodeParaDlg *m_NodeParaDlg;
    WTimeBaseDlg *m_TimeBaseDlg;
    WStageWidget *m_Stage;
    WPhaseWidget *m_PhaseDlg;
    WStatus *m_StatusDlg;
    WDetWidget *m_DetDlg;
    WEventLogWidget *m_EventDlg;
    WClusterDlg *m_ClusterDlg;
    WVipDlg *m_VipDlg;
    WUserLogIn *m_UserLogIn;
    WUserViewDlg *m_UserView;
    WSystemPara *m_SystemPara;
    WConflct *m_Conflict;
    WTraffic *m_Traffic;
    WScheduleDlg *m_Schedule;
};

#endif // WINDOWSTACK_H
