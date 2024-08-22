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
        auto element = text(s.label) | center | size(WIDTH, EQUAL, 3) | borderLight;
        if (s.focused)
            element |= inverted;

        return element;
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
        if (GetWinner(grid).compare(Computer) == 0)
        {
            gameOver = 1;
            screen.ExitLoopClosure()();
            return true;
        }
        else if (GetWinner(grid).compare(Player) == 0)
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

    auto renderer = Renderer(layout, [&]() {
        Elements elements;
        elements.push_back(text("Tic-Tac-Toe") | bold | center);
        elements.push_back(separator());
        elements.push_back(layout -> Render());

        if (gameOver == 1)
            elements.push_back(text("Skill issue!"));
        else if (gameOver == 2)
            elements.push_back(text("You won!"));
        else if (gameOver == 3)
            elements.push_back(text("Draw!"));

        *elements.rbegin() |= center;

        return vbox(elements);
    });

    screen.Loop(renderer);
}
