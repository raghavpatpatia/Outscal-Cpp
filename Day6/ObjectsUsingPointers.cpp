#include <iostream>

using namespace std;
class Player
{
private:
    int playerHealth;
public:
    int GetPlayerHealth()
    {
        return playerHealth;
    }

    int SetPlayerHealth(int health)
    {
        playerHealth = health;
        return playerHealth;
    }
};

int main()
{
    Player *player = new Player();
    player->SetPlayerHealth(100);
    cout << endl << "Player's Health: " << player->GetPlayerHealth() << endl;
    delete player;
    return 0;
}