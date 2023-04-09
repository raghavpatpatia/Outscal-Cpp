#include <iostream>
using namespace std;

class Player
{
public:
    Player() // constructor of player class
    {
        cout << endl << "I am a player, I just not spawned" << endl;
    }
    ~Player() // destructor of player class
    {
        cout << endl << "Ops, that enemy killed me, I just died!" << endl;
    }
};

int main()
{
    Player player1; //object of player -> static allocation
    Player *player2 = new Player(); // object of player using pointer and new keyword -> dynamic allocation
    delete player2; // freeing memory of player2
    return 0;
}