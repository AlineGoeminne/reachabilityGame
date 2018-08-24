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