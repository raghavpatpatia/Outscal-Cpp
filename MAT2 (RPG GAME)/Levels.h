#ifndef LEVELS_H
#define LEVELS_H

#include "GameManager.h"

class Level : public GameManager
{
protected:
    vector<bool> hasEnemyDied;
    vector<CharacterController*> enemy;
    CharacterController* player;
public:
    void InputSystem(char input, CharacterController* enemy);
    bool AllTrue();
    bool AnyEnemyAlive();
    virtual void BattleLoop();
    virtual void LevelPattern() = 0;
    virtual void GameLoop() = 0;
};

class Level1 : public Level
{
public:
    Level1();
    void LevelPattern();
    void GameLoop();
};

class Level2 : public Level
{
public:
    Level2();
    void LevelPattern();
    void GameLoop();
};

class Level3 : public Level
{
public:
    Level3();
    void LevelPattern();
    void GameLoop();
};

class Level4 : public Level
{
public:
    Level4();
    void LevelPattern();
    void GameLoop();
};

class Level5 : public Level
{
public:
    Level5();
    void LevelPattern();
    void GameLoop();
};

class Level6 : public Level
{
public:
    Level6();
    void LevelPattern();
    void GameLoop();
};

#endif //LEVELS_H