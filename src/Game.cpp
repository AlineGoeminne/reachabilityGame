#include "Game.hpp"

Game::Game(Graph& graph, Vertex::Ptr init) :
    m_graph(graph),
    m_init(init)
    {
    
}

Graph& Game::getGraph() {
    return m_graph;
}

Vertex::Ptr Game::getInit() {
    return m_init;
}