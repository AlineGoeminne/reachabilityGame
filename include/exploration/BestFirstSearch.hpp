#pragma once

#include <functional>
#include <vector>
#include <map>

#include "Path.hpp"
#include "ReachabilityGame.hpp"
#include "Vertex.hpp"

struct State {
    State(std::size_t nPlayers) :
        RP(0),
        visitedPlayers(nPlayers, false),
        costsPlayers(nPlayers, 0),
        nNotYetVisited(nPlayers)
        {

    }

    Long RP; // Somme des coûts
    std::vector<bool> visitedPlayers; // Est-ce que joueur i a atteint un objectif
    std::vector<Long> costsPlayers; // Coût par joueur jusqu'au sommet courant
    std::size_t nNotYetVisited; // Nombre de joueurs qui n'a pas encore visité un objectif
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

    Ptr parent;
    State state;
    Long pathCost;
    Path path;
};

typedef std::vector<std::vector<Long>> CostsForATarget;
typedef std::unordered_map<unsigned int, CostsForATarget> CostsMap;
typedef std::function<Long(const Node::Ptr& node, const std::vector<Long>& epsilon, const Vertex::Ptr vertex, const CostsMap& costsMap)> heuristicSignature;

Path bestFirstSearch(const ReachabilityGame& game, const heuristicSignature& heuristic, Long allowedTime = Long::infinity);