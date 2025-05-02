

#include "Random.cpp"

class Strategy
{
private:
    /*
    typy strategií:
    řeší reakci na minule nebo reakci na body
    */
    Random *randomness;
    int randomness_intensity;
    bool points_strategy;
    bool moves_strategy;
    bool first_move;
    bool current_move;
    bool react_to_def;
    bool react_to_coop;

public:
    Strategy(Random *r, int ri, bool fm, bool cm, bool rtd, bool rtc, bool ps, bool ms)
    {
        this->randomness = r;
        this->randomness_intensity = ri;
        this->first_move = fm;
        this->current_move = cm;
        this->react_to_def = rtd;
        this->react_to_coop = rtc;
        this->points_strategy = ps;
        this->moves_strategy = ms;
    }

    bool getPointsStrategy();
    int getRandIntensity();
    bool getMovesStrategy();
    bool getFirstMove();
    bool getCurrentMove();
    bool getReactToDefect();
    bool getReactToCoop();
    void setIntensity();
    Random *getRandomness();
};

void Strategy::setIntensity()
{
    this->randomness->changeIntensity(this->randomness_intensity);
}

int Strategy::getRandIntensity()
{
    return this->randomness_intensity;
}
bool Strategy::getPointsStrategy()
{
    return this->points_strategy;
}
bool Strategy::getMovesStrategy()
{
    return this->moves_strategy;
}
bool Strategy::getCurrentMove()
{
    return this->current_move;
}
Random *Strategy::getRandomness()
{
    return this->randomness;
}
bool Strategy::getFirstMove()
{
    return this->first_move;
}
bool Strategy::getReactToDefect()
{
    return this->react_to_def;
}
bool Strategy::getReactToCoop()
{
    return this->react_to_coop;
}