#include <ctime>
#include <iostream>
#include <numeric>
#include <fstream>

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
    //std::ofstream output("../plots/naiveShared.data");
    std::ofstream output("../plots/treeShared.data");

    std::cout << "SharedTargets\tMoyenne\tMédianne\n";

    bool shared = false;
    do {
        std::vector<std::clock_t> times(nGenerations, 0);

        for (std::size_t i = 0 ; i < nGenerations ; i++) {
            //ReachabilityGame game = generators::randomGenerator(20, 1, 5, 5, shared);
            ReachabilityGame game = generators::randomTreeLikeGenerator(20, 1, 5, 0.5, 0.5, 0.5, false, 5, shared);

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

        std::cout << shared << '\t' << mean << '\t' << median << '\n';
        output << shared << '\t' << mean << '\t' << median << '\n';
        shared = !shared;
    } while (shared != false);

    output.close();

    return 0;
}