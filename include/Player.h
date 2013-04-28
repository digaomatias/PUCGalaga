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

private:
        double xspeed,yspeed;       // speed in pixels/s
        int updateCount;            // current count of updates
        int firstFrame, lastFrame; // frame range
        int curframe;		        // current frame
        double curFrameD;           // the current frame as double
		int framecount,framedelay;  // slow down the frame animation
        int spriteW, spriteH;       // width and height of a single sprite frame
        std::vector <CSprite*> shotVector;
        char* shotPath;
};

#endif // CSPRITE_H
