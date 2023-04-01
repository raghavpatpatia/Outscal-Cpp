#include <iostream>

using namespace std;

class Player
{
private:
    int health;

public:
    Player(int hp)
    {
        cout << endl
             << "Hi, I am a custom constructor of Class Player, some call me parameterized constructor as well. basically, developers use me to set the specific values to the variables." << endl;
        health = hp;
    }
    int getHealth()
    {
        return health;
    }
};

int main()
{
    Player player(100);
    cout << endl
         << "Player's Health: " << player.getHealth() << endl;
    return 0;
}