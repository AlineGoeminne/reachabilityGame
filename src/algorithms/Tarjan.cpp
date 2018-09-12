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

#include "algorithms/Tarjan.hpp"

#include <vector>
#include <stack>
#include <algorithm>

// Les algorithmes sont inspirés du pseudo-code de la page Wikipédia (https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)

/**
 * \brief Le coeur de Tarjan
 * \param v L'ID du sommet actuel
 * \param index L'index (selon le pseudo-code)
 * \param indices Le tableau des index
 * \param lowLink Le tableau des lowLink (selon le pseudo-code)
 * \param stack La pile
 * \param onStack Un tableau de booléen indiquant si tel sommet est sur la pile ou non
 * \param vertices L'ensemble des sommets
 */
algorithms::stronglyConnectedComponents strongConnect(unsigned int v, std::size_t &index, std::vector<std::size_t> &indices, std::vector<std::size_t> &lowLink, std::stack<unsigned int> &stack, std::vector<bool> &onStack, const std::vector<Vertex::Ptr>& vertices) {
    indices[v] = index;
    lowLink[v] = index;
    index++;

    stack.push(v);
    onStack[v] = true;

    algorithms::stronglyConnectedComponents components;

    for (const auto &e : *vertices[v]) {
        unsigned int w = e.first;

        if (indices[w] == 0) {
            auto compo = strongConnect(w, index, indices, lowLink, stack, onStack, vertices);
            components.insert(compo.begin(), compo.end());
            lowLink[v] = std::min(lowLink[v], lowLink[w]);
        }
        else if (onStack[w]) {
            lowLink[v] = std::min(lowLink[v], indices[w]);
        }
    }

    algorithms::stronglyConnectedComponent component;
    if (lowLink[v] == indices[v]) {
        unsigned int w = stack.top();
        stack.pop();
        onStack[w] = false;
        component.insert(w);

        while (w != v) {
            w = stack.top();
            stack.pop();
            onStack[w] = false;
            component.insert(w);
        }

        components.insert(component);
    }

    return components;
}

namespace algorithms {
    stronglyConnectedComponents tarjan(const Graph& graph) {
        std::size_t size = graph.size();
        std::size_t index = 1;
        std::vector<std::size_t> indices(size, 0);
        std::vector<std::size_t> lowLink(size, 0);
        std::stack<unsigned int> stack;
        std::vector<bool> onStack(size, false);

        stronglyConnectedComponents components;

        for (const Vertex::Ptr v : graph.getVertices()) {
            if (indices[v->getID()] == 0) {
                auto compo = strongConnect(v->getID(), index, indices, lowLink, stack, onStack, graph.getVertices());
                components.insert(compo.begin(), compo.end());
            }
        }

        return components;
    }
}