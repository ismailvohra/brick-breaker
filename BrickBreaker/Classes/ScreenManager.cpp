#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
    this->renderer = NULL;
}
ScreenManager::ScreenManager(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

ScreenManager::~ScreenManager()
{
    //dtor
}
