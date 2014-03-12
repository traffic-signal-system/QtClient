#include "wclusterdlg.h"
#include "ui_wclusterdlg.h"

WClusterDlg::WClusterDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WClusterDlg)
{
    ui->setupUi(this);
}

WClusterDlg::~WClusterDlg()
{
    delete ui;
}
