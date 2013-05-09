/****************************************************************************
** Meta object code from reading C++ file 'qtweetdirectmessagenew.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/qtweetdirectmessagenew.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtweetdirectmessagenew.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QTweetDirectMessageNew_t {
    QByteArrayData data[7];
    char stringdata[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QTweetDirectMessageNew_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QTweetDirectMessageNew_t qt_meta_stringdata_QTweetDirectMessageNew = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 19),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 14),
QT_MOC_LITERAL(4, 59, 7),
QT_MOC_LITERAL(5, 67, 17),
QT_MOC_LITERAL(6, 85, 7)
    },
    "QTweetDirectMessageNew\0parsedDirectMessage\0"
    "\0QTweetDMStatus\0message\0parseJsonFinished\0"
    "jsonDoc\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTweetDirectMessageNew[] = {

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

void QTweetDirectMessageNew::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTweetDirectMessageNew *_t = static_cast<QTweetDirectMessageNew *>(_o);
        switch (_id) {
        case 0: _t->parsedDirectMessage((*reinterpret_cast< const QTweetDMStatus(*)>(_a[1]))); break;
        case 1: _t->parseJsonFinished((*reinterpret_cast< const QJsonDocument(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QTweetDirectMessageNew::*_t)(const QTweetDMStatus & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QTweetDirectMessageNew::parsedDirectMessage)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QTweetDirectMessageNew::staticMetaObject = {
    { &QTweetNetBase::staticMetaObject, qt_meta_stringdata_QTweetDirectMessageNew.data,
      qt_meta_data_QTweetDirectMessageNew,  qt_static_metacall, 0, 0}
};


const QMetaObject *QTweetDirectMessageNew::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTweetDirectMessageNew::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTweetDirectMessageNew.stringdata))
        return static_cast<void*>(const_cast< QTweetDirectMessageNew*>(this));
    return QTweetNetBase::qt_metacast(_clname);
}

int QTweetDirectMessageNew::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QTweetDirectMessageNew::parsedDirectMessage(const QTweetDMStatus & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
