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