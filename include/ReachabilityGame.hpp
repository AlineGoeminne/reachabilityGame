#pragma once

#include <vector>

#include "Graph.hpp"
#include "Player.hpp"
#include "types/Long.hpp"
#include "Game.hpp"
#include "exploration/BestFirstSearch.hpp"

/**
 * \brief Un jeu d'atteignabilité
 */
class ReachabilityGame : public Game {
public:
    ReachabilityGame(Graph graph, Vertex::Ptr init, const std::vector<Player>& players);

    const std::vector<Player>& getPlayers() const;

    std::size_t getMaxLength() const;

    /**
     * \brief L'heuristique A* positive telle que définie dans le projet/mémoire
     * \param node Le noeud actuel de l'exploration
     * \param epsilon Les coûts actuels
     * \param costsMap Les coûts pour arriver à chaque cible
     */
    types::Long AStartPositive(const exploration::Node::Ptr& node, const std::vector<types::Long> &epsilon, const exploration::CostsMap &costsMap);

private:
    std::vector<Player> m_players;
    std::vector<types::Long> m_maxWeightsPath;
};