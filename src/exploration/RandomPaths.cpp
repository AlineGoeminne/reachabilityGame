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

#include "exploration/RandomPaths.hpp"

#include <random>
#include <chrono>
#include <vector>

/**
 * \brief Génère aléatoirement un chemin de longueur donné
 * \param game Le jeu
 * \param length La longueur du chemin
 */
Path generatePath(const ReachabilityGame &game, std::size_t length) {
    std::shared_ptr<const Vertex> current = game.getInit();
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    Path path(game, current);

    while(length--) {
        // On va tirer le successeur au hasard
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

/**
 * \brief Retourne le meilleur EN parmi ceux donnés
 * \param paths L'ensemble des EN
 * \param nPlayers Le nombre de joueurs
 */
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

        types::Long sumCost = 0; // Les coûts totaux
        types::Long partialCost = 0; // La somme de coûts pour les joueurs qui ont vu leur cible
        std::size_t nReached = 0; // Le nombre de joueurs qui ont vu une cible
        for (const auto &cost : costs) {
            if (cost.first) {
                nReached++;
                partialCost += cost.second;
            }
            sumCost += cost.second;
        }

        if (nReached != nPlayers && valueBestCost > sumCost) {
            // Tout le monde n'a pas vu une cible mais on a un coût inférieur à celui trouvé précédemment
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