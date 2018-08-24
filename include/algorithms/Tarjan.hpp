#pragma once

#include <unordered_set>
#include <set>

#include "Vertex.hpp"
#include "Graph.hpp"

/**
 * \brief Des algorithmes divers
 */
namespace algorithms {
    typedef std::set<unsigned int> stronglyConnectedComponent;
    typedef std::unordered_set<stronglyConnectedComponent> stronglyConnectedComponents;

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