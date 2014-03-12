#ifndef WCLUSTERDLG_H
#define WCLUSTERDLG_H

#include <QWidget>

namespace Ui {
    class WClusterDlg;
}

class WClusterDlg : public QWidget
{
    Q_OBJECT

public:
    explicit WClusterDlg(QWidget *parent = 0);
    ~WClusterDlg();

private:
    Ui::WClusterDlg *ui;
};

#endif // WCLUSTERDLG_H
