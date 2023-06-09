#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum Levels { level1 = 1, level2, level3, level4, level5, level6 };
enum Items { sword, shield, armor, bow };
enum Ability { criticalHits, lifesteal, block, invincible };

int randomNumber(int min = 0, int max = 100)
{
    srand(static_cast<unsigned int>(time(0)));
    int randNum = (rand() % max) + min;
    return randNum;
}

class CharacterController {
private:
    int health;
    int maxHealth;
    int heal;
    int attackPower;
    int defence;

public:
    CharacterController(int hp, int atck, int hl, int def) : health(hp), attackPower(atck), heal(hl), defence(def) { maxHealth = hp; }
    int GetHealth() { return health; }
    int GetMaxHealth() { return maxHealth; }
    int GetAttackPower() { return attackPower; }
    int GetDefence() { return defence; }
    int GetHeal() { return heal; }
    void SetHealth(int health) { this->health = health; }
    void Ai(CharacterController *player) 
    { 
        if (randomNumber(0, 2) > 0)
        {
            cout << endl << "Enemy attacked the player..." << endl;
            Attack(player);
        }
        else
        {
            cout << endl << "Enemy healed itself..." << endl;
            Heal();
        } 
    }
    int HealthPercent(int percent)
    {
        int maxHealthPercent = (GetMaxHealth() * percent) / 100;
        return maxHealthPercent;
    }
    void Stats(Levels level) { cout << "Health: " << health << "\nAttack Power: " << attackPower << "\nHeal: " << heal << "\nDefence: " << defence; }
    void EnableItemandAbility(Ability ability, Items it) {/*Enabling items and abilities of player*/}
    virtual void Attack(CharacterController* other) = 0;
    virtual int Defence(int damage) = 0;
    virtual void Heal() = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual ~CharacterController();
};

class Player : public CharacterController {
private:
    const int meleeDamage = 25;
    const int rangedDamage = 15;
    vector<Items> item;
    vector<Ability> abilities;

public:
    Player(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}
    bool HasItemandAbility(Ability ability, Items it)
    {
        return (count(abilities.begin(), abilities.end(), ability > 0) && count(item.begin(), item.end(), it > 0));
    }
    void EnableItemandAbility(Ability ability, Items it)
    {
        if (!HasItemandAbility(ability, it))
        {
            abilities.push_back(ability);
            item.push_back(it);
        }
    }
    void Stats(Levels level)
    {
        cout << endl << "Health: " << GetHealth() << endl;
        cout << "Attack Power: " << GetAttackPower() << endl;
        cout << "Defence: " << GetDefence() << endl;
        cout << "Healing Power: " << GetHeal() << endl;

        switch (level)
        {
            case level3:
                cout << "Melee Damage: " << meleeDamage << endl;
                cout << "Special Ability: Critical Hits (10\% chance)" << endl;
                break;

            case level4:
                cout << "Melee Damage: " << meleeDamage << endl;
                cout << "Special Ability: Critical Hits (10\% chance)\nBlock (10\% chance)" << endl;
                break;

            case level5:
                cout << "Melee Damage: " << meleeDamage << endl;
                cout << "Special Ability: Critical Hits (10\% chance)\nBlock (10\% chance)\nInvincibility (10\% chance)" << endl;
                break;

            case level6:
                cout << "Melee Damage: " << meleeDamage << endl;
                cout << "Ranged Damage: " << rangedDamage << endl;
                cout << "Special Ability: Critical Hits (10\% chance)\nBlock (10\% chance)\nInvincibility (10\% chance)\nLife Steal (10\% chance)" << endl;
                break;
        }
    }
    void Attack(CharacterController* enemy)
    {
        int randomDamage = 0;
        randomDamage += randomNumber(20, GetAttackPower());
        if (HasItemandAbility(criticalHits, sword))
        {
            randomDamage += meleeDamage;
            if (randomNumber() < 10) // special ability for critical hit
            {
                cout << endl << "Special ability critical hits activated... Dealt additional damage of 5 points..." << endl;
                randomDamage + 5;
            }

            else
            {
                if (HasItemandAbility(lifesteal, bow))
                {
                    randomDamage += rangedDamage;
                    if (randomNumber() < 10) 
                    {
                        if (randomNumber(0, 2) > 0) // special ability life steal if random number is 1
                        {
                            cout << endl << "Special ability life steal activated..." << endl;
                            cout << "Player's health increased by 50 points..." << endl;
                            cout << "Player's previous health: " << GetHealth() << endl;
                            cout << "Enemy's previous health: " << enemy->GetHealth() << endl;
                            enemy->SetHealth(enemy->GetHealth() - 50);
                            SetHealth(GetHealth() + 50);
                            cout << "Player's current health: " << GetHealth() << endl;
                            cout << "Enemy's current health: " << enemy->GetHealth() << endl << endl;
                        }
                        else // special ability critical hit if random number is 0
                        {
                            cout << endl << "Special ability critical hits activated... Dealt additional damage of 5 points..." << endl;
                            randomDamage + 5;
                        }
                    }
                    
                }
            }
        }
    }
    void Heal()
    {
        if (GetHealth() == GetMaxHealth())
        {
            cout << endl << "Player is already at full health..." << endl;
            return;
        }
        cout << endl << "Player's health (before heal): " << GetHealth() << endl;
        int randHeal = randomNumber(15, GetHeal());
        int remainingHeal = GetMaxHealth() - GetHealth();
        randHeal = min(randHeal, remainingHeal); // Limit heal amount to not exceed maxHealth

        cout << endl << "Healing done: " << randHeal << " points" << endl;
        SetHealth(GetHealth() + randHeal);

        cout << endl << "Player's health (after heal): " << GetHealth() << endl;
    }
    int Defence(int damage)
    {
        int totalDamage = damage;
        damage -= GetDefence();
        if (HasItemandAbility(block, shield)) // if shield is unlocked
        {
            damage -= 10;
            if (randomNumber() < 10) // checking if special ability block is activated
            {
                cout << endl << "Special ability block activated...\nOnly 1\% of actual damage is taken by the player" << endl;
                damage = (totalDamage * 1) / 100;
            }
            else
            {
                if (HasItemandAbility(invincible, armor)) // checking if armor is unlocked
                {
                    damage -= 10;
                    if (randomNumber() < 10) 
                    {
                        if (randomNumber(0, 2) > 0) // activating invincible ability if random number is 1
                        {
                            cout << endl <<"Special ability invincible activated...\nDamage taken: 0 points..." << endl;
                            damage = 0;
                        }
                        else // activating block if random number is 0
                        {
                            cout << endl << "Special ability block activated...\nOnly 1\% of actual damage is taken by the player" << endl;
                            damage = (totalDamage * 1) / 100;
                        }
                    }
                }
            }
        }        
        return abs(damage);
    }
    void TakeDamage(int damage)
    {
        SetHealth(GetHealth() - Defence(damage));
        if (GetHealth() < 0)
        {
            SetHealth(0);
        }
    }
    ~Player(){ cout << endl << "Player died..." << endl; }
};

class Enemy : public CharacterController {
public:
    Enemy(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}
    void Attack(CharacterController* player)
    {
        int randomDamage;
        randomDamage = randomNumber(10, GetAttackPower());
        if (GetHealth() > HealthPercent(50)) // If health is > 50% then attack damage will be 10 points extra
        {
            randomDamage += 10;
        }

        else if (GetHealth() < HealthPercent(25)) // If health is < 25% then attack damage will br 20 points extra
        {
            randomDamage += 20;
        }
        cout << endl << "Player's health(before taking damage): " << player->GetHealth() << endl;
        player->TakeDamage(randomDamage);
        cout << endl << "Player took damage of " << player->Defence(randomDamage) << " points" << endl;
        cout << endl << "Player's health(after taking damage): " << player->GetHealth() << endl;
    }
    void Heal()
    {
        int randHeal;
        if (GetHealth() == GetMaxHealth())
        {
            cout << endl << "Enemy is already at full health..." << endl;
        }
        else
        {
            if (GetHealth() > HealthPercent(50))
            {
                randHeal = randomNumber(1, GetHeal());
            }
            else
            {
                randHeal = randomNumber(5, GetHeal());
            }
            
            cout << endl << "Enemy's health (before heal): " << GetHealth() << endl;
            SetHealth(GetHealth() + randHeal);
            
            if (GetHealth() > GetMaxHealth())
            {
                randHeal -= (GetHealth() - GetMaxHealth());
                SetHealth(GetMaxHealth());
            }
            
            cout << endl << "Enemy gained heal of " << randHeal << " points" << endl;
            cout << endl << "Enemy's health (after heal): " << GetHealth() << endl;
        }
    }
    int Defence(int damage)
    {
        if (GetHealth() < HealthPercent(10))
        {
            damage -= GetDefence();
        }
        return abs(damage);
    }
    void TakeDamage(int damage)
    {
        SetHealth(GetHealth() - Defence(damage));
        if (GetHealth() < 0)
        {
            SetHealth(0);
        }
    }
    ~Enemy(){ cout << endl << "Enemy died..." << endl; }
};

class God : public CharacterController {
public:
    God(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}
    int Smash(int damage)
    {
        cout << "King of Gods used special ability: Smash\n";
        damage += 50;
        return damage;
    }
    void Attack(CharacterController* player)
    {
        int randomDamage;
        randomDamage += randomNumber(70, GetAttackPower());

        if (GetHealth() > HealthPercent(50)) // If health is > 50% then attack damage will be 20 points extra
        {
            randomDamage += 20;
        }

        else if (GetHealth() < HealthPercent(25)) // If health is < 25% then attack damage will be 30 points extra
        {
            randomDamage += 30;
        }
        
        if (randomNumber() < 10)
        {
            cout << endl << "Player's health(before taking damage): " << player->GetHealth() << endl;
            player->TakeDamage(Smash(randomDamage));
            cout << endl << "Player took damage of " << player->Defence(Smash(randomDamage)) << " points" << endl;
            cout << endl << "Player's health(after taking damage): " << player->GetHealth() << endl;
        }
        else
        {
            cout << endl << "Player's health(before taking damage): " << player->GetHealth() << endl;
            player->TakeDamage(randomDamage);
            cout << endl << "Player took damage of " << player->Defence(randomDamage) << " points" << endl;
            cout << endl << "Player's health(after taking damage): " << player->GetHealth() << endl;
        }
    }
    void Heal()
    {
        int randHeal;
        if (GetHealth() == GetMaxHealth())
        {
            cout << endl << "God is already at full health..." << endl;
        }
        else
        {
            if (GetHealth() > HealthPercent(50))
            {
                randHeal = randomNumber(20, GetHeal());
            }
            else
            {
                randHeal = randomNumber(30, GetHeal());
            }
            
            cout << endl << "God's health (before heal): " << GetHealth() << endl;
            SetHealth(GetHealth() + randHeal);
            
            if (GetHealth() > GetMaxHealth())
            {
                randHeal -= (GetHealth() - GetMaxHealth());
                SetHealth(GetMaxHealth());
            }

            cout << endl << "God gained heal of " << randHeal << " points" << endl;
            cout << endl << "God's health (after heal): " << GetHealth() << endl;
        }
    }
    int Defence(int damage)
    {
        if (GetHealth() < HealthPercent(10))
        {
            damage -= GetDefence();
        }
        return abs(damage);
    }
    void TakeDamage(int damage)
    {
        SetHealth(GetHealth() - Defence(damage));
        if (GetHealth() < 0)
        {
            SetHealth(0);
        }
    }
    ~God(){ cout << endl << "King of Gods was defeated..." << endl; }
};

class LevelManager;

class Level
{
protected:
    vector<bool> hasEnemyDied;
    vector<CharacterController*> enemy;
    CharacterController* player;
    Levels currentLevel;
    LevelManager* lm = nullptr;
public:
    Level(LevelManager* lm)
    {
        this->lm = lm;
    }
    virtual void LevelGameLoop(){};
    void InputSystem(char input, CharacterController* enemy)
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
    bool AllTrue()
    {
        return all_of(hasEnemyDied.begin(), hasEnemyDied.end(), [](bool value){ return value; });
    }
    bool AnyEnemyAlive()
    {
        return any_of(hasEnemyDied.begin(), hasEnemyDied.end(), [](bool enemyDied) { return !enemyDied; });
    }
    virtual void BattleLoop()
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
    
    // void LevelVariables()
    // {
    //     vector<Level*> level = {new Level1(), new Level2(), new Level3()};
    // }
    // void NewLevel(Levels currentLevel)
    // {
    //     char input;
    //     bool validInput = false;
    //     while (!validInput)
    //     {
    //         cout << "Input 'm' to go to new level...\nInput: ";
    //         cin >> input;
    //         Level* level = nullptr;
    //         if (tolower(input) == 'm')
    //         {
    //             validInput = true;
    //             switch (currentLevel)
    //             {
    //                 case level1:

    //                     level = new Level1();
    //                     break;
    //                 case level2:
    //                     level = new Level2();
    //                     break;
    //                 case level3:
    //                     level = new Level3();
    //                     break;
    //                 case level4:
    //                     level = new Level4();
    //                     break;
    //                 case level5:
    //                     level = new Level5();
    //                     break;
    //                 case level6:
    //                     level = new Level6();
    //                     break;
    //             }
    //         }
    //         else
    //         {
    //             cout << endl << "Wrong Input, try again..." << endl;
    //         }
    //     }
    // }
    virtual void LevelPattern() = 0;
    virtual void GameLoop() = 0;
};

class Level1 : public Level
{
public:
    void LevelGameLoop()
    {
        player = new Player(100, 50, 30, 20);
        enemy.push_back(new Enemy(100, 20, 20, 10));
        hasEnemyDied.push_back(false);
        GameLoop();
    }
    
    void LevelPattern()
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
    void GameLoop()
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
                    lm->NewLevel(currentLevel);
                }
            }
            else
            {
                cout << endl << "Wrong input, try again..." << endl;
            }
        }
    }
};

class Level2 : public Level
{
public:
    void LevelGameLoop()
    {
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
    void LevelPattern()
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
    void GameLoop()
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
                    lm->NewLevel(currentLevel);
                }
            }
            else
            {
                cout << endl << "Wrong input, try again..." << endl;
            }
        }
    }
};

class Level3 : public Level
{
public:
    Level3()
    {
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
    void LevelPattern()
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
    void GameLoop()
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
                    lm->NewLevel(currentLevel);
                }
            }
            else
            {
                cout << endl << "Wrong input, try again..." << endl;
            }
        }
    }
};

class Level4 : public Level
{
public:
    Level4()
    {
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
    void LevelPattern()
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
    void GameLoop()
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
                    lm->NewLevel(currentLevel);
                }
            }
            else
            {
                cout << endl << "Wrong input, try again..." << endl;
            }
        }
    }
};

class Level5 : public Level
{
public:
    Level5()
    {
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
    void LevelPattern()
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
    void GameLoop()
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
                    lm->NewLevel(currentLevel);
                }
            }
            else
            {
                cout << endl << "Wrong input, try again..." << endl;
            }
        }
    }
};

class Level6 : public Level
{
public:
    Level6()
    {
        player = new Player(600, 150, 80, 120);
        enemy.clear();
        hasEnemyDied.clear();
        enemy.push_back(new God(500, 140, 80, 125));
        hasEnemyDied.push_back(false);
        GameLoop();
    }
    void LevelPattern()
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
    void GameLoop()
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
};

class LevelManager
{
private:
    vector<Level*> levelref;
public:
    LevelManager()
    {
        levelref.push_back(new Level1(this));
        levelref.push_back(new Level2(this));
    }
    void PlayLevelGameLoop(int currentLevel)
    {
        levelref[currentLevel - 1]->LevelGameLoop();
    }
    void NewLevel(Levels currentLevel)
    {
        char input;
        bool validInput = false;
        while (!validInput)
        {
            cout << "Input 'm' to go to new level...\nInput: ";
            cin >> input;
            if (tolower(input) == 'm')
            {
                validInput = true;
                switch (currentLevel)
                {
                    case level1:
                        PlayLevelGameLoop(currentLevel);
                        break;
                    case level2:
                        PlayLevelGameLoop(currentLevel);
                        break;
                    case level3:
                        level = new Level3();
                        break;
                    case level4:
                        level = new Level4();
                        break;
                    case level5:
                        level = new Level5();
                        break;
                    case level6:
                        level = new Level6();
                        break;
                }
            }
            else
            {
                cout << endl << "Wrong Input, try again..." << endl;
            }
        }
    }
};

class GameManager
{
private:
    LevelManager levelManager;
public:
    GameManager()
    {
        Story();
        levelManager.NewLevel(level1);
    }
    void Story()
    {
        cout << "\nWelcome to the text-based RPG game where you embark on an epic journey with the demon lord to avenge his death and defeat the king of gods.\n\nIn this world, the city of EM was once a peaceful kingdom protected by a demon lord. However, a mystical door appeared one day, leading to the GOD realm, where a greedy king ruled over all the gods. The king coveted the beautiful city of EM and decided to sign a peace treaty as a cover to capture it.\n\nAfter a decade of negotiations, both parties agreed to the treaty. On the day of the signing, the demon lord hosted a party at his mansion. The king of gods poisoned the demon lord's drink, and realizing he wouldn't survive, the demon lord cast a reincarnation spell, vowing to take revenge on the king of gods in his next life.\n\nFifteen years later, the king of gods appointed new staff for the demon lord's mansion, and a wandering demon entered the sealed room where the demon lord died. The demon died suddenly, and within 15 seconds, the reincarnation spell activated, and the demon lord's soul possessed the demon's body, getting reincarnated. Now, the demon lord must defeat five labyrinths to defeat the king of gods. Each labyrinth is guarded by the king's appointed guards. After defeating each labyrinth, the demon lord gains special rewards and increased stats.\n\nAre you ready to join the demon lord on this epic adventure and defeat the king of gods?" << endl;
    }
};

int main()
{
    GameManager* gameManager = new GameManager();
    return 0;
}