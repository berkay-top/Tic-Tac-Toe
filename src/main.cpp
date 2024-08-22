#include "options.hpp"

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

using namespace ftxui;

ButtonOption Style()
{
    ButtonOption option;
    option.transform = [](const EntryState& s)
    {
        auto element = text(s.label) | center | size(WIDTH, EQUAL, 3) | border;
        if (s.focused)
            element |= color(Color::White);

        return element | color(Color::GrayDark);
    };

    return option;
}
 

int main()
{
    auto screen = ScreenInteractive::FitComponent();

    Grid grid; grid.fill(" ");
    int gameOver = 0;
    Difficulty diff = Difficulty::HARD;

    auto checkFinish = [&]()
    {
        auto winner = GetWinner(grid);
        if (winner.compare(Computer) == 0)
        {
            gameOver = 1;
            screen.ExitLoopClosure()();
            return true;
        }
        else if (winner.compare(Player) == 0)
        {
            gameOver = 2;
            screen.ExitLoopClosure()();
            return true;
        }
        else if (IsGridFull(grid))
        {
            gameOver = 3;
            screen.ExitLoopClosure()();
            return true;
        }

        return false;
    };

    Components b(9);
    for (int i = 0; i < 9; i++)
        b[i] = Button(&grid[i], [&, i]() {
            if (grid[i] != " ")
                return;

            grid[i] = Player;

            if (checkFinish())
                return;

            grid[BestMove(diff, grid)] = Computer;

            if (checkFinish())
                return;
        }, Style());

    auto r1 = Container::Horizontal({b[0], b[1], b[2]});
    auto r2 = Container::Horizontal({b[3], b[4], b[5]});
    auto r3 = Container::Horizontal({b[6], b[7], b[8]});

    auto layout = Container::Vertical({r1, r2, r3});

    auto renderer = Renderer(layout, [&]()
    {
        if (gameOver == 0)
            return window(text("Tic-Tac-Toe") | center, layout -> Render()) | color(Color::Blue);

        Element txt;
        if (gameOver == 1)
            txt = text("Skill issue!") | bold | center | border | flex | color(Color::Red);
        else if (gameOver == 2)
            txt = text("You won!") | bold | center | border | flex | color(Color::Green);
        else if (gameOver == 3)
            txt = text("Draw!") | bold | center | border | flex | color(Color::Yellow);

        return vbox({window(text("Tic-Tac-Toe") | center, layout -> Render()) | color(Color::Blue), txt});
    });

    screen.Loop(renderer);
}
