#include "Menu.h"
#include "Button.h"
#include "GamePlay.h"
#include "DiskManager.h"
#include "LevelSelection.h"
#include <iostream>

Menu::Menu(){
    renderer = NULL;
}
Menu::Menu(SDL_Renderer* renderer){

    //std::cout<<*frame;
    this->renderer = renderer;
    popup = NULL;
    if(loadMedia()){
        newGame = Button("New Game", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)}, &gSpriteSheetTexture, &buttonSpriteTexture, Brown);
        loadGame = Button("Load Game", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)+70}, &gSpriteSheetTexture, &buttonSpriteTexture, Brown);
        exitGame = Button("Exit Game", {(float)SCREEN_WIDTH/2, (float)(SCREEN_HEIGHT/2)+140}, &gSpriteSheetTexture, &buttonSpriteTexture, Brown);
    }else{
        std::cout<<"Error loading media in Menu class";
    }

}
void Menu::show(long int frame){
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( gMusic, -1 );
    }
    backSpriteSheetTexture.Render(0,0,0,0.0,NULL,SDL_FLIP_NONE,renderer);
    newGame.Draw(renderer);
    loadGame.Draw(renderer);
    exitGame.Draw(renderer);

    if(popup){
        popup->show();
    }
}
void Menu::click(int x, int y, MouseEventType eventType, ScreenManager** selfPointer){
    if(popup){
        popup->click(x,y,eventType,selfPointer, &popup);
        return;
    }
    if(eventType == ClickDown){
        if(newGame.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );

            newGame.setIsClicked(true);
            std::cout<<"New Game Button Down"<<std::endl;
        }else if(loadGame.pointLiesInBounds(x,y)){
            ScreenManager* loadedGame = DiskManager::LoadGame(this->renderer);
            if(!loadedGame){
                Mix_PlayChannel( -1, ggScratch, 0 );
            }
            loadGame.setIsClicked(true);
            std::cout<<"Load Game Button Down"<<std::endl;
        }else if(exitGame.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );

            exitGame.setIsClicked(true);
            std::cout<<"Exit Game Button Down"<<std::endl;
        }
    }else if(eventType == ClickUp){

        if(newGame.pointLiesInBounds(x,y) && newGame.getIsClicked()){
            std::cout<<"New Game Button Up"<<std::endl;
            popup = new LevelSelection(this->renderer);
        }else if(loadGame.pointLiesInBounds(x,y) && loadGame.getIsClicked()){
            std::cout<<"Load Game Button Up "<<std::endl;
            ScreenManager* loadedGame = DiskManager::LoadGame(this->renderer);
            if(loadedGame){
                delete *selfPointer;
                *selfPointer = loadedGame;
            }
        }else if(exitGame.pointLiesInBounds(x,y) && exitGame.getIsClicked()){
            std::cout<<"Exit Game Button Up"<<std::endl;
            delete *selfPointer;
            *selfPointer = NULL;
        }
        newGame.setIsClicked(false);
        exitGame.setIsClicked(false);
        loadGame.setIsClicked(false);
    }
}
void Menu::keyboardEvent(const Uint8* event, ScreenManager** selfPointer){

}
Menu::~Menu(){
    gSpriteSheetTexture.Free();
    backSpriteSheetTexture.Free();
    buttonSpriteTexture.Free();
}

bool Menu::loadMedia()
{
	//Load sprite sheet texture
	if( !gSpriteSheetTexture.LoadFromFile( "Images/final2.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if( !backSpriteSheetTexture.LoadFromFile( "Images/mainMenu.jpg", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		return false;
	}
	if(!buttonSpriteTexture.LoadFromFile("Images/button.jpg",renderer))
    {
        printf( "Failed to load sprite sheet texture!\n" );
		return false;
    }
    gMusic = Mix_LoadMUS( "sounds/theme.wav" );
	if( gMusic == NULL )
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
	ggScratch= Mix_LoadWAV( "sounds/error.mp3" );
	if( gScratch == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
	}
	return true;
}
