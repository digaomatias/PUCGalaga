/*
 *  PauseState.cpp
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include "CGame.h"
#include "PauseState.h"
#include "PlayState.h"

PauseState PauseState::m_PauseState;

using namespace std;

void PauseState::init()
{
    pauseImage = new CImage();
    pauseImage->loadImage("data/img/paused.png"); // load pause state bitmap
	cout << "PauseState Init Successful" << endl;
}

void PauseState::cleanup()
{
    delete pauseImage;
	cout << "PauseState Cleanup Successful" << endl;
}

void PauseState::pause()
{
	cout << "PauseState Paused" << endl;
}

void PauseState::resume()
{
	cout << "PauseState Resumed" << endl;
}

void PauseState::handleEvents(CGame* game)
{
	SDL_Event event;

    if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

			case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {

                    case SDLK_p:
                        game->popState();
                        break;
                    default:
                        break;
                }
		}
	}
}

void PauseState::update(CGame* game)
{
}

void PauseState::draw(CGame* game)
{
    glClearColor(1,1,1,0.2); // gray
    glClear(GL_COLOR_BUFFER_BIT);
    pauseImage->setPosition(50,50);
    pauseImage->draw();
    SDL_GL_SwapBuffers();
}

