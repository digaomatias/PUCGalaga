
#ifndef _PAUSE_STATE_H_
#define _PAUSE_STATE_H_

#include <SDL.h>
#include "CGameState.h"
#include "CImage.h"

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

    // Singleton
    static PauseState* instance()
    {
        return &m_PauseState;
    }

    protected:

    PauseState() {}

    private:

    static PauseState m_PauseState;

    CImage* pauseImage;
};

#endif
