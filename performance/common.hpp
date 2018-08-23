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