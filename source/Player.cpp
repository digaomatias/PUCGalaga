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
    delete firstLife;
    delete secondLife;
    delete thirdLife;
}

// Construtor
Player::Player(char* sparrowPath, char* shotSparrowPath) : CSprite()
{
    loadSpriteSparrowXML(sparrowPath);
    shotPath = shotSparrowPath;

    lifeQuantity = 3;

    firstLife = new CSprite();
    firstLife->loadSpriteSparrowXML(sparrowPath);
    firstLife->setAnimRate(0);
    firstLife->setCurrentFrame(6);
    firstLife->setPosition(80, 450);
    firstLife->setScale(1);
    firstLife->setYspeed(0);

    secondLife = new CSprite();
    secondLife->loadSpriteSparrowXML(sparrowPath);
    secondLife->setAnimRate(0);
    secondLife->setCurrentFrame(6);
    secondLife->setPosition(50, 450);
    secondLife->setScale(1);
    secondLife->setYspeed(0);

    thirdLife = new CSprite();
    thirdLife->loadSpriteSparrowXML(sparrowPath);
    thirdLife->setAnimRate(0);
    thirdLife->setCurrentFrame(6);
    thirdLife->setPosition(20, 450);
    thirdLife->setScale(1);
    thirdLife->setYspeed(0);
}

void Player::draw()
{
    CSprite::draw();

    for(vector<CSprite*>::iterator t = shotVector.begin(); t != shotVector.end(); ++t)
    {
        (*t)->draw();
    }

    switch(lifeQuantity)
    {
        case 3: thirdLife->draw();
        case 2: secondLife->draw();
        case 1: firstLife->draw();
        default: break;
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

void Player::hit()
{
    lifeQuantity--;
}

bool Player::dead()
{
    return (lifeQuantity < 1);
}
