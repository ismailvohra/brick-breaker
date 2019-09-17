#ifndef LEVELCOMPLETE_H_INCLUDED
#define LEVELCOMPLETE_H_INCLUDED

#include "ScreenManager.h"
#include "Button.h"
#include "Statics.h"

class LevelComplete: public Pop_Up
{
    public:
        LevelComplete();
        LevelComplete(SDL_Renderer* renderer);
        void show();
        void click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer);
        void keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer);
        ~LevelComplete();

    private:
        Button restart;
        Button nextLevel;
        Button quit;
        Mix_Chunk *gScratch = NULL;
        Mix_Chunk *gamewon = NULL;
        LTexture gSpriteSheetTexture;
        LTexture backSpriteSheetTexture;
        LTexture buttonSpriteTexture;
    protected:
        bool loadMedia();
};


#endif // LEVELCOMPLETE_H_INCLUDED
