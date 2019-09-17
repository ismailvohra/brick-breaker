#ifndef NORMALFIRE_H
#define NORMALFIRE_H
#include"Fire.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "LTexture.h"

using namespace std;


class NormalFire :public Fire
{
    public:
        enum ANIMATION_FRAMES {FLYING_FRAMES = 2};
        SDL_Rect spriteClips[ FLYING_FRAMES ];
        LTexture* spriteSheetTexture;

    public:
        NormalFire(LTexture* image, float x, float y);
        NormalFire();
        virtual ~NormalFire();
        virtual void Move();
        virtual void Render(long int frame, SDL_Renderer* gRenderer);
};


#endif // NORMALFIRE_H
