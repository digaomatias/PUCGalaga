/*
 *  CSprite.cpp
 *  Sprite class
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */
#include <vector>
#include "Player.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define SHOTSPEED 400

Player::~Player()
{
    shotVector.clear();
}

// Construtor
Player::Player(char* sparrowPath, char* shotSparrowPath) : CSprite()
{
    loadSpriteSparrowXML(sparrowPath);
    shotPath = shotSparrowPath;
}

void Player::draw()
{
    CSprite::draw();

    for(vector<CSprite*>::iterator t = shotVector.begin(); t != shotVector.end(); ++t)
    {
        (*t)->draw();
    }
}

void Player::update(double interval)
{
    CSprite::update(interval);

    vector< CSprite * >::iterator iter = shotVector.begin();
    vector< CSprite * >::iterator end  = shotVector.end();

    while (iter != shotVector.end())
    {
        CSprite * pItem = *iter;

        if (pItem->getY() >= 0)
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

void Player::shoot()
{
    CSprite* shotSprite = new CSprite();
    shotSprite->loadSpriteSparrowXML(shotPath);
    shotSprite->setAnimRate(0);
    shotSprite->setCurrentFrame(0);
    shotSprite->setPosition(x, y);
    shotSprite->setScale(2);
    shotSprite->setYspeed(-SHOTSPEED);
    shotVector.push_back(shotSprite);
}

vector<CSprite*> Player::getShots()
{
    return shotVector;
}


