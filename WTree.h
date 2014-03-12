//author: sun
//date:2011.09.29

#ifndef TREE_H
#define TREE_H

#include <QWidget>
#include <QMenu>
#include "pdataprocess.h"

/*
 节点树
*/
namespace Ui {
    class Tree;
}

class WTree : public QWidget
{
    Q_OBJECT
public:
    explicit WTree(QWidget *parent = 0);
    ~WTree();

    void setDataProcess(PDataProcess *dp);
    void mousePressEvent(QMouseEvent *);

signals:


public slots:
    void on_treeViewClick(QModelIndex);
    void on_nodeIdChange(int);//节点 群 vip
//    void on_tabWidgetChange(int);

private:
    Ui::Tree *ui;
    QMenu *m_pMenu;
    PDataProcess *m_pDataProcess;
};

#endif // TREE_H
