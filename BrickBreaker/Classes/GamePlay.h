#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "Bat.h"
#include "Ball.h"
#include "Board.h"
#include "LTexture.h"
#include "Statics.h"
#include "Board.h"
#include "Object.h"
#include "ScreenManager.h"
#include "Fire.h"
#include "q.h"
#include <SDL_mixer.h>
#include "Pop-Up.h"
#include "PowerUps.h"

#include <typeinfo>



class GamePlay : public ScreenManager
{
public:
        //levels, lives, and loading from savedInstance
        GamePlay(SDL_Renderer* gRenderer, int levelNumber, int lifeCount = 3);
        GamePlay(SDL_Renderer* gRenderer, Queue* qu, Board* board, LTexture* backTexture, LTexture* batBallTexture, LTexture* buttonSprite, LTexture* fontSprite, LTexture* PowerSpriteSheet, int levelNumber, int lifeCount = 3);
        GamePlay(SDL_Renderer* renderer, ShapeLevel levelShape, int lifeCount = 3);
        void show(long int frame);
        void click(int x, int y, MouseEventType eventType, ScreenManager** selfPointer);
        void keyboardEvent(const Uint8* event, ScreenManager** selfPointer); //keyboard events
        ~GamePlay();
        Board* getBoard() const;
        Ball* getBall() const;
        SDL_Rect getBoardBounds();
        void CreateLevel(int);
        int getCurrentLevel() const;
        void CreateLevel(ShapeLevel);
        int getLives() const;
        node* getQHead() const;
    private:
        void init();
        int lives;
        int levelNumber;
        bool isPaused;
        bool loadMedia();
        bool loadSounds();
        void updateLifeButton();
        void allBallOperations(node* ballNode);

        //all the spites
        LTexture* backgroundSprite;
        LTexture* batBallSpriteSheet;
        LTexture* PowerSpriteSheet;
        LTexture* buttonSprite;
        LTexture* fontSprite;
        bool shoot;

        Board* board;

        Queue* q;
        int count = 0;

        SDL_Rect side1;
        SDL_Rect side2;
        SDL_Rect side3;

        Pop_Up* popup;
        Button life;

        float x, y, width, height;

        //collision detection functions
        bool detectCollisionBetween(Bat*, Ball*);
        bool detectCollisionBetween(Bat*, PowerUps*);
        CollisionType detectCollisionBetween(const SDL_Rect& wall, Ball*);
        CollisionType detectCollisionWithSides(Ball*);
        bool isBallAlive(Ball*);

        Mix_Chunk* medium;
        Mix_Chunk* powers;
        Mix_Chunk* smash;
        Mix_Chunk* missi;
        Mix_Chunk* fir;
        bool holdball;
        bool blast;
        bool mball;
        bool mismake;
        bool firemake;
        bool MisActivate;
        bool FireActivate;
        bool ThroughActivate;
        bool NormalActivate;
        bool IspeedActivate;
        bool dspeedActivate;
        bool BigbActivate;
        bool SmallbActivate;
        bool isObjectAlive(Object* ball);
};

#endif // GAMEPLAY_H
