#include <iostream>

using namespace std;
int main()
{
    int enemyHealth, *p, *q;
    cout << endl << "Enter Enemy's Health: ";
    cin >> enemyHealth;
    p = new int(enemyHealth);
    q = new int(enemyHealth);
    cout << "Value of P: " << p << endl << "Value of Q: " << q << endl;
    cout << "Value of *P: " << *p << endl << "Value of *Q: " << *q << endl << "Value of Enemy health: " << enemyHealth << endl;
    cout << endl << "Enter value of Enemy's Health again: ";
    cin >> enemyHealth;
    cout << "Value of P: " << p << endl << "Value of Q: " << q << endl;
    cout << "Value of *P: " << *p << endl << "Value of *Q: " << *q << endl << "Value of Enemy health: " << enemyHealth << endl;
    return 0;
}