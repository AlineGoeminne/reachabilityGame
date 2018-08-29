#include <fstream>

#include "ReachabilityGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "exploration/RandomPaths.hpp"
#include "generators/RandomGenerator.hpp"

using namespace std::placeholders;

int main() {
    std::ofstream res("../plots/randomVSBestFirstSearch.data");
    std::size_t nGenerations = 100;

    for (std::size_t size = 5 ; size <= 20 ; size++) {
        std::size_t nRandomBest = 0;
        std::size_t nBestFirstBest = 0;
        std::size_t nTimeOuts = 0;
        std::size_t nFailed = 0;
        for (std::size_t i = 0 ; i < nGenerations ; i++) {
            std::cout << "GENERATION " << i << '\n';
            ReachabilityGame game = generators::randomGenerator(size, 1, 5, 2, false);

            std::size_t nReachedBest = 0;
            types::Long costBest = 0;
            try {
                Path best = exploration::bestFirstSearch(game, std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2), 10);

                for (const auto& cost : best.getCosts()) {
                    if (cost.first) {
                        nReachedBest++;
                    }
                    costBest += cost.second;
                }
            }
            catch (exploration::OutOfTime &e) {
                nTimeOuts++;
            }

            std::size_t nReachedRandom = 0;
            types::Long costRandom = 0;
            try {
                Path random = exploration::randomPath(game, 1000);

                for (const auto& cost : random.getCosts()) {
                    if (cost.first) {
                        nReachedRandom++;
                    }
                    costRandom += cost.second;
                }
            }
            catch (exploration::NoENGenerated &e) {
                nFailed++;
            }

            if (nReachedRandom > nReachedBest) {
                nRandomBest++;
            }
            else if (nReachedBest == nReachedRandom && costRandom < costBest) {
                nRandomBest++;
            }

            if (nReachedBest > nReachedRandom) {
                nBestFirstBest++;
            }
            else if (nReachedBest == nReachedRandom && costBest < costRandom) {
                nBestFirstBest++;
            }
        }

        std::cout << size << '\n';
        res << size << '\t' << nRandomBest << '\t' << nBestFirstBest << '\t' << nTimeOuts << '\t' << nFailed << '\n';
        res.flush();
    }

    return 0;
}