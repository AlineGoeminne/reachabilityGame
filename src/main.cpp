#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "MinMaxGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "generators/RandomGenerator.hpp"

using namespace exploration;
using namespace types;

int main() {
    using namespace std::placeholders;
    for (int i = 0 ; i < 1000 ; i++) {
        ReachabilityGame game = generators::randomGenerator(50, 1, 10, 2, false);

        heuristicSignature fun = std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2, _3);

        Path p = bestFirstSearch(game, fun);
    }

    return 0;
}