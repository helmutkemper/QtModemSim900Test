/****************************************************************************
** Meta object code from reading C++ file 'dtmf.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Modem/dtmf.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dtmf.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dtmf_t {
    QByteArrayData data[14];
    char stringdata[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dtmf_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dtmf_t qt_meta_stringdata_Dtmf = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Dtmf"
QT_MOC_LITERAL(1, 5, 14), // "on_pb1_clicked"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "on_pb2_clicked"
QT_MOC_LITERAL(4, 36, 14), // "on_pb3_clicked"
QT_MOC_LITERAL(5, 51, 14), // "on_pb4_clicked"
QT_MOC_LITERAL(6, 66, 14), // "on_pb5_clicked"
QT_MOC_LITERAL(7, 81, 14), // "on_pb6_clicked"
QT_MOC_LITERAL(8, 96, 14), // "on_pb7_clicked"
QT_MOC_LITERAL(9, 111, 14), // "on_pb8_clicked"
QT_MOC_LITERAL(10, 126, 14), // "on_pb9_clicked"
QT_MOC_LITERAL(11, 141, 14), // "on_pbA_clicked"
QT_MOC_LITERAL(12, 156, 14), // "on_pb0_clicked"
QT_MOC_LITERAL(13, 171, 14) // "on_pbB_clicked"

    },
    "Dtmf\0on_pb1_clicked\0\0on_pb2_clicked\0"
    "on_pb3_clicked\0on_pb4_clicked\0"
    "on_pb5_clicked\0on_pb6_clicked\0"
    "on_pb7_clicked\0on_pb8_clicked\0"
    "on_pb9_clicked\0on_pbA_clicked\0"
    "on_pb0_clicked\0on_pbB_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dtmf[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dtmf::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dtmf *_t = static_cast<Dtmf *>(_o);
        switch (_id) {
        case 0: _t->on_pb1_clicked(); break;
        case 1: _t->on_pb2_clicked(); break;
        case 2: _t->on_pb3_clicked(); break;
        case 3: _t->on_pb4_clicked(); break;
        case 4: _t->on_pb5_clicked(); break;
        case 5: _t->on_pb6_clicked(); break;
        case 6: _t->on_pb7_clicked(); break;
        case 7: _t->on_pb8_clicked(); break;
        case 8: _t->on_pb9_clicked(); break;
        case 9: _t->on_pbA_clicked(); break;
        case 10: _t->on_pb0_clicked(); break;
        case 11: _t->on_pbB_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Dtmf::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dtmf.data,
      qt_meta_data_Dtmf,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dtmf::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dtmf::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dtmf.stringdata))
        return static_cast<void*>(const_cast< Dtmf*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dtmf::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
