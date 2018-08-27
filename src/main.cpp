#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "MinMaxGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"
#include "generators/RandomGenerator.hpp"

using namespace exploration;
using namespace types;
using namespace std::placeholders;

int main() {
    Vertex::Ptr v0 = std::make_shared<Vertex>(0, 1, 3);
    Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 3);

    v0->addSuccessor(v0, 1);
    v0->addSuccessor(v1, 1);
    v1->addSuccessor(v0, 1);

    v0->addTargetFor(0);
    v0->addTargetFor(1);
    v1->addTargetFor(2);

    Player p0(0, {}, {v0}), p1(1, {v1}, {v0}), p2(2, {v0}, {v1});

    Graph graph({v0, v1}, {1, 1, 1});

    ReachabilityGame game(graph, v0, {p0, p1, p2});

    Path best = exploration::bestFirstSearch(game, std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2));

    std::cout << best << '\n';
    std::cout << game << '\n';

    return 0;
}