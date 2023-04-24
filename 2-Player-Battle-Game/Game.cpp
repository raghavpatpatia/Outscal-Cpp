#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

// Player class
class Player
{
private:
    int health;
    int baseDamage;
public:
    Player(int hp, int damage): health(hp), baseDamage(damage){}
    virtual void Stats() = 0;
    virtual void Attack(Player* opponent) = 0;
    virtual void Heal() = 0;
    virtual int GetAdditionalDamage() = 0;
    virtual int GetHeal() = 0;
    int GetHealth(){return health;}
    void SetHealth(int hp){health = hp;}
    int GetBaseDamage(){return baseDamage;}
    virtual int SpecialAbility()
    {
        srand(time(0));
        if (rand() % 5 == 0)
        {
            return 100;
        }
        else
        {
            return 0;
        }
    }
    virtual ~Player()
    {
        // Virtual Player destructor
    }
};

// Vampire class
class Vampire : public Player
{
private:
    int additionalDamage;
    int heal;
public: 
    Vampire() : Player(200, 50){}
    
    int GetAdditionalDamage() override 
    {
        srand(time(0));
        additionalDamage = rand() % 80 + 5;
        return additionalDamage;
    }

    int GetHeal() override 
    {
        srand(time(0));
        heal = rand() % 80 + 5;
        return heal;
    }
    void Attack(Player* opponent) override 
    {
        int damage = GetBaseDamage() + GetAdditionalDamage();
        int special = SpecialAbility();
        if (special == 100)
        {
            cout << "Vampire used his special ability Blood Seal..." << endl;
            opponent->SetHealth(1);
        }
        else
        {
            opponent->SetHealth(opponent->GetHealth() - damage);
            cout << "You attacked your opponent and dealt " << damage << " damage." << endl;
        }
    }
    void Heal() override 
    {
        int hl = GetHealth() + GetHeal();
        if (GetHealth() >= 200)
        {
            SetHealth(200);
            cout << "Player is at full health..." << endl;
            cout << "Current health: " << GetHealth() << endl;
        }
        else
        {
            SetHealth(hl);
            cout << "You healed yourself for " << heal << " HP. Your current health is " << GetHealth() << endl;
        }
    }

    void Stats() override
    {
        cout << endl << "I am a Vampire. I drank blood of a Dracula and then I was turned into a vampire now I fight in his name." << endl;
        cout << "Vampire's health: " << GetHealth() << endl;
        cout << "Vampire's base damage: " << GetBaseDamage() << endl;
        cout << "Vampires can deal random additional damage of: 5 to 80" << endl;
        cout << "Vampires have random healing capacity of: 5 to 80" << endl << endl;
    }
    ~Vampire()
    {
      cout << "Your Vampire Player died..." << endl;
    }
};

// Warewolf class
class Warewolf : public Player
{
private:
    int additionalDamage;
    int heal;
public: 
    Warewolf() : Player(150, 80){}
    int GetAdditionalDamage() override 
    {
        srand(time(0));
        additionalDamage = rand() % 50 + 10;
        return additionalDamage;
    }
    int GetHeal() override 
    {
        srand(time(0));
        heal = rand() % 80 + 20;
        return heal;
    }
    void Attack(Player* opponent) override 
    {
        int damage = GetBaseDamage() + GetAdditionalDamage();
        int special = SpecialAbility();
        if (special == 100)
        {
            cout << "Warewolf used his special ability Heal + Damage..." << endl;
            opponent->SetHealth(opponent->GetHealth() - damage);
            SetHealth(GetHealth() + heal);
            cout << "You attacked your opponent and dealt " << damage << " damage and healed yourself with " << heal << " HP." << endl;
        }
        else
        {
            opponent->SetHealth(opponent->GetHealth() - damage);
            cout << "You attacked your opponent and dealt " << damage << " damage." << endl;
        }
    }
    void Heal() override 
    {
        int hl = GetHealth() + GetHeal();
        if (GetHealth() >= 150)
        {
            SetHealth(150);
            cout << "Player is at full health..." << endl;
            cout << "Current health: " << GetHealth() << endl;
        }
        else
        {
            SetHealth(hl);
            cout << "You healed yourself for " << heal << " HP. Your current health is " << GetHealth() << endl;
        }
    }

    void Stats() override
    {
        cout << endl << "I am a Warewolf. I was bitten by a Warewolf alpha and then I was turned into a Warewolf now I fight in his name." << endl;
        cout << "Warewolf's health: " << GetHealth() << endl;
        cout << "Warewolf's base damage: " << GetBaseDamage() << endl;
        cout << "Warewolves can deal random additional damage of: 10 to 50" << endl;
        cout << "Warewolves have random healing capacity of: 20 to 80" << endl << endl;
    }
    ~Warewolf()
    {
      cout << "Your Warewolf Player died..." << endl;
    }
};

// Golem class
class Golem : public Player
{
private:
    int additionalDamage;
    int heal;
public: 
    Golem() : Player(120, 80){}
    int GetAdditionalDamage() override 
    {
        srand(time(0));
        additionalDamage = rand() % 90 + 20;
        return additionalDamage;
    }
    int GetHeal() override 
    {
        srand(time(0));
        heal = rand() % 90 + 30;
        return heal;
    }
    void Attack(Player* opponent) override 
    {
        int damage = GetBaseDamage() + GetAdditionalDamage();
        int special = SpecialAbility();
        if (special == 100)
        {
            if (GetHealth() <= 20)
            {
                damage += 50;
                cout << "Golemn used his special ability Rage..." << endl;
                opponent->SetHealth(opponent->GetHealth() - damage);
                cout << "You attacked your opponent and dealt " << damage << " damage." << endl;
            }
            else
            {
                opponent->SetHealth(opponent->GetHealth() - damage);
                cout << "You attacked your opponent and dealt " << damage << " damage." << endl;
            }
        }
        else
        {
            opponent->SetHealth(opponent->GetHealth() - damage);
            cout << "You attacked your opponent and dealt " << damage << " damage." << endl;
        }
    }
    void Heal() override 
    {
        int hl = GetHealth() + GetHeal();
        if (GetHealth() >= 120)
        {
            SetHealth(120);
            cout << "Player is at full health..." << endl;
            cout << "Player's health: " << GetHealth() << endl;
        }
        else
        {
            SetHealth(hl);
            cout << "You healed yourself for " << heal << " HP. Your current health is " << GetHealth() << endl;
        }
    }

    void Stats() override
    {
        cout << endl << "I am a Golem. I was created by a Nacromancer and now I fight by his side." << endl;
        cout << "Golemn's health: " << GetHealth() << endl;
        cout << "Golemn's base damage: " << GetBaseDamage() << endl;
        cout << "Golemns can deal random additional damage of: 20 to 90" << endl;
        cout << "Golemns have random healing capacity of: 30 to 90" << endl << endl;
    }
    ~Golem()
    {
      cout << "Your Golem Player died..." << endl;
    }
};

// Starting rules
void Rules()
{
    cout << endl << "\t\t\t Battle Adventure Game" << endl;
    cout << endl << "\t\t\t\tRules" << endl;
    cout << endl << "1) Each Player Has only one turn at a time" << endl;
    cout << "2) Each Player Has Different Damages, Heals, Additional Damage and SPECIAL ABILITY."<< endl;
    cout << "NOTE: Each Special Ability has 20\% probability." << endl;
    cout << "3) The one's helath is below 0 , will die and loose the game.." << endl;
    cout << "4) Player can have two options in its turn, either to damage other player or to heal yourself.." << endl;
    cout << "5) Press H to heal and D to damage!" << endl;
    cout << endl << "\t\t There are three types of Player in our game" << endl;
    cout << endl;
    cout << "1) Vampire => High Health, High Heal , Avg Base Damage, High Additional Damage" << endl;
    cout << " Specail Ability ~ Blood Seal(Leaves enemy with only 1 hp)" << endl;
    cout << endl;
    cout << endl;
    cout << "2) Warewolf => Avg Health, High Heal , High Base Damage, Avg Additional Damage" << endl;
    cout << " Specail Ability ~ Heal + Damage(in single turn)" << endl;
    cout << endl;
    cout << endl;
    cout << "3) Golem => Low Health, Very High Heal , High Base Damage, Very High Additional Damage" << endl;
    cout <<" Specail Ability(depends on health) ~ Rage(Damage increases when player is close to death)" << endl; 
    cout << endl;
}

// Player character selection function
void PlayerSelection(Player*& ptr)
{
    int choice;
    do
    {
        cout << "Enter (1) for Vampire\nEnter (2) for Warewolf\nEnter (3) for Golem" << endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
                ptr = new Vampire();
                ptr->Stats();
                break;
            case 2:
                ptr = new Warewolf();
                ptr->Stats();
                break;
            case 3:
                ptr = new Golem();
                ptr->Stats();
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    } while(ptr == nullptr);
}

int main()
{
    // Initializing Variables
    bool isPlayer1playing = true;
    bool isPlayer1dead = false;
    char input;

    // Displaying stater rules
    Rules();

    // Player selection
    Player* player1 = nullptr;
    cout << "Player 1 select your character:" << endl;
    PlayerSelection(player1);
    Player* player2 = nullptr;
    cout << "Player 2 select your character:" << endl;
    PlayerSelection(player2);
    
    // Game loop till either player's health is 0
    while(player1->GetHealth() > 0 && player2->GetHealth() > 0)
    {
        // Logic if Player 1 is playing
        if (isPlayer1playing == true)
        {
            cout << "Player 1:\nPress (h) to heal and (d) to damage: ";
            cin >> input;
            if (input == 'H' || input == 'h')
            {
                player1->Heal();
            }
            if (input == 'D' || input == 'd')
            {
                player1->Attack(player2);
            }
            isPlayer1playing = false;
        }
        // Logic if Player 2 is playing
        else if (isPlayer1playing == false)
        {
            cout << "Player 2:\nPress (h) to heal and (d) to damage: ";
            cin >> input;
            if (input == 'H' || input == 'h')
            {
                player2->Heal();
            }
            if (input == 'D' || input == 'd')
            {
                player2->Attack(player1);
            }
            isPlayer1playing = true;
        }

        // If Player1's health is 0 setting isPlayer1dead to true
        if (player1->GetHealth() <= 0)
        {
            isPlayer1dead = true;
        }
    }

    // If Player 1 is dead
    if (isPlayer1dead)
    {
      cout << endl;
      delete player1;
      cout << endl << "Congrats Player2 you won..." << endl;
      cout << "Player2 died of exhaustion..." << endl;
      delete player2;
    }

    // If Player 2 is dead
    else
    {
      cout << endl;
      delete player2;
      cout << endl << "Congrats Player1 you won..." << endl;
      cout << "Player1 died of exhaustion..." << endl;
      delete player1;
    }
    return 0;
}