/*
 *  MenuState.h
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <SDL.h>
#include "CGameState.h"
#include "CImage.h"
#include "CSprite.h"

class MenuState : public CGameState
{
    public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(CGame* game);
    void update(CGame* game);
    void draw(CGame* game);

    // Singleton
    static MenuState* instance()
    {
        return &m_MenuState;
    }

    protected:

    MenuState() {}

    private:

    static MenuState m_MenuState;

    CImage* menuImage;
    CSprite* options[3];
    int opcaoSel;

    bool firstTime; // true se for primeiro update - usada para setar pos. inicial do Smurf
};

#endif
