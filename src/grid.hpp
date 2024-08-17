#include <array>
#include <utility>

enum class player {Computer, Player};
enum class state {Computer = 1, Player = -1, NoOne = 0};

using cell = std::pair<int, int>;
using move = cell;
using grid = std::array<std::array<state, 3>, 3>;

state check_win(grid);
move optimalMove(grid);
