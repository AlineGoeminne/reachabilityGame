#include "exploration/RandomPaths.hpp"

#include <random>
#include <chrono>
#include <vector>

Path generatePath(const ReachabilityGame &game, std::size_t length) {
    std::shared_ptr<const Vertex> current = game.getInit();
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    Path path(game, current);

    while(length--) {
        std::uniform_int_distribution<std::size_t> successorChoice(0, current->getNumberSuccessors() - 1);

        std::size_t succIndex = successorChoice(generator);

        std::shared_ptr<const Vertex> succ = nullptr;

        for (auto s = current->cbegin() ; s != current->cend() ; s++) {
            if (succIndex-- == 0) {
                succ = s->second.first.lock();
                break;
            }
        }

        path.addStep(succ);
        current = succ;
    }

    return path;
}

const Path& filterBest(const std::vector<Path> &paths, std::size_t nPlayers) {
    std::size_t bestCostIndex = 0;
    std::size_t bestReachedIndex = 0;
    types::Long valueBestCost = types::Long::infinity;
    types::Long valueBestReached = 0;
    types::Long partialValueBestCost = types::Long::infinity;
    bool allPlayersEN = false;

    for (std::size_t i = 0 ; i < paths.size() ; i++) {
        const Path &p = paths[i];
        const auto &costs = p.getCosts();

        types::Long sumCost = 0, partialCost = 0;
        std::size_t nReached = 0;
        for (const auto &cost : costs) {
            if (cost.first) {
                nReached++;
                partialCost += cost.second;
            }
            sumCost += cost.second;
        }

        if (nReached != nPlayers && valueBestCost > sumCost) {
            // Tout le monde n'a pas vu une cible mais c'est le meilleur EN dans ce cas
            bestCostIndex = i;
            valueBestCost = sumCost;
        }
        else if (valueBestReached < nReached) {
            // On voit plus de monde qu'avant
            bestReachedIndex = i;
            valueBestReached = nReached;
            if (nPlayers == nReached) {
                // On a vu tout le monde
                allPlayersEN = true;
            }
        }
        else if (valueBestReached == nReached && partialCost < partialValueBestCost) {
            // On voit autant de monde que l'EN déjà retenu mais les coûts sont moindres
            bestReachedIndex = i;
            partialValueBestCost = partialCost;
        }
    }

    if (allPlayersEN) {
        return paths[bestReachedIndex];
    }
    else {
        return paths[bestCostIndex];
    }
}

namespace exploration {
    Path randomPath(const ReachabilityGame &game, std::size_t nPaths) {
        std::vector<Path> paths;
        paths.reserve(nPaths);

        for (std::size_t i = 0 ; i < nPaths ; i++) {
            Path p = generatePath(game, game.getMaxLength());
            if (p.isANashEquilibrium()) {
                paths.push_back(p);
            }
        }

        if (paths.size() == 0) {
            throw NoENGenerated("Pas d'équilibre de Nash généré");
        }

        return filterBest(paths, game.getMaxLength());
    }
}