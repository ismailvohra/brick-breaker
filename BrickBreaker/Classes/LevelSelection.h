#ifndef LEVELSELECTION_H_INCLUDED
#define LEVELSELECTION_H_INCLUDED

#include "ScreenManager.h"
#include "Button.h"
#include "Statics.h"

class LevelSelection: public Pop_Up
{
    public:
        LevelSelection();
        LevelSelection(SDL_Renderer* renderer);
        void show();
        void click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer);
        void keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer);
        ~LevelSelection();

    private:
        Button l1,l2,l3,l4,l5,l6,l7,l8,l9,l10;
        Mix_Chunk *gScratch = NULL;
        Button circleBtn,diamondBtn,waveBtn,backButton;
        LTexture gSpriteSheetTexture;
        LTexture backSpriteSheetTexture;
        LTexture buttonSpriteTexture;
    protected:
        bool loadMedia();
};

#endif // LEVELSELECTION_H_INCLUDED
