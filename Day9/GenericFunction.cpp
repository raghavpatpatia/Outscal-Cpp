#include <iostream>
using namespace std;

template <typename T>
void AddScore(T currentScore, T updatedScore)
{
    cout << endl <<"The updated score(current score + new score) is: " << currentScore + updatedScore << endl;
}

int main()
{
    int number1, number2;
    float score1, score2;
    cout << endl << "Enter (integer) current score: ";
    cin >> number1;
    cout << endl << "Enter (integer) additional score: ";
    cin >> number2;
    AddScore<int>(number1, number2); // Generic function for integer type
    cout << endl << "Enter (float) current score: ";
    cin >> score1;
    cout << endl << "Enter (float) additional score: ";
    cin >> score2;
    AddScore<float>(score1, score2); // Generic function for float type
    return 0;
}