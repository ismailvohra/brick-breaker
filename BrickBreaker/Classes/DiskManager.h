#ifndef DISKMANAGER_H
#define DISKMANAGER_H
#include "GamePlay.h"

class DiskManager
{
    public:
        DiskManager();
        static GamePlay* LoadGame(SDL_Renderer* renderer);
        static void SaveGame(const GamePlay& gameplay);

    private:
        static void saveBricks(const GamePlay& gamePlay, ofstream* editFile);
        static void saveBalls(const GamePlay& gamePlay, ofstream* editFile);
};

#endif // DISKMANAGER_H
