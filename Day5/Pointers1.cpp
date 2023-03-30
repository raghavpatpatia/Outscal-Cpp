#include <iostream>

using std::cin;
using std::cout;
using std::endl;
int main()
{
    int playerHealth;
    cout << endl
         << "Enter Player's Health: ";
    cin >> playerHealth;
    int *p;
    p = &playerHealth;
    cout << "Value of p: " << p << endl;
    cout << "Address of Player's Health: " << &playerHealth << endl;
    cout << "Value of *p(derefrencing to value of playerHealth variable): " << *p << endl;
    cout << "Player's Health: " << playerHealth << endl;
    cout << "Enter the value of *p(derefrencing): ";
    cin >> *p;
    cout << "Value of *p(derefrencing to value of playerHealth variable): " << *p << endl;
    cout << "Player's Health: " << playerHealth << endl;
    return 0;
}