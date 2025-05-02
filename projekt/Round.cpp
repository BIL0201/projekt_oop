#include "Player.cpp"

class Round
{
private:
    Player *Player1;
    Player *Player2;

public:
    Round(Player *P1, Player *P2)
    {
        this->Player1 = P1;
        this->Player2 = P2;
    }

    void simulateRound();
};

void Round::simulateRound()
{
    Strategy *strat1 = Player1->getStrategy();
    Strategy *strat2 = Player2->getStrategy();
    bool move1;
    bool move2;

    if (strat1->getMovesStrategy()) // pozdeji implementace
    {
        if (Player1->getLastPlayAgainst() == true)
        {
            move1 = strat1->getReactToCoop();
        }
        else
        {
            move1 = strat1->getReactToDefect();
        }
    }

    if (strat2->getMovesStrategy())
    {
        if (Player2->getLastPlayAgainst() == true)
        {
            move2 = strat2->getReactToCoop();
        }
        else
        {
            move2 = strat2->getReactToDefect();
        }
    }

    /*
    každá strategie má zatím pointsstrategy anebo movesstrategy
    */

    if (strat1->getPointsStrategy())
    {
        if (Player1->getLastPlayPoints() == 5)
        {
            move1 = Player1->getLastPlay();
        }
        else if (Player1->getLastPlayPoints() == 3)
        {
            move1 = Player1->getLastPlay();
        }
        else
        {
            move1 = !Player1->getLastPlay();
        }
    }

    if (strat2->getPointsStrategy())
    {
        if (Player2->getLastPlayPoints() == 5)
        {
            move1 = Player2->getLastPlay();
        }
        else if (Player2->getLastPlayPoints() == 3)
        {
            move1 = Player2->getLastPlay();
        }
        else
        {
            move1 = !Player2->getLastPlay();
        }
    }

    /*
    RANDOM
    */

    if (strat1->getRandomness()->controlledRandom() == false)
    {
        move1 = !move1;
    }

    if (strat2->getRandomness()->controlledRandom() == false)
    {
        move2 = !move2;
    }

    if (move1 == true && move2 == true)
    {
        Player1->changePoints(3);
        Player2->changePoints(3);
    }
    else if (move1 == true && move2 == false)
    {
        Player1->changePoints(0);
        Player2->changePoints(5);
    }
    else if (move1 == false && move2 == true)
    {
        Player1->changePoints(5);
        Player2->changePoints(0);
    }
    else
    {
        Player1->changePoints(1);
        Player2->changePoints(1);
    }

    Player1->changeLastPlayAgainst(move2);
    Player2->changeLastPlayAgainst(move1);
}
