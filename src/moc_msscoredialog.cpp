/****************************************************************************
** Meta object code from reading C++ file 'msscoredialog.h'
**
** Created: Fri Mar 13 13:23:47 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "msscoredialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msscoredialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MSScoreDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      30,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MSScoreDialog[] = {
    "MSScoreDialog\0\0slotAddScore()\0"
    "slotClearScore()\0"
};

const QMetaObject MSScoreDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MSScoreDialog,
      qt_meta_data_MSScoreDialog, 0 }
};

const QMetaObject *MSScoreDialog::metaObject() const
{
    return &staticMetaObject;
}

void *MSScoreDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MSScoreDialog))
        return static_cast<void*>(const_cast< MSScoreDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MSScoreDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotAddScore(); break;
        case 1: slotClearScore(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
