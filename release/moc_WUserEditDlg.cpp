/****************************************************************************
** Meta object code from reading C++ file 'WUserEditDlg.h'
**
** Created: Fri Sep 21 18:10:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WUserEditDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WUserEditDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WUserEditDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      29,   13,   13,   13, 0x08,
      40,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WUserEditDlg[] = {
    "WUserEditDlg\0\0on_browseBtn()\0on_okBtn()\0"
    "on_userRightsBtn()\0"
};

void WUserEditDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WUserEditDlg *_t = static_cast<WUserEditDlg *>(_o);
        switch (_id) {
        case 0: _t->on_browseBtn(); break;
        case 1: _t->on_okBtn(); break;
        case 2: _t->on_userRightsBtn(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WUserEditDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WUserEditDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WUserEditDlg,
      qt_meta_data_WUserEditDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WUserEditDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WUserEditDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WUserEditDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WUserEditDlg))
        return static_cast<void*>(const_cast< WUserEditDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int WUserEditDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
