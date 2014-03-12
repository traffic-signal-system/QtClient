/****************************************************************************
** Meta object code from reading C++ file 'wnodeparadlg.h'
**
** Created: Fri Sep 21 18:10:39 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wnodeparadlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wnodeparadlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WNodeParaDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x0a,
      36,   13,   13,   13, 0x0a,
      53,   13,   13,   13, 0x0a,
      69,   13,   13,   13, 0x0a,
      85,   13,   13,   13, 0x0a,
     101,   13,   13,   13, 0x0a,
     120,  118,   13,   13, 0x0a,
     145,   13,   13,   13, 0x0a,
     165,  161,   13,   13, 0x0a,
     194,  161,   13,   13, 0x0a,
     226,  161,   13,   13, 0x0a,
     253,   13,   13,   13, 0x0a,
     267,   13,   13,   13, 0x0a,
     281,   13,   13,   13, 0x0a,
     296,   13,   13,   13, 0x0a,
     310,   14,   13,   13, 0x0a,
     331,  161,   13,   13, 0x0a,
     356,  161,   13,   13, 0x0a,
     385,   14,   13,   13, 0x0a,
     408,   13,   13,   13, 0x0a,
     423,   13,   13,   13, 0x0a,
     439,   13,   13,   13, 0x0a,
     454,   13,   13,   13, 0x0a,
     469,   14,   13,   13, 0x0a,
     491,   14,   13,   13, 0x0a,
     517,   14,   13,   13, 0x0a,
     540,   14,   13,   13, 0x0a,
     564,   13,   13,   13, 0x0a,
     595,   13,   13,   13, 0x0a,
     624,   13,   13,   13, 0x0a,
     637,   13,   13,   13, 0x0a,
     667,   13,   13,   13, 0x0a,
     699,   13,   13,   13, 0x0a,
     722,   13,   13,   13, 0x0a,
     740,   13,   13,   13, 0x0a,
     758,   13,   13,   13, 0x0a,
     776,   13,   13,   13, 0x0a,
     795,   13,   13,   13, 0x0a,
     808,   13,   13,   13, 0x0a,
     821,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WNodeParaDlg[] = {
    "WNodeParaDlg\0\0index\0setDlgData(int)\0"
    "on_editNodeBtn()\0on_addNodeBtn()\0"
    "on_delNodeBtn()\0on_appNodeBtn()\0"
    "on_readNodeBtn()\0,\0dealRcvNodeCmd(int,bool)\0"
    "on_dataChange()\0str\0on_nodeNameCBChange(QString)\0"
    "on_nodeClusterCBChange(QString)\0"
    "on_nodeIpLEChange(QString)\0on_addCTBtn()\0"
    "on_delCTBtn()\0on_readCTBtn()\0on_appCTBtn()\0"
    "on_ctNameChange(int)\0on_ctNameChange(QString)\0"
    "on_ctDomainIdChange(QString)\0"
    "on_ctEnableChange(int)\0on_addVipBtn()\0"
    "on_readVipBtn()\0on_delVipBtn()\0"
    "on_appVipBtn()\0on_cbVipIdChange(int)\0"
    "on_cbVipEnableChange(int)\0"
    "on_cbVipDirChange(int)\0on_cbVipCtrlChange(int)\0"
    "on_edVipStartChange(QDateTime)\0"
    "on_edVipEndChange(QDateTime)\0on_timeout()\0"
    "on_treeViewClick(QModelIndex)\0"
    "on_moduleViewClick(QModelIndex)\0"
    "on_moduleNoChange(int)\0on_moduleAddBtn()\0"
    "on_moduleDelBtn()\0on_btnAppModule()\0"
    "on_btnReadModule()\0on_dec1Btn()\0"
    "on_dec2Btn()\0on_rcvModuleTable()\0"
};

void WNodeParaDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WNodeParaDlg *_t = static_cast<WNodeParaDlg *>(_o);
        switch (_id) {
        case 0: _t->setDlgData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_editNodeBtn(); break;
        case 2: _t->on_addNodeBtn(); break;
        case 3: _t->on_delNodeBtn(); break;
        case 4: _t->on_appNodeBtn(); break;
        case 5: _t->on_readNodeBtn(); break;
        case 6: _t->dealRcvNodeCmd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->on_dataChange(); break;
        case 8: _t->on_nodeNameCBChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->on_nodeClusterCBChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->on_nodeIpLEChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->on_addCTBtn(); break;
        case 12: _t->on_delCTBtn(); break;
        case 13: _t->on_readCTBtn(); break;
        case 14: _t->on_appCTBtn(); break;
        case 15: _t->on_ctNameChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_ctNameChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->on_ctDomainIdChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->on_ctEnableChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_addVipBtn(); break;
        case 20: _t->on_readVipBtn(); break;
        case 21: _t->on_delVipBtn(); break;
        case 22: _t->on_appVipBtn(); break;
        case 23: _t->on_cbVipIdChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_cbVipEnableChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_cbVipDirChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_cbVipCtrlChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_edVipStartChange((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 28: _t->on_edVipEndChange((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 29: _t->on_timeout(); break;
        case 30: _t->on_treeViewClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 31: _t->on_moduleViewClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 32: _t->on_moduleNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_moduleAddBtn(); break;
        case 34: _t->on_moduleDelBtn(); break;
        case 35: _t->on_btnAppModule(); break;
        case 36: _t->on_btnReadModule(); break;
        case 37: _t->on_dec1Btn(); break;
        case 38: _t->on_dec2Btn(); break;
        case 39: _t->on_rcvModuleTable(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WNodeParaDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WNodeParaDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WNodeParaDlg,
      qt_meta_data_WNodeParaDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WNodeParaDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WNodeParaDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WNodeParaDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WNodeParaDlg))
        return static_cast<void*>(const_cast< WNodeParaDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int WNodeParaDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
