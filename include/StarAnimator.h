#ifndef STARANIMATOR_H
#define STARANIMATOR_H

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
#include "time.h"

class StarAnimator
{
public:
        StarAnimator();
        ~StarAnimator();
        void animate(int starAmount, int width, int height);
        void update(double interval);
        void draw();

private:
        int screen_width, screen_height;
        std::vector <CSprite*> stars;
        char* starsPath;
        void allocateStars(int count);
        int generateXPosition();
        int generateYPosition();
};

#endif // StarAnimator_H
