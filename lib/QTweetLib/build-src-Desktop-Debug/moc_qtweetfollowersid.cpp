/****************************************************************************
** Meta object code from reading C++ file 'qtweetfollowersid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetfollowersid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetfollowersid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetFollowersID_t {
    QByteArrayData data[9];
    char stringdata[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetFollowersID_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetFollowersID_t qt_meta_stringdata_QTweetFollowersID = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 9),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 13),
QT_MOC_LITERAL(4, 43, 3),
QT_MOC_LITERAL(5, 47, 10),
QT_MOC_LITERAL(6, 58, 10),
QT_MOC_LITERAL(7, 69, 17),
QT_MOC_LITERAL(8, 87, 7)
    },
    "QTweetFollowersID\0parsedIDs\0\0QList<qint64>\0"
    "ids\0nextCursor\0prevCursor\0parseJsonFinished\0"
    "jsonDoc\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetFollowersID[] = {

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
       1,    3,   24,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       7,    1,   31,    2, 0x09,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    8,

       0        // eod
};

void QTweetFollowersID::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetFollowersID *_t = static_cast<QTweetFollowersID *>(_o);
        switch (_id) {
        case 0: _t->parsedIDs((*reinterpret_cast< const QList<qint64>(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->parseJsonFinished((*reinterpret_cast< const QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            typedef void (QTweetFollowersID::*_t)(const QList<qint64> & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetFollowersID::parsedIDs)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QTweetFollowersID::staticMetaObject = {
    { &QTweetNetBase::staticMetaObject, qt_meta_stringdata_QTweetFollowersID.data,
      qt_meta_data_QTweetFollowersID,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetFollowersID::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetFollowersID::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetFollowersID.stringdata))
        return static_cast<void*>(const_cast< QTweetFollowersID*>(this));
    return QTweetNetBase::qt_metacast(_clname);
}

int QTweetFollowersID::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QTweetFollowersID::parsedIDs(const QList<qint64> & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
