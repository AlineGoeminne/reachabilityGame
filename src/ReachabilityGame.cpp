#include "ReachabilityGame.hpp"

#include <iostream>

ReachabilityGame::ReachabilityGame(Graph graph, Vertex::Ptr init, const std::vector<Player>& players) :
    Game(graph, init),
    m_players(players),
    m_maxWeightsPath(players.size())
    {
    for (std::size_t i = 0 ; i < players.size() ; i++) {
        // Le poids maximal pour un chemin est (|Pi| + 1) * |V| * max(|w_i|)
        m_maxWeightsPath[i] = Long(getMaxLength()) * getGraph().getMaxWeights()[i];
    }
}

const std::vector<Player> &ReachabilityGame::getPlayers() const {
    return m_players;
}

std::size_t ReachabilityGame::getMaxLength() const {
    return (m_players.size() + 1) * getGraph().size();
}

Long ReachabilityGame::AStartPositive(const Node::Ptr& node, const std::vector<Long> &epsilon, const Vertex::Ptr vertex, const CostsMap &costsMap) {
    // g(n) = Coût vers les cibles déjà atteintes + coûts partiels (joueurs qui n'ont pas encore atteints une cible)
    Long g_n = node->state.RP;
    for (unsigned int notReached : node->state.notVisitedPlayers) {
        g_n += epsilon[notReached];
    }

    Long h_n = 0;
    for (unsigned int notReached : node->state.notVisitedPlayers) {
        Long shortest;
        for (const Vertex::Ptr goal : m_players[notReached].getGoals()) {
            auto itr = costsMap.find(goal);
            const CostsForATarget& target = itr->second;
            shortest = std::min(shortest, target[notReached]);
        }
        h_n += std::min(shortest, getGraph().getMaxWeights()[notReached] - epsilon[notReached]);
    }

    return g_n + h_n;
}