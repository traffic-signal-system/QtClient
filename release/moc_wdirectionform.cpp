/****************************************************************************
** Meta object code from reading C++ file 'wdirectionform.h'
**
** Created: Fri Sep 21 18:11:05 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wdirectionform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wdirectionform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DirectionIcon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      50,   40,   14,   14, 0x05,
      81,   74,   14,   14, 0x05,
     104,   74,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DirectionIcon[] = {
    "DirectionIcon\0\0b\0includePhaseTurn(bool)\0"
    "b,phaseId\0mouseClick(bool,quint8)\0"
    ",phase\0leftClick(bool,quint8)\0"
    "rightClick(bool,quint8)\0"
    "on_includePhaseTurn(bool)\0"
};

void DirectionIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DirectionIcon *_t = static_cast<DirectionIcon *>(_o);
        switch (_id) {
        case 0: _t->includePhaseTurn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->mouseClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 2: _t->leftClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 3: _t->rightClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 4: _t->on_includePhaseTurn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DirectionIcon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DirectionIcon::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_DirectionIcon,
      qt_meta_data_DirectionIcon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DirectionIcon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DirectionIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DirectionIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DirectionIcon))
        return static_cast<void*>(const_cast< DirectionIcon*>(this));
    return QLabel::qt_metacast(_clname);
}

int DirectionIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DirectionIcon::includePhaseTurn(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DirectionIcon::mouseClick(bool _t1, quint8 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DirectionIcon::leftClick(bool _t1, quint8 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DirectionIcon::rightClick(bool _t1, quint8 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
static const uint qt_meta_data_WDirectionForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   16,   15,   15, 0x05,
      52,   50,   15,   15, 0x25,
      69,   15,   15,   15, 0x25,
      84,   82,   15,   15, 0x05,
     107,   82,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     131,   82,   15,   15, 0x0a,
     157,   82,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WDirectionForm[] = {
    "WDirectionForm\0\0b,phaseId\0"
    "mouseClick(bool,quint8)\0b\0mouseClick(bool)\0"
    "mouseClick()\0,\0leftClick(bool,quint8)\0"
    "rightClick(bool,quint8)\0"
    "on_leftClick(bool,quint8)\0"
    "on_rightClick(bool,quint8)\0"
};

void WDirectionForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WDirectionForm *_t = static_cast<WDirectionForm *>(_o);
        switch (_id) {
        case 0: _t->mouseClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 1: _t->mouseClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->mouseClick(); break;
        case 3: _t->leftClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 4: _t->rightClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 5: _t->on_leftClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 6: _t->on_rightClick((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WDirectionForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WDirectionForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WDirectionForm,
      qt_meta_data_WDirectionForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WDirectionForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WDirectionForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WDirectionForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WDirectionForm))
        return static_cast<void*>(const_cast< WDirectionForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int WDirectionForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WDirectionForm::mouseClick(bool _t1, quint8 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void WDirectionForm::leftClick(bool _t1, quint8 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WDirectionForm::rightClick(bool _t1, quint8 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
static const uint qt_meta_data_StageGroup[] = {

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
      18,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StageGroup[] = {
    "StageGroup\0\0phase\0mouseClick(quint16)\0"
    "on_mouseClick(phaseWidget*)\0"
};

void StageGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StageGroup *_t = static_cast<StageGroup *>(_o);
        switch (_id) {
        case 0: _t->mouseClick((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 1: _t->on_mouseClick((*reinterpret_cast< phaseWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StageGroup::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StageGroup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StageGroup,
      qt_meta_data_StageGroup, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StageGroup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StageGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StageGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StageGroup))
        return static_cast<void*>(const_cast< StageGroup*>(this));
    return QWidget::qt_metacast(_clname);
}

int StageGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void StageGroup::mouseClick(quint16 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
