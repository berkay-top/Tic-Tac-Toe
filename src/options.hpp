#include <array>
#include <string>

enum class Difficulty {EASY, MEDIUM, HARD};

using Move = int;
using Grid = std::array<std::string, 9>;

const std::string Computer = "O";
const std::string Player = "X";

Move BestMove(Difficulty, Grid);
std::string GetWinner(Grid);
bool IsGridFull(Grid);
