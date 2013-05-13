/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 04/13
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include <cmath>
#include "CGame.h"
#include "PlayState.h"
#include "StarAnimator.h"
#include "PauseState.h"
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
    starAnimator->animate(200, 640, 480);

    player = new Player("data/img/spaceship1.xml", "data/img/spaceshots.xml");
    // player->loadSprite("data/img/smurf_sprite.png", 128, 128, 0, 0, 0, 0, 7, 3, 16);

    // Carrega um sprite de Smurf
    player->loadSpriteSparrowXML("data/img/spaceship1.xml");
    // Posição inicial
    player->setPosition(320,400);
    // Taxa de animação: zero no início (personagem está parado)
    player->setAnimRate(0);
    player->setCurrentFrame(6);
    player->setScale(2);
    dirx = 0; // direção do personagem: para a direita (5), esquerda (-5)
    diry = 0; // direção do personagem: para cima (5), baixo (-5)

    //map = new TMXLoader();
    // Carrega mapa com duas camadas
    //map->loadMap("data/maps/desert2.tmx");

    // Adiciona o jogador na lista de objetos que o mapa deve desenhar
    // na camada especificada (default: primeira camada - 0)
    //map->addImageObject(player);
    // O mapa tem DUAS camadas: na segunda camada ha apenas um "pilar" azul

    keyState = SDL_GetKeyState(0); // get key state array
    cout << "PlayState Init Successful" << endl;
}

void PlayState::cleanup()
{
    // Libera memória
    delete player;
    delete map;
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

    /*
    // Se uma das direções não for zero, ativa animação dos frames do personagem
    if(dirx || diry)
        player->setAnimRate(30);
    else {
        // Caso contrário, pára a animação dos frames
        // e fixa o frame atual no 3 (Smurf parado)
        player->setAnimRate(0);
        player->setCurrentFrame(3);
    }

    // Se movimento for para a direita, desliga o "mirror" do personagem
    if(dirx > 0)
        player->setMirror(false);
        // Se for para a esquerda, liga
    else if(dirx < 0)
        player->setMirror(true);
    */
}

void PlayState::update(CGame* game)
{
    //float x = player->getX();
    //float y = player->getY();
    // Seta o pan da câmera de jogo, de forma a centralizar o personagem
    //game->setXpan(x-game->getWidth()/2);
    //game->setYpan(y-game->getHeight()/2);
    // Atualiza a câmera de jogo
    game->updateCamera();
    // Atualiza a animação de frames e movimento do personagem
    starAnimator->update(game->getUpdateInterval());
    player->update(game->getUpdateInterval());
    //spaceshot->update(game->getUpdateInterval());
}

void PlayState::draw(CGame* game)
{
    glClearColor(0.0,0.0,0.0,1); // light gray
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Não desenha mais diretamente o personagem
    //player->setRotation(0);
    //player->setScale(1);
    //player->draw();

    // Agora o mapa e' responsavel por desenhar o jogador, imediatamente depois
    // da camada 0 (primeira camada do mapa)

    // Essa é a única forma de desenhar o personagem ENTRE as camadas
    mapImage->draw();
    starAnimator->draw();
    player->draw();
    //spaceshot->drawFrame(0);
    SDL_GL_SwapBuffers();
}
