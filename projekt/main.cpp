
#include "Tournament.cpp"

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
