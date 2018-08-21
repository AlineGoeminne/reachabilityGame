#include "generators/RandomTreeLikeGenerator.hpp"

int main() {
    ReachabilityGame game = generators::randomTreeLikeGenerator(10000, 3, 5, 0.25, 0.25, 0.25, 1, 1, false, 2, false, {1, 0}, {0.1, 0.1}, {types::Long::infinity, types::Long::infinity});

    game.printDOT();

    return 0;
}
