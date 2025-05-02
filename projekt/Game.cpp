
#include "Round.cpp"

class Game
{
private:
    Player *Player1;
    Player *Player2;
    Round *round;
    int num_rounds;
    int rew_cc;
    int rew_cd;
    int rew_dc;
    int rew_dd;
    bool cooperate;

public:
    Game(Player *p1, Player *p2, Round *R, int nr, int cc, int cd, int dc, int dd, bool coop)
    {
        this->Player1 = p1;
        this->Player2 = p2;
        this->round = R;
        this->num_rounds = nr;
        this->rew_cc = cc;
        this->rew_cd = cd;
        this->rew_dc = dc;
        this->rew_dd = dd;
        this->cooperate = coop;
    }
    Player *getPlayer1();
    Player *getPlayer2();
    Round *getRound();
    int getNumRounds();
    int getRewCC();
    int getRewCD();
    int getRewDC();
    int getRewDD();
    int getCoop();
    void simulateGame();
};

void Game::simulateGame()
{
    Player1->changeLastPlayAgainst(Player1->getStrategy()->getFirstMove());
    Player2->changeLastPlayAgainst(Player2->getStrategy()->getFirstMove());
    for (int i = 0; i < this->num_rounds; i++)
    {
        round->simulateRound();
    }
}

Player *Game::getPlayer1()
{
    return this->Player1;
}

Player *Game::getPlayer2()
{
    return this->Player2;
}

Round *Game::getRound()
{
    return this->round;
}

int Game::getNumRounds()
{
    return this->num_rounds;
}
int Game::getRewCC()
{
    return this->rew_cc;
}
int Game::getRewCD()
{
    return this->rew_cd;
}
int Game::getRewDC()
{
    return this->rew_dc;
}
int Game::getRewDD()
{
    return this->rew_dd;
}
int Game::getCoop()
{
    return this->cooperate;
}