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

#include "generators/GenerateWeights.hpp"

namespace generators {
    std::uniform_int_distribution<long> constructWeightDistribution(long minWeight, long maxWeight) {
        return std::uniform_int_distribution<long> (minWeight, maxWeight);
    }

    std::vector<types::Long> generateWeights(std::size_t nPlayers, std::default_random_engine &generator, std::uniform_int_distribution<long> &weightDistribution, bool multipleWeights) {
        std::vector<types::Long> weights;
        if (multipleWeights) {
            for (std::size_t i = 0 ; i < nPlayers ; i++) {
                weights.push_back(weightDistribution(generator));
            }
        }
        else {
            weights = std::vector<types::Long>(nPlayers, weightDistribution(generator));
        }
        return weights;
    }
}