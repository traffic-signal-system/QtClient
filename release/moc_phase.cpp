/****************************************************************************
** Meta object code from reading C++ file 'phase.h'
**
** Created: Fri Sep 21 18:11:04 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../phase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'phase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WordIcon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   10,    9,    9, 0x05,
      44,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      70,   68,    9,    9, 0x0a,
      99,    9,    9,    9, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_WordIcon[] = {
    "WordIcon\0\0id,bClick\0mouseClick(quint8,bool)\0"
    "leaveContent(WordIcon*)\0b\0"
    "on_setOverlapFlagValid(bool)\0"
    "on_setOverlapFlagValid()\0"
};

void WordIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WordIcon *_t = static_cast<WordIcon *>(_o);
        switch (_id) {
        case 0: _t->mouseClick((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->leaveContent((*reinterpret_cast< WordIcon*(*)>(_a[1]))); break;
        case 2: _t->on_setOverlapFlagValid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_setOverlapFlagValid(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WordIcon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WordIcon::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_WordIcon,
      qt_meta_data_WordIcon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WordIcon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WordIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WordIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WordIcon))
        return static_cast<void*>(const_cast< WordIcon*>(this));
    return QLabel::qt_metacast(_clname);
}

int WordIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WordIcon::mouseClick(quint8 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WordIcon::leaveContent(WordIcon * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_ChlIcon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,    9,    8,    8, 0x05,
      61,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ChlIcon[] = {
    "ChlIcon\0\0chlId,bClick,phaseId\0"
    "mouseClick(quint8,bool,quint8)\0"
    "leaveContent(ChlIcon*)\0"
};

void ChlIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChlIcon *_t = static_cast<ChlIcon *>(_o);
        switch (_id) {
        case 0: _t->mouseClick((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 1: _t->leaveContent((*reinterpret_cast< ChlIcon*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ChlIcon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChlIcon::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ChlIcon,
      qt_meta_data_ChlIcon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChlIcon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChlIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChlIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChlIcon))
        return static_cast<void*>(const_cast< ChlIcon*>(this));
    return QLabel::qt_metacast(_clname);
}

int ChlIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void ChlIcon::mouseClick(quint8 _t1, bool _t2, quint8 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChlIcon::leaveContent(ChlIcon * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_IconContent[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x05,
      59,   37,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      95,   12,   12,   12, 0x0a,
     124,   12,   12,   12, 0x0a,
     171,  156,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IconContent[] = {
    "IconContent\0\0b\0setOverlapValid(bool)\0"
    "contId,bClick,phaseId\0"
    "mouseClickPhase(quint8,bool,quint8)\0"
    "on_chlLeaveContent(ChlIcon*)\0"
    "on_phaseLeaveContent(WordIcon*)\0"
    "phaseId,bClick\0on_mouseClickPhase(quint8,bool)\0"
};

void IconContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IconContent *_t = static_cast<IconContent *>(_o);
        switch (_id) {
        case 0: _t->setOverlapValid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->mouseClickPhase((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 2: _t->on_chlLeaveContent((*reinterpret_cast< ChlIcon*(*)>(_a[1]))); break;
        case 3: _t->on_phaseLeaveContent((*reinterpret_cast< WordIcon*(*)>(_a[1]))); break;
        case 4: _t->on_mouseClickPhase((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IconContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IconContent::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IconContent,
      qt_meta_data_IconContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IconContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IconContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IconContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IconContent))
        return static_cast<void*>(const_cast< IconContent*>(this));
    return QWidget::qt_metacast(_clname);
}

int IconContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void IconContent::setOverlapValid(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IconContent::mouseClickPhase(quint8 _t1, bool _t2, quint8 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_LoadIcon[] = {

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
      13,   10,    9,    9, 0x05,
      39,    9,    9,    9, 0x25,
      67,   60,    9,    9, 0x05,
     114,   92,    9,    9, 0x05,
     164,  150,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     191,    9,    9,    9, 0x0a,
     238,  223,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoadIcon[] = {
    "LoadIcon\0\0,b\0clearContent(quint8,bool)\0"
    "clearContent(quint8)\0loadNo\0"
    "mouseDoubleClick(quint8)\0contId,bClick,phaseId\0"
    "mouseClickPhase(quint8,bool,quint8)\0"
    "contId,bClick\0mouseClickDir(quint8,bool)\0"
    "on_phaseLeaveContent(WordIcon*)\0"
    "phaseId,bClick\0on_mouseClickPhase(quint8,bool)\0"
};

void LoadIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoadIcon *_t = static_cast<LoadIcon *>(_o);
        switch (_id) {
        case 0: _t->clearContent((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->clearContent((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->mouseDoubleClick((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->mouseClickPhase((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 4: _t->mouseClickDir((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->on_phaseLeaveContent((*reinterpret_cast< WordIcon*(*)>(_a[1]))); break;
        case 6: _t->on_mouseClickPhase((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoadIcon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoadIcon::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_LoadIcon,
      qt_meta_data_LoadIcon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadIcon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadIcon))
        return static_cast<void*>(const_cast< LoadIcon*>(this));
    return QLabel::qt_metacast(_clname);
}

int LoadIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void LoadIcon::clearContent(quint8 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void LoadIcon::mouseDoubleClick(quint8 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LoadIcon::mouseClickPhase(quint8 _t1, bool _t2, quint8 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LoadIcon::mouseClickDir(quint8 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
static const uint qt_meta_data_phaseWidget[] = {

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
      13,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_phaseWidget[] = {
    "phaseWidget\0\0mouseClick(phaseWidget*)\0"
};

void phaseWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        phaseWidget *_t = static_cast<phaseWidget *>(_o);
        switch (_id) {
        case 0: _t->mouseClick((*reinterpret_cast< phaseWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phaseWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phaseWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_phaseWidget,
      qt_meta_data_phaseWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phaseWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phaseWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phaseWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phaseWidget))
        return static_cast<void*>(const_cast< phaseWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int phaseWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void phaseWidget::mouseClick(phaseWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_DragIcon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DragIcon[] = {
    "DragIcon\0"
};

void DragIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DragIcon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DragIcon::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_DragIcon,
      qt_meta_data_DragIcon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DragIcon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DragIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DragIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DragIcon))
        return static_cast<void*>(const_cast< DragIcon*>(this));
    return QLabel::qt_metacast(_clname);
}

int DragIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ColorWidget[] = {

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
      16,   13,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ColorWidget[] = {
    "ColorWidget\0\0,,\0colorTimeChange(quint8,quint8,quint8)\0"
};

void ColorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ColorWidget *_t = static_cast<ColorWidget *>(_o);
        switch (_id) {
        case 0: _t->colorTimeChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ColorWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ColorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ColorWidget,
      qt_meta_data_ColorWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorWidget))
        return static_cast<void*>(const_cast< ColorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ColorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ColorWidget::colorTimeChange(quint8 _t1, quint8 _t2, quint8 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
