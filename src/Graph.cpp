#include "Graph.hpp"

#include <iostream>

Graph::Graph(std::vector<Vertex::Ptr>& vertices, std::size_t nPlayers) :
    m_vertices(vertices)
    {
    computeMaxWeights(nPlayers);
}

Graph::Graph(std::vector<Vertex::Ptr>& vertices, std::vector<Long> maxWeight) :
    m_vertices(vertices),
    m_maxWeights(maxWeight)
    {

}

Graph::~Graph() {

}

std::vector<Long> Graph::getWeights(unsigned int u, unsigned int v) const {
    Vertex::Ptr vertex = m_vertices.at(u);
    return vertex->getWeights(v);
}

const std::vector<Long>& Graph::getMaxWeights() const {
    return m_maxWeights;
}

std::size_t Graph::size() const {
    return m_vertices.size();
}

std::vector<Vertex::Ptr>& Graph::getVertices() {
    return m_vertices;
}

const std::vector<Vertex::Ptr>& Graph::getVertices() const {
    return m_vertices;
}

std::vector<Vertex::Ptr>::const_iterator Graph::cbegin() const {
    return m_vertices.cbegin();
}

std::vector<Vertex::Ptr>::const_iterator Graph::cend() const {
    return m_vertices.cend();
}

std::size_t Graph::getNumberPlayers() const {
    return m_maxWeights.size();
}

void Graph::computeMaxWeights(std::size_t nPlayers) {
    m_maxWeights = std::vector<Long>(nPlayers, Long::infinity);

    for (auto &vertex : m_vertices) {
        for (auto &succ : *vertex) {
            for (std::size_t i = 0 ; i < nPlayers ; i++) {
                if (succ.second.second[i] < m_maxWeights[i]) {
                    m_maxWeights[i] = succ.second.second[i];
                }
            }
        }
    }
}