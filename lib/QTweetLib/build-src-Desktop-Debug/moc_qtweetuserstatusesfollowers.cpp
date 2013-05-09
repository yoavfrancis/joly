/****************************************************************************
** Meta object code from reading C++ file 'qtweetuserstatusesfollowers.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetuserstatusesfollowers.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetuserstatusesfollowers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetUserStatusesFollowers_t {
    QByteArrayData data[9];
    char stringdata[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetUserStatusesFollowers_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetUserStatusesFollowers_t qt_meta_stringdata_QTweetUserStatusesFollowers = {
    {
QT_MOC_LITERAL(0, 0, 27),
QT_MOC_LITERAL(1, 28, 19),
QT_MOC_LITERAL(2, 48, 0),
QT_MOC_LITERAL(3, 49, 17),
QT_MOC_LITERAL(4, 67, 13),
QT_MOC_LITERAL(5, 81, 10),
QT_MOC_LITERAL(6, 92, 10),
QT_MOC_LITERAL(7, 103, 17),
QT_MOC_LITERAL(8, 121, 7)
    },
    "QTweetUserStatusesFollowers\0"
    "parsedFollowersList\0\0QList<QTweetUser>\0"
    "followersList\0nextCursor\0prevCursor\0"
    "parseJsonFinished\0jsonDoc\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetUserStatusesFollowers[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x05,
       1,    2,   41,    2, 0x25,
       1,    1,   46,    2, 0x25,

 // slots: name, argc, parameters, tag, flags
       7,    1,   49,    2, 0x09,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    8,

       0        // eod
};

void QTweetUserStatusesFollowers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetUserStatusesFollowers *_t = static_cast<QTweetUserStatusesFollowers *>(_o);
        switch (_id) {
        case 0: _t->parsedFollowersList((*reinterpret_cast< const QList<QTweetUser>(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->parsedFollowersList((*reinterpret_cast< const QList<QTweetUser>(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->parsedFollowersList((*reinterpret_cast< const QList<QTweetUser>(*)>(_a[1]))); break;
        case 3: _t->parseJsonFinished((*reinterpret_cast< const QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTweetUserStatusesFollowers::*_t)(const QList<QTweetUser> & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserStatusesFollowers::parsedFollowersList)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QTweetUserStatusesFollowers::staticMetaObject = {
    { &QTweetNetBase::staticMetaObject, qt_meta_stringdata_QTweetUserStatusesFollowers.data,
      qt_meta_data_QTweetUserStatusesFollowers,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetUserStatusesFollowers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetUserStatusesFollowers::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetUserStatusesFollowers.stringdata))
        return static_cast<void*>(const_cast< QTweetUserStatusesFollowers*>(this));
    return QTweetNetBase::qt_metacast(_clname);
}

int QTweetUserStatusesFollowers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTweetNetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QTweetUserStatusesFollowers::parsedFollowersList(const QList<QTweetUser> & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
