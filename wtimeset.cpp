#include "wtimeset.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QBrush>
#include <QLineEdit>
#include <QGroupBox>

#include <QDebug>

WTimeSet::WTimeSet(QWidget *parent) :
    QWidget(parent)
{
    init();

    m_bOptionBtnClick = false;
    lbOption->hide();
    cbOption->hide();

    sbStageTime->setRange(1,200);
    setEditable(false);
    leStageIndex->setEnabled(false);

    //try
//    cbStagePatternId->setEditable(true);
//    cbStagePatternId->setEditText(QObject::tr("配时"));

    connect(sbStageTime,SIGNAL(valueChanged(int)),this,SLOT(on_sbStageTime(int)));

    connect(optionBtn,SIGNAL(clicked()),this,SLOT(on_OptionBtn()));
    connect(cbStagePatternId,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(StageTimeChange(QString)));

}

void WTimeSet::init()
{
    this->setMaximumWidth(140);
    QLabel *lbStagePattern = new QLabel(tr("阶段配时:"));
    QLabel *lbStageIndex = new QLabel(tr("阶段号:"));
    QLabel *lbStageTime = new QLabel(tr("阶段时间:"));


    cbStagePatternId = new QComboBox();

    leStageIndex = new QLineEdit;
    sbStageTime = new QSpinBox();

    QHBoxLayout *topHLayout = new QHBoxLayout;

    QVBoxLayout *leftVLayout = new QVBoxLayout;
    leftVLayout->addWidget(lbStagePattern);
    leftVLayout->addWidget(lbStageIndex);
    leftVLayout->addWidget(lbStageTime);

    QVBoxLayout *rightVLayout = new QVBoxLayout;
    rightVLayout->addWidget(cbStagePatternId);
    rightVLayout->addWidget(leStageIndex);
    rightVLayout->addWidget(sbStageTime);

    topHLayout->addLayout(leftVLayout);
    topHLayout->addLayout(rightVLayout);

    m_pColorWidget = new ColorWidget;

    optionBtn = new QPushButton(tr("更多>>"));
    lbOption = new QLabel(tr("选项参数:"));
    cbOption = new QComboBox();


    QHBoxLayout *btnHLayout = new QHBoxLayout;
    btnHLayout->addStretch();
    btnHLayout->addWidget(optionBtn);
    QHBoxLayout *optionHLayout = new QHBoxLayout;
    optionHLayout->addWidget(lbOption);
    optionHLayout->addWidget(cbOption);

//    addBtn = new QPushButton(tr("添加"));
//    delBtn = new QPushButton(tr("删除"));
//    QHBoxLayout *bottomHLayout = new QHBoxLayout;
//    bottomHLayout->addStretch();
//    bottomHLayout->addWidget(addBtn);
//    bottomHLayout->addWidget(delBtn);
//    bottomHLayout->addStretch();

    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    mainVLayout->addLayout(topHLayout);
    mainVLayout->addWidget(m_pColorWidget);
    mainVLayout->addLayout(btnHLayout);
    mainVLayout->addLayout(optionHLayout);
    //mainVLayout->addLayout(bottomHLayout);
    mainVLayout->setSizeConstraint(QLayout::SetFixedSize);

    int RWidth = 65;
    cbStagePatternId->setMaximumWidth(RWidth);
    leStageIndex->setMaximumWidth(RWidth);
    sbStageTime->setMaximumWidth(RWidth);
    cbOption->setMaximumWidth(RWidth);
    int BWidth = 50;
    optionBtn->setMaximumWidth(BWidth);
//    addBtn->setMaximumWidth(BWidth);
//    delBtn->setMaximumWidth(BWidth);


}

WTimeSet::~WTimeSet()
{
}

void WTimeSet::setTimeValue(quint8 green, quint8 yellow, quint8 red)
{
    m_pColorWidget->setTimeValue(green,yellow,red);

}

void WTimeSet::setStageTime(quint8 stagetime)
{
    sbStageTime->setValue(stagetime);
}
//void WTimeSet::clearTimeValue()
//{
//}

quint8 WTimeSet::getTimeGreen()
{
    return m_pColorWidget->getTimeGreen();
}

quint8 WTimeSet::getTimeYellow()
{
    return m_pColorWidget->getTimeYellow();
}

quint8 WTimeSet::getTimeRed()
{
    return m_pColorWidget->getTimeRed();
}

void WTimeSet::setEditable(bool b)
{
    m_pColorWidget->setEditable(b);
    sbStageTime->setEnabled(b);
}

void WTimeSet::setCurStageIndex(quint8 stageindex)
{
    m_ucStageNo = stageindex;
    QString str = QObject::tr(("阶段"));
    str+=QString::number(stageindex);
    leStageIndex->setText(str);
}

quint8 WTimeSet::getCurStageIndex()
{
    return m_ucStageNo;
}

void WTimeSet::setCurStageTime(quint8 StagePatternId)
{
    QString str = QObject::tr("配时");
    str+=QString::number(StagePatternId);
    int index = cbStagePatternId->findText(str);
    if(index!=-1)
    {
        cbStagePatternId->setCurrentIndex(index);
        m_ucStagePatternId = StagePatternId;
    }

}

quint8 WTimeSet::getCurStageTime()
{

    return m_ucStagePatternId;
}

void WTimeSet::setStageTimeText(quint8 StagePatternId)
{
    QString str = QObject::tr("配时");
    m_ucStagePatternId = StagePatternId;
    str+=QString::number(StagePatternId);
    int index = cbStagePatternId->findText(str);
    if(index!=-1)
    {
        cbStagePatternId->setCurrentIndex(index);
    }
    else
    {
        //qDebug()<<"setedit stageid:"<<str;
        cbStagePatternId->setEditable(true);
        cbStagePatternId->setEditText(str);
    }

}

void WTimeSet::setStageTimeModel(QStringListModel*model)
{
    cbStagePatternId->setModel(model);
}

//----------------------------------------
void WTimeSet::on_sbStageTime(int stagetime)
{
    //quint8 yellow = m_pColorWidget->getTimeYellow();
    //quint8 red = m_pColorWidget->getTimeRed();
    //sbStageTime->setMinimum(yellow+red+1);
    m_pColorWidget->setStageTime(stagetime);
}

void WTimeSet::on_OptionBtn()
{

    m_bOptionBtnClick = !m_bOptionBtnClick;
    if(m_bOptionBtnClick)
    {
        optionBtn->setText(tr("<<隐藏"));
        lbOption->show();
        cbOption->show();
    }
    else
    {
        optionBtn->setText(tr("更多>>"));
        lbOption->hide();
        cbOption->hide();
    }
}
