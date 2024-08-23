#include <array>
#include <string>

enum class Difficulty {EASY, MEDIUM, HARD};

class TicTacToe
{

    using Grid = std::array<std::string, 9>;

    Grid board;

    Difficulty difficulty;

    std::string Computer;
    std::string Player;

    int minimax(Grid&, bool);
    int BestMoveEasy(Grid);
    int BestMoveMedium(Grid);
    int BestMoveHard(Grid);

public:

    TicTacToe(Difficulty diff, std::string symbol) : difficulty(diff), Player(symbol)
    {
        board.fill(" ");
        Computer = (Player == "X" ? "O" : "X");
    }

    int BestMove();
    std::string GetWinner(Grid);
    bool IsGridFull(Grid);
    void GameUI();
};
