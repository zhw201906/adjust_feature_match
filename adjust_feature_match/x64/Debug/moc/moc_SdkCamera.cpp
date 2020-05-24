/****************************************************************************
** Meta object code from reading C++ file 'SdkCamera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SdkCamera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SdkCamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SdkCamera_t {
    QByteArrayData data[9];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SdkCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SdkCamera_t qt_meta_stringdata_SdkCamera = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SdkCamera"
QT_MOC_LITERAL(1, 10, 15), // "signalShowImage"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "uint8_t*"
QT_MOC_LITERAL(4, 36, 12), // "pRgbFrameBuf"
QT_MOC_LITERAL(5, 49, 6), // "nWidth"
QT_MOC_LITERAL(6, 56, 7), // "nHeight"
QT_MOC_LITERAL(7, 64, 8), // "uint64_t"
QT_MOC_LITERAL(8, 73, 12) // "nPixelFormat"

    },
    "SdkCamera\0signalShowImage\0\0uint8_t*\0"
    "pRgbFrameBuf\0nWidth\0nHeight\0uint64_t\0"
    "nPixelFormat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SdkCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Bool, 0x80000000 | 3, QMetaType::Int, QMetaType::Int, 0x80000000 | 7,    4,    5,    6,    8,

       0        // eod
};

void SdkCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SdkCamera *_t = static_cast<SdkCamera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->signalShowImage((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< uint64_t(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef bool (SdkCamera::*_t)(uint8_t * , int , int , uint64_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SdkCamera::signalShowImage)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SdkCamera::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SdkCamera.data,
      qt_meta_data_SdkCamera,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SdkCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SdkCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SdkCamera.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SdkCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
bool SdkCamera::signalShowImage(uint8_t * _t1, int _t2, int _t3, uint64_t _t4)
{
    bool _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
