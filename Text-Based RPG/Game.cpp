#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// Enum for levels from 1-6
enum Levels { level1 = 1, level2, level3, level4, level5, level6 };

// Enum for player Items
enum Items { sword, shield, armor, bow };

// Enum for abilities
enum Ability { criticalHits, lifesteal, block, invincible };

// generates a random number between 2 numbers
int randomNumber(int min = 0, int max = 100)
{
    srand(static_cast<unsigned int>(time(0)));
    int randNum = (rand() % max) + min;
    return randNum;
}

// Abstract class character controller
class CharacterController
{
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
    virtual void Stats(Levels level) { cout << "Health: " << health << "\nAttack Power: " << attackPower << "\nHeal: " << heal << "\nDefence: " << defence; }
    virtual void EnableItemandAbility(Ability ability, Items it) {/*Enabling items and abilities of player*/}
    virtual void Attack(CharacterController *other) = 0;
    virtual int Defence(int damage) = 0;
    virtual void Heal() = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual ~CharacterController() {}
};

// Player class
class Player : public CharacterController
{
private:
    const int meleeDamage = 25;
    const int rangedDamage = 15;
    vector<Items> item;
    vector<Ability> abilities;
public:   
    // Player parameterized constructor
    Player(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}

    // check if specific ability and item is enabled
    bool HasItemandAbility(Ability ability, Items it)
    {
        return (count(abilities.begin(), abilities.end(), ability > 0) && count(item.begin(), item.end(), it > 0));
    }

    // Function to enable ability and item
    void EnableItemandAbility(Ability ability, Items it)
    {
        // checking if ability and item is already enabled
        if (!HasItemandAbility(ability, it))
        {
            abilities.push_back(ability);
            item.push_back(it);
        }
    }

    // Showing stats according to player's level
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

    // Attack function
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

        cout << endl << "Enemy's Health (before damage): " << enemy->GetHealth() << endl;
        cout << endl << "Enemy took damage of " << enemy->Defence(randomDamage) << endl;
        enemy->TakeDamage(randomDamage);
        cout << endl << "Enemy's current Health (after damage): " << enemy->GetHealth() << endl;
    }

    // Healing function
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

    // Defence function
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

    // taking damage function
    void TakeDamage(int damage)
    {
        SetHealth(GetHealth() - Defence(damage));
        if (GetHealth() < 0)
        {
            SetHealth(0);
        }
    }

    // Player destructor
    ~Player(){ cout << endl << "Player died..." << endl; }
};

// Enemy class
class Enemy : public CharacterController
{
public:

    // Enemy class parameterized constructor
    Enemy(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}

    // Attack function
    void Attack (CharacterController* player)
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

    // Heal function
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

    // defence will activate only if health is less than 10 % of max health
    int Defence(int damage)
    {
        if (GetHealth() < HealthPercent(10))
        {
            damage -= GetDefence();
        }
        return abs(damage);
    }

    // taking damage
    void TakeDamage(int damage)
    {
        SetHealth(GetHealth() - Defence(damage));
        if (GetHealth() < 0)
        {
            SetHealth(0);
        }
    }

    // Destructor
    ~Enemy(){ cout << endl << "Enemy died..." << endl; }
};

// God class
class God : public CharacterController
{

public:

    // God class parameterized constructor
    God(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}

    // Special ability of boss player
    int Smash(int damage)
    {
        cout << "King of Gods used special ability: Smash\n";
        damage += 50;
        return damage;
    }

    // Attack function
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

    // Heal function
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

    // defence will activate only if health is less than 10 % of max health
    int Defence(int damage)
    {
        if (GetHealth() < HealthPercent(10))
        {
            damage -= GetDefence();
        }
        return abs(damage);
    }

    // taking damage
    void TakeDamage(int damage)
    {
        SetHealth(GetHealth() - Defence(damage));
        if (GetHealth() < 0)
        {
            SetHealth(0);
        }
    }

    // Destructor
    ~God(){ cout << endl << "King of Gods was defeated..." << endl; }
};

class Level
{
protected:
    vector<bool> hasEnemyDied;
    vector<CharacterController*> enemy;
    CharacterController* player;
    bool allTrue = all_of(hasEnemyDied.begin(), hasEnemyDied.end(), [](bool value){
        return value;
    });
    bool anyEnemyAlive = any_of(hasEnemyDied.begin(), hasEnemyDied.end(), [](bool enemyDied) {
        return !enemyDied;
    });

public:
    // Input system to take input from player
    void InputSystem(char input, CharacterController* player, CharacterController* enemy) 
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

    // Battle loop
    void BattleLoop(CharacterController* player, Levels level)
    {
        char input;
        for(int i = 0; i < level; i++)
        {
            if (!hasEnemyDied[i])
            {
                cout << endl << "Demon Lord's turn: ";
                InputSystem(input, player, enemy[i]);
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

    void VictoryCondition(Levels level)
    {
        if (player->GetHealth() > 0)
        {
            if (level == level6 && anyEnemyAlive)
            {
                BattleLoop(player, level1);
            }

            if (anyEnemyAlive)
            {
                BattleLoop(player, level);
            }
        }
    }

    // Level architecture to be shown in each level
    void LevelPattern(Levels level)
    {
        if (level == level6)
        {
            cout << endl << "__________Level-" << level << "__________" << endl;
            cout << "__________Final-Level__________" << endl << endl;
        }
        else
        {
            cout << endl << "__________Level-" << level << "__________" << endl << endl;
        }
        cout << "Welcome Demon Lord your stats for level " << level << " are: " << endl;
        player->Stats(level);
        cout << endl;
        if (level == level6)
        {
            cout << endl << "__________Boss Fight__________" << endl;
            cout << "__________Demon Lord vs God__________" << endl << endl;
        }
        else
        {
            cout << endl << "__________Enemies in level " << level <<"__________" << endl;
        }
        for( int i = 1; i <= level; i++)
        {
            if (level == level6)
            {
                break;
            }
            else
            {
                cout << i << ") Enemy " << i << endl;
            }
        }
        cout << endl << "__________Fight__________" << endl;
        cout << endl << endl;
        cout << "Press 'y' to continue...\n";
    }

    virtual void InitializePlayerandEnemy() = 0;

    virtual void LevelStart() = 0;

};

class Level1 : public Level
{
private:
    Levels currentLevel = level1;
public:

    Level1()
    {
        LevelStart();
    }

    void InitializePlayerandEnemy()
    {
        player = new Player(100, 50, 30, 20);
        enemy.push_back(new Enemy(100, 20, 20, 10));
        hasEnemyDied.push_back(false);
    }
    void LevelStart()
    {
        char input;
        bool validInput = false;
        InitializePlayerandEnemy();
        LevelPattern(currentLevel);
        while (!validInput) 
        {
            cin >> input;
            if (tolower(input) == 'y') 
            {
                validInput = true;
                input = '\0';
                cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
                VictoryCondition(currentLevel);
                if (allTrue)
                {
                    cout << "\nCongrats You have cleared level 1.\nYou have received a map.\n";
                }
            }
            else
            {
            cout << endl << "Wrong Input, try again..." << endl;
            }
        }
    }
};

class Level2 : public Level
{
private:
    Levels currentLevel = level2;
public:

    Level2()
    {
        LevelStart();
    }

    void InitializePlayerandEnemy()
    {
        enemy.clear();
        hasEnemyDied.clear();
        for (int i = 1; i <= currentLevel; i++)
        {
            enemy.push_back(new Enemy(150, 50, 25, 20));
            hasEnemyDied.push_back(false);
        }
        player = new Player(200, 70, 40, 40);
    }
    void LevelStart()
    {
        char input;
        bool validInput = false;
        InitializePlayerandEnemy();
        LevelPattern(currentLevel);
        while (!validInput) 
        {
            cin >> input;
            if (tolower(input) == 'y') 
            {
                validInput = true;
                input = '\0';
                cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
                VictoryCondition(currentLevel);
                if (allTrue)
                {
                    player->EnableItemandAbility(criticalHits, sword);
                    cout << "\nCongrats You have cleared level 2.\nYou have received a sword and obtained a special ability Critical Hits.\n";
                }
            }
            else
            {
            cout << endl << "Wrong Input, try again..." << endl;
            }
        }
    }
};

class Level3 : public Level
{
private:
    Levels currentLevel = level3;
public:

    Level3()
    {
        LevelStart();
    }

    void InitializePlayerandEnemy()
    {
        enemy.clear();
        hasEnemyDied.clear();
        for (int i = 1; i <= currentLevel; i++)
        {
            enemy.push_back(new Enemy(200, 60, 30, 25));
            hasEnemyDied.push_back(false);
        }
        player = new Player(300, 90, 50, 60);
    }
    void LevelStart()
    {
        char input;
        bool validInput = false;
        InitializePlayerandEnemy();
        LevelPattern(currentLevel);
        while (!validInput) 
        {
            cin >> input;
            if (tolower(input) == 'y') 
            {
                validInput = true;
                input = '\0';
                cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
                VictoryCondition(currentLevel);
                if (allTrue)
                {
                    player->EnableItemandAbility(block, shield);
                    cout << "\nCongrats You have cleared level 3.\nYou have received a shield and obtained a special ability Block.\n";
                }
            }
            else
            {
            cout << endl << "Wrong Input, try again..." << endl;
            }
        }
    }
};

class Level4 : public Level
{
private:
    Levels currentLevel = level4;
public:

    Level4()
    {
        LevelStart();
    }

    void InitializePlayerandEnemy()
    {
        enemy.clear();
        hasEnemyDied.clear();
        for (int i = 1; i <= currentLevel; i++)
        {
            enemy.push_back(new Enemy(250, 70, 35, 30));
            hasEnemyDied.push_back(false);
        }
        player = new Player(400, 110, 60, 80);
    }
    void LevelStart()
    {
        char input;
        bool validInput = false;
        InitializePlayerandEnemy();
        LevelPattern(currentLevel);
        while (!validInput) 
        {
            cin >> input;
            if (tolower(input) == 'y') 
            {
                validInput = true;
                input = '\0';
                cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
                VictoryCondition(currentLevel);
                if (allTrue)
                {
                    player->EnableItemandAbility(invincible, armor);
                    cout << "\nCongrats You have cleared level 4.\nYou have received a armor and obtained a special ability Invincibility.\n";
                }
            }
            else
            {
            cout << endl << "Wrong Input, try again..." << endl;
            }
        }
    }
};

class Level5 : public Level
{
private:
    Levels currentLevel = level5;
public:

    Level5()
    {
        LevelStart();
    }

    void InitializePlayerandEnemy()
    {
        enemy.clear();
        hasEnemyDied.clear();
        for (int i = 1; i <= currentLevel; i++)
        {
            enemy.push_back(new Enemy(300, 80, 40, 35));
            hasEnemyDied.push_back(false);
        }
        player = new Player(500, 130, 70, 100);
    }
    void LevelStart()
    {
        char input;
        bool validInput = false;
        InitializePlayerandEnemy();
        LevelPattern(currentLevel);
        while (!validInput) 
        {
            cin >> input;
            if (tolower(input) == 'y') 
            {
                validInput = true;
                input = '\0';
                cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
                VictoryCondition(currentLevel);
                if (allTrue)
                {
                    player->EnableItemandAbility(lifesteal, bow);
                    cout << "\nCongrats You have cleared level 5.\nYou have received a bow and obtained a special ability Life Steal.\n";
                }
            }
            else
            {
            cout << endl << "Wrong Input, try again..." << endl;
            }
        }
    }
};

class Level6 : public Level
{
private:
    Levels currentLevel = level6;
public:

    Level6()
    {
        LevelStart();
    }

    void InitializePlayerandEnemy()
    {
        enemy.clear();
        hasEnemyDied.clear();
        enemy.push_back(new God(500, 140, 80, 125));
        hasEnemyDied.push_back(false);
        player = new Player(600, 150, 80, 120);
    }
    void LevelStart()
    {
        char input;
        bool validInput = false;
        InitializePlayerandEnemy();
        LevelPattern(currentLevel);
        while (!validInput) 
        {
            cin >> input;
            if (tolower(input) == 'y') 
            {
                validInput = true;
                input = '\0';
                cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
                VictoryCondition(currentLevel);
                if (allTrue)
                {
                    cout << "\nCongrats You have cleared level 6.\nYou Won, You have defeated King of Gods and now you are new ruler of city of EM.\n";
                    exit(0);
                }
            }
            else
            {
            cout << endl << "Wrong Input, try again..." << endl;
            }
        }
    }
};

class GameManager {
private:
    Levels currentLevel;
    Level* level;

public:
    GameManager() {
        currentLevel = level1;
        level = nullptr;
        PlayGame();
    }

    ~GameManager() {
        delete level;
    }

    void MoveToNextLevel() {
        if (level != nullptr) {
            delete level;
        }

        switch (currentLevel) {
            case level1:
                level = new Level1();
                break;
            case level2:
                level = new Level2();
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
            default:
                level = nullptr;
                break;
        }

        if (level != nullptr) {
            level->LevelStart();
            currentLevel = static_cast<Levels>(currentLevel + 1);
            if (currentLevel > level6) {
                currentLevel = level6;
            }
        }
    }

    void PlayGame() {
        char input;
        bool validInput = false;
        while (!validInput) {
            cout << "Press 'm' to move to the next level or 'q' to quit: ";
            cin >> input;
            if (tolower(input) == 'm') {
                validInput = true;
                MoveToNextLevel();
            } else if (tolower(input) == 'q') {
                validInput = true;
                cout << "Quitting the game..." << endl;
                exit(0);
            } else {
                cout << "Wrong Input, try again..." << endl;
            }
        }
    }
};

int main()
{
    GameManager game;
    return 0;
}