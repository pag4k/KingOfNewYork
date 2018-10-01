#include <string>

const int FACE_NUMBER = 6;

enum class DiceFace
{
    None = -1,
    Attack = 0,
    Celebrity = 1,
    Destruction = 2,
    Energy = 3,
    Heal = 4,
    Ouch = 5
};

struct DiceResult
{
    DiceFace Dice[FACE_NUMBER];
};

class DiceRoller
{
public:
    DiceRoller(int DiceNumber, int RollNumber);
    ~DiceRoller() {};

    DiceResult BeginRolling();
    void PrintRollHistory();

private:
    DiceFace RollDice(int FaceNumber);
    std::string GetFaceName(DiceFace Face);

    //The numberof dices.
    int DiceNumber;
    //The maximum number of rolls.
    int RollNumber;
    //The number of rolls for the current turn.
    int RollCount;

    int RollHistory[FACE_NUMBER];



};