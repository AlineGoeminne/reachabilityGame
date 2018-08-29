#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "MinMaxGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "exploration/RandomPaths.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"
#include "generators/RandomGenerator.hpp"
#include "generators/RandomStronglyConnectedGenerator.hpp"

using namespace exploration;
using namespace types;
using namespace std::placeholders;

int main() {
    ReachabilityGame game = generators::randomStronglyConnectedGenerator(10, 1, 5, 2, false);

    std::vector<Long> valuesJ1 = MinMaxGame::convert(game, 0).getValues(game.getPlayers()[0].getGoals());
    std::vector<Long> valuesJ2 = MinMaxGame::convert(game, 1).getValues(game.getPlayers()[1].getGoals());

    while (valuesJ1[0] == types::Long::infinity || valuesJ2[0] == types::Long::infinity || valuesJ1[0] == 0 || valuesJ2[0] == 0) {
        game = generators::randomStronglyConnectedGenerator(10, 1, 5, 2, false);

        valuesJ1 = MinMaxGame::convert(game, 0).getValues(game.getPlayers()[0].getGoals());
        valuesJ2 = MinMaxGame::convert(game, 1).getValues(game.getPlayers()[1].getGoals());
    }

    std::cout << valuesJ1[0] << ' ' << valuesJ2[0] << '\n';
    std::cout << game << '\n';
    game.printDOT();

    std::cout << exploration::bestFirstSearch(game, std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2)) << '\n';
}