#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
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
    CharacterController(){}
    CharacterController(int hp, int atck, int hl, int def) : health(hp), attackPower(atck), heal(hl), defence(def) { maxHealth = hp; }
    int GetHealth() { return health; }
    int GetMaxHealth() { return maxHealth; }
    int GetAttackPower() { return attackPower; }
    int GetDefence() { return defence; }
    int GetHeal() { return heal; }
    void SetHealth(int health) { this->health = health; }
    virtual void Stats(Levels level) { cout << "Health: " << health << "\nAttack Power: " << attackPower << "\nHeal: " << heal << "\nDefence: " << defence; }
    virtual void Ai(CharacterController *player) { cout << "AI for enemy class" << endl; }
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
    // Player default constructor
    Player(){}

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

int main()
{

    return 0;
}