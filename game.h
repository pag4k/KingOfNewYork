#include <vector>
#include <string>
#include "common.h"

class FPlayer;
class FCard;
class FDeck;
class FTileStack;

class FGame
{
public:
  FGame(int NumberOfPlayer);
  ~FGame();


private:
    int Number_of_Players;
    std::vector<FPlayer *> Players;
    FPlayer *Superstar;
    FPlayer *StatusOfLiberty;
    FDeck *Deck;
    FTileStack *TileStack;

    //TODO: ADD CARD BUYING CODE.
    FCard *AvailableCards[MAXIMUM_AVAILABLE_CARDS];
};

