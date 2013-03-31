#-------------------------------------------------
#
# Project created by QtCreator 2011-06-03T14:28:09
#
#-------------------------------------------------

QT       -= core
QT       -= gui

TARGET = Framework
CONFIG   += console
CONFIG   += opengl
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = ../../../bin

QMAKE_CXXFLAGS += -m32

LIBS += -framework SDL -framework SDL_image -framework SDL_image \
    -framework Cocoa \
    ../../../lib/Box2D-2.1.0/lib-OSX/libBox2D.a \
    ../../../lib/irrKlang-1.3.0/macosx-gcc/libirrklang.dylib \
    -lglew32
#    SDLMain.o


INCLUDEPATH += ../../../include \
    /Library/Frameworks/SDL.framework/Headers \
    /Library/Frameworks/SDL_image.framework/Headers \
    /Library/Frameworks/SDL_mixer.framework/Headers \
    ../../../lib/irrKlang-1.3.0/include \
    ../../../lib/Box2D-2.1.0/include

SOURCES += \
    ../../../source/CImage.cpp \
    ../../../source/CGame.cpp \
    ../../../source/MenuState.cpp \
    ../../../source/main.cpp \
    ../../../source/PlayState.cpp \
    ../../../source/TextureManager.cpp

OBJECTIVE_SOURCES += \
    ../../../source/SDLMain.m

HEADERS += \
    ../../../include/SDLMain.h \
    ../../../include/PlayState.h \
    ../../../include/MenuState.h \
    ../../../include/CImage.h \
    ../../../include/CGameState.h \
    ../../../include/CGame.h \
    ../../../include/Graphics.h

OTHER_FILES += \
    ../../../bin/data/shaders/nightvision.vert
