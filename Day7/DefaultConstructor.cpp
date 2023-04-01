#include <iostream>

using namespace std;
class Player
{
private:
    int health;
    int score;
    float spawnTime;
    string name;

public:
    Player()
    {
        cout << endl
             << "Hi, I am a default constructor of Class Player, basically developers use me to initialize important variables/parameters of the player." << endl;
        health = 100;
        score = 500;
        name = "Player1";
        spawnTime = 2.0;
    }
    int getHealth()
    {
        return health;
    }
    int getScore()
    {
        return score;
    }
    float getSpawnTime()
    {
        return spawnTime;
    }
    string getName()
    {
        return name;
    }
};

int main()
{
    Player player;
    cout << endl
         << "Player's Name: " << player.getName() << endl
         << "Player's Health: " << player.getHealth() << endl
         << "Player's Score: " << player.getScore() << endl
         << "Player's Spawn Time: " << player.getSpawnTime() << " seconds" << endl;
    return 0;
}