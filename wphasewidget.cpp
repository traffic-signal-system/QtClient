#include "wphasewidget.h"
#include "ui_wphasewidget.h"
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include "DCommon.h"
#define DIRECTIONNUM MAX_PHASEMAP_NUM//二次过街另加不算在16个内
#define COMPHASENUM MAX_PHASE_NUM

#define CHANNELNUM MAX_CHANNEL_NUM
#define SHOWTIME 3000

WPhaseWidget::WPhaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WPhaseWidget)
{
    QWidget *w = new QWidget;
    ui->setupUi(w);
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hMainLayout = new QHBoxLayout(this);
    vLayout->addStretch();
    vLayout->addWidget(w);
    vLayout->addStretch();
    hMainLayout->addStretch();
    hMainLayout->addLayout(vLayout);
    hMainLayout->addStretch();
    init();
    m_bTimer = false;
    m_ucClickChlId = 0;
    m_bDlgInit = false;
    m_ucClickContComIndex = 0;
    m_ucClickLoadIndex = 0;
    m_ucClickPhaseId = 0;
    m_bLoadCont = false;//方向容器
    m_bComCont = false;//跟随容器
    m_bPhase = false;//非容器里
    m_bIconClick = false;
    m_bChl = false;
    m_bDir = false;
    m_ucClickDirIndex = 0;
    m_pDataProcess = NULL;
    m_pTbChl = NULL;
    m_pTbCom = NULL;
    m_pTbOverlap = NULL;
    m_bDClick = false;
//    m_iTimeId = 0;
//    m_pTbDirMap = NULL;
//    this->setToolTip(tr("步骤：\n1 配置实际路口路标（双击带直行路标可变换直左、左直右、直右、直四种状态；\n  双击人行可变换一次人行、二次人行；\n  点击路标参数框里的'有效'按钮选择路标的显示隐藏）\n2 为路标配置相位，确认相位参数框更多里的‘相位选择’是否为人行；\n3 为相位配置通道"));
//    ui->comCbOption->setEditable(true);
//    ui->comCbTpye->setEditable(true);
}

WPhaseWidget::~WPhaseWidget()
{
    delete ui;
}

void WPhaseWidget::init()
{
    //m_pWidget = new phaseWidget(ui->framPhase);
    QImage img;
    if(img.load(":/Files/images/back.jpg"))
    {
        qDebug()<<"img success phase widget";
    }
    QPalette p = ui->framPhase->palette();
    QBrush brush(img);
    //brush.setTextureImage(img);
    p.setBrush(QPalette::Background,brush);
    ui->framPhase->setPalette(p);
    this->setAcceptDrops(true);
    createDirection();
    createComPhase();
    createOverlapPhase();
    createChannel();
    dlgChlInit();
    dlgComInit();
    dlgOverlapInit();
    dlgDirInit();

    ui->chlBtnShow->hide();
    ui->comBtnMore->hide();
//    ui->groupBox_2
}

void WPhaseWidget::createDirection()
{
    ui->layoutNorth->setDirection(QBoxLayout::RightToLeft);
    ui->layoutEast->setDirection(QBoxLayout::BottomToTop);
    ui->layoutSouth->setDirection(QBoxLayout::LeftToRight);
    ui->layoutWest->setDirection(QBoxLayout::TopToBottom);
    ui->layoutNPed->setDirection(QBoxLayout::LeftToRight);
    ui->layoutEPed->setDirection(QBoxLayout::TopToBottom);
    ui->layoutSPed->setDirection(QBoxLayout::RightToLeft);
    ui->layoutWPed->setDirection(QBoxLayout::BottomToTop);
    //-------二次过街--------
    LoadIcon *pedN = new LoadIcon(0x2a);
    LoadIcon *pedE = new LoadIcon(0x4a);
    LoadIcon *pedS = new LoadIcon(0x6a);
    LoadIcon *pedW = new LoadIcon(0x8a);

    for(int i=0;i<DIRECTIONNUM;i++)//方向还是用16个，二次过街另加
    {
        LoadIcon *load = new LoadIcon(i+1);
        connect(load,SIGNAL(mouseClickPhase(quint8,bool,quint8)),this,SLOT(on_mouseClickLoadContentPhase(quint8,bool,quint8)));
        connect(load,SIGNAL(mouseClickDir(quint8,bool)),this,SLOT(on_mouseClickDir(quint8,bool)));
        connect(load,SIGNAL(clearContent(quint8,bool)),this,SLOT(on_dirClearContent(quint8,bool)));
        if(i%4==1||i%4==3)
        {

            connect(load,SIGNAL(mouseDoubleClick(quint8)),this,SLOT(on_mouseDoubleClick(quint8)));
        }
        m_ListDir.append(load);
        if(i<3)
        {
            ui->layoutNorth->addWidget(load);
        }
        else if(i==3)
        {
            ui->layoutNPed->addWidget(load);
            ui->layoutNPed->addWidget(pedN);
        }
        else if(i<7)
        {
            ui->layoutEast->addWidget(load);
        }
        else if(i==7)
        {
            ui->layoutEPed->addWidget(load);
            ui->layoutEPed->addWidget(pedE);
        }
        else if(i<11)
        {
            ui->layoutSouth->addWidget(load);
        }
        else if(i==11)
        {
            ui->layoutSPed->addWidget(load);
            ui->layoutSPed->addWidget(pedS);
        }
        else if(i<15)
        {
            ui->layoutWest->addWidget(load);
        }
        else
        {
            ui->layoutWPed->addWidget(load);
            ui->layoutWPed->addWidget(pedW);
        }
    }
    m_ListDir.append(pedN);
    m_ListDir.append(pedE);
    m_ListDir.append(pedS);
    m_ListDir.append(pedW);
    pedN->setFlagValid(false);
    pedE->setFlagValid(false);
    pedS->setFlagValid(false);
    pedW->setFlagValid(false);
    connect(pedN,SIGNAL(mouseDoubleClick(quint8)),this,SLOT(on_mouseDoubleClick(quint8)));
    connect(pedN,SIGNAL(mouseClickDir(quint8,bool)),this,SLOT(on_mouseClickDir(quint8,bool)));
    connect(pedN,SIGNAL(clearContent(quint8,bool)),this,SLOT(on_dirClearContent(quint8,bool)));

    connect(pedE,SIGNAL(mouseDoubleClick(quint8)),this,SLOT(on_mouseDoubleClick(quint8)));
    connect(pedE,SIGNAL(mouseClickDir(quint8,bool)),this,SLOT(on_mouseClickDir(quint8,bool)));
    connect(pedE,SIGNAL(clearContent(quint8,bool)),this,SLOT(on_dirClearContent(quint8,bool)));

    connect(pedS,SIGNAL(mouseDoubleClick(quint8)),this,SLOT(on_mouseDoubleClick(quint8)));
    connect(pedS,SIGNAL(mouseClickDir(quint8,bool)),this,SLOT(on_mouseClickDir(quint8,bool)));
    connect(pedS,SIGNAL(clearContent(quint8,bool)),this,SLOT(on_dirClearContent(quint8,bool)));

    connect(pedW,SIGNAL(mouseDoubleClick(quint8)),this,SLOT(on_mouseDoubleClick(quint8)));
    connect(pedW,SIGNAL(mouseClickDir(quint8,bool)),this,SLOT(on_mouseClickDir(quint8,bool)));
    connect(pedW,SIGNAL(clearContent(quint8,bool)),this,SLOT(on_dirClearContent(quint8,bool)));

    //------------
    connect(pedN,SIGNAL(mouseClickPhase(quint8,bool,quint8)),this,SLOT(on_mouseClickLoadContentPhase(quint8,bool,quint8)));
    connect(pedE,SIGNAL(mouseClickPhase(quint8,bool,quint8)),this,SLOT(on_mouseClickLoadContentPhase(quint8,bool,quint8)));
    connect(pedS,SIGNAL(mouseClickPhase(quint8,bool,quint8)),this,SLOT(on_mouseClickLoadContentPhase(quint8,bool,quint8)));
    connect(pedW,SIGNAL(mouseClickPhase(quint8,bool,quint8)),this,SLOT(on_mouseClickLoadContentPhase(quint8,bool,quint8)));
}

void WPhaseWidget::createComPhase()
{
    ui->layoutPhase->setColumnStretch(0,1);
    ui->layoutPhase->setColumnStretch(1,2);
    ui->layoutPhase->setColumnStretch(2,1);
    ui->layoutPhase->setColumnStretch(3,2);
    ui->layoutPhase->setColumnStretch(4,1);
    ui->layoutPhase->setColumnStretch(5,2);
    ui->layoutPhase->setColumnStretch(6,1);
    ui->layoutPhase->setColumnStretch(7,2);
    int rowNum = COMPHASENUM/4;
    for(int i=0;i<COMPHASENUM;i++)
    {
        WordIcon *comPhase = new WordIcon(i+1);
        IconContent *chlContent = new IconContent(true,i+1);//通道容器 1-COMPHASENUM
        m_ListCom.append(comPhase);
        m_ListComChl.append(chlContent);
        ui->layoutPhase->addWidget(comPhase,i%rowNum,i/rowNum*4);
        ui->layoutPhase->addWidget(chlContent,i%rowNum,i/rowNum*4+1);

        connect(comPhase,SIGNAL(mouseClick(quint8,bool)),this,SLOT(on_mouseClickPhase(quint8,bool)));
    }
}

void WPhaseWidget::createOverlapPhase()
{
    ui->layoutOverlap->setColumnStretch(0,1);
    ui->layoutOverlap->setColumnStretch(1,3);
    ui->layoutOverlap->setColumnStretch(2,2);
    ui->layoutOverlap->setColumnStretch(3,1);
    ui->layoutOverlap->setColumnStretch(4,3);
    ui->layoutOverlap->setColumnStretch(5,2);

    int rowNum = OVERLAPPHASENUM/4;
    for(int i=0;i<OVERLAPPHASENUM;i++)
    {
        WordIcon *overlap = new WordIcon(i+1+MAXCOMPHASE,false,false,false);
        IconContent *comContent = new IconContent(false,i+1);
        IconContent *amendContent = new IconContent(false,i+1+OVERLAPPHASENUM);
        QVBoxLayout *vLayout = new QVBoxLayout;
        vLayout->setMargin(0);
        vLayout->setSpacing(0);
        vLayout->addWidget(comContent);
        vLayout->addWidget(amendContent);
        IconContent *chlContent = new IconContent(true,i+1+MAXCOMPHASE/*i+1*/);//修改通道容器id 与 跟随相位id一致
        connect(comContent,SIGNAL(setOverlapValid(bool)),overlap,SLOT(on_setOverlapFlagValid(bool)));
        connect(amendContent,SIGNAL(setOverlapValid(bool)),overlap,SLOT(on_setOverlapFlagValid(bool)));
        connect(overlap,SIGNAL(mouseClick(quint8,bool)),this,SLOT(on_mouseClickPhase(quint8,bool)));
        connect(comContent,SIGNAL(mouseClickPhase(quint8,bool,quint8)),this,SLOT(on_mouseClickComContentPhase(quint8,bool,quint8)));
        connect(amendContent,SIGNAL(mouseClickPhase(quint8,bool,quint8)),this,SLOT(on_mouseClickComContentPhase(quint8,bool,quint8)));
        m_ListOverlap.append(overlap);
        m_ListContentCom.append(comContent);
        m_ListContentCom.append(amendContent);
        //m_ListContentAmend.append();
        m_ListOverlapChl.append(chlContent);
        ui->layoutOverlap->addWidget(overlap,i%rowNum,i/rowNum*3);
        ui->layoutOverlap->addLayout(vLayout,i%rowNum,i/rowNum*3+1);
        ui->layoutOverlap->addWidget(chlContent,i%rowNum,i/rowNum*3+2);

    }
}

void WPhaseWidget::createChannel()
{
    int colNum = CHANNELNUM/2;
    for(int i=0;i<CHANNELNUM;i++)
    {
        ChlIcon *icon = new ChlIcon(i+1);
        m_ListChl.append(icon);
        connect(icon,SIGNAL(mouseClick(quint8,bool,quint8)),this,SLOT(on_mouseClickChl(quint8,bool,quint8)));
        ui->layoutChl->addWidget(icon,i/colNum,i%colNum);
    }
}

void WPhaseWidget::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
    {
        QByteArray data = e->mimeData()->data("Drag-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        WordIcon *icon;
        stream>>i>>offset;
        icon = static_cast<WordIcon*>((void*)(i));
        if(icon->getFlagDirContent()||icon->getFlagOverlapContent())
        {
            if(children().contains(e->source()))
            {

                e->setDropAction(Qt::MoveAction);
                e->accept();
            }
            else
            {

                e->acceptProposedAction();
            }
        }

    }
    else if(e->mimeData()->hasFormat("Chl-Icon"))
    {
        if(children().contains(e->source()))
        {

            e->setDropAction(Qt::MoveAction);
            e->accept();
        }
        else
        {

            e->acceptProposedAction();
        }
    }
}

void WPhaseWidget::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasFormat("Drag-Icon"))
    {
        QByteArray data = e->mimeData()->data("Drag-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        WordIcon *icon;
        stream>>i>>offset;
        icon = static_cast<WordIcon*>((void*)(i));
        if(icon->getFlagDirContent()||icon->getFlagOverlapContent())
        {
            if(icon->getFlagDirContent())
            {
                quint8 id = icon->getId();
                if(id>0&&id<COMPHASENUM+1)
                {
                    m_ListCom[id-1]->setFlagUsed(false);
                }
                else if(id>MAXCOMPHASE&&id<MAXCOMPHASE+OVERLAPPHASENUM+1)
                {
                    m_ListOverlap[id-1-MAXCOMPHASE]->setFlagUsed(false);
                }
            }
            icon->close();
        }

    }
    else if(e->mimeData()->hasFormat("Chl-Icon"))
    {
        QByteArray data = e->mimeData()->data("Chl-Icon");
        QDataStream stream(&data,QIODevice::ReadOnly);
        QPoint offset;
        int i;
        ChlIcon *icon;
        stream>>i>>offset;
        icon = static_cast<ChlIcon*>((void*)(i));
        icon->setFlagUsed(false);
        layoutAddChl(icon);
//        int id = icon->getId();
//        ui->layoutChl->addWidget(icon,(id-1)/(CHANNELNUM/2),(id-1)%(CHANNELNUM/2));
    }
    else
    {
        e->ignore();
    }

    //        delete e->mimeData();
}

//void WPhaseWidget::timerEvent(QTimerEvent *)
//{
//    if(!ui->dlgFrameChl->isHidden())
//    {
////        if(chlDlgFocuse())
//        {
////            qDebug()<<"time out has focus";
//        }
////        else
////        {
////            this->killTimer(e->timerId());
////            m_bTimer = false;
////            hideChlDlg();
////        }
//    }

//}

void WPhaseWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    m_bDClick = !m_bDClick;
    showDirDlg(m_bDClick);
}

void WPhaseWidget::dlgChlInit()
{
    QStringList list;
    for(int i=0;i<CHANNELNUM;i++)
    {
        list.append(tr("通道%1").arg(i+1));
    }
    ui->chlCbNo->addItems(list);
    ui->chlFrameMore->hide();
    ui->chlLePhase->setReadOnly(true);
    ui->dlgFrameChl->hide();
    connect(ui->chlBtnShow,SIGNAL(clicked()),this,SLOT(on_chlBtnMore()));
    connect(ui->chlCbNo,SIGNAL(currentIndexChanged(int)),this,SLOT(on_chlCbNoChange(int)));
    connect(ui->chlCbType,SIGNAL(currentIndexChanged(int)),this,SLOT(on_chlCbTypeChange(int)));
    connect(ui->chlCbLight,SIGNAL(currentIndexChanged(int)),this,SLOT(on_chlCbLightChange(int)));
    connect(ui->chlCbMode,SIGNAL(currentIndexChanged(int)),this,SLOT(on_chlCbModeChange(int)));
    QPalette p = ui->dlgFrameChl->palette();
    p.setColor(QPalette::WindowText,Qt::yellow);
    ui->dlgFrameChl->setPalette(p);
}

void WPhaseWidget::showChlDlg(bool b)
{
    ui->dlgFrameChl->setVisible(b);
    if(b)
    {
        ui->chlFrameMore->show();
        showComDlg(false);
        showOverlapDlg(false);
        showDirDlg(false);
    }
    else
    {

        ui->chlFrameMore->hide();
    }
}

//void WPhaseWidget::hideChlDlg()
//{
//    ui->dlgFrameChl->hide();
//}

//bool WPhaseWidget::chlDlgFocuse()
//{
//    return ui->chlBtnShow->hasFocus()||ui->chlCbLight->hasFocus()
//                                     ||ui->chlCbMode->hasFocus()
//                                     ||ui->chlCbNo->hasFocus()
//                                     ||ui->chlCbType->hasFocus()
//                                     ||ui->chlLb1->hasFocus()
//                                     ||ui->chlLb2->hasFocus()
//                                     ||ui->chlLb3->hasFocus()
//                                     ||ui->chlLb4->hasFocus()
//                                     ||ui->chlLb5->hasFocus()
//                                     ||ui->dlgFrameChl->hasFocus();
//}

void WPhaseWidget::setChlDlg()
{

    if(m_pTbChl!=NULL)
    {
        quint8 mode = m_pTbChl->bControlMode;
        int lightIndex = mode&0x08?1:0;

        int flashIndex = 0;//关灯
        if(mode&0x04)
        {
            flashIndex = 2;
        }
        else if(mode&0x02)
        {
            flashIndex = 1;
        }

        quint8 typeIndex = 0;
        switch(m_pTbChl->bControlType)
        {
        case 2:
            typeIndex = 0;
            break;
        case 3:
            typeIndex = 1;
            break;
        case 4:
            typeIndex = 2;
            break;
        case 1:
            typeIndex = 3;
            break;
        default:
            break;
        }
        ui->chlCbType->setCurrentIndex(typeIndex);
        ui->chlCbLight->setCurrentIndex(lightIndex);
        ui->chlCbMode->setCurrentIndex(flashIndex);
    }
}

//void WPhaseWidget::getChlDlg()
//{

//}


void WPhaseWidget::dlgComInit()
{
    QStringList list;
    for(int i=0;i<COMPHASENUM;i++)
    {
        list.append(tr("相位%1").arg(i+1));
    }
    ui->comCbId->addItems(list);
    ui->dlgFrameCom1->setVisible(false);
    ui->dlgFrameCom2->setVisible(false);
    connect(ui->comBtnMore,SIGNAL(clicked()),this,SLOT(on_comBtnMore()));
    connect(ui->comCbId,SIGNAL(currentIndexChanged(int)),SLOT(on_comCbIdChange(int)));
    connect(ui->comSbPedGreen,SIGNAL(valueChanged(int)),this,SLOT(on_comSbPedGreenChange(int)));
    connect(ui->comSbPedClean,SIGNAL(valueChanged(int)),this,SLOT(on_comSbPedCleanChange(int)));
    connect(ui->comSbMinGreen,SIGNAL(valueChanged(int)),this,SLOT(on_comSbMinGreenChange(int)));
    connect(ui->comSbUnitDelay,SIGNAL(valueChanged(int)),this,SLOT(on_comSbUnitDelayChange(int)));
    connect(ui->comSbFlashGreen,SIGNAL(valueChanged(int)),this,SLOT(on_comSbFlashGreenChange(int)));
    connect(ui->comSbMaxGreen2,SIGNAL(valueChanged(int)),this,SLOT(on_comSbMaxGreen2Change(int)));
    connect(ui->comSbFixGreen,SIGNAL(valueChanged(int)),this,SLOT(on_comSbFixGreenChange(int)));
    connect(ui->comSbMaxGreen1,SIGNAL(valueChanged(int)),this,SLOT(on_comSbMaxGreen1Change(int)));
    connect(ui->comCbTpye,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comCbTypeChange(int)));
    connect(ui->comCbOption,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comCbOptionChange(int)));
//    m_bComBtnMore = false;
    QPalette p = ui->dlgFrameCom1->palette();
    p.setColor(QPalette::WindowText,Qt::yellow);
    ui->dlgFrameCom1->setPalette(p);
    p = ui->dlgFrameCom2->palette();
    p.setColor(QPalette::WindowText,Qt::yellow);
    ui->dlgFrameCom2->setPalette(p);
}

void WPhaseWidget::showComDlg(bool b)
{
    ui->dlgFrameCom1->setVisible(b);
    ui->dlgFrameCom2->setVisible(b/*&&m_bComBtnMore*/);
//    else
//    {
//        ui->dlgFrameCom1->hide();
//        if(!ui->dlgFrameCom2->isHidden())
//        {
//            ui->dlgFrameCom2->hide();
//        }
//    }
}

void WPhaseWidget::setComDlg()
{
    ui->comSbPedGreen->setValue(m_pTbCom->bPedestrianGreenTime);
    ui->comSbPedClean->setValue(m_pTbCom->bPedestrianClearTime);
    ui->comSbMinGreen->setValue(m_pTbCom->bMinGreenTime);
    ui->comSbUnitDelay->setValue(m_pTbCom->bDelayGreenUnit);
    ui->comSbMaxGreen1->setValue(m_pTbCom->bMaxGreenTime1);
    ui->comSbFlashGreen->setValue(m_pTbCom->bGreenFlashTime);
    ui->comSbMaxGreen2->setValue(m_pTbCom->bMaxGreenTime2);
    ui->comSbFixGreen->setValue(m_pTbCom->bFixedGreenTime);

    quint8 type = m_pTbCom->bPhaseType;
    quint8 option = m_pTbCom->bPhaseOption;
//    qDebug()<<"option"<<m_pTbCom->bNo<<m_pTbCom->bPhaseOption;

    if(type&0x80)
    {
        ui->comCbTpye->setCurrentIndex(0);//固定相位
    }
    else if(type&0x40)
    {
        ui->comCbTpye->setCurrentIndex(1);//待定相位
    }
    else if(type&0x20)
    {
        ui->comCbTpye->setCurrentIndex(2);//弹性相位
    }
    else if(type&0x10)
    {
        ui->comCbTpye->setCurrentIndex(3);//关键相位
    }
    else/* if(type==0)*/
    {
        ui->comCbTpye->setCurrentIndex(4);//空白
//        ui->comCbTpye->clearEditText();
    }

    if(option&0x01)
    {
        ui->comCbOption->setCurrentIndex(0);//启用相位
    }
    else if(option&0x02)
    {
        ui->comCbOption->setCurrentIndex(2);//行人过街相位
    }
    else if(option&0x04)
    {
        ui->comCbOption->setCurrentIndex(3);//同阶段相位出现
    }
    else if(option&0x08)
    {
        ui->comCbOption->setCurrentIndex(4);//行人跟随机动车
    }
    else if(option&0x10)
    {
        ui->comCbOption->setCurrentIndex(1);//跟随同阶段放行
    }
    else //if(option==0)*/
    {
        ui->comCbOption->setCurrentIndex(5);//空白
//        ui->comCbOption->clearEditText();
    }

}

//void WPhaseWidget::getComDlg()
//{

//}

void WPhaseWidget::dlgOverlapInit()
{
    QStringList listOverlap;
    for(int i=0;i<OVERLAPPHASENUM;i++)
    {
        listOverlap.append(tr("跟随相位%1").arg(i+1));
    }
    ui->overlapCbId->addItems(listOverlap);
//    QStringList;
//    ui->overlapCbAmend->addAction();
    ui->dlgFrameOverlap->setVisible(false);
    connect(ui->overlapCbId,SIGNAL(currentIndexChanged(int)),this,SLOT(on_overlapCbIdChange(int)));
    connect(ui->overlapCbType,SIGNAL(currentIndexChanged(int)),this,SLOT(on_overlapCbTypeChange(int)));
    connect(ui->overlapSbTailGreen,SIGNAL(currentIndexChanged(int)),this,SLOT(on_overlapSbTailGreenChange(int)));
    connect(ui->overlapSbTailRed,SIGNAL(currentIndexChanged(int)),this,SLOT(on_overlapSbTailRedChange(int)));
    connect(ui->overlapSbTailYellow,SIGNAL(currentIndexChanged(int)),this,SLOT(on_overlapSbTailYellowChange(int)));

    QPalette p = ui->dlgFrameOverlap->palette();
    p.setColor(QPalette::WindowText,Qt::yellow);
    ui->dlgFrameOverlap->setPalette(p);
}

void WPhaseWidget::showOverlapDlg(bool b)
{
    ui->dlgFrameOverlap->setVisible(b);
}

void WPhaseWidget::setOverlapDlg()
{
    int typeIndex = 0;
    quint8 type = m_pTbOverlap->bType;
    if(type==2)
    {
        typeIndex = 0;
    }
    else if(type==3)
    {
        typeIndex = 1;
    }
    else if(type==1)
    {
        typeIndex = 2;
    }
    else
    {
        typeIndex = 3;
    }
    ui->overlapCbType->setCurrentIndex(typeIndex);
    ui->overlapSbTailGreen->setValue(m_pTbOverlap->bTailGreen);
    ui->overlapSbTailYellow->setValue(m_pTbOverlap->bTailYellow);
    ui->overlapSbTailRed->setValue(m_pTbOverlap->bTailRed);

}

//void WPhaseWidget::getOverlapDlg()
//{

//}

void WPhaseWidget::clearPreClick()
{
//    qDebug()<<"m_ucClickChlId"<<m_ucClickChlId<<m_bChl<<"m_ucClickPhaseId"<<m_ucClickPhaseId<<"m_bLoadCont"<<m_bLoadCont<<"m_bComCont"<<m_bComCont<<"m_bPhase"<<m_bPhase;

    if(m_bChl)
    {
        if(m_ucClickChlId>0&&m_ucClickChlId<CHANNELNUM+1)
        {
            m_ListChl[m_ucClickChlId-1]->setFlagClick(false);
            m_bChl = false;
//            qDebug()<<"clear chl click"<<m_ucClickChlId;
        }
    }
    else if(m_bDir)
    {
//        qDebug()<<"m_ucClickDirIndex---------------"<<m_ucClickDirIndex;
        if(m_ucClickDirIndex<m_ListDir.count())
            m_ListDir[m_ucClickDirIndex]->setFlagClick(false);
        m_bDir = false;
    }
    if(m_ucClickPhaseId==0)
    {
        return;
    }
    if(m_bLoadCont)
    {
        if(m_ucClickLoadIndex<m_ListDir.count())
            m_ListDir[m_ucClickLoadIndex]->setFlagClick(m_ucClickPhaseId);
        m_bLoadCont = false;
    }
    else if(m_bComCont)
    {
        if(m_ucClickContComIndex<m_ListContentCom.count())
            m_ListContentCom[m_ucClickContComIndex]->setFlagClick(m_ucClickPhaseId);
        m_bComCont = false;
    }
    else if(m_bPhase)
    {
        if(m_ucClickPhaseId>0&&m_ucClickPhaseId<COMPHASENUM+1)
        {
            m_ListCom[m_ucClickPhaseId-1]->setFlagClick(false);
        }
        else if(m_ucClickPhaseId>MAXCOMPHASE&&m_ucClickPhaseId<MAXCOMPHASE+OVERLAPPHASENUM+1)
        {
            m_ListOverlap[m_ucClickPhaseId-MAXCOMPHASE-1]->setFlagClick(false);
        }
        m_bPhase = false;
    }
//    showPhaseDlg(m_ucClickPhaseId,false);
}

void WPhaseWidget::showPhaseDlg(quint8 id,bool b)
{
    ui->dlgFrameChl->setVisible(false);
    ui->dlgFrameDir->setVisible(false);
    if(id>0&&id<COMPHASENUM+1)
    {
        if(b)
        {
            int index = ui->comCbId->currentIndex();
            if(index==id-1)
            {
                on_comCbIdChange(index);
            }
            else
            {
                ui->comCbId->setCurrentIndex(id-1);
            }
        }
        showOverlapDlg(false);
        showComDlg(b);
    }
    else if(id>MAXCOMPHASE&&id<MAXCOMPHASE+OVERLAPPHASENUM+1)
    {
        if(b)
        {
            int index = ui->overlapCbId->currentIndex();
            if(index==id-1-MAXCOMPHASE)
            {
                on_overlapCbIdChange(index);
            }
            else
            {
                ui->overlapCbId->setCurrentIndex(id-1-MAXCOMPHASE);
            }
        }
        showComDlg(false);
        showOverlapDlg(b);
    }
}

void WPhaseWidget::dlgDirInit()
{
    QPalette p = ui->dlgFrameDir->palette();
    p.setColor(QPalette::WindowText,Qt::yellow);
    ui->dlgFrameDir->setPalette(p);

    QStringList list;
    QStringList listDir;
    QStringList listType;
    listDir<<tr("北")<<tr("东")<<tr("南")<<tr("西");
    listType<<tr("向左")<<tr("左直")<<tr("直行")<<tr("直右")<<tr("左直右")<<tr("向右")<<tr("一次人行")<<tr("二次人行");
    int dirCnt = listDir.count();
    int typeCnt = listType.count();
    for(int i=0;i<dirCnt;i++)
    {
        for(int j=0;j<typeCnt;j++)
        {
            ui->dirCbNo->addItem(listDir[i]+listType[j]);
        }
    }

    for(int i=0;i<COMPHASENUM;i++)
    {
        ui->dirCbCom->addItem(tr("普通相位%1").arg(i+1));
    }
    ui->dirCbCom->addItem(tr("无相位"));

    for(int i=0;i<OVERLAPPHASENUM;i++)
    {
        ui->dirCbOverlap->addItem(tr("跟随相位%1").arg(i+1));
    }
    ui->dirCbOverlap->addItem(tr("无相位"));

    ui->dlgFrameDir->setVisible(false);
    connect(ui->dirCbNo,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dirCbNoChange(int)));
    connect(ui->dirCbCom,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dirCbComChange(int)));
    connect(ui->dirCbOverlap,SIGNAL(currentIndexChanged(int)),this,SLOT(on_dirCbOverlapChange(int)));
    connect(ui->dirSbLoadNum,SIGNAL(valueChanged(int)),this,SLOT(on_dirSbLoadChange(int)));
    connect(ui->dirCbValid,SIGNAL(clicked()),this,SLOT(on_dirCbVoidChange()));
}

void WPhaseWidget::showDirDlg(bool b)
{
    if(b)
    {
        showChlDlg(false);
        showComDlg(false);
        showOverlapDlg(false);
    }
    ui->dlgFrameDir->setVisible(b);
}

void WPhaseWidget::setStraightLoadNo(quint8 loadNo)
{
    int dir = (loadNo>>5)-1;
    int index = dir*4+1;
    m_ListDir[index]->setLoadNo(loadNo);
    if((loadNo&0x01)==1)
    {
        m_ListDir[index-1]->setFlagValid(false);
//        m_ListDir[index-1]->setVisible(false);
    }
    else
    {
        m_ListDir[index-1]->setFlagValid(true);
//        m_ListDir[index-1]->setVisible(true);
    }
    if((loadNo&0x04)!=0)
    {
        m_ListDir[index+1]->setFlagValid(false);
//        m_ListDir[index+1]->setVisible(false);
    }
    else
    {
//        m_ListDir[index+1]->setFlagValid(true);
        m_ListDir[index+1]->setVisible(true);
    }
}

void WPhaseWidget::setDirDlg()
{
    quint8 id = m_ListDir[m_ucClickDirIndex]->getPhaseId();
    if(id>0&&id<COMPHASENUM+1)
    {
        ui->dirCbOverlap->setCurrentIndex(ui->dirCbOverlap->count()-1);
        ui->dirCbCom->setCurrentIndex(id-1);
    }
    else if(id>MAXCOMPHASE&&id<MAXCOMPHASE+1+OVERLAPPHASENUM)
    {
        ui->dirCbCom->setCurrentIndex(ui->dirCbCom->count()-1);
        ui->dirCbOverlap->setCurrentIndex(id-MAXCOMPHASE-1);
    }
    else
    {
        ui->dirCbCom->setCurrentIndex(ui->dirCbCom->count()-1);
        ui->dirCbOverlap->setCurrentIndex(ui->dirCbOverlap->count()-1);
    }
//qDebug()<<"dirSbLoadNum"<<m_ListDir[m_ucClickDirIndex]->getLoadNum();
    ui->dirSbLoadNum->setValue(m_ListDir[m_ucClickDirIndex]->getLoadNum());

    if(m_ListDir[m_ucClickDirIndex]->getFlagValid())
    {
        ui->dirCbValid->setCheckState(Qt::Checked);
    }
    else
    {
        ui->dirCbValid->setCheckState(Qt::Unchecked);
    }
}

//void WPhaseWidget::getDirDlg()
//{

//}

int WPhaseWidget::getListIndex(quint8 loadNo)
{
    int listIndex = -1;
    int dir = (loadNo>>5)-1;
    if((loadNo&0x18)!=0)//人行
    {
        if((loadNo&0x07)!=2)//0,1
        {
            listIndex = dir*4+3;
        }
        else//2次
        {
            listIndex = dir+DIRECTIONNUM;
        }
    }
    else
    {
        switch(loadNo&0x07)
        {
        case 1:
            listIndex = dir*4;
            break;
        case 2:
        case 3:
        case 6:
        case 7:
            listIndex = dir*4+1;
            break;
        case 4:
            listIndex = dir*4+2;
            break;
        default:
            break;
        }
    }
    return listIndex;
}

int WPhaseWidget::getListIndexByCbIndex(int index)
{
    if(index!=-1)
    {
        quint8 loadNo = 0;
        loadNo|=(index/8+1);
        loadNo<<=5;
        switch(index%8)
        {
        case 6:
            loadNo|=0x08;
            break;
        case 7:
            loadNo|=0x0a;
            break;
        case 0:
            loadNo|=0x01;
            break;
        case 1:
            loadNo|=0x03;
            break;
        case 2:
            loadNo|=0x02;
            break;
        case 3:
            loadNo|=0x06;
            break;
        case 4:
            loadNo|=0x07;
            break;
        case 5:
            loadNo|=0x04;
            break;
        default:
            break;
        }
        if(loadNo>0)
        {
            return getListIndex(loadNo);
        }
    }
    return -1;
}

int WPhaseWidget::getDirCbNoIndex(quint8 loadNo)
{
    int dir = (loadNo>>5)-1;
    bool bPed = (loadNo&0x18)==0?false:true;
    int index = -1;
    if(bPed)
    {
        switch(loadNo&0x07)
        {
        case 0:
        case 1:
            index = dir*8+6;//每个方向8个路标
            break;
        case 2:
            index = dir*8+7;
            break;
        default:
            break;
        }
        return index;
    }
    else
    {
        switch(loadNo&0x07)
        {
        case 1:
            index = dir*8+0;
            break;
        case 2:
            index = dir*8+2;
            break;
        case 3:
            index = dir*8+1;
            break;
        case 6:
            index = dir*8+3;
            break;
        case 7:
            index = dir*8+4;
            break;
        case 4:
            index = dir*8+5;
            break;
        default:
            break;
        }
        return index;
    }
}

void WPhaseWidget::setDataProcess(PDataProcess *p)
{
    m_pDataProcess = p;
    connect(p,SIGNAL(rcvPhase()),this,SLOT(on_rcvPhase()));
    connect(ui->btnApp,SIGNAL(clicked()),this,SLOT(on_btnApp()));
    connect(ui->btnRead,SIGNAL(clicked()),this,SLOT(on_btnRead()));
}

void WPhaseWidget::clearInterface()
{
    int phaseCnt = m_ListCom.count();
    int overlapCnt = m_ListOverlap.count();
    int comChlCnt = m_ListComChl.count();
    int chlCnt = m_ListChl.count();
    int OverlapChlCnt = m_ListOverlapChl.count();
    int dirCnt = m_ListDir.count();
    for(int i=0;i<dirCnt;i++)
    {
        m_ListDir[i]->clearPhaseIcon();
        m_ListDir[i]->setFlagValid(false);
    }
    for(int i=0;i<chlCnt;i++)
    {
        layoutAddChl(m_ListChl[i]);
    }
    for(int i=0;i<comChlCnt;i++)
    {
        m_ListComChl[i]->clearContent();
    }
    for(int i=0;i<OverlapChlCnt;i++)
    {
        m_ListOverlapChl[i]->clearContent();
    }
    for(int i=0;i<phaseCnt;i++)
    {
        m_ListCom[i]->setFlagUsed(false);//
    }
    for(int i=0;i<overlapCnt;i++)
    {
        m_ListOverlap[i]->setFlagUsed(false);//
        m_ListOverlap[i]->on_setOverlapFlagValid(false);
        m_ListContentCom[i*2]->clearContent();
        m_ListContentCom[i*2+1]->clearContent();
    }

}

void WPhaseWidget::layoutAddChl(ChlIcon *icon)
{
    icon->setFlagUsed(false);
    icon->setChlPhaseId(0);
    int id = icon->getId();
    ui->layoutChl->addWidget(icon,(id-1)/(CHANNELNUM/2),(id-1)%(CHANNELNUM/2));
}

void WPhaseWidget::getInterfaceData()
{
    getPhaseMapTabel();
    getOverlapTable();
    getChannelTableData();
}

void WPhaseWidget::getChannelTableData()
{
    int cnt = m_ListChl.count();

    for(int i=0;i<cnt;i++)
    {
        if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            m_pTbChl = m_pDataProcess->m_pTscInfo->tbChannel+i;
            m_pTbChl->bNo = i+1;
            quint8 phase = m_ListChl[i]->getPhaseId();
            if(phase>MAXCOMPHASE)//通道类型 只分为 跟随相位 和 机动车
            {
                phase -= MAXCOMPHASE;
                m_pTbChl->bControlType = 4;
                editOverlapPhaseDirect(phase);
            }
            else
            {
                if(m_pTbChl->bControlType==4)//普通相位 其类型如果是 跟随相位 更改为 机动车
                {
                    m_pTbChl->bControlType = 2;
                }
            }
//            if(m_pTbChl->bControlType == 0)//0 无类型，默认为 机动车
//            {
//                m_pTbChl->bControlType = 2;
//            }
            m_pTbChl->bControlSource = phase;
        }
    }
}

void WPhaseWidget::getPhaseMapTabel()
{
    if(m_pDataProcess->m_pTscInfo!=NULL)
    {
        int cnt = m_ListDir.count();
        int tbSize = sizeof(PhaseMap_Table);
        int index = -1;
        PhaseMap_Table *mapBase = m_pDataProcess->m_pTscInfo->tbPhaseMap;
        memset((char*)mapBase,0,tbSize*MAX_PHASEMAP_NUM);
        for(int i=0;i<cnt;i++)
        {
            LoadIcon* icon = m_ListDir[i];
            if(icon->getFlagValid())
            {
                index++;
                if(index<MAX_PHASEMAP_NUM)
                {
    //                m_pTbDirMap = m_pDataProcess->m_pTscInfo->tbPhaseMap+index;
                    quint8 id = icon->getContentId();
                    quint8 phase = icon->getPhaseId();
                    quint8 num = icon->getLoadNum();
                    (mapBase+index)->bPhaseIconId = id;
                    (mapBase+index)->bCommonPhaseNo = phase<MAXCOMPHASE?phase:0;
                    (mapBase+index)->bOverlapPhaseNo = phase>MAXCOMPHASE?(phase-MAXCOMPHASE):0;
                    (mapBase+index)->bLaneNum = num;
                }
                else
                {
                    qDebug()<<"phase map cnt error";//方向超过16个
                }
            }
        }
    }
}

void WPhaseWidget::getOverlapTable()
{
    if(m_pDataProcess->m_pTscInfo!=NULL)
    {
//        memset(m_pDataProcess->m_pTscInfo->tbOverlap,0,sizeof(Overlap_Table)*OVERLAPPHASENUM);
        for(int i=0;i<OVERLAPPHASENUM;i++)
        {
            m_pTbOverlap = m_pDataProcess->m_pTscInfo->tbOverlap+i;
            QList<quint8> listInclude = m_ListContentCom[i*2]->getListData();
            QList<quint8> listAmend = m_ListContentCom[i*2+1]->getListData();
            int cntInclude = listInclude.count();
            int cntAmend = listAmend.count();
            m_pTbOverlap->bIncludedPhaseLen = cntInclude;
            m_pTbOverlap->bModifierPhaseLen = cntAmend;
            for(int j=0;j<INCLUDEPHASELEN;j++)
            {
                if(j<cntInclude)
                {
                    m_pTbOverlap->bIncludedPhase[j] = listInclude[j];
                }
                else
                {
                    m_pTbOverlap->bIncludedPhase[j] = 0;
                }
            }
            for(int k=0;k<MODIFIERPHASELEN;k++)
            {
                if(k<cntAmend)
                {
                    m_pTbOverlap->bModifierPhase[k] = listAmend[k];
                }
                else
                {
                    m_pTbOverlap->bModifierPhase[k] = 0;
                }
            }
            m_pTbOverlap->bNo = i+1;
            qDebug()<<"getoverlaptable bNo"<<i+1;
        }
    }
}

/*
 如果跟随相位有通道输出，没有对应方向；
 查找第一包含相位的对应方向，填写此方向的跟随相位
*/
void WPhaseWidget::editOverlapPhaseDirect(quint8 overPhaseId)
{
    if(m_pDataProcess!=NULL&&overPhaseId>0&&overPhaseId<(MAX_OVERLAP_NUM+1))
    {
        PhaseMap_Table *pDir = m_pDataProcess->m_pTscInfo->tbPhaseMap;
        if(m_pDataProcess->m_pTscInfo!=NULL)
        {
            for(int i=0;i<MAX_PHASEMAP_NUM;i++)
            {
                if((pDir+i)->bOverlapPhaseNo==overPhaseId)
                {
                    return;
                }
            }
        }
        //没有对应方向
        Overlap_Table *pOver = m_pDataProcess->m_pTscInfo->tbOverlap+overPhaseId-1;
        quint8 comPhase = 0;
        if(pOver->bIncludedPhaseLen>0)
        {
            for(int i=0;i<INCLUDEPHASELEN;i++)
            {
                if(pOver->bIncludedPhase[i]!=0)
                {
                    comPhase = pOver->bIncludedPhase[i];
                    break;
                }
            }
        }
        if(comPhase!=0)
        {
            for(int i=0;i<MAX_PHASEMAP_NUM;i++)
            {
                if((pDir+i)->bCommonPhaseNo ==comPhase)
                {
                    //(pDir+i)->bCommonPhaseNo = overPhaseId;
                    (pDir+i)->bOverlapPhaseNo = overPhaseId;
                    return;
                }
            }
        }
    }
}

void WPhaseWidget::timerEvent(QTimerEvent *e)
{
    this->killTimer(e->timerId());
    if(m_bTimer)
    {
        m_bTimer = false;
        if(!ui->btnRead->isEnabled())
        {
            ui->btnRead->setEnabled(true);
        }
    }
}

//void WPhaseWidget::setDirIconValid(quint8 index, bool b)
//{
//    m_ListDir[index]->setFlagValid(b);
//    if(index<DIRECTIONNUM&&index%4==3)
//    {
//        m_ListDir[index]->setPedSmall(false);
//    }
//    if(index>(DIRECTIONNUM-1))
//    {
//        int dir = index-DIRECTIONNUM;
//        m_ListDir[dir*4+3]->setPedSmall(b);
//        qDebug()<<"turn small"<<dir*4+3<<b;
//    }
//}

void WPhaseWidget::on_loadClearPhase(quint8 id)
{
    if(id>0&&id<COMPHASENUM+1)
    {
        m_ListCom[id-1]->setFlagUsed(false);
    }
    else if(id>MAXCOMPHASE&&id<MAXCOMPHASE+OVERLAPPHASENUM+1)
    {
        m_ListOverlap[id-1-MAXCOMPHASE]->setFlagUsed(false);
    }
}

void WPhaseWidget::on_chlBtnMore()
{
    if(ui->chlFrameMore->isHidden())
    {
        ui->chlFrameMore->show();
        ui->chlBtnShow->setText(tr("<<隐藏"));
    }
    else
    {
        ui->chlFrameMore->hide();
        ui->chlBtnShow->setText(tr("更多>>"));
    }
}

void WPhaseWidget::on_mouseClickChl(quint8 chlId,bool bClick, quint8 phaseId)
{/*qDebug()<<"release m_bDrag click"<<chlId<<bClick;*/
    if(bClick&&chlId>0&&chlId<CHANNELNUM+1)
    {
        m_bIconClick = true;

        int index = ui->chlCbNo->currentIndex();
        if(index==chlId-1)
        {
            on_chlCbNoChange(index);
        }
        else
        {
            ui->chlCbNo->setCurrentIndex(chlId-1);
        }
        QString strPhase;
        if(phaseId>0&&phaseId<COMPHASENUM+1)
        {
            strPhase = tr("相位%1").arg(phaseId);
        }
        else if(phaseId>MAXCOMPHASE&&phaseId<MAXCOMPHASE+OVERLAPPHASENUM+1)
        {
            strPhase = tr("跟随相位%1").arg(phaseId-MAXCOMPHASE);
        }
        else if(phaseId==0)
        {
            strPhase = tr("无相位");
        }
        ui->chlLePhase->setText(strPhase);

//        for(int i=0;i<CHANNELNUM;i++)
//        {
//            ChlIcon *icon = m_ListChl[i];
//            //qDebug()<<"icon id"<<m_ListChl.count()<<i;
//            if(icon->getId()!=chlId)
//            {
//                icon->setFlagClick(false);
//            }
//        }
    }
    showChlDlg(bClick);
    m_bChl = bClick;
//    else
//    {
//        hideChlDlg();
//    }

}
/*
 index = chlId-1;
*/
void WPhaseWidget::on_chlCbNoChange(int index)
{
    if(index!=-1)
    {
        clearPreClick();
        m_bDlgInit = false;

        m_ucClickChlId = index+1;
        if(m_bIconClick)
        {
            m_bIconClick = false;
        }
        else
        {

            m_ListChl[index]->setFlagClick(true);
            m_bChl = true;
        }
        m_pTbChl = m_pDataProcess->m_pTscInfo->tbChannel+index;
        setChlDlg();
        m_bDlgInit = true;
    }
}

void WPhaseWidget::on_chlCbTypeChange(int typeIndex)
{
    if(m_bDlgInit&&typeIndex!=-1&&m_pTbChl!=NULL)
    {
        switch(typeIndex)
        {
        case 0:
            m_pTbChl->bControlType = 2;
            break;
        case 1:
            m_pTbChl->bControlType = 3;
            break;
        case 2:
            m_pTbChl->bControlType = 4;
            break;
        case 3:
            m_pTbChl->bControlType = 1;
            break;
        default:
            break;
        }

    }
}

void WPhaseWidget::on_chlCbLightChange(int index)
{
    if(m_bDlgInit&&index!=-1&&m_pTbChl!=NULL)
    {
        quint8 ctrlMode = m_pTbChl->bControlMode;
        if(index==0)
        {
            m_pTbChl->bControlMode = ctrlMode&0xf7;
        }
        else if(index==1)
        {
            m_pTbChl->bControlMode = ctrlMode|0x08;
        }
    }

}

void WPhaseWidget::on_chlCbModeChange(int index)
{

    if(m_bDlgInit&&index!=-1&&m_pTbChl!=NULL)
    {
        quint8 ctrlMode = m_pTbChl->bControlMode;
        ctrlMode&=0xf9;
        switch(index)
        {
        case 0:
            break;
        case 1:
            ctrlMode |= 0x02;
            break;
        case 2:
            ctrlMode |= 0x04;
            break;
        default:
            break;
        }
        m_pTbChl->bControlMode = ctrlMode;
    }
}

void WPhaseWidget::on_mouseClickPhase(quint8 phaseId, bool bClick)
{
    m_bIconClick = true;
    showPhaseDlg(phaseId,bClick);
    if(bClick)
    {
//        clearPreClick();
//        m_ucClickPhaseId = phaseId;
    }

    m_bPhase = bClick;
//    m_bLoadCont = false;
//    m_bComCont = false;
}

void WPhaseWidget::on_mouseClickComContentPhase(quint8 contId, bool bClick, quint8 phaseId)
{//qDebug()<<"click com content"<<contId<<bClick<<phaseId;

    m_bIconClick = true;
    showPhaseDlg(phaseId,bClick);
    if(bClick)
    {
//        clearPreClick();
//        m_ucClickPhaseId = phaseId;
        for(int i=0;i<OVERLAPPHASENUM*2;i++)
        {
            if(m_ListContentCom[i]->getContentId()==contId)
            {
                m_ucClickContComIndex = i;
                break;
            }
        }
    }

//    m_bPhase = false;
//    m_bLoadCont = false;
    m_bComCont = bClick;
}

void WPhaseWidget::on_mouseClickLoadContentPhase(quint8 contId, bool bClick, quint8 phaseId)
{//qDebug()<<"click load content"<<contId<<bClick<<phaseId;

    m_bIconClick = true;
    showPhaseDlg(phaseId,bClick);
    if(bClick)
    {
//        clearPreClick();
//        m_ucClickPhaseId = phaseId;
        int cnt = m_ListDir.count();
        for(int i=0;i<cnt;i++)
        {
            if(m_ListDir[i]->getContentId()==contId)
            {
                m_ucClickLoadIndex = i;
                break;
            }
        }
    }

//    m_bPhase = false;
    m_bLoadCont = bClick;
//    m_bComCont = false;
}

void WPhaseWidget::on_comBtnMore()
{
    m_bComBtnMore = !m_bComBtnMore;
    ui->dlgFrameCom2->setVisible(m_bComBtnMore);
    if(m_bComBtnMore)
    {
        ui->comBtnMore->setText(tr("<<隐藏"));
    }
    else
    {
        ui->comBtnMore->setText(tr("更多>>"));
    }
}

void WPhaseWidget::on_comCbIdChange(int index)
{
    if(index==-1)
        return;
    clearPreClick();
    m_ucClickPhaseId = index+1;
    m_bDlgInit = false;
    m_pTbCom = m_pDataProcess->m_pTscInfo->tbPhase+index;
    setComDlg();
    m_bDlgInit = true;
    if(m_bIconClick)
    {
        m_bIconClick = false;
    }
    else
    {
        m_ListCom[index]->setFlagClick(true);
        m_bPhase = true;
    }
}

void WPhaseWidget::on_comSbPedGreenChange(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bPedestrianGreenTime = time;

    }
}

void WPhaseWidget::on_comSbPedCleanChange(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bPedestrianClearTime = time;

    }
}

void WPhaseWidget::on_comSbMinGreenChange(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bMinGreenTime = time;

    }
}

void WPhaseWidget::on_comSbUnitDelayChange(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bDelayGreenUnit = time;

    }
}

void WPhaseWidget::on_comSbMaxGreen1Change(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bMaxGreenTime1 = time;

    }
}

void WPhaseWidget::on_comSbFlashGreenChange(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bGreenFlashTime = time;

    }
}

void WPhaseWidget::on_comSbMaxGreen2Change(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bMaxGreenTime2 = time;

    }
}

void WPhaseWidget::on_comSbFixGreenChange(int time)
{
    if(m_bDlgInit)
    {
        m_pTbCom->bFixedGreenTime = time;

    }
}

void WPhaseWidget::on_comCbTypeChange(int index)
{
    if(m_bDlgInit&&index!=-1)
    {
        quint8 type = 0;
        switch(index)
        {
        case 0:
            type = 0x80;
            break;
        case 1:
            type = 0x40;
            break;
        case 2:
            type = 0x20;
            break;
        case 3:
            type = 0x10;
            break;

        default:
            break;
        }
        m_pTbCom->bPhaseType = type;

    }
}

void WPhaseWidget::on_comCbOptionChange(int index)
{
    if(m_bDlgInit&&index!=-1)
    {

        quint8 option = 0;
        switch(index)
        {
        case 0:
            option = 0x01;
            break;
        case 1:
            option = 0x10;
            break;
        case 2:
            option = 0x02;
            break;
        case 3:
            option = 0x04;
            break;
        case 4:
            option = 0x08;
            break;
        default:
            break;
        }
        m_pTbCom->bPhaseOption = option;
    }
}

void WPhaseWidget::on_overlapCbIdChange(int index)
{
    if(index==-1)
        return;
    clearPreClick();
    m_ucClickPhaseId = index+1+MAXCOMPHASE;
    m_bDlgInit = false;
    m_pTbOverlap = m_pDataProcess->m_pTscInfo->tbOverlap+index;
    setOverlapDlg();
    m_bDlgInit = true;
    if(m_bIconClick)
    {
        m_bIconClick = false;
    }
    else
    {
        m_ListOverlap[index]->setFlagClick(true);
        m_bPhase = true;
    }
}

void WPhaseWidget::on_overlapCbTypeChange(int index)
{
    if(m_bDlgInit&&index!=-1)
    {
        quint8 type = 0;
        switch(index)
        {
        case 0:
            type = 2;
            break;
        case 1:
            type = 3;
            break;
        case 2:
            type = 1;
            break;
        default:
            break;
        }
        m_pTbOverlap->bType = type;
    }

}


void WPhaseWidget::on_overlapSbTailGreenChange(int time)
{
    if(m_bDlgInit)
    {
        m_pTbOverlap->bTailGreen = time;
    }

}


void WPhaseWidget::on_overlapSbTailYellowChange(int time)
{

    if(m_bDlgInit)
    {
        m_pTbOverlap->bTailYellow = time;
    }
}


void WPhaseWidget::on_overlapSbTailRedChange(int time)
{

    if(m_bDlgInit)
    {
        m_pTbOverlap->bTailRed = time;
    }
}
void WPhaseWidget::on_dirClearContent(quint8 id, bool b)
{
    if(id>0&&id<COMPHASENUM+1)
    {
        m_ListCom[id-1]->setFlagUsed(b);
    }
    else if(id>MAXCOMPHASE&&id<MAXCOMPHASE+OVERLAPPHASENUM+1)
    {
        m_ListOverlap[id-MAXCOMPHASE-1]->setFlagUsed(b);
    }
}

void WPhaseWidget::on_mouseDoubleClick(quint8 loadNo)
{//qDebug()<<"mouse double click"<<tr("0x%1").arg(loadNo,2,16);
    int dir = (loadNo>>5)-1;//0,1,2,3
    if((loadNo&0x18)!=0)//人行
    {/*
        qDebug()<<"mouse double click"<<tr("0x%1").arg(loadNo,2,16)<<"dir"<<dir;*/
        switch(loadNo&0x07)
        {
        case 0://一次过街
            m_ListDir[dir*4+3]->setLoadNo(loadNo+1);
            m_ListDir[DIRECTIONNUM+dir]->setFlagValid();
            break;
        case 1://二次过街 的 一次
            m_ListDir[dir*4+3]->setLoadNo(loadNo-1);
            m_ListDir[DIRECTIONNUM+dir]->setFlagValid(false);
            break;
        case 2://二次过街的 二次
            m_ListDir[dir*4+3]->setLoadNo(loadNo-2);
            m_ListDir[DIRECTIONNUM+dir]->setFlagValid(false);
        default:
            break;
        }
    }
    else
    {
        //int index = dir*4+1;
        switch(loadNo&0x07)
        {
        case 0x02:
            setStraightLoadNo(loadNo|0x03);
            break;
        case 0x03:
            setStraightLoadNo(loadNo&0xfa|0x07);
            break;
        case 0x06:
            setStraightLoadNo(loadNo&0xfa);
            break;
        case 0x07:
            setStraightLoadNo((loadNo&0xfa)|0x06);
            break;
        default:
            break;
        }
    }
}

void WPhaseWidget::on_mouseClickDir(quint8 loadNo, bool bClick)
{
    if(bClick)
    {
        m_bIconClick = true;

//        int listIndex = getListIndex(loadNo);
//        if(listIndex!=-1)
//        {
//            m_ucClickDirIndex = listIndex;
//        }
//        else
//        {
//            qDebug()<<"m_ucClickDirIndex"<<m_ucClickDirIndex;
//            return;
//        }
        int cbIndex = getDirCbNoIndex(loadNo);
//        qDebug()<<"cbIndex by loadNo"<<cbIndex<<tr("loadNo0x%1").arg(loadNo,2,16);
        if(cbIndex!=-1)
        {
            int curIndex = ui->dirCbNo->currentIndex();

            if(curIndex!=cbIndex)
            {
                ui->dirCbNo->setCurrentIndex(cbIndex);
            }
            else
            {
                on_dirCbNoChange(cbIndex);
            }
        }

    }
    m_bDir = bClick;

    showDirDlg(bClick);
}

void WPhaseWidget::on_dirCbNoChange(int index)
{
    clearPreClick();
//    int listIndex;
    int listIndex = getListIndexByCbIndex(index);
    if(listIndex>-1&&listIndex<m_ListDir.count())
    {
        m_ucClickDirIndex = listIndex;
        m_bDir = true;
    }
    if(m_bIconClick)
    {
        m_bIconClick = false;
    }
    else
    {
        m_ListDir[listIndex]->setFlagClick(true);
    }
    m_bDlgInit = false;
    setDirDlg();
    m_bDlgInit = true;

}

void WPhaseWidget::on_dirCbComChange(int index)
{
    if(m_bDlgInit&&index!=-1)
    {
        qDebug()<<"on_dirCbComChange";
        if(index<COMPHASENUM)
        {
            m_ListDir[m_ucClickDirIndex]->addPhaseIcon(index+1);
        }
        else
        {
            m_ListDir[m_ucClickDirIndex]->clearPhaseIcon();
        }
    }
}

void WPhaseWidget::on_dirCbOverlapChange(int index)
{
    if(m_bDlgInit&&index!=-1)
    {qDebug()<<"on_dirCbOverlapChange";
        if(index<OVERLAPPHASENUM)
        {
            m_ListDir[m_ucClickDirIndex]->addPhaseIcon(index+1+MAXCOMPHASE);
        }
        else
        {
            m_ListDir[m_ucClickDirIndex]->clearPhaseIcon();
        }
    }
}

void WPhaseWidget::on_dirSbLoadChange(int value)
{
    if(m_bDlgInit)
    {qDebug()<<"on_dirSbLoadChange";
        m_ListDir[m_ucClickDirIndex]->setLoadNum(value);
    }
}

void WPhaseWidget::on_dirCbVoidChange()
{
    if(m_bDlgInit)
    {
        m_ListDir[m_ucClickDirIndex]->setFlagValid(ui->dirCbValid->isChecked());
    }
}
void WPhaseWidget::on_rcvPhase()
{
    if(m_bTimer)
    {
        m_bTimer = false;
        ui->btnRead->setEnabled(true);
    }
    clearInterface();
    //通道对应相位,这里是将相位关联方向的所有都取得，。就算是通道已经不与相位关联了。他也取得就存在BUG
    int chlCnt = m_pDataProcess->m_ListLoadMap.count();
    for(int i=0;i<chlCnt;i++)
    {
        quint8 id = m_pDataProcess->m_ListLoadMap[i];
        if(id>0&&id<COMPHASENUM+1)
        {
            m_ListComChl[id-1]->addChl(m_ListChl[i]);
            qDebug()<<tr("普通相位%1:对应通道%2").arg(id-1).arg(i);
        }
        else if(id>MAXCOMPHASE&&id<MAXCOMPHASE+OVERLAPPHASENUM+1)
        {
            m_ListOverlapChl[id-1-MAXCOMPHASE]->addChl(m_ListChl[i]);
        }
    }

    //跟随相位容器
    for(int i=0;i<OVERLAPPHASENUM;i++)
    {
        m_pTbOverlap = m_pDataProcess->m_pTscInfo->tbOverlap+i;
        int cntInclude = m_pTbOverlap->bIncludedPhaseLen;
        int cntAmend = m_pTbOverlap->bModifierPhaseLen;
        for(int j=0;j<cntInclude;j++)
        {
            m_ListContentCom[i*2]->addComPhase(m_pTbOverlap->bIncludedPhase[j]);
        }
        for(int k=0;k<cntAmend;k++)
        {
            m_ListContentCom[i*2+1]->addComPhase(m_pTbOverlap->bModifierPhase[k]);
        }
    }

    //图标
    int pixCnt = m_pDataProcess->m_ListLoadNo.count();
    for(int i=0;i<pixCnt;i++)
    {
        quint8 loadNo = m_pDataProcess->m_ListLoadNo[i];
        int dirIndex = getListIndex(loadNo);
        if(dirIndex>-1&&dirIndex<20)
        {
            m_ListDir[dirIndex]->setLoadNo(loadNo);
        }
    }
    int validCnt = m_pDataProcess->m_ListValid.count();
    for(int i=0;i<validCnt;i++)
    {
        m_ListDir[i]->setFlagValid(m_pDataProcess->m_ListValid[i]);
        m_ListDir[i]->setLoadNum(m_pDataProcess->m_ListLoadNum[i]);
    }

    int dirCnt = m_pDataProcess->m_ListPhaseMap.count();
    for(int i=0;i<dirCnt;i++)
    {
        quint8 id = m_pDataProcess->m_ListPhaseMap[i];
        m_ListDir[i]->addPhaseIcon(id);//i方向index
    }
    qDebug()<<"phase widget complette";
}

void WPhaseWidget::on_btnApp()
{
    if(m_pDataProcess!=NULL)
    {
        getInterfaceData();
        if(m_pDataProcess->sendPhaseTableToLib())
        {
            ui->btnRead->setEnabled(false);
            this->startTimer(8000);
            m_bTimer = true;
        }
    }
}

void WPhaseWidget::on_btnRead()
{
    if(m_pDataProcess!=NULL)
    {
        m_pDataProcess->requireTscTable(TSC_TABLE_PHASE);
    }
}
