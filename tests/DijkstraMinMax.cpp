#include "catch.hpp"

#include "MinMaxGame.hpp"
#include "ReachabilityGame.hpp"
#include "Graph.hpp"
#include "Vertex.hpp"
#include "Player.hpp"

TEST_CASE("DijkstraMinMax", "[dijkstra]") {
    SECTION("Exemple du mémoire") {
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

        std::vector<Player> players;
        players.emplace_back(0);
        players[0].addVertex(v1);
        players[0].addVertex(v3);
        players[0].addVertex(v4);
        players[0].addVertex(v6);
        players[0].addGoal(v0);

        players.emplace_back(1);
        players[1].addVertex(v2);
        players[1].addVertex(v5);
        players[1].addVertex(v7);

        ReachabilityGame game(g, v0, players);

        MinMaxGame minmax = MinMaxGame::convert(game, 0);

        auto values = minmax.getValues();

        REQUIRE(values[0] == 0);
        REQUIRE(values[1] == 1);
        REQUIRE(values[2] == 2);
        REQUIRE(values[3] == 3);
        REQUIRE(values[4] == 4);
        REQUIRE(values[5] == Long::infinity);
        REQUIRE(values[6] == Long::infinity);
        REQUIRE(values[7] == Long::infinity);
    }

}