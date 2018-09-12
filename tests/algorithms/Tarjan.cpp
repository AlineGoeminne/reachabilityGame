/*
 * ReachabilityGame - a program to compute the best Nash equilibrium in reachability games
 * Copyright (C) 2018 Gaëtan Staquet and Aline Goeminne
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "catch.hpp"

#include "algorithms/Tarjan.hpp"

TEST_CASE("Algorithme de Tarjan", "[algorithms]") {
    SECTION("Le graphe est une seule composante") {
        Vertex::Ptr v0 = std::make_shared<Vertex>(0, 0, 2);
        Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 2);
        Vertex::Ptr v2 = std::make_shared<Vertex>(2, 0, 2);
        Vertex::Ptr v3 = std::make_shared<Vertex>(3, 0, 2);

        v0->addSuccessor(v1, 1);
        v1->addSuccessor(v3, 1);
        v2->addSuccessor(v1, 1);
        v3->addSuccessor(v0, 1);
        v3->addSuccessor(v2, 1);

        std::vector<Vertex::Ptr> vertices{v0, v1, v2, v3};

        Graph graph(vertices, 2);

        auto components = algorithms::tarjan(graph);

        REQUIRE(components.size() == 1);

        REQUIRE(components.find({0, 1, 2, 3}) != components.end());
    }

    SECTION("Aucune composante fortement connexe") {
        Vertex::Ptr v0 = std::make_shared<Vertex>(0, 0, 2);
        Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 2);
        Vertex::Ptr v2 = std::make_shared<Vertex>(2, 0, 2);
        Vertex::Ptr v3 = std::make_shared<Vertex>(3, 0, 2);

        v0->addSuccessor(v1, 0);
        v1->addSuccessor(v2, 0);
        v2->addSuccessor(v3, 0);
        v3->addSuccessor(v3, 0);

        std::vector<Vertex::Ptr> vertices{v0, v1, v2, v3};

        Graph graph(vertices, {0, 0});

        auto components = algorithms::tarjan(graph);

        REQUIRE(components.size() == 4);
        REQUIRE(components.find({0}) != components.end());
        REQUIRE(components.find({1}) != components.end());
        REQUIRE(components.find({2}) != components.end());
        REQUIRE(components.find({3}) != components.end());
    }

    SECTION("Deux composantes fortement connexes") {
        Vertex::Ptr v0 = std::make_shared<Vertex>(0, 0, 2);
        Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 2);
        Vertex::Ptr v2 = std::make_shared<Vertex>(2, 0, 2);
        Vertex::Ptr v3 = std::make_shared<Vertex>(3, 0, 2);
        Vertex::Ptr v4 = std::make_shared<Vertex>(4, 0, 2);
        Vertex::Ptr v5 = std::make_shared<Vertex>(5, 0, 2);
        Vertex::Ptr v6 = std::make_shared<Vertex>(6, 0, 2);
        Vertex::Ptr v7 = std::make_shared<Vertex>(7, 0, 2);

        v0->addSuccessor(v1, 0);
        v1->addSuccessor(v2, 0);
        v2->addSuccessor(v3, 0);
        v3->addSuccessor(v0, 0);

        v4->addSuccessor(v5, 0);
        v5->addSuccessor(v6, 0);
        v6->addSuccessor(v7, 0);
        v7->addSuccessor(v4, 0);

        std::vector<Vertex::Ptr> vertices{v0, v1, v2, v3, v4, v5, v6, v7};

        SECTION("Graphes disjoints") {
            Graph graph(vertices, {0, 0});

            auto components = algorithms::tarjan(graph);

            REQUIRE(components.size() == 2);
            REQUIRE(components.find({0, 1, 2, 3}) != components.end());
            REQUIRE(components.find({4, 5, 6, 7}) != components.end());
        }

        SECTION("Un seul graphe") {
            v3->addSuccessor(v7, 0);

            Graph graph(vertices, {0, 0});

            auto components = algorithms::tarjan(graph);

            REQUIRE(components.size() == 2);
            REQUIRE(components.find({0, 1, 2, 3}) != components.end());
            REQUIRE(components.find({4, 5, 6, 7}) != components.end());

            SECTION("On unit les deux composantes") {
                v6->addSuccessor(v2, 0);

                auto components = algorithms::tarjan(graph);

                REQUIRE(components.size() == 1);
                REQUIRE(components.find({0, 1, 2, 3, 4, 5, 6, 7}) != components.end());
            }
        }
    }

    SECTION("Un noeud seul attaché à une composante") {
        Vertex::Ptr v0 = std::make_shared<Vertex>(0, 0, 2);
        Vertex::Ptr v1 = std::make_shared<Vertex>(1, 0, 2);
        Vertex::Ptr v2 = std::make_shared<Vertex>(2, 0, 2);
        Vertex::Ptr v3 = std::make_shared<Vertex>(3, 0, 2);
        Vertex::Ptr v4 = std::make_shared<Vertex>(4, 0, 2);

        v0->addSuccessor(v1, 0);
        v1->addSuccessor(v2, 0);
        v2->addSuccessor(v3, 0);
        v3->addSuccessor(v0, 0);
        v4->addSuccessor(v0, 0);

        std::vector<Vertex::Ptr> vertices{v0, v1, v2, v3, v4};

        Graph graph(vertices, {0, 0});

        auto components = algorithms::tarjan(graph);

        REQUIRE(components.size() == 2);
        REQUIRE(components.find({4}) != components.end());
        REQUIRE(components.find({0, 1, 2, 3}) != components.end());
    }
}