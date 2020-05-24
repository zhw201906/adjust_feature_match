/****************************************************************************
** Meta object code from reading C++ file 'MyDisplayLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MyDisplayLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyDisplayLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyDisplayLabel_t {
    QByteArrayData data[5];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyDisplayLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyDisplayLabel_t qt_meta_stringdata_MyDisplayLabel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MyDisplayLabel"
QT_MOC_LITERAL(1, 15, 10), // "mousePress"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9), // "mouseMove"
QT_MOC_LITERAL(4, 37, 12) // "mouseRelease"

    },
    "MyDisplayLabel\0mousePress\0\0mouseMove\0"
    "mouseRelease"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyDisplayLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyDisplayLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyDisplayLabel *_t = static_cast<MyDisplayLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mousePress(); break;
        case 1: _t->mouseMove(); break;
        case 2: _t->mouseRelease(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MyDisplayLabel::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyDisplayLabel::mousePress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyDisplayLabel::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyDisplayLabel::mouseMove)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyDisplayLabel::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyDisplayLabel::mouseRelease)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MyDisplayLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_MyDisplayLabel.data,
      qt_meta_data_MyDisplayLabel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyDisplayLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyDisplayLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyDisplayLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int MyDisplayLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MyDisplayLabel::mousePress()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyDisplayLabel::mouseMove()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyDisplayLabel::mouseRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
