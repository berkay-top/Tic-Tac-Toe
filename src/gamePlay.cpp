#include "optimalMove.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

std::string gameMode;

int main()
{
    auto screen = ScreenInteractive::FitComponent();

    bool gameOver = 0;
    Components button;

    for (int i = 0; i < 9; i++)
    {
        auto onClick = [&, i]()
        {
            if (board[i] != " ")
                return;

            board[i] = playerLetter;
            
            if (moveCount == 9 || CheckWin(board) != Player::NoOne)
            {
                gameOver = 1;
                screen.ExitLoopClosure()();
                return;
            }

            Move nextMove = OptimalMove(difficulty, board, computerLetter);

            if (moveCount == 9 || CheckWin(board, computerLetter) != Player::NoOne)
            {
                gameOver = 1;
                screen.ExitLoopClosure()();
                return;
            }
        };

        button.push_back(Button(&board[i], onClick));
    }

    auto r1 = Container::Horizontal({ button[0], button[1], button[2] });
    auto r2 = Container::Horizontal({ button[0], button[1], button[2] });
    auto r3 = Container::Horizontal({ button[0], button[1], button[2] });

    auto buttonGrid = Container::Vertical({ r1, r2, r3 });

    auto element = [&]()
    {
        Elements elements = {
            text("Tic-Tac-Toe") | bold,
            separator(),
            buttonGrid -> Render()
        };

        if (!gameOver)
            return elements;

        Element txt;
        if (CheckWin(board) == Player::Computer)
            txt = text("Skill issue!");
        else if (CheckWin(board) == Player::Player)
            txt = text("You won!");
        else
            txt = text("Draw!");

        elements.push_back(txt | bold);

        return elements;
    };
}
