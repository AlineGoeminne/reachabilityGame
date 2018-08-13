#include "ReachabilityGame.hpp"

ReachabilityGame::ReachabilityGame(Graph graph, Vertex::Ptr init, std::vector<Player> players) :
    Game(graph, init),
    m_players(players),
    m_maxWeightsPath(players.size())
    {
    for (std::size_t i = 0 ; i < players.size() ; i++) {
        // Le poids maximal pour un chemin est (|Pi| + 1) * |V| * max(|w_i|)
        m_maxWeightsPath[i] = (players.size() + 1) * graph.size() * graph.getMaxWeights()[i];
    }
}