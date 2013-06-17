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
#include "StarAnimator.h"

using namespace std;

#define BIGSTARSPEED 50
#define MEDIUMSTARSPEED 100
#define SMALLSTARSPEED 150

StarAnimator::StarAnimator()
{
    stars = vector<CSprite*>();
    srand(time(NULL));
}

StarAnimator::~StarAnimator()
{

}

void StarAnimator::animate(int amount, int width, int height)
{
    screen_width = width;
    screen_height = height;
    //initialize random seed.
    allocateStars(amount);
}

void StarAnimator::allocateStars(int amount)
{
    int count = 0;
    while(count++ < amount)
    {
        CSprite* star = new CSprite();
        star->loadSpriteSparrowXML("data/img/stars.xml");
        star->setAnimRate(0);
        star->setCurrentFrame(2);
        star->setPosition(generateXPosition(), generateYPosition());

        int starspeed = rand() % 3;
        if(starspeed == 0)
            star->setYspeed(BIGSTARSPEED);
        if(starspeed == 1)
            star->setYspeed(MEDIUMSTARSPEED);
        if(starspeed == 2)
            star->setYspeed(SMALLSTARSPEED);

        stars.push_back(star);
    }
}

int StarAnimator::generateXPosition()
{
    return rand() % screen_width;
}

int StarAnimator::generateYPosition()
{
    return -(rand() % screen_height);
}

void StarAnimator::update(double interval)
{
    for(vector<CSprite*>::iterator i = stars.begin(); i != stars.end(); ++i)
    {
        CSprite* sprite = (*i);
        sprite->update(interval);

        if(sprite->getY() > screen_height)
            sprite->setPosition(generateXPosition(), generateYPosition());
    }
}

void StarAnimator::draw()
{
    for(vector<CSprite*>::iterator i = stars.begin(); i != stars.end(); ++i)
    {
            (*i)->draw();
    }
}
