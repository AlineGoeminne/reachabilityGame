#include <iostream>

#include "Vertex.hpp"
#include "Graph.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "MinMaxGame.hpp"
#include "exploration/BestFirstSearch.hpp"
#include "exploration/RandomPaths.hpp"
#include "generators/RandomTreeLikeGenerator.hpp"
#include "generators/RandomGenerator.hpp"

using namespace exploration;
using namespace types;
using namespace std::placeholders;

int main() {
    Vertex::Ptr v0 = std::make_shared<Vertex>(0, 1, 2);
    Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 2);
    Vertex::Ptr v2 = std::make_shared<Vertex>(2, 0, 2);
    Vertex::Ptr v3 = std::make_shared<Vertex>(3, 1, 2);
    Vertex::Ptr v4 = std::make_shared<Vertex>(4, 1, 2);
    Vertex::Ptr v5 = std::make_shared<Vertex>(5, 0, 2);

    v0->addSuccessor(v1, {1, 50});
    v0->addSuccessor(v2, {1, 1});
    v1->addSuccessor(v2, {100, 200});
    v2->addSuccessor(v3, {20, 10});
    v2->addSuccessor(v4, {1, 1});
    v3->addSuccessor(v2, {10, 20});
    v3->addSuccessor(v5, {1, 5});
    v4->addSuccessor(v1, {1, 1});
    v5->addSuccessor(v3, {5, 1});

    v1->addTargetFor(1);
    v4->addTargetFor(1);
    v5->addTargetFor(0);

    Player p0(0, {v1, v2, v5}, {v5}), p1(1, {v0, v4, v3}, {v1, v4});

    Graph graph({v0, v1, v2, v3, v4, v5}, 2);

    ReachabilityGame game(graph, v0, {p0, p1});

    Path path = exploration::randomPath(game, 10);

    std::cout << path << ' ' << std::boolalpha << path.isANashEquilibrium() << '\n';

    return 0;
}