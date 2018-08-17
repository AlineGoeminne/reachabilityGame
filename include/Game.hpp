#pragma once

#include "Graph.hpp"
#include "Vertex.hpp"

/**
 * \brief La base des jeux
 */
class Game {
public:
    /**
     * \brief Construit le jeu
     * \param graph Le graphe
     * \param init Le sommet de départ
     */
    Game(Graph& graph, Vertex::Ptr init);

    /**
     * \brief Donne le graphe
     * \return Le graphe
     */
    Graph &getGraph();

    /**
     * \brief Donne le graphe immuable
     * \return Le graphe
     */
    const Graph &getGraph() const;

    /**
     * \brief Donne le sommet de départ
     * \return Le sommet de départ
     */
    Vertex::Ptr getInit();

    /**
     * \brief Donne le sommet de départ immuable
     * \return Le sommet de départ
     */
    const Vertex::Ptr getInit() const;

protected:
    Graph m_graph;
    Vertex::Ptr m_init;
};