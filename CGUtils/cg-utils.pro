#-------------------------------------------------
#
# Project created by QtCreator 2019-01-12T11:55:02
#
#-------------------------------------------------

#QT       -= gui
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cg-utils
TEMPLATE = lib

DEFINES += CGUTILS_LIBRARY

QMAKE_CXXFLAGS += -std=c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    utils.cpp \
    triangle.cpp \
    polygon.cpp \
    mesh.cpp \
    optimalpolygontriangulator.cpp \
    matrix.tpp \
    vector.tpp \
    camera.cpp

HEADERS += \
        cg-utils_global.h \
    matrix.h \
    utils.h \
    triangle.h \
    polygon.h \
    mesh.h \
    optimalpolygontriangulator.h \
    traits.h \
    vector.h \
    camera.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
