/*
 * ReachabilityGame - a program to compute the best Nash equilibrium in reachability games
 * Copyright (C) 2018 Gaëtan Staquet and Aline Goeminne
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
        return std::make_pair(std::weak_ptr<Vertex>(), std::vector<Long>(m_nPlayers, Long::infinity));
    }
    else {
        return itr->second;
    }
}

Vertex::Edge Vertex::getPredecessor(unsigned int id) const {
    auto itr = m_predecessors.find(id);
    if (itr == m_predecessors.end()) {
        return std::make_pair(std::weak_ptr<Vertex>(), std::vector<Long>(m_nPlayers, Long::infinity));
    }
    else {
        return itr->second;
    }
}

bool Vertex::hasSuccessor(unsigned int id) const {
    auto itr = m_successors.find(id);
    return itr != m_successors.end();
}

std::vector<Long> Vertex::getWeights(unsigned int id) const {
    auto e = getSuccessor(id);
    // weak_ptr => on a besoin de "lock" pour savoir si le pointeur est valide
    if (e.first.lock()) {
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

Vertex::StoreEdge::const_iterator Vertex::cbegin() const {
    return m_successors.cbegin();
}

Vertex::StoreEdge::iterator Vertex::end() {
    return m_successors.end();
}

Vertex::StoreEdge::const_iterator Vertex::cend() const {
    return m_successors.cend();
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