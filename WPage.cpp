#include "WPage.h"


WPage::WPage(QWidget *parent) :
    QWidget(parent),
    m_pDataProcess(NULL)
{
}

void WPage::receiveMessage(void *)
{
    ;
}

void WPage::sendMessage(void *)
{
    ;
}

void WPage::setProcessor(PDataProcess *processor)
{
    m_pDataProcess = processor;
}
