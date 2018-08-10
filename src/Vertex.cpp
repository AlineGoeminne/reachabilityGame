#include "Vertex.hpp"

Vertex::Vertex(unsigned int id, unsigned int player) :
    m_id(id),
    m_player(player)
    {

}

Vertex::~Vertex() {

}

void Vertex::addSuccessor(Ptr vertex, int weight) {
    m_successors[vertex->getID()] = std::make_pair(vertex, weight);
    vertex->addPredecessor(shared_from_this(), weight);
}

Vertex::Edge Vertex::getSuccessor(unsigned int id) const {
    auto itr = m_successors.find(id);
    if (itr == m_successors.end()) {
        return std::make_pair(nullptr, 0);
    }
    else {
        return itr->second;
    }
}

Vertex::Edge Vertex::getPredecessor(unsigned int id) const {
    auto itr = m_predecessors.find(id);
    if (itr == m_predecessors.end()) {
        return std::make_pair(nullptr, 0);
    }
    else {
        return itr->second;
    }
}

unsigned int Vertex::getID() const {
    return m_id;
}

void Vertex::addPredecessor(Vertex::Ptr vertex, int weight) {
    m_predecessors[vertex->getID()] = std::make_pair(vertex, weight);
}