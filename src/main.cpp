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
    ReachabilityGame game = generators::randomTreeLikeGenerator(3, 1, 1, 0.0000000000000000001, 0, 0, 0, -10, 0, false, 2, false, {0.3, 0.7});

    std::cout << game << '\n';
}