/****************************************************************************
** Meta object code from reading C++ file 'WUserViewDlg.h'
**
** Created: Fri Sep 21 18:10:34 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WUserViewDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WUserViewDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WUserViewDlg[] = {

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
      14,   13,   13,   13, 0x08,
      30,   13,   13,   13, 0x08,
      47,   13,   13,   13, 0x08,
      64,   13,   13,   13, 0x08,
      80,   13,   13,   13, 0x08,
      98,   96,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WUserViewDlg[] = {
    "WUserViewDlg\0\0on_addUserBtn()\0"
    "on_editUserBtn()\0on_quitUserBtn()\0"
    "on_delUserBtn()\0on_refreshBtn()\0,\0"
    "dealReceivedMessage(char*,int)\0"
};

void WUserViewDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WUserViewDlg *_t = static_cast<WUserViewDlg *>(_o);
        switch (_id) {
        case 0: _t->on_addUserBtn(); break;
        case 1: _t->on_editUserBtn(); break;
        case 2: _t->on_quitUserBtn(); break;
        case 3: _t->on_delUserBtn(); break;
        case 4: _t->on_refreshBtn(); break;
        case 5: _t->dealReceivedMessage((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WUserViewDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WUserViewDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WUserViewDlg,
      qt_meta_data_WUserViewDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WUserViewDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WUserViewDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WUserViewDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WUserViewDlg))
        return static_cast<void*>(const_cast< WUserViewDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int WUserViewDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
