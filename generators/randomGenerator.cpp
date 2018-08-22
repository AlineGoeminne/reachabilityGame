#include <iostream>

#include "generators/RandomGenerator.hpp"

using namespace generators;

int main() {
    ReachabilityGame game = randomGenerator(100, 1, 10, 1, 1, true, 2, false, {0.5, 0.5}, {0, 0.5}, {2, types::Long::infinity});

    game.printDOT();

    //std::cout << game.numberOfReachableVertices() << '\n';

    return 0;
}