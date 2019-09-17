#ifndef ThroughBall_H
#define ThroughBall_H
#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"
#include "Board.h"
#include "Bat.h"
#include "Ball.h"
using namespace std;


class ThroughBall :public Ball
{
    public:
        enum ANIMATION_FRAMES {FLYING_FRAMES = 3};
        SDL_Rect spriteClips[ FLYING_FRAMES ];
        LTexture* spriteSheetTexture;
    public:
        ThroughBall(LTexture* image, float x, float y);
        ThroughBall();
        virtual ~ThroughBall();
        void SetAlive(bool);
        bool GetAlive();
        virtual void Move(float xx, float yy);
        virtual void Render(long int frame,SDL_Renderer* gRenderer);
        void didCollide(CollisionInfo info);
};




#endif // BALL_H

