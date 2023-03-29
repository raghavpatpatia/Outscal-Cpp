#include <iostream>

using namespace std;
int main()
{
    int playerHealth;
    short playerCode;
    cout << endl
         << "Enter player's health: ";
    cin >> playerHealth;
    playerCode = playerHealth;
    cout << ((playerHealth == playerCode) ? "true\n" : ((playerHealth == 5) ? "true\n" : ((playerHealth == 35000) ? "false\n" : "false\n")));
    return 0;
}