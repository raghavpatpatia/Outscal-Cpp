#ifndef PLAYERANDENEMIES_H
#define PLAYERANDENEMIES_H

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

int randomNumber(int min = 0, int max = 100);
class CharacterController {
private:
    int health;
    int maxHealth;
    int heal;
    int attackPower;
    int defence;

public:
    CharacterController(int hp, int atck, int hl, int def);
    int GetHealth();
    int GetMaxHealth();
    int GetAttackPower();
    int GetDefence();
    int GetHeal();
    void SetHealth(int health);
    void Ai(CharacterController* player);
    int HealthPercent(int percent);
    virtual void Stats(Levels level);
    virtual void EnableItemandAbility(Ability ability, Items it);
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
    Player(int hp, int atck, int hl, int def);
    bool HasItemandAbility(Ability ability, Items it);
    void EnableItemandAbility(Ability ability, Items it);
    void Stats(Levels level);
    void Attack(CharacterController* enemy);
    void Heal();
    int Defence(int damage);
    void TakeDamage(int damage);
    ~Player();
};

class Enemy : public CharacterController {
public:
    Enemy(int hp, int atck, int hl, int def);
    void Attack(CharacterController* player);
    void Heal();
    int Defence(int damage);
    void TakeDamage(int damage);
    ~Enemy();
};

class God : public CharacterController {
public:
    God(int hp, int atck, int hl, int def);
    int Smash(int damage);
    void Attack(CharacterController* player);
    void Heal();
    int Defence(int damage);
    void TakeDamage(int damage);
    ~God();
};

#endif  // PLAYERANDENEMIES_H