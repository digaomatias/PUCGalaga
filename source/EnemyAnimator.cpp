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
    animationType = SQUARED_MOVE;

    handleAllocation(amount, sparrowPath, shotSparrowPath, life);
}

EnemyAnimator::EnemyAnimator(int amount, int width, int height, char* sparrowXML, char* shotSparrowPath, int life, int animationType)
{
    enemies = vector<Enemy*>();
    srand(time(NULL));
    sparrowPath = sparrowXML;

    screen_width = width;
    screen_height = height;

    deadEnemyQuantity = 0;
    this->animationType = animationType;

    handleAllocation(amount, sparrowPath, shotSparrowPath, life);
}

EnemyAnimator::EnemyAnimator()
{
    //Does nothing:
    finished = true;
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

void EnemyAnimator::handleAllocation(int amount, char* sparrowPath, char* shotSparrowPath, int life)
{
    int count = 0;
    switch(animationType)
    {
        case SQUARED_MOVE:;
            while(count++ < amount)
            {
                Enemy* enemy = new Enemy(sparrowPath, shotSparrowPath, life);
                enemy->setFrameRange(0,1);
                enemy->setAnimRate(5);
                enemy->setYspeed(ENEMY_SPEED);
                int x = (screen_width*10)/100;
                int y = (-enemy->getHeight()-5)*count;
                enemy->setPosition(x, y);

                enemies.push_back(enemy);
            }
            break;
        case LEFT_TO_RIGHT:
            while(count++ < amount)
            {
                Enemy* enemy = new Enemy(sparrowPath, shotSparrowPath, life);
                enemy->setFrameRange(6,7);
                enemy->setAnimRate(5);
                enemy->setXspeed(ENEMY_SPEED);
                int x = (-enemy->getWidth()-5)*count;
                int y = (screen_height*10)/100;
                enemy->setPosition(x, y);

                enemies.push_back(enemy);
            }
            break;
        case RIGHT_TO_LEFT:
            while(count++ < amount)
            {
                Enemy* enemy = new Enemy(sparrowPath, shotSparrowPath, life);
                enemy->setFrameRange(6,7);
                enemy->setAnimRate(5);
                enemy->setMirror(true);
                enemy->setXspeed(-ENEMY_SPEED);
                int x = screen_width+(enemy->getWidth()+5)*count;
                int y = (screen_height*35)/100;
                enemy->setPosition(x, y);

                enemies.push_back(enemy);
            }
            break;
        case DOWN_UP:
            int lineCount = 1;
            int columnCount = 0;
            while(count++ < amount)
            {
                Enemy* enemy = new Enemy(sparrowPath, shotSparrowPath, life);
                enemy->setFrameRange(6,7);
                enemy->setAnimRate(5);
                enemy->setMirror(true);
                enemy->setYspeed(ENEMY_SPEED);

                int startingX = (screen_width*10)/100;
                int x = startingX+(enemy->getWidth()+5)*columnCount;
                int y = (-enemy->getHeight()+5)*lineCount;
                enemy->setPosition(x, y);

                if(x > screen_width - (screen_width*10)/100)
                {
                    lineCount++;
                    columnCount = 0;
                }
                columnCount++;

                enemies.push_back(enemy);
            }
            break;
    }
}

void EnemyAnimator::handleAnimation(Enemy* enemy)
{
    switch(animationType)
    {
        case SQUARED_MOVE:
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
            break;

        case LEFT_TO_RIGHT:
            break;
        case RIGHT_TO_LEFT:
            break;
        case DOWN_UP:
            if(enemy->getY() >= (screen_height*50)/100)
            {
                enemy->setYspeed(-ENEMY_SPEED*1.2);
                enemy->setFrameRange(0,1);
                enemy->setMirror(true);
            }
            break;
    }
}

void EnemyAnimator::update(double interval, CGame* game, Player* player)
{
    if(!finished)
    {
        vector<CSprite*> shots = player->getShots();

        for(vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end();)
        {
            Enemy* enemy = (*i);

            bool finishedAnimation = false;

            switch(animationType)
            {
                case SQUARED_MOVE:
                    finishedAnimation = (enemy->getY() < 0 && enemy->getX() > (screen_width/2));
                    break;
                case LEFT_TO_RIGHT:
                    finishedAnimation = enemy->getX() > (screen_width+enemy->getWidth());
                    break;
                case RIGHT_TO_LEFT:
                    finishedAnimation = enemy->getX() < (-enemy->getWidth());
                    break;
                case DOWN_UP:
                    finishedAnimation = enemy->getY() < (-screen_height/2);
                    break;
            }

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

            handleAnimation(enemy);

            ++i;
        }

         finished = enemies.size()==0;
    }
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
