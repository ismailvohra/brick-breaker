#ifndef POP-UP_H_INCLUDED
#define POP-UP_H_INCLUDED

#include "ScreenManager.h"
#include "Button.h"
#include "Statics.h"

class Pop_Up
{
    public:
        Pop_Up(){renderer = NULL;}
        Pop_Up(SDL_Renderer* renderer){this->renderer = renderer;}
        virtual void show()=0;
        virtual void click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer) = 0;
        virtual void keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer) = 0;
        ~Pop_Up(){}

    protected:
        SDL_Renderer* renderer;
        virtual bool loadMedia()=0;
};

#endif // POP-UP_H_INCLUDED
