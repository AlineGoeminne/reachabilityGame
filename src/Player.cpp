#include "Player.hpp"

Player::Player() {

}

Player::Player(const std::unordered_set<Vertex::Ptr>& vertices, const std::unordered_set<Vertex::Ptr>& goals) :
    m_vertices(vertices),
    m_goals(goals)
    {

}

void Player::addVertex(Vertex::Ptr vertex) {
    m_vertices.insert(vertex);
}

const std::unordered_set<Vertex::Ptr>& Player::getVertices() const {
    return m_vertices;
}

void Player::addGoal(Vertex::Ptr goal) {
    m_goals.insert(goal);
}

const std::unordered_set<Vertex::Ptr>& Player::getGoals() const {
    return m_vertices;
}