/****************************************************************************
** Meta object code from reading C++ file 'weventlogwidget.h'
**
** Created: Fri Sep 21 18:10:53 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../weventlogwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weventlogwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WEventLogWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      30,   16,   16,   16, 0x0a,
      49,   43,   16,   16, 0x0a,
      70,   16,   16,   16, 0x0a,
      86,   16,   16,   16, 0x0a,
     104,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WEventLogWidget[] = {
    "WEventLogWidget\0\0on_readBtn()\0"
    "on_sort(int)\0index\0on_cbNameChange(int)\0"
    "on_changeNode()\0on_eventlogShow()\0"
    "on_cbTimeChange()\0"
};

void WEventLogWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WEventLogWidget *_t = static_cast<WEventLogWidget *>(_o);
        switch (_id) {
        case 0: _t->on_readBtn(); break;
        case 1: _t->on_sort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_cbNameChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_changeNode(); break;
        case 4: _t->on_eventlogShow(); break;
        case 5: _t->on_cbTimeChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WEventLogWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WEventLogWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WEventLogWidget,
      qt_meta_data_WEventLogWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WEventLogWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WEventLogWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WEventLogWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WEventLogWidget))
        return static_cast<void*>(const_cast< WEventLogWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int WEventLogWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
