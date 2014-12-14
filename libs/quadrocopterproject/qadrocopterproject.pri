#TEMPLATE = lib
#DESTDIR  = c:/helloapp
HEADERS += \
    $$PWD/planning_map_widget.h \
    $$PWD/planningstatswidget.h \
    $$PWD/segment_manager.h \
    $$PWD/segment_stat_widget.h \
    $$PWD/planning_map_toolbar.h \
    $$PWD/segment_line_manager.h
SOURCES += \
    $$PWD/planning_map_widget.cpp \
    $$PWD/planningstatswidget.cpp \
    $$PWD/segment_manager.cpp \
    $$PWD/segment_stat_widget.cpp \
    $$PWD/planning_map_toolbar.cpp \
    $$PWD/segment_line_manager.cpp
#DEFINES += USE_MY_STUFF
CONFIG  += debug
QT      += widgets

FORMS += \
    $$PWD/forms/planning_stats.ui \
    $$PWD/forms/segment_stat.ui
