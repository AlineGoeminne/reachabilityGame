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
    return m_vertices;
}