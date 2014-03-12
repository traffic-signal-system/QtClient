#ifndef CLUSTERDLG_H
#define CLUSTERDLG_H

#include <QWidget>
#include <QStringListModel>
#include "ctnode.h"
#include "pdataprocess.h"

/*
 群界面
*/
namespace Ui {
    class ClusterDlg;
}

class WClusterDlg : public QWidget
{
    Q_OBJECT

public:
    explicit WClusterDlg(QWidget *parent = 0);
    ~WClusterDlg();
    void setDataProcess(PDataProcess*p);
    void showCtPatternData();
    void clearCtPatternData();

public slots:
    void on_leftBtn();
    void on_rightBtn();
    void on_leftOneBtn();
    void on_rightOneBtn();
    void on_clusterMoreBtn();
    void on_nodeMoreBtn();

    void on_cbCtNameChange(int index);
    void on_getCtCircle();//得到 方案号 群周期后 获取各个节点的 阶段配时号 和 配时时间，构造node节点
    void on_getCtNodeStage(quint8 nodeId);//取得阶段配时

    void on_mouseSelectCtNode(quint32);
    void on_cbCtNodeNameChange(int);
    void on_offsetChange(quint32);
    void on_appBtn();
    void on_readBtn();
    void on_cbCheck();
    void on_treeViewClick(QModelIndex);

    void on_addCTBtn();
    void on_delCTBtn();
    void on_readCTBtn();
    void on_appCTBtn();

    //void on_ctNameChange(int index);
    void on_ctNameChange(QString str);
    void on_ctDomainIdChange(QString str);
    void on_ctEnableChange(int index);
    void on_sbNodeDifChange(int);

//    void on_ctPatternAddBtn();
    void on_ctPatternDelBtn();
    void on_ctPatternReadBtn();
    void on_ctPatternAppBtn();
    void on_ctPatternNoChange(int);
    void on_ctPatternCircle(int);
    void on_ctPatternStagePattern(int);
    void on_ctPatternCtlMode();
    void on_ctPatternSbOffsetChange(int value);
    void on_ctPatternLeOffset(QString);
    void on_ctPatternLeCoor(QString);

    void on_rcvCtPattern();
    void on_ctNameModelChange();

private:
    Ui::ClusterDlg *ui;
    CtNodeContent *m_pNodeContent;
    bool m_bClusterMoreBtn;
    bool m_bNodeMoreBtn;
    quint8 m_ucKeyIndex;
    quint8 m_ucKeyOffset;
    PDataProcess *m_pDataProcess;
    QStringList m_ListCtNodeId;//与m_pNodeContent m_ListRelativeOffset m_ListNodePosIndex顺序一致
    QStringList m_ListCtNodeName;
    QList<quint8> m_ListCtNodeIndex;
    SClusterPattern* m_pCtPattern;
    bool m_bDlgInit;//
    int m_iCurCtIndex;//当前群 index

    //quint8 m_ucOffsetBase;//第一个节点的相位差
//    QStringListModel *m_pModelCtNodeName;


};

#endif // CLUSTERDLG_H
