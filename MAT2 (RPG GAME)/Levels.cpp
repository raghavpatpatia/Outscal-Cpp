#include "Levels.h"

// Level class
void Level::InputSystem(char input, CharacterController* enemy) 
{
    bool validInput = false;
    while (!validInput) 
    {
        cin >> input;
        if (tolower(input) == 'a') 
        {
            player->Attack(enemy);
            validInput = true;
        } 
        else if (tolower(input) == 'h') 
        {
            player->Heal();
            validInput = true;
        } 
        else 
        {
            cout << endl << "Wrong Input try again..." << endl;
        }
    }
}
bool Level::AllTrue()
{
    return all_of(hasEnemyDied.begin(), hasEnemyDied.end(), [](bool value){ return value; });
}
bool Level::AnyEnemyAlive()
{
    return any_of(hasEnemyDied.begin(), hasEnemyDied.end(), [](bool enemyDied) { return !enemyDied; });
}
void Level::BattleLoop()
{
    char input;
    for(int i = 0; i < enemy.size(); i++)
    {
        if (!hasEnemyDied[i])
        {
            cout << endl << "Demon Lord's turn: ";
            InputSystem(input, enemy[i]);
            if (enemy[i]->GetHealth() <= 0) 
            {
                delete enemy[i];
                hasEnemyDied[i] = true;
            }
            else
            {
                cout << endl << "Enemy " << (i + 1) << " turn:" << endl;
                enemy[i]->Ai(player);
            }
        }
        if (player->GetHealth() <= 0) 
        {
            delete player;
            cout << endl << "You failed mission..." << endl;
            exit(0);
        }
    }
}

// Level1 class
Level1::Level1()
{
    currentLevel = level1;
    player = new Player(100, 50, 30, 20);
    enemy.push_back(new Enemy(100, 20, 20, 10));
    hasEnemyDied.push_back(false);
    GameLoop();
}
void Level1::LevelPattern()
{
    cout << endl << "__________Level-1__________" << endl << endl;
    cout << "Welcome Demon Lord your stats for level 1 are: " << endl;
    player->Stats(currentLevel);
    cout << endl << endl << "__________Enemies in level 1__________" << endl;
    for( int i = 1; i <= currentLevel; i++)
    {
        cout << i << ") Enemy " << i << endl;
    }
    cout << endl << endl;
    cout << "Press 'y' to continue..." << endl;
}
void Level1::GameLoop()
{
    char input;
    bool validInput = false;
    LevelPattern();
    while(!validInput)
    {
        cin >> input;
        if (tolower(input) == 'y')
        {
            validInput = true;
            cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
            while(player->GetHealth() > 0 && AnyEnemyAlive())
            {
                BattleLoop();
            }
            if (AllTrue())
            {
                cout << endl << "Congrats You have cleared level 1." << endl;
                cout << endl << "You have received a map" << endl;
                currentLevel = level2;
                NewLevel();
            }
        }
        else
        {
            cout << endl << "Wrong input, try again..." << endl;
        }
    }
}

// Level2 class
Level2::Level2()
{
    currentLevel = level2;
    player = new Player(200, 70, 40, 40);
    enemy.clear();
    hasEnemyDied.clear();
    for (int i = 1; i <= currentLevel; i++)
    {
        enemy.push_back(new Enemy(150, 50, 25, 20));
        hasEnemyDied.push_back(false);
    }
    GameLoop();
}
void Level2::LevelPattern()
{
    cout << endl << "__________Level-2__________" << endl << endl;
    cout << "Welcome Demon Lord your stats for level 2 are: " << endl;
    player->Stats(currentLevel);
    cout << endl << endl << "__________Enemies in level 2__________" << endl;
    for( int i = 1; i <= currentLevel; i++)
    {
        cout << i << ") Enemy " << i << endl;
    }
    cout << endl << endl;
    cout << "Press 'y' to continue..." << endl;
}
void Level2::GameLoop()
{
    char input;
    bool validInput = false;
    LevelPattern();
    while(!validInput)
    {
        cin >> input;
        if (tolower(input) == 'y')
        {
            validInput = true;
            cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
            while(player->GetHealth() > 0 && AnyEnemyAlive())
            {
                BattleLoop();
            }
            if (AllTrue())
            {
                player->EnableItemandAbility(criticalHits, sword);
                cout << "\nCongrats You have cleared level 2.\nYou have received a sword and obtained a special ability Critical Hits.\n";
                currentLevel = level3;
                NewLevel();
            }
        }
        else
        {
            cout << endl << "Wrong input, try again..." << endl;
        }
    }
}

// Level3 class
Level3::Level3()
{
    currentLevel = level3;
    player = new Player(300, 90, 50, 60);
    enemy.clear();
    hasEnemyDied.clear();
    for (int i = 1; i <= currentLevel; i++)
    {
        enemy.push_back(new Enemy(200, 60, 30, 25));
        hasEnemyDied.push_back(false);
    }
    GameLoop();
}
void Level3::LevelPattern()
{
    cout << endl << "__________Level-3__________" << endl << endl;
    cout << "Welcome Demon Lord your stats for level 3 are: " << endl;
    player->Stats(currentLevel);
    cout << endl << endl << "__________Enemies in level 3__________" << endl;
    for( int i = 1; i <= currentLevel; i++)
    {
        cout << i << ") Enemy " << i << endl;
    }
    cout << endl << endl;
    cout << "Press 'y' to continue..." << endl;
}
void Level3::GameLoop()
{
    char input;
    bool validInput = false;
    LevelPattern();
    while(!validInput)
    {
        cin >> input;
        if (tolower(input) == 'y')
        {
            validInput = true;
            cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
            while(player->GetHealth() > 0 && AnyEnemyAlive())
            {
                BattleLoop();
            }
            if (AllTrue())
            {
                player->EnableItemandAbility(block, shield);
                cout << "\nCongrats You have cleared level 3.\nYou have received a shield and obtained a special ability Block.\n";
                currentLevel = level4;
                NewLevel();
            }
        }
        else
        {
            cout << endl << "Wrong input, try again..." << endl;
        }
    }
}

// Level4 class
Level4::Level4()
{
    currentLevel = level4;
    player = new Player(400, 110, 60, 80);
    enemy.clear();
    hasEnemyDied.clear();
    for (int i = 1; i <= currentLevel; i++)
    {
        enemy.push_back(new Enemy(250, 70, 35, 30));
        hasEnemyDied.push_back(false);
    }
    GameLoop();
}
void Level4::LevelPattern()
{
    cout << endl << "__________Level-4__________" << endl << endl;
    cout << "Welcome Demon Lord your stats for level 4 are: " << endl;
    player->Stats(currentLevel);
    cout << endl << endl << "__________Enemies in level 4__________" << endl;
    for( int i = 1; i <= currentLevel; i++)
    {
        cout << i << ") Enemy " << i << endl;
    }
    cout << endl << endl;
    cout << "Press 'y' to continue..." << endl;
}
void Level4::GameLoop()
{
    char input;
    bool validInput = false;
    LevelPattern();
    while(!validInput)
    {
        cin >> input;
        if (tolower(input) == 'y')
        {
            validInput = true;
            cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
            while(player->GetHealth() > 0 && AnyEnemyAlive())
            {
                BattleLoop();
            }
            if (AllTrue())
            {
                player->EnableItemandAbility(invincible, armor);
                cout << "\nCongrats You have cleared level 4.\nYou have received a armor and obtained a special ability Invincibility.\n";
                currentLevel = level5;
                NewLevel();
            }
        }
        else
        {
            cout << endl << "Wrong input, try again..." << endl;
        }
    }
}

// Level5 class
Level5::Level5()
{
    currentLevel = level5;
    player = new Player(500, 130, 70, 100);
    enemy.clear();
    hasEnemyDied.clear();
    for (int i = 1; i <= currentLevel; i++)
    {
        enemy.push_back(new Enemy(300, 80, 40, 35));
        hasEnemyDied.push_back(false);
    }
    GameLoop();
}
void Level5::LevelPattern()
{
    cout << endl << "__________Level-5__________" << endl << endl;
    cout << "Welcome Demon Lord your stats for level 5 are: " << endl;
    player->Stats(currentLevel);
    cout << endl << endl << "__________Enemies in level 5__________" << endl;
    for( int i = 1; i <= currentLevel; i++)
    {
        cout << i << ") Enemy " << i << endl;
    }
    cout << endl << endl;
    cout << "Press 'y' to continue..." << endl;
}
void Level5::GameLoop()
{
    char input;
    bool validInput = false;
    LevelPattern();
    while(!validInput)
    {
        cin >> input;
        if (tolower(input) == 'y')
        {
            validInput = true;
            cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
            while(player->GetHealth() > 0 && AnyEnemyAlive())
            {
                BattleLoop();
            }
            if (AllTrue())
            {
                player->EnableItemandAbility(lifesteal, bow);
                cout << "\nCongrats You have cleared level 5.\nYou have received a bow and obtained a special ability Life Steal.\n";
                currentLevel = level6;
                NewLevel();
            }
        }
        else
        {
            cout << endl << "Wrong input, try again..." << endl;
        }
    }
}

// Level class
Level6::Level6()
{
    currentLevel = level6;
    player = new Player(600, 150, 80, 120);
    enemy.clear();
    hasEnemyDied.clear();
    enemy.push_back(new God(500, 140, 80, 125));
    hasEnemyDied.push_back(false);
    GameLoop();
}
void Level6::LevelPattern()
{
    cout << endl << "__________Level-6__________" << endl;
    cout << "__________Final Level__________" << endl << endl;
    cout << "Welcome Demon Lord your stats for level 6 are: " << endl;
    player->Stats(currentLevel);
    cout << endl << endl << "__________Boss Fight__________" << endl;
    cout << "__________Demon Lord vs God__________" << endl;
    cout << endl << endl << "__________Enemy in level 6__________" << endl;
    cout << "1) God(Boss Fight)" << endl;
    cout << endl << endl;
    cout << "Press 'y' to continue..." << endl;
}
void Level6::GameLoop()
{
    char input;
    bool validInput = false;
    LevelPattern();
    while(!validInput)
    {
        cin >> input;
        if (tolower(input) == 'y')
        {
            validInput = true;
            cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
            while(player->GetHealth() > 0 && AnyEnemyAlive())
            {
                BattleLoop();
            }
            if (AllTrue())
            {
                cout << "\nCongrats You have cleared level 6.\nYou Won, You have defeated King of Gods and now you are new ruler of city of EM.\n";
                exit(0);
            }
        }
        else
        {
            cout << endl << "Wrong input, try again..." << endl;
        }
    }
}
