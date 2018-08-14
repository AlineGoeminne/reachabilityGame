#pragma once

#include <vector>

#include "Graph.hpp"
#include "Player.hpp"
#include "types/Long.hpp"
#include "Game.hpp"

class ReachabilityGame : public Game {
public:
    ReachabilityGame(Graph graph, Vertex::Ptr init, const std::vector<Player>& players);

private:
    std::vector<Player> m_players;
    std::vector<Long> m_maxWeightsPath;
};