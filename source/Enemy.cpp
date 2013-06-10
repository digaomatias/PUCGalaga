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

#define SHOTSPEED 400

Enemy::~Enemy()
{
    shotVector.clear();
}

// Construtor
Enemy::Enemy(char* sparrowPath, char* shotSparrowPath, CGame* game) : CSprite()
{
    this.game = game;
    loadSpriteSparrowXML(sparrowPath);
    shotPath = shotSparrowPath;
    firstFrame = 0;
    lastFrame = 0;
    curFrameD = 0.0;
    curframe = 0;
    curframe = 0;
    framedelay = 10;
}

void Enemy::draw()
{
    CSprite::draw();

    for(vector<CSprite*>::iterator t = shotVector.begin(); t != shotVector.end(); ++t)
    {
        (*t)->draw();
    }
}

void Enemy::update(double interval)
{
    CSprite::update(interval);

    vector< CSprite * >::iterator iter = shotVector.begin();
    vector< CSprite * >::iterator end  = shotVector.end();

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
    shotSprite->setCurrentFrame(0);
    shotSprite->setPosition(x, y);
    shotSprite->setScale(2);
    shotSprite->setYspeed(SHOTSPEED);
    shotVector.push_back(shotSprite);
}


