#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"
#include"Statics.h"


#ifndef OBJECT_H_
#define OBJECT_H_



class Object {
public:
    Object();
    Object(SDL_Renderer* renderer);
    virtual ~Object(); //destroys all child class
    float x, y, width, height; //position and width and height
    MovingObjectType objectType;
    virtual void Render(long int frame, SDL_Renderer* renderer)=0; //Renders object
    virtual void Move()=0; //virtual abstract functions to move

protected:
    SDL_Renderer* renderer;

};

#endif
