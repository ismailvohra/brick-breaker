#include "MissileFire.h"
#include "Fire.h"

MissileFire::MissileFire(LTexture* image, float x, float y)
{
    this->objectType = ObjectMissileType;
    spriteSheetTexture = image;


    spriteClips[ 0 ].x =   300;
    spriteClips[ 0 ].y =   290;
    spriteClips[ 0 ].w = 24;
    spriteClips[ 0 ].h = 30;


    //Frame 1

    this->x = x;
    this->y = y;

    this->width = spriteClips[ 0 ].w;
    this->height = spriteClips[ 0 ].h;

    //alive  = true;
}


MissileFire::~MissileFire()
{
    spriteSheetTexture = NULL;
}

//void MissileFire::SetAlive(bool alive)
//{
//    this->alive = alive;
//}
//
//bool MissileFire::GetAlive()
//{
//    return alive;
//}


void MissileFire::Move()
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

void MissileFire::Render(long int frame, SDL_Renderer* gRenderer)
{
    spriteSheetTexture->Render( x - width/2, y - height/2, &spriteClips[ frame % FLYING_FRAMES ], 0.0, NULL, SDL_FLIP_NONE, gRenderer );
}
