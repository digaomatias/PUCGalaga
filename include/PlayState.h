/*
 *  PlayState.h
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#include <SDL.h>
#include "CGameState.h"
#include "CSprite.h"
#include "Player.h"
#include "maploader/TMXLoader.h"
#include "StarAnimator.h"
#include "EnemyAnimator.h"
#include "CFont.h"

class PlayState : public CGameState
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
    static PlayState* instance()
    {
        return &m_PlayState;
    }

    protected:

    PlayState() {}

    private:

    static PlayState m_PlayState; // singleton

    float dirx, diry; // movement direction
    Player* player;  // player image
    std::vector<EnemyAnimator*> enemyAnimators;
    std::vector<EnemyAnimator*>::iterator animatorsIt;

    std::vector<EnemyAnimator*> auxEnemyAnimators;
    std::vector<EnemyAnimator*>::iterator auxAnimatorIt;
    CImage* mapImage;
    StarAnimator* starAnimator;
    Uint8* keyState;  // array to store keyboard state
    CFont* scoreFont;
    int score;
    bool gameOver;
};

#endif
