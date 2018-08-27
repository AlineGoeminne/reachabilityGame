#include <ctime>
#include <iostream>
#include <numeric>
#include <fstream>
#include <iterator>

#include "generators/RandomTreeLikeGenerator.hpp"
#include "exploration/BestFirstSearch.hpp"

#include "common.hpp"

using namespace types;
using namespace std::placeholders;

int main()
{
    std::size_t nGenerations = 1000;
    std::ofstream tree("../plots/treePlayersSize.data", std::ofstream::app);

    std::size_t size = 20;
    long minWeight = 1;
    long maxWeight = 1;
    bool multipleWeights = false;
    std::size_t nPlayers = 5;
    bool sharedTargets = true;

    std::size_t lowBranchingFactor = 1;
    std::size_t upBranchingFactor = 5;
    double probaSelf = 0.5;
    double probaSameDepth = 0.5;
    double probaSkipping = 0.5;
    double probaClimbing = 0.5;

    tree << std::boolalpha << "# size=" << size << "; branchingFactor in [" << lowBranchingFactor << ", " << upBranchingFactor << "]; probaSelf=" << probaSelf << "; probaSameDetph=" << probaSameDepth << "; probaSkipping=" << probaSkipping << "; probaClimbing=" << probaClimbing << "; weights in [" << minWeight << ", " << maxWeight << "]; mutlipleWeight=" << multipleWeights << "; nPlayers=" << nPlayers << "; sharedTargets=" << sharedTargets << "; probaPlayers=1/nPlayers; probaTargets=0.1; maximumTargets=infinity;\n";

    for (nPlayers = 2 ; nPlayers < 21 ; nPlayers++) {
        std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
        std::vector<double> probaTargets(nPlayers, 0.1);
        std::vector<Long> maximumTargets(nPlayers, Long::infinity);

        for (size = 5 ; size < 31 ; size++) {
            std::vector<std::clock_t> timesTree(nGenerations, 0);
            std::size_t nTimeOut = 0;

            for (std::size_t i = 0 ; i < nGenerations ; i++) {
                std::cout << "GENERATION " << i << '\n';
                ReachabilityGame game = generators::randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSelf, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
            
                try {
                    timesTree[i] = execute(game);
                }
                catch(std::runtime_error &e) {
                    timesTree[i] = 10;
                    nTimeOut++;
                }
            }

            double meanTree, medianTree;
            std::tie(meanTree, medianTree) = values(timesTree);

            std::cout << nPlayers << ' ' << size << '\n';
            tree << nPlayers << '\t' << size << '\t' << meanTree << '\t' << medianTree << '\t' << nTimeOut << '\n';
            tree.flush();
        }
    }

    tree.close();

    return 0;
}