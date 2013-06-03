/*
 *  PauseState.cpp
 *  Example "pause" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include "CGame.h"
#include "CFont.h"
#include "PauseState.h"
#include "OptionsState.h"

PauseState PauseState::m_PauseState;

using namespace std;

void PauseState::init()
{
    titleImage = new CImage();
    titleImage->loadImage("data/img/mainTitle.png"); // load menu state bitmap

    options[0] = new CSprite();
    options[0]->loadSpriteSparrowXML("data/img/menuContinue.xml");
    options[0]->setPosition(80,220);

    options[1] = new CSprite();
    options[1]->loadSpriteSparrowXML("data/img/menuOptions.xml");
    options[1]->setPosition(80,280);

    options[2] = new CSprite();
    options[2]->loadSpriteSparrowXML("data/img/menuQuit.xml");
    options[2]->setPosition(80,380);

    opcaoSel = 0;
    cout << "PauseState Init Successful" << endl;
}

void PauseState::cleanup()
{
    delete titleImage;
     for(int o=0; o<3; o++)
        delete options[o];
	cout << "PauseState Clean Successful" << endl;
}

void PauseState::resume() {}

void PauseState::pause() {}

void PauseState::handleEvents(CGame* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

            case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        game->popState();
                        break;
                    case SDLK_RETURN:
                        if(opcaoSel == 2)
                            game->quit();
                        else
                            if(opcaoSel == 0)
                                game->popState();
                        else
                            game->pushState(OptionsState::instance());
                            break;
                    case SDLK_UP:
                        opcaoSel--;
                        if(opcaoSel < 0)
                            opcaoSel = 2;
                        break;
                    case SDLK_DOWN:
                        opcaoSel++;
                        if(opcaoSel > 2)
                            opcaoSel = 0;
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
    glClearColor(0, 0, 0, 1); //black
    glClear(GL_COLOR_BUFFER_BIT);

    titleImage->setPosition(50,50);
    titleImage->draw();

    for(int o=0; o<3; o++)
        if(o == opcaoSel)
            options[o]->drawFrame(1);
        else
            options[o]->drawFrame(0);

    SDL_GL_SwapBuffers();
}

