#include <iostream>

#include "catch.hpp"

#include "exploration/BestFirstSearch.hpp"
#include "ReachabilityGame.hpp"
#include "Vertex.hpp"

using namespace std::placeholders;
using namespace exploration;
using namespace types;

#define HEURISTIC_BIND std::bind(&ReachabilityGame::AStartPositive, &game, _1, _2)

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

        REQUIRE(path.isANashEquilibrium());
        REQUIRE(path.getCosts()[0].first);
        REQUIRE(path.getCosts()[0].second == 2);
        REQUIRE(path.getCosts()[1].first);
        REQUIRE(path.getCosts()[1].second == 3);
        REQUIRE(path == Path(game, {v1, v2, v3, v0}));
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

        std::unordered_set<Vertex::Ptr> vertices1{v1, v3, v4, v6};
        std::unordered_set<Vertex::Ptr> vertices2{v0, v2, v5, v7};

        SECTION("Goal1={v6}, Goal2={v0}, init=v3") {
            Player j1(0, vertices1, {v6});
            v6->addTargetFor(0);

            Player j2(1, vertices2, {v0});
            v0->addTargetFor(1);

            ReachabilityGame game(g, v3, {j1, j2});

            Path path = bestFirstSearch(game, HEURISTIC_BIND);

            REQUIRE(path.isANashEquilibrium());
            REQUIRE_FALSE(path.getCosts()[0].first);
            REQUIRE(path.getCosts()[1].first);
            REQUIRE(path.getCosts()[1].second == 2);

            REQUIRE(path == Path(game, {v3, v2, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0, v0}));
        }

        SECTION("Goal1={v4, v7}, Goal2={v6}, init=v5") {
            Player j1(0, vertices1, {v4, v7});
            v4->addTargetFor(0);
            v7->addTargetFor(0);

            Player j2(1, vertices2, {v6});
            v6->addTargetFor(1);

            ReachabilityGame game(g, v5, {j1, j2});

            Path path = bestFirstSearch(game, HEURISTIC_BIND);

            REQUIRE(path.isANashEquilibrium());
            REQUIRE(path.getCosts()[0].first);
            REQUIRE(path.getCosts()[0].second == 2);
            REQUIRE(path.getCosts()[1].first);
            REQUIRE(path.getCosts()[1].second == 1);

            REQUIRE(path == Path(game, {v5, v6, v7}));
        }
    }

    SECTION("Que pour J2") {
        // Cet exemple vient d'une erreur dans le code en Python
        Vertex::Ptr v0 = std::make_shared<Vertex>(0, 1, 2);
        Vertex::Ptr v1 = std::make_shared<Vertex>(1, 1, 2);
        Vertex::Ptr v2 = std::make_shared<Vertex>(2, 1, 2);
        Vertex::Ptr v3 = std::make_shared<Vertex>(3, 1, 2);
        Vertex::Ptr v4 = std::make_shared<Vertex>(4, 1, 2);

        v0->addSuccessor(v0, 1);
        v0->addSuccessor(v1, 0);
        v0->addSuccessor(v3, 1);

        v1->addSuccessor(v2, 1);
        v1->addSuccessor(v3, 0);
        v1->addSuccessor(v4, 1);

        v2->addSuccessor(v0, 0);
        v2->addSuccessor(v1, 0);
        v2->addSuccessor(v2, 1);
        v2->addSuccessor(v3, 1);
        v2->addSuccessor(v4, 1);

        v3->addSuccessor(v0, 0);
        v3->addSuccessor(v2, 1);
        v3->addSuccessor(v4, 0);

        v4->addSuccessor(v0, 1);

        std::vector<Vertex::Ptr> vertices{v0, v1, v2, v3, v4};

        Graph g(vertices, 2);

        Player min(0, {}, {v0});
        Player max(1, {v0, v1, v2, v3, v4}, {v3});
        v0->addTargetFor(0);
        v3->addTargetFor(1);

        ReachabilityGame game(g, v4, {min, max});

        Path path = bestFirstSearch(game, HEURISTIC_BIND);

        REQUIRE(path.isANashEquilibrium());
        REQUIRE(path.getCosts()[0].first);
        REQUIRE(path.getCosts()[0].second == 1);
        REQUIRE(path.getCosts()[1].first);
        REQUIRE(path.getCosts()[1].second == 1);

        REQUIRE(path == Path(game, {v4, v0, v1, v3}));
    }
}