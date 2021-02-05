/****************************************************************************
** Meta object code from reading C++ file 'msmainwindow.h'
**
** Created: Fri Mar 13 22:32:38 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "msmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MSMainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x09,
      28,   13,   13,   13, 0x09,
      46,   13,   13,   13, 0x09,
      57,   13,   13,   13, 0x09,
      68,   13,   13,   13, 0x09,
      80,   13,   13,   13, 0x09,
      91,   13,   13,   13, 0x09,
     103,   13,   13,   13, 0x09,
     115,   13,   13,   13, 0x09,
     133,   13,   13,   13, 0x09,
     144,   13,   13,   13, 0x09,
     156,   13,   13,   13, 0x09,
     170,   13,   13,   13, 0x09,
     185,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MSMainWindow[] = {
    "MSMainWindow\0\0slotNewGame()\0"
    "slotRestartGame()\0slotUndo()\0slotRedo()\0"
    "slotScore()\0slotExit()\0slotMusic()\0"
    "slotSound()\0slotPreferences()\0slotHelp()\0"
    "slotAbout()\0slotTimeOut()\0slotGameOver()\0"
    "slotChangeMenuStatus()\0"
};

const QMetaObject MSMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MSMainWindow,
      qt_meta_data_MSMainWindow, 0 }
};

const QMetaObject *MSMainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MSMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MSMainWindow))
        return static_cast<void*>(const_cast< MSMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MSMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotNewGame(); break;
        case 1: slotRestartGame(); break;
        case 2: slotUndo(); break;
        case 3: slotRedo(); break;
        case 4: slotScore(); break;
        case 5: slotExit(); break;
        case 6: slotMusic(); break;
        case 7: slotSound(); break;
        case 8: slotPreferences(); break;
        case 9: slotHelp(); break;
        case 10: slotAbout(); break;
        case 11: slotTimeOut(); break;
        case 12: slotGameOver(); break;
        case 13: slotChangeMenuStatus(); break;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
