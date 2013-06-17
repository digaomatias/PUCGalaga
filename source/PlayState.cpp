/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 04/13
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <sstream>
#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include <cmath>
#include "CGame.h"
#include "PlayState.h"
#include "StarAnimator.h"
#include "PauseState.h"
#include "EnemyAnimator.h"
PlayState PlayState::m_PlayState;

using namespace std;

#define SPEED 225

void PlayState::init()
{
    mapImage = new CImage();
    mapImage->loadImage("data/img/galaga_map.png");
    mapImage->setPosition(0,0);

    /*spaceshot = new CSprite();
    spaceshot->loadSpriteSparrowXML("data/img/spaceshots.xml");
    spaceshot->setPosition(-10, -10); //Cria o tiro fora da tela pra só aparecer após apertar espaço.
    spaceshot->setScale(2);*/

    starAnimator = new StarAnimator();
    starAnimator->animate(70, 640, 480);

    player = new Player("data/img/spaceship1.xml", "data/img/spaceshots.xml");
    // player->loadSprite("data/img/smurf_sprite.png", 128, 128, 0, 0, 0, 0, 7, 3, 16);

    // Carrega um sprite de Smurf
    player->loadSpriteSparrowXML("data/img/spaceship1.xml");
    // Posição inicial
    player->setPosition(320,400);
    // Taxa de animação: zero no início (personagem está parado)
    player->setAnimRate(0);
    player->setCurrentFrame(6);
    player->setScale(1.5);

    enemyAnimator1 = new EnemyAnimator(10, 640, 480, "data/img/enemy1.xml", "data/img/spaceshots.xml", 1);

    // Taxa de animação: zero no início (personagem está parado)
    dirx = 0; // direção do personagem: para a direita (5), esquerda (-5)
    diry = 0; // direção do personagem: para cima (5), baixo (-5)

    // O mapa tem DUAS camadas: na segunda camada ha apenas um "pilar" azul

    keyState = SDL_GetKeyState(0); // get key state array

    scoreFont = new CFont();
    //scoreFont->loadFont("data/fonts/lucida12.png", 112, 208);
    scoreFont->loadFont("data/fonts/arialblack28.png", 448, 640);
    score = 0;

    cout << "PlayState Init Successful" << endl;
}

void PlayState::cleanup()
{
    // Libera memória
    delete player;
    delete enemyAnimator1;
    delete mapImage;
    delete starAnimator;
    delete scoreFont;
	cout << "PlayState Clean Successful" << endl;
}

void PlayState::pause()
{
    // Nada a fazer...
	cout << "PlayState Paused" << endl;
}

void PlayState::resume()
{
    // Nada a fazer...
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
                    case SDLK_SPACE:
                        player->shoot();
                        break;
                    case SDLK_ESCAPE:
                        game->pushState(PauseState::instance());
                        break;
                    default:
                        break;
                }
                break;
            case SDL_VIDEORESIZE:
                game->resize(event.resize.w, event.resize.h);
        }
        // Atribui o deslocamento adequado às variáveis dirx e diry,
        // de acordo com as setas pressionadas
        dirx = keyState[SDLK_RIGHT]*SPEED + keyState[SDLK_LEFT]*-SPEED;
        //diry = keyState[SDLK_DOWN] *SPEED + keyState[SDLK_UP]  *-SPEED;
    }

    //movimento para a direita
    bool movimentoDireita = dirx > 0;
    bool movimentoEsquerda = dirx < 0;
    bool estaParado = dirx == 0;
    float posicaoPlayerHorizontal = player->getX();
    bool posicaoPlayerInicioEsquerda = posicaoPlayerHorizontal <= 5;
    bool posicaoPlayerInicioDireita = posicaoPlayerHorizontal >= 612;
    bool podeMovimentarEsquerda = (movimentoEsquerda && (!posicaoPlayerInicioEsquerda));
    bool podeMovimentarDireita = podeMovimentarDireita = (movimentoDireita && (!posicaoPlayerInicioDireita));

    if(podeMovimentarEsquerda || podeMovimentarDireita)
    {
        // Seta velocidade atual do sprite
        player->setXspeed(dirx);
        //player->setYspeed(diry);
    }
    else
    {
        player->setXspeed(0);
    }

}

void PlayState::update(CGame* game)
{
    // Atualiza a câmera de jogo
    game->updateCamera();
    // Atualiza a animação de frames e movimento do personagem
    starAnimator->update(game->getUpdateInterval());
    player->update(game->getUpdateInterval());
    enemyAnimator1->update(game->getUpdateInterval(), game, player);

    score = (enemyAnimator1->getDeadEnemyQuantity() * 10);

    //check if player has no more lifes to show a game over
}

void PlayState::draw(CGame* game)
{
    glClearColor(0.0,0.0,0.0,1); // light gray
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Essa é a única forma de desenhar o personagem ENTRE as camadas
    mapImage->draw();
    starAnimator->draw();
    player->draw();
    enemyAnimator1->draw();

    std::stringstream sstm;
    sstm << "SCORE: " << score;

    //draw score
    //scoreFont->draw(480,460, const_cast<char *>(sstm.str().c_str()));
    scoreFont->draw(300,440, const_cast<char *>(sstm.str().c_str()));

    SDL_GL_SwapBuffers();
}
