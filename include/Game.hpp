#pragma once

#include "Graph.hpp"
#include "Vertex.hpp"

class Game {
public:
    Game(Graph& graph, Vertex::Ptr init);

    Graph &getGraph();
    const Graph &getGraph() const;
    Vertex::Ptr getInit();
    const Vertex::Ptr getInit() const;

protected:
    Graph m_graph;
    Vertex::Ptr m_init;
};