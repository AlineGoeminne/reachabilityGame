#include "Graph.hpp"

#include <iostream>

Graph::Graph(std::vector<Vertex::Ptr>& vertices) :
    m_vertices(vertices)
    {
    computeMaxWeight();
}

Graph::Graph(std::vector<Vertex::Ptr>& vertices, long maxWeight) :
    m_vertices(vertices),
    m_maxWeight(maxWeight)
    {

}

Long Graph::getWeight(unsigned int u, unsigned int v) const {
    Vertex::Ptr vertex = m_vertices.at(u);
    return vertex->getWeight(v);
}

void Graph::computeMaxWeight() {
    Long mini = -Long::infinity();
    for (auto &vertex : m_vertices) {
        for (auto &succ : *vertex) {
            if (succ.second.second < mini.getValue()) {
                mini = succ.second.second;
            }
        }
    }
}