#include <ctime>
#include <iostream>
#include <numeric>
#include <fstream>
#include <iterator>

#include "generators/RandomGenerator.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"
#include "exploration/BestFirstSearch.hpp"

using namespace types;
using namespace std::placeholders;

double clock_tToMilliSeconds(std::clock_t value) {
    return 1000. * value/CLOCKS_PER_SEC;
}

std::clock_t execute(ReachabilityGame &game) {
    std::clock_t start = std::clock();

    exploration::bestFirstSearch(game, std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2));

    std::clock_t end = std::clock();

    return end-start;
}

std::tuple<double, double> values(std::vector<std::clock_t> &tab) {
    double mean = clock_tToMilliSeconds(std::accumulate(tab.begin(), tab.end(), 0) / tab.size());

    // On va calculer la médianne
    double median;
    std::sort(tab.begin(), tab.end());
    if (tab.size() % 2 == 0) {
        median = clock_tToMilliSeconds((tab[tab.size()/2 - 1] + tab[tab.size()/2])/2);
    }
    else {
        median = clock_tToMilliSeconds(tab[tab.size()/2]);
    }

    return std::make_tuple(mean, median);
}

int main()
{

    std::size_t nGenerations = 1000;
    //std::ofstream naive("../plots/naiveSize.data");
    std::ofstream tree("../plots/treeSize.data");

    std::size_t size = 20;
    std::size_t lowOutgoing = 1;
    std::size_t upOutgoing = 5;
    long minWeight = 1;
    long maxWeight = 1;
    bool multipleWeights = false;
    std::size_t nPlayers = 2;
    bool sharedTargets = true;
    std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
    std::vector<double> probaTargets(nPlayers, 0.1);
    std::vector<Long> maximumTargets(nPlayers, Long::infinity);

    std::size_t lowBranchingFactor = 1;
    std::size_t upBranchingFactor = 5;
    double probaSelf = 0.5;
    double probaSameDepth = 0.5;
    double probaSkipping = 0.5;
    double probaClimbing = 0.5;

    /*
    naive << std::boolalpha << "# outgoing in [" << lowOutgoing << ", " << upOutgoing << "]; weights in [" << minWeight << ", " << maxWeight << "]; mutlipleWeight=" << multipleWeights << "; nPlayers=" << nPlayers << "; sharedTargets=" << sharedTargets << "; probaPlayers=(";
    std::copy(probaPlayers.begin(), probaPlayers.end(), std::ostream_iterator<double>(naive, ", "));
    naive << "); probaTargets=(";
    std::copy(probaTargets.begin(), probaTargets.end(), std::ostream_iterator<double>(naive, ", "));
    naive << "); maximumTargets=(";
    std::copy(maximumTargets.begin(), maximumTargets.end(), std::ostream_iterator<Long>(naive, ", "));
    naive << ")\n";
    */

    tree << std::boolalpha << "# branchingFactor in [" << lowBranchingFactor << ", " << upBranchingFactor << "]; probaSelf=" << probaSelf << "; probaSameDetph=" << probaSameDepth << "; probaSkipping=" << probaSkipping << "; probaClimbing=" << probaClimbing << "; weights in [" << minWeight << ", " << maxWeight << "]; mutlipleWeight=" << multipleWeights << "; nPlayers=" << nPlayers << "; sharedTargets=" << sharedTargets << "; probaPlayers=(";
    std::copy(probaPlayers.begin(), probaPlayers.end(), std::ostream_iterator<double>(tree, ", "));
    tree << "); probaTargets=(";
    std::copy(probaTargets.begin(), probaTargets.end(), std::ostream_iterator<double>(tree, ", "));
    tree << "); maximumTargets=(";
    std::copy(maximumTargets.begin(), maximumTargets.end(), std::ostream_iterator<Long>(tree, ", "));
    tree << ")\n";

    for (size = 5 ; size < 51 ; size++) {
        //std::vector<std::clock_t> timesNaive(nGenerations, 0);
        std::vector<std::clock_t> timesTree(nGenerations, 0);

        for (std::size_t i = 0 ; i < nGenerations ; i++) {
            /*
            ReachabilityGame game = generators::randomGenerator(size, lowBranchingFactor, upBranchingFactor, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);

            while (game.percentageOfReachableVertices() < 70) {
                game = generators::randomGenerator(size, lowBranchingFactor, upBranchingFactor, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
            }

            timesNaive[i] = execute(game);
            */

            ReachabilityGame game = generators::randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSelf, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
        
            timesTree[i] = execute(game);
        }

        //double meanNaive, medianNaive, meanTree, medianTree;
        //std::tie(meanNaive, medianNaive) = values(timesNaive);
        //std::tie(meanTree, medianTree) = values(timesTree);

        std::cout << size << '\n';
        //naive << size << '\t' << meanNaive << '\t' << medianNaive << '\n';
        //tree << size << '\t' << meanTree << '\t' << medianTree << '\n';
    }

    //naive.close();
    tree.close();

    return 0;
}