#include "options.hpp"
#include <random>
#include <chrono>

int minimax(Grid& g, bool isMaximizing)
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

Move BestMoveEasy(Grid g)
{
    std::vector<int> emptyCells;
    for (int i = 0; i < 9; i++)
        if (g[i] == " ") emptyCells.push_back(i);

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dist(0, emptyCells.size() - 1);
    return emptyCells[dist(gen)];
}

Move BestMoveMedium(Grid g)
{
    std::vector<int> emptyCells;
    for (int i = 0; i < 9; i++)
        if (g[i] == " ") emptyCells.push_back(i);

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dist(0, emptyCells.size() - 1);
    return emptyCells[dist(gen)];
}

Move BestMoveHard(Grid g)
{
    int bestScore = -1;
    std::vector<Move> bestMoves;
    for (int i = 0; i < 9; i++)
    {
        if (g[i] != " ")
            continue;

        g[i] = Computer;
        int currScore = minimax(g, 0);
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

Move BestMove(Difficulty diff, Grid g)
{
    switch (diff)
    {
        case Difficulty::EASY:
            return BestMoveEasy(g);
            break;
        case Difficulty::MEDIUM:
            return BestMoveMedium(g);
            break;
        default:
            return BestMoveHard(g);
    }
}
