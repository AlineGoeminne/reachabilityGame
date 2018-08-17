#include <iostream>

#include "catch.hpp"

#include "exploration/BestFirstSearch.hpp"
#include "ReachabilityGame.hpp"
#include "Vertex.hpp"

using namespace std::placeholders;

#define HEURISTIC_BIND std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2, _3, _4)

TEST_CASE("A* positif", "[exploration]") {
    SECTION("Petit exemple") {
        // Code d'Aline
        Vertex::Ptr v0 = std::make_shared<Vertex>(0, 0, 2);
        Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 2);
        Vertex::Ptr v2 = std::make_shared<Vertex>(2, 1, 2);
        Vertex::Ptr v3 = std::make_shared<Vertex>(3, 0, 2);
        Vertex::Ptr v4 = std::make_shared<Vertex>(4, 0, 2);

        std::vector<Vertex::Ptr> vertices{v0, v1, v2, v3, v4};

        v0->addSuccessor(v1, 1);
        v1->addSuccessor(v0, 1);
        v1->addSuccessor(v2, 1);
        v2->addSuccessor(v3, 1);
        v2->addSuccessor(v4, 4);
        v3->addSuccessor(v0, 1);
        v3->addSuccessor(v4, 1);
        v4->addSuccessor(v2, 2);
        v4->addSuccessor(v3, 1);

        Graph g(vertices, 2);

        Player p1(0, {v0, v1, v3, v4}, {v3});
        Player p2(1, {v2}, {v0});
        v3->addTargetFor(0);
        v0->addTargetFor(1);

        Vertex::Ptr init = v1;

        ReachabilityGame game(g, init, {p1, p2});

        heuristicSignature heuristic = HEURISTIC_BIND;

        Path path = bestFirstSearch(game, heuristic);

        REQUIRE(path == Path(game, {v1, v2, v3, v0}, 2));
    }

    SECTION("Plus gros exemple") {
        // Exemple 3 du projet de MAB1 (p. 65)
        Vertex::Ptr v0 = std::make_shared<Vertex>(0, 1, 2);
        Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 2);
        Vertex::Ptr v2 = std::make_shared<Vertex>(2, 1, 2);
        Vertex::Ptr v3 = std::make_shared<Vertex>(3, 0, 2);
        Vertex::Ptr v4 = std::make_shared<Vertex>(4, 0, 2);
        Vertex::Ptr v5 = std::make_shared<Vertex>(5, 1, 2);
        Vertex::Ptr v6 = std::make_shared<Vertex>(6, 0, 2);
        Vertex::Ptr v7 = std::make_shared<Vertex>(7, 1, 2);

        v0->addSuccessor(v0, 1);
        v1->addSuccessor(v0, 1);
        v2->addSuccessor(v0, 1);
        v2->addSuccessor(v1, 1);
        v3->addSuccessor(v0, 5);
        v3->addSuccessor(v2, 1);
        v4->addSuccessor(v2, 5);
        v4->addSuccessor(v3, 1);
        v5->addSuccessor(v4, 1);
        v5->addSuccessor(v6, 1);
        v6->addSuccessor(v7, 1);
        v7->addSuccessor(v6, 1);

        std::vector<Vertex::Ptr> vertices{v0, v1, v2, v3, v4, v5, v6, v7};

        Graph g(vertices, 2);

        Player j1(0, {v1, v3, v4, v6}, {v6});
        v6->addTargetFor(0);

        Player j2(1, {v0, v2, v5, v7}, {v0});
        v0->addTargetFor(1);

        ReachabilityGame game(g, v3, {j1, j2});

        Path path = bestFirstSearch(game, HEURISTIC_BIND);

        std::cout << path << '\n';
    }
}