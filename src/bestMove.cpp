#include "options.hpp"
#include <random>
#include <chrono>

int TicTacToe::minimax(Grid& g, bool isMaximizing)
{
    std::string winner = GetWinner(g);
    if (winner == Computer)
        return 1;
    else if (winner == Player)
        return -1;
    else if (IsGridFull(g))
        return 0;

    int bestScore = isMaximizing ? -1 : 1;
    for (int i = 0; i < 9; i++)
    {
        if (g[i] != " ")
            continue;

        g[i] = isMaximizing ? Computer : Player;
        int currScore = minimax(g, !isMaximizing);
        g[i] = " ";

        bestScore = isMaximizing ? std::max(bestScore, currScore) : std::min(bestScore, currScore);
    }

    return bestScore;
}

int TicTacToe::BestMoveEasy(Grid grid)
{
    std::vector<int> emptyCells;
    for (int i = 0; i < 9; i++)
        if (grid[i] == " ") emptyCells.push_back(i);

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dist(0, emptyCells.size() - 1);
    return emptyCells[dist(gen)];
}

int TicTacToe::BestMoveMedium(Grid grid)
{
    std::vector<int> emptyCells;
    for (int i = 0; i < 9; i++)
        if (grid[i] == " ") emptyCells.push_back(i);

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dist(0, emptyCells.size() - 1);
    return emptyCells[dist(gen)];
}

int TicTacToe::BestMoveHard(Grid grid)
{
    int bestScore = -1;
    std::vector<int> bestMoves;
    for (int i = 0; i < 9; i++)
    {
        if (grid[i] != " ")
            continue;

        grid[i] = Computer;
        int currScore = minimax(grid, 0);
        grid[i] = " ";

        if (currScore > bestScore)
        {
            bestScore = currScore;
            bestMoves.clear();
            bestMoves.push_back(i);
        }
        if (currScore == bestScore)
            bestMoves.push_back(i);
    }

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dist(0, bestMoves.size() - 1);
    return bestMoves[dist(gen)];
}

int TicTacToe::BestMove()
{
    switch (difficulty)
    {
        case Difficulty::EASY:
            return BestMoveEasy(board);
            break;
        case Difficulty::MEDIUM:
            return BestMoveMedium(board);
            break;
        default:
            return BestMoveHard(board);
    }
}
