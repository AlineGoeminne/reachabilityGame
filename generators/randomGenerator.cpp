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

#include "generators/RandomGenerator.hpp"

using namespace generators;

int main() {
    ReachabilityGame game = randomGenerator(10, 1, 5, 1, 1, true, 2, false, {0.5, 0.5}, {0, 0.5}, {2, types::Long::infinity});

    game.printDOT();

    //std::cout << game.numberOfReachableVertices() << '\n';

    return 0;
}