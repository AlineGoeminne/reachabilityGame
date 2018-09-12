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
        Path path(game, {v1, v2, v3, v4, v3, v4, v3, v4});

        bool res = path.isANashEquilibrium();

        REQUIRE(res);

        REQUIRE(path.getCosts()[0].first);
        REQUIRE(path.getCosts()[0].second == 2);
        REQUIRE_FALSE(path.getCosts()[1].first);
    }

    SECTION("Les deux joueurs voient leur objectif") {
        Path path(game, {v1, v2, v3, v0, v1, v0, v1, v0, v1});

        bool res = path.isANashEquilibrium();

        REQUIRE(res);

        REQUIRE(path.getCosts()[0].first);
        REQUIRE(path.getCosts()[0].second == 2);
        REQUIRE(path.getCosts()[1].first);
        REQUIRE(path.getCosts()[1].second == 3);
    }

    SECTION("Pas un EN") {
        Path path(game, {v1, v2, v4, v2, v4, v2, v4, v2, v4, v2, v4});

        bool res = path.isANashEquilibrium();

        REQUIRE_FALSE(res);

        REQUIRE_FALSE(path.getCosts()[0].first);
        REQUIRE_FALSE(path.getCosts()[1].first);
    }
}