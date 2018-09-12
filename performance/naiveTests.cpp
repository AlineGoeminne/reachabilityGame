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

#include "generators/RandomGenerator.hpp"
#include "exploration/BestFirstSearch.hpp"

#include "common.hpp"

using namespace types;

int main()
{
    std::size_t nGenerations = 1000;
    std::ofstream naive("../plots/naivePlayersSize.data");

    std::size_t size = 20;
    std::size_t lowOutgoing = 1;
    std::size_t upOutgoing = 5;
    long minWeight = 1;
    long maxWeight = 1;
    bool multipleWeights = false;
    std::size_t nPlayers = 5;
    bool sharedTargets = true;

    naive << std::boolalpha << "# size=" << size << "; outgoing in [" << lowOutgoing << ", " << upOutgoing << "]; weights in [" << minWeight << ", " << maxWeight << "]; mutlipleWeight=" << multipleWeights << "; nPlayers=" << nPlayers << "; sharedTargets=" << sharedTargets << "; probaPlayers=1/nPlayers; probaTargets=0.1; maximumTargets=infinity\n";

    for (nPlayers = 2 ; nPlayers <= 10 ; nPlayers++) {
        for (size = 5 ; size <= 30 ; size++) {
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
                    timesNaive[i] = 10 * CLOCKS_PER_SEC; // Pour avoir 10 secondes
                    nTimeOut++;
                }
            }

            double meanNaive, medianNaive;
            std::tie(meanNaive, medianNaive) = values(timesNaive);

            std::cout << nPlayers << ' ' << size << '\n';
            naive << nPlayers << '\t' << size << '\t' << meanNaive << '\t' << medianNaive << '\t' << nTimeOut << '\n';
            naive.flush();
        }
    }

    naive.close();

    return 0;
}