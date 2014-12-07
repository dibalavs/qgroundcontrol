######################################################################
# Automatically generated by qmake (2.01a) Sa. Mrz 19 17:12:54 2011
######################################################################

# HACK! BIG TIME!
DEFINES += EXTERNAL_USE

OPMAPCONTROL_DIR = libs/opmapcontrol
DEPENDPATH += $$OPMAPCONTROL/core $$OPMAPCONTROL_DIR/src/internals $$OPMAPCONTROL_DIR/src/mapwidget $$OPMAPCONTROL_DIR/src/internals/projections
INCLUDEPATH += $$OPMAPCONTROL_DIR/src/core $$OPMAPCONTROL_DIR/src/internals $$OPMAPCONTROL_DIR/src/internals/projections $$OPMAPCONTROL_DIR/src/mapwidget

# Input
HEADERS += $$OPMAPCONTROL_DIR/opmapcontrol.h \
           $$OPMAPCONTROL_DIR/src/core/accessmode.h \
           $$OPMAPCONTROL_DIR/src/core/alllayersoftype.h \
           $$OPMAPCONTROL_DIR/src/core/cache.h \
           $$OPMAPCONTROL_DIR/src/core/cacheitemqueue.h \
           $$OPMAPCONTROL_DIR/src/core/debugheader.h \
           $$OPMAPCONTROL_DIR/src/core/diagnostics.h \
           $$OPMAPCONTROL_DIR/src/core/geodecoderstatus.h \
           $$OPMAPCONTROL_DIR/src/core/kibertilecache.h \
           $$OPMAPCONTROL_DIR/src/core/languagetype.h \
           $$OPMAPCONTROL_DIR/src/core/maptype.h \
           $$OPMAPCONTROL_DIR/src/core/memorycache.h \
           $$OPMAPCONTROL_DIR/src/core/opmaps.h \
           $$OPMAPCONTROL_DIR/src/core/placemark.h \
           $$OPMAPCONTROL_DIR/src/core/point.h \
           $$OPMAPCONTROL_DIR/src/core/providerstrings.h \
           $$OPMAPCONTROL_DIR/src/core/pureimage.h \
           $$OPMAPCONTROL_DIR/src/core/pureimagecache.h \
           $$OPMAPCONTROL_DIR/src/core/rawtile.h \
           $$OPMAPCONTROL_DIR/src/core/size.h \
           $$OPMAPCONTROL_DIR/src/core/tilecachequeue.h \
           $$OPMAPCONTROL_DIR/src/core/urlfactory.h \
           $$OPMAPCONTROL_DIR/src/internals/copyrightstrings.h \
           $$OPMAPCONTROL_DIR/src/internals/core.h \
           $$OPMAPCONTROL_DIR/src/internals/debugheader.h \
           $$OPMAPCONTROL_DIR/src/internals/loadtask.h \
           $$OPMAPCONTROL_DIR/src/internals/mousewheelzoomtype.h \
           $$OPMAPCONTROL_DIR/src/internals/pointlatlng.h \
           $$OPMAPCONTROL_DIR/src/internals/pureprojection.h \
           $$OPMAPCONTROL_DIR/src/internals/rectangle.h \
           $$OPMAPCONTROL_DIR/src/internals/rectlatlng.h \
           $$OPMAPCONTROL_DIR/src/internals/sizelatlng.h \
           $$OPMAPCONTROL_DIR/src/internals/tile.h \
           $$OPMAPCONTROL_DIR/src/internals/tilematrix.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/configuration.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/gpsitem.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/homeitem.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/mapgraphicitem.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/mapripform.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/mapripper.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/opmapwidget.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/trailitem.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/traillineitem.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/uavitem.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/uavmapfollowtype.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/uavtrailtype.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/waypointitem.h \
           $$OPMAPCONTROL_DIR/src/internals/projections/lks94projection.h \
           $$OPMAPCONTROL_DIR/src/internals/projections/mercatorprojection.h \
           $$OPMAPCONTROL_DIR/src/internals/projections/mercatorprojectionyandex.h \
           $$OPMAPCONTROL_DIR/src/internals/projections/platecarreeprojection.h \
           $$OPMAPCONTROL_DIR/src/internals/projections/platecarreeprojectionpergo.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/waypointlineitem.h \
           $$OPMAPCONTROL_DIR/src/mapwidget/basenavitem.h
FORMS += $$OPMAPCONTROL_DIR/src/mapwidget/mapripform.ui
SOURCES += $$OPMAPCONTROL_DIR/src/core/alllayersoftype.cpp \
           $$OPMAPCONTROL_DIR/src/core/cache.cpp \
           $$OPMAPCONTROL_DIR/src/core/cacheitemqueue.cpp \
           $$OPMAPCONTROL_DIR/src/core/diagnostics.cpp \
           $$OPMAPCONTROL_DIR/src/core/kibertilecache.cpp \
           $$OPMAPCONTROL_DIR/src/core/languagetype.cpp \
           $$OPMAPCONTROL_DIR/src/core/memorycache.cpp \
           $$OPMAPCONTROL_DIR/src/core/opmaps.cpp \
           $$OPMAPCONTROL_DIR/src/core/placemark.cpp \
           $$OPMAPCONTROL_DIR/src/core/point.cpp \
           $$OPMAPCONTROL_DIR/src/core/providerstrings.cpp \
           $$OPMAPCONTROL_DIR/src/core/pureimage.cpp \
           $$OPMAPCONTROL_DIR/src/core/pureimagecache.cpp \
           $$OPMAPCONTROL_DIR/src/core/rawtile.cpp \
           $$OPMAPCONTROL_DIR/src/core/size.cpp \
           $$OPMAPCONTROL_DIR/src/core/tilecachequeue.cpp \
           $$OPMAPCONTROL_DIR/src/core/urlfactory.cpp \
           $$OPMAPCONTROL_DIR/src/internals/core.cpp \
           $$OPMAPCONTROL_DIR/src/internals/loadtask.cpp \
           $$OPMAPCONTROL_DIR/src/internals/MouseWheelZoomType.cpp \
           $$OPMAPCONTROL_DIR/src/internals/pointlatlng.cpp \
           $$OPMAPCONTROL_DIR/src/internals/pureprojection.cpp \
           $$OPMAPCONTROL_DIR/src/internals/rectangle.cpp \
           $$OPMAPCONTROL_DIR/src/internals/rectlatlng.cpp \
           $$OPMAPCONTROL_DIR/src/internals/sizelatlng.cpp \
           $$OPMAPCONTROL_DIR/src/internals/tile.cpp \
           $$OPMAPCONTROL_DIR/src/internals/tilematrix.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/configuration.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/gpsitem.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/homeitem.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/mapgraphicitem.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/mapripform.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/mapripper.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/opmapwidget.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/trailitem.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/traillineitem.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/uavitem.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/waypointitem.cpp \
           $$OPMAPCONTROL_DIR/src/internals/projections/lks94projection.cpp \
           $$OPMAPCONTROL_DIR/src/internals/projections/mercatorprojection.cpp \
           $$OPMAPCONTROL_DIR/src/internals/projections/mercatorprojectionyandex.cpp \
           $$OPMAPCONTROL_DIR/src/internals/projections/platecarreeprojection.cpp \
           $$OPMAPCONTROL_DIR/src/internals/projections/platecarreeprojectionpergo.cpp \
           $$OPMAPCONTROL_DIR/src/mapwidget/waypointlineitem.cpp
RESOURCES += $$OPMAPCONTROL_DIR/src/mapwidget/mapresources.qrc
