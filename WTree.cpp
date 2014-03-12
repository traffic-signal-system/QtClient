//author: sun
//date:2011.09.29


#include "WTree.h"
#include "ui_tree.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QMouseEvent>

WTree::WTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tree)
{
    QAction *acDel = new QAction(tr("删除"),this);
    QAction *acAdd = new QAction(tr("添加"),this);
    m_pMenu = new QMenu(this);
    m_pMenu->addAction(acDel);
    m_pMenu->addAction(acAdd);
    ui->setupUi((QWidget*)(this->parent()));
    ui->treeView->setDragEnabled(true);
    ui->treeView->setAcceptDrops(true);
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_treeViewClick(QModelIndex)));
}

WTree::~WTree()
{
    delete ui;
}

void WTree::setDataProcess(PDataProcess *dp)
{
    m_pDataProcess = dp;
    ui->treeView->setModel(m_pDataProcess->m_TscNameIconModel);
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),m_pDataProcess,SLOT(on_treeViewClick(QModelIndex)));
    //connect(ui->treeView,SIGNAL(pressed(QModelIndex)),m_pDataProcess,SIGNAL(clickTreeView(QModelIndex)));
    connect(ui->treeView,SIGNAL(pressed(QModelIndex)),dp,SLOT(on_treeViewRightClick(QModelIndex)));
    connect(dp,SIGNAL(nodeChangeIndex(int)),this,SLOT(on_nodeIdChange(int)));
//    connect(dp,SIGNAL(tabWidgetChange(int)),this,SLOT(on_tabWidgetChange(int)));
}

void WTree::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<e->button()<<e->pos()<<"mouse press";
}

void WTree::on_treeViewClick(QModelIndex index)
{
    if(index.isValid())
    {qDebug()<<"on_treeViewClick-------------------------------------------------------------------------"<<index.row();

        QString str = m_pDataProcess->m_TscNameIconModel->data(index).toString();
        qDebug()<<index.row()<<index.column()<<str;
        if(QApplication::mouseButtons()&&Qt::NoButton)
        {
            qDebug()<<"nobutton";
        }
        else if(QApplication::mouseButtons()&&Qt::RightButton)
        {
            qDebug()<<"rightbutton";
        }
    }
}

void WTree::on_nodeIdChange(int index)
{
    if(index!=-1)
    {
        QModelIndex mIndex;
        int cnt = 0;
        switch(m_pDataProcess->m_iTabWidgetIndex)
        {
        case 0:
            break;
        case 1:
            qDebug()<<"on_nodeIdChange------------------------dddddddddddd-------------------------------"<<index;
            mIndex = ui->treeView->model()->index(index,0);
            break;
        case 2:
            mIndex = ui->treeView->model()->index(index,0);
            break;
        case 3:
            cnt = m_pDataProcess->m_TscNameList.count();
            mIndex = ui->treeView->model()->index(index+cnt,0);
            break;
        default:
            break;
        }

        ui->treeView->setCurrentIndex(mIndex);
        if(!m_pDataProcess->m_bFlagNodeNameFocus)
            ui->treeView->setFocus();
    }
}

//void WTree::on_tabWidgetChange(int index)
//{
//    QString title;
//    switch(index)
//    {
//    case 0:
//        break;
//    case 1:
//        title = tr("节点列表");
//        break;
//    case 2:
//        title = tr("群列表");
//        break;
//    case 3:
//        title = tr("VIP列表");
//        break;
//    default:
//        break;
//    }

//    QHeaderView *h = ui->treeView->header();

//}
