QT += testlib
QT += gui
QT += widgets
QT += core
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_notestest.cpp \
    ../lab1/filereader.cpp \
    ../lab1/mainwindow.cpp \
    ../lab1/secondwindow.cpp \
    ../lab1/windowofgroups.cpp

HEADERS += \
    ../lab1/filereader.h \
    ../lab1/mainwindow.h \
    ../lab1/secondwindow.h \
    ../lab1/windowofgroups.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-editinghistory-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/release/ -leditinghistory
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-editinghistory-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug/ -leditinghistory


INCLUDEPATH += $$PWD/../editinghistory
DEPENDPATH += $$PWD/../editinghistory

FORMS += \
    ../lab1/mainwindow.ui \
    ../lab1/secondwindow.ui \
    ../lab1/windowofgroups.ui

