
#include "Strategy.cpp"

class Player
{
private:
    Strategy *strategy;
    int points;
    bool last_play_against;
    int last_play_points; // poslední body, co "uhrál" mělo by začínat na nule
    bool last_play;
    std::string name;

public:
    Player(Strategy *s, int p, bool lpa, const std::string &n, int lpp, bool lp)
    {
        this->strategy = s;
        this->points = p;
        this->last_play_against = lpa;
        this->name = n;
        this->last_play_points = lpp;
        this->last_play = lp;
    }
    bool getLastPlayAgainst();
    bool getLastPlay();
    int getLastPlayPoints();
    Strategy *getStrategy();
    int getPoints();
    void changePoints(int a);
    void changeLastPlayAgainst(bool move);
    void initialize_lpp();
    std::string getName();
};

void Player::initialize_lpp()
{
    this->last_play_points = 0;
}

bool Player::getLastPlay()
{
    return this->last_play;
}

int Player::getLastPlayPoints()
{
    return this->last_play_points;
}

std::string Player::getName()
{
    return this->name;
}

void Player::changeLastPlayAgainst(bool move)
{
    this->last_play_against = move;
}

void Player::changePoints(int a)
{
    this->points += a;
}

bool Player::getLastPlayAgainst()
{
    return this->last_play_against;
}

Strategy *Player::getStrategy()
{
    return this->strategy;
}

int Player::getPoints()
{
    return this->points;
}
