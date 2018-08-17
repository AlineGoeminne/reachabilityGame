#include "Vertex.hpp"
#include <iostream>

using namespace types;

Vertex::Vertex(unsigned int id, unsigned int player, std::size_t nPlayers) :
    m_nPlayers(nPlayers),
    m_id(id),
    m_player(player)
    {
}

Vertex::~Vertex() {

}

void Vertex::addSuccessor(Ptr vertex, Long weight) {
    // On crée un tableau de taille nPlayers rempli avec weight
    std::vector<Long> weights(m_nPlayers, weight);
    addSuccessor(vertex, weights);
}

void Vertex::addSuccessor(Ptr vertex, std::vector<Long> weights) {
    m_successors[vertex->getID()] = std::make_pair(vertex, weights);
    vertex->addPredecessor(shared_from_this(), weights);
}

Vertex::Edge Vertex::getSuccessor(unsigned int id) const {
    auto itr = m_successors.find(id);
    if (itr == m_successors.end()) {
        return std::make_pair(nullptr, std::vector(m_nPlayers, Long::infinity));
    }
    else {
        return itr->second;
    }
}

Vertex::Edge Vertex::getPredecessor(unsigned int id) const {
    auto itr = m_predecessors.find(id);
    if (itr == m_predecessors.end()) {
        return std::make_pair(nullptr, std::vector(m_nPlayers, Long::infinity));
    }
    else {
        return itr->second;
    }
}

std::vector<Long> Vertex::getWeights(unsigned int id) const {
    auto e = getSuccessor(id);
    if (e.first) {
        return e.second;
    }
    else {
        return std::vector<Long>(m_nPlayers, Long::infinity);
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
    return m_target.size() > 0;
}

bool Vertex::isTargetFor(unsigned int player) const {
    return m_target.find(player) != m_target.end();
}

const std::unordered_set<unsigned int>& Vertex::getTargetPlayers() const {
    return m_target;
}

void Vertex::addTargetFor(unsigned int player) {
    if (!isTargetFor(player)) {
        m_target.insert(player);
    }
}

void Vertex::addPredecessor(Vertex::Ptr vertex, std::vector<Long> weights) {
    m_predecessors[vertex->getID()] = std::make_pair(vertex, weights);
}

bool operator==(const Vertex &a, const Vertex &b) {
    return a.getID() == b.getID();
}

bool operator!=(const Vertex &a, const Vertex &b) {
    return !(a == b);
}

std::ostream& operator<<(std::ostream &os, const Vertex &a) {
    os << "v" << a.m_id;
    return os;
}