/****************************************************************************
** Meta object code from reading C++ file 'wphasewidget.h'
**
** Created: Fri Sep 21 18:11:02 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wphasewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wphasewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WPhaseWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      40,   13,   13,   13, 0x0a,
      77,   56,   13,   13, 0x0a,
     114,   13,   13,   13, 0x0a,
     136,   13,   13,   13, 0x0a,
     160,   13,   13,   13, 0x0a,
     185,   13,   13,   13, 0x0a,
     224,  209,   13,   13, 0x0a,
     278,  256,   13,   13, 0x0a,
     327,  256,   13,   13, 0x0a,
     377,   13,   13,   13, 0x0a,
     393,   13,   13,   13, 0x0a,
     415,   13,   13,   13, 0x0a,
     443,   13,   13,   13, 0x0a,
     471,   13,   13,   13, 0x0a,
     499,   13,   13,   13, 0x0a,
     528,   13,   13,   13, 0x0a,
     557,   13,   13,   13, 0x0a,
     587,   13,   13,   13, 0x0a,
     616,   13,   13,   13, 0x0a,
     644,   13,   13,   13, 0x0a,
     668,   13,   13,   13, 0x0a,
     694,   13,   13,   13, 0x0a,
     720,   13,   13,   13, 0x0a,
     748,   13,   13,   13, 0x0a,
     781,   13,   13,   13, 0x0a,
     815,   13,   13,   13, 0x0a,
     851,  846,   13,   13, 0x0a,
     890,  883,   13,   13, 0x0a,
     932,  918,   13,   13, 0x0a,
     968,  962,   13,   13, 0x0a,
     990,  962,   13,   13, 0x0a,
    1013,  962,   13,   13, 0x0a,
    1046, 1040,   13,   13, 0x0a,
    1070,   13,   13,   13, 0x0a,
    1091,   13,   13,   13, 0x0a,
    1105,   13,   13,   13, 0x0a,
    1117,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WPhaseWidget[] = {
    "WPhaseWidget\0\0on_loadClearPhase(quint8)\0"
    "on_chlBtnMore()\0chlId,bClick,phaseId\0"
    "on_mouseClickChl(quint8,bool,quint8)\0"
    "on_chlCbNoChange(int)\0on_chlCbTypeChange(int)\0"
    "on_chlCbLightChange(int)\0"
    "on_chlCbModeChange(int)\0phaseId,bClick\0"
    "on_mouseClickPhase(quint8,bool)\0"
    "contId,bClick,phaseId\0"
    "on_mouseClickComContentPhase(quint8,bool,quint8)\0"
    "on_mouseClickLoadContentPhase(quint8,bool,quint8)\0"
    "on_comBtnMore()\0on_comCbIdChange(int)\0"
    "on_comSbPedGreenChange(int)\0"
    "on_comSbPedCleanChange(int)\0"
    "on_comSbMinGreenChange(int)\0"
    "on_comSbUnitDelayChange(int)\0"
    "on_comSbMaxGreen1Change(int)\0"
    "on_comSbFlashGreenChange(int)\0"
    "on_comSbMaxGreen2Change(int)\0"
    "on_comSbFixGreenChange(int)\0"
    "on_comCbTypeChange(int)\0"
    "on_comCbOptionChange(int)\0"
    "on_overlapCbIdChange(int)\0"
    "on_overlapCbTypeChange(int)\0"
    "on_overlapSbTailGreenChange(int)\0"
    "on_overlapSbTailYellowChange(int)\0"
    "on_overlapSbTailRedChange(int)\0id,b\0"
    "on_dirClearContent(quint8,bool)\0loadNo\0"
    "on_mouseDoubleClick(quint8)\0loadNo,bClick\0"
    "on_mouseClickDir(quint8,bool)\0index\0"
    "on_dirCbNoChange(int)\0on_dirCbComChange(int)\0"
    "on_dirCbOverlapChange(int)\0value\0"
    "on_dirSbLoadChange(int)\0on_dirCbVoidChange()\0"
    "on_rcvPhase()\0on_btnApp()\0on_btnRead()\0"
};

void WPhaseWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WPhaseWidget *_t = static_cast<WPhaseWidget *>(_o);
        switch (_id) {
        case 0: _t->on_loadClearPhase((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->on_chlBtnMore(); break;
        case 2: _t->on_mouseClickChl((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 3: _t->on_chlCbNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_chlCbTypeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_chlCbLightChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_chlCbModeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_mouseClickPhase((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->on_mouseClickComContentPhase((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 9: _t->on_mouseClickLoadContentPhase((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 10: _t->on_comBtnMore(); break;
        case 11: _t->on_comCbIdChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_comSbPedGreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_comSbPedCleanChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_comSbMinGreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_comSbUnitDelayChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_comSbMaxGreen1Change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_comSbFlashGreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_comSbMaxGreen2Change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_comSbFixGreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_comCbTypeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_comCbOptionChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->on_overlapCbIdChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_overlapCbTypeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_overlapSbTailGreenChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_overlapSbTailYellowChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_overlapSbTailRedChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_dirClearContent((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 28: _t->on_mouseDoubleClick((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 29: _t->on_mouseClickDir((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 30: _t->on_dirCbNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->on_dirCbComChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_dirCbOverlapChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_dirSbLoadChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->on_dirCbVoidChange(); break;
        case 35: _t->on_rcvPhase(); break;
        case 36: _t->on_btnApp(); break;
        case 37: _t->on_btnRead(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WPhaseWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WPhaseWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WPhaseWidget,
      qt_meta_data_WPhaseWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WPhaseWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WPhaseWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WPhaseWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WPhaseWidget))
        return static_cast<void*>(const_cast< WPhaseWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int WPhaseWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
