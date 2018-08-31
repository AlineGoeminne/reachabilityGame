#include "generators/RandomStronglyConnectedGenerator.hpp"
#include "algorithms/Tarjan.hpp"

int main() {
    ReachabilityGame game = generators::randomStronglyConnectedGenerator(10, 1, 3, 1, 10, true, 2, false, {0.2, 0.8}, {0.7, 0.1}, {2, 3});
    std::cout << game << '\n';

    return 0;
}