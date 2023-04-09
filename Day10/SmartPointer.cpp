#include <iostream>
#include <memory>

using namespace std;
class Player
{
private: 
    int health; // health and lives private variables
    int lives;
public:
    Player(int hp, int life) // Parameterized constructor
    {
        health = hp;
        lives = life;
        cout << endl << "I am a player, I just got spawned!" << endl << "Player's Health: " << health << endl;
    }
    ~Player() // Destructror of player class
    {
        cout << endl << "Destructor of player class\n" << "I am a player and I died" << endl << "Player's Health: " << health << endl;
    }
};

class FastPlayer: public Player // Class FastPlayer inheriting Player
{
private:
    int speed; // speed private variable
public:
    FastPlayer(int sp, int hp, int life) : Player(hp, life) // Paramaterized constructor of fastplayer showing constructor's inheritance
    {
        speed = sp;
        cout << "My speed: " << speed << endl; // initializing and printing speed variable
    }
    
    ~FastPlayer()
    {
        cout << endl << "Destructor of FastPlayer class\n" << "I am a FastPlayer and I died" << endl << "FastPlayer's speed: " << speed;
    }
};

void localObjects() // creating a local variable
{
    unique_ptr<Player> player4(new Player(60, 1)); // creating a smart pointer of Player class
    unique_ptr<FastPlayer> fastPlayer(new FastPlayer(80, 50, 3)); // creating a smart pointer of FastPlayer class
}

int main()
{
    unique_ptr<Player> player1(new Player(100, 3));// creating first player
    unique_ptr<Player> player2(new Player(50, 2)); // creating second player
    unique_ptr<Player> player3(new Player(10, 1)); // creating third player
    unique_ptr<FastPlayer> fastPlayer(new FastPlayer(90, 100, 2)); // creating FastPlayer
    localObjects();
    return 0;
}