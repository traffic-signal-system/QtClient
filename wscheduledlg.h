#ifndef WSCHEDULEDLG_H
#define WSCHEDULEDLG_H

#include <QWidget>

#include <QDialog>
#include "pdataprocess.h"
#include <QTableWidget>
#include <QTableView>
#include <QListView>
#include <QStandardItemModel>
#include <QRadioButton>
#include <QPushButton>
#include <QDateEdit>
#include <QDateTime>
#include <QCheckBox>
#include <QList>
#include <QComboBox>
#include <QLabel>
#include "CommClass.h"
/*
 ���ȼƻ�����
*/
class WScheduleDlg : public QDialog
{
    Q_OBJECT
public:
    explicit WScheduleDlg(QWidget *parent = 0);
    ~WScheduleDlg();
    void initDlg();

    void setDataProcess(PDataProcess *dp);
    void setInterfaceFromData(TimeBase_Table*);
    void getDataFromInterface(TimeBase_Table*);
//    void setWidgetsEnable(bool b);
    void setPatternDeligate();
    void timerEvent(QTimerEvent *);
    void startTimeOut();
    void clearInterface();
    void setCheckBoxEnable(bool b);
//    void showByIndex();
    quint8 getBaseNum(QString str);



signals:


public slots:
    void on_changeSpecialModel();//���ڸ��յ� ����ʱ
    void on_dataChange();
    void on_tabChange(int index);

    void on_clickTimebaseIndex(QModelIndex index);
    void on_clickSchIndex(QModelIndex index);//ʱ��
    void showSumSelect();

    void showSumBtn();
    void showSeason();

    void on_addBtn();
    void on_editBtn();
    void on_delBtn();
    void on_appBtn();
    void on_readBtn();

    void on_moreBtn();

    void on_addEventBtn();
    void on_delEventBtn();

    void on_addSchBtn();
    void on_editSchBtn();
    void on_delSchBtn();
    void on_appSchBtn();
    void on_readSchBtn();


    void on_rcvTimeBaseResponse(char*para1,int len);//д���ݿ�ʱ������ֵ
    void on_rcvScheduleResponse(char*para1,int len);

    void on_tbViewSelect(QModelIndex);//ѡ���б�ѡ�� ���½�������
    void on_schViewSelect(QModelIndex);//
    void on_eventViewSelect(QModelIndex);

    void on_updatePatternDeligate();//��Ӧ pdataprocess �� m_ListTimePatternName�б䶯 ��Ϣ
    void on_clusterClick(bool b);
    void on_ctBtn();

    void on_cbAllDay(bool b);
private:
    //QStandardItemModel *tbModel;
    //QTableView *tbView;
    QListView *tbView;

    QTabWidget *tabWidget;
    QWidget *normalWidget;
    QWidget *specialWidget;

    QCheckBox *selCB;
    QRadioButton *winRBtn;
    QRadioButton *sumRBtn;
    QPushButton *sumBtn;
 //   QPushButton *moreDateBtn;
//    QDateEdit *startDate;
//    QDateEdit *endDate;
    QComboBox *startMonthCB;
    QComboBox *endMonthCB;
    QWidget *sumWidget;

//    QCheckBox *sunCB;
//    QCheckBox *monCB;
//    QCheckBox *tueCB;
//    QCheckBox *wedCB;
//    QCheckBox *truCB;
//    QCheckBox *friCB;
//    QCheckBox *satCB;
    QList<QCheckBox*> weekDayList;
    QList<QCheckBox*> monthList;
    QList<QCheckBox*> monthDayList;



//    QStandardItemModel *schModel;
//    QTableView *schView;
    QLabel *startMonthLB;
    QLabel *endMonthLB;

    QComboBox *scheduleCB;
    QListView *schView;

    QPushButton *addSchBtn;
    QPushButton *editSchBtn;
    QPushButton *delSchBtn;
    QPushButton *appSchBtn;
    QPushButton *readSchBtn;

    QPushButton *addBtn;
    QPushButton *editBtn;
    QPushButton *appBtn;
    QPushButton *delBtn;
    QPushButton *readBtn;

    QComboBox *cbChoice;

    QPushButton *moreBtn;
    bool m_bMoreClick;
    QTableView *eventView;
    ComboxDeligate *ctrlDeligate;
    TimeEditDeligate *timeDeligate;
    ComboxDeligate *patternDeligate;

    bool m_bFlagBtn;//����ת����־

    bool m_bFlagAdd;
    bool m_bFlagEdit;
    bool m_bFlagDel;

    bool m_bFlagSchAdd;
    bool m_bFlagSchEdit;
    bool m_bFlagSchDel;

    QPushButton *addEventBtn;
    QPushButton *delEventBtn;

    TimeBase_Table *m_pTimeBase;
    byte m_ucTimeBaseIndex;//ʱ��������洢λ��

    quint8 m_ucScheduleIndex;//ʱ�α�����洢λ��
    quint8 m_ucEventIndex;//�б��� ѡ���е�λ�� ����ɾ��
   // byte m_ucTimeBaseNameIndex;//ʱ���б�λ��
    Schedule_Table *m_pSchedule;
    //byte m_ucScheduleIndex;

    PDataProcess *m_pDataProcess;

    //bool m_bFlagCluster;
    QPushButton *ctBtn;

    bool m_bTimeOut;//��ʱΪtrue
    bool m_bTimer;
    qint32 m_iTimerId;
    bool m_bClusterClick;
    quint8 m_ucBase;
    quint8 m_ucCount;
    bool m_bDataInit;//���ݳ�ʼ�� ���Ϊtrue

    QCheckBox*cbAllDay;//������ ȫѡ��ť

};

#endif // WSCHEDULEDLG_H
