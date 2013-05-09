/****************************************************************************
** Meta object code from reading C++ file 'qtweetstatusshow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetstatusshow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetstatusshow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetStatusShow_t {
    QByteArrayData data[11];
    char stringdata[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetStatusShow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetStatusShow_t qt_meta_stringdata_QTweetStatusShow = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 12),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 12),
QT_MOC_LITERAL(4, 44, 6),
QT_MOC_LITERAL(5, 51, 17),
QT_MOC_LITERAL(6, 69, 7),
QT_MOC_LITERAL(7, 77, 7),
QT_MOC_LITERAL(8, 85, 8),
QT_MOC_LITERAL(9, 94, 16),
QT_MOC_LITERAL(10, 111, 15)
    },
    "QTweetStatusShow\0parsedStatus\0\0"
    "QTweetStatus\0status\0parseJsonFinished\0"
    "jsonDoc\0tweetid\0trimUser\0includeMyRetweet\0"
    "includeEntities\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetStatusShow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       4,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x09,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    6,

 // properties: name, type, flags
       7, QMetaType::LongLong, 0x00095103,
       8, QMetaType::Bool, 0x00095103,
       9, QMetaType::Bool, 0x00095103,
      10, QMetaType::Bool, 0x00095103,

       0        // eod
};

void QTweetStatusShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetStatusShow *_t = static_cast<QTweetStatusShow *>(_o);
        switch (_id) {
        case 0: _t->parsedStatus((*reinterpret_cast< const QTweetStatus(*)>(_a[1]))); break;
        case 1: _t->parseJsonFinished((*reinterpret_cast< const QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTweetStatusShow::*_t)(const QTweetStatus & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetStatusShow::parsedStatus)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QTweetStatusShow::staticMetaObject = {
    { &QTweetNetBase::staticMetaObject, qt_meta_stringdata_QTweetStatusShow.data,
      qt_meta_data_QTweetStatusShow,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetStatusShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetStatusShow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetStatusShow.stringdata))
        return static_cast<void*>(const_cast< QTweetStatusShow*>(this));
    return QTweetNetBase::qt_metacast(_clname);
}

int QTweetStatusShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTweetNetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint64*>(_v) = tweetid(); break;
        case 1: *reinterpret_cast< bool*>(_v) = isTrimUser(); break;
        case 2: *reinterpret_cast< bool*>(_v) = includeMyRetweet(); break;
        case 3: *reinterpret_cast< bool*>(_v) = includeEntities(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setTweetid(*reinterpret_cast< qint64*>(_v)); break;
        case 1: setTrimUser(*reinterpret_cast< bool*>(_v)); break;
        case 2: setIncludeMyRetweet(*reinterpret_cast< bool*>(_v)); break;
        case 3: setIncludeEntities(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QTweetStatusShow::parsedStatus(const QTweetStatus & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
