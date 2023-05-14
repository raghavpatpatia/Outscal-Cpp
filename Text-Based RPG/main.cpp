#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

// Enum for levels from 1-6
enum Levels { level1 = 1, level2, level3, level4, level5, level6 };

// Abstract class controller (base class for Player, Enemy, and God classes)
class Controller
{
private:
    int health;
    int attackPower;
    int heal;
    int defence;
public:
    Controller(){}
    Controller(int hp, int atck, int hl, int def) : health(hp), attackPower(atck), heal(hl), defence(def) {}
    int GetHealth() { return health; }
    int GetAttackPower() { return attackPower; }
    int GetDefence() { return defence; }
    int GetHeal() { return heal; }
    void SetHealth(int health) { this->health = health; }
    virtual void Stats(Levels level) { cout << "Health: " << health << "\nAttack Power: " << attackPower << "\nHeal: " << heal << "\nDefence: " << defence; }
    virtual void Ai(Controller *player) { cout << "AI for enemy class" << endl; }
    virtual void Attack(Controller *other) = 0;
    virtual int Defence(int damage) = 0;
    virtual void Heal() = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual ~Controller() {}
};

// Player class
class Player : public Controller
{
private:
    const int meleeDamage = 25;
    const int rangedDamage = 15;
    int maxHealth;
    bool map;
    bool sword;
    bool shield;
    bool armor;
    bool bow;
    bool criticalHits;
    bool lifesteal;
    bool block;
    bool invincible;
public:

    Player(){}
    // Initializing variables
    Player(int hp, int atck, int hl, int def) : Controller(hp, atck, hl, def)
    {
        maxHealth = hp;
        map = false;
        sword = false;
        shield = false;
        armor = false;
        bow = false;
        criticalHits = false;
        lifesteal = false;
        block = false;
        invincible = false;
    }
    
    // Setters
    void SetMap(bool input){map = input;}
    void SetSword(bool input){sword= input;}
    void SetShield(bool input){shield = input;}
    void SetArmor(bool input){armor = input;}
    void SetBow(bool input){bow = input;}
    void SetCriticalHits(bool input){criticalHits = input;}
    void SetBlock(bool input){block = input;}
    void SetInvincibility(bool input){invincible = input;}
    void SetLifeSteal(bool input){lifesteal = input;}

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

    // Attacking Enemy
    void Attack(Controller* enemy)
    {
        int randomDamage = 0;
        srand(time(0));

        if (sword && !bow) // Damage after clearing level 2 (having sword but not bow)
        {
            randomDamage = (rand() % (GetAttackPower() + meleeDamage)) + 20;
            if (criticalHits && (rand() % 100) < 10) // Activate critical hits with a 10% chance
            {
                cout << endl << "Special ability critical hits activated... Dealt additional damage of 5 points..." << endl;
                randomDamage += 5;
            }
        }

        else if (sword && bow) // Damage after clearing level 5 (having sword and bow)
        {
            // Generate random damage by adding melee damage, ranged damage, and attack power
            randomDamage = (rand() % (GetAttackPower() + meleeDamage + rangedDamage)) + 20;
            if (lifesteal && criticalHits && (rand() % 100) < 10) // Check if lifesteal and critical hits are activated with a 10% chance
            {
                if ((rand() % 2) > 0) // Activate life steal
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
                else // Activate critical hit
                {
                    cout << endl << "Special ability critical hits activated... Dealt additional damage of 5 points..." << endl;
                    randomDamage += 5;
                }
            }
        }
        else // If nothing is activated or player is on levels 1 and 2, generate random damage from 20 to maximum attack power
        {
            randomDamage = (rand() % GetAttackPower()) + 20;
        }

        cout << "Enemy's Health (before damage): " << enemy->GetHealth() << endl;
        cout << "Enemy took damage of " << enemy->Defence(randomDamage) << endl;
        enemy->TakeDamage(randomDamage);
        cout << "Enemy's current Health (after damage): " << enemy->GetHealth() << endl;
    }

    // Healing function
    void Heal()
    {
        srand(time(0));
        if (GetHealth() == maxHealth)
        {
            cout << endl << "Player is already at full health..." << endl;
            return;
        }
        cout << endl << "Player's health (before heal): " << GetHealth() << endl;
        int randHeal = (rand() % GetHeal()) + 15;
        int remainingHeal = maxHealth - GetHealth();
        randHeal = min(randHeal, remainingHeal); // Limit heal amount to not exceed maxHealth

        cout << "Healing done: " << randHeal << " points" << endl;
        SetHealth(GetHealth() + randHeal);

        cout << "Player's health (after heal): " << GetHealth() << endl;
    }

    // Defence function
    int Defence(int damage)
    {
        srand(time(0));
        
        if (shield && !armor) // If we have a shield but not armor
        {
            if ((rand() % 100) < 10 && block) // 10% chance for block ability to work
            {
                cout << endl << "Special ability block activated...\nOnly 1\% of actual damage is taken by the player" << endl;
                damage = (damage * 1) / 100;
            }
            else
            {
                damage -= GetDefence() + 10;
            }
        }
        else if (shield && armor) // If we have both shield and armor
        {
            if (invincible && (rand() % 100) < 10) // 10% chance for invincibility ability to work
            {
                cout << endl <<"Special ability invincible activated...\nDamage taken: 0 points..." << endl;
                damage = 0;
            }
            else
            {
                damage -= GetDefence() + 20;
            }
        }
        else
        {
            damage -= GetDefence();
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
    
    // Destructor
    ~Player()
    {
        cout << endl << "Player died..." << endl;
    }
};

// Enemy class
class Enemy : public Controller
{
private:
    int maxHealth;
public:

    // Initializing variables
    Enemy(int hp, int atck, int hl, int def) : Controller(hp, atck, hl, def)
    {
        maxHealth = hp;
    }

    // maximum health percent function
    int HealthPercent(int percent)
    {
        int maxHealthPercent = (maxHealth * percent) / 100;
        return maxHealthPercent;
    }

    // Attack function
    void Attack(Controller *player)
    {
        int randomDamage;
        srand(time(0));
        if (GetHealth() > HealthPercent(50)) // If health is > 50% then attack between 5 - max attack power
        {
            randomDamage = (rand() % GetAttackPower()) + 5;
        }

        else if (GetHealth() < HealthPercent(25)) // If health is < 25% then attack between 15 - max attack power
        {
            randomDamage = (rand() % GetAttackPower()) + 15;
        }

        else // If health is > 25% and health is < 50% then attack between 10 - max attack power
        {
            randomDamage = (rand() % GetAttackPower()) + 10;
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
        srand(time(0));
        
        if (GetHealth() == maxHealth)
        {
            cout << endl << "Enemy is already at full health..." << endl;
        }
        else
        {
            if (GetHealth() > HealthPercent(50))
            {
                randHeal = (rand() % GetHeal()) + 1;
            }
            else
            {
                randHeal = (rand() % GetHeal()) + 5;
            }
            
            cout << endl << "Enemy's health (before heal): " << GetHealth() << endl;
            SetHealth(GetHealth() + randHeal);
            
            if (GetHealth() > maxHealth)
            {
                randHeal -= (GetHealth() - maxHealth);
                SetHealth(maxHealth);
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

    // random choice for heal or attack
    void Ai(Controller *player)
    {
        srand(time(0));
        if ((rand() % 2) > 0)
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

    // Destructor
    ~Enemy()
    {
        cout << endl << "Enemy died..." << endl;
    }
};

// God class
class God : public Controller
{
private:
    int maxHealth;
public:

    // Initializing variables
    God(int hp, int atck, int hl, int def) : Controller(hp, atck, hl, def)
    {
        maxHealth = hp;
    }

    // maximum health percent function
    int HealthPercent(int percent)
    {
        int maxHealthPercent = (maxHealth * percent) / 100;
        return maxHealthPercent;
    }

    // Special ability of boss player
    int Smash(int damage)
    {
        cout << "King of Gods used special ability: Smash\nDelt 50 additional damage...\n";
        damage += 50;
        return damage;
    }

    // Attack function
    void Attack(Controller *player)
    {
        int randomDamage;
        srand(time(0));
        if (GetHealth() > HealthPercent(50)) // If health is > 50% then attack between 50 - max attack power
        {
            randomDamage = (rand() % GetAttackPower()) + 50;
        }

        else if (GetHealth() < HealthPercent(25)) // If health is < 25% then attack between 100 - max attack power
        {
            randomDamage = (rand() % GetAttackPower()) + 100;
        }

        else // If health is > 25% and health is < 50% then attack between 75 - max attack power
        {
            randomDamage = (rand() % GetAttackPower()) + 70;
        }
        
        if ((rand() % 100) < 10)
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
        srand(time(0));
        
        if (GetHealth() == maxHealth)
        {
            cout << endl << "God is already at full health..." << endl;
        }
        else
        {
            if (GetHealth() > HealthPercent(50))
            {
                randHeal = (rand() % GetHeal()) + 1;
            }
            else
            {
                randHeal = (rand() % GetHeal()) + 5;
            }
            
            cout << endl << "God's health (before heal): " << GetHealth() << endl;
            SetHealth(GetHealth() + randHeal);
            
            if (GetHealth() > maxHealth)
            {
                randHeal -= (GetHealth() - maxHealth);
                SetHealth(maxHealth);
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

    // random choice for heal or attack
    void Ai(Controller *player)
    {
        srand(time(0));
        if ((rand() % 2) > 0)
        {
            cout << endl << "God attacked the player..." << endl;
            Attack(player);
        }
        else
        {
            cout << endl << "God healed itself..." << endl;
            Heal();
        }
    }

    // Destructor
    ~God()
    {
        cout << endl << "King of Gods was defeated..." << endl;
    }
};

// Manages levels and battles between player and enemies
class LevelManager
{
private:
    vector<bool> hasEnemyDied;
    vector<Controller*> enemy;
    Controller* player = new Player();
    bool allTrue = all_of(hasEnemyDied.begin(), hasEnemyDied.end(), [](bool value) {
        return value;
    });
public:
    // Initialize Player for each level and show stats for each level
    void PlayerStats(Levels currentLevel)
    {
        switch(currentLevel)
        {
            case level1:
                player = new Player(100, 50, 30, 20);
                player->Stats(currentLevel);
                break;
            case level2:
                player = new Player(200, 70, 40, 40);
                player->Stats(currentLevel);
                break;
            case level3:
                player = new Player(300, 90, 50, 60);
                player->Stats(currentLevel);
                break;
            case level4:
                player = new Player(400, 110, 60, 80);
                player->Stats(currentLevel);
                break;
            case level5:
                player = new Player(500, 130, 70, 100);
                player->Stats(currentLevel);
                break;
            case level6:
                player = new Player(600, 150, 80, 120);
                player->Stats(currentLevel);
                break;
        }
    }

    // Initialize enemies for each level
    void EnemiesInEachLevel(Levels currentLevel)
    {
        switch(currentLevel)
        {
            case level1:
                enemy.push_back(new Enemy(100, 20, 20, 10));
                hasEnemyDied.push_back(false);
                break;
            case level2:
                enemy.clear();
                hasEnemyDied.clear();
                for (int i = 1; i <= currentLevel; i++)
                {
                    enemy.push_back(new Enemy(150, 50, 25, 20));
                    hasEnemyDied.push_back(false);
                }
                break;
            case level3:
                enemy.clear();
                hasEnemyDied.clear();
                for (int i = 1; i <= currentLevel; i++)
                {
                    enemy.push_back(new Enemy(200, 60, 30, 25));
                    hasEnemyDied.push_back(false);
                }
                break;
            case level4:
                enemy.clear();
                hasEnemyDied.clear();
                for (int i = 1; i <= currentLevel; i++)
                {
                    enemy.push_back(new Enemy(250, 70, 35, 30));
                    hasEnemyDied.push_back(false);
                }
                break;
            case level5:
                enemy.clear();
                hasEnemyDied.clear();
                for (int i = 1; i <= currentLevel; i++)
                {
                    enemy.push_back(new Enemy(300, 80, 40, 35));
                    hasEnemyDied.push_back(false);
                }
                break;
            case level6:
                enemy.clear();
                hasEnemyDied.clear();
                enemy.push_back(new God(500, 140, 80, 125));
                hasEnemyDied.push_back(false);
                break;
        }
    }

    // Level architecture to be shown in each level
    void LevelPattern(Levels currentLevel)
    {
        if (currentLevel == level6)
        {
            cout << endl << "__________Level-" << currentLevel << "__________" << endl;
            cout << "__________Final-Level__________" << endl << endl;
        }
        else
        {
            cout << endl << "__________Level-" << currentLevel << "__________" << endl << endl;
        }
        cout << "Welcome Demon Lord your stats for level " << currentLevel << " are: " << endl;
        PlayerStats(currentLevel);
        EnemiesInEachLevel(currentLevel);
        cout << endl;
        if (currentLevel == level6)
        {
            cout << endl << "__________Boss Fight__________" << endl;
            cout << "__________Demon Lord vs God__________" << endl << endl;
        }
        else
        {
            cout << endl << "__________Enemies in level " << currentLevel <<"__________" << endl;
        }
        for( int i = 1; i <= currentLevel; i++)
        {
            if (currentLevel == level6)
            {
                break;
            }
            else
            {
                cout << i << ") Enemy " << i << endl;
            }
        }
        cout << endl << endl << endl;
    }

    // Input system to take input from player
    void InputSystem(char input, Controller *player, Controller *enemy) 
    {
        bool validInput = false;
        while (!validInput) 
        {
            cin >> input;
            tolower(input);
            if (input == 'a') 
            {
                player->Attack(enemy);
                validInput = true;
            } 
            else if (input == 'h') 
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
    void BattleLoop(Controller* player, Levels level)
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

    friend class GameManager;
};

// GameManager class(Levels 1-6, story, and some other functions)
class GameManager : public LevelManager
{
private:
    Levels currentLevel = level1;
public:
    // Game-Play
    GameManager()
    {
        Story();
        NextLevel();
    }

    // Starting story
    void Story()
    {
        cout << "\nWelcome to the text-based RPG game where you embark on an epic journey with the demon lord to avenge his death and defeat the king of gods.\n\nIn this world, the city of EM was once a peaceful kingdom protected by a demon lord. However, a mystical door appeared one day, leading to the GOD realm, where a greedy king ruled over all the gods. The king coveted the beautiful city of EM and decided to sign a peace treaty as a cover to capture it.\n\nAfter a decade of negotiations, both parties agreed to the treaty. On the day of the signing, the demon lord hosted a party at his mansion. The king of gods poisoned the demon lord's drink, and realizing he wouldn't survive, the demon lord cast a reincarnation spell, vowing to take revenge on the king of gods in his next life.\n\nFifteen years later, the king of gods appointed new staff for the demon lord's mansion, and a wandering demon entered the sealed room where the demon lord died. The demon died suddenly, and within 15 seconds, the reincarnation spell activated, and the demon lord's soul possessed the demon's body, getting reincarnated. Now, the demon lord must defeat five labyrinths to defeat the king of gods. Each labyrinth is guarded by the king's appointed guards. After defeating each labyrinth, the demon lord gains special rewards and increased stats.\n\nAre you ready to join the demon lord on this epic adventure and defeat the king of gods?" << endl;
    }
    
    // Function to switch levels
    void NextLevel()
    {
        char input;
        bool validInput = false;
        cout << endl << "Input 'm' to go to new level...\nInput: ";
        while (!validInput) 
        {
            cin >> input;
            if (tolower(input) == 'm') 
            {
                Level();
                validInput = true;
            }
            else
            {
                cout << endl << "Wrong Input, try again..." << endl;
            }
        }
        validInput = false;
    }

    // Conditions for each level
    void VictoryConditionsandBattle(Levels currentLevel)
    {
      Player* demon = new Player();
      if (player->GetHealth() > 0)
      {
        switch(currentLevel)
        {
          case level1:
            while(!hasEnemyDied[0])
            {
              BattleLoop(player, currentLevel);
            }
            break;
          case level2:
            while(!hasEnemyDied[0] || !hasEnemyDied[1])
            {
              BattleLoop(player, currentLevel);
            }
            break;
          case level3:
            while(!hasEnemyDied[0] || !hasEnemyDied[1] || !hasEnemyDied[2])
            {
              BattleLoop(player, currentLevel);
            }
            break;
          case level4:
            while(!hasEnemyDied[0] || !hasEnemyDied[1] || !hasEnemyDied[2] || !hasEnemyDied[3])
            {
              BattleLoop(player, currentLevel);
            }
            break;
          case level5:
            while(!hasEnemyDied[0] || !hasEnemyDied[1] || !hasEnemyDied[2] || !hasEnemyDied[3] || !hasEnemyDied[4])
            {
              BattleLoop(player, currentLevel);
            }
            break;
          case level6:
            while(!hasEnemyDied[0])
            {
              BattleLoop(player, level1);
            }
            break;
        }
      }
      if (allTrue)
      {
        switch(currentLevel)
        {
          case level1:
            demon->SetMap(true);
            cout << endl << "Congrats You have cleared level 1." << endl;
            cout << endl << "You have received a map" << endl;
            GameManager::currentLevel = level2;
            NextLevel();
            break;
          case level2:
            cout << endl << "Congrats You have cleared level 2." << endl;
            demon->SetSword(true);
            demon->SetCriticalHits(true);
            cout << endl << "You have received a sword and obtained a special ability Critical Hits" << endl;
            GameManager::currentLevel = level3;
            NextLevel();
            break;
          case level3:
            demon->SetShield(true);
            demon->SetBlock(true);
            cout << endl << "Congrats You have cleared level 3." << endl;
            cout << endl << "You have received a shield and obtained a special ability Block" << endl;
            GameManager::currentLevel = level4;
            NextLevel();
            break;
          case level4:
            demon->SetArmor(true);
            demon->SetInvincibility(true);
            cout << endl << "Congrats You have cleared level 4." << endl;
            cout << endl << "You have received a armor and obtained a special ability Invincibility" << endl;
            GameManager::currentLevel = level5;
            NextLevel();
            break;
          case level5:
            demon->SetBow(true);
            demon->SetLifeSteal(true);
            cout << endl << "Congrats You have cleared level 5." << endl;
            cout << endl << "You have received a bow and obtained a special ability Life Steal" << endl;
            GameManager::currentLevel = level6;
            NextLevel();
            break;
          case level6:
            cout << endl << "Congrats You have cleared level 6." << endl;
            cout << endl << "You Won, You have defeated King of Gods and now you are new ruler of city of EM." << endl;
            exit(0);
            break;
        }
      }
    }

    // code that each level will execute
    void Level()
    {
      char input;
      bool validInput = false;
      LevelPattern(currentLevel);
      cout << "Press 'y' to continue...\n";
      while (!validInput) 
      {
            cin >> input;
            if (tolower(input) == 'y') 
            {
                validInput = true;
                input = '\0';
                cout << endl << "Welcome Demon Lord, press 'a' to attack enemy and 'h' to heal...";
                VictoryConditionsandBattle(currentLevel);
            }
            else
            {
              cout << endl << "Wrong Input, try again..." << endl;
            }
      }
    } 
};

int main()
{
    GameManager *game = new GameManager();
    delete game;
    return 0;
}