/****************************************************************************
** Meta object code from reading C++ file 'wstage.h'
**
** Created: Fri Sep 21 18:10:46 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wstage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wstage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WStage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x05,
      39,    7,    7,    7, 0x05,
      54,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,    7,    7,    7, 0x0a,
      97,   95,    7,    7, 0x0a,
     127,    7,    7,    7, 0x0a,
     139,    7,    7,    7, 0x0a,
     151,    7,    7,    7, 0x0a,
     164,    7,    7,    7, 0x0a,
     176,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WStage[] = {
    "WStage\0\0index\0changeStageIndex(quint8)\0"
    "btnReadStage()\0btnAppStage()\0"
    "on_iconMouseClick(quint16)\0,\0"
    "on_widMouseClick(bool,quint8)\0on_btnAdd()\0"
    "on_btnDel()\0on_btnRead()\0on_btnApp()\0"
    "on_changeNode()\0"
};

void WStage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WStage *_t = static_cast<WStage *>(_o);
        switch (_id) {
        case 0: _t->changeStageIndex((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->btnReadStage(); break;
        case 2: _t->btnAppStage(); break;
        case 3: _t->on_iconMouseClick((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 4: _t->on_widMouseClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 5: _t->on_btnAdd(); break;
        case 6: _t->on_btnDel(); break;
        case 7: _t->on_btnRead(); break;
        case 8: _t->on_btnApp(); break;
        case 9: _t->on_changeNode(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WStage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WStage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WStage,
      qt_meta_data_WStage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WStage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WStage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WStage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WStage))
        return static_cast<void*>(const_cast< WStage*>(this));
    return QWidget::qt_metacast(_clname);
}

int WStage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void WStage::changeStageIndex(quint8 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WStage::btnReadStage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WStage::btnAppStage()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
