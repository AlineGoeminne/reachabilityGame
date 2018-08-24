#include "algorithms/Tarjan.hpp"

#include <vector>
#include <stack>
#include <algorithm>

// Les algorithmes sont inspirés du pseudo-code de la page Wikipédia (https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)

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