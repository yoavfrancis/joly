/****************************************************************************
** Meta object code from reading C++ file 'qtweetuserstream.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetuserstream.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetuserstream.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetUserStream_t {
    QByteArrayData data[25];
    char stringdata[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetUserStream_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetUserStream_t qt_meta_stringdata_QTweetUserStream = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 6),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 14),
QT_MOC_LITERAL(4, 40, 12),
QT_MOC_LITERAL(5, 53, 6),
QT_MOC_LITERAL(6, 60, 11),
QT_MOC_LITERAL(7, 72, 13),
QT_MOC_LITERAL(8, 86, 7),
QT_MOC_LITERAL(9, 94, 19),
QT_MOC_LITERAL(10, 114, 14),
QT_MOC_LITERAL(11, 129, 13),
QT_MOC_LITERAL(12, 143, 18),
QT_MOC_LITERAL(13, 162, 2),
QT_MOC_LITERAL(14, 165, 6),
QT_MOC_LITERAL(15, 172, 11),
QT_MOC_LITERAL(16, 184, 14),
QT_MOC_LITERAL(17, 199, 13),
QT_MOC_LITERAL(18, 213, 16),
QT_MOC_LITERAL(19, 230, 13),
QT_MOC_LITERAL(20, 244, 14),
QT_MOC_LITERAL(21, 259, 12),
QT_MOC_LITERAL(22, 272, 9),
QT_MOC_LITERAL(23, 282, 16),
QT_MOC_LITERAL(24, 299, 6)
    },
    "QTweetUserStream\0stream\0\0statusesStream\0"
    "QTweetStatus\0status\0friendsList\0"
    "QList<qint64>\0friends\0directMessageStream\0"
    "QTweetDMStatus\0directMessage\0"
    "deleteStatusStream\0id\0userid\0reconnected\0"
    "failureConnect\0startFetching\0"
    "streamDisconnect\0replyFinished\0"
    "replyReadyRead\0replyTimeout\0sslErrors\0"
    "QList<QSslError>\0errors\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetUserStream[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x05,
       3,    1,   82,    2, 0x05,
       6,    1,   85,    2, 0x05,
       9,    1,   88,    2, 0x05,
      12,    2,   91,    2, 0x05,
      15,    0,   96,    2, 0x05,
      16,    0,   97,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      17,    0,   98,    2, 0x0a,
      18,    0,   99,    2, 0x0a,
      19,    0,  100,    2, 0x08,
      20,    0,  101,    2, 0x08,
      21,    0,  102,    2, 0x08,
      22,    1,  103,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   13,   14,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,

       0        // eod
};

void QTweetUserStream::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetUserStream *_t = static_cast<QTweetUserStream *>(_o);
        switch (_id) {
        case 0: _t->stream((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->statusesStream((*reinterpret_cast< const QTweetStatus(*)>(_a[1]))); break;
        case 2: _t->friendsList((*reinterpret_cast< const QList<qint64>(*)>(_a[1]))); break;
        case 3: _t->directMessageStream((*reinterpret_cast< const QTweetDMStatus(*)>(_a[1]))); break;
        case 4: _t->deleteStatusStream((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: _t->reconnected(); break;
        case 6: _t->failureConnect(); break;
        case 7: _t->startFetching(); break;
        case 8: _t->streamDisconnect(); break;
        case 9: _t->replyFinished(); break;
        case 10: _t->replyReadyRead(); break;
        case 11: _t->replyTimeout(); break;
        case 12: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<qint64> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTweetUserStream::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStream::stream)) {
                *result = 0;
            }
        }
        {
            typedef void (QTweetUserStream::*_t)(const QTweetStatus & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStream::statusesStream)) {
                *result = 1;
            }
        }
        {
            typedef void (QTweetUserStream::*_t)(const QList<qint64> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStream::friendsList)) {
                *result = 2;
            }
        }
        {
            typedef void (QTweetUserStream::*_t)(const QTweetDMStatus & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStream::directMessageStream)) {
                *result = 3;
            }
        }
        {
            typedef void (QTweetUserStream::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStream::deleteStatusStream)) {
                *result = 4;
            }
        }
        {
            typedef void (QTweetUserStream::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStream::reconnected)) {
                *result = 5;
            }
        }
        {
            typedef void (QTweetUserStream::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStream::failureConnect)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject QTweetUserStream::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QTweetUserStream.data,
      qt_meta_data_QTweetUserStream,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetUserStream::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetUserStream::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetUserStream.stringdata))
        return static_cast<void*>(const_cast< QTweetUserStream*>(this));
    return QObject::qt_metacast(_clname);
}

int QTweetUserStream::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QTweetUserStream::stream(const QByteArray & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QTweetUserStream::statusesStream(const QTweetStatus & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QTweetUserStream::friendsList(const QList<qint64> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QTweetUserStream::directMessageStream(const QTweetDMStatus & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QTweetUserStream::deleteStatusStream(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QTweetUserStream::reconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QTweetUserStream::failureConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
