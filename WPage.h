#ifndef WPAGE_H
#define WPAGE_H

#include <QWidget>
//class PDataProcess;
#include "PDataProcess.h"

/*
 ·ÏÆú
*/
class WPage : public QWidget
{
    Q_OBJECT
public:
    explicit WPage(QWidget *parent = 0);
    virtual ~WPage() = 0{}

    void setProcessor(PDataProcess *processor);

private:
    virtual void receiveMessage(void *);
    virtual void sendMessage(void *);


signals:

public slots:

protected:
    PDataProcess *m_pDataProcess;

};

#endif // WPAGE_H
