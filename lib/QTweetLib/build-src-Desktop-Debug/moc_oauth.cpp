/****************************************************************************
** Meta object code from reading C++ file 'oauth.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/oauth.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oauth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OAuth_t {
    QByteArrayData data[8];
    char stringdata[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_OAuth_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_OAuth_t qt_meta_stringdata_OAuth = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 10),
QT_MOC_LITERAL(2, 17, 16),
QT_MOC_LITERAL(3, 34, 10),
QT_MOC_LITERAL(4, 45, 3),
QT_MOC_LITERAL(5, 49, 4),
QT_MOC_LITERAL(6, 54, 3),
QT_MOC_LITERAL(7, 58, 6)
    },
    "OAuth\0oauthToken\0oauthTokenSecret\0"
    "HttpMethod\0GET\0POST\0PUT\0DELETE\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OAuth[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       1,   20, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QByteArray, 0x00095003,
       2, QMetaType::QByteArray, 0x00095003,

 // enums: name, flags, count, data
       3, 0x0,    4,   24,

 // enum data: key, value
       4, uint(OAuth::GET),
       5, uint(OAuth::POST),
       6, uint(OAuth::PUT),
       7, uint(OAuth::DELETE),

       0        // eod
};

void OAuth::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject OAuth::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OAuth.data,
      qt_meta_data_OAuth,  qt_static_metacall, 0, 0}
};


const QMetaObject *OAuth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OAuth::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OAuth.stringdata))
        return static_cast<void*>(const_cast< OAuth*>(this));
    return QObject::qt_metacast(_clname);
}

int OAuth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QByteArray*>(_v) = oauthToken(); break;
        case 1: *reinterpret_cast< QByteArray*>(_v) = oauthTokenSecret(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setOAuthToken(*reinterpret_cast< QByteArray*>(_v)); break;
        case 1: setOAuthTokenSecret(*reinterpret_cast< QByteArray*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
