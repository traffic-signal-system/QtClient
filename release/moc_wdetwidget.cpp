/****************************************************************************
** Meta object code from reading C++ file 'wdetwidget.h'
**
** Created: Fri Sep 21 18:10:52 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wdetwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wdetwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WDetWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      29,   11,   11,   11, 0x0a,
      41,   11,   11,   11, 0x0a,
      54,   11,   11,   11, 0x0a,
      65,   11,   11,   11, 0x0a,
      78,   11,   11,   11, 0x0a,
      94,   92,   11,   11, 0x0a,
     117,   11,   11,   11, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_WDetWidget[] = {
    "WDetWidget\0\0on_statusCheck()\0on_appBtn()\0"
    "on_readBtn()\0on_upBtn()\0on_downBtn()\0"
    "on_flashBtn()\0b\0on_stopDetStatus(bool)\0"
    "on_stopDetStatus()\0"
};

void WDetWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WDetWidget *_t = static_cast<WDetWidget *>(_o);
        switch (_id) {
        case 0: _t->on_statusCheck(); break;
        case 1: _t->on_appBtn(); break;
        case 2: _t->on_readBtn(); break;
        case 3: _t->on_upBtn(); break;
        case 4: _t->on_downBtn(); break;
        case 5: _t->on_flashBtn(); break;
        case 6: _t->on_stopDetStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_stopDetStatus(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WDetWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WDetWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WDetWidget,
      qt_meta_data_WDetWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WDetWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WDetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WDetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WDetWidget))
        return static_cast<void*>(const_cast< WDetWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int WDetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
