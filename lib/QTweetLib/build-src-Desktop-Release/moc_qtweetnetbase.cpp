/****************************************************************************
** Meta object code from reading C++ file 'qtweetnetbase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetnetbase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetnetbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetNetBase_t {
    QByteArrayData data[13];
    char stringdata[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetNetBase_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetNetBase_t qt_meta_stringdata_QTweetNetBase = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 8),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 8),
QT_MOC_LITERAL(4, 33, 5),
QT_MOC_LITERAL(5, 39, 24),
QT_MOC_LITERAL(6, 64, 4),
QT_MOC_LITERAL(7, 69, 8),
QT_MOC_LITERAL(8, 78, 5),
QT_MOC_LITERAL(9, 84, 12),
QT_MOC_LITERAL(10, 97, 13),
QT_MOC_LITERAL(11, 111, 11),
QT_MOC_LITERAL(12, 123, 13)
    },
    "QTweetNetBase\0finished\0\0response\0error\0"
    "QTweetNetBase::ErrorCode\0code\0errorMsg\0"
    "reply\0oauthTwitter\0OAuthTwitter*\0"
    "jsonParsing\0authenticaion\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetNetBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x05,
       4,    2,   32,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    0,   37,    2, 0x09,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString,    6,    7,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       9, 0x80000000 | 10, 0x0009500b,
      11, QMetaType::Bool, 0x00095003,
      12, QMetaType::Bool, 0x00095003,

       0        // eod
};

void QTweetNetBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetNetBase *_t = static_cast<QTweetNetBase *>(_o);
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< QTweetNetBase::ErrorCode(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->reply(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTweetNetBase::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetNetBase::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (QTweetNetBase::*_t)(QTweetNetBase::ErrorCode , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetNetBase::error)) {
                *result = 1;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< OAuthTwitter* >(); break;
        }
    }

}

const QMetaObject QTweetNetBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QTweetNetBase.data,
      qt_meta_data_QTweetNetBase,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetNetBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetNetBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetNetBase.stringdata))
        return static_cast<void*>(const_cast< QTweetNetBase*>(this));
    return QObject::qt_metacast(_clname);
}

int QTweetNetBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< OAuthTwitter**>(_v) = oauthTwitter(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isJsonParsingEnabled(); break;
        case 2: *reinterpret_cast< bool*>(_v) = isAuthenticationEnabled(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setOAuthTwitter(*reinterpret_cast< OAuthTwitter**>(_v)); break;
        case 1: setJsonParsingEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 2: setAuthenticationEnabled(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QTweetNetBase::finished(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QTweetNetBase::error(QTweetNetBase::ErrorCode _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
