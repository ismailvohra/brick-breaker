#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Statics.h"

class ScreenManager
{
    public:
        ScreenManager();
        ScreenManager(SDL_Renderer* renderer);
        virtual void show(long int frame) = 0;
        virtual void click(int x, int y, MouseEventType eventType, ScreenManager** selfPointer) = 0;
        virtual void keyboardEvent(const Uint8* event, ScreenManager** selfPointer) = 0;
        virtual ~ScreenManager();

    protected:
        SDL_Renderer* renderer;


};

#endif // SCREENMANAGER_H
