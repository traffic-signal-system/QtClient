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
 �׶���ʱ  ʱ�����
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
    void setCurStageTime(quint8 patternId);//��ʱ��
    quint8 getCurStageTime();//��ʱ��id
    void setStageTimeText(quint8 patternId);//��ʱid

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
    quint8 m_ucStagePatternId;//�׶���ʱ��
    quint8 m_ucStageNo;//�׶κ�

    //quint16 m_usGreenChannel;//������λ

//    quint8 m_ucTimeGreen;//�̵�ʱ��
//    quint8 m_ucTimeYellow;//�Ƶ�ʱ��
//    quint8 m_ucTimeRed;//���ʱ��

    quint8 m_ucOption;//ѡ�����

    bool m_bOptionBtnClick;


};

#endif // WTIMESET_H
