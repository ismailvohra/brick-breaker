#include "NormalFire.h"
#include "Fire.h"

NormalFire::NormalFire(LTexture* image, float x, float y)
{
    this->objectType = ObjectFireType;
    spriteSheetTexture = image;


    spriteClips[ 0 ].x =   196;
    spriteClips[ 0 ].y =   290;
    spriteClips[ 0 ].w = 24;
    spriteClips[ 0 ].h = 24;


    //Frame 1
    spriteClips[ 1 ].x = 230 ;
    spriteClips[ 1 ].y =   290;
    spriteClips[ 1 ].w = 24;
    spriteClips[ 1 ].h = 24;

    this->x = x;
    this->y = y;

    this->width = spriteClips[ 0 ].w;
    this->height = spriteClips[ 0 ].h;

    //alive  = true;
}


NormalFire::~NormalFire()
{
    spriteSheetTexture = NULL;
}


void NormalFire::Move()
{

     //speedy = speedy * friction;

        speedy = -5;
        y+=speedy;
//    }

        //speedx = speedx * friction;
       // x = x + speedx;
//
//
//            y = y + speedy;
}

void NormalFire::Render(long int frame, SDL_Renderer* gRenderer)
{
    spriteSheetTexture->Render( x - width/2, y - height/2, &spriteClips[ frame % FLYING_FRAMES ], 0.0, NULL, SDL_FLIP_NONE, gRenderer );
}
