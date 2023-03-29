#include <iostream>

using namespace std;
int main()
{
    string playerType;
    int number;
    cout << endl
         << "There are 3 Mythical creatures: Witches, Vampires, and Warewolves..." << endl
         << endl;
    cout << "Enter your player to see it's stats: " << endl
         << "(Witch, Vampire, or Warewolf)" << endl;
    cin >> playerType;
    for (int i = 0; i < playerType.length(); i++)
    {
        playerType[i] = tolower(playerType[i]);
    }
    if (playerType == "witch" || playerType == "witches")
        number = 1;
    else if (playerType == "vampire" || playerType == "vampires")
        number = 2;
    else if (playerType == "warewolf" || playerType == "warewolves")
        number = 3;

    
    switch (number)
    {
    case 1:
        cout << endl
             << "Witch character stats:" << endl
             << "Strength: 20\nMana: 80\nDuaribility: 60" << endl;
        break;
    case 2:
        cout << endl
             << "Vampire character stats:" << endl
             << "Strength: 70\nMana: 60\nDuaribility: 70" << endl;
        break;
    case 3:
        cout << endl
             << "Warewolf character stats:" << endl
             << "Strength: 80\nMana: 40\nDuaribility: 80" << endl;
        break;
    default:
        cout << endl
             << "Wrong character input..." << endl;
        break;
    }
    return 0;
}