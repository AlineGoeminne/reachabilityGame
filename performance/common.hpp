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

#include <ctime>
#include <iostream>
#include <numeric>
#include <fstream>
#include <iterator>

#include "generators/RandomTreeLikeGenerator.hpp"
#include "exploration/BestFirstSearch.hpp"

using namespace types;
using namespace std::placeholders;

double clock_tToMilliSeconds(std::clock_t value) {
    return 1000. * value/CLOCKS_PER_SEC;
}

std::clock_t execute(ReachabilityGame &game) {
    std::clock_t start = std::clock();

    exploration::bestFirstSearch(game, std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2), 10);

    std::clock_t end = std::clock();

    return end-start;
}

std::tuple<double, double> values(std::vector<std::clock_t> &tab) {
    double mean = 0;
    for (auto &a : tab) {
        mean += clock_tToMilliSeconds(a);
    }
    mean /= tab.size();

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