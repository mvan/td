include(./td.pri)

include(./server/server.pri)

include(./audio/audio.pri)
include(./engine/engine.pri)
include(./graphics/graphics.pri)
include(./input/input.pri)
include(./network/network.pri)
include(./physics/physics.pri)
include(./util/util.pri)

DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = ../obj/server
DEFINES += SERVER

HEADERS += $$SERVER_HDRS $$AUDIO_HDRS $$NETWORK_HDRS_S $$ENGINE_HDRS_S $$BASE_GRAPHICS_HDRS $$INPUT_HDRS $$PHYSICS_HDRS $$UTIL_HDRS
SOURCES += $$SERVER_SRCS $$AUDIO_SRCS $$NETWORK_SRCS_S $$ENGINE_SRCS_S $$BASE_GRAPHICS_SRCS $$INPUT_SRCS $$PHYSICS_SRCS $$UTIL_SRCS
