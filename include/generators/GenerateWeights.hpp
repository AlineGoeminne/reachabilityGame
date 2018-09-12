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

#pragma once

#include <random>
#include <vector>

#include "types/Long.hpp"

namespace generators {
    /**
     * \brief Construit la distribution uniforme sur les poids
     * \return La distribution uniforme sur les poids
     */
    std::uniform_int_distribution<long> constructWeightDistribution(long minWeight, long maxWeight);

    /**
     * \brief Génère le tableau de poids (un poids par joueur).
     * 
     * Si multipleWeights est vrai, un nouveau poids est tiré pour chaque joueur. Sinon, le même poids est donné à tout le monde. 
     * 
     * \return Le tableau de poids
     */
    std::vector<types::Long> generateWeights(std::size_t nPlayers, std::default_random_engine &generator, std::uniform_int_distribution<long> &weightDistribution, bool multipleWeights);
}