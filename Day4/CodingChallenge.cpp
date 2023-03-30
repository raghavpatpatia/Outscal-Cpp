#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

class Boxes
{
private:
    short RED = 10;
    short BLUE = 20;
    short sum = 0;

public:
    string GenerateRandomString()
    {
        char box[2] = {'R', 'B'};
        srand(static_cast<unsigned int>(time(0)));
        int StringLength = rand() % 10 + 1;
        string result = "";
        for (int i = 0; i < StringLength; i++)
        {
            result = result + box[rand() % 2];
        }
        return result;
    }

    void Print()
    {
        string str;
        short streak = 1;
        str = GenerateRandomString();
        if (str[0] == 'R')
        {
            sum += RED;
        }
        else if (str[0] == 'B')
        {
            sum += BLUE;
        }
        for (int i = 1; i < str.length(); i++)
        {
            if (str[i] == 'R')
            {
                if (str[i] == str[i - 1])
                {
                    streak++;
                    sum += RED * streak;
                }
                else
                {
                    streak = 1;
                    sum += RED;
                }
            }
            else if (str[i] == 'B')
            {
                if (str[i] == str[i - 1])
                {
                    streak++;
                    sum += BLUE * streak;
                }
                else
                {
                    streak = 1;
                    sum += BLUE;
                }
            }
        }
        cout << endl
             << "String: " << str << endl
             << "Sum: " << sum << endl;
    }
};

int main()
{
    Boxes box;
    box.Print();
}