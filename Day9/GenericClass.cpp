#include <iostream>

using namespace std;

template <typename T>
class SpecialAbility
{
private:
    T attackStrength;
public:
    void SetAttackPower(T attackPower)
    {
        attackStrength = attackPower;
    }
    void PerformSpecialAbility()
    {
        cout << "Enemy's Attack Power is: " << attackStrength << endl;
    }
};

int main()
{
    int attackPow1;
    float attackPow2;
    SpecialAbility<int> enemy1; // Creating integer type object of Generic class SpecialAbility
    SpecialAbility<float> enemy2; // Creating float type object of Generic class SpecialAbility
    cout << endl << "Enter Attack power of Integer Enemy: ";
    cin >> attackPow1;
    enemy1.SetAttackPower(attackPow1);
    enemy1.PerformSpecialAbility();
    cout << endl << "Enter Attack power of Float Enemy: ";
    cin >> attackPow2;
    enemy2.SetAttackPower(attackPow2);
    enemy2.PerformSpecialAbility();
    return 0;
}