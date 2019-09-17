#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED
#include "SDL_mixer.h"
#include "ScreenManager.h"
#include "Button.h"
#include "Statics.h"

class GameOver: public Pop_Up
{
    public:
        GameOver();
        GameOver(SDL_Renderer* renderer);
        void show();
        void click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer);
        void keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer);
        ~GameOver();

    private:
        Button restart;
        Button quit;
        LTexture gSpriteSheetTexture;
        LTexture backSpriteSheetTexture;
        LTexture buttonSpriteTexture;
        Mix_Chunk *over = NULL;
    protected:
        bool loadMedia();
};

#endif // GAMEOVER_H_INCLUDED
