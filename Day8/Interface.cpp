#include <iostream>

using namespace std;

class PlayerInterface
{
public:
    virtual void DoubleJump() = 0;
    virtual void Fire() = 0;
};

class Player : public PlayerInterface
{
public:
    virtual void DoubleJump()
    {
        cout << endl << "DoubleJump is overriden" << endl;
    }
    virtual void Fire()
    {
        cout << endl << "Fire is overriden" << endl;
    }
};

int main()
{
    Player player;
    player.DoubleJump();
    player.Fire();
    return 0;
}