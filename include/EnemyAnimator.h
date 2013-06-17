#ifndef ENEMYANIMATOR_H
#define ENEMYANIMATOR_H

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
#include "Enemy.h"

#define SQUARED_MOVE 1
#define LEFT_TO_RIGHT 2
#define RIGHT_TO_LEFT 3
#define DOWN_UP 4
class EnemyAnimator
{
public:
        EnemyAnimator(int enemyAmount, int width, int height, char* sparrowXML, char* shotSparrowPath, int life);
        ~EnemyAnimator();
        void update(double interval, CGame* game, std::vector<CSprite*> shots);
        void draw();
        bool isFinished();

private:
        bool finished;
        int screen_width, screen_height;
        std::vector <Enemy*> enemies;
        char* sparrowPath;
        void allocateEnemies(int count, char* sparrowPath, char* shotSparrowPath, int life);
        void handleShotsCollision(Enemy* enemy, std::vector<CSprite*> shots);
        int generateXPosition();
        int generateYPosition(Enemy* enemy, int order);
};

#endif // EnemyAnimator_H

