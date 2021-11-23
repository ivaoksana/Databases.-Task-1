TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += "c:/sqlite/sqlite3.dll"
SOURCES += \
        main.cpp \
        simplesql.cpp \
        sqlite3.c

HEADERS += \
    matrix.h \
    simplesql.h \
