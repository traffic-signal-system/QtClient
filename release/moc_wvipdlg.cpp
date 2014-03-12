/****************************************************************************
** Meta object code from reading C++ file 'wvipdlg.h'
**
** Created: Fri Sep 21 18:10:58 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wvipdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wvipdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WVipDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,    9,    8,    8, 0x0a,
      37,    9,    8,    8, 0x0a,
      65,   63,    8,    8, 0x0a,
      87,    9,    8,    8, 0x0a,
     110,    8,    8,    8, 0x0a,
     131,    9,    8,    8, 0x0a,
     155,   63,    8,    8, 0x0a,
     173,    8,    8,    8, 0x0a,
     204,    8,    8,    8, 0x0a,
     233,    8,    8,    8, 0x0a,
     247,    8,    8,    8, 0x0a,
     262,    8,    8,    8, 0x0a,
     278,    8,    8,    8, 0x0a,
     293,    8,    8,    8, 0x0a,
     308,    8,    8,    8, 0x0a,
     333,  331,    8,    8, 0x0a,
     364,    8,    8,    8, 0x0a,
     393,    8,    8,    8, 0x0a,
     406,    8,    8,    8, 0x0a,
     418,    8,    8,    8, 0x0a,
     440,    8,    8,    8, 0x0a,
     461,    9,    8,    8, 0x0a,
     483,    8,    8,    8, 0x0a,
     536,  508,    8,    8, 0x0a,
     600,  581,    8,    8, 0x2a,
     651,  640,    8,    8, 0x2a,
     687,  684,    8,    8, 0x2a,
     715,    8,    8,    8, 0x2a,
     740,  736,    8,    8, 0x0a,
     771,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WVipDlg[] = {
    "WVipDlg\0\0index\0on_cbVipIdChange(int)\0"
    "on_cbVipEnableChange(int)\0b\0"
    "on_cbVipEnable2(bool)\0on_cbVipDirChange(int)\0"
    "on_cbDirChange(bool)\0on_cbVipCtrlChange(int)\0"
    "on_cbManual(bool)\0on_edVipStartChange(QDateTime)\0"
    "on_edVipEndChange(QDateTime)\0on_startBtn()\0"
    "on_addVipBtn()\0on_readVipBtn()\0"
    "on_delVipBtn()\0on_appVipBtn()\0"
    "on_vipNodeListChange()\0,\0"
    "on_vipItemChange(quint32,bool)\0"
    "on_mouseSelectNode(VipNode*)\0on_readBtn()\0"
    "on_appBtn()\0on_sbStageChange(int)\0"
    "on_sbTimeChange(int)\0on_iconSelect(quint8)\0"
    "on_cbVipStateCheck(bool)\0"
    "id,bManual,stageId,bVipShow\0"
    "on_rcvVipNodeState(quint32,bool,quint8,bool)\0"
    "id,bManual,stageId\0"
    "on_rcvVipNodeState(quint32,bool,quint8)\0"
    "id,bManual\0on_rcvVipNodeState(quint32,bool)\0"
    "id\0on_rcvVipNodeState(quint32)\0"
    "on_rcvVipNodeState()\0str\0"
    "on_treeViewClickVipId(QString)\0"
    "on_vipIdModelChange()\0"
};

void WVipDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WVipDlg *_t = static_cast<WVipDlg *>(_o);
        switch (_id) {
        case 0: _t->on_cbVipIdChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_cbVipEnableChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_cbVipEnable2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_cbVipDirChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_cbDirChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_cbVipCtrlChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_cbManual((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_edVipStartChange((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 8: _t->on_edVipEndChange((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 9: _t->on_startBtn(); break;
        case 10: _t->on_addVipBtn(); break;
        case 11: _t->on_readVipBtn(); break;
        case 12: _t->on_delVipBtn(); break;
        case 13: _t->on_appVipBtn(); break;
        case 14: _t->on_vipNodeListChange(); break;
        case 15: _t->on_vipItemChange((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->on_mouseSelectNode((*reinterpret_cast< VipNode*(*)>(_a[1]))); break;
        case 17: _t->on_readBtn(); break;
        case 18: _t->on_appBtn(); break;
        case 19: _t->on_sbStageChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_sbTimeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_iconSelect((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 22: _t->on_cbVipStateCheck((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->on_rcvVipNodeState((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 24: _t->on_rcvVipNodeState((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 25: _t->on_rcvVipNodeState((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 26: _t->on_rcvVipNodeState((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 27: _t->on_rcvVipNodeState(); break;
        case 28: _t->on_treeViewClickVipId((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: _t->on_vipIdModelChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WVipDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WVipDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WVipDlg,
      qt_meta_data_WVipDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WVipDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WVipDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WVipDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WVipDlg))
        return static_cast<void*>(const_cast< WVipDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int WVipDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
