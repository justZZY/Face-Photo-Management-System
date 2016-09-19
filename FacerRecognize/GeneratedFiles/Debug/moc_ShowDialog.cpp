/****************************************************************************
** Meta object code from reading C++ file 'ShowDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ShowDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShowDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShowDialog_t {
    QByteArrayData data[8];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowDialog_t qt_meta_stringdata_ShowDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ShowDialog"
QT_MOC_LITERAL(1, 11, 7), // "savePic"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 5), // "toStd"
QT_MOC_LITERAL(4, 26, 6), // "toGray"
QT_MOC_LITERAL(5, 33, 7), // "toErode"
QT_MOC_LITERAL(6, 41, 6), // "toBlur"
QT_MOC_LITERAL(7, 48, 7) // "toCanny"

    },
    "ShowDialog\0savePic\0\0toStd\0toGray\0"
    "toErode\0toBlur\0toCanny"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ShowDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowDialog *_t = static_cast<ShowDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->savePic(); break;
        case 1: _t->toStd(); break;
        case 2: _t->toGray(); break;
        case 3: _t->toErode(); break;
        case 4: _t->toBlur(); break;
        case 5: _t->toCanny(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ShowDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ShowDialog.data,
      qt_meta_data_ShowDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShowDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShowDialog.stringdata0))
        return static_cast<void*>(const_cast< ShowDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ShowDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
