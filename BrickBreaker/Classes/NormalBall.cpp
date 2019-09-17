#include "NormalBall.h"
#include "Ball.h"
#include<math.h>



NormalBall::NormalBall(LTexture* image, float x, float y)
{
    this->objectType = ObjectBallType;
    type = NormalBallType;
    spriteSheetTexture = image;


    //Frame 0
    spriteClips[ 0 ].x = 153.5;
    spriteClips[ 0 ].y = 320;
    spriteClips[ 0 ].w = 24;
    spriteClips[ 0 ].h = 24;

    this->x = x;
    this->y = y;

    this->width = spriteClips[ 0 ].w;
    this->height = spriteClips[ 0 ].h;
    this->shouldMove = false;

    //friction = 0.50f;
    SetDirection(-1,-1);
}


NormalBall::~NormalBall()
{
    spriteSheetTexture = NULL;
}

//void NormalBall::SetAlive(bool alive)
//{
//    this->alive = alive;
//}
//
//bool NormalBall::GetAlive()
//{
//    return alive;
//}



void NormalBall::Move(float x, float y)
{
    this->y += diry*y;
    this->x += dirx*x;
}

void NormalBall::Render(long int frame,SDL_Renderer* gRenderer)
{
    spriteSheetTexture->Render( x - width/2, y - height/2, &spriteClips[0], 0.0, NULL, SDL_FLIP_NONE, gRenderer );
}
void NormalBall::didCollide(CollisionInfo info){
    Ball::didCollide(info);
}
