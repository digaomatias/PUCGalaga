#ifndef PLAYER_H
#define PLAYER_H

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

class Player : public CSprite
{
public:
        Player(char* sparrowPath, char* shotSparrowPath);
        ~Player();
        void draw();
        void shoot();
        void update(double updateInterval);
        std::vector<CSprite*> getShots();

private:
        std::vector <CSprite*> shotVector;
        char* shotPath;
};

#endif // CSPRITE_H
