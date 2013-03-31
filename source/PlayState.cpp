/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include <cmath>
#include "CGame.h"
#include "PlayState.h"
#include "PauseState.h"

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init()
{
    player = new CImage();
    player->loadImage("data/img/Char14s.png");
    player->setPosition(10,100);
    dirx = 0; // direção do personagem: para a direita (5), esquerda (-5)
    diry = 0; // direção do personagem: para cima (5), baixo (-5)
    keyState = SDL_GetKeyState(0); // get key state array
    cout << "PlayState Init Successful" << endl;
}

void PlayState::cleanup()
{
    delete player;
	cout << "PlayState Clean Successful" << endl;
}

void PlayState::pause()
{
	cout << "PlayState Paused" << endl;
}

void PlayState::resume()
{
	cout << "PlayState Resumed" << endl;
}

void PlayState::handleEvents(CGame* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

            case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        game->quit();
                        break;
                    case SDLK_p:
                        game->pushState(PauseState::instance());
                        break;
                    default:
                        break;
                }
                break;
            case SDL_VIDEORESIZE:
                game->resize(event.resize.w, event.resize.h);
        }
        dirx = keyState[SDLK_RIGHT]*5 + keyState[SDLK_LEFT]*-5;
        diry = keyState[SDLK_DOWN] *5 + keyState[SDLK_UP]  *-5;
    }
}

void PlayState::update(CGame* game)
{
    float x = player->getX();
    float y = player->getY();
    player->setPosition(x+dirx,y+diry);
}

void PlayState::draw(CGame* game)
{
    glClearColor(0.8,0.8,0.8,1); // light gray
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    player->setRotation(0);
    player->setScale(1);
    player->draw();

    SDL_GL_SwapBuffers();
}
