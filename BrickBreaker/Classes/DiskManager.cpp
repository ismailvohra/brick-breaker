#include "DiskManager.h"
#include "NormalBall.h"
#include "ThroughBall.h"
#include "FireBall.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

DiskManager::DiskManager()
{
    //ctor
}
void DiskManager::SaveGame(const GamePlay& gameplay){
    ofstream* editFile = new ofstream();
    editFile->open("Levels/SavedInstance.txt");

    //Saving Balls
    saveBalls(gameplay, editFile);

    //Saving Bricks
    saveBricks(gameplay, editFile);

    //Saving Bat
    *editFile<<endl<<"Bat:";
    *editFile<<endl<<">"<<Bat::GetInstance()->width<<","<<Bat::GetInstance()->x<<","<<Bat::GetInstance()->y;

    *editFile<<endl<<"Game:";
    *editFile<<endl<<">"<<gameplay.getLives()<<","<<gameplay.getCurrentLevel();
    //Should save score, lives, levelCount and more...
    editFile->close();
}
void DiskManager::saveBricks(const GamePlay& gamePlay, ofstream* editFile){
    *editFile<<endl<<"Bricks:";
    Board* board = gamePlay.getBoard();
    Node* temp = board->getHead();
    for(int j = 0; j <= BOARD_HEIGHT; j++){
        *editFile<<endl<<">";
        for(int i = 0; i<BOARD_WIDTH; i++){
            if(temp->position == i && temp->y == j){
                if(temp->brick->state){
                    *editFile<<(temp->brick->type == 3 ? 3 : temp->brick->breaktype);
                }else{
                    *editFile<<"-";
                }
                temp = temp->next;
            }else{
                *editFile<<"-";
            }
            if(!temp){
                *editFile<<endl;
                return;
            }
        }
    }
}
void DiskManager::saveBalls(const GamePlay& gamePlay, ofstream* editFile){
    *editFile<<"Balls:";
    node* qHead = gamePlay.getQHead();
    while(qHead){
        node* temp = qHead->next;
        if(!qHead->unit){
            qHead = temp;
            continue;
        }
        if(qHead->unit->objectType == ObjectBallType){
            Ball* ball = dynamic_cast<Ball*>(qHead->unit);
            *editFile<<endl<<">"<<ball->x<<","<<ball->y<<","<<ball->dirx<<","<<ball->diry<<","<<ball->type<<","<<ball->BALL_SPEED;
        }
        qHead = temp;
    }
}

GamePlay* DiskManager::LoadGame(SDL_Renderer* renderer){

    //Loading the file if it is saved.
    ifstream readfile("Levels/SavedInstance.txt");
    string name2;
    if(!readfile){
        return NULL;
    }
    if(!(readfile >> name2)){
        return NULL;
    }

    //Loading textures for Bat & Ball
    LTexture* backgroundTexture = new LTexture;
    LTexture* batBallTexture = new LTexture;
    LTexture* buttonSprite = new LTexture();
    LTexture* fontSprite = new LTexture();
    LTexture* powerSprite = new LTexture();
    if( !backgroundTexture->LoadFromFile( "Images/bgimage.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	if( !batBallTexture->LoadFromFile( "Images/finalsprites.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
    if( !fontSprite->LoadFromFile( "Images/final2.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}
	if(!buttonSprite->LoadFromFile("Images/button.jpg",renderer))
    {
        printf( "Failed to load sprite sheet texture!\n" );
    }
    if(!powerSprite->LoadFromFile( "Images/powerups.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
	}

    //Defining Objects of GamePlay
    Bat* bat = Bat::GetInstance();
    Board* board = new Board(24, 65, 768, 600, renderer);
    Queue* q = new Queue();

    float ballx, bally, ballDirX, ballDirY, batX, batY;
    int ballSpeed, batWidth, levelNumber, lifeCount;
    BallType ballType = NormalBallType;


    //Reading ball info and loading them in the queue
    if(name2.find("Ball") != string::npos){
        while(readfile >> name2){
            if(name2.find(">") == string::npos){
                break;
            }
            int j = 0;
            for(int i = 1; i < name2.length(); i++){
                string::size_type commaIndex = name2.find(",", i);
                switch(j){
                case 0:
                    ballx = atof(name2.substr(i, commaIndex-i).c_str());
                    break;
                case 1:
                    bally = atof(name2.substr(i, commaIndex-i).c_str());
                    break;
                case 2:
                    ballDirX = atof(name2.substr(i, commaIndex-i).c_str());
                    break;
                case 3:
                    ballDirY = atof(name2.substr(i, commaIndex-i).c_str());
                    break;
                case 4:
                    ballType = static_cast<BallType>(atoi(name2.substr(i, commaIndex-i).c_str()));
                    break;
                case 5:
                    ballSpeed = atoi(name2.substr(i, commaIndex-i).c_str());
                    break;
                }
                if(commaIndex == string::npos){
                    break;
                }
                i = commaIndex;
                j++;
            }
            Ball* ball = NULL;
            if(ballType == NormalBallType){
                ball = new NormalBall(batBallTexture, ballx, bally);
            }else if(ballType == ThroughBallType){
                ball = new ThroughBall(batBallTexture, ballx, bally);
            }else{
                ball = new FireBall(batBallTexture, ballx, bally);
            }
            ball->dirx = ballDirX;
            ball->diry = ballDirY;
            ball->type = ballType;
            ball->SetDirection(ballDirX, ballDirY);
            ball->BALL_SPEED = ballSpeed;
            q->Enqueue(ball);
        }
    }

    //Reading bricks info and loading them in the board.
    if(name2.find("Brick") != string::npos){
        int k = 0;
        while(readfile >> name2 && k <= BOARD_HEIGHT){
            if(name2.find(">") == string::npos){
                break;
            }
            for(int l=1; l<name2.length(); l++)
            {
                if((l-1)==BOARD_WIDTH)
                {
                    break;
                }
                Brick* brick = new Brick();
                brick->state = true;
                int bricktype = atoi(name2.substr(l, 1).c_str());
                brick->type=rand()%3;
                brick->breaktype=bricktype;
                if(name2[l]=='3')
                {
                    brick->breaktype = 0;
                    brick->type=3;
                }else
                if(name2[l]!='0' && bricktype == 0)
                {
                    continue;
                }
                board->Enqueue(brick, l-1, k);
            }
            k++;
        }
    }

    //Running cursor to find bat details
    do{
        if(name2.find("Bat") != string::npos){
            break;
        }
    }while(readfile >> name2);
    //reading bat details and making a new bat instance
    if(name2.length() > 0){
        if(readfile >> name2){
            if(name2.find(">") != string::npos){
                int j = 0;
                for(int i = 1; i < name2.length(); i++){
                    string::size_type commaIndex = name2.find(",", i);
                    switch(j){
                    case 0:
                        batWidth = atoi(name2.substr(i, commaIndex-i).c_str());
                        break;
                    case 1:
                        batX = atof(name2.substr(i, commaIndex-i).c_str());
                        break;
                    case 2:
                        batY = atof(name2.substr(i, commaIndex-i).c_str());
                        break;
                    }
                    if(commaIndex == string::npos){
                        break;
                    }
                    i = commaIndex;
                    j++;
                }
                bat->SetValue(batBallTexture, batX, batY);
                bat->width = batWidth;
            }
        }
    }

    //Reading GameInstance Details
    if(readfile >> name2){
        if(name2.find("Game") != string::npos){
            if(readfile >> name2){
                if(name2.find(">") != string::npos){
                    int j = 0;
                    for(int i = 1; i < name2.length(); i++){
                        string::size_type commaIndex = name2.find(",", i);
                        switch(j){
                        case 0:
                            lifeCount = atoi(name2.substr(i, commaIndex-i).c_str());
                            break;
                        case 1:
                            levelNumber = atoi(name2.substr(i, commaIndex-i).c_str());
                            break;
                        }
                        if(commaIndex == string::npos){
                            break;
                        }
                        i = commaIndex;
                        j++;
                    }
                }
            }
        }
    }

    readfile.close();
    GamePlay* gamePlay = new GamePlay(renderer, q, board, backgroundTexture, batBallTexture, buttonSprite, fontSprite, powerSprite, levelNumber, lifeCount);

    return gamePlay;
}
