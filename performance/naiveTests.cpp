#include <ctime>
#include <iostream>
#include <numeric>
#include <fstream>
#include <iterator>

#include "generators/RandomGenerator.hpp"
#include "exploration/BestFirstSearch.hpp"

#include "common.hpp"

using namespace types;

int main()
{
    std::size_t nGenerations = 1000;
    std::ofstream naive("../plots/naiveSize.data");

    std::size_t size = 20;
    std::size_t lowOutgoing = 1;
    std::size_t upOutgoing = 5;
    long minWeight = 1;
    long maxWeight = 1;
    bool multipleWeights = false;
    std::size_t nPlayers = 5;
    bool sharedTargets = true;

    naive << std::boolalpha << "# size=" << size << "; outgoing in [" << lowOutgoing << ", " << upOutgoing << "]; weights in [" << minWeight << ", " << maxWeight << "]; mutlipleWeight=" << multipleWeights << "; nPlayers=" << nPlayers << "; sharedTargets=" << sharedTargets << "; probaPlayers=1/nPlayers; probaTargets=0.1; maximumTargets=infinity\n";

    for (size = 5 ; size <= 50 ; size++) {
        std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
        std::vector<double> probaTargets(nPlayers, 0.1);
        std::vector<Long> maximumTargets(nPlayers, Long::infinity);

        std::vector<std::clock_t> timesNaive(nGenerations, 0);

        std::size_t nTimeOut = 0;

        for (std::size_t i = 0 ; i < nGenerations ; i++) {
            std::cout << "GENERATION " << i << '\n';
            ReachabilityGame game = generators::randomGenerator(size, lowOutgoing, upOutgoing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);

            while (game.percentageOfReachableVertices() < 70) {
                game = generators::randomGenerator(size, lowOutgoing, upOutgoing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
            }

            try {
                timesNaive[i] = execute(game);
            }
            catch(std::runtime_error &e) {
                timesNaive[i] = 10;
                nTimeOut++;
            }
        }

        double meanNaive, medianNaive;
        std::tie(meanNaive, medianNaive) = values(timesNaive);

        std::cout << size << '\n';
        naive << size << '\t' << meanNaive << '\t' << medianNaive << '\t' << nTimeOut << '\n';
        naive.flush();
    }

    naive.close();

    return 0;
}