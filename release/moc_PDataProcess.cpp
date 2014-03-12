/****************************************************************************
** Meta object code from reading C++ file 'PDataProcess.h'
**
** Created: Fri Sep 21 18:10:27 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PDataProcess.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PDataProcess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PDataProcess[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      57,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      48,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x05,
      54,   13,   13,   13, 0x25,
      80,   13,   13,   13, 0x05,
     110,  104,   13,   13, 0x05,
     139,  131,   13,   13, 0x05,
     168,  131,   13,   13, 0x05,
     198,  196,   13,   13, 0x05,
     238,  228,   13,   13, 0x05,
     274,  228,   13,   13, 0x05,
     310,  228,   13,   13, 0x05,
     349,  228,   13,   13, 0x05,
     395,  386,   13,   13, 0x05,
     426,  196,   13,   13, 0x05,
     455,   13,   13,   13, 0x05,
     482,   13,   13,   13, 0x05,
     506,   13,   13,   13, 0x05,
     529,   13,   13,   13, 0x05,
     546,   13,   13,   13, 0x05,
     567,  104,   13,   13, 0x05,
     599,  104,   13,   13, 0x05,
     626,   13,   13,   13, 0x05,
     650,   13,   13,   13, 0x05,
     670,   13,   13,   13, 0x05,
     684,   13,   13,   13, 0x05,
     695,   13,   13,   13, 0x05,
     704,   13,   13,   13, 0x05,
     729,  718,   13,   13, 0x05,
     771,   13,   13,   13, 0x05,
     786,   13,   13,   13, 0x05,
     806,  228,   13,   13, 0x05,
     844,  839,   13,   13, 0x05,
     864,   13,   13,   13, 0x05,
     884,   13,   13,   13, 0x05,
     899,  228,   13,   13, 0x05,
     936,   13,   13,   13, 0x05,
     954,   13,   13,   13, 0x05,
     975,  968,   13,   13, 0x05,
     998,   13,   13,   13, 0x05,
    1013,   13,   13,   13, 0x05,
    1033,   13,   13,   13, 0x05,
    1081, 1053,   13,   13, 0x05,
    1124, 1120,   13,   13, 0x05,
    1144,   13,   13,   13, 0x05,
    1168, 1163,   13,   13, 0x05,
    1198, 1196,   13,   13, 0x05,
    1230, 1217,   13,   13, 0x05,
    1285, 1273,   13,   13, 0x05,
    1328,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
    1346, 1120,   13,   13, 0x0a,
    1370,   13,   13,   13, 0x0a,
    1387,   13,   13,   13, 0x0a,
    1412,   13,   13,   13, 0x0a,
    1450,  104,   13,   13, 0x0a,
    1480,  104,   13,   13, 0x0a,
    1509,   13,   13,   13, 0x0a,
    1538,   13,   13,   13, 0x0a,
    1573,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PDataProcess[] = {
    "PDataProcess\0\0,index\0"
    "statusBarMessage(QString,quint8)\0"
    "statusBarMessage(QString)\0"
    "setNodeParaCbTscId(int)\0index\0"
    "nodeChangeIndex(int)\0rcv,len\0"
    "receivedUserLogin(char*,int)\0"
    "receivedUserView(char*,int)\0,\0"
    "receivedNodeCommand(int,bool)\0para1,len\0"
    "receivedTimeBaseResponse(char*,int)\0"
    "receivedScheduleResponse(char*,int)\0"
    "receivedTimePatternResponse(char*,int)\0"
    "receivedStageTimeResponse(char*,int)\0"
    "byteArr,\0sendToService(QByteArray,bool)\0"
    "recvMessage(QByteArray,bool)\0"
    "clickTreeView(QModelIndex)\0"
    "resetNodeNameModel(int)\0readCmdArr(QByteArray)\0"
    "rcvModuleTable()\0changeSpecialModel()\0"
    "clickTimebaseIndex(QModelIndex)\0"
    "clickSchIndex(QModelIndex)\0"
    "updateTimePatternName()\0rcvStageTimeTable()\0"
    "rcvConflict()\0rcvPhase()\0rcvDet()\0"
    "rcvDetAlarm()\0para1,len,\0"
    "rcvAutoReport(unsigned char*,int,quint32)\0"
    "changeNodeId()\0rcvManualCtrl(bool)\0"
    "rcvTscStatus(unsigned char*,int)\0time\0"
    "rcvTscTime(quint32)\0cbFlashStatus(bool)\0"
    "eventlogShow()\0rcvDetAutoReport(unsigned char*,int)\0"
    "cbDetStatus(bool)\0getCtCircle()\0nodeId\0"
    "getCtNodeStage(quint8)\0rcvCtPattern()\0"
    "ctNameModelChange()\0vipNodeListChange()\0"
    "id,bManual,stageId,bVipShow\0"
    "vipNodeState(quint32,bool,quint8,bool)\0"
    "str\0clickVipId(QString)\0vipIdModelChange()\0"
    "id,b\0vipItemChange(quint32,bool)\0b\0"
    "clusterClick(bool)\0max,min,maxY\0"
    "trafficMaxMinTime(quint32,quint32,quint32)\0"
    "str,mapData\0trafficData(QString,QMap<quint32,quint32>)\0"
    "completeTraffic()\0dealMessage(QByteArray)\0"
    "on_connect(bool)\0on_rcvTscIpInfo(QString)\0"
    "on_treeviewDataChange(QStandardItem*)\0"
    "on_treeViewClick(QModelIndex)\0"
    "on_setFlagShowInterfase(int)\0"
    "on_tabWidgetIndexChange(int)\0"
    "on_treeViewRightClick(QModelIndex)\0"
    "on_schEventChange()\0"
};

void PDataProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PDataProcess *_t = static_cast<PDataProcess *>(_o);
        switch (_id) {
        case 0: _t->statusBarMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 1: _t->statusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setNodeParaCbTscId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->nodeChangeIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->receivedUserLogin((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->receivedUserView((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->receivedNodeCommand((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->receivedTimeBaseResponse((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->receivedScheduleResponse((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->receivedTimePatternResponse((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->receivedStageTimeResponse((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->sendToService((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->recvMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->clickTreeView((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 14: _t->resetNodeNameModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->readCmdArr((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 16: _t->rcvModuleTable(); break;
        case 17: _t->changeSpecialModel(); break;
        case 18: _t->clickTimebaseIndex((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 19: _t->clickSchIndex((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 20: _t->updateTimePatternName(); break;
        case 21: _t->rcvStageTimeTable(); break;
        case 22: _t->rcvConflict(); break;
        case 23: _t->rcvPhase(); break;
        case 24: _t->rcvDet(); break;
        case 25: _t->rcvDetAlarm(); break;
        case 26: _t->rcvAutoReport((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        case 27: _t->changeNodeId(); break;
        case 28: _t->rcvManualCtrl((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->rcvTscStatus((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 30: _t->rcvTscTime((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 31: _t->cbFlashStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->eventlogShow(); break;
        case 33: _t->rcvDetAutoReport((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 34: _t->cbDetStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->getCtCircle(); break;
        case 36: _t->getCtNodeStage((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 37: _t->rcvCtPattern(); break;
        case 38: _t->ctNameModelChange(); break;
        case 39: _t->vipNodeListChange(); break;
        case 40: _t->vipNodeState((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 41: _t->clickVipId((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 42: _t->vipIdModelChange(); break;
        case 43: _t->vipItemChange((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 44: _t->clusterClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->trafficMaxMinTime((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        case 46: _t->trafficData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QMap<quint32,quint32>(*)>(_a[2]))); break;
        case 47: _t->completeTraffic(); break;
        case 48: _t->dealMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 49: _t->on_connect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->on_rcvTscIpInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 51: _t->on_treeviewDataChange((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 52: _t->on_treeViewClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 53: _t->on_setFlagShowInterfase((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->on_tabWidgetIndexChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->on_treeViewRightClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 56: _t->on_schEventChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PDataProcess::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PDataProcess::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PDataProcess,
      qt_meta_data_PDataProcess, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PDataProcess::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PDataProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PDataProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PDataProcess))
        return static_cast<void*>(const_cast< PDataProcess*>(this));
    return QObject::qt_metacast(_clname);
}

int PDataProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 57)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 57;
    }
    return _id;
}

// SIGNAL 0
void PDataProcess::statusBarMessage(QString _t1, quint8 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void PDataProcess::setNodeParaCbTscId(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PDataProcess::nodeChangeIndex(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PDataProcess::receivedUserLogin(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PDataProcess::receivedUserView(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PDataProcess::receivedNodeCommand(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PDataProcess::receivedTimeBaseResponse(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PDataProcess::receivedScheduleResponse(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PDataProcess::receivedTimePatternResponse(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PDataProcess::receivedStageTimeResponse(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PDataProcess::sendToService(QByteArray _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void PDataProcess::recvMessage(QByteArray _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void PDataProcess::clickTreeView(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void PDataProcess::resetNodeNameModel(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void PDataProcess::readCmdArr(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void PDataProcess::rcvModuleTable()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}

// SIGNAL 17
void PDataProcess::changeSpecialModel()
{
    QMetaObject::activate(this, &staticMetaObject, 17, 0);
}

// SIGNAL 18
void PDataProcess::clickTimebaseIndex(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void PDataProcess::clickSchIndex(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void PDataProcess::updateTimePatternName()
{
    QMetaObject::activate(this, &staticMetaObject, 20, 0);
}

// SIGNAL 21
void PDataProcess::rcvStageTimeTable()
{
    QMetaObject::activate(this, &staticMetaObject, 21, 0);
}

// SIGNAL 22
void PDataProcess::rcvConflict()
{
    QMetaObject::activate(this, &staticMetaObject, 22, 0);
}

// SIGNAL 23
void PDataProcess::rcvPhase()
{
    QMetaObject::activate(this, &staticMetaObject, 23, 0);
}

// SIGNAL 24
void PDataProcess::rcvDet()
{
    QMetaObject::activate(this, &staticMetaObject, 24, 0);
}

// SIGNAL 25
void PDataProcess::rcvDetAlarm()
{
    QMetaObject::activate(this, &staticMetaObject, 25, 0);
}

// SIGNAL 26
void PDataProcess::rcvAutoReport(unsigned char * _t1, int _t2, quint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void PDataProcess::changeNodeId()
{
    QMetaObject::activate(this, &staticMetaObject, 27, 0);
}

// SIGNAL 28
void PDataProcess::rcvManualCtrl(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void PDataProcess::rcvTscStatus(unsigned char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void PDataProcess::rcvTscTime(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void PDataProcess::cbFlashStatus(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void PDataProcess::eventlogShow()
{
    QMetaObject::activate(this, &staticMetaObject, 32, 0);
}

// SIGNAL 33
void PDataProcess::rcvDetAutoReport(unsigned char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void PDataProcess::cbDetStatus(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void PDataProcess::getCtCircle()
{
    QMetaObject::activate(this, &staticMetaObject, 35, 0);
}

// SIGNAL 36
void PDataProcess::getCtNodeStage(quint8 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void PDataProcess::rcvCtPattern()
{
    QMetaObject::activate(this, &staticMetaObject, 37, 0);
}

// SIGNAL 38
void PDataProcess::ctNameModelChange()
{
    QMetaObject::activate(this, &staticMetaObject, 38, 0);
}

// SIGNAL 39
void PDataProcess::vipNodeListChange()
{
    QMetaObject::activate(this, &staticMetaObject, 39, 0);
}

// SIGNAL 40
void PDataProcess::vipNodeState(quint32 _t1, bool _t2, quint8 _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void PDataProcess::clickVipId(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 41, _a);
}

// SIGNAL 42
void PDataProcess::vipIdModelChange()
{
    QMetaObject::activate(this, &staticMetaObject, 42, 0);
}

// SIGNAL 43
void PDataProcess::vipItemChange(quint32 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void PDataProcess::clusterClick(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void PDataProcess::trafficMaxMinTime(quint32 _t1, quint32 _t2, quint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 45, _a);
}

// SIGNAL 46
void PDataProcess::trafficData(QString _t1, QMap<quint32,quint32> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 46, _a);
}

// SIGNAL 47
void PDataProcess::completeTraffic()
{
    QMetaObject::activate(this, &staticMetaObject, 47, 0);
}
QT_END_MOC_NAMESPACE
