/****************************************************************************
** Meta object code from reading C++ file 'FacerRecognize.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FacerRecognize.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FacerRecognize.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FacerRecognize_t {
    QByteArrayData data[14];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FacerRecognize_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FacerRecognize_t qt_meta_stringdata_FacerRecognize = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FacerRecognize"
QT_MOC_LITERAL(1, 15, 17), // "openFileOperation"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "setPathsToRight"
QT_MOC_LITERAL(4, 50, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 67, 16), // "setPathsToDialog"
QT_MOC_LITERAL(6, 84, 15), // "setPathToDialog"
QT_MOC_LITERAL(7, 100, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 117, 14), // "changePicLabel"
QT_MOC_LITERAL(9, 132, 15), // "deletePicfromDB"
QT_MOC_LITERAL(10, 148, 13), // "signalManager"
QT_MOC_LITERAL(11, 162, 15), // "createRightMenu"
QT_MOC_LITERAL(12, 178, 8), // "clearAll"
QT_MOC_LITERAL(13, 187, 9) // "addSample"

    },
    "FacerRecognize\0openFileOperation\0\0"
    "setPathsToRight\0QTreeWidgetItem*\0"
    "setPathsToDialog\0setPathToDialog\0"
    "QListWidgetItem*\0changePicLabel\0"
    "deletePicfromDB\0signalManager\0"
    "createRightMenu\0clearAll\0addSample"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FacerRecognize[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    2,   65,    2, 0x09 /* Protected */,
       5,    2,   70,    2, 0x09 /* Protected */,
       6,    1,   75,    2, 0x09 /* Protected */,
       8,    0,   78,    2, 0x09 /* Protected */,
       9,    0,   79,    2, 0x09 /* Protected */,
      10,    1,   80,    2, 0x09 /* Protected */,
      11,    0,   83,    2, 0x09 /* Protected */,
      12,    0,   84,    2, 0x09 /* Protected */,
      13,    0,   85,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FacerRecognize::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FacerRecognize *_t = static_cast<FacerRecognize *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFileOperation(); break;
        case 1: _t->setPathsToRight((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->setPathsToDialog((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setPathToDialog((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->changePicLabel(); break;
        case 5: _t->deletePicfromDB(); break;
        case 6: _t->signalManager((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->createRightMenu(); break;
        case 8: _t->clearAll(); break;
        case 9: _t->addSample(); break;
        default: ;
        }
    }
}

const QMetaObject FacerRecognize::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FacerRecognize.data,
      qt_meta_data_FacerRecognize,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FacerRecognize::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FacerRecognize::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FacerRecognize.stringdata0))
        return static_cast<void*>(const_cast< FacerRecognize*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FacerRecognize::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
