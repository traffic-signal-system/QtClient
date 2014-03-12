#ifndef WPHASEWIDGET_H
#define WPHASEWIDGET_H

#include <QWidget>
#include "phase.h"
#include "pdataprocess.h"
#include <QTimer>

namespace Ui {
    class WPhaseWidget;
}

class WPhaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WPhaseWidget(QWidget *parent = 0);
    ~WPhaseWidget();
    void init();
    void createDirection();
    void createComPhase();
    void createOverlapPhase();
    void createChannel();
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
//    void timerEvent(QTimerEvent *);
    //---------dlgChl------------
    void dlgChlInit();
    void showChlDlg(bool b);
    void setChlDlg();//���� ��λ���� ����ģʽ ����
//    void getChlDlg();//��ȡ����ͨ���� ��λ
    //------------dlgCom---------
    void dlgComInit();
    void showComDlg(bool b);
    void setComDlg();
//    void getComDlg();
    //--------------dlgOverlap--------
    void dlgOverlapInit();
    void showOverlapDlg(bool b);
    void setOverlapDlg();
//    void getOverlapDlg();
    //-------phase------------
    void clearPreClick();//ȥ����һ��click
    void showPhaseDlg(quint8 id,bool b);
    //-------dir----------------
    void dlgDirInit();
    void showDirDlg(bool b);
    void setStraightLoadNo(quint8 loadNo);
    void setDirDlg();
  //  void getDirDlg();
    int getListIndex(quint8 loadNo);//��loadNo�õ�list index
    int getListIndexByCbIndex(int index);
    int getDirCbNoIndex(quint8 loadNo);
    void setDataProcess(PDataProcess*p);
    void clearInterface();//�������
    void layoutAddChl(ChlIcon*icon);
    void getInterfaceData();//��ȡ��������
    void getChannelTableData();//��ȡ����ͨ����λ ͨ������ ֻ�� ���� ����������  �Զ� ȡֵ������������λ��������ı���Ч
    void getPhaseMapTabel();
    void getOverlapTable();//������λ ������λ
    void editOverlapPhaseDirect(quint8 overPhaseId);//�� ������λ ��ͨ�� �޷���ʱ������ȡ ��һ��������λ �ķ���
   // void setDirIconValid(quint8 index,bool b);
    void timerEvent(QTimerEvent *);
public slots:
    void on_loadClearPhase(quint8);
    //------dlgChl-------
    void on_chlBtnMore();
    void on_mouseClickChl(quint8 chlId,bool bClick,quint8 phaseId);
    void on_chlCbNoChange(int);
    void on_chlCbTypeChange(int);
    void on_chlCbLightChange(int);
    void on_chlCbModeChange(int);
    //------------phase----------
    void on_mouseClickPhase(quint8 phaseId,bool bClick);
    void on_mouseClickComContentPhase(quint8 contId,bool bClick,quint8 phaseId);//������λ����
    void on_mouseClickLoadContentPhase(quint8 contId,bool bClick,quint8 phaseId);//��������
    //----------comPhase---------
    void on_comBtnMore();
    void on_comCbIdChange(int);
    void on_comSbPedGreenChange(int);
    void on_comSbPedCleanChange(int);
    void on_comSbMinGreenChange(int);
    void on_comSbUnitDelayChange(int);
    void on_comSbMaxGreen1Change(int);
    void on_comSbFlashGreenChange(int);
    void on_comSbMaxGreen2Change(int);
    void on_comSbFixGreenChange(int);
    void on_comCbTypeChange(int);
    void on_comCbOptionChange(int);
//-----------overlapPhase--------------
    void on_overlapCbIdChange(int);
    void on_overlapCbTypeChange(int);
    void on_overlapSbTailGreenChange(int);
    void on_overlapSbTailYellowChange(int);
    void on_overlapSbTailRedChange(int);
    //--------------dir-----------
    void on_dirClearContent(quint8 id,bool b);
    void on_mouseDoubleClick(quint8 loadNo);
    void on_mouseClickDir(quint8 loadNo,bool bClick);
    void on_dirCbNoChange(int index);
    void on_dirCbComChange(int index);
    void on_dirCbOverlapChange(int index);
    void on_dirSbLoadChange(int value);
    void on_dirCbVoidChange();

    void on_rcvPhase();
    void on_btnApp();
    void on_btnRead();

//    void on_rcvPhaseMap();//������� �ֶ�ȡ��һ��  rcvPhase()�ź�
private:
    Ui::WPhaseWidget *ui;
    phaseWidget *m_pWidget;
    QList<WordIcon*> m_ListCom;
    QList<IconContent*> m_ListComChl;
    QList<WordIcon*> m_ListOverlap;
    QList<IconContent*> m_ListContentCom;
    QList<IconContent*> m_ListOverlapChl;
    QList<ChlIcon*> m_ListChl;
    QList<LoadIcon*> m_ListDir;
    bool m_bTimer;//true timer������
//    int m_iTimeId;
    bool m_bDlgInit;//dlg ��ɳ�ʼ��Ϊ true�����ݳ�ʼ���� �б仯�Ŵ洢

    quint8 m_ucClickChlId;
    quint8 m_ucClickContComIndex;
    quint8 m_ucClickLoadIndex;
    quint8 m_ucClickPhaseId;
    quint8 m_ucClickDirIndex;//m_ListDir index;
    //-----��һ��click������-----
    bool m_bChl;
    bool m_bLoadCont;//��������
    bool m_bComCont;//��������
    bool m_bPhase;//��������
    bool m_bDir;//·��
    bool m_bIconClick;//������ combobox
    //----------comPhase-----
    bool m_bComBtnMore;
    bool btry;
    //---------dir-----
    bool m_bDClick;//����˫�� �� ·�������

    PDataProcess *m_pDataProcess;
    Channel_Table* m_pTbChl;
    Phase_Table* m_pTbCom;
    Overlap_Table* m_pTbOverlap;
//    PhaseMap_Table* m_pTbDirMap;
};

#endif // WPHASEWIDGET_H
