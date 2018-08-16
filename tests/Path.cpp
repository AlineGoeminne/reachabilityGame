#include "catch.hpp"

#include <iostream>

#include "Path.hpp"
#include "ReachabilityGame.hpp"
#include "Vertex.hpp"

TEST_CASE("Est-ce qu'un chemin est un équilibre de Nash", "[path]") {
    // Le test est repris du code d'Aline
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

    v3->addTargetFor(0);
    v0->addTargetFor(1);

    Graph g(vertices, 2);

    Player p1(0, {v0, v1, v3, v4}, {v3});
    Player p2(0, {v2}, {v0});

    Vertex::Ptr init = v1;

    ReachabilityGame game(g, init, {p1, p2});

    SECTION("J1 voit son objectif") {
        Path path(game, {v1, v2, v3, v4, v3, v4, v3, v4}, 2);

        auto res = path.isANashEquilibrium();

        REQUIRE(res.first);

        REQUIRE(path.getCosts()[0].first);
        REQUIRE(path.getCosts()[0].second == 2);
        REQUIRE_FALSE(path.getCosts()[1].first);
    }

    SECTION("Les deux joueurs voient leur objectif") {
        Path path(game, {v1, v2, v3, v0, v1, v0, v1, v0, v1}, 2);

        auto res = path.isANashEquilibrium();

        REQUIRE(res.first);

        REQUIRE(path.getCosts()[0].first);
        REQUIRE(path.getCosts()[0].second == 2);
        REQUIRE(path.getCosts()[1].first);
        REQUIRE(path.getCosts()[1].second == 3);
    }

    SECTION("Pas un EN") {
        Path path(game, {v1, v2, v4, v2, v4, v2, v4, v2, v4, v2, v4}, 2);

        auto res = path.isANashEquilibrium();

        REQUIRE_FALSE(res.first);

        REQUIRE_FALSE(path.getCosts()[0].first);
        REQUIRE_FALSE(path.getCosts()[1].first);
    }
        //self.assertTrue(game.is_a_Nash_equilibrium(path2, {2}))
}