#include "PlayerAndEnemies.h"

// Default random function
int randomNumber(int min, int max)
{
    srand(static_cast<unsigned int>(time(0)));
    int randNum = (rand() % max) + min;
    return randNum;
}

// CharacterController class
CharacterController::CharacterController(int hp, int atck, int hl, int def) : health(hp), attackPower(atck), heal(hl), defence(def) { maxHealth = hp; }
int CharacterController::GetHealth() { return health; }
int CharacterController::GetMaxHealth() { return maxHealth; }
int CharacterController::GetAttackPower() { return attackPower; }
int CharacterController::GetDefence() { return defence; }
int CharacterController::GetHeal() { return heal; }
void CharacterController::SetHealth(int health) { this->health = health; }
void CharacterController::Ai(CharacterController *player) 
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
int CharacterController::HealthPercent(int percent)
{
    int maxHealthPercent = (GetMaxHealth() * percent) / 100;
    return maxHealthPercent;
}
void CharacterController::Stats(Levels level) { cout << "Health: " << health << "\nAttack Power: " << attackPower << "\nHeal: " << heal << "\nDefence: " << defence; }
void CharacterController::EnableItemandAbility(Ability ability, Items it) {/*Enabling items and abilities of player*/}
    
// Player class
Player::Player(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}
bool Player::HasItemandAbility(Ability ability, Items it)
{
    return (count(abilities.begin(), abilities.end(), ability > 0) && count(item.begin(), item.end(), it > 0));
}
void Player::EnableItemandAbility(Ability ability, Items it)
{
    if (!HasItemandAbility(ability, it))
    {
        abilities.push_back(ability);
        item.push_back(it);
    }
}
void Player::Stats(Levels level)
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
void Player::Attack(CharacterController* enemy)
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
void Player::Heal()
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
int Player::Defence(int damage)
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
void Player::TakeDamage(int damage)
{
    SetHealth(GetHealth() - Defence(damage));
    if (GetHealth() < 0)
    {
        SetHealth(0);
    }
}
Player::~Player(){ cout << endl << "Player died..." << endl; }

// Enemy class
Enemy::Enemy(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}
void Enemy::Attack (CharacterController* player)
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
void Enemy::Heal()
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
int Enemy::Defence(int damage)
{
    if (GetHealth() < HealthPercent(10))
    {
        damage -= GetDefence();
    }
    return abs(damage);
}
void Enemy::TakeDamage(int damage)
{
    SetHealth(GetHealth() - Defence(damage));
    if (GetHealth() < 0)
    {
        SetHealth(0);
    }
}
Enemy::~Enemy(){ cout << endl << "Enemy died..." << endl; }

// God class
God::God(int hp, int atck, int hl, int def) : CharacterController(hp, atck, hl, def){}
int God::Smash(int damage)
{
    cout << "King of Gods used special ability: Smash\n";
    damage += 50;
    return damage;
}
void God::Attack(CharacterController* player)
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
void God::Heal()
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
int God::Defence(int damage)
{
    if (GetHealth() < HealthPercent(10))
    {
        damage -= GetDefence();
    }
    return abs(damage);
}
void God::TakeDamage(int damage)
{
    SetHealth(GetHealth() - Defence(damage));
    if (GetHealth() < 0)
    {
        SetHealth(0);
    }
}
God::~God(){ cout << endl << "King of Gods was defeated..." << endl; }
