#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

/*
nápad:
strategie, co hraje jako tit for tat,
ale jeste k tomu umi byt zakernejsi
-> na začátku bude defect a
pokud jí prochazí defect porad tak u toho zustane
*/

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

class Tournament
{
private:
    std::vector<Player *> Players;
    std::vector<Game *> Games;

public:
    Tournament(std::vector<Player *> Ps)
    {
        this->Players = Ps;
    }

    std::vector<Game *> generateGames(std::vector<Player *> Players);
    void simulateTournament();
    void printResults();
};

std::vector<Game *> Tournament::generateGames(std::vector<Player *> Players)
{
    std::vector<Game *> generatedGames;

    for (size_t i = 0; i < Players.size(); i++)
    {
        for (size_t j = i + 1; j < Players.size(); j++)
        {
            Round *r = new Round(Players[i], Players[j]);
            Game *g = new Game(Players[i], Players[j], r, 300, 3, 0, 5, 1, true);
            generatedGames.push_back(g);
        }
    }

    this->Games = generatedGames;
    return generatedGames;
}

void Tournament::simulateTournament()
{
    for (Game *game : this->Games)
    {
        game->simulateGame();
    }
}

void Tournament::printResults()
{
    cout << "=== Tournament Results ===" << endl;
    for (Player *player : this->Players)
    {
        cout << player->getName() << " has " << player->getPoints() << " points." << endl;
    }
}

int main()
{
    srand(time(NULL)); // Inicializace random seed pro náhodnou strategii

    Random *random = new Random(0);
    // === STRATEGIE ===
    Strategy *alwaysCooperateStrategy = new Strategy(random, 0, true, true, true, true, false, true);
    Strategy *alwaysDefectStrategy = new Strategy(random, 0, false, false, false, false, false, true);
    Strategy *titForTatStrategy = new Strategy(random, 0, true, true, false, true, false, true);
    // !!!!!!!!!!!!!!!!!!
    Strategy *grimTriggerStrategy = new Strategy(random, 0, true, true, true, false, false, true);
    Strategy *randomStrategy1 = new Strategy(random, 10, true, true, true, true, false, true);
    Strategy *suspiciousTitForTat = new Strategy(random, 0, false, true, false, true, false, true);
    Strategy *titForTwoTats = new Strategy(random, 0, true, true, false, true, false, true);
    Strategy *pavlovStrategy = new Strategy(random, 1, true, false, true, false, true, false);
    Strategy *prober = new Strategy(random, 0, false, true, true, true, false, true);
    Strategy *hardTitForTat = new Strategy(random, 0, true, true, false, false, false, true);
    Strategy *softGrim = new Strategy(random, 7, true, true, false, true, false, true);
    Strategy *randomStrategy2 = new Strategy(random, 2, true, true, false, true, false, true);
    Strategy *randomStrategy3 = new Strategy(random, 1, true, true, false, true, false, true);
    Strategy *randomStrategy4 = new Strategy(random, 3, true, true, false, true, false, true);

    // === HRÁČI ===
    Player *alwaysCooperatePlayer = new Player(alwaysCooperateStrategy, 0, true, "Always Cooperate", 0, true);
    Player *alwaysDefectPlayer = new Player(alwaysDefectStrategy, 0, false, "Always Defect", 0, false);
    Player *titForTatPlayer = new Player(titForTatStrategy, 0, true, "Tit for Tat", 0, true);
    Player *grimTriggerPlayer = new Player(grimTriggerStrategy, 0, true, "Grim Trigger", 0, true);
    Player *randomPlayer1 = new Player(randomStrategy1, 0, true, "Random Player", 0, true);
    Player *randomPlayer2 = new Player(randomStrategy2, 0, true, "Random Player", 0, true);
    Player *randomPlayer3 = new Player(randomStrategy3, 0, true, "Random Player", 0, true);
    Player *randomPlayer4 = new Player(randomStrategy4, 0, true, "Random Player", 0, true);
    Player *suspiciousTitForTatPlayer = new Player(suspiciousTitForTat, 0, false, "Suspicious Tit for Tat", 0, false);
    Player *titForTwoTatsPlayer = new Player(titForTwoTats, 0, true, "Tit for Two Tats", 0, true);
    Player *pavlovPlayer = new Player(pavlovStrategy, 0, true, "Pavlov", 0, true);
    Player *proberPlayer = new Player(prober, 0, false, "Prober", 0, false);
    Player *hardTitForTatPlayer = new Player(hardTitForTat, 0, true, "Hard Tit for Tat", 0, true);
    Player *softGrimPlayer = new Player(softGrim, 0, true, "Soft Grim", 0, true);

    // === VEKTOR HRÁČŮ ===
    std::vector<Player *> players = {
        alwaysCooperatePlayer,
        alwaysDefectPlayer,
        titForTatPlayer,
        grimTriggerPlayer,
        randomPlayer1,
        randomPlayer2,
        randomPlayer3,
        randomPlayer4,
        suspiciousTitForTatPlayer,
        titForTwoTatsPlayer,
        pavlovPlayer,
        proberPlayer,
        hardTitForTatPlayer,
        softGrimPlayer};

    for (Player *player : players)
    {
        // strateg
        player->getStrategy()->setIntensity();
        player->initialize_lpp();
    }

    // === TURNAJ ===
    Tournament tournament(players);

    tournament.generateGames(players);
    tournament.simulateTournament();
    tournament.simulateTournament();
    tournament.simulateTournament();
    tournament.simulateTournament();
    tournament.simulateTournament();
    tournament.printResults();

    for (Player *player : players)
    {
        delete player->getStrategy();
        delete player;
    }

    return 0;
}
