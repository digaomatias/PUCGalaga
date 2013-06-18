#ifndef GAMEOVERSTATE_H_INCLUDED
#define GAMEOVERSTATE_H_INCLUDED

#include <SDL.h>
#include "CGameState.h"
#include "CFont.h"

class GameOverState : public CGameState
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
        static GameOverState* instance()
        {
            return &m_GameOverState;
        }

    protected:

        GameOverState() {}

    private:

        static GameOverState m_GameOverState; // singleton
        CFont* gameOverFont;
};

#endif // GAMEOVERSTATE_H_INCLUDED
