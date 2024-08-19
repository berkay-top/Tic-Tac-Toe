#include <array>
#include <string>

enum class Player {Player, NoOne, Computer};
enum class DifficultyLevel {Easy, Medium, Hard};

using Move = int;
using Grid = std::array<std::string, 9>;

class Game
{
    DifficultyLevel difficulty;
    std::string playerSymbol;
    std::string computerSymbol;
    Grid gameBoard;

    Player minimax(Grid, Player);
    Move OptimalMoveEasy();
    Move OptimalMoveMedium();
    Move OptimalMoveHard();

public:
    Player CheckWin(Grid) const;
    Move OptimalMove(Player player);
};
