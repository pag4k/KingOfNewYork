#include <vector>
#include <string>
#include "common.h"
#include <memory>

#include "map.h"
#include "card.h"
#include "tile.h"
#include <borough.h>

class FPlayer;

class FGame
{
public:
    FGame(int NumberOfPlayer);
    ~FGame();

    void Print();

private:
    FMap *Map =  nullptr;
    int Number_of_Players;
    std::vector<std::shared_ptr<FPlayer>> Players;
    std::vector<std::shared_ptr<FPlayer>> PlayersInManhattan;
    std::shared_ptr<FPlayer> Superstar;
    std::shared_ptr<FPlayer> StatusOfLiberty;
    FDeck Deck;
    FDeck DiscardDeck;
    FTileStack TileStack;
    int TokenInventory[NUMBER_OF_TOKEN_TYPE];
    int EnergyCubes;

    //TODO: ADD CARD BUYING CODE.
    std::unique_ptr<FCard> AvailableCards[MAXIMUM_AVAILABLE_CARDS];
};

