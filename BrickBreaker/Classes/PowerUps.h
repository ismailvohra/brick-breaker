#ifndef POWERUPS_H
#define POWERUPS_H

#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "LTexture.h"

using namespace std;


class PowerUps : public Object
{
    public:
        bool alive;
        float speedx;
        float speedy;
        float friction; //lower speed means more friction
        PowerType powerType;
        LTexture* spriteSheetTexture;

    public:
        PowerUps(LTexture* image, int x, int y);
        ~PowerUps();
        virtual void Move();
        virtual void Render(long int frame, SDL_Renderer* gRenderer);
};

#endif // POWERUPS_H
