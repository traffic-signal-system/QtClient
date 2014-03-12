/****************************************************************************
** Meta object code from reading C++ file 'wtimeset.h'
**
** Created: Fri Sep 21 18:10:44 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wtimeset.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wtimeset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WTimeSet[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,    9,    9,    9, 0x0a,
      59,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WTimeSet[] = {
    "WTimeSet\0\0str\0StageTimeChange(QString)\0"
    "on_sbStageTime(int)\0on_OptionBtn()\0"
};

void WTimeSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WTimeSet *_t = static_cast<WTimeSet *>(_o);
        switch (_id) {
        case 0: _t->StageTimeChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_sbStageTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_OptionBtn(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WTimeSet::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WTimeSet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WTimeSet,
      qt_meta_data_WTimeSet, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WTimeSet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WTimeSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WTimeSet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WTimeSet))
        return static_cast<void*>(const_cast< WTimeSet*>(this));
    return QWidget::qt_metacast(_clname);
}

int WTimeSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WTimeSet::StageTimeChange(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
