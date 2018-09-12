/*
 * ReachabilityGame - a program to compute the best Nash equilibrium in reachability games
 * Copyright (C) 2018 Gaëtan Staquet and Aline Goeminne
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
    std::ofstream tree("../plots/treePlayersSize.data", std::ios_base::app);

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

    for (nPlayers = 8 ; nPlayers <= 8 ; nPlayers++) {
        for (size = 18 ; size <= 30 ; size++) {
            std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
            std::vector<double> probaTargets(nPlayers, 0.1);
            std::vector<Long> maximumTargets(nPlayers, Long::infinity);

            std::vector<std::clock_t> timesTree(nGenerations, 0);
            std::size_t nTimeOut = 0;

            for (std::size_t i = 0 ; i < nGenerations ; i++) {
                std::cout << "GENERATION " << i << '\n';
                ReachabilityGame game = generators::randomTreeLikeGenerator(size, lowBranchingFactor, upBranchingFactor, probaSelf, probaSameDepth, probaSkipping, probaClimbing, minWeight, maxWeight, multipleWeights, nPlayers, sharedTargets, probaPlayers, probaTargets, maximumTargets);
            
                try {
                    timesTree[i] = execute(game);
                }
                catch(std::runtime_error &e) {
                    timesTree[i] = 10 * CLOCKS_PER_SEC; // Pour avoir 10 secondes
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