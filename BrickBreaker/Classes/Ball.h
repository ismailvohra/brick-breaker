#ifndef BALL_H
#define BALL_H
#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "LTexture.h"
#include "Bat.h"



using namespace std;
//enum MMOTION {RRIGHT, LLEFT, UUP, DDOWN};

class Ball : public Object
{
    public:
       // bool alive;
        float dirx; //x-direction of ball
        float diry; //y-direction of ball
        float speedx; //speed in x- direction
        float speedy; //speed in y- direction
        //float friction;
        bool shouldMove; //checking move
        int BALL_SPEED = 9;
        BallType type;
        virtual void Move(float x, float y) = 0;
        virtual void Render(long int frame, SDL_Renderer* gRenderer) = 0;
        void SetDirection(float dirx, float diry); //Changes direction when collides with object
        virtual void Move();
        virtual void didCollide(CollisionInfo info) = 0;
        virtual Ball* multiplyBall(LTexture* image);
};


#endif // BALL_H
