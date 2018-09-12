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

#include "Player.hpp"

Player::Player(unsigned int id) :
    m_id(id)
    {

}

Player::Player(unsigned int id, const std::unordered_set<Vertex::Ptr>& vertices, const std::unordered_set<Vertex::Ptr>& goals) :
    m_id(id),
    m_vertices(vertices),
    m_goals(goals)
    {
    
}

Player::~Player() {

}

void Player::addVertex(Vertex::Ptr vertex) {
    m_vertices.insert(vertex);
}

const std::unordered_set<Vertex::Ptr>& Player::getVertices() const {
    return m_vertices;
}

void Player::addGoal(Vertex::Ptr goal) {
    goal->addTargetFor(m_id);
    m_goals.insert(goal);
}

const std::unordered_set<Vertex::Ptr>& Player::getGoals() const {
    return m_goals;
}