TEMPLATE = lib
CONFIG += qt
!win32:CONFIG += staticlib debug
TARGET = tiled
DESTDIR = ../../lib
DLLDESTDIR = ../../bin

win32:LIBS += zlib1.lib
else:LIBS += -lz

DEFINES += QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_TO_ASCII
DEFINES += TILED_LIBRARY
contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols
OBJECTS_DIR = ../../obj
SOURCES += compression.cpp \
    isometricrenderer.cpp \
    layer.cpp \
    map.cpp \
    mapobject.cpp \
    mapreader.cpp \
    mapwriter.cpp \
    objectgroup.cpp \
    orthogonalrenderer.cpp \
    properties.cpp \
    tilelayer.cpp \
    tileset.cpp
HEADERS += compression.h \
    isometricrenderer.h \
    layer.h \
    map.h \
    mapobject.h \
    mapreader.h \
    maprenderer.h \
    mapwriter.h \
    object.h \
    objectgroup.h \
    orthogonalrenderer.h \
    properties.h \
    tile.h \
    tiled_global.h \
    tilelayer.h \
    tileset.h
mac {
    contains(QT_CONFIG, ppc):CONFIG += x86 \
        ppc
    QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.5.sdk
}
