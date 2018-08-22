#include "generators/RandomTreeLikeGenerator.hpp"

int main() {
    ReachabilityGame game = generators::randomTreeLikeGenerator(100, 3, 5, 0, 0, 0, 1, 1, false, 2, false, {0.5, 0.5}, {0.1, 0.1}, {types::Long::infinity, types::Long::infinity});

    game.printDOT();

    return 0;
}
