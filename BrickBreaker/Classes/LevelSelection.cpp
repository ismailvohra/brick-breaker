#include "Pop-Up.h"
#include "Button.h"
#include "GamePlay.h"
#include "Menu.h"
#include "LevelSelection.h"
#include <iostream>

LevelSelection::LevelSelection(){
    renderer = NULL;
}
LevelSelection::LevelSelection(SDL_Renderer* renderer){
    this->renderer = renderer;
    if(loadMedia()){
        l1 = Button("01", {(float)(SCREEN_WIDTH/2)-240,(int)(200)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l2 = Button("02", {(float)(SCREEN_WIDTH/2)-100, (int)(200)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l3 = Button("03", {(float)(SCREEN_WIDTH/2)-240, (int)(270)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l4 = Button("04", {(float)(SCREEN_WIDTH/2)-100, (int)(270)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l5 = Button("05", {(float)(SCREEN_WIDTH/2)-240, (int)(340)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l6 = Button("06", {(float)(SCREEN_WIDTH/2)-100, (int)(340)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l7 = Button("07", {(float)(SCREEN_WIDTH/2)-240, (int)(410)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l8 = Button("08", {(float)(SCREEN_WIDTH/2)-100, (int)(410)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l9 = Button("09", {(float)(SCREEN_WIDTH/2)-240, (int)(480)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        l10 = Button("10", {(float)(SCREEN_WIDTH/2)-100, (int)(480)}, &gSpriteSheetTexture, &buttonSpriteTexture, Green);
        circleBtn = Button("Circle", {(float)(SCREEN_WIDTH/2)+200, (int)(200)}, &gSpriteSheetTexture, &buttonSpriteTexture, Red);
        diamondBtn = Button("Diamond", {(float)(SCREEN_WIDTH/2)+200, (int)(270)}, &gSpriteSheetTexture, &buttonSpriteTexture, Red);
        waveBtn = Button(" Wave ", {(float)(SCREEN_WIDTH/2)+200, (int)(340)}, &gSpriteSheetTexture, &buttonSpriteTexture, Red);
        backButton = Button(" Back ", {(float)(SCREEN_WIDTH/2)+200, (int)(480)}, &gSpriteSheetTexture, &buttonSpriteTexture, Brown);
    }else{
        std::cout<<"Error loading media in Pop-up class";
    }

}
void LevelSelection::show()
{
    backSpriteSheetTexture.Render(130,0,0,0.0,NULL,SDL_FLIP_NONE,renderer);
    l1.Draw(renderer);
    l2.Draw(renderer);
    l3.Draw(renderer);
    l4.Draw(renderer);
    l5.Draw(renderer);
    l6.Draw(renderer);
    l7.Draw(renderer);
    l8.Draw(renderer);
    l9.Draw(renderer);
    l10.Draw(renderer);
    circleBtn.Draw(renderer);
    diamondBtn.Draw(renderer);
    waveBtn.Draw(renderer);
    backButton.Draw(renderer);
}
void LevelSelection::click(int x, int y, MouseEventType eventType, ScreenManager** parentPointer, Pop_Up** selfPointer){
    if(eventType == ClickDown){
        if(l1.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l1.setIsClicked(true);
            std::cout<<"L1 Button Down"<<std::endl;
        }else if(l2.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l2.setIsClicked(true);
            std::cout<<"L2 Button Down"<<std::endl;
        }else if(l3.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l3.setIsClicked(true);
            std::cout<<"L3 Button Down"<<std::endl;
        }else if(l4.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l4.setIsClicked(true);
            std::cout<<"L4 Button Down"<<std::endl;
        }else if(l5.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l5.setIsClicked(true);
            std::cout<<"L5 Button Down"<<std::endl;
        }else if(l6.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l6.setIsClicked(true);
            std::cout<<"L6 Button Down"<<std::endl;
        }else if(l7.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l7.setIsClicked(true);
            std::cout<<"L7 Button Down"<<std::endl;
        }else if(l8.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l8.setIsClicked(true);
            std::cout<<"L8 Button Down"<<std::endl;
        }else if(l9.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l9.setIsClicked(true);
            std::cout<<"L9 Button Down"<<std::endl;
        }else if(l10.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            l10.setIsClicked(true);
            std::cout<<"L10 Button Down"<<std::endl;
        }else if(circleBtn.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            circleBtn.setIsClicked(true);
            std::cout<<"Circle Button Down"<<std::endl;
        }else if(diamondBtn.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            diamondBtn.setIsClicked(true);
            std::cout<<"Diamond Button Down"<<std::endl;
        }else if(waveBtn.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            waveBtn.setIsClicked(true);
            std::cout<<"Wave Button Down"<<std::endl;
        }else if(backButton.pointLiesInBounds(x,y)){
            Mix_PlayChannel( -1, gScratch, 0 );
            backButton.setIsClicked(true);
            std::cout<<"Back Button Down"<<std::endl;
        }
    }else if(eventType == ClickUp){
        if(l1.pointLiesInBounds(x,y) && l1.getIsClicked()){
            std::cout<<"L1 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 1);
            delete this;
        }else if(l2.pointLiesInBounds(x,y) && l2.getIsClicked()){
            std::cout<<"L2 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 2);
            delete this;
        }else if(l3.pointLiesInBounds(x,y) && l3.getIsClicked()){
            std::cout<<"L3 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 3);
            delete this;
        }else if(l4.pointLiesInBounds(x,y) && l4.getIsClicked()){
            std::cout<<"L4 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 4);
            delete this;
        }else if(l5.pointLiesInBounds(x,y) && l5.getIsClicked()){
            std::cout<<"L5 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 5);
            delete this;
        }else if(l6.pointLiesInBounds(x,y) && l6.getIsClicked()){
            std::cout<<"L6 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 6);
            delete this;
        }else if(l7.pointLiesInBounds(x,y) && l7.getIsClicked()){
            std::cout<<"L7 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 7);
            delete this;
        }else if(l8.pointLiesInBounds(x,y) && l8.getIsClicked()){
            std::cout<<"L8 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 8);
            delete this;
        }else if(l9.pointLiesInBounds(x,y) && l9.getIsClicked()){
            std::cout<<"L9 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 9);
            delete this;
        }else if(l10.pointLiesInBounds(x,y) && l10.getIsClicked()){
            std::cout<<"L10 Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, 10);
            delete this;
        }else if(circleBtn.pointLiesInBounds(x,y) && circleBtn.getIsClicked()){
            std::cout<<"Circle Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, circle);
            delete this;
        }else if(diamondBtn.pointLiesInBounds(x,y) && diamondBtn.getIsClicked()){
            std::cout<<"Diamond Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, diamond);
            delete this;
        }else if(waveBtn.pointLiesInBounds(x,y) && waveBtn.getIsClicked()){
            std::cout<<"Wave Button Up"<<std::endl;
            delete *parentPointer;
            *parentPointer = new GamePlay(this->renderer, wave);
            delete this;
        }else if(backButton.pointLiesInBounds(x,y) && backButton.getIsClicked()){
            std::cout<<"Back Button Up"<<std::endl;
            delete this;
            *selfPointer= NULL;
        }
        l1.setIsClicked(false);
        l2.setIsClicked(false);
        l3.setIsClicked(false);
        l4.setIsClicked(false);
        l5.setIsClicked(false);
        l6.setIsClicked(false);
        l7.setIsClicked(false);
        l8.setIsClicked(false);
        l9.setIsClicked(false);
        l10.setIsClicked(false);
        circleBtn.setIsClicked(false);
        diamondBtn.setIsClicked(false);
        waveBtn.setIsClicked(false);
        backButton.setIsClicked(false);
    }
}
void LevelSelection::keyboardEvent(const Uint8* event, ScreenManager** parentPointer, Pop_Up** selfPointer){

}
LevelSelection::~LevelSelection(){

}

bool LevelSelection::loadMedia()
{
	//Load sprite sheet texture
	if( !gSpriteSheetTexture.LoadFromFile( "Images/final2.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	if( !backSpriteSheetTexture.LoadFromFile( "Images/level.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		return false;
	}
	if(!buttonSpriteTexture.LoadFromFile("Images/button.jpg",renderer))
    {
        printf( "Failed to load sprite sheet texture!\n" );
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
