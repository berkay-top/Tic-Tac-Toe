#include "options.hpp"
#include <random>
#include <chrono>

int TicTacToe::minimax(Grid& g, bool isMaximizing, int depth)
{
    if (depth == 10)
        return 0;

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
        int currScore = minimax(g, !isMaximizing, depth + 1);
        g[i] = " ";

        bestScore = isMaximizing ? std::max(bestScore, currScore) : std::min(bestScore, currScore);
    }

    return bestScore;
}

int TicTacToe::BestMove()
{
    Grid g = board;
    int bestScore = -1;
    std::vector<int> bestMoves;
    for (int i = 0; i < 9; i++)
    {
        if (g[i] != " ")
            continue;

        g[i] = Computer;
        int currScore;
        if (difficulty == Difficulty::HARD)
            currScore = minimax(g, 0, 0);
        else if (difficulty == Difficulty::MEDIUM)
            currScore = minimax(g, 0, 5);
        else
            currScore = minimax(g, 0, 10);
        g[i] = " ";

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
