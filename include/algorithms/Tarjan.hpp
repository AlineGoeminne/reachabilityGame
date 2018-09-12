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

#include <unordered_set>
#include <set>

#include "Vertex.hpp"
#include "Graph.hpp"

/**
 * \brief Des algorithmes divers
 */
namespace algorithms {
    /**
     * \brief Contient les indices des sommets formants une composante fortement connexe
     */
    typedef std::set<unsigned int> stronglyConnectedComponent;
    /**
     * \brief Contient l'ensemble des composantes fortement connexes
     */
    typedef std::unordered_set<stronglyConnectedComponent> stronglyConnectedComponents;

    /**
     * \brief Exécute l'algorithme de Tarjan sur le graphe.
     * \param graph Le graphe
     * \return L'ensemble des composantes fortement connexes du graphe
     */
    stronglyConnectedComponents tarjan(const Graph& graph);
}

namespace std {
    template <>
    struct hash<algorithms::stronglyConnectedComponent> {
        size_t operator()(const algorithms::stronglyConnectedComponent& s) const {
            size_t sum = 0;
            for (const unsigned int v : s) {
                sum += v;
            }
            return sum;
        }
    };
}