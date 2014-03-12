/****************************************************************************
** Meta object code from reading C++ file 'Vip.h'
**
** Created: Fri Sep 21 18:11:00 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Vip.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Vip.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VipNode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_VipNode[] = {
    "VipNode\0\0mouseSelect(VipNode*)\0"
};

void VipNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VipNode *_t = static_cast<VipNode *>(_o);
        switch (_id) {
        case 0: _t->mouseSelect((*reinterpret_cast< VipNode*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VipNode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VipNode::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VipNode,
      qt_meta_data_VipNode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VipNode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VipNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VipNode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VipNode))
        return static_cast<void*>(const_cast< VipNode*>(this));
    return QWidget::qt_metacast(_clname);
}

int VipNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void VipNode::mouseSelect(VipNode * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_VipNodeContent[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VipNodeContent[] = {
    "VipNodeContent\0\0mouseSelect(VipNode*)\0"
    "on_mouseSelect(VipNode*)\0"
};

void VipNodeContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VipNodeContent *_t = static_cast<VipNodeContent *>(_o);
        switch (_id) {
        case 0: _t->mouseSelect((*reinterpret_cast< VipNode*(*)>(_a[1]))); break;
        case 1: _t->on_mouseSelect((*reinterpret_cast< VipNode*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VipNodeContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VipNodeContent::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VipNodeContent,
      qt_meta_data_VipNodeContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VipNodeContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VipNodeContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VipNodeContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VipNodeContent))
        return static_cast<void*>(const_cast< VipNodeContent*>(this));
    return QWidget::qt_metacast(_clname);
}

int VipNodeContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void VipNodeContent::mouseSelect(VipNode * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
