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
    firstFrame = 0;
    lastFrame = 0;
    curFrameD = 0.0;
    curframe = 0;
    curframe = 0;
    framedelay = 10;
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
    vector<CSprite*> shootsToKeep = vector<CSprite*>();
    vector<CSprite*> shootsToRemove = vector<CSprite*>();

    for(vector<CSprite*>::iterator t = shotVector.begin(); t != shotVector.end(); ++t)
    {
        (*t)->update(interval);
        float shootY = (*t)->getY();
        if(shootY >= 0)
        {
            shootsToKeep.push_back(*t);
        }
        else
        {
            shootsToRemove.push_back(*t);
        }
    }

    for(vector<CSprite*>::iterator t = shootsToRemove.begin(); t != shootsToRemove.end(); ++t)
    {
        delete *t;
    }

    shootsToRemove.clear();
    shotVector.clear();
    shotVector = shootsToKeep;
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


