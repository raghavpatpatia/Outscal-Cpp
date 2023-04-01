#include <iostream>

using namespace std;
class Player
{
public:
    Player()
    {
        cout << endl << "Creating an object of class Player" << endl;
    }
    ~Player()
    {
        cout << endl << "Deleting object of class Player" << endl;
    }
};

class StrongPlayer : public Player
{
public:
    StrongPlayer()
    {
        cout << endl << "Creating an object of class StrongPlayer" << endl;
    }
    ~StrongPlayer()
    {
        cout << endl << "Deleting object of class StrongPlayer " << endl;
    }
};

int main()
{
    StrongPlayer strongPlayer;
    return 0;
}