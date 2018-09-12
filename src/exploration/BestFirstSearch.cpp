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

#include "exploration/BestFirstSearch.hpp"

#include <queue>
#include <memory>
#include <chrono>

#include "MinMaxGame.hpp"
#include "Path.hpp"
#include "ReachabilityGame.hpp"

using namespace types;

namespace exploration {
    /**
     * \brief Comparaison entre deux noeuds de l'exploration
     */
    struct CompareNodes {
        /** \brief Compare deux Node::Ptr */
        bool operator()(const Node::Ptr& a, const Node::Ptr &b) const {
            return a->pathCost > b->pathCost;
        }
    };

    /**
     * \brief Calcule tous les coûts par Dijkstra.
     * 
     * Pour chacune des cibles du jeu, calcule les coûts pour y arriver à partir de chaque sommet
     * \param game Le jeu
     * \return Une map qui associe à chaque cible un tableau de coût (une valeur par sommet)
     */
    CostsMap computeAllDijkstra(const ReachabilityGame &game) {
        CostsMap res;
        std::unordered_set<Vertex::Ptr> goals;
        for (const Player &p : game.getPlayers()) {
            goals.insert(p.getGoals().begin(), p.getGoals().end());
        }

        MinMaxGame dijGraph = MinMaxGame::convert(game);
        for (const Vertex::Ptr &goal : goals) {
            res[goal] = dijGraph.getValues({goal});
        }
        return res;
    }

    Path bestFirstSearch(const ReachabilityGame& game, const heuristicSignature& heuristic, Long allowedTime) {
        std::size_t nPlayers = game.getGraph().getNumberPlayers();

        CostsMap costsMap = computeAllDijkstra(game);

        // On initialise le premier noeud de l'exploration
        Path path(game, game.getInit());
        Node::Ptr init = std::make_shared<Node>(nPlayers, path);
        for (unsigned int player : game.getInit()->getTargetPlayers()) {
            init->state.notVisitedPlayers.erase(player);
        }
        init->pathCost = heuristic(init, costsMap);

        // On construit la frontière avec le noeud créé
        std::priority_queue<Node::Ptr, std::vector<Node::Ptr>, CompareNodes> frontier;
        frontier.push(init);

        std::unordered_set<unsigned int> allPlayers;
        for (unsigned int i = 0 ; i < nPlayers ; i++) {
            allPlayers.insert(i);
        }

        auto start = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        while(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start < allowedTime) {
            if (frontier.empty()) {
                throw EmptyFrontier("La frontière est vide");
            }

            Node::Ptr currentNode = frontier.top();
            frontier.pop();

            if (currentNode->state.notVisitedPlayers.size() == 0) {
                // Tout le monde a vu une cible. On a donc un équilibre de Nash (si exploration optimale)
                return currentNode->path;
            }
            else if (currentNode->path.size() == game.getMaxLength()) {
                // On a atteint la longueur maximale
                // Il se peut que ce soit un équilibre de Nash
                // On va vérifier pour les joueurs qui n'ont pas encore atteint un objectif

                if (currentNode->path.isANashEquilibrium(currentNode->state.notVisitedPlayers)) {
                    // On a un EN
                    return currentNode->path;
                }
            }
            else {
                const std::shared_ptr<const Vertex> last = currentNode->path.getLast();

                // On va itérer sur chaque successeur du dernier sommet du chemin
                for (auto succEdge = last->cbegin() ; succEdge != last->cend() ; succEdge++) {
                    const Vertex::Ptr succ = succEdge->second.first.lock();
                    const std::vector<Long>& w = succEdge->second.second;

                    // On copie le noeud et on ajoute un pas
                    Node::Ptr newNode = std::make_shared<Node>(currentNode);
                    newNode->path.addStep(succ);

                    // On met à jour les coûts en ajoutant le coût de l'arc emprunté
                    for (std::size_t i = 0 ; i < nPlayers ; i++) {
                        newNode->state.epsilon[i] = w[i] + currentNode->state.epsilon[i];
                    }

                    if (succ->isTarget()) {
                        std::unordered_set<unsigned int> newReached;
                        for (unsigned int p : newNode->state.notVisitedPlayers) {
                            if (succ->isTargetFor(p)) {
                                newReached.insert(p);
                            }
                        }

                        if (newReached.size() != 0) {
                            // On a des joueurs qui atteignent une cible pour la première fois
                            bool nash = true;
                            // On vérifie si on a un équilibre de Nash pour chaque joueur
                            for (unsigned int p : newReached) {
                                allPlayers.erase(p);
                                if (!newNode->path.isANashEquilibrium(allPlayers)) {
                                    nash = false;
                                }
                                allPlayers.insert(p);
                            }
                            // Si oui, on va ajouter un nouveau noeud à la frontière
                            if (nash) {
                                for (unsigned int p : newReached) {
                                    newNode->state.notVisitedPlayers.erase(p);
                                    newNode->state.RP += newNode->state.epsilon[p];
                                }
                                newNode->pathCost = heuristic(newNode, costsMap);
                                frontier.push(newNode);
                            }
                        }
                        else {
                            newNode->pathCost = heuristic(newNode, costsMap);
                            frontier.push(newNode);
                        }
                    } 
                    else {
                        newNode->pathCost = heuristic(newNode, costsMap);
                        frontier.push(newNode);
                    }
                }
            }
        }
        throw OutOfTime("L'exploration s'est achevée par manque de temps");
    }
}