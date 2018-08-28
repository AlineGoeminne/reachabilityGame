#include "generators/RandomStronglyConnectedGenerator.hpp"
#include "exploration/BestFirstSearch.hpp"

using namespace std::placeholders;

int main() {
    for (std::size_t nPlayers = 4 ; nPlayers < 50 ; nPlayers++) {
        std::vector<double> probaPlayers(nPlayers, 1./nPlayers);
        std::vector<double> probaTargets(nPlayers, 0.01);
        std::vector<types::Long> maximumTargets(nPlayers, types::Long::infinity);

        std::cout << "nPlayers " << nPlayers << '\n';

        for (std::size_t size = 2 ; size < 11 ; size++) {
            std::cout << "size " << size << '\n';
            for (std::size_t i = 0 ; i < 10000 ; i++) {
                ReachabilityGame game = generators::randomStronglyConnectedGenerator(size, 1, 2, 1, 1, true, nPlayers, false, probaPlayers, probaTargets, maximumTargets);

                Path path = exploration::bestFirstSearch(game, std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2));

                bool all = true;
                for (auto &c : path.getCosts()) {
                    if (!c.first) {
                        all = false;
                    }
                }

                if (!all) {
                    std::cout << path << '\n';
                    std::cout << std::boolalpha << path.isANashEquilibrium() << '\n';
                    std::cout << game << '\n';
                    return 0;
                }
            }
        }
    }
    return 0;
}