#include "options.hpp"
#include <algorithm>

std::string GetWinner(Grid g)
{
    for (int i = 0; i < 9; i += 3)
        if (g[i] == g[i + 1] &&
            g[i] == g[i + 2] &&
            g[i] != " ") return g[i];

    for (int i = 0; i < 3; i++)
        if (g[i] == g[i + 3] &&
            g[i] == g[i + 6] &&
            g[i] != " ") return g[i];

    if (g[0] == g[4] &&
        g[0] == g[8] &&
        g[0] != " ") return g[0];

    if (g[2] == g[4] &&
        g[2] == g[6] &&
        g[2] != " ") return g[2];

    return " ";
}

bool IsGridFull(Grid g)
{
    return std::count(g.begin(), g.end(), " ") == 0;
}
