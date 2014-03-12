#include "broadcastform.h"
#include "ui_broadcastform.h"

BroadCastForm::BroadCastForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BroadCastForm)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
//    ui->groupBox->setFlat(true);
}

BroadCastForm::~BroadCastForm()
{
    delete ui;
}

void BroadCastForm::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    ui->tbViewTscIp->setModel(m_pDataProcess->m_pModelTscIp);
    ui->tbViewTscIp->setColumnWidth(0,300);
    ui->tbViewTscIp->setColumnWidth(1,100);
    ui->tbViewTscIp->setColumnWidth(2,100);
    connect(ui->bcBtn,SIGNAL(clicked()),this,SLOT(on_bcBtnClick()));
}

void BroadCastForm::on_bcBtnClick()
{
    m_pDataProcess->m_pModelTscIp->removeRows(0,m_pDataProcess->m_pModelTscIp->rowCount());
    m_pDataProcess->startBroadCast();
//    m_pDataProcess->requireTscInfoTable(NODE_EXIST);
}
