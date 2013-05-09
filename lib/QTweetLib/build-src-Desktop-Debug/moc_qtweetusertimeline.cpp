/****************************************************************************
** Meta object code from reading C++ file 'qtweetusertimeline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetusertimeline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetusertimeline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetUserTimeline_t {
    QByteArrayData data[18];
    char stringdata[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetUserTimeline_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetUserTimeline_t qt_meta_stringdata_QTweetUserTimeline = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 14),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 19),
QT_MOC_LITERAL(4, 55, 8),
QT_MOC_LITERAL(5, 64, 17),
QT_MOC_LITERAL(6, 82, 7),
QT_MOC_LITERAL(7, 90, 6),
QT_MOC_LITERAL(8, 97, 10),
QT_MOC_LITERAL(9, 108, 7),
QT_MOC_LITERAL(10, 116, 5),
QT_MOC_LITERAL(11, 122, 5),
QT_MOC_LITERAL(12, 128, 4),
QT_MOC_LITERAL(13, 133, 8),
QT_MOC_LITERAL(14, 142, 15),
QT_MOC_LITERAL(15, 158, 10),
QT_MOC_LITERAL(16, 169, 14),
QT_MOC_LITERAL(17, 184, 18)
    },
    "QTweetUserTimeline\0parsedStatuses\0\0"
    "QList<QTweetStatus>\0statuses\0"
    "parseJsonFinished\0jsonDoc\0userID\0"
    "screenName\0sinceID\0maxID\0count\0page\0"
    "trimUser\0includeEntities\0includeRts\0"
    "excludeReplies\0contributorDetails\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetUserTimeline[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
      11,   30, // properties
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
       8, QMetaType::QString, 0x00095103,
       9, QMetaType::LongLong, 0x00095103,
      10, QMetaType::LongLong, 0x00095103,
      11, QMetaType::Int, 0x00095103,
      12, QMetaType::Int, 0x00095103,
      13, QMetaType::Bool, 0x00095103,
      14, QMetaType::Bool, 0x00095103,
      15, QMetaType::Bool, 0x00095103,
      16, QMetaType::Bool, 0x00095103,
      17, QMetaType::Bool, 0x00095003,

       0        // eod
};

void QTweetUserTimeline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetUserTimeline *_t = static_cast<QTweetUserTimeline *>(_o);
        switch (_id) {
        case 0: _t->parsedStatuses((*reinterpret_cast< const QList<QTweetStatus>(*)>(_a[1]))); break;
        case 1: _t->parseJsonFinished((*reinterpret_cast< const QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTweetUserTimeline::*_t)(const QList<QTweetStatus> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetUserTimeline::parsedStatuses)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QTweetUserTimeline::staticMetaObject = {
    { &QTweetNetBase::staticMetaObject, qt_meta_stringdata_QTweetUserTimeline.data,
      qt_meta_data_QTweetUserTimeline,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetUserTimeline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetUserTimeline::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetUserTimeline.stringdata))
        return static_cast<void*>(const_cast< QTweetUserTimeline*>(this));
    return QTweetNetBase::qt_metacast(_clname);
}

int QTweetUserTimeline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 0: *reinterpret_cast< qint64*>(_v) = userID(); break;
        case 1: *reinterpret_cast< QString*>(_v) = screenName(); break;
        case 2: *reinterpret_cast< qint64*>(_v) = sinceID(); break;
        case 3: *reinterpret_cast< qint64*>(_v) = maxID(); break;
        case 4: *reinterpret_cast< int*>(_v) = count(); break;
        case 5: *reinterpret_cast< int*>(_v) = page(); break;
        case 6: *reinterpret_cast< bool*>(_v) = isTrimUser(); break;
        case 7: *reinterpret_cast< bool*>(_v) = isIncludeEntities(); break;
        case 8: *reinterpret_cast< bool*>(_v) = isIncludeRts(); break;
        case 9: *reinterpret_cast< bool*>(_v) = isExcludeReplies(); break;
        case 10: *reinterpret_cast< bool*>(_v) = isContributorsDetails(); break;
        }
        _id -= 11;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setUserID(*reinterpret_cast< qint64*>(_v)); break;
        case 1: setScreenName(*reinterpret_cast< QString*>(_v)); break;
        case 2: setSinceID(*reinterpret_cast< qint64*>(_v)); break;
        case 3: setMaxID(*reinterpret_cast< qint64*>(_v)); break;
        case 4: setCount(*reinterpret_cast< int*>(_v)); break;
        case 5: setPage(*reinterpret_cast< int*>(_v)); break;
        case 6: setTrimUser(*reinterpret_cast< bool*>(_v)); break;
        case 7: setIncludeEntities(*reinterpret_cast< bool*>(_v)); break;
        case 8: setIncludeRts(*reinterpret_cast< bool*>(_v)); break;
        case 9: setExcludeReplies(*reinterpret_cast< bool*>(_v)); break;
        case 10: setContributorsDetails(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 11;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QTweetUserTimeline::parsedStatuses(const QList<QTweetStatus> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
