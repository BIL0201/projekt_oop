
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;

class Random
{
private:
    int intensity;

public:
    Random(int i)
    {
        this->intensity = i;
    }
    bool controlledRandom();
    void changeIntensity(int a);
};

void Random::changeIntensity(int a)
{
    this->intensity = a;
}
bool Random::controlledRandom()
{
    int roll = rand() % 10 + 1; // hodím číslo 1-10

    if (roll <= this->intensity)
    {
        // když jsme "uspěli", tak vrátíme náhodnou 0 nebo 1
        return rand() % 2;
    }
    else
    {
        // když neuspějeme, tak třeba vrátíme false (nebo si to můžeš přizpůsobit)
        return true;
    }
}