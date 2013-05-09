/****************************************************************************
** Meta object code from reading C++ file 'oauthtwitter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/oauthtwitter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oauthtwitter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OAuthTwitter_t {
    QByteArrayData data[15];
    char stringdata[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_OAuthTwitter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_OAuthTwitter_t qt_meta_stringdata_OAuthTwitter = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 22),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 20),
QT_MOC_LITERAL(4, 58, 18),
QT_MOC_LITERAL(5, 77, 19),
QT_MOC_LITERAL(6, 97, 18),
QT_MOC_LITERAL(7, 116, 3),
QT_MOC_LITERAL(8, 120, 14),
QT_MOC_LITERAL(9, 135, 8),
QT_MOC_LITERAL(10, 144, 8),
QT_MOC_LITERAL(11, 153, 12),
QT_MOC_LITERAL(12, 166, 21),
QT_MOC_LITERAL(13, 188, 20),
QT_MOC_LITERAL(14, 209, 22)
    },
    "OAuthTwitter\0authorizeXAuthFinished\0"
    "\0authorizePinFinished\0accessTokenGranted\0"
    "authorizeXAuthError\0requestAccessToken\0"
    "pin\0authorizeXAuth\0username\0password\0"
    "authorizePin\0finishedAuthorization\0"
    "networkAccessManager\0QNetworkAccessManager*\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OAuthTwitter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       1,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x05,
       3,    0,   55,    2, 0x05,
       4,    0,   56,    2, 0x05,
       5,    0,   57,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    1,   58,    2, 0x0a,
       8,    2,   61,    2, 0x0a,
      11,    0,   66,    2, 0x0a,
      12,    0,   67,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      13, 0x80000000 | 14, 0x0009510b,

       0        // eod
};

void OAuthTwitter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OAuthTwitter *_t = static_cast<OAuthTwitter *>(_o);
        switch (_id) {
        case 0: _t->authorizeXAuthFinished(); break;
        case 1: _t->authorizePinFinished(); break;
        case 2: _t->accessTokenGranted(); break;
        case 3: _t->authorizeXAuthError(); break;
        case 4: _t->requestAccessToken((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->authorizeXAuth((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->authorizePin(); break;
        case 7: _t->finishedAuthorization(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OAuthTwitter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OAuthTwitter::authorizeXAuthFinished)) {
                *result = 0;
            }
        }
        {
            typedef void (OAuthTwitter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OAuthTwitter::authorizePinFinished)) {
                *result = 1;
            }
        }
        {
            typedef void (OAuthTwitter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OAuthTwitter::accessTokenGranted)) {
                *result = 2;
            }
        }
        {
            typedef void (OAuthTwitter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OAuthTwitter::authorizeXAuthError)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject OAuthTwitter::staticMetaObject = {
    { &OAuth::staticMetaObject, qt_meta_stringdata_OAuthTwitter.data,
      qt_meta_data_OAuthTwitter,  qt_static_metacall, 0, 0}
};


const QMetaObject *OAuthTwitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OAuthTwitter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OAuthTwitter.stringdata))
        return static_cast<void*>(const_cast< OAuthTwitter*>(this));
    return OAuth::qt_metacast(_clname);
}

int OAuthTwitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OAuth::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QNetworkAccessManager**>(_v) = networkAccessManager(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setNetworkAccessManager(*reinterpret_cast< QNetworkAccessManager**>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void OAuthTwitter::authorizeXAuthFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void OAuthTwitter::authorizePinFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void OAuthTwitter::accessTokenGranted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void OAuthTwitter::authorizeXAuthError()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
