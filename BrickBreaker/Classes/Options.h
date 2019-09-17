#ifndef Options_H_INCLUDED
#define Options_H_INCLUDED

#include "ScreenManager.h"
#include "Button.h"
#include "Statics.h"

class Options: public Pop_Up
{
    public:
        Options();
        Options(SDL_Renderer* renderer);
        void show();
        void click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer);
        void keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer);
        ~Options();

    private:
        Button resume;
        Button save;
        Button restart;
        Button quit;
        LTexture gSpriteSheetTexture;
        LTexture backSpriteSheetTexture;
        LTexture buttonSpriteTexture;
        Mix_Music *gMusic = NULL;
        Mix_Chunk *gScratch = NULL;

    protected:
        bool loadMedia();
};

#endif
