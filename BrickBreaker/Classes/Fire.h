#ifndef FIRE_H
#define FIRE_H
#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"

using namespace std;


class Fire :public Object
{
    public:
       // bool alive;
        float speedx;
        float speedy;
    public:
        virtual void Move()=0; //moving fire in y-direction
        virtual void Render(long int frame, SDL_Renderer* gRenderer) = 0;
};






#endif // FIRE_H
