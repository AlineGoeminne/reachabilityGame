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

#include "generators/RandomStronglyConnectedGenerator.hpp"
#include "algorithms/Tarjan.hpp"

int main() {
    ReachabilityGame game = generators::randomStronglyConnectedGenerator(10, 1, 3, 1, 10, true, 2, false, {0.2, 0.8}, {0.7, 0.1}, {2, 3});
    std::cout << game << '\n';

    return 0;
}