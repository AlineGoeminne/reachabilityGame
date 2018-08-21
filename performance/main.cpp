#include <ctime>
#include <iostream>
#include <numeric>

#include "generators/RandomGenerator.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"
#include "exploration/BestFirstSearch.hpp"

double clock_tToMilliSeconds(std::clock_t value) {
    return 1000. * value/CLOCKS_PER_SEC;
}

int main()
{
    using namespace std::placeholders;

    std::size_t nGenerations = 1000;

    std::cout << "Taille\tMoyenne\tMédianne\n";

    for (std::size_t size = 5 ; size < 101 ; size++) {
        std::vector<std::clock_t> times(nGenerations, 0);

        for (std::size_t i = 0 ; i < nGenerations ; i++) {
            //ReachabilityGame game = generators::randomGenerator(size, 1, 5, 2, false);
            ReachabilityGame game = generators::randomTreeLikeGenerator(size, 1, 5, 0.5, 0.5, 0.5, false, 2, false);

            std::clock_t start = std::clock();

            exploration::bestFirstSearch(game, std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2, _3));

            std::clock_t end = std::clock();

            times[i] = end-start;
        }

        double mean = clock_tToMilliSeconds(std::accumulate(times.begin(), times.end(), 0) / nGenerations);

        // On va calculer la médianne
        double median;
        std::sort(times.begin(), times.end());
        if (times.size() % 2 == 0) {
            median = clock_tToMilliSeconds((times[times.size()/2 - 1] + times[times.size()/2])/2);
        }
        else {
            median = clock_tToMilliSeconds(times[times.size()/2]);
        }

        std::cout << size << '\t' << mean << '\t' << median << '\n';
    }

    return 0;
}