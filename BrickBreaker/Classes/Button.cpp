#include"Button.h"
#include"Point.h"
#include<SDL.h>
#include<iostream>

Button::Button()
{
    isClicked = false;
}

Button::~Button()
{
    //dtor
}

Button::Button(std::string str, Point p, LTexture* fontTexture, LTexture* buttonTexture,ButtonColorType colorType){
    this->word = Word(fontTexture, p.x, p.y, str);
    this->buttonTexture = buttonTexture;
    this->center = p;
    this->color = colorType;
    isClicked = false;
}

void Button::Draw(SDL_Renderer* gRenderer){
    int length = this->word.length;
    int wordWidth = length*40;
    if (isClicked==true){
        SDL_Rect spriteClipLeft = {80+(((int)color)*160), 0, 20, 60};
        SDL_Rect spriteClipRight = {140+(((int)color)*160), 0, 20, 60};
        SDL_Rect spriteClipMiddle = {100+(((int)color)*160), 0, 40, 60};
        int x = center.x - wordWidth/2 - 20;
        int y = center.y - 30;
        buttonTexture->Render( x, y, &spriteClipLeft, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
        x += 20;
        for(int i = 0; i<length ; i++){
            buttonTexture->Render( x, y, &spriteClipMiddle, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
            x += 40;
        }
        buttonTexture->Render( x, y, &spriteClipRight, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
        this->word.Render(gRenderer, true);
    }else{
        SDL_Rect spriteClipLeft = {0+(((int)color)*160), 0, 20, 60};
        SDL_Rect spriteClipRight = {60+(((int)color)*160), 0, 20, 60};
        SDL_Rect spriteClipMiddle = {20+(((int)color)*160), 0, 40, 60};
        int x = center.x - wordWidth/2 - 20;
        int y = center.y - 30;
        buttonTexture->Render( x, y, &spriteClipLeft, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
        x += 20;
        for(int i = 0; i<length ; i++){
            buttonTexture->Render( x, y, &spriteClipMiddle, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
            x += 40;
        }
        buttonTexture->Render( x, y, &spriteClipRight, 0.0, NULL, SDL_FLIP_NONE, gRenderer );
        this->word.Render(gRenderer, true);
        }
    }
void Button::shiftOriginToCenter(){
    int length = this->word.length;
    int wordWidth = length*40;
    this->center.y += 30;
    this->center.x += (wordWidth/2)+20;
    word.x = this->center.x+20;
    word.y = this->center.y;
}
bool Button::pointLiesInBounds(int x, int y){
    int length = this->word.length;
    int wordWidth_2 = length*20;
    bool isInXRange = x > center.x-wordWidth_2-20 && x < center.x+wordWidth_2+20;
    bool isInYRange = y > center.y-30 && y < center.y+30;
    return isInXRange && isInYRange;
}
void Button::setIsClicked(bool flag){
    isClicked = flag;
}
bool Button::getIsClicked(){
    return isClicked;
}
