#include <iostream>

using namespace std;
class Player
{
private: 
    int health;
    int lives;
public:
    Player(int hp, int life)
    {
        health = hp;
        lives = life;
        cout << endl << "I am a player, I just got spawned!" << endl << "Player's Health: " << health << endl;
    }
    ~Player()
    {
        cout << endl << "I am a player and I died" << endl << "Player's Health: " << health << endl;
    }
};

class FastPlayer: public Player
{
private:
    int speed;
public:
    FastPlayer(int sp, int hp, int life) : Player(hp, life)
    {
        speed = sp;
        cout << "My speed: " << speed << endl;
    }
    
    ~FastPlayer()
    {
        cout << endl << "I am a FastPlayer and I died" << endl << "FastPlayer's speed: " << speed;
    }
};

void localObjects()
{
    Player *player4 = new Player(60, 1);
    delete player4;
    FastPlayer *fastPlayer = new FastPlayer(80, 50, 3);
    delete fastPlayer;
}

int main()
{
    Player *player1 = new Player(100, 3); // creating first player
    Player *player2 = new Player(50, 2); // creating second player
    Player *player3 = new Player(10, 1); // creating third player
    FastPlayer *fastPlayer = new FastPlayer(90, 100, 2); // creating FastPlayer
    localObjects();
    delete player1;  // deleting first player
    delete player2;  // deleting second player
    delete player3;  // deleting third player
    delete fastPlayer;  // deleting FastPlayer
    return 0;
}