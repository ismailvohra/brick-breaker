#pragma once
#include<string>
#include"Character.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"
#include"Word.h"
#include"Statics.h"

class Button
{
    public:
        Button();
        ~Button();
        Button(std::string, Point, LTexture*, LTexture*, ButtonColorType);
        void Draw(SDL_Renderer*);
        void shiftOriginToCenter();
        bool pointLiesInBounds(int x, int y);
        void setIsClicked(bool flag);
        bool getIsClicked();

    private:
        Word word;
        Point center;
        LTexture* buttonTexture;
        bool isClicked;
        ButtonColorType color;
};
