#pragma once

#include "Graph.hpp"
#include "Vertex.hpp"

class Game {
public:
    Game(Graph& graph, Vertex::Ptr init);

    Graph &getGraph();
    Vertex::Ptr getInit();

private:
    Graph m_graph;
    Vertex::Ptr m_init;
};