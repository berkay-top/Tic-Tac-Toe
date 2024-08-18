#include <vector>
#include <tuple>
#include "optimalMove.hpp"

std::vector<Cell> empty_cells(grid g)
{
    std::vector<Cell> res;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (g[i][j] == State::NoOne)
                res.push_back(std::make_pair(i, j));

    return res;
}

Player check_win(grid g)
{
    int c = 0;
    for (int i = 0; i < 3; i++)
    {
        if (g[i][0] == g[i][1] &&
            g[i][1] == g[i][2])
            return g[i][0];

        if (g[0][i] == g[1][i] &&
            g[1][i] == g[2][i])
            return g[0][i];
    }

    if (g[0][0] == g[1][1] &&
        g[1][1] == g[2][2])
        return g[0][0];

    if (g[0][2] == g[1][1] &&
        g[1][1] == g[2][0])
        return g[0][2];

    return Player::NoOne;
}

Player minimax(grid currGrid, Player currPlayer)
{
    Player Winner = check_win(currGrid);
    if (Winner != Player::NoOne)
        return Winner;

    auto emptyCells = empty_cells(currGrid);
    if (emptyCells.empty())
        return Player::NoOne;

    Player bestCase;
    if (currPlayer == Player::Computer)
    {
        bestCase = Player::Player;
        for (auto cell : emptyCells)
        {
            int x, y;
            std::tie(x, y) = cell;
            
            currGrid[x][y] = State::Computer;
            Player currCase = minimax(currGrid, Player::Player);
            currGrid[x][y] = State::NoOne;

            bestCase = std::max(bestCase, currCase);
        }
    }
    else
    {
        bestCase = Player::Computer;
        for (auto cell : emptyCells)
        {
            int x, y;
            std::tie(x, y) = cell;

            currGrid[x][y] = State::Player;
            Player currCase = minimax(currGrid, Player::Computer);
            currGrid[x][y] = State::NoOne;

            bestCase = std::min(bestCase, currCase);
        }
    }

    return bestCase;
}

Move optimalMove(grid currGrid)
{
    Player bestCase = Player::Player;
    Move bestMove = {-1, -1};
    std::vector<Cell> emptyCells = empty_cells(currGrid);
    for (auto cell : emptyCells)
    {
        int x, y;
        std::tie(x, y) = cell;
        currGrid[x][y] = State::Computer;
        Player currCase = minimax(currGrid, Player::Player);
        currGrid[x][y] = State::NoOne;

        if (currCase > bestCase)
        {
            bestCase = currCase;
            bestMove = cell;
        }
    }

    return bestMove;
}
