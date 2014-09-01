#-------------------------------------------------
#
# Project created by QtCreator 2014-08-27T15:13:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notes
TEMPLATE = app


SOURCES += main.cpp\
        main_window.cpp \
    models/note.cpp \
    widgets/jlabel.cpp \
    widgets/window_add_note.cpp \
    widgets/editable_label.cpp

HEADERS  += main_window.hpp \
    models/note.hpp \
    utils/resources_manager.hpp \
    utils/icons_manager.hpp \
    utils/pixmap_manager.hpp \
    widgets/jlabel.hpp \
    widgets/window_add_note.hpp \
    widgets/editable_label.hpp

QMAKE_CXXFLAGS += -std=c++11
