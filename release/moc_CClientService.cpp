/****************************************************************************
** Meta object code from reading C++ file 'CClientService.h'
**
** Created: Fri Sep 21 18:10:31 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CClientService.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CClientService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_handlerThread[] = {

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

static const char qt_meta_stringdata_handlerThread[] = {
    "handlerThread\0"
};

void handlerThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData handlerThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject handlerThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_handlerThread,
      qt_meta_data_handlerThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &handlerThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *handlerThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *handlerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_handlerThread))
        return static_cast<void*>(const_cast< handlerThread*>(this));
    return QThread::qt_metacast(_clname);
}

int handlerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_bcThread[] = {

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
      14,   10,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_bcThread[] = {
    "bcThread\0\0str\0rcvTscInfo(QString)\0"
};

void bcThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        bcThread *_t = static_cast<bcThread *>(_o);
        switch (_id) {
        case 0: _t->rcvTscInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData bcThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject bcThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_bcThread,
      qt_meta_data_bcThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &bcThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *bcThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *bcThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_bcThread))
        return static_cast<void*>(const_cast< bcThread*>(this));
    return QThread::qt_metacast(_clname);
}

int bcThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void bcThread::rcvTscInfo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_CClientService[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      40,   32,   15,   15, 0x05,
      70,   61,   15,   15, 0x05,
     101,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,  121,   15,   15, 0x0a,
     146,  142,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CClientService[] = {
    "CClientService\0\0connected(bool)\0byteArr\0"
    "received(QByteArray)\0byteArr,\0"
    "sendToService(QByteArray,bool)\0"
    "rcvTscInfo(QString)\0b\0slot_Disconn(bool)\0"
    "str\0on_rcvTscInfo(QString)\0"
};

void CClientService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CClientService *_t = static_cast<CClientService *>(_o);
        switch (_id) {
        case 0: _t->connected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->received((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->sendToService((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->rcvTscInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->slot_Disconn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_rcvTscInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CClientService::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CClientService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CClientService,
      qt_meta_data_CClientService, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CClientService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CClientService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CClientService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CClientService))
        return static_cast<void*>(const_cast< CClientService*>(this));
    return QObject::qt_metacast(_clname);
}

int CClientService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CClientService::connected(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CClientService::received(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CClientService::sendToService(QByteArray _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CClientService::rcvTscInfo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
