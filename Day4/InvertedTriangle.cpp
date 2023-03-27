#include <iostream>

using namespace std;
int main()
{
    for (int rows = 6; rows >= 1; rows--)
    {
        for (int column = 1; column <= rows; column++)
        {
            cout << "* ";
        }
        cout << endl;
    }
    return 0;
}