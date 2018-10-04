#include <vector>
#include <string>
#include "common.h"

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
    int Number_of_Players;
    std::vector<FPlayer *> Players;
    FPlayer *Superstar;
    FPlayer *StatusOfLiberty;
    FDeck Deck;
    FDeck DiscardDeck;
    FTileStack TileStack;
    int TokenInventory[NUMBER_OF_TOKEN_TYPE];

    //TODO: ADD CARD BUYING CODE.
    FCard *AvailableCards[MAXIMUM_AVAILABLE_CARDS];
};

