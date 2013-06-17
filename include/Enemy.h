#ifndef ENEMY_H
#define ENEMY_H

/*
 *  CSprite.cpp
 *  Sprite class
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include <vector>
#include "CMultiImage.h"
#include "CGame.h"
#include "CSprite.h"
#include "TexRect.h"
#include "tinyxml.h"

class Enemy : public CSprite
{
public:
        Enemy(char* sparrowPath, char* shotSparrowPath, int life);
        ~Enemy();
        void draw();
        void shoot();
        void update(double updateInterval, CGame* game);
        bool isDead();
        bool isShooting();
        bool isExploding();
        void hit();
private:
        std::vector <CSprite*> shotVector;
        char* shotPath;
        int lives;
        bool exploding;
        CSprite* boom;
};

#endif // ENEMY_H
