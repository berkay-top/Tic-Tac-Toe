#include "optimalMove.hpp"

Player Game::CheckWin(Grid grid) const
{
    auto f = [=](std::string symbol)
    {
        return (symbol.compare(computerSymbol) == 0 ? Player::Computer : Player::Player);
    };

    for (int i = 0; i < 9; i += 3)
    {
        if (grid[i] == grid[i + 1] && grid[i] == grid[i + 2])
            return f(grid[i]);
        if (grid[i / 3] == grid[i / 3 + 3] && grid[i / 3] == grid[i / 3 + 6])
            return f(grid[i / 3]);
    }

    if (grid[0] == grid[4] && grid[0] == grid[8])
        return f(grid[0]);

    if (grid[2] == grid[4] && grid[2] == grid[6])
        return f(grid[2]);

    return Player::NoOne;
}
