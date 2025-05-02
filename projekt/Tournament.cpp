
#include "Game.cpp"

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