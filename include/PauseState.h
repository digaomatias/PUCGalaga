/*
 *  PauseState.h
 *  Example "pause" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef PAUSE_STATE_H_
#define PAUSE_STATE_H_

#include <SDL.h>
#include "CGameState.h"
#include "CImage.h"
#include "CSprite.h"


class CFont;

class PauseState : public CGameState
{
    public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(CGame* game);
    void update(CGame* game);
    void draw(CGame* game);

    // Implement Singleton Pattern
    static PauseState* instance()
    {
        return &m_PauseState;
    }

    protected:

    PauseState() {}

    private:

    static PauseState m_PauseState;

    CImage* titleImage;
    CSprite* options[3];
    int opcaoSel;

};

#endif
