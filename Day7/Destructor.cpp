#include <iostream>

using namespace std;

class Player
{
public:
    Player()
    {
        cout << endl << "I am a player Blaze. I just got spawned in the game world because my developer created the player's object. Agggh! boring life begins, fight, die, respawn. Huh I am gonna kill that bastard if I get out of this game" << endl;
    }
    ~Player()
    {
        cout << endl << "See?? that C++ destroyed my object by calling a destructor and now I died. that **** language you know 😡" << endl;
    }
};

int main()
{
    Player player;
    return 0;
}