#ifndef MissileFire_H
#define MissileFire_H
#include"Fire.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "LTexture.h"

using namespace std;


class MissileFire :public Fire
{
    public:

        enum ANIMATION_FRAMES {FLYING_FRAMES = 1};
        SDL_Rect spriteClips[ FLYING_FRAMES ];
        LTexture* spriteSheetTexture;
    public:
        MissileFire(LTexture* image, float x, float y);
        MissileFire();
        virtual ~MissileFire();
        virtual void Move();
        virtual void Render(long int frame, SDL_Renderer* gRenderer);
};


#endif // MissileFire_H
