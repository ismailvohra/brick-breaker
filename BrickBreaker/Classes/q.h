#pragma once
#include"node (2).h"
#include"Object.h"

class Queue
{
private:
    node* head;
    node* tail;
public:
    Queue();
    ~Queue();
    void Enqueue(Object*);
    void Clean();
    void Render(long int frame, SDL_Renderer* gRenderer);
    void Move();
    node* getHead();
    node* getTail();
    void bringTailBack();
    void moveHeadAhead();
};
