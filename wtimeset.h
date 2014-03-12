#ifndef WTIMESET_H
#define WTIMESET_H

#include <QWidget>

#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include "colorwidget.h"
#include <QStringListModel>

//#include "dragicon.h"

/*
 阶段配时  时间调整
*/
class WTimeSet : public QWidget
{
    Q_OBJECT
public:
    explicit WTimeSet(QWidget *parent = 0);
    void init();
    ~WTimeSet();

    void setTimeValue(quint8 green=13,quint8 yellow=3,quint8 red=3);
    void setStageTime(quint8);
    //void clearTimeValue();
    quint8 getTimeGreen();
    quint8 getTimeYellow();
    quint8 getTimeRed();

    void setEditable(bool b);
    void setCurStageIndex(quint8 stageindex);
    quint8 getCurStageIndex();
    void setCurStageTime(quint8 patternId);//配时号
    quint8 getCurStageTime();//配时号id
    void setStageTimeText(quint8 patternId);//配时id

    void setStageTimeModel(QStringListModel*model);


signals:
    void StageTimeChange(QString str);

public slots:

    void on_sbStageTime(int);//
    void on_OptionBtn();


private:
    QComboBox *cbStagePatternId;
    QLineEdit *leStageIndex;
    QSpinBox *sbStageTime;
    ColorWidget *m_pColorWidget;

    QLabel *lbOption;
    QComboBox *cbOption;
    QPushButton *optionBtn;

//    QPushButton *addBtn;
//    QPushButton *delBtn;
    quint8 m_ucStagePatternId;//阶段配时号
    quint8 m_ucStageNo;//阶段号

    //quint16 m_usGreenChannel;//允许相位

//    quint8 m_ucTimeGreen;//绿灯时间
//    quint8 m_ucTimeYellow;//黄灯时间
//    quint8 m_ucTimeRed;//红灯时间

    quint8 m_ucOption;//选项参数

    bool m_bOptionBtnClick;


};

#endif // WTIMESET_H
