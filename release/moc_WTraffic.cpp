/****************************************************************************
** Meta object code from reading C++ file 'WTraffic.h'
**
** Created: Fri Sep 21 18:11:13 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WTraffic.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WTraffic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WTraffic[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x0a,
      36,   10,    9,    9, 0x0a,
      57,    9,    9,    9, 0x0a,
      71,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WTraffic[] = {
    "WTraffic\0\0b\0on_cbDevicedCheck(bool)\0"
    "on_cbTimeCheck(bool)\0on_btnQuery()\0"
    "on_btnDelete()\0"
};

void WTraffic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WTraffic *_t = static_cast<WTraffic *>(_o);
        switch (_id) {
        case 0: _t->on_cbDevicedCheck((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_cbTimeCheck((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_btnQuery(); break;
        case 3: _t->on_btnDelete(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WTraffic::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WTraffic::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WTraffic,
      qt_meta_data_WTraffic, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WTraffic::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WTraffic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WTraffic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WTraffic))
        return static_cast<void*>(const_cast< WTraffic*>(this));
    return QWidget::qt_metacast(_clname);
}

int WTraffic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_trafficLine[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   13,   12,   12, 0x0a,
      89,   73,   12,   12, 0x0a,
     135,   12,   12,   12, 0x0a,
     156,   12,   12,   12, 0x0a,
     167,   12,   12,   12, 0x0a,
     180,   12,   12,   12, 0x0a,
     193,   12,   12,   12, 0x0a,
     207,   12,   12,   12, 0x0a,
     223,   12,   12,   12, 0x0a,
     240,   12,   12,   12, 0x0a,
     255,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_trafficLine[] = {
    "trafficLine\0\0maxTime,minTime,maxY\0"
    "on_setMaxMinY(quint32,quint32,quint32)\0"
    "strName,mapData\0"
    "on_setLineData(QString,QMap<quint32,quint32>)\0"
    "on_completeTraffic()\0on_btnUp()\0"
    "on_btnDown()\0on_btnLeft()\0on_btnRight()\0"
    "on_btnLeftBig()\0on_btnRightBig()\0"
    "on_btnPageUp()\0on_btnPageDown()\0"
};

void trafficLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        trafficLine *_t = static_cast<trafficLine *>(_o);
        switch (_id) {
        case 0: _t->on_setMaxMinY((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        case 1: _t->on_setLineData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QMap<quint32,quint32>(*)>(_a[2]))); break;
        case 2: _t->on_completeTraffic(); break;
        case 3: _t->on_btnUp(); break;
        case 4: _t->on_btnDown(); break;
        case 5: _t->on_btnLeft(); break;
        case 6: _t->on_btnRight(); break;
        case 7: _t->on_btnLeftBig(); break;
        case 8: _t->on_btnRightBig(); break;
        case 9: _t->on_btnPageUp(); break;
        case 10: _t->on_btnPageDown(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData trafficLine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject trafficLine::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_trafficLine,
      qt_meta_data_trafficLine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &trafficLine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *trafficLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *trafficLine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_trafficLine))
        return static_cast<void*>(const_cast< trafficLine*>(this));
    return QWidget::qt_metacast(_clname);
}

int trafficLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
