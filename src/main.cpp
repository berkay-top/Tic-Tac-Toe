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

void TicTacToe::GameUI()
{
    auto screen = ScreenInteractive::FitComponent();

    if (Computer == "X")
        board[BestMove()] = Computer;

    int gameOver = 0;

    auto checkFinish = [&]()
    {
        auto winner = GetWinner(board);
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
        else if (IsGridFull(board))
        {
            gameOver = 3;
            screen.ExitLoopClosure()();
            return true;
        }

        return false;
    };

    Components b(9);
    for (int i = 0; i < 9; i++)
        b[i] = Button(&board[i], [&, i]() {
            if (board[i] != " ")
                return;

            board[i] = Player;

            if (checkFinish())
                return;

            board[BestMove()] = Computer;

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

int main()
{
    auto screen = ScreenInteractive::TerminalOutput();
    
    int tg1_selected = 0, tg2_selected = 0;
    std::vector<std::string> tg1_entries = {"Easy", "Medium", "Hard"};
    std::vector<std::string> tg2_entries = {"X", "O"};
    auto tg1 = Toggle(&tg1_entries, &tg1_selected);
    auto tg2 = Toggle(&tg2_entries, &tg2_selected);

    auto container = Container::Vertical({tg1, tg2});

    auto renderer = Renderer(container, [&]() {
        return vbox({
            text("Choose game options, then press <Enter>:"),
            text(""),
            hbox(text("Difficulty: "), tg1 -> Render()),
            hbox(text("Symbol (X goes first): "), tg2 -> Render())
        });
    });

    auto component = CatchEvent(renderer, [&](Event event) {
        if (event == Event::Return)
        {
            screen.ExitLoopClosure()();
            return true;
        }

        return false;
    });

    screen.Loop(component);

    TicTacToe game(static_cast<Difficulty>(tg1_selected), tg2_entries[tg2_selected]);
    game.GameUI();
}
