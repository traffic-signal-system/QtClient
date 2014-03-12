/****************************************************************************
** Meta object code from reading C++ file 'WMainwindow.h'
**
** Created: Fri Sep 21 18:10:21 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WMainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WMainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      39,   31,   12,   12, 0x08,
      64,   12,   12,   12, 0x08,
      78,   12,   12,   12, 0x08,
      97,   12,   12,   12, 0x08,
     116,   12,   12,   12, 0x08,
     136,   12,   12,   12, 0x08,
     154,   12,   12,   12, 0x08,
     170,   12,   12,   12, 0x08,
     187,   12,   12,   12, 0x08,
     206,   12,   12,   12, 0x08,
     225,   12,   12,   12, 0x08,
     243,   12,   12,   12, 0x08,
     257,   12,   12,   12, 0x08,
     275,   12,   12,   12, 0x08,
     293,   12,   12,   12, 0x08,
     312,   12,   12,   12, 0x08,
     330,   12,   12,   12, 0x08,
     369,  356,   12,   12, 0x08,
     401,   12,   12,   12, 0x08,
     421,  414,   12,   12, 0x08,
     457,   12,   12,   12, 0x28,
     492,  486,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WMainWindow[] = {
    "WMainWindow\0\0dispDebugWindow()\0byteArr\0"
    "dealReceived(QByteArray)\0on_userView()\0"
    "on_nodeParaClick()\0on_timePlanClick()\0"
    "on_stagePlanClick()\0on_action8Click()\0"
    "on_phaseClick()\0on_statusClick()\0"
    "on_detectorClick()\0on_eventLogClick()\0"
    "on_clusterClick()\0on_vipClick()\0"
    "on_fromBtnClick()\0on_sysparaClick()\0"
    "on_conflictClick()\0on_TrafficClick()\0"
    "on_windowstackChange(int)\0byteArr,flag\0"
    "on_sendMessage(QByteArray,bool)\0"
    "on_readCmd()\0,index\0"
    "on_statusBarMessage(QString,quint8)\0"
    "on_statusBarMessage(QString)\0index\0"
    "on_tabIndexChange(int)\0"
};

void WMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WMainWindow *_t = static_cast<WMainWindow *>(_o);
        switch (_id) {
        case 0: _t->dispDebugWindow(); break;
        case 1: _t->dealReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->on_userView(); break;
        case 3: _t->on_nodeParaClick(); break;
        case 4: _t->on_timePlanClick(); break;
        case 5: _t->on_stagePlanClick(); break;
        case 6: _t->on_action8Click(); break;
        case 7: _t->on_phaseClick(); break;
        case 8: _t->on_statusClick(); break;
        case 9: _t->on_detectorClick(); break;
        case 10: _t->on_eventLogClick(); break;
        case 11: _t->on_clusterClick(); break;
        case 12: _t->on_vipClick(); break;
        case 13: _t->on_fromBtnClick(); break;
        case 14: _t->on_sysparaClick(); break;
        case 15: _t->on_conflictClick(); break;
        case 16: _t->on_TrafficClick(); break;
        case 17: _t->on_windowstackChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_sendMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 19: _t->on_readCmd(); break;
        case 20: _t->on_statusBarMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 21: _t->on_statusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->on_tabIndexChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_WMainWindow,
      qt_meta_data_WMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WMainWindow))
        return static_cast<void*>(const_cast< WMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int WMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
