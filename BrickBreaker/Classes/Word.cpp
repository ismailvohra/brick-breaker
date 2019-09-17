
#include<string>
#include <iostream>
#include"LTexture.h"
#include"Character.h"
#include"Word.h"
Word::Word(LTexture* image, float x, float y, std::string str)
{


    this->str = str;
    this->length = str.length();
    this->chars = new Character[length];
    this->x =x;
    this->y =y;
    spriteSheetTexture = image;
    for(int i = 0; i<length; i++){
        chars[i] = Character(spriteSheetTexture, (float)(x-(length*20)+(i*40)), (float)(y)-30, this->str[i]);
    }
}
Word::Word(){
    chars = NULL;
    length = 0;
    x = 0.0f;
    y=0.0f;
    spriteSheetTexture = NULL;
    str = "";
}
Word::~Word(){
    if(chars){
        delete chars;
    }
    chars = NULL;
    spriteSheetTexture = NULL;
}
void Word::Render(SDL_Renderer* gRenderer, bool debug)
{
    int a = length;
    for (int i=0;i<length;i++)
    {
        chars[i].Render(gRenderer, true);
    }
}
