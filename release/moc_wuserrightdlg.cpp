/****************************************************************************
** Meta object code from reading C++ file 'wuserrightdlg.h'
**
** Created: Fri Sep 21 18:10:37 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wuserrightdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wuserrightdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WRoleRightsDlg[] = {

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
      16,   15,   15,   15, 0x0a,
      27,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WRoleRightsDlg[] = {
    "WRoleRightsDlg\0\0on_okBtn()\0on_allChenk()\0"
};

void WRoleRightsDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WRoleRightsDlg *_t = static_cast<WRoleRightsDlg *>(_o);
        switch (_id) {
        case 0: _t->on_okBtn(); break;
        case 1: _t->on_allChenk(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WRoleRightsDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WRoleRightsDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WRoleRightsDlg,
      qt_meta_data_WRoleRightsDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WRoleRightsDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WRoleRightsDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WRoleRightsDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WRoleRightsDlg))
        return static_cast<void*>(const_cast< WRoleRightsDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int WRoleRightsDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
