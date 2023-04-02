#include <iostream>

using namespace std;
class Weapon
{
public:
    virtual void attack()
    {
        cout << endl << "Weapon performed attack" << endl;
    }

    void info()
    {
        cout << endl << "The weapon is a fire gauntlet that throws flamethrower attacks at the enemy." << endl;
    }
};

class RangedWeapon: public Weapon
{
public:
    void attack()
    {
        cout << endl << "Performing ranged attack" << endl;
    }

    void info()
    {
        cout << endl << "Fire gauntlet's attack power is 500, and its range is 50m." << endl;
    }
};

int main()
{
    Weapon *weapon;
    RangedWeapon rangedWeapon;
    weapon = &rangedWeapon;
    weapon->attack();
    weapon->info();
    return 0;
}