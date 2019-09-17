#include "GamePlay.h"
#include "Bat.h"
#include "NormalBall.h"
#include "Board.h"
#include<string>
#include "Pop-Up.h"
#include "Options.h"
#include "GameOver.h"
#include "LevelComplete.h"

#include"PowerUps.h"
#include<string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cmath>

#include "windows.h"
#include "FireBall.h"
#include "ThroughBall.h"
#include "NormalFire.h"
#include "MissileFire.h"
#include <SDL_mixer.h>
#include <SDL.h>
#include <sstream>
#include <conio.h>
void GamePlay::init(){
    q = new Queue;
    backgroundSprite = NULL;
    batBallSpriteSheet = NULL;
    PowerSpriteSheet = NULL;
    buttonSprite = NULL;
    fontSprite = NULL;
    board = NULL;
    popup = NULL;
    medium = NULL;
    powers = NULL;
    smash = NULL;
    missi = NULL;
    fir = NULL;
    Mix_HaltMusic();
    shoot = false;
    mismake = false;
    MisActivate = false;
    FireActivate = false;
    ThroughActivate = false;
    NormalActivate = false;
    IspeedActivate = false;
    dspeedActivate = false;
    firemake = false;
    mball = false;
    isPaused = false;
    this->side1.h=650;
    this->side1.w=5;
    this->side1.x=0;
    this->side1.y=0;

    this->side2.h=5;
    this->side2.w=1000;
    this->side2.x=0;
    this->side2.y=0;

    this->side3.h=650;
    this->side3.w=5;
    this->side3.x=1000-5;
    this->side3.y=0;

    srand(time(0));

    x = 24;
    y = 65;
    width = 768;
    height = 600;
}

GamePlay::GamePlay(SDL_Renderer* renderer, int levelNumber, int lifeCount)
{
    init();
    this->lives = lifeCount;
    this->renderer = renderer;
    loadMedia();
    loadSounds();

    Bat* bat = Bat::GetInstance();
    bat->SetValue(batBallSpriteSheet, (float)SCREEN_WIDTH/2, 630);
    Ball* ball = new NormalBall(batBallSpriteSheet, bat->x, bat->y-24);
    q->Enqueue(ball);

    this->levelNumber = levelNumber;
    CreateLevel(levelNumber);
    updateLifeButton();
    Bat::GetInstance()->width = Bat::GetInstance()->normalwidth;

}
GamePlay::GamePlay(SDL_Renderer* renderer, ShapeLevel levelShape, int lifeCount)
{
    init();
    this->lives = lifeCount;
    this->renderer = renderer;
    loadMedia();
    loadSounds();

    Bat* bat = Bat::GetInstance();
    bat->SetValue(batBallSpriteSheet, (float)SCREEN_WIDTH/2, 630);
    Ball* ball = new NormalBall(batBallSpriteSheet, bat->x, bat->y-24);
    q->Enqueue(ball);

    this->levelNumber = levelShape*-1;
    CreateLevel(levelShape);
    updateLifeButton();
    Bat::GetInstance()->width = Bat::GetInstance()->normalwidth;

}
GamePlay::GamePlay(SDL_Renderer* gRenderer, Queue* qu, Board* board, LTexture* backTexture, LTexture* batBallTexture, LTexture* buttonSprite, LTexture* fontSprite, LTexture* PowerSpriteSheet, int levelNumber, int lifeCount){

    init();
    this->lives = lifeCount;
    this->levelNumber = levelNumber;
    this->renderer = gRenderer;
    loadSounds();
    this->backgroundSprite = backTexture;
    this->batBallSpriteSheet = batBallTexture;
    this->fontSprite = fontSprite;
    this->buttonSprite = buttonSprite;
    this->PowerSpriteSheet = PowerSpriteSheet;
    this->board = board;

    delete this->q;
    (this->q) = qu;
    updateLifeButton();

    x = board->x;
    y = board->y;
    width = board->width;
    height = board->height;
    Bat::GetInstance()->width = Bat::GetInstance()->normalwidth;
    isPaused = true;
}



GamePlay::~GamePlay(){
    if (backgroundSprite) backgroundSprite->Free();
    if (batBallSpriteSheet) batBallSpriteSheet->Free();
    if (PowerSpriteSheet) PowerSpriteSheet->Free();
    if (buttonSprite) buttonSprite->Free();
    if (fontSprite) fontSprite->Free();
    if (q) delete q;
    if (board) delete board;

    backgroundSprite = NULL;
    batBallSpriteSheet = NULL;
    PowerSpriteSheet = NULL;
    buttonSprite = NULL;
    fontSprite = NULL;
    board = NULL;
    popup = NULL;
    medium = NULL;
    powers = NULL;
    smash = NULL;
    missi = NULL;
    fir = NULL;
}






void GamePlay::show(long int frame)
{
    //Rendering Background
    backgroundSprite->Render(0,0,0,0.0,NULL, SDL_FLIP_NONE, renderer);
    //Rendering Sides
    SDL_SetRenderDrawColor( renderer,100,100,100,255);
    SDL_RenderFillRect(renderer,&(this->side1));
    SDL_RenderFillRect(renderer,&(this->side2));
    SDL_RenderFillRect(renderer,&(this->side3));

    //Rendering Bat
    Bat::GetInstance()->Render(frame, renderer);

    //Rendering Bricks
    board->Display(renderer);
    if(board->isLevelComplete()){
        if(!popup){
            popup = new LevelComplete(renderer);
        }
    }

    //Rendering all Moving Objects including Ball
    q->Render(frame,renderer);

    bool isPaused = popup != NULL;
    if(!isPaused){
        q->Move();
    }

    if (mismake)
    {
        Fire* fire =  new MissileFire(batBallSpriteSheet, Bat::GetInstance()->x, Bat::GetInstance()->y-23);
        q->Enqueue(fire);
        Mix_PlayChannel( -1,missi, 0 );
        MisActivate = true;
    }
    if (frame%10 ==0 && count<10 && firemake )
    {
        Fire* fire = new NormalFire(batBallSpriteSheet, Bat::GetInstance()->x, Bat::GetInstance()->y-23);
        Mix_PlayChannel( -1, fir, 0 );
        q->Enqueue(fire);
        count++;
        blast = true;
    }
    Fire* fire = NULL;
    node* qHead = q->getHead();
    bool liveBallFound = false;
    while(qHead){
        node* temp = qHead->next;
        if(!qHead->unit){
            qHead = temp;
            continue;
        }
        switch(qHead->unit->objectType){
        case ObjectBallType:
            if(isBallAlive(dynamic_cast<Ball*>(qHead->unit))){
                liveBallFound = true;
            }
            allBallOperations(qHead);
            break;
        case ObjectMissileType:
        case ObjectFireType:
            fire = dynamic_cast<Fire*>(qHead->unit);
            if(board->detectCollisionWithBricks(Point((int)fire->x - fire->width/2, (int)fire->y - fire->height/2), (fire->objectType == ObjectFireType ? (NormalFireType) : (MissileFireType)))){
                if(temp){
                    qHead->next->prev = qHead->prev;
                }else{
                    q->bringTailBack();
                }
                if(qHead->prev){
                    qHead->prev->next = temp;
                }else{
                    q->moveHeadAhead();
                }
                delete qHead;
                qHead = NULL;
            }else
            if(!isObjectAlive(fire)){
                if(temp){
                    qHead->next->prev = qHead->prev;
                }else{
                    q->bringTailBack();
                }
                if(qHead->prev){
                    qHead->prev->next = temp;
                }else{
                    q->moveHeadAhead();
                }
                delete qHead;
            }
            break;
        case ObjectPowerType:
            PowerUps* power = dynamic_cast<PowerUps*>(qHead->unit);

            if(detectCollisionBetween(Bat::GetInstance(), power))
            {
                Mix_PlayChannel( -1, powers, 0 );
                switch(power->powerType)
                {
                    case PowerThroughBall: ThroughActivate=true;break;
                    case PowerFireBall: FireActivate=true;break;
                    case PowerMultiBall: mball=true;break;
                    case PowerFastBall: IspeedActivate=true;break;
                    case PowerSlowBall: dspeedActivate=true;break;
                    case PowerShrinkBat: Bat::GetInstance()->width = Bat::GetInstance()->smallwidth;break;
                    case PowerExpandBat: Bat::GetInstance()->width = Bat::GetInstance()->bigwidth;break;
                    case PowerMissile: mismake=true;break;
                    case PowerFire: firemake=true;break;
                    case PowerBomb: lives--; updateLifeButton(); break;
                    case PowerLife: lives++; updateLifeButton(); break;
                }
                if(temp){
                    qHead->next->prev = qHead->prev;
                }else{
                    q->bringTailBack();
                }
                if(qHead->prev){
                    qHead->prev->next = temp;
                }else{
                    q->moveHeadAhead();
                }
                delete qHead;
                qHead = NULL;
            }else
            if(!isObjectAlive(power)){
                if(temp){
                    qHead->next->prev = qHead->prev;
                }else{
                    q->bringTailBack();
                }
                if(qHead->prev){
                    qHead->prev->next = temp;
                }else{
                    q->moveHeadAhead();
                }
                delete qHead;
            }
            break;
        }
        qHead = temp;
    }
    if(!liveBallFound){
        lives--;
        if(lives>=0){
            Ball* ball = new NormalBall(batBallSpriteSheet, Bat::GetInstance()->x, Bat::GetInstance()->y-24);
            q->Enqueue(ball);
        }
        updateLifeButton();
    }

    node* qHead2 = q->getHead();
    node* qTail = q->getTail();
    while(true){
        if(!qHead2){
            break;
        }
        node* temp = qHead2->next;
        if(!qHead2->unit){
            if(qHead2 == qTail){
                break;
            }
            qHead2 = temp;
            continue;
        }
        if(qHead2->unit->objectType == ObjectBallType){
            Ball* ball = dynamic_cast<Ball*>(qHead2->unit);
            if(IspeedActivate)
            {
                ball->BALL_SPEED = 15;
            }
            if (dspeedActivate)
            {
                ball->BALL_SPEED = 5;
            }
            if(mball){
                Ball* newBall = ball->multiplyBall(batBallSpriteSheet);
                q->Enqueue(newBall);
            }
        }
        if(qHead2 == qTail){
            break;
        }
        qHead2 = temp;
    }
    mball = false;
    IspeedActivate = false;
    dspeedActivate = false;
    mball = false;

    shoot = false;
    if (MisActivate)
    {
        mismake = false;
    }

    if(isPaused){
        popup->show();
    }
    life.Draw(renderer);
}


void GamePlay::CreateLevel(int LevelNumber) {
    board = new Board(x, y, width, height, renderer);

    std::string content;
    std::stringstream ss;
    ss << LevelNumber;
    std::string str = ss.str();

    std::string filename = "Levels/" + str + ".txt";

	//opening file
    std::ifstream readfile;
    readfile.open(filename.c_str());
    int j = 0;
    while (getline(readfile, content) && j <= BOARD_HEIGHT)
    {
        for(int i=0; i<content.length(); i++)
        {
            if((i)==BOARD_WIDTH)
            {
                break;
            }
            Brick* brick = new Brick();
            brick->state = true;
            int bricktype = atoi(content.substr(i, 1).c_str());
            brick->type=rand()%3;
            brick->breaktype=bricktype;
            if(content[i]=='3')
            {
                brick->breaktype = 0;
                brick->type=3;
            }else
            if(content[i]!='0' && bricktype == 0)
            {
                continue;
            }
            board->Enqueue(brick, i, j);
        }
        j++;
    }
}
void GamePlay::click(int x, int y, MouseEventType eventType, ScreenManager** selfPointer){
    if(popup){
        popup->click(x,y,eventType,selfPointer, &popup);
        return;
    }
}

void GamePlay::keyboardEvent(const Uint8* event, ScreenManager** selfPointer){
    if(event[ SDL_SCANCODE_SPACE ]){
        shoot = true;
        isPaused = false;
    }
    if(event[ SDL_SCANCODE_M ]){
        if(!mball){
            mball = true;
        }
    }
    if(event[ SDL_SCANCODE_P ]){
        if(!popup){
            popup = new Options(this->renderer);
        }
    }
    if((event[ SDL_SCANCODE_RIGHT ] || event[ SDL_SCANCODE_LEFT ]) && !isPaused){
        MOTION direction = event[ SDL_SCANCODE_RIGHT ] ? RIGHT : LEFT;
        if(event[ SDL_SCANCODE_RIGHT ]){
            if(Bat::GetInstance()->x+Bat::GetInstance()->width/2>=this->side3.x || popup){return;}
            Bat::GetInstance()->Move(RIGHT);
        }
        if(event[ SDL_SCANCODE_LEFT ]){
            if (Bat::GetInstance()->x-Bat::GetInstance()->width/2<=this->side1.x+this->side1.w || popup){return;}
            Bat::GetInstance()->Move(LEFT);
        }
        node* qHead = q->getHead();
        while(qHead){
            node* temp = qHead->next;
            if(!qHead->unit){
                qHead = temp;
                continue;
            }
            if(qHead->unit->objectType == ObjectBallType){
                Ball* ball = dynamic_cast<Ball*>(qHead->unit);
                if(!ball->shouldMove){
                    ball->x += direction == RIGHT ? 10 : -10;
                }
            }
            qHead = temp;
        }

    }
    if(popup){
        popup->keyboardEvent(event,selfPointer, &popup);
        return;
    }
}

node* GamePlay::getQHead() const{
    return q->getHead();
}

void GamePlay::allBallOperations(node* ballNode){
    Ball* ball = dynamic_cast<Ball*>(ballNode->unit);
    bool shouldDeleteBall = !isBallAlive(ball);
    if(ball->shouldMove && !shouldDeleteBall){
        CollisionInfo info = board->detectCollisionWithBricks(Point(ball->x - ball->width/2, ball->y - ball->height/2), ball->type, Point(ball->width, ball->height));
        ball->didCollide(info);
        if(info.directionType != None){
            Mix_PlayChannel( -1, smash, 0 );
        }
        if(info.directionType != None && info.objectType == CollisionObjectBreakableBrickType && info.brick){
            if(rand()%100<40){

                PowerUps* power = new PowerUps(PowerSpriteSheet, ball->x, ball->y);
                q->Enqueue(power);
            }
        }
    }

    if(shouldDeleteBall){
        if(ballNode->next){
            ballNode->next->prev = ballNode->prev;
        }else{
            q->bringTailBack();
        }
        if(ballNode->prev){
            ballNode->prev->next = ballNode->next;
        }else{
            q->moveHeadAhead();
        }
        ballNode->unit = NULL;
        delete ballNode;
        ballNode = NULL;
        return;
    }
    if (NormalActivate)
    {
        int speedx = ball->dirx;
        int speedy = ball->diry;
        int x = ball->x;
        int y = ball->y;
        int sp = ball->BALL_SPEED;
        bool shouldMove = ball->shouldMove;
        if(ballNode->next){
            ballNode->next->prev = ballNode->prev;
        }else{
            q->bringTailBack();
        }
        if(ballNode->prev){
            ballNode->prev->next = ballNode->next;
        }else{
            q->moveHeadAhead();
        }
        ballNode->unit = NULL;
        delete ballNode;
        ball = new NormalBall(batBallSpriteSheet, x, y);
        NormalActivate = false;
        ball->dirx = speedx;
        ball->diry = speedy;
        ball->BALL_SPEED = sp;
        ball->shouldMove = shouldMove;
        q->Enqueue(ball);
    }
    if (FireActivate)
    {
        //ThroughActivate = false;
        int speedx = ball->dirx;
        int sp = ball->BALL_SPEED;
        int speedy = ball->diry;
        int x = ball->x;
        int y = ball->y;
        bool shouldMove = ball->shouldMove;
        if(ballNode->next){
            ballNode->next->prev = ballNode->prev;
        }else{
            q->bringTailBack();
        }
        if(ballNode->prev){
            ballNode->prev->next = ballNode->next;
        }else{
            q->moveHeadAhead();
        }
        ballNode->unit = NULL;
        delete ballNode;
        ball = new FireBall(batBallSpriteSheet, x, y);
        FireActivate = false;
        ball->dirx = speedx;
        ball->diry = speedy;
        ball->BALL_SPEED = sp;
        ball->shouldMove = shouldMove;
        q->Enqueue(ball);
    }
    if (ThroughActivate)
    {
        //FireActivate  = false;
        int speedx = ball->dirx;
        int speedy = ball->diry;
        int sp = ball->BALL_SPEED;
        int x = ball->x;
        int y = ball->y;
        bool shouldMove = ball->shouldMove;
        if(ballNode->next){
            ballNode->next->prev = ballNode->prev;
        }else{
            q->bringTailBack();
        }
        if(ballNode->prev){
            ballNode->prev->next = ballNode->next;
        }else{
            q->moveHeadAhead();
        }
        ballNode->unit = NULL;
        delete ballNode;
        ball = new ThroughBall(batBallSpriteSheet, x, y);
        ThroughActivate = false;
        ball->dirx = speedx;
        ball->diry = speedy;
        ball->BALL_SPEED = sp;
        ball->shouldMove = shouldMove;
        q->Enqueue(ball);
    }



    //Code for Ball-Side Collision Detection
    CollisionInfo wallCollision;
    wallCollision.objectType = CollisionObjectWallType;
    wallCollision.directionType = detectCollisionWithSides(ball);
    ball->didCollide(wallCollision);
    if(wallCollision.directionType != None){
        Mix_PlayChannel( -1, medium, 0 );
    }

    //Code for Ball-Bat Collision Detection
    if (detectCollisionBetween(Bat::GetInstance(), ball) && ball->shouldMove){
        Mix_PlayChannel( -1, medium, 0 );
//        Mix_PlayChannel( 1, medium, 0 );
        float ballcenterx = ball->x + ball->width / 2.0f;
        int hitx = ballcenterx - Bat::GetInstance()->x-12;
        if (hitx>0 && hitx<15)
        {
            ball->SetDirection(0.5,-1);
        }
        else if (hitx>15 && hitx<30)
        {
            ball->SetDirection(1,-1);
        }
        else if (hitx>30 && hitx<45)
        {
            ball->SetDirection(1.5,-1);
        }
        else if (hitx>45)
        {
            ball->SetDirection(2,-1);
        }
        else if (hitx<0 && hitx>-15)
        {
            ball->SetDirection(-0.5,-1);
        }
        else if (hitx<-15 && hitx>-30)
        {
            ball->SetDirection(-1,-1);
        }
        else if (hitx<-30 && hitx>-45)
        {
            ball->SetDirection(-1.5,-1);
        }
        else if (hitx<-45)
        {
            ball->SetDirection(-2,-1);
        }
        else
        {
            ball->diry*=-1;
        }
    }
    if(shoot){
        ball->shouldMove = true;
    }
}

bool GamePlay::loadMedia(){
    backgroundSprite = new LTexture();
    batBallSpriteSheet = new LTexture();
    PowerSpriteSheet = new LTexture();
    buttonSprite = new LTexture();
    fontSprite = new LTexture();
    if( !backgroundSprite->LoadFromFile( "Images/bgimage.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if( !batBallSpriteSheet->LoadFromFile( "Images/finalsprites.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if( !PowerSpriteSheet->LoadFromFile( "Images/powerups.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if( !fontSprite->LoadFromFile( "Images/final2.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if(!buttonSprite->LoadFromFile("Images/button.jpg",renderer))
    {
        printf( "Failed to load sprite sheet texture!\n" );
		return false;
    }
}
bool GamePlay::loadSounds(){
    medium= Mix_LoadWAV( "sounds/ball collision.wav" );
	if( medium == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	smash= Mix_LoadWAV( "sounds/brick smash.wav" );
	if( smash== NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	powers= Mix_LoadWAV( "sounds/power up 2.wav" );
	if( powers == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	missi= Mix_LoadWAV( "sounds/Missile.wav" );
	if( missi == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	fir= Mix_LoadWAV( "sounds/fire.wav" );
	if( fir == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	return true;
}
bool GamePlay::detectCollisionBetween(Bat* bat, Ball* ball){
    bool isInXRange = (ball->x+(ball->width) >= bat->x-(bat->width/2)) && (ball->x-(ball->width/2)) <= (bat->x + (bat->width/2));
    float batOriginY = bat->y - bat->height/2;
    float ballMaxY = ball->y + ball->height/2;
    return isInXRange && ballMaxY-batOriginY < ball->BALL_SPEED && ballMaxY-batOriginY >= 0;
}
CollisionType GamePlay::detectCollisionWithSides(Ball* ball){
    CollisionType type = detectCollisionBetween(side2, ball);
    if(type!=None){
        return type;
    }
    type = detectCollisionBetween(side3, ball);
    return type != None ? type : detectCollisionBetween(side1, ball);
}

bool GamePlay::detectCollisionBetween(Bat* bat, PowerUps* powerup){
    if(!powerup || !bat){
        return false;
    }
    bool isInXRange = (powerup->x+(powerup->width) >= bat->x-(bat->width/2)) && (powerup->x-(bat->width/2)) <= (bat->x + (bat->width/2));
    float batOriginY = bat->y - bat->height/2;
    float ballMaxY = powerup->y + powerup->height/2;
    return isInXRange && ballMaxY-batOriginY < powerup->speedy && ballMaxY-batOriginY > -1;
}

CollisionType GamePlay::detectCollisionBetween(const SDL_Rect& wall, Ball* ball){
    //this means the wall is horizontal
    if(wall.w > wall.h){
        if(ball->y-ball->height/2<=wall.y+wall.h){
            return Vertical;
        }
        return None;
    }
    //this means the wall is at the left side of the level.
    if(wall.x-5 < 0){
        if(ball->x-(ball->width/2) <= wall.w){
            return Horizontal;
        }
        return None;
    }
    //if the code reaches here, this means the wall is longitudinal and is at the right side.
    if(ball->x+(ball->width/2) >= wall.x){
        return Horizontal;
    }
    return None;
}
bool GamePlay::isBallAlive(Ball* ball){
    return ball->y-ball->height<=SCREEN_HEIGHT;
}
bool GamePlay::isObjectAlive(Object* ball){
    Point origin(ball->x-ball->width/2, ball->y-ball->height/2);
    Point dest(origin.x+ball->width, origin.y+ball->height);
    return origin.x < SCREEN_WIDTH && origin.y < SCREEN_HEIGHT && dest.x > 0 && dest.y > 0;
}
Board* GamePlay::getBoard() const {
    return board;
}
SDL_Rect GamePlay::getBoardBounds(){
    return {x,y,width,height};
}
int GamePlay::getCurrentLevel() const{
    return levelNumber;
}
void GamePlay::CreateLevel(ShapeLevel shapelevel){
    board = new Board(x, y, width, height, renderer);
    if(shapelevel==circle)
    {
        int circle_radius = 4; // or whatever you want

        for (int i = 0; i <= 2*circle_radius; i++)
        {
            for (int j = 0; j <= 2*circle_radius; j++)
            {
                float distance_to_centre = sqrt((i - circle_radius)*(i - circle_radius) + (j - circle_radius)*(j - circle_radius));
                if (distance_to_centre > circle_radius-0.5 && distance_to_centre < circle_radius+0.5)
                {
                     int bricktype = rand()%2;
                    Brick* brick = new Brick;
                    brick->type=rand()%3;
                    brick->breaktype=bricktype;
                    brick->state = true;
                    board->Enqueue(brick, 3+j, i);
                }
                else
                {
                     continue;
                }
            }
            continue;
        }
    }
    else if(shapelevel==diamond)
    {
        int n, c, k, space = 1;
        n=5;
        space = n - 1;
        for (k = 1; k<=n; k++)
        {
            space--;

            for (c = 1; c<= 2*k-1; c++)
                cout<<"";
            for(int i=1; i<c; i++)
            {
                int bricktype = rand()%2;
                Brick* brick = new Brick;
                brick->type=rand()%3;
                brick->breaktype=bricktype;
                brick->state = true;
                board->Enqueue(brick, space+i+3, k-1);
            }
        }

        space = 1;

        for (k = 1; k<= n - 1; k++)
        {
            space++;

            for (c = 1 ; c<= 2*(n-k)-1; c++)
                cout<<"";
            for(int i=1; i<c; i++)
            {
                int bricktype = rand()%2;
                Brick* brick = new Brick;
                brick->type=rand()%3;
                brick->breaktype=bricktype;
                brick->state = true;
                board->Enqueue(brick, space+i-2+3, k+n-1);
            }
        }
    }
    else if(shapelevel==wave)
    {
        string s;
        int n = 5;
        int len = 15;

        //Generate String
        for (int i=0; i<len; i++)
        {
            s[i]='*';
        }
        // Create a 2d character array
        char a[len][len] = { };

        // for counting the rows of the ZigZag
        int row = 0;
        bool down;

        for (int i=0; i<len; i++)
        {
            // put characters in the matrix
            a[row][i] = s[i];

            // You have reached the bottom
            if (row==n-1)
                down = false;
            else if (row==0)
                down = true;

            (down)?(row++):(row--);
        }

        // Print the Zig-Zag String
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<len; j++)
            {
                if(a[i][j]=='*')
                {
                    Brick* brick = new Brick;
                    brick->type=rand()%3;
                    brick->breaktype=rand()%2;
                    brick->state = true;
                    board->Enqueue(brick, j, i);
                }
            }
            //cout<<endl;
        }
    }
}
int GamePlay::getLives() const{
    return lives;
}
void GamePlay::updateLifeButton() {
    int lifeCount = lives < 0 ? 0 : lives;
    std::string content;
    std::stringstream ss;
    ss << lifeCount;
    std::string str = ss.str();
    std::string livesSS = "Life: " + str;
    if(lives<0){
        if(!popup){
            popup = new GameOver(renderer);
        }
    }
    life = Button(livesSS, {(float)SCREEN_WIDTH - (20*(livesSS.length()+1)) - 5, (float)(35.0)}, fontSprite, buttonSprite, Life);
}
