/****************************************************************************
** Meta object code from reading C++ file 'WUserLogIn.h'
**
** Created: Fri Sep 21 18:10:29 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WUserLogIn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WUserLogIn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WUserLogIn[] = {

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
      12,   11,   11,   11, 0x08,
      27,   11,   11,   11, 0x08,
      51,   11,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,
     111,  103,   11,   11, 0x08,
     142,  134,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WUserLogIn[] = {
    "WUserLogIn\0\0setConnected()\0"
    "On_exitButton_clicked()\0"
    "On_connectButton_clicked()\0"
    "On_loginButton_clicked()\0bStatus\0"
    "setConnectStatus(bool)\0rcv,len\0"
    "checkLogInStatus(char*,int)\0"
};

void WUserLogIn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WUserLogIn *_t = static_cast<WUserLogIn *>(_o);
        switch (_id) {
        case 0: _t->setConnected(); break;
        case 1: _t->On_exitButton_clicked(); break;
        case 2: _t->On_connectButton_clicked(); break;
        case 3: _t->On_loginButton_clicked(); break;
        case 4: _t->setConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->checkLogInStatus((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WUserLogIn::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WUserLogIn::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WUserLogIn,
      qt_meta_data_WUserLogIn, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WUserLogIn::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WUserLogIn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WUserLogIn::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WUserLogIn))
        return static_cast<void*>(const_cast< WUserLogIn*>(this));
    return QDialog::qt_metacast(_clname);
}

int WUserLogIn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
