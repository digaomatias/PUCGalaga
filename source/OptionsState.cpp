/*
 *  OptionsState.cpp
 *  Options state
 *
 *
 */

#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include <cmath>
#include "OptionsState.h"
OptionsState OptionsState::m_OptionsState;

using namespace std;

void OptionsState::init()
{
    instructionsImage = new CImage();
    instructionsImage->loadImage("data/img/instrucoes.png");

    goBackSprite = new CSprite();
    goBackSprite->loadSpriteSparrowXML("data/img/menuGoBack.xml");

    cout << "OptionsState Init Successful" << endl;
}

void OptionsState::cleanup()
{
    delete instructionsImage;
    delete goBackSprite;

    cout << "OptionsState Clean Successful" << endl;
}

void OptionsState::pause()
{
    // Nada a fazer...
	cout << "OptionsState Paused" << endl;
}

void OptionsState::resume()
{
    // Nada a fazer...
	cout << "OptionsState Resumed" << endl;
}

void OptionsState::handleEvents(CGame* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

            case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				    case SDLK_RETURN:
                    case SDLK_ESCAPE:
                        game->popState();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_VIDEORESIZE:
                game->resize(event.resize.w, event.resize.h);
        }
    }
}

void OptionsState::update(CGame* game)
{
    // Atualiza a câmera de jogo
    game->updateCamera();
}

void OptionsState::draw(CGame* game)
{
    glClearColor(0, 0, 0, 1); //black
    glClear(GL_COLOR_BUFFER_BIT);

    instructionsImage->setPosition(50,50);
    instructionsImage->draw();

    goBackSprite->setPosition(50, 400);
    goBackSprite->drawFrame(1);

    SDL_GL_SwapBuffers();
}
