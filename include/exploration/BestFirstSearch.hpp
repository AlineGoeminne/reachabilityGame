#pragma once

#include <functional>
#include <vector>
#include <map>

#include "Vertex.hpp"
#include "Path.hpp"

class ReachabilityGame;

struct State {
    State(std::size_t nPlayers) :
        RP(0),
        costsPlayers(nPlayers, 0)
        {
        for (unsigned int i = 0 ; i < nPlayers ; i++) {
            notVisitedPlayers.insert(i);
        }
    }

    Long RP; // Somme des coûts
    std::vector<Long> costsPlayers; // Coût par joueur jusqu'au sommet courant
    std::unordered_set<unsigned int> notVisitedPlayers; // Ensemble des joueurs qui n'ont pas encore atteint un objectif
};

struct Node {
    typedef std::shared_ptr<Node> Ptr;

    Node(std::size_t nPlayers, Path p) :
        parent(nullptr),
        state(nPlayers),
        pathCost(0),
        path(p)
        {
    }

    Node(Ptr par, State s, Long pcost, Path p) :
        parent(par),
        state(s),
        pathCost(pcost),
        path(p)
        {
    }

    Node(Node::Ptr node) :
        parent(node->parent),
        state(node->state),
        pathCost(node->pathCost),
        path(node->path)
        {

    }

    Ptr parent;
    State state;
    Long pathCost;
    Path path;
};

typedef std::vector<Long> CostsForATarget;
typedef std::unordered_map<Vertex::Ptr, CostsForATarget> CostsMap;
typedef std::function<Long(const Node::Ptr& node, const std::vector<Long>& epsilon, const Vertex::Ptr vertex, const CostsMap& costsMap)> heuristicSignature;

Path bestFirstSearch(const ReachabilityGame& game, const heuristicSignature& heuristic, Long allowedTime = Long::infinity);