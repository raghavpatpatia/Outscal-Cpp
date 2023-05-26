#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "PlayerAndEnemies.h"
#include "Levels.h"

class GameManager
{
protected:
    Levels currentLevel;
public:
    GameManager();
    void Story();
    void NewLevel();
};

#endif