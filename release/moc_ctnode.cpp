/****************************************************************************
** Meta object code from reading C++ file 'ctnode.h'
**
** Created: Fri Sep 21 18:10:57 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ctnode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctnode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CtNode[] = {

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
       8,    7,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CtNode[] = {
    "CtNode\0\0mouseSelect(quint32)\0"
};

void CtNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CtNode *_t = static_cast<CtNode *>(_o);
        switch (_id) {
        case 0: _t->mouseSelect((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CtNode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CtNode::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_CtNode,
      qt_meta_data_CtNode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CtNode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CtNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CtNode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CtNode))
        return static_cast<void*>(const_cast< CtNode*>(this));
    return QLabel::qt_metacast(_clname);
}

int CtNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void CtNode::mouseSelect(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_CtNodeContent[] = {

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
      15,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CtNodeContent[] = {
    "CtNodeContent\0\0offsetChange(quint32)\0"
};

void CtNodeContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CtNodeContent *_t = static_cast<CtNodeContent *>(_o);
        switch (_id) {
        case 0: _t->offsetChange((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CtNodeContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CtNodeContent::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CtNodeContent,
      qt_meta_data_CtNodeContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CtNodeContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CtNodeContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CtNodeContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CtNodeContent))
        return static_cast<void*>(const_cast< CtNodeContent*>(this));
    return QWidget::qt_metacast(_clname);
}

int CtNodeContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CtNodeContent::offsetChange(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
