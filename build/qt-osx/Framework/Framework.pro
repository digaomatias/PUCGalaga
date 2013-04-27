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
    -lglew32
#    SDLMain.o


INCLUDEPATH += ../../../include \
    /Library/Frameworks/SDL.framework/Headers \
    /Library/Frameworks/SDL_image.framework/Headers \
    /Library/Frameworks/SDL_mixer.framework/Headers \
    ../../../lib/irrKlang-1.3.0/include \
    ../../../lib/Box2D-2.1.0/include \
    ../../../include/tinyxml \
    ../../../include/maploader

SOURCES += \
    ../../../source/CImage.cpp \
    ../../../source/CGame.cpp \
    ../../../source/MenuState.cpp \
    ../../../source/main.cpp \
    ../../../source/PlayState.cpp \
    ../../../source/TextureManager.cpp \
    ../../../source/CMultiImage.cpp \
    ../../../source/CSprite.cpp \
    ../../../source/CFont.cpp \
    ../../../source/maploader/TMXLoader.cpp \
    ../../../source/maploader/base64.cpp \
    ../../../source/tinyxml/tinyxmlparser.cpp \
    ../../../source/tinyxml/tinyxmlerror.cpp \
    ../../../source/tinyxml/tinyxml.cpp \
    ../../../source/tinyxml/tinystr.cpp \
    ../../../source/PlaySpriteState.cpp \
    ../../../source/PauseState.cpp

OBJECTIVE_SOURCES += \
    ../../../source/SDLMain.m

HEADERS += \
    ../../../include/SDLMain.h \
    ../../../include/PlayState.h \
    ../../../include/MenuState.h \
    ../../../include/CImage.h \
    ../../../include/CGameState.h \
    ../../../include/CGame.h \
    ../../../include/Graphics.h \
    ../../../include/CMultiImage.h \
    ../../../include/CSprite.h \
    ../../../include/CFont.h \
    ../../../include/maploader/TMXLoader.h \
    ../../../include/maploader/base64.h \
    ../../../include/tinyxml/tinyxml.h \
    ../../../include/tinyxml/tinystr.h \
    ../../../include/TexRect.h \
    ../../../include/PlaySpriteState.h \
    ../../../include/PauseState.h

OTHER_FILES += \
    ../../../bin/data/shaders/nightvision.vert
