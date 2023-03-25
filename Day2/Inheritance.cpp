#include <iostream>

using namespace std;
class Enemy
{
protected:
    short int health = 100;
    short int attackPower;
    short int attackRange;
    short int XP;
    short int level;

    bool isAlive()
    {
        if (health > 0)
            return true;
        
        return false;
    }
    void XPDrop()
    {
        if (!isAlive())
        {
            if (level % 5 == 0)
            {
                XP *= 10;
                cout << "Enemy's XP: " << XP << endl;
            }
            else
            {
                cout << "Enemy's XP: " << XP << endl;
            }
        }
    }
public:
    void TakeDamage(int damage)
    {
        if (isAlive())
        {
            health -= damage;
            cout << endl << "Enemy has taken damage..." << endl;
            cout << "Enemy's Health: " << health << endl;
        }
        else
        {
            cout << endl << "Enemy is Dead..." << endl;
            XPDrop();
        }
    }
    void SetAttackPower(int power)
    {
        this->attackPower = power;
    }
    void SetAttackRange(int range)
    {
        this->attackRange = range;
    }
    void SetLevel(int level)
    {
        this->level = level;
    }
    void SetXP(int XP)
    {
        this->XP = XP;
    }
};

class FlyingEnemy : public Enemy
{
public:
    void FlyAttack()
    {
        if (attackRange > 0)
        {
            if (level % 2 == 0)
            {
                if (health > 50)
                {
                    attackPower *= 5;
                    attackRange *= 5;
                }
                else
                {
                    attackPower *= 8;
                    attackRange -= 10;
                }
                cout << endl << "Flying Enemy's Attack Power: " << attackPower << endl;
                cout << "Flying Enemy's Attack Range: " << attackRange << endl;
            }
            else
            {
                if (health < 50)
                {
                    attackPower *= 5;
                    attackRange -= 15;
                }
                cout << endl << "Flying Enemy's Attack Power: " << attackPower << endl;
                cout << "Flying Enemy's Attack Range: " << attackRange << endl;
            }
        }
        else 
        {
            cout << endl << "Enemy can't attack..." << endl;
        }
    }
};

class GroundEnemy : public Enemy
{
public:
    void GroundAttack()
    {
        if (attackRange > 0)
        {
            if (level % 2 == 0)
            {
                if (health > 50)
                {
                    attackPower *= 2;
                    attackRange *= 2;
                }
                else
                {
                    attackPower *= 5;
                    attackRange -= 7;
                }
                cout << endl << "Ground Enemy's Attack Power: " << attackPower << endl;
                cout << "Ground Enemy's Attack Range: " << attackRange << endl;
            }
            else
            {
                if (health < 50)
                {
                    attackPower *= 4;
                    attackRange -= 10;
                }
                cout << endl << "Ground Enemy's Attack Power: " << attackPower << endl;
                cout << "Ground Enemy's Attack Range: " << attackRange << endl;
            }
        }
        else 
        {
            cout << endl << "Enemy can't attack..." << endl;
        }
    }
};

int main()
{
    FlyingEnemy fly;
    cout << endl << "\t\t\tFlying Enemy" << endl;
    fly.SetAttackPower(20);
    fly.SetAttackRange(10);
    fly.SetXP(50);
    fly.SetLevel(5);
    fly.FlyAttack();
    fly.TakeDamage(20);
    fly.FlyAttack();
    fly.TakeDamage(50);
    fly.FlyAttack();
    fly.TakeDamage(10);
    fly.FlyAttack();
    fly.TakeDamage(20);
    fly.TakeDamage(5);
    GroundEnemy ground;
    cout << endl << "\t\t\tGround Enemy" << endl;
    ground.SetAttackPower(10);
    ground.SetAttackRange(5);
    ground.SetXP(50);
    ground.SetLevel(2);
    ground.GroundAttack();
    ground.TakeDamage(20);
    ground.GroundAttack();
    ground.TakeDamage(50);
    ground.GroundAttack();
    ground.TakeDamage(10);
    ground.GroundAttack();
    ground.TakeDamage(20);
    ground.TakeDamage(5);
    return 0;
}