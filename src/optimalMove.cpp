#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "optimalMove.hpp"

Player Game::minimax(Grid grid, Player player)
{
    if (CheckWin(grid) != Player::NoOne || std::count(begin(grid), end(grid), " "))
        return CheckWin(grid);

    Player bestCase;
    if (player == Player::Computer)
    {
        bestCase = Player::Player;
        for (int i = 0; i < 9; i++)
            if (grid[i] == " ")
            {
                grid[i] = computerSymbol;
                Player currCase = minimax(grid, Player::Player);
                grid[i] = " ";

                bestCase = std::max(currCase, bestCase);
            }
    }
    else
    {
        bestCase = Player::Computer;
        for (int i = 0; i < 9; i++)
            if (grid[i] == " ")
            {
                grid[i] = computerSymbol;
                Player currCase = minimax(grid, Player::Computer);
                grid[i] = " ";

                bestCase = std::min(currCase, bestCase);
            }
    }

    return bestCase;
}

Move Game::OptimalMoveHard()
{
    Player bestCase = Player::Player;
    std::vector<Move> bestMoves;
    for (int i = 0; i < 9; i++)
        if (gameBoard[i] == " ")
        {
            gameBoard[i] = computerSymbol;
            Player currCase = minimax(gameBoard, Player::Computer);
            gameBoard[i] = " ";

            if (currCase > bestCase)
            {
                bestCase = currCase;
                bestMoves.clear();
                bestMoves.push_back(i);
            }
            else if (currCase == bestCase)
                bestMoves.push_back(i);
        }

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> rng(0, bestMoves.size() - 1);
    return bestMoves[rng(gen)];
}

Move Game::OptimalMove(Player player)
{
    switch (difficulty)
    {
        case DifficultyLevel::Easy:
            return OptimalMoveEasy();
        case DifficultyLevel::Medium:
            return OptimalMoveMedium();
        default:
            return OptimalMoveHard();
    }
}
