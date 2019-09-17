#include "Bat.h"
#include "Board.h"

Bat* Bat::instance = NULL;

Bat* Bat::GetInstance()
{
    if (!(instance))
        instance = new Bat();
    return instance;
}
Bat::~Bat()
{
    spriteSheetTexture = NULL;
}


void Bat::SetValue(LTexture* image, float x, float y)
{
    spriteSheetTexture = image;


    //Frame 0
    spriteClips3[ 0 ].x =   15;
    spriteClips3[ 0 ].y =   250;
    spriteClips3[ 0 ].w = 75;
    spriteClips3[ 0 ].h = 30;



    spriteClips[ 0 ].x =   0;
    spriteClips[ 0 ].y =   280;
    spriteClips[ 0 ].w = 115;
    spriteClips[ 0 ].h = 30;

    spriteClips2[ 0 ].x =   0;
    spriteClips2[ 0 ].y =   320;
    spriteClips2[ 0 ].w = 140;
    spriteClips2[ 0 ].h = 30;



    this->x = x;
    this->y = y;
    this->smallwidth= spriteClips3[0].w;
    this->bigwidth= spriteClips2[0].w;
    this->normalwidth= spriteClips[0].w;

    this->width = spriteClips[ 0 ].w;
    this->height = spriteClips[ 0 ].h;

    //friction = 0.01f;
    speedx = 0;
    speedy = 0;
    //alive  = true;
}




void Bat::Move(int direction)
{

    if(direction==LEFT )
    {
        speedx = -10;
        x=x+speedx;
    }

    if(direction==RIGHT)
    {
        speedx = 10;
        x=x+speedx;
    }


}

void Bat::Move(){}


void Bat::Render(long int frame, SDL_Renderer* gRenderer)
{
    spriteSheetTexture->Render( x - width/2, y - height/2, width == normalwidth ? &spriteClips[0] : (width == bigwidth ? &spriteClips2[0] : &spriteClips3[0]), 0.0, NULL, SDL_FLIP_NONE, gRenderer );
    SDL_SetRenderDrawColor( gRenderer,255,0,0, 255 );
}

