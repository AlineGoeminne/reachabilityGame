#include "ReachabilityGame.hpp"

#include <iostream>

ReachabilityGame::ReachabilityGame(Graph graph, Vertex::Ptr init, const std::vector<Player>& players) :
    Game(graph, init),
    m_players(players),
    m_maxWeightsPath(players.size())
    {
    for (std::size_t i = 0 ; i < players.size() ; i++) {
        // Le poids maximal pour un chemin est (|Pi| + 1) * |V| * max(|w_i|)
        m_maxWeightsPath[i] = Long((m_players.size() + 1) * getGraph().size()) * getGraph().getMaxWeights()[i];
    }
}