#include "GameManager.h"

GameManager::GameManager()
{
    currentLevel = level1;
    Story();
    NewLevel();
}

void GameManager::Story()
{
    cout << "\nWelcome to the text-based RPG game where you embark on an epic journey with the demon lord to avenge his death and defeat the king of gods.\n\nIn this world, the city of EM was once a peaceful kingdom protected by a demon lord. However, a mystical door appeared one day, leading to the GOD realm, where a greedy king ruled over all the gods. The king coveted the beautiful city of EM and decided to sign a peace treaty as a cover to capture it.\n\nAfter a decade of negotiations, both parties agreed to the treaty. On the day of the signing, the demon lord hosted a party at his mansion. The king of gods poisoned the demon lord's drink, and realizing he wouldn't survive, the demon lord cast a reincarnation spell, vowing to take revenge on the king of gods in his next life.\n\nFifteen years later, the king of gods appointed new staff for the demon lord's mansion, and a wandering demon entered the sealed room where the demon lord died. The demon died suddenly, and within 15 seconds, the reincarnation spell activated, and the demon lord's soul possessed the demon's body, getting reincarnated. Now, the demon lord must defeat five labyrinths to defeat the king of gods. Each labyrinth is guarded by the king's appointed guards. After defeating each labyrinth, the demon lord gains special rewards and increased stats.\n\nAre you ready to join the demon lord on this epic adventure and defeat the king of gods?" << endl;
}

void GameManager::NewLevel()
{
    char input;
    bool validInput = false;
    while (!validInput)
    {
        cout << "Input 'm' to go to new level...\nInput: ";
        cin >> input;
        Level* level = nullptr;
        if (tolower(input) == 'm')
        {
            validInput = true;
            switch (currentLevel)
            {
                case level1:
                    level = new Level1();
                    break;
                case level2:
                    level = new Level2();
                    break;
                case level3:
                    level = new Level3();
                    break;
                case level4:
                    level = new Level4();
                    break;
                case level5:
                    level = new Level5();
                    break;
                case level6:
                    level = new Level6();
                    break;
            }
        }
        else
        {
            cout << endl << "Wrong Input, try again..." << endl;
        }
    }
    
}