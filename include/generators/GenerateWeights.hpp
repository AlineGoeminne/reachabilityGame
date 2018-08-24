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