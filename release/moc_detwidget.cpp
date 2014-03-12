/****************************************************************************
** Meta object code from reading C++ file 'detwidget.h'
**
** Created: Fri Sep 21 18:10:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../detwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'detwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DetIcon[] = {

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
       9,    8,    8,    8, 0x05,
      48,   32,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DetIcon[] = {
    "DetIcon\0\0leaveContent(DetIcon*)\0"
    "b,btype,index,p\0mouseStatus(bool,bool,quint8,QPoint)\0"
};

void DetIcon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DetIcon *_t = static_cast<DetIcon *>(_o);
        switch (_id) {
        case 0: _t->leaveContent((*reinterpret_cast< DetIcon*(*)>(_a[1]))); break;
        case 1: _t->mouseStatus((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< QPoint(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DetIcon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetIcon::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DetIcon,
      qt_meta_data_DetIcon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetIcon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetIcon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetIcon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetIcon))
        return static_cast<void*>(const_cast< DetIcon*>(this));
    return QDialog::qt_metacast(_clname);
}

int DetIcon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void DetIcon::leaveContent(DetIcon * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DetIcon::mouseStatus(bool _t1, bool _t2, quint8 _t3, QPoint _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_DetContent[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      49,   33,   11,   11, 0x05,
      92,   86,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     110,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DetContent[] = {
    "DetContent\0\0removeIcon(DetIcon*)\0"
    "b,btype,index,p\0mouseStatus(bool,bool,quint8,QPoint)\0"
    "detNo\0detChangePos(int)\0on_IconLeave(DetIcon*)\0"
};

void DetContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DetContent *_t = static_cast<DetContent *>(_o);
        switch (_id) {
        case 0: _t->removeIcon((*reinterpret_cast< DetIcon*(*)>(_a[1]))); break;
        case 1: _t->mouseStatus((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< QPoint(*)>(_a[4]))); break;
        case 2: _t->detChangePos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_IconLeave((*reinterpret_cast< DetIcon*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DetContent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetContent::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DetContent,
      qt_meta_data_DetContent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetContent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetContent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetContent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetContent))
        return static_cast<void*>(const_cast< DetContent*>(this));
    return QDialog::qt_metacast(_clname);
}

int DetContent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void DetContent::removeIcon(DetIcon * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DetContent::mouseStatus(bool _t1, bool _t2, quint8 _t3, QPoint _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DetContent::detChangePos(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
static const uint qt_meta_data_DetParaDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      25,   23,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   11,   11,   11, 0x0a,
      59,   11,   11,   11, 0x0a,
      80,   74,   11,   11, 0x0a,
     102,   74,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     146,  140,   11,   11, 0x0a,
     167,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DetParaDlg[] = {
    "DetParaDlg\0\0closeDlg()\0b\0mouseStatus(bool)\0"
    "on_confirmBtn()\0on_cancelBtn()\0index\0"
    "on_cbDetNoChange(int)\0on_cbDirNoChange(int)\0"
    "on_dataChange()\0detNo\0on_detChangePos(int)\0"
    "on_btnMore()\0"
};

void DetParaDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DetParaDlg *_t = static_cast<DetParaDlg *>(_o);
        switch (_id) {
        case 0: _t->closeDlg(); break;
        case 1: _t->mouseStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_confirmBtn(); break;
        case 3: _t->on_cancelBtn(); break;
        case 4: _t->on_cbDetNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_cbDirNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_dataChange(); break;
        case 7: _t->on_detChangePos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_btnMore(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DetParaDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetParaDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DetParaDlg,
      qt_meta_data_DetParaDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetParaDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetParaDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetParaDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetParaDlg))
        return static_cast<void*>(const_cast< DetParaDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int DetParaDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DetParaDlg::closeDlg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DetParaDlg::mouseStatus(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_DetWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   10,   10,   10, 0x0a,
      44,   10,   10,   10, 0x0a,
      78,   68,   10,   10, 0x0a,
     114,   10,   10,   10, 0x0a,
     147,  131,   10,   10, 0x0a,
     189,  187,   10,   10, 0x0a,
     213,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DetWidget[] = {
    "DetWidget\0\0stopDetStatus()\0on_rcvDetector()\0"
    "on_removeIcon(DetIcon*)\0para1,len\0"
    "on_rcvDetStatus(unsigned char*,int)\0"
    "on_rcvDetAlarm()\0b,btype,index,p\0"
    "on_mouseStatus(bool,bool,quint8,QPoint)\0"
    "b\0on_dlgMouseStatus(bool)\0"
    "on_closeDetParaDlg()\0"
};

void DetWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DetWidget *_t = static_cast<DetWidget *>(_o);
        switch (_id) {
        case 0: _t->stopDetStatus(); break;
        case 1: _t->on_rcvDetector(); break;
        case 2: _t->on_removeIcon((*reinterpret_cast< DetIcon*(*)>(_a[1]))); break;
        case 3: _t->on_rcvDetStatus((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_rcvDetAlarm(); break;
        case 5: _t->on_mouseStatus((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< QPoint(*)>(_a[4]))); break;
        case 6: _t->on_dlgMouseStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_closeDetParaDlg(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DetWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DetWidget,
      qt_meta_data_DetWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetWidget))
        return static_cast<void*>(const_cast< DetWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int DetWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void DetWidget::stopDetStatus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_FlowWidget[] = {

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

static const char qt_meta_stringdata_FlowWidget[] = {
    "FlowWidget\0"
};

void FlowWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData FlowWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FlowWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FlowWidget,
      qt_meta_data_FlowWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FlowWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FlowWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FlowWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FlowWidget))
        return static_cast<void*>(const_cast< FlowWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FlowWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
