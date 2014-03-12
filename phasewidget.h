#ifndef PHASEWIDGET_H
#define PHASEWIDGET_H
#include "wordicon.h"
#include "loadicon.h"
#include "overlapcontent.h"
#include "loadparadlg.h"
#include "comphaseparadlg.h"
#include "overlapparadlg.h"
#include "pdataprocess.h"

#include <QGridLayout>

#define CHANNELNUM 16
#define COMMONPHASENUM 16
#define OVERLAPPHASENUM 8


#include <QWidget>

class PhaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhaseWidget(QWidget *parent = 0);
    ~PhaseWidget();
    void init();
    void createListLoadIcon(int num=CHANNELNUM);
    void setLoadIconPos();
    void createListComPhase(int num=COMMONPHASENUM);
    void setComPhasePos();
    void createListOverlapPhase(int num=OVERLAPPHASENUM);
    void setOverlapPos();
    void createListOverlapContent(int num=OVERLAPPHASENUM);

    void setListPoint();//用于将pDataProcess的 映射 list传递到 m_pListChannelId

    void setChannelData();//重新设置 num 及bPhase

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
    void paintEvent(QPaintEvent *);

    void setDataProcess(PDataProcess*p);
signals:

public slots:
    //void on_rcvWordIcon(WordIcon*);
    //void on_removeIcon(WordIcon*w);

    void on_WordIconDoubleClick(QPoint p,bool bPhase,quint8 phaseId/*,quint8 chlId*/);
    void on_LoadIconDoubleClick(QPoint p,quint8 loadNo,quint8 chlId);
    void on_LoadDirComboChange(int);

    void on_ReadBtn();
    void on_appBtn();

    void on_LoadDlgAppBtn(quint8 loadDir,quint8 chlId);

    void on_RcvPhase();//接收完普通相位表，跟随相位表，通道表，映射表后更新界面

private:
    QList<QPixmap> m_ListPix;
    QList<LoadIcon*> m_ListLoadIcon;

    QList<quint8>* m_pListComMap;
    QList<quint8>* m_pListOverlapMap;
    QList<quint8>* m_pListChannelMap;//方向对应的通道 指向 pDataProcess里的 list；

    QList<WordIcon*> m_ListComPhase;
    QList<WordIcon*> m_ListOverlapPhase;//放于 overlapcontent里
    QList<OverlapContent*> m_ListOverlapContent;
//    QLayout *m_pLayout1;
//    QLayout *m_pLayout2;
//    QLayout *m_pLayout3;
//    QLayout *m_pLayout4;
    QHBoxLayout *m_pLayout;
    LoadParaDlg *m_DlgLoad;
    ComPhaseParaDlg *m_DlgComPhase;
    OverlapParaDlg *m_DlgOverlap;
    QPushButton *readBtn;
    QPushButton *appBtn;
//    QLayout *m_pBottomLeftLayout;
//    QLayout *m_pBottomRightLayout;
   // QList<quint8> list;//try

    PDataProcess *m_pDataProcess;

};

#endif // PHASEWIDGET_H
