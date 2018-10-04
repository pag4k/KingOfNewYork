#include <vector>
#include <string>

class FPlayer;

class FGame
{
public:
  FGame(int NumberOfPlayer);
  ~FGame();


private:
    int Number_of_Players;
    std::vector<FPlayer *> Players;
};

