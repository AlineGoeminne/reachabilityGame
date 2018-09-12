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