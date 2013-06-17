/*
 *  CSprite.cpp
 *  Sprite class
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */
#include <vector>
#include "Enemy.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define SHOTSPEED 180

Enemy::~Enemy()
{
    shotVector.clear();
}

// Construtor
Enemy::Enemy(char* sparrowPath, char* shotSparrowPath, int life) : CSprite()
{
    loadSpriteSparrowXML(sparrowPath);
    shotPath = shotSparrowPath;
    lives = life;
    exploding = false;

    boom = new CSprite();
    boom->loadSpriteSparrowXML("data/img/explosion.xml");
    boom->setScale(1.5);
    boom->setFrameRange(0, 4);
    boom->setCurrentFrame(0);
    boom->setAnimRate(15);
}

void Enemy::draw()
{
    CSprite::draw();

    for(vector<CSprite*>::iterator t = shotVector.begin(); t != shotVector.end(); ++t)
    {
        (*t)->draw();
    }

    if(exploding)
        boom->draw();
}

void Enemy::update(double interval, CGame* game)
{
    if(exploding)
    {
        boom->setVisible(true);
        boom->setPosition(this->getX(), this->getY());
        boom->update(game->getUpdateInterval());
        if(boom->getCurrentFrame() == 4)
        {
            boom->setVisible(false);
            exploding = false;
            delete boom;
        }
    }
    else
        CSprite::update(interval);

    vector< CSprite * >::iterator iter = shotVector.begin();

    while (iter != shotVector.end())
    {
        CSprite * pItem = *iter;

        if (pItem->getY() <= game->getHeight())
        {
            pItem->update(interval);
            ++iter;
        }
        else
        {
            delete pItem;
            iter = shotVector.erase(iter);
        }
    }
}

void Enemy::shoot()
{
    CSprite* shotSprite = new CSprite();
    shotSprite->loadSpriteSparrowXML(shotPath);
    shotSprite->setAnimRate(0);
    shotSprite->setCurrentFrame(1);
    shotSprite->setPosition(x, y);
    shotSprite->setScale(1.4);
    shotSprite->setYspeed(SHOTSPEED);
    shotVector.push_back(shotSprite);
}

void Enemy::hit()
{
    lives--;
    if(isDead())
    {
        exploding = true;
        setVisible(false);
    }
}

bool Enemy::isShooting()
{
    return shotVector.size() > 0;
}

bool Enemy::isExploding()
{
    return exploding;
}

bool Enemy::isDead()
{
    return lives == 0;
}


