#include <iostream>

using namespace std;
enum PlayerType
{
    CommonTypePlayer,
    TankTypePlayer,
    HighDamageTypePlayer
};

class Player
{
private:
    PlayerType playerType = CommonTypePlayer;
public:
    void TakeDamage()
    {
        cout << endl << "Player is taking damage" << endl;
    }

    PlayerType GetPlayerType()
    {
        return playerType;
    }
};

class TankPlayer: public Player
{
private:
    PlayerType playerType = TankTypePlayer;
public:
    void TakeDamage()
    {
        cout << endl << "TankPlayer is taking damage" << endl;
    }
    PlayerType GetPlayerType()
    {
        return playerType;
    }
};

class HighDamagePlayer: public Player
{
private:
    PlayerType playerType = HighDamageTypePlayer;
public:
    void TakeDamage()
    {
        cout << endl << "HighDamagePlayer is taking damage" << endl;
    }
    PlayerType GetPlayerType()
    {
        return playerType;
    }
};

int main()
{
    Player player;
    player.TakeDamage();
    cout << "Player Type: " << player.GetPlayerType() << endl;

    TankPlayer tankPlayer;
    tankPlayer.TakeDamage();
    cout << "Tank Player Type: " << tankPlayer.GetPlayerType() << endl;

    HighDamagePlayer highDamagePlayer;
    highDamagePlayer.TakeDamage();
    cout << "High Damage Player Type: " << highDamagePlayer.GetPlayerType() << endl;
}