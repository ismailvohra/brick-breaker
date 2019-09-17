#include "Pop-Up.h"
#include "Button.h"
#include "GamePlay.h"
#include "Menu.h"
#include "GameOver.h"
#include <iostream>

GameOver::GameOver(){

    renderer = NULL;
}
GameOver::GameOver(SDL_Renderer* renderer){
    //Mix_PlayChannel( -1, over, 0 );
    this->renderer = renderer;
    if(loadMedia()){
        restart = Button("Restart", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)-50}, &gSpriteSheetTexture, &buttonSpriteTexture, Red);
        quit = Button(" Quit ", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)+20}, &gSpriteSheetTexture, &buttonSpriteTexture, Red);
    }else{
        std::cout<<"Error loading media in Pop-up class";
    }

}
void GameOver::show()
{
     Mix_PlayChannel( -1, over, 0 );
    backSpriteSheetTexture.Render(275,80,0,0.0,NULL,SDL_FLIP_NONE,renderer);
    restart.Draw(renderer);
    quit.Draw(renderer);
}
void GameOver::click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer){
    if(eventType == ClickDown){
        if(restart.pointLiesInBounds(x,y)){
            restart.setIsClicked(true);
            std::cout<<"Restart Button Down"<<std::endl;
        }else if(quit.pointLiesInBounds(x,y)){
            quit.setIsClicked(true);
            std::cout<<"Quit Button Down"<<std::endl;
        }
    }else if(eventType == ClickUp){
        if(restart.pointLiesInBounds(x,y) && restart.getIsClicked()){
            std::cout<<"Restart Button Up"<<std::endl;
            GamePlay* gamePlay = dynamic_cast<GamePlay*>(*parentPointer);
            int currentLevel = gamePlay->getCurrentLevel();
            delete *parentPointer;
            if(currentLevel>0){
                *parentPointer = new GamePlay(this->renderer, currentLevel);
                delete this;
            }else{
                ShapeLevel shapeLevel = static_cast<ShapeLevel>(currentLevel*-1);
                *parentPointer = new GamePlay(this->renderer, shapeLevel);
                delete this;
            }
        }else if(quit.pointLiesInBounds(x,y) && quit.getIsClicked()){
            std::cout<<"Quit Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new Menu(this->renderer);
            delete this;
        }
        restart.setIsClicked(false);
        quit.setIsClicked(false);
    }
}
void GameOver::keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer){

}
GameOver::~GameOver(){

}

bool GameOver::loadMedia()
{
	//Load sprite sheet texture
	if( !gSpriteSheetTexture.LoadFromFile( "Images/final2.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if( !backSpriteSheetTexture.LoadFromFile( "Images/over.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		return false;
	}
	if(!buttonSpriteTexture.LoadFromFile("Images/button.jpg",renderer))
    {
        printf( "Failed to load sprite sheet texture!\n" );
		return false;
    }
    over= Mix_LoadWAV( "sounds/gameover.wav" );
	if(over == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	return true;
}
