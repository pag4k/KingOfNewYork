#include <vector>
#include <string>
#include "common.h"

#include "graph.h"
#include "card.h"
#include "tile.h"

class FPlayer;

class FGame
{
public:
    FGame(int NumberOfPlayer);
    ~FGame();

    void Print();

private:
    FGraph Graph;
    int Number_of_Players;
    std::vector<FPlayer *> Players;
    std::vector<FPlayer *> PlayersInManhattan;
    FPlayer *Superstar;
    FPlayer *StatusOfLiberty;
    FDeck Deck;
    FDeck DiscardDeck;
    FTileStack TileStack;
    int TokenInventory[NUMBER_OF_TOKEN_TYPE];
    int EnergyCubes;

    //TODO: ADD CARD BUYING CODE.
    FCard *AvailableCards[MAXIMUM_AVAILABLE_CARDS];
};

