#include <vector>
#include <tuple>
#include "optimalMove.hpp"

std::vector<cell> empty_cells(grid g)
{
    std::vector<cell> res;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (g[i][j] == state::NoOne)
                res.push_back(std::make_pair(i, j));

    return res;
}

state check_win(grid g)
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

    return state::NoOne;
}

state minimax(grid currGrid, player currPlayer)
{
    state Winner = check_win(currGrid);
    if (Winner != state::NoOne)
        return Winner;

    auto emptyCells = empty_cells(currGrid);
    if (emptyCells.empty())
        return state::NoOne;

    state bestState;
    if (currPlayer == player::Computer)
    {
        bestState = state::Player;
        for (auto i : emptyCells)
        {
            int x, y;
            std::tie(x, y) = i;
            
            currGrid[x][y] = state::Computer;
            state currState = minimax(currGrid, player::Player);
            currGrid[x][y] = state::NoOne;

            bestState = std::max(bestState, currState);
        }
    }
    else
    {
        bestState = state::Computer;
        for (auto i : emptyCells)
        {
            int x, y;
            std::tie(x, y) = i;

            currGrid[x][y] = state::Player;
            state currState = minimax(currGrid, player::Computer);
            currGrid[x][y] = state::NoOne;

            bestState = std::min(bestState, currState);
        }
    }

    return bestState;
}

move optimalMove(grid currGrid)
{
    state bestState = state::Player;
    move bestMove;
    std::vector<cell> emptyCells = empty_cells(currGrid);
    for (auto cell : emptyCells)
    {
        int x, y;
        std::tie(x, y) = cell;
        currGrid[x][y] = state::Computer;
        state currState = minimax(currGrid, player::Player);
        currGrid[x][y] = state::NoOne;

        if (currState > bestState)
        {
            bestState = currState;
            bestMove = cell;
        }
    }

    return bestMove;
}
