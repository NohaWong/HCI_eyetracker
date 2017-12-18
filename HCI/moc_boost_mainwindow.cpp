/****************************************************************************
** Meta object code from reading C++ file 'boost_mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "boost_mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'boost_mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_boost_MainWindow_t {
    QByteArrayData data[7];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_boost_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_boost_MainWindow_t qt_meta_stringdata_boost_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "boost_MainWindow"
QT_MOC_LITERAL(1, 17, 18), // "primary_edges_only"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 19), // "internal_edges_only"
QT_MOC_LITERAL(4, 57, 6), // "browse"
QT_MOC_LITERAL(5, 64, 5), // "build"
QT_MOC_LITERAL(6, 70, 9) // "print_scr"

    },
    "boost_MainWindow\0primary_edges_only\0"
    "\0internal_edges_only\0browse\0build\0"
    "print_scr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_boost_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void boost_MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        boost_MainWindow *_t = static_cast<boost_MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->primary_edges_only(); break;
        case 1: _t->internal_edges_only(); break;
        case 2: _t->browse(); break;
        case 3: _t->build(); break;
        case 4: _t->print_scr(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject boost_MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_boost_MainWindow.data,
      qt_meta_data_boost_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *boost_MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *boost_MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_boost_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< boost_MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int boost_MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
