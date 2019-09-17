#include "PowerUps.h"
#include "string"
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <sstream>
PowerUps::PowerUps(LTexture* image, int x, int y)
{
    this->objectType = ObjectPowerType;
    powerType  = static_cast<PowerType>(rand() % 11);
    spriteSheetTexture = image;

    this->x = x;
    this->y = y;

    this->width = 36;
    this->height = 36;

    friction = 0.50f;
    speedy = 3;
    alive  = true;
}


PowerUps::~PowerUps()
{
    spriteSheetTexture = NULL;
}




void PowerUps::Move()
{
    y+=speedy;
}

void PowerUps::Render(long int frame, SDL_Renderer* gRenderer)
{
    int powerX = powerType;
    int powerY = 0;
    if(powerType > 8){
        powerX = powerType-9;
        powerY = 2;
    }else if(powerType > 4){
        powerX = powerType-5;
        powerY = 1;
    }
    SDL_Rect destRect = {2+(40*powerX), 2+(40*powerY), (int)width, (int)height};
    spriteSheetTexture->Render( (int)(x - width/2), (int)(y - height/2), &destRect, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
}
