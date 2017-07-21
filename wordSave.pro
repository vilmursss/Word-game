QT       += core sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = sqlite_qt
CONFIG   += console
CONFIG   -= app_bundle


TEMPLATE = app


SOURCES += main.cpp \
    dbmanager.cpp \
    game.cpp \
    addword.cpp \
    mainwindow.cpp \
    removewords.cpp \
    editword.cpp \
    wordsearch.cpp \
    showsearchedwords.cpp

HEADERS += \
dbmanager.h \
    game.h \
    addword.h \
    mainwindow.h \
    removewords.h \
    editword.h \
    wordsearch.h \
    showsearchedwords.h

FORMS += \
    game.ui \
    addword.ui \
    mainwindow.ui \
    removewords.ui \
    editword.ui \
    wordsearch.ui \
    showsearchedwords.ui

RESOURCES += \
    resources.qrc
