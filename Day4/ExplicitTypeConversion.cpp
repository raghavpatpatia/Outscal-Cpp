#include <iostream>

using namespace std;
int main()
{
    int playerHealth;
    cout << endl
         << "Enter Player's health: ";
    cin >> playerHealth;
    float playerHealthFractional;
    playerHealthFractional = (float)playerHealth / 2;
    cout << endl
         << "Size of Player health fractional(float): " << sizeof(playerHealthFractional) << " bytes" << endl
         << "Value of Player health fractional: " << playerHealthFractional << endl
         << "Size of Player health(int): " << sizeof(playerHealth) << " bytes" << endl;
    return 0;
}