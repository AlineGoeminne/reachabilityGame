#include "exploration/BestFirstSearch.hpp"

#include <queue>
#include <memory>
#include <chrono>

struct CompareNodes {
    bool operator()(const Node::Ptr& a, const Node::Ptr &b) const {
        return a->pathCost < b->pathCost;
    }
};

class EmptyFrontier : public std::runtime_error {
public:
    explicit EmptyFrontier(const std::string &what) :
        std::runtime_error(what) {
    }
    explicit EmptyFrontier(const char* what) :
        std::runtime_error(what) {
    }
};

Path bestFirstSearch(const ReachabilityGame& game, const heuristicSignature& heuristic, Long allowedTime) {
    std::size_t nPlayers = game.getGraph().getNumberPlayers();

    std::vector<Long> epsilon(nPlayers, 0);

    // On initialise le premier noeud de l'exploration
    Path path(game, game.getInit(), nPlayers);
    Node::Ptr init = std::make_shared<Node>(nPlayers, path);
    for (unsigned int player : game.getInit()->getTargetPlayers()) {
        init->state.visitedPlayers[player] = true;
        init->state.nNotYetVisited--;
    }
    init->pathCost = heuristic(init, epsilon, game.getInit(), costsMap);
    // TODO: costsMap doit venir de all_dijkstra
    // TODO: all_dijkstra

    std::priority_queue<Node::Ptr, std::vector<Node::Ptr>, CompareNodes> frontier;
    std::unordered_set<Node::Ptr> explored;

    auto start = std::chrono::system_clock::now().time_since_epoch().count();

    while(std::chrono::system_clock::now().time_since_epoch().count() - start < allowedTime) {
        if (frontier.empty()) {
            throw EmptyFrontier("La frontière est vide");
        }

        Node::Ptr node = frontier.top();
        frontier.pop();

        if (node->state.nNotYetVisited == 0) {
            // Tout le monde a vu une cible. On a donc un équilibre de Nash (si exploration optimale)
            return node->path;
        }
    }
}