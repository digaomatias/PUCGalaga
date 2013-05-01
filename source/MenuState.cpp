/*
 *  MenuState.cpp
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
#include "MenuState.h"
#include "PlayState.h"

MenuState MenuState::m_MenuState;

using namespace std;

void MenuState::init()
{
    menuImage = new CImage();
    menuImage->loadImage("data/img/mainTitle.png"); // load menu state bitmap

    options[0] = new CSprite();
    options[0]->loadSpriteSparrowXML("data/img/menuNewGame.xml");
    options[0]->setPosition(80,180);

    options[1] = new CSprite();
    options[1]->loadSpriteSparrowXML("data/img/menuOptions.xml");
    options[1]->setPosition(80,280);

    options[2] = new CSprite();
    options[2]->loadSpriteSparrowXML("data/img/menuQuit.xml");
    options[2]->setPosition(80,380);

    opcaoSel = 0;
    firstTime = true;

	cout << "MenuState Init Successful" << endl;
}

void MenuState::cleanup()
{
    delete menuImage;
    for(int o=0; o<3; o++)
        delete options[o];
	cout << "MenuState Cleanup Successful" << endl;
}

void MenuState::pause()
{
	cout << "MenuState Paused" << endl;
}

void MenuState::resume()
{
	cout << "MenuState Resumed" << endl;
}

void MenuState::handleEvents(CGame* game)
{
	SDL_Event event;

    if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

			case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {

                    case SDLK_RETURN:
                        if(opcaoSel == 2)
                            game->quit();
                        else
                            if(opcaoSel == 0)
                                game->changeState(PlayState::instance());
                        else
                            cout << "Estado de Options" << endl;
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
                    case SDLK_ESCAPE:
                        game->quit();
                        break;
                    default:
                        break;
                }
		}
	}
}

void MenuState::update(CGame* game)
{
    if(firstTime) {
        //Apenas para caso necessite efetuar uma ação apenas na primeira atualização
        //
        firstTime = false;
    }
}

void MenuState::draw(CGame* game)
{
    //glClearColor(0.6,0.6,0.6,1); // gray
    glClearColor(0, 0, 0, 1); //black
    glClear(GL_COLOR_BUFFER_BIT);

    menuImage->setPosition(50,50);
    menuImage->draw();

    for(int o=0; o<3; o++)
        if(o == opcaoSel)
            options[o]->drawFrame(1);
        else
            options[o]->drawFrame(0);

    SDL_GL_SwapBuffers();
}



