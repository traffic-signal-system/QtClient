/****************************************************************************
** Meta object code from reading C++ file 'wstagewidget.h'
**
** Created: Fri Sep 21 18:11:07 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wstagewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wstagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WStageWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      34,   13,   13,   13, 0x0a,
      60,   13,   13,   13, 0x0a,
      90,   13,   13,   13, 0x0a,
     121,   13,   13,   13, 0x0a,
     151,   13,   13,   13, 0x0a,
     185,   13,   13,   13, 0x0a,
     204,   13,   13,   13, 0x0a,
     223,   13,   13,   13, 0x0a,
     243,   13,   13,   13, 0x0a,
     261,   13,   13,   13, 0x0a,
     285,   13,   13,   13, 0x0a,
     311,   13,   13,   13, 0x0a,
     356,  339,   13,   13, 0x0a,
     404,  398,   13,   13, 0x0a,
     432,   13,   13,   13, 0x0a,
     450,   13,   13,   13, 0x0a,
     467,   13,   13,   13, 0x0a,
     481,   13,   13,   13, 0x0a,
     504,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WStageWidget[] = {
    "WStageWidget\0\0on_patternBtnMore()\0"
    "on_patternSbNoChange(int)\0"
    "on_patternSbCircleChange(int)\0"
    "on_patternSbStageNoChange(int)\0"
    "on_patternSbOffsetChange(int)\0"
    "on_patternSbCoordinateChange(int)\0"
    "on_patternBtnDel()\0on_patternBtnApp()\0"
    "on_patternBtnRead()\0on_stageBtnMore()\0"
    "on_stageSbNoChange(int)\0"
    "on_stageSbTimeChange(int)\0"
    "on_stageCbOptionChange(int)\0"
    "green,yellow,red\0"
    "on_stageColorChange(quint8,quint8,quint8)\0"
    "index\0on_stageIndexChange(quint8)\0"
    "on_btnReadStage()\0on_btnAppStage()\0"
    "on_rcvPhase()\0on_rcvStageTimeTable()\0"
    "on_rcvTimePatternTable()\0"
};

void WStageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WStageWidget *_t = static_cast<WStageWidget *>(_o);
        switch (_id) {
        case 0: _t->on_patternBtnMore(); break;
        case 1: _t->on_patternSbNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_patternSbCircleChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_patternSbStageNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_patternSbOffsetChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_patternSbCoordinateChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_patternBtnDel(); break;
        case 7: _t->on_patternBtnApp(); break;
        case 8: _t->on_patternBtnRead(); break;
        case 9: _t->on_stageBtnMore(); break;
        case 10: _t->on_stageSbNoChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_stageSbTimeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_stageCbOptionChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_stageColorChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 14: _t->on_stageIndexChange((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->on_btnReadStage(); break;
        case 16: _t->on_btnAppStage(); break;
        case 17: _t->on_rcvPhase(); break;
        case 18: _t->on_rcvStageTimeTable(); break;
        case 19: _t->on_rcvTimePatternTable(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WStageWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WStageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WStageWidget,
      qt_meta_data_WStageWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WStageWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WStageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WStageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WStageWidget))
        return static_cast<void*>(const_cast< WStageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int WStageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
