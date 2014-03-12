//author: sun
//date:2011.09.29

#ifndef DETECTORMONITER_H
#define DETECTORMONITER_H

#include <QWidget>
#include "WPage.h"

namespace Ui {
    class DetectorMonitor;
}


class WDetectormoniter : public WPage
{
    Q_OBJECT
public:
    explicit WDetectormoniter(QWidget *parent = 0);
    ~WDetectormoniter();

signals:


public slots:

private slots:
    void On_pushButton_clicked(void);


private :
    Ui::DetectorMonitor *ui;

};

#endif // DETECTORMONITER_H
