#-------------------------------------------------
#
# Project created by QtCreator 2020-08-27T10:32:47
#
#-------------------------------------------------

equals(QT_MAJOR_VERSION, 5) {
    QT  += core
    QT  += widgets
    QT  += gui
    QT  += xml
    QT  += sql
}

TARGET = STC
TEMPLATE = app

#LIBS += -lsqlite

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    db/sqlitedatabase.cpp \
    db/dbaccessor.cpp

HEADERS  += mainwindow.h \
    db/sqlitedatabase.h \
    db/dbaccessor.h

FORMS    += mainwindow.ui
