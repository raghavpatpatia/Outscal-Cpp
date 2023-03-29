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
    cout << "Size of Player Code(short): " << sizeof(playerCode) << " bytes" << endl
         << "Value of Player Code: " << playerCode << endl
         << "Size of Player Health(int): " << sizeof(playerHealth) << " bytes" << endl;
    return 0;
}