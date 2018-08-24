#include "generators/RandomStronglyConnectedGenerator.hpp"
#include "algorithms/Tarjan.hpp"

int main() {
    for (int i = 0 ; i < 10000 ; i++) {
        std::cout << i << '\n';
        ReachabilityGame game = generators::randomStronglyConnectedGenerator(20, 1, 5, 1, 1, false, 2, false, {0.5, 0.5}, {0.1, 0.1}, {types::Long::infinity, types::Long::infinity});
    }

    return 0;
}