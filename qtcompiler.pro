TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    twd.cpp \
    lexical.cpp \
    syntax.cpp \
    executer.cpp

HEADERS += \
    lexical.h \
    syntax.h \
    enum.h

DISTFILES += \
    file.txt
