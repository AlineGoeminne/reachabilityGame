#include "Vertex.hpp"

Vertex::Vertex(unsigned int id, unsigned int player, std::size_t nPlayers) :
    m_id(id),
    m_player(player),
    m_isTarget(false),
    m_target(nPlayers, false)
    {
}

Vertex::~Vertex() {

}

void Vertex::addSuccessor(Ptr vertex, long weight) {
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

Long Vertex::getWeight(unsigned int id) const {
    auto e = getSuccessor(id);
    if (e.first) {
        return e.second;
    }
    else {
        return Long::infinity();
    }
}

unsigned int Vertex::getID() const {
    return m_id;
}

unsigned int Vertex::getPlayer() const {
    return m_player;
}

std::size_t Vertex::getNumberSuccessors() const {
    return m_successors.size();
}

std::size_t Vertex::getNumberPredecessors() const {
    return m_predecessors.size();
}

Vertex::StoreEdge::iterator Vertex::begin() {
    return m_successors.begin();
}

Vertex::StoreEdge::iterator Vertex::end() {
    return m_successors.end();
}

Vertex::StoreEdge::iterator Vertex::beginPredecessors() {
    return m_predecessors.begin();
}

Vertex::StoreEdge::iterator Vertex::endPredecessors() {
    return m_predecessors.end();
}

bool Vertex::isTarget() const {
    return m_isTarget;
}

bool Vertex::isTargetFor(unsigned int player) const {
    return m_target[player];
}

void Vertex::addTargetFor(unsigned int player) {
    m_target[player] = true;
}

void Vertex::addPredecessor(Vertex::Ptr vertex, long weight) {
    m_predecessors[vertex->getID()] = std::make_pair(vertex, weight);
}