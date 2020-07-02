#-------------------------------------------------
#
# Project created by QtCreator 2020-05-03T21:34:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BigClass.cpp \
    Classes.cpp \
    CompulsoryCourse.cpp \
    Course.cpp \
    ElectiveCourses.cpp \
    Schedule.cpp \
    SmallClass.cpp

HEADERS  += mainwindow.h \
    abc.h \
    BigClass.hpp \
    Classes.hpp \
    CompulsoryCourse.hpp \
    Course.hpp \
    ElectiveCourses.hpp \
    Schedule.hpp \
    SmallClass.hpp

FORMS    += mainwindow.ui
