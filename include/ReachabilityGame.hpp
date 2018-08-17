#pragma once

#include <vector>

#include "Graph.hpp"
#include "Player.hpp"
#include "types/Long.hpp"
#include "Game.hpp"
#include "exploration/BestFirstSearch.hpp"

class ReachabilityGame : public Game {
public:
    ReachabilityGame(Graph graph, Vertex::Ptr init, const std::vector<Player>& players);

    const std::vector<Player>& getPlayers() const;

    std::size_t getMaxLength() const;

    Long AStartPositive(const Node::Ptr& node, const std::vector<Long> &epsilon, const Vertex::Ptr vertex, const CostsMap &costsMap);

private:
    std::vector<Player> m_players;
    std::vector<Long> m_maxWeightsPath;
};