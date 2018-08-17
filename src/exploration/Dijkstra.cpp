#include "exploration/Dijkstra.hpp"

#include <queue>

struct DijNode {
    Vertex::Ptr vertex;
    std::vector<Long> dist;
};

CostVertices dijkstra(const Graph &graph, Vertex::Ptr start) {
    std::size_t nPlayers = graph.getNumberPlayers();
    std::priority_queue<DijNode> queue;
    CostVertices done;

    for (auto itr = graph.cbegin() ; itr != graph.cend() ; ++itr) {
        DijNode node;
        node.vertex = *itr;
        if (start->getID() == node.vertex->getID()) {
            // On a le noeud de départ
            node.dist = std::vector<Long>(nPlayers, 0);
        }
        else {
            node.dist = std::vector<Long>(nPlayers, Long::infinity);
        }
        queue.push(node);
    }

    while (!queue.empty()) {
        DijNode node = queue.top();
        queue.pop();

        for (const auto vertex : *node.vertex) {
            std::vector<Long> dist(nPlayers);
            // On additionne les poids pour chaque joueur
            for (std::size_t i = 0 ; i < nPlayers ; i++) {
                dist[i] = node.dist[i] + vertex.second.second[i];
            }
        }
    }
}