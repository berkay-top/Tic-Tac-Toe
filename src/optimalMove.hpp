#include <array>
#include <utility>

enum class State {Player, NoOne, Computer};
using Player = State;

using Cell = std::pair<int, int>;
using Move = Cell;
using grid = std::array<std::array<State, 3>, 3>;

Player check_win(grid);
Move optimalMove(grid);
