#ifndef WDIRECTIONFORM_H
#define WDIRECTIONFORM_H

#include <QWidget>
#include <QGraphicsView>
#include <QLabel>
#define MAXCOMPHASE 32
#define DIRECTIONNUM 16
#define DIRECTIONTOTAL 20
#define DIRICONWIDTH 30
#define DIRICONHEIGHT 100
#include "pdataprocess.h"
//#include <QPainter>
//#include <QRectF>
#include "phase.h"
//---------------------------------------------------
class DirectionIcon : public QLabel
{
    Q_OBJECT
public:
    explicit DirectionIcon(quint8 id,QWidget *parent = 0);
    ~DirectionIcon();
    void init();//Ϊ�½ڵ�
    void initState();//Ϊ�µĽ׶�
    void analyseId();
    void paintEvent(QPaintEvent *);
    void setPhaseId(quint8 phaseId);
    quint8 getPhaseId();
    void setFlagValid(bool b);
    void setFlagGreen(bool b);
    void setIconGreen(bool b);
    void setIconRed(bool b);
    void setFlagYellow(bool b);
    void setFlagRed(bool b);
    void setPixGreen(QPixmap&pix);
    void setPixYellow(QPixmap&pix);
    void setPixRed(QPixmap&pix);
    void setPixNull(QPixmap&pix);
    void setPixConflict(QPixmap&pix);
    void setFlash(bool b);
    void setFlagFlashMode(bool b);
    void timerEvent(QTimerEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
    quint32 getPhase();//����24��λ
    void setFlagClickAble(bool b);
    void setFlagInclude(bool b);
    void setPedSmall(bool b);
    bool getFlagGreen();//Ϊ��ȡͼ����Ϣ
    bool getFlagValid();//Ϊͼ���һ�ι��� ��С
    bool getFlagClickAble();//ͼ���Ƿ�ɵ�� �ɵ���� �������� ��ͻ��λ
    QPixmap getGreenPix();
    //-------��ͻ��λ----------
    void setFlagConflict(bool b=true);
    void setFlagConflictGreen(bool b);
    void setConflictGreen(bool b);//���ڽ���checkѡ��ʱ ��ʾ��ɫͼ��

    void editConflict(bool);
//    void setConflictBase(PhaseConflict_Table*p);

signals:
    void includePhaseTurn(bool b);
    void mouseClick(bool b,quint8 phaseId);//�ı�������λʱ

    void leftClick(bool,quint8 phase);
    void rightClick(bool,quint8 phase);
public slots:
    void on_includePhaseTurn(bool b);
private:
    quint8 m_ucDirId;//1-20 �̶�ͼ�꣬ͼƬ�ɱ䣬λ�ü���С���䣨�������У�
    quint8 m_ucPhaseId;
    bool m_bValid;
    bool m_bGreen;
    bool m_bYellow;
    bool m_bRed;//��ʱ��ͻ��λ Ҳ��Ϊtrue
    bool m_bFlash;//true��ʾ��ɫ
    bool m_bFlashMode;//true ǰ����� false������
    bool m_bClick;
    bool m_bClickAble;
    QPixmap m_PixGreen;
    QPixmap m_PixYellow;
    QPixmap m_PixRed;
    QPixmap m_PixNull;
    QPixmap m_PixConflict;
    int m_iTimerId;
    bool m_bTimer;
    bool m_bInclude;//������λ��־
    quint8 m_ucIncludeNum;//������λ����
    quint8 m_ucDir;//���� 0����1����2�ϣ�3��

    //-------��ͻ��λ-------
    bool m_bConflict;//��ͻ��λ�����־ Ĭ��Ϊ false
    bool m_bRightClick;//��ͻ��λ�Ҽ�ѡȡ Ĭ��Ϊfalse
    bool m_bConflictGreen;//ѡ��������λ ����ѡ�����λ Ĭ��false ���ܵ�ָ��

    int m_iConflict;//��һ���׶��� �ǳ�ͻ��λ ����ʱ ��1�� ��NULL ʱ��1��
    //------------������λ ���� ������λ �޶�Ӧ����ʱ��ȡ ��һ�� ������λ����

    bool m_bClickAll;//�ܿ���

};

//---------------------------------------------------
namespace Ui {
    class WDirectionForm;
}

class WDirectionForm : public QWidget
{
    Q_OBJECT

public:
    explicit WDirectionForm(QWidget *parent = 0,bool bConflict=false);
    ~WDirectionForm();
    void setLayoutDir();
    void setBack(quint8 dir=0);
    QImage getBackImage();
    void setDirIconValid(quint8 index,bool b);
    void loadPixmap();
    int getListIconIndex(quint8 dirId);
    int getListPixIndex(quint8 dirId);
    QList<bool> getListFlagGreen();
    QList<QPixmap> getListPixGreen();
    quint16 getPhase();//������λ
    DirectionIcon* getIcon(quint8 phaseId);
//    void mouseReleaseEvent(QMouseEvent *);
//    void drawBackground(QPainter*painter,const QRectF&rect);
    void setLcdShow(bool b);
    void setLcdNum(int time);
    void setAllowPhase(quint16 phase);//0722��ӳ�ͻ��λ����

    void clearState();//���Ľ׶�
    void changeStage();//���Ľڵ�
    void setIconPixmap(QList<quint8>);//�ڸ��Ľڵ�ʱ ������Ҫ �� ֱ�� ͼ��
    void setFlagValid(QList<bool>);
    void setPhaseId(QList<quint8>);
    void setOverlapConnect(QList<quint8> listPhase);
    void setUnClickAble();
    void setFlagInitStageIcon(bool b);
    void killFlash();
//---------------��ͻ��λ
    void setConflict(quint8 phase,quint16 conflict,bool b=true);//�׶���ʱ b���� bΪtrueʱ conflictNum++��
    void setConflictBase(PhaseConflict_Table*p);
    void setConflictGreen(quint8 phaseId,bool b=true);
    //������λ
    void setOverlapBase(Overlap_Table *p);

signals:
    void mouseClick(bool b=true,quint8 phaseId=0);//������λ
    void leftClick(bool,quint8);
    void rightClick(bool,quint8);
public slots:
//    void on_mouseClick(quint8 phase);
    void on_leftClick(bool,quint8);
    void on_rightClick(bool,quint8);

private:
    Ui::WDirectionForm *ui;
    QList<QLayout*> m_ListLayout;
    QList<DirectionIcon*> m_ListDirIcon;
    QList<QPixmap> m_ListPix;
    QImage m_img;
    bool m_bInitStageIcon;//��������λ ��ȡ ͼ��ʱ ��emit mouseClick() ��ɳ�ʼ��Ϊ true
    bool m_bConflict;
    PhaseConflict_Table *m_pConflictBase;

    Overlap_Table *m_pOverlapBase;
};

//-----------------------------------------------------------------------
class StageGroup : public QWidget
{
    Q_OBJECT

public:
    explicit StageGroup(QWidget *parent = 0);
    ~StageGroup();
    void addStage(phaseWidget*icon=NULL);
    void setListAllowGreen(QList<bool> listGreen,QList<QPixmap>listPix,quint16 phase=0);
    void clearGroup();
    void delIcon();
    void setBack(quint8 dir=0);
    void setIconWidth();
    void getStageIndex(quint8 &index,quint8 &cnt);//��ȡ��ǰ �׶� ��λ����Ϣ
    void setIconDark(quint8 index);
    void mouseClick(quint8 index);

signals:
    void mouseClick(quint16 phase);//���� ���ͼ�� ���� ������λ
   // void mouseClick(quint8 stageId);

public slots:
    void on_mouseClick(phaseWidget*);//���ͼ��

private:
//    QWidget *m_pForm;
    QHBoxLayout *m_pLayoutGroup;
    QList<phaseWidget*> m_pListIcon;
    phaseWidget *m_pIcon;
    quint8 m_ucDir;//dir: 0xff  8�� 7���� 6�� 5���� 4�� 3���� 2�� 1������ʱֻ��4���� ��
    //bool m_bClickPhase;//Ĭ��Ϊtrue ͼ����ʱ ���� ������λ��false���� ͼ�� �׶κ�
};
#endif // WDIRECTIONFORM_H
