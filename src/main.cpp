#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "MinMaxGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"
#include "generators/RandomGenerator.hpp"

using namespace exploration;
using namespace types;

int main() {
    using namespace std::placeholders;
    for (int i = 0 ; i < 1000 ; i++) {
        ReachabilityGame game = generators::randomGenerator(5, 1, 2, 1, 1, false, 2, true, {1./2, 1./2}, {0.1, 0.1}, {Long::infinity, Long::infinity});

        std::cout << i << '\n';

        heuristicSignature fun = std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2);

        bestFirstSearch(game, fun);
    }

    return 0;
}