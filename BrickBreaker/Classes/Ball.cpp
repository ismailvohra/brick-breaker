#include "Ball.h"
#include"NormalBall.h"
#include"ThroughBall.h"
#include"FireBall.h"
#include<math.h>

void Ball::SetDirection(float dirx, float diry)
{
    float length = sqrt(dirx * dirx + diry * diry);
    this->dirx = BALL_SPEED * (dirx / length);
    this->diry = BALL_SPEED * (diry / length);
}
void Ball::Move(){
    if(shouldMove){
        Move(1,1);
    }
}
Ball* Ball::multiplyBall(LTexture* image){
    Ball* ball = NULL;
    if(this->type == NormalBallType){
        ball = new NormalBall(image, this->x, this->y);
    }else if(this->type == ThroughBallType){
        ball = new ThroughBall(image, this->x, this->y);
    }else{
        ball = new FireBall(image, this->x, this->y);
    }
    ball->BALL_SPEED = BALL_SPEED;
    ball->shouldMove = shouldMove;
    ball->type = type;
    ball->diry = diry;
    ball->dirx = dirx*-1;
    return ball;
}
void Ball::didCollide(CollisionInfo info){
    if(info.directionType == None){
        return;
    }
    if(info.objectType == CollisionObjectBreakableBrickType || info.objectType == CollisionObjectUnbreakableBrickType || info.objectType == CollisionObjectWallType)
        {
            if (info.directionType == Vertical)
            {
                diry *= -1;
            }
            else
            {
                dirx *= -1;
            }
            this->Move();
        }
}

