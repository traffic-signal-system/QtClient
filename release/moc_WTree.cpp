/****************************************************************************
** Meta object code from reading C++ file 'WTree.h'
**
** Created: Fri Sep 21 18:10:25 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WTree.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WTree.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WTree[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      37,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WTree[] = {
    "WTree\0\0on_treeViewClick(QModelIndex)\0"
    "on_nodeIdChange(int)\0"
};

void WTree::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WTree *_t = static_cast<WTree *>(_o);
        switch (_id) {
        case 0: _t->on_treeViewClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_nodeIdChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WTree::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WTree::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WTree,
      qt_meta_data_WTree, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WTree::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WTree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WTree::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WTree))
        return static_cast<void*>(const_cast< WTree*>(this));
    return QWidget::qt_metacast(_clname);
}

int WTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
