#include "weventlogwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>
#include <QLabel>
#include <QDateTime>
#include <QStringList>
#include <QAction>


WEventLogWidget::WEventLogWidget(QWidget *parent) :
    QWidget(parent)
{
    m_pView = new QTableView();
    m_pView->setMinimumWidth(720);
    m_pModel = NULL;
    m_pDataProcess = NULL;
    m_bSort = false;
    readBtn =new QPushButton(tr("查询"));
    cbName = new QComboBox;
    QLabel *lbNodeName = new QLabel(tr("节点名："));
    QLabel *lbStart = new QLabel(tr("开始："));
    QLabel *lbEnd = new QLabel(tr("结束："));
    QLabel *lbWord = new QLabel(tr("事件关键字："));
//    model = new QStandardItemModel();
//    QAction *action1 = new QAction(tr("节点1"),cbName);
//    QAction *action2 = new QAction(tr("节点2"),cbName);
//    QAction *action3 = new QAction(tr("节点3"),cbName);
//    action1->setCheckable(true);
//    action2->setCheckable(true);
//    action3->setCheckable(true);
//    cbName->addAction(action1);
//    cbName->addAction(action2);
//    cbName->addAction(action3);
//    cbName->addAction();

//    model->setItem(0,(QStandardItem*)box1);

//    nameView = new QTableView();
//    nameView->setModel(model);
//    nameView->setFixedHeight(40);
//    nameView
//    ckNodeName = new CheckGroup();
    leName = new QLineEdit;
//    menu = new QMenu();
//menu->setTearOffEnabled(true);
//    menu->addAction(action1);
//    menu->addAction(action2);
//    menu->addAction(action3);
    dateStart = new QDateTimeEdit;
    dateEnd = new QDateTimeEdit;
    leWord = new QLineEdit;
    leWord->setToolTip(tr("以中文逗号分隔"));

    cbStart = new QCheckBox;
    cbEnd = new QCheckBox;

    QHBoxLayout *hStart = new QHBoxLayout;
    QHBoxLayout *hEnd = new QHBoxLayout;
    QHBoxLayout *hBtn = new QHBoxLayout;
    hStart->addWidget(lbStart);
    hStart->addWidget(cbStart);
    hStart->addStretch();
    hEnd->addWidget(lbEnd);
    hEnd->addWidget(cbEnd);
    hEnd->addStretch();
    hBtn->addStretch();
    hBtn->addWidget(readBtn);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(lbNodeName,0,0);
    grid->addWidget(cbName,1,0);
//    grid->addWidget(lbStart,2,0);
//    grid->addWidget(cbStart,2,1);
    grid->addLayout(hStart,2,0);
    grid->addWidget(dateStart,3,0);
//    grid->addWidget(lbEnd,4,0);
//    grid->addWidget(cbStart,2,1);
    grid->addLayout(hEnd,4,0);
    grid->addWidget(dateEnd,5,0);
    grid->addWidget(lbWord,6,0);
    grid->addWidget(leWord,7,0);
    grid->addLayout(hBtn,8,0);
//    grid->addWidget(readBtn,8,0);
//    QHBoxLayout *hBtnLayout = new QHBoxLayout;
//    QHBoxLayout *hBtnLayout1 = new QHBoxLayout;
////    hBtnLayout->addStretch();
////    hBtnLayout->addWidget(cbName);
//    hBtnLayout->addWidget(lbStart);
//    hBtnLayout->addWidget(dateStart);

//    hBtnLayout->addWidget(lbEnd);
//    hBtnLayout->addWidget(dateEnd);
//    hBtnLayout->addStretch();
////    hBtnLayout1->addStretch();
//    hBtnLayout1->addWidget(lbWord);
//    hBtnLayout1->addWidget(leWord);

//    hBtnLayout1->addWidget(readBtn);
//    hBtnLayout1->addStretch();

//    QVBoxLayout *vLayout1 = new QVBoxLayout;
//    vLayout1->addLayout(hBtnLayout);
//    vLayout1->addLayout(hBtnLayout1);


//    vLayout->addStretch();

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addLayout(grid);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
//    vLayout->addWidget(m_pView);
//    vLayout->addLayout(hLayout);

    QHBoxLayout *hMainLayout = new QHBoxLayout(this);
    hMainLayout->addStretch();
    hMainLayout->addWidget(m_pView);
    hMainLayout->addLayout(vLayout);

//    hMainLayout->addLayout(vLayout);
    hMainLayout->addStretch();

    connect(readBtn,SIGNAL(clicked()),this,SLOT(on_readBtn()));
    QDateTime time = QDateTime::currentDateTime();
    dateEnd->setDateTime(time);

}

WEventLogWidget::~WEventLogWidget()
{
    qDebug()<<"~WEventLogWidget()";
}

void WEventLogWidget::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    m_pModel = p->m_pModelEventLog;
    m_pView->setModel(m_pModel);
//    m_pView->setColumnWidth(0,160);
//    m_pView->setColumnWidth(1,290);
    cbName->setModel(m_pDataProcess->m_EventNameModel);
//    cbName->setModel(model);
    m_pView->setColumnWidth(0,90);
    m_pView->setColumnWidth(1,160);
    m_pView->setColumnWidth(2,220);
    //m_pView->verticalHeader()->hide();
   // m_pView->setVerticalHeader(QHeaderView(Qt::Vertical));
    connect(m_pView->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(on_sort(int)));
//    connect(cbName,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbNameChange(int)));

    connect(p,SIGNAL(changeNodeId()),this,SLOT(on_changeNode()));
    connect(p,SIGNAL(eventlogShow()),this,SLOT(on_eventlogShow()));

    connect(cbStart,SIGNAL(clicked()),this,SLOT(on_cbTimeChange()));
    connect(cbEnd,SIGNAL(clicked()),this,SLOT(on_cbTimeChange()));
}

void WEventLogWidget::mousePressEvent(QMouseEvent *)
{
    qDebug()<<"mousePressEvent";
//    menu->move();
//    menu->hideTearOffMenu();
//    menu->popup(this->mapToGlobal(e->pos()));
}

void WEventLogWidget::on_readBtn()
{
//    m_pDataProcess->requireTscTable(TSC_TABLE_EVENTLOG);
//    QDateTime timeStart = dateStart->dateTime();
//    QDateTime timeEnd = dateEnd->dateTime();
    QString str = leWord->text();
//    m_pDataProcess->m_uiEventLogStart = timeStart.toTime_t();
//    m_pDataProcess->m_uiEventLogEnd = timeEnd.toTime_t();
    on_cbTimeChange();
    m_pDataProcess->m_ListEventLogSearch.clear();
    QStringList list;
    if(str.contains(tr("，")))
    {
        list = str.split(tr("，"));
    }
    else
    {
        list.append(str);
    }
    if(!str.isEmpty())
    {
        m_pDataProcess->m_ListEventLogSearch<<list;
    }
    m_pDataProcess->clearEventLogModel();
    m_pDataProcess->requireTscEvent(cbName->currentIndex());
}

void WEventLogWidget::on_sort(int index)
{
    //qDebug()<<"click"<<index;
    m_bSort = !m_bSort;
    if(m_bSort)
    {
        m_pModel->sort(index,Qt::AscendingOrder);
    }
    else
    {
        m_pModel->sort(index,Qt::DescendingOrder);
    }
}

void WEventLogWidget::on_cbNameChange(int index)
{
    m_pDataProcess->clearEventLogModel();
    m_pDataProcess->requireTscEvent(index);
}

void WEventLogWidget::on_changeNode()
{
    if(m_pDataProcess->m_bFlagShowEventLog)
    {
        on_readBtn();
    }
}

void WEventLogWidget::on_eventlogShow()
{
//    QStringList list;
//    list.append(m_pDataProcess->m_TscNameList);
//    ckNodeName->setCheckBoxes(list);
//    cbName->setItemDelegate(m_pDataProcess->ckNodeNameDeligate);
////    nameView->setItemDelegateForColumn(0,m_pDataProcess->ckNodeNameDeligate);
//    m_pView->setItemDelegateForColumn(1,m_pDataProcess->ckNodeNameDeligate);
    qDebug()<<"on_eventlogShow";

}

void WEventLogWidget::on_cbTimeChange()
{
    if(cbStart->isChecked())
    {
        QDateTime timeStart = dateStart->dateTime();
        m_pDataProcess->m_uiEventLogStart = timeStart.toTime_t();
    }
    else
    {
        QDateTime timeStart = QDateTime::currentDateTime();
        m_pDataProcess->m_uiEventLogStart = 0;
    }

    if(cbEnd->isChecked())
    {
        QDateTime timeEnd = dateEnd->dateTime();
        m_pDataProcess->m_uiEventLogEnd = timeEnd.toTime_t();
    }
    else
    {
        QDateTime timeEnd = QDateTime::currentDateTime();
        m_pDataProcess->m_uiEventLogEnd = timeEnd.toTime_t();
    }
}
