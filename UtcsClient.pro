LIBS        += -L"e:/ACE_wrappers/lib" -lws2_32
LIBS        += -L"e:/ACE_wrappers/lib" -lws2_32
LIBS += -L e:/ACE_wrappers/ace -lACE -lws2_32
LIBS += -L e:/ACE_wrappers/lib -lACE -lws2_32
LIBS += -L e:/ACE_wrappers/TAO/tao -lACE -lws2_32
LIBS += -L e:/ACE_wrappers/TAO -lACE -lws2_32

LIBS        += -lACE -lTAO -lTAO_CosNaming -lTAO_CosNaming_Serv -lTAO_CosNaming_Skel
LIBS        += -lTAO_PortableServer
LIBS        += -lTAO_AnyTypeCode
LIBS        += -lTAO_Valuetype
LIBS        += -lTAO_PI
LIBS        += -lTAO_Messaging
LIBS        += -lTAO_TypeCodeFactory
LIBS        += -lTAO_RTEvent

INCLUDEPATH += e:/ACE_wrappers
INCLUDEPATH += e:/ACE_wrappers/TAO
INCLUDEPATH += e:/ACE_wrappers/TAO/tao
INCLUDEPATH += e:/ACE_wrappers/TAO/orbsvcs/orbsvcs/Naming
INCLUDEPATH += e:/ACE_wrappers/TAO/orbsvcs/orbsvcs
INCLUDEPATH += e:/ACE_wrappers/TAO/orbsvcs/

SOURCES += \
    main.cpp \
    WMainwindow.cpp \
    WWindowstack.cpp \
    WTree.cpp \
    PDataProcess.cpp \
    WUserLogIn.cpp \
    CClientService.cpp \
    WUserViewDlg.cpp \
    WUserEditDlg.cpp \
    wuserrightdlg.cpp \
    wnodeparadlg.cpp \
    wtimebasedlg.cpp \
    CommClass.cpp \
    wtimeset.cpp \
    wstage.cpp \
    wstatus.cpp \
    detwidget.cpp \
    wdetwidget.cpp \
    weventlogwidget.cpp \
    clusterdlg.cpp \
    ctnode.cpp \
    wvipdlg.cpp \
    Vip.cpp \
    wphasewidget.cpp \
    phase.cpp \
    wdirectionform.cpp \
    wstagewidget.cpp \
    wsystempara.cpp \
    wconflct.cpp \
    WTraffic.cpp \
    broadcastform.cpp \
    wscheduledlg.cpp

FORMS += \
    wvipdlg.ui \
    wtraffic.ui \
    wsystempara.ui \
    wstatus.ui \
    wstagewidget.ui \
    wstage.ui \
    wphasewidget.ui \
    windowstack.ui \
    wdirectionform.ui \
    wconflct.ui \
    wclusterdlg.ui \
    usrlogin.ui \
    tree.ui \
    status.ui \
    mainwindow.ui \
    form.ui \
    detectormonitor.ui \
    detector.ui \
    clusterdlg.ui \
    broadcastform.ui

HEADERS += \
    WMainwindow.h \
    WWindowstack.h \
    WTree.h \
    DTable.h \
    DCommon.h \
    PDataProcess.h \
    WUserLogIn.h \
    CClientService.h \
    WUserViewDlg.h \
    WUserEditDlg.h \
    wuserrightdlg.h \
    wnodeparadlg.h \
    wtimebasedlg.h \
    CommClass.h \
    wtimeset.h \
    wstage.h \
    wstatus.h \
    detwidget.h \
    wdetwidget.h \
    weventlogwidget.h \
    clusterdlg.h \
    ctnode.h \
    wvipdlg.h \
    Vip.h \
    wphasewidget.h \
    phase.h \
    wdirectionform.h \
    wstagewidget.h \
    wsystempara.h \
    wconflct.h \
    WTraffic.h \
    broadcastform.h \
    wscheduledlg.h

RESOURCES += \
    interface.qrc
