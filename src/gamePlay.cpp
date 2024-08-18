#include "optimalMove.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

ButtonOption Style() {
    ButtonOption res;
    res.transform = [](const EntryState& s) {
        return text(s.label) | center | size(WIDTH, EQUAL, 3) | border;
    };
    return res;
};

int main()
{
    auto screen = ScreenInteractive::FitComponent();

    grid gameGrid;
    for (auto& row : gameGrid)
        std::fill(row.begin(), row.end(), State::NoOne);

    std::array<std::string, 9> cell;
    cell.fill(" ");

    bool winnerFound = 0;
    Player winner;
    int c = 0;

    auto button = [&] (int i) {
        return Button(&cell[i], [&, i]() {
            if (cell[i] == " ") {
                cell[i] = "O";
                gameGrid[i / 3][i % 3] = State::Player;
                c++;

                if (check_win(gameGrid) != Player::NoOne || c == 9)
                {
                    winnerFound = true;
                    winner = check_win(gameGrid);
                    screen.ExitLoopClosure()();
                    return;
                }

                Move mv = optimalMove(gameGrid);
                cell[mv.first * 3 + mv.second] = "X";
                gameGrid[mv.first][mv.second] = State::Computer;
                c++;

                if (check_win(gameGrid) != Player::NoOne || c == 9)
                {
                    winnerFound = true;
                    winner = check_win(gameGrid);
                    screen.ExitLoopClosure()();
                    return;
                }
            }
        }, Style());
    };

    auto row1 = Container::Horizontal({ button(0), button(1), button(2) });
    auto row2 = Container::Horizontal({ button(3), button(4), button(5) });
    auto row3 = Container::Horizontal({ button(6), button(7), button(8) });

    auto layout = Container::Vertical({ row1, row2, row3 });

    auto renderer = Renderer(layout, [&]() {
        if (winnerFound) {
            if (winner == Player::Player)
                return text("You won!") | bold;
            else if (winner == Player::Computer)
                return text("Skill issue!") | bold;
            else
                return text("Draw!") | bold;
        }

        return vbox({
            text("Tic-Tac-Toe") | bold | center,
            separator(),
            layout -> Render()
        });
    });

    screen.Loop(renderer);
}
