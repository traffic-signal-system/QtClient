/****************************************************************************
** Meta object code from reading C++ file 'clusterdlg.h'
**
** Created: Fri Sep 21 18:10:55 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../clusterdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clusterdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WClusterDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      26,   12,   12,   12, 0x0a,
      40,   12,   12,   12, 0x0a,
      56,   12,   12,   12, 0x0a,
      73,   12,   12,   12, 0x0a,
      93,   12,   12,   12, 0x0a,
     116,  110,   12,   12, 0x0a,
     139,   12,   12,   12, 0x0a,
     163,  156,   12,   12, 0x0a,
     189,   12,   12,   12, 0x0a,
     219,   12,   12,   12, 0x0a,
     246,   12,   12,   12, 0x0a,
     271,   12,   12,   12, 0x0a,
     283,   12,   12,   12, 0x0a,
     296,   12,   12,   12, 0x0a,
     309,   12,   12,   12, 0x0a,
     339,   12,   12,   12, 0x0a,
     353,   12,   12,   12, 0x0a,
     367,   12,   12,   12, 0x0a,
     382,   12,   12,   12, 0x0a,
     400,  396,   12,   12, 0x0a,
     425,  396,   12,   12, 0x0a,
     454,  110,   12,   12, 0x0a,
     477,   12,   12,   12, 0x0a,
     501,   12,   12,   12, 0x0a,
     522,   12,   12,   12, 0x0a,
     544,   12,   12,   12, 0x0a,
     565,   12,   12,   12, 0x0a,
     591,   12,   12,   12, 0x0a,
     615,   12,   12,   12, 0x0a,
     645,   12,   12,   12, 0x0a,
     673,  667,   12,   12, 0x0a,
     705,   12,   12,   12, 0x0a,
     735,   12,   12,   12, 0x0a,
     763,   12,   12,   12, 0x0a,
     781,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WClusterDlg[] = {
    "WClusterDlg\0\0on_leftBtn()\0on_rightBtn()\0"
    "on_leftOneBtn()\0on_rightOneBtn()\0"
    "on_clusterMoreBtn()\0on_nodeMoreBtn()\0"
    "index\0on_cbCtNameChange(int)\0"
    "on_getCtCircle()\0nodeId\0"
    "on_getCtNodeStage(quint8)\0"
    "on_mouseSelectCtNode(quint32)\0"
    "on_cbCtNodeNameChange(int)\0"
    "on_offsetChange(quint32)\0on_appBtn()\0"
    "on_readBtn()\0on_cbCheck()\0"
    "on_treeViewClick(QModelIndex)\0"
    "on_addCTBtn()\0on_delCTBtn()\0on_readCTBtn()\0"
    "on_appCTBtn()\0str\0on_ctNameChange(QString)\0"
    "on_ctDomainIdChange(QString)\0"
    "on_ctEnableChange(int)\0on_sbNodeDifChange(int)\0"
    "on_ctPatternDelBtn()\0on_ctPatternReadBtn()\0"
    "on_ctPatternAppBtn()\0on_ctPatternNoChange(int)\0"
    "on_ctPatternCircle(int)\0"
    "on_ctPatternStagePattern(int)\0"
    "on_ctPatternCtlMode()\0value\0"
    "on_ctPatternSbOffsetChange(int)\0"
    "on_ctPatternLeOffset(QString)\0"
    "on_ctPatternLeCoor(QString)\0"
    "on_rcvCtPattern()\0on_ctNameModelChange()\0"
};

void WClusterDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WClusterDlg *_t = static_cast<WClusterDlg *>(_o);
        switch (_id) {
        case 0: _t->on_leftBtn(); break;
        case 1: _t->on_rightBtn(); break;
        case 2: _t->on_leftOneBtn(); break;
        case 3: _t->on_rightOneBtn(); break;
        case 4: _t->on_clusterMoreBtn(); break;
        case 5: _t->on_nodeMoreBtn(); break;
        case 6: _t->on_cbCtNameChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_getCtCircle(); break;
        case 8: _t->on_getCtNodeStage((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 9: _t->on_mouseSelectCtNode((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 10: _t->on_cbCtNodeNameChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_offsetChange((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 12: _t->on_appBtn(); break;
        case 13: _t->on_readBtn(); break;
        case 14: _t->on_cbCheck(); break;
        case 15: _t->on_treeViewClick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 16: _t->on_addCTBtn(); break;
        case 17: _t->on_delCTBtn(); break;
        case 18: _t->on_readCTBtn(); break;
        case 19: _t->on_appCTBtn(); break;
        case 20: _t->on_ctNameChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->on_ctDomainIdChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->on_ctEnableChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_sbNodeDifChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_ctPatternDelBtn(); break;
        case 25: _t->on_ctPatternReadBtn(); break;
        case 26: _t->on_ctPatternAppBtn(); break;
        case 27: _t->on_ctPatternNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_ctPatternCircle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_ctPatternStagePattern((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_ctPatternCtlMode(); break;
        case 31: _t->on_ctPatternSbOffsetChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_ctPatternLeOffset((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->on_ctPatternLeCoor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 34: _t->on_rcvCtPattern(); break;
        case 35: _t->on_ctNameModelChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WClusterDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WClusterDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WClusterDlg,
      qt_meta_data_WClusterDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WClusterDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WClusterDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WClusterDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WClusterDlg))
        return static_cast<void*>(const_cast< WClusterDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int WClusterDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
