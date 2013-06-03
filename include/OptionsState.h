#ifndef OPTIONSSTATE_H_INCLUDED
#define OPTIONSSTATE_H_INCLUDED

#include <SDL.h>
#include "CGameState.h"
#include "CImage.h"
#include "CSprite.h"

class OptionsState : public CGameState
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
    static OptionsState* instance()
    {
        return &m_OptionsState;
    }

    protected:

    OptionsState() {}

    private:

    static OptionsState m_OptionsState;

    CImage* instructionsImage;
    CSprite* goBackSprite;

};

#endif // OPTIONSSTATE_H_INCLUDED
