#include "Graph.hpp"

#include <iostream>

Graph::Graph(std::vector<Vertex::Ptr>& vertices, std::size_t nPlayers) :
    m_vertices(vertices)
    {
    computeMaxWeights(nPlayers);
}

Graph::Graph(std::vector<Vertex::Ptr>& vertices, std::vector<long> maxWeight) :
    m_vertices(vertices),
    m_maxWeights(maxWeight)
    {

}

std::vector<Long> Graph::getWeights(unsigned int u, unsigned int v) const {
    Vertex::Ptr vertex = m_vertices.at(u);
    return vertex->getWeights(v);
}

std::size_t Graph::size() const {
    return m_vertices.size();
}

const std::vector<Vertex::Ptr>& Graph::getVertices() const {
    return m_vertices;
}

void Graph::computeMaxWeights(std::size_t nPlayers) {
    std::vector<Long> mini(nPlayers, Long::infinity);

    for (auto &vertex : m_vertices) {
        for (auto &succ : *vertex) {
            for (std::size_t i = 0 ; i < nPlayers ; i++) {
                if (succ.second.second[i] < mini[i]) {
                    mini[i] = succ.second.second[i];
                }
            }
        }
    }
}