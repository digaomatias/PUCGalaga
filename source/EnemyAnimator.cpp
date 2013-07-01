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
#include "EnemyAnimator.h"

using namespace std;

#define ENEMY_SPEED 140

EnemyAnimator::EnemyAnimator(int amount, int width, int height, char* sparrowXML, char* shotSparrowPath, int life)
{
    enemies = vector<Enemy*>();
    srand(time(NULL));
    sparrowPath = sparrowXML;

    screen_width = width;
    screen_height = height;

    deadEnemyQuantity = 0;

    allocateEnemies(amount, sparrowPath, shotSparrowPath, life);
}

EnemyAnimator::~EnemyAnimator()
{
}

void EnemyAnimator::allocateEnemies(int amount, char* sparrowPath, char* shotSparrowPath, int life)
{
    int count = 0;
    while(count++ < amount)
    {
        Enemy* enemy = new Enemy(sparrowPath, shotSparrowPath, life);
        enemy->setFrameRange(0,1);
        enemy->setAnimRate(5);
        enemy->setYspeed(ENEMY_SPEED);
        enemy->setPosition(generateXPosition(), generateYPosition(enemy, count));

        enemies.push_back(enemy);
    }
}

int EnemyAnimator::generateXPosition()
{
    //Retorna no 10% de width
    return (screen_width*10)/100;
}

int EnemyAnimator::generateYPosition(Enemy* enemy, int order)
{
    //posiciona os inimigos numa distância equivalente ao tamanho deles e -2 pixels de offset.
    return (-enemy->getHeight()-5)*order;
}

void EnemyAnimator::handleShotsCollision(Enemy* enemy, vector<CSprite*> shots)
{
    for(vector<CSprite*>::iterator i = shots.begin(); i != shots.end(); ++i)
    {
        CSprite* shot = (*i);
        if(shot->bboxCollision(enemy))
        {
            enemy->hit();
            deadEnemyQuantity++;
            shot->setY(-1);
        }
    }
}

void EnemyAnimator::update(double interval, CGame* game, Player* player)
{
    vector<CSprite*> shots = player->getShots();

    for(vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();)
    {
        Enemy* enemy = (*i);

        bool finishedAnimation = (enemy->getY() < 0 && enemy->getX() > (screen_width/2));
        //remove inimigo se estiver morto e não estiver explodindo e atirando
        if((finishedAnimation || enemy->isDead() ) && !enemy->isShooting() && !enemy->isExploding())
         {
            i = enemies.erase(i);
            continue;
         }

        if(!enemy->isExploding() && !enemy->isDead())
        {
            handleShotsCollision(enemy, shots);
        }

        enemy->update(interval, game, player);

        //1 chance em 5 de atirar
        if(!enemy->isDead() && enemy->getY()>0 && rand()%100 == 0)
        {
            enemy->shoot();
        }

        if(enemy->getY() >= (screen_height*30)/100)
        {
            enemy->setYspeed(0);
            enemy->setXspeed(ENEMY_SPEED);
            enemy->setFrameRange(6,7);
        }

        if(enemy->getX() >= (screen_width*90)/100)
        {
            enemy->setXspeed(0);
            enemy->setYspeed(-ENEMY_SPEED);
            enemy->setFrameRange(0,1);
            enemy->setMirror(true);
        }

        ++i;
    }

     finished = enemies.size()==0;
}

bool EnemyAnimator::isFinished()
{
    return finished;
}

void EnemyAnimator::draw()
{

    for(vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
    {
            (*i)->draw();
    }
}

int EnemyAnimator::getDeadEnemyQuantity()
{
    return deadEnemyQuantity;
}
