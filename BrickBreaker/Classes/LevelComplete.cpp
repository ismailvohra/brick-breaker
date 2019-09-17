#include "Pop-Up.h"
#include "Button.h"
#include "GamePlay.h"
#include "Menu.h"
#include "LevelComplete.h"
#include <iostream>

LevelComplete::LevelComplete(){
    renderer = NULL;
}
LevelComplete::LevelComplete(SDL_Renderer* renderer){

    this->renderer = renderer;
    if(loadMedia()){
        nextLevel = Button(" Next ", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)}, &gSpriteSheetTexture, &buttonSpriteTexture, Brown);
        restart = Button("Restart", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)+70}, &gSpriteSheetTexture, &buttonSpriteTexture, Brown);
        quit = Button(" Quit ", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)+140}, &gSpriteSheetTexture, &buttonSpriteTexture, Brown);
    }else{
        std::cout<<"Error loading media in Pop-up class";
    }

}
void LevelComplete::show()
{
    Mix_PlayChannel( -1, gamewon, 0 );
    backSpriteSheetTexture.Render(275,180,0,0.0,NULL,SDL_FLIP_NONE,renderer);
    nextLevel.Draw(renderer);
    restart.Draw(renderer);
    quit.Draw(renderer);
}
void LevelComplete::click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer){
    if(eventType == ClickDown){
        if(nextLevel.pointLiesInBounds(x,y)){
                Mix_PlayChannel( -1, gScratch, 0 );
            nextLevel.setIsClicked(true);
            std::cout<<"nextLevel Button Down"<<std::endl;
        }else if(restart.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            restart.setIsClicked(true);
            std::cout<<"Restart Button Down"<<std::endl;
        }else if(quit.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            quit.setIsClicked(true);
            std::cout<<"Quit Button Down"<<std::endl;
        }
    }else if(eventType == ClickUp){
        GamePlay* gamePlay = dynamic_cast<GamePlay*>(*parentPointer);
        if(nextLevel.pointLiesInBounds(x,y) && nextLevel.getIsClicked()){
            std::cout<<"nextLevel Button Up"<<std::endl;
            if(gamePlay->getCurrentLevel()>0){
                int nextLevel = gamePlay->getCurrentLevel() == 10 ? 1 : gamePlay->getCurrentLevel()+1;
                int lives = gamePlay->getLives();
                delete *parentPointer;
                *parentPointer = new GamePlay(this->renderer, nextLevel, lives);
            }else{
                int lives = gamePlay->getLives();
                delete *parentPointer;
                *parentPointer = new GamePlay(this->renderer, 1, lives);
            }
            delete this;
        }else if(restart.pointLiesInBounds(x,y) && restart.getIsClicked()){
            std::cout<<"Restart Button Up"<<std::endl;
            if(gamePlay->getCurrentLevel()>0){
                int nextLevel = gamePlay->getCurrentLevel() == 10 ? 1 : gamePlay->getCurrentLevel()+1;
                int lives = gamePlay->getLives();
                delete *parentPointer;
                *parentPointer = new GamePlay(this->renderer, nextLevel, lives);
            }else{
                ShapeLevel shapeLevel = static_cast<ShapeLevel>(gamePlay->getCurrentLevel()*-1);
                delete *parentPointer;
                *parentPointer = new GamePlay(this->renderer, shapeLevel);
            }
            delete this;
        }else if(quit.pointLiesInBounds(x,y) && quit.getIsClicked()){
            std::cout<<"Quit Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new Menu(this->renderer);
            delete this;
        }
        nextLevel.setIsClicked(false);
        restart.setIsClicked(false);
        quit.setIsClicked(false);
    }
}
void LevelComplete::keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer)
{

}

LevelComplete::~LevelComplete()
{

}

bool LevelComplete::loadMedia()
{
	//Load sprite sheet texture
	if( !gSpriteSheetTexture.LoadFromFile( "Images/final2.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if( !backSpriteSheetTexture.LoadFromFile( "Images/levelcomplete.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		return false;
	}
	if(!buttonSpriteTexture.LoadFromFile("Images/button.jpg",renderer))
    {
        printf( "Failed to load sprite sheet texture!\n" );
		return false;
    }
    gamewon= Mix_LoadWAV( "sounds/game_won.wav" );
	if( gamewon== NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	gScratch= Mix_LoadWAV( "sounds/click.mp3" );
	if( gScratch == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}

	return true;
}
