#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Classes/LTexture.h"
#include "Classes/Ball.h"
#include "Classes/Bat.h"
#include "Classes/Board.h"
#include "Classes/NormalBall.h"
#include "Classes/GamePlay.h"
#include "Classes/ScreenManager.h"
#include "Classes/Statics.h"
#include "Classes/Menu.h"


#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

//Pre defined screen width and height



//bool init();

//bool loadMedia();

//void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//All Screens will implement this protocol to get rendered on through main
ScreenManager* currentManager = NULL;

bool init();
bool loadMedia();
LTexture splash;
void close();

int main( int argc, char* args[] )
{
    bool splashFlag = false;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
		close();
		return -1;
	}
    bool quit = false;                      //Main loop flag
    SDL_Event e;                            //Event handler

    long int frame = 0;                     //Current animation frame

    /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 1 and 10: */
    int random =0;

    currentManager = new Menu(gRenderer);

    splash.Render(132,0,0,0.0,NULL,SDL_FLIP_NONE,gRenderer);
    SDL_RenderPresent(gRenderer);
    Sleep(1000);
    while( !quit )                          //While application is running
    {
        while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            SDL_bool flag = SDL_bool(true);
            SDL_SetWindowBordered(gWindow, flag);
            if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
            {
                //Get mouse position
                int x, y;
                SDL_GetMouseState( &x, &y );
                if(e.type ==  SDL_MOUSEMOTION)
                {
                    currentManager->click(x, y, MouseMotion, &currentManager);
                }else if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        currentManager->click(x, y, ClickDown, &currentManager);
                    }else{
                        currentManager->click(x, y, RightClickDown, &currentManager);
                    }
                }else if(e.type == SDL_MOUSEBUTTONUP)
                {
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        currentManager->click(x, y, ClickUp, &currentManager);
                    }else{
                        currentManager->click(x, y, RightClickUp, &currentManager);
                    }
                }
            }
        }
        if(!currentManager){
            break;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        currentManager->keyboardEvent(currentKeyStates, &currentManager);

        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
        SDL_RenderClear(gRenderer);
        if(!currentManager){
            break;
        }
        currentManager->show(frame);
        SDL_RenderPresent(gRenderer);
        ++frame;
    }
    close();
	return 0;
}

bool init()

{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    //Create Splash_window
    gWindow = SDL_CreateWindow( "Break Out", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        return false;
    }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					return false;
				}
//    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
//				{
//					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
//					return false;
//				}

	return loadMedia();
}

bool loadMedia(){
    if( !splash.LoadFromFile( "Images/2.jpg", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	return true;
}

void close()
{
    //splash.Free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
