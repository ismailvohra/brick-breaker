#include"Character.h"
#include<iostream>

Character::Character()
{
    width = 40;
    height = 42;
    character_value = 0;
    number_value=0;
}
Character::~Character(){
    //dtor
}
Character::Character(LTexture* image, float x, float y, char i)
{
    spriteSheetTexture = image;
    int a= int(i);
    character_value = a-65;
    number_value=a-48;
    lowerChar_value=a-97;
    if (character_value<26 && character_value>-1)
    {
        for (int i=-1; i<character_value*40;i=i+40)
        {
            spriteClips.x = i;
            spriteClips.y = 5;
            spriteClips.w = 40;
            spriteClips.h = 60;
        }
    }
    if (lowerChar_value<26 && lowerChar_value>-1)
    {
        for (int i=-1; i<lowerChar_value*40;i=i+40)
        {
            spriteClips.x = i;
            spriteClips.y = 132;
            spriteClips.w = 40;
            spriteClips.h = 60;
        }
    }
    if (number_value<10 && number_value>-1)
    {
        for (int i=-1; i<number_value*40;i=i+40)
        {
            spriteClips.x = i;
            spriteClips.y = 65;
            spriteClips.w = 40;
            spriteClips.h = 60;
        }
    }
    if (a==46)
    {
        spriteClips.x = 600;
        spriteClips.y = 67;
        spriteClips.w = 40;
        spriteClips.h = 60;
    }
    if (a==58)
    {
        spriteClips.x = 640;
        spriteClips.y = 65;
        spriteClips.w = 40;
        spriteClips.h = 60;
    }
    if (a==32)
    {
        spriteClips.x = 400;
        spriteClips.y = 65;
        spriteClips.w = 40;
        spriteClips.h = 60;
    }
    position.x = x;
    position.y = y;

    this->width = spriteClips.w;
    this->height = spriteClips.h;
}

void Character::Render(SDL_Renderer* gRenderer, bool debug)
{

    spriteSheetTexture->Render( position.x, position.y, &spriteClips, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
//    if(debug == true)
//    {
//        SDL_Rect rect = { position.x - width/2, position.y - height/2, width, height };
//        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//        SDL_RenderDrawRect( gRenderer, &rect );
//    }
}

void Character::SetPosition(Point& position)
{
    this->position.x = position.x - width/2;
    this->position.y = position.y - height/2;
}

void Character::SetPosition(int x, int y)
{
    this->position.x = x - width/2;
    this->position.y = y - height/2;
}

int Character::GetFrameWidth()
{
    return width;
}
int Character::GetFrameHeight()
{
    return height;
}

