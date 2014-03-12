/****************************************************************************
** Meta object code from reading C++ file 'wtimebasedlg.h'
**
** Created: Fri Sep 21 18:10:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wtimebasedlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wtimebasedlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WTimeBaseDlg[] = {

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
      14,   13,   13,   13, 0x0a,
      38,   13,   13,   13, 0x0a,
      60,   54,   13,   13, 0x0a,
      78,   54,   13,   13, 0x0a,
     113,   54,   13,   13, 0x0a,
     143,   13,   13,   13, 0x0a,
     159,   13,   13,   13, 0x0a,
     172,   13,   13,   13, 0x0a,
     185,   13,   13,   13, 0x0a,
     197,   13,   13,   13, 0x0a,
     210,   13,   13,   13, 0x0a,
     222,   13,   13,   13, 0x0a,
     234,   13,   13,   13, 0x0a,
     247,   13,   13,   13, 0x0a,
     260,   13,   13,   13, 0x0a,
     277,   13,   13,   13, 0x0a,
     294,   13,   13,   13, 0x0a,
     309,   13,   13,   13, 0x0a,
     325,   13,   13,   13, 0x0a,
     340,   13,   13,   13, 0x0a,
     355,   13,   13,   13, 0x0a,
     381,  371,   13,   13, 0x0a,
     415,  371,   13,   13, 0x0a,
     449,   13,   13,   13, 0x0a,
     478,   13,   13,   13, 0x0a,
     508,   13,   13,   13, 0x0a,
     540,   13,   13,   13, 0x0a,
     569,  567,   13,   13, 0x0a,
     591,   13,   13,   13, 0x0a,
     602,  567,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WTimeBaseDlg[] = {
    "WTimeBaseDlg\0\0on_changeSpecialModel()\0"
    "on_dataChange()\0index\0on_tabChange(int)\0"
    "on_clickTimebaseIndex(QModelIndex)\0"
    "on_clickSchIndex(QModelIndex)\0"
    "showSumSelect()\0showSumBtn()\0showSeason()\0"
    "on_addBtn()\0on_editBtn()\0on_delBtn()\0"
    "on_appBtn()\0on_readBtn()\0on_moreBtn()\0"
    "on_addEventBtn()\0on_delEventBtn()\0"
    "on_addSchBtn()\0on_editSchBtn()\0"
    "on_delSchBtn()\0on_appSchBtn()\0"
    "on_readSchBtn()\0para1,len\0"
    "on_rcvTimeBaseResponse(char*,int)\0"
    "on_rcvScheduleResponse(char*,int)\0"
    "on_tbViewSelect(QModelIndex)\0"
    "on_schViewSelect(QModelIndex)\0"
    "on_eventViewSelect(QModelIndex)\0"
    "on_updatePatternDeligate()\0b\0"
    "on_clusterClick(bool)\0on_ctBtn()\0"
    "on_cbAllDay(bool)\0"
};

void WTimeBaseDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WTimeBaseDlg *_t = static_cast<WTimeBaseDlg *>(_o);
        switch (_id) {
        case 0: _t->on_changeSpecialModel(); break;
        case 1: _t->on_dataChange(); break;
        case 2: _t->on_tabChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_clickTimebaseIndex((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_clickSchIndex((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 5: _t->showSumSelect(); break;
        case 6: _t->showSumBtn(); break;
        case 7: _t->showSeason(); break;
        case 8: _t->on_addBtn(); break;
        case 9: _t->on_editBtn(); break;
        case 10: _t->on_delBtn(); break;
        case 11: _t->on_appBtn(); break;
        case 12: _t->on_readBtn(); break;
        case 13: _t->on_moreBtn(); break;
        case 14: _t->on_addEventBtn(); break;
        case 15: _t->on_delEventBtn(); break;
        case 16: _t->on_addSchBtn(); break;
        case 17: _t->on_editSchBtn(); break;
        case 18: _t->on_delSchBtn(); break;
        case 19: _t->on_appSchBtn(); break;
        case 20: _t->on_readSchBtn(); break;
        case 21: _t->on_rcvTimeBaseResponse((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->on_rcvScheduleResponse((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 23: _t->on_tbViewSelect((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 24: _t->on_schViewSelect((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 25: _t->on_eventViewSelect((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 26: _t->on_updatePatternDeligate(); break;
        case 27: _t->on_clusterClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_ctBtn(); break;
        case 29: _t->on_cbAllDay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WTimeBaseDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WTimeBaseDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WTimeBaseDlg,
      qt_meta_data_WTimeBaseDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WTimeBaseDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WTimeBaseDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WTimeBaseDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WTimeBaseDlg))
        return static_cast<void*>(const_cast< WTimeBaseDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int WTimeBaseDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
