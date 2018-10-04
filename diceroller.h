#include <string>
#include "common.h"

struct FDiceResult;

class FDiceRoller {
public :
    FDiceRoller();
    ~FDiceRoller(){};

    FDiceResult BeginRolling();
    void PrintRollHistory();

private :
    EDiceFace RollDice(int FaceNumber);
    //TODO: ADD GREEN DICE!
    //The numberof dices.
    int DiceNumber;
    //The maximum number of rolls.
    int RollNumber;
    //The number of rolls for the current turn.
    int RollCount;

    int RollHistory[NUMBER_OF_FACES_ON_DICE];

};