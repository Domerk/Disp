#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T17:23:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyCompiler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lexer.cpp

HEADERS  += mainwindow.h \
    lexer.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=gnu++0x
