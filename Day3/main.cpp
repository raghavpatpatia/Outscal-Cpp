#include <iostream>

using namespace std;
class Dragon
{
public:
    void AccessSuperPower(bool ans)
    {
        if (ans == true)
        {
            cout << endl
             << "Dragon used it's Fire Power called \"FlameThrower\"" << endl << "You Won!" << endl;
        }
        else 
        {
            cout << endl << "Nothing happened!! The attack failed..." << endl;
        }
        
    }
    void AccessSuperPower(string word)
    {
        for (int i = 0; i < word.length(); i++)
        {
            word[i] = tolower(word[i]);
        }
        if (word == "water")
        {
            cout << endl
                 << "The dragon's action of splashing water with its tail resulted in a tsunami" << endl << "You Won!" << endl;
        }
        else
        {
            cout << endl
                 << "Nothing happened!! The attack failed..." << endl;
        }
    }
    void AccessSuperPower(string word, int number)
    {
        for (int i = 0; i < word.length(); i++)
        {
            word[i] = tolower(word[i]);
        }
        if (word == "air" && (number > 1 && number <= 100))
        {
            if (number < 100)
            {
                cout << endl
                 << "The dragon unfurled its wings to take flight, which generated powerful gusts of wind and resulted in the destruction of " << number << " spirits." << endl << "Rest of the spirits fled away..." << endl << "You Won!" << endl;
            }
            else 
            {
                cout << endl
                 << "The dragon unfurled its wings to take flight, which generated powerful gusts of wind and resulted in the destruction of " << number << " spirits." << endl << "You Won!" << endl;
            }
        }

        else if (word == "air" && number == 1)
        {
            cout << endl
                 << "The dragon unfurled its wings to take flight, which generated gusts of wind and resulted in the destruction of " << number << " spirit." << endl << "The attack failed..." << endl;
        }

        else
        {
            cout << endl
                 << "Nothing happened!! The attack failed..." << endl << "Dragon died!" << endl;
        }
    }
};

int main()
{
    Dragon dragon;
    string attack;
    short int num;
    bool isAlive = true;
    cout << endl << "\t\t\t Dragon Power" << endl;
    cout << endl << "You are a powerful dragon who is fighting against Wind, Fire, and Earth spirits..." << endl;
    cout << "You are given 3 powerful attacks:" << endl << "Fire" << endl << "Water" << endl << "Air" << endl;
    cout << "Use your powers wisely to destroy spirit kings and spirit armies" << endl << endl;
    if (isAlive == true)
    {
        cout << "Round 1:" << endl << "Dragon VS Fire spirit king" << endl;
        cout << "To destroy Fire spirit king use water attack" << endl << "Enter: water" << endl;
        cin >> attack;
        dragon.AccessSuperPower(attack);
        cout << endl << "Round 2:" << endl << "Dragon VS Wind spirit king" << endl;
        cout << "To destroy Wind spirit king use fire attack" << endl << "Enter: fire" << endl;
        cin >> attack;
        if (attack == "fire" || attack == "Fire")
        {
            dragon.AccessSuperPower(true);
        }
        else
        {
            dragon.AccessSuperPower(false);
        }
        cout << endl << "Round 3:" << endl << "Final Round..." << endl << "Dragon VS Earth spirit king and his army of 100 spirits" << endl;
        cout << "To destroy Earth spirit king and his army use Wind attack" << endl << "Enter: air" << endl;
        cin >> attack;
        cout << "Enter a number from 1 to 100..." << endl;
        cin >> num;
        dragon.AccessSuperPower(attack, num);
    }
    cout << "Game Over..." << endl;
    return 0;
}