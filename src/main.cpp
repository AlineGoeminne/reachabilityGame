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

#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "MinMaxGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "exploration/RandomPaths.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"
#include "generators/RandomGenerator.hpp"
#include "generators/RandomStronglyConnectedGenerator.hpp"

using namespace exploration;
using namespace types;
using namespace std::placeholders;

int main() {
    ReachabilityGame game = generators::randomTreeLikeGenerator(3, 1, 1, 0.0000000000000000001, 0, 0, 0, -10, 0, false, 2, false, {0.3, 0.7});

    std::cout << game << '\n';
}