#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T01:17:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LAB04
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    error.cpp \
    gauss_matrix.cpp \
    legandre_poli.cpp \
    zero_root.cpp \
    spline.cpp

HEADERS  += mainwindow.h \
    error.h \
    gauss_matrix.h \
    legandre_poli.h \
    zero_root.h \
    spline.h

FORMS    += mainwindow.ui
