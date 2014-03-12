/****************************************************************************
** Meta object code from reading C++ file 'wstatus.h'
**
** Created: Fri Sep 21 18:10:48 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wstatus.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WStatus[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      23,    8,    8,    8, 0x0a,
      43,    8,    8,    8, 0x0a,
      70,   64,    8,    8, 0x0a,
      92,    8,    8,    8, 0x0a,
     109,    8,    8,    8, 0x0a,
     127,    8,    8,    8, 0x0a,
     163,  150,    8,    8, 0x0a,
     210,  208,    8,    8, 0x0a,
     243,  233,    8,    8, 0x0a,
     281,  279,    8,    8, 0x0a,
     304,   64,    8,    8, 0x0a,
     332,    8,    8,    8, 0x0a,
     348,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WStatus[] = {
    "WStatus\0\0on_checkBtn()\0on_ctrlTypeChange()\0"
    "on_lightModeChange()\0index\0"
    "on_cbPhaseChange(int)\0on_nextStepBtn()\0"
    "on_nextStageBtn()\0on_cbFlashStatus(bool)\0"
    "para1,len,id\0on_rcvAutoReport(unsigned char*,int,quint32)\0"
    "b\0on_rcvManualCtrl(bool)\0para1,len\0"
    "on_rcvTscStatus(unsigned char*,int)\0"
    "t\0on_rcvTscTime(quint32)\0"
    "on_selectStageIndex(quint8)\0on_nodeChange()\0"
    "on_cbService(bool)\0"
};

void WStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WStatus *_t = static_cast<WStatus *>(_o);
        switch (_id) {
        case 0: _t->on_checkBtn(); break;
        case 1: _t->on_ctrlTypeChange(); break;
        case 2: _t->on_lightModeChange(); break;
        case 3: _t->on_cbPhaseChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_nextStepBtn(); break;
        case 5: _t->on_nextStageBtn(); break;
        case 6: _t->on_cbFlashStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_rcvAutoReport((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        case 8: _t->on_rcvManualCtrl((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_rcvTscStatus((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->on_rcvTscTime((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 11: _t->on_selectStageIndex((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->on_nodeChange(); break;
        case 13: _t->on_cbService((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WStatus::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WStatus::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WStatus,
      qt_meta_data_WStatus, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WStatus::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WStatus))
        return static_cast<void*>(const_cast< WStatus*>(this));
    return QWidget::qt_metacast(_clname);
}

int WStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
