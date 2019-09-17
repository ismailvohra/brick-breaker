#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"
#include"Point.h"
#include<string>

class Character
{
private:
    Point position;
    int character_value;
    int number_value;
    int lowerChar_value;
    int width;
    int height;
    SDL_Rect spriteClips;
    LTexture* spriteSheetTexture;
public:
    ~Character();
    Character();
    Character(LTexture* image, float x, float y, char i);
    virtual void Render(SDL_Renderer* gRenderer, bool debug);
    void SetPosition(Point&);
    void SetPosition(int, int);
    int GetFrameWidth();
    int GetFrameHeight();


};

