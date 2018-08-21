#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "MinMaxGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"

using namespace exploration;
using namespace types;

int main() {
    using namespace std::placeholders;
    ReachabilityGame game = generators::randomTreeLikeGenerator(10, 1, 3, 0.5, 0.5, 0.5, false, 2, true);

    heuristicSignature fun = std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2, _3);

    Path p = bestFirstSearch(game, fun);

    return 0;
}