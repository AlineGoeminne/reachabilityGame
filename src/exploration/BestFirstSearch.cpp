#include "exploration/BestFirstSearch.hpp"

#include <queue>
#include <memory>
#include <chrono>

#include "MinMaxGame.hpp"
#include "Path.hpp"
#include "ReachabilityGame.hpp"

using namespace types;

namespace exploration {
    struct CompareNodes {
        bool operator()(const Node::Ptr& a, const Node::Ptr &b) const {
            return a->pathCost > b->pathCost;
        }
    };

    class EmptyFrontier : public std::runtime_error {
    public:
        explicit EmptyFrontier(const std::string &what) :
            std::runtime_error(what) {
        }
        explicit EmptyFrontier(const char* what) :
            std::runtime_error(what) {
        }
    };

    class OutOfTime : public std::runtime_error {
    public:
        explicit OutOfTime(const std::string &what) :
            std::runtime_error(what) {
        }
        explicit OutOfTime(const char* what) :
            std::runtime_error(what) {
        }
    };

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

        std::vector<Long> epsilon(nPlayers, 0);

        // On initialise le premier noeud de l'exploration
        Path path(game, game.getInit(), nPlayers);
        Node::Ptr init = std::make_shared<Node>(nPlayers, path);
        for (unsigned int player : game.getInit()->getTargetPlayers()) {
            init->state.notVisitedPlayers.erase(player);
        }
        init->pathCost = heuristic(init, epsilon, costsMap);

        std::priority_queue<Node::Ptr, std::vector<Node::Ptr>, CompareNodes> frontier;
        std::unordered_set<Node::Ptr> explored;

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

            Node::Ptr node = frontier.top();
            frontier.pop();

            if (node->state.notVisitedPlayers.size() == 0) {
                // Tout le monde a vu une cible. On a donc un équilibre de Nash (si exploration optimale)
                return node->path;
            }
            else if (node->path.size() == game.getMaxLength()) {
                // On a atteint la longueur maximale
                // Il se peut que ce soit un équilibre de Nash
                // On va vérifier pour les joueurs qui n'ont pas encore atteint un objectif

                if (node->path.isANashEquilibrium(node->state.notVisitedPlayers)) {
                    // On a un EN
                    return node->path;
                }
            }
            else {
                const Vertex::Ptr last = node->path.getLast();

                for (const auto& succEdge : *last) {
                    const Vertex::Ptr succ = succEdge.second.first;
                    const std::vector<Long>& w = succEdge.second.second;

                    std::vector<Long> epsilon(nPlayers);
                    for (std::size_t i = 0 ; i < nPlayers ; i++) {
                        epsilon[i] = w[i] + node->state.costsPlayers[i];
                    }

                    Node::Ptr newNode = std::make_shared<Node>(node);
                    Path &newPath = newNode->path;
                    newPath.addStep(succ);

                    if (succ->isTarget()) {
                        std::unordered_set<unsigned int> newReached;
                        for (unsigned int p : node->state.notVisitedPlayers) {
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
                                if (!newPath.isANashEquilibrium(allPlayers)) {
                                    nash = false;
                                }
                                allPlayers.insert(p);
                            }
                            // Si oui, on va ajouter un nouveau noeud à la frontière
                            if (nash) {
                                for (unsigned int p : newReached) {
                                    newNode->state.costsPlayers[p] = epsilon[p];
                                    newNode->state.notVisitedPlayers.erase(p);
                                    newNode->state.RP += newNode->state.costsPlayers[p];
                                }
                                newNode->pathCost = heuristic(newNode, epsilon, costsMap);
                                frontier.push(newNode);
                            }
                        }
                        else {
                            newNode->pathCost = heuristic(newNode, epsilon, costsMap);
                            frontier.push(newNode);
                        }
                    } 
                    else {
                        newNode->pathCost = heuristic(newNode, epsilon, costsMap);
                        frontier.push(newNode);
                    }
                }
            }
        }
        throw OutOfTime("L'exploration s'est achevée par manque de temps");
    }
}