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
    void DoubleJump()
    {
        cout << endl << "DoubleJump is overriden" << endl;
    }
    void Fire()
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