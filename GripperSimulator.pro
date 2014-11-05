#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T19:18:02
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GripperSimulator
TEMPLATE = app
QMAKE_MAC_SDK = macosx
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    Models/object.cpp \
    Models/gripper.cpp \
    Models/simulation.cpp \
    Graphics/simulationdisplaywidget.cpp \
    Models/linearvaluechanger.cpp \
    Models/objectinformation.cpp \
    Models/scorecalculator.cpp \
    JavaScript/javascriptgripper.cpp \
    JavaScript/javascriptevaluator.cpp \
    JavaScript/javascriptconsole.cpp

HEADERS  += mainwindow.h \
    Models/object.h \
    Models/gripper.h \
    Models/simulation.h \
    Graphics/simulationdisplaywidget.h \
    Models/linearvaluechanger.h \
    Models/objectinformation.h \
    Models/scorecalculator.h \
    JavaScript/javascriptgripper.h \
    JavaScript/javascriptevaluator.h \
    JavaScript/javascriptconsole.h

FORMS    += mainwindow.ui \
    JavaScript/javascriptconsole.ui
