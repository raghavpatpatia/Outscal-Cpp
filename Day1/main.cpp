#include <iostream>

using namespace std;
class Player // creating a Player class with class keyword
{
private: // Declaring private access modifier. Under this all the values/data members and functions/member functions can be accessed only inside this class not outside the class.
    int health = 100;
    int score = 5;

protected:
    bool isAlive() // Creating a bool function which checks if player's health is greater then 0 then player is alive else player is not alive
    {
        if (health > 0)
            return true;

        return false;
    }

public:                 // Declaring public access modifier. Under this all the values/data members and functions/member functions can be accessed inside and outside the class well as outside the proogram.
    void CurrentStats() // Creating a function which prints current stats of the player
    {
        cout << endl
             << "Player's Health: " << health << endl
             << "Player's Score: " << score << endl;
    }

    void TakeDamage(int damage) // Creating a function which checks if player is alive then decrease player's health with the damage inflected on the player
    {
        if (isAlive())
        {
            health = health - damage;
            cout << "Player's Health: " << health << endl;
        }

        else
        {
            cout << "Player is dead..." << endl;
        }
    }
};

class Tank : public Player // Creating a class Tank which is inherating Player class
{
protected:
    void UpdateScore()
    {
        if (isAlive()) // isAlive function is accessible because it's access modifier was protected if it was private it would give an error
        {
        }
    }
};

int main()
{
    Player player;         // Creating object player of Player class
    player.CurrentStats(); // Checking current stats of the player.
    player.TakeDamage(45); // Setting Health to 55
    player.TakeDamage(55); // Setting health to 0
    player.TakeDamage(5);  // Telling player is already dead...
    Tank tank;             // Creating object tank of Tank class
    return 0;
}