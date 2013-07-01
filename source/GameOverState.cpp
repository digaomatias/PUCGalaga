#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include "GameOverState.h"
GameOverState GameOverState::m_GameOverState;

using namespace std;

void GameOverState::init()
{
    gameOverFont = new CFont();
    gameOverFont->loadFont("data/fonts/arialblack28.png", 448, 640);

    cout << "GameOverState Init Successful" << endl;
}

void GameOverState::cleanup()
{
    cout << "GameOverState Clean Successful" << endl;
}

void GameOverState::pause()
{
    // Nada a fazer...
	cout << "GameOverState Paused" << endl;
}

void GameOverState::resume()
{
    // Nada a fazer...
	cout << "GameOverState Resumed" << endl;
}

void GameOverState::handleEvents(CGame* game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->quit();
				break;

            case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            game->quit();
                    }
                }
                break;

            case SDL_VIDEORESIZE:
                game->resize(event.resize.w, event.resize.h);
        }

    }
}

void GameOverState::update(CGame* game)
{
    // Atualiza a câmera de jogo
    game->updateCamera();
}

void GameOverState::draw(CGame* game)
{
    gameOverFont->draw(180,230, "GAME OVER");

    SDL_GL_SwapBuffers();
}
