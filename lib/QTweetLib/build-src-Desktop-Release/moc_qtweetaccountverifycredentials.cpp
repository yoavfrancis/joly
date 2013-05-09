/****************************************************************************
** Meta object code from reading C++ file 'qtweetaccountverifycredentials.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetaccountverifycredentials.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetaccountverifycredentials.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetAccountVerifyCredentials_t {
    QByteArrayData data[7];
    char stringdata[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetAccountVerifyCredentials_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetAccountVerifyCredentials_t qt_meta_stringdata_QTweetAccountVerifyCredentials = {
    {
QT_MOC_LITERAL(0, 0, 30),
QT_MOC_LITERAL(1, 31, 10),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 10),
QT_MOC_LITERAL(4, 54, 4),
QT_MOC_LITERAL(5, 59, 17),
QT_MOC_LITERAL(6, 77, 7)
    },
    "QTweetAccountVerifyCredentials\0"
    "parsedUser\0\0QTweetUser\0user\0"
    "parseJsonFinished\0jsonDoc\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetAccountVerifyCredentials[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
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

       0        // eod
};

void QTweetAccountVerifyCredentials::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetAccountVerifyCredentials *_t = static_cast<QTweetAccountVerifyCredentials *>(_o);
        switch (_id) {
        case 0: _t->parsedUser((*reinterpret_cast< const QTweetUser(*)>(_a[1]))); break;
        case 1: _t->parseJsonFinished((*reinterpret_cast< const QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTweetAccountVerifyCredentials::*_t)(const QTweetUser & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetAccountVerifyCredentials::parsedUser)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QTweetAccountVerifyCredentials::staticMetaObject = {
    { &QTweetNetBase::staticMetaObject, qt_meta_stringdata_QTweetAccountVerifyCredentials.data,
      qt_meta_data_QTweetAccountVerifyCredentials,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetAccountVerifyCredentials::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetAccountVerifyCredentials::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetAccountVerifyCredentials.stringdata))
        return static_cast<void*>(const_cast< QTweetAccountVerifyCredentials*>(this));
    return QTweetNetBase::qt_metacast(_clname);
}

int QTweetAccountVerifyCredentials::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}

// SIGNAL 0
void QTweetAccountVerifyCredentials::parsedUser(const QTweetUser & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
