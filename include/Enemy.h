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
        Enemy(char* sparrowPath, char* shotSparrowPath, CGame* game);
        ~Enemy();
        void draw();
        void shoot();
        void update(double updateInterval);

private:
        std::vector <CSprite*> shotVector;
        char* shotPath;
        CGame* game; //game is only used to clean up the shots
};

#endif // CSPRITE_H
