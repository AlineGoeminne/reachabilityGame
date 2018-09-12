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

#include "Graph.hpp"

#include <iostream>

using namespace types;

Graph::Graph(const std::vector<Vertex::Ptr>& vertices, std::size_t nPlayers) :
    m_vertices(vertices)
    {
    computeMaxWeights(nPlayers);
}

Graph::Graph(const std::vector<Vertex::Ptr>& vertices, std::vector<Long> maxWeight) :
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

void Graph::updateMaxWeights() {
    computeMaxWeights(m_maxWeights.size());
}

void Graph::computeMaxWeights(std::size_t nPlayers) {
    m_maxWeights = std::vector<Long>(nPlayers, 0);

    for (auto &vertex : m_vertices) {
        for (auto &succ : *vertex) {
            for (std::size_t i = 0 ; i < nPlayers ; i++) {
                m_maxWeights[i] = std::max(m_maxWeights[i], succ.second.second[i]);
            }
        }
    }
}