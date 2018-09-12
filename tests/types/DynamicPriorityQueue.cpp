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

#include "types/DynamicPriorityQueue.hpp"

using namespace types;

SCENARIO("On stocke des simples entiers", "[types]") {
    GIVEN("Le comparateur par défaut") {
        DynamicPriorityQueue<int> queue;

        WHEN("On insère {5, 1, 20, 2, 1}") {
            queue.push(5);
            queue.push(1);
            queue.push(20);
            queue.push(2);
            queue.push(1);

            THEN("Le haut du tas est 20") {
                REQUIRE(queue.top() == 20);

                AND_THEN("Après extraction, le haut est 5") {
                    queue.pop();
                    REQUIRE(queue.top() == 5);

                    AND_THEN("Après extraction, il reste, dans l'ordre {2, 1, 1}") {
                        queue.pop();
                        REQUIRE(queue.top() == 2);
                        queue.pop();
                        REQUIRE(queue.top() == 1);
                        queue.pop();
                        REQUIRE(queue.top() == 1);

                        AND_THEN("Le tas est vide") {
                            queue.pop();
                            REQUIRE(queue.empty());
                            REQUIRE_THROWS(queue.top());
                            REQUIRE_THROWS(queue.pop());
                        }
                    }
                }
            }

            AND_WHEN("On change 5 en 30") {
                queue.update(5, 30);

                THEN("Le haut du tas est 30") {
                    REQUIRE(queue.top() == 30);

                    AND_THEN("Le reste du tas est {20, 2, 1, 1}") {
                        queue.pop();
                        REQUIRE(queue.top() == 20);
                        queue.pop();
                        REQUIRE(queue.top() == 2);
                        queue.pop();
                        REQUIRE(queue.top() == 1);
                        queue.pop();
                        REQUIRE(queue.top() == 1);
                    }
                }
            }

            AND_WHEN("On change 5 en 0") {
                queue.update(5, 0);

                THEN("La pile est {20, 2, 1, 1, 0}") {
                    REQUIRE(queue.top() == 20);
                    queue.pop();
                    REQUIRE(queue.top() == 2);
                    queue.pop();
                    REQUIRE(queue.top() == 1);
                    queue.pop();
                    REQUIRE(queue.top() == 1);
                    queue.pop();
                    REQUIRE(queue.top() == 0);
                }
            }
        }
    }
    
    GIVEN("Le comparateur std::greater") {
        DynamicPriorityQueue<int, std::greater<int>> queue;
        
        WHEN("On insère {1, 2, 20, 5}") {
            queue.push(1);
            queue.push(2);
            queue.push(20);
            queue.push(5);

            THEN("Le tas est {1, 2, 5, 20}") {
                REQUIRE(queue.top() == 1);
                queue.pop();
                REQUIRE(queue.top() == 2);
                queue.pop();
                REQUIRE(queue.top() == 5);
                queue.pop();
                REQUIRE(queue.top() == 20);
            }
        }
    }
}

struct Data {
    int d;

    Data() : d(0) {}
    Data(int a) : d(a) {}

    bool operator()(const Data& a, const Data& b) const {
        return a.d < b.d;
    }

};

bool operator==(const Data& a, const Data &b) {
    return a.d == b.d;
}

SCENARIO("On stocke des structures/classes", "[types]") {
    DynamicPriorityQueue<Data, Data> queue;

    WHEN("On insère des instances définies par {3, 1, 7, 4}") {
        queue.push({3});
        queue.push({1});
        queue.push({7});
        queue.push({4});

        THEN("Le haut du tas est 7") {
            REQUIRE(queue.top() == Data(7));

            AND_THEN("Le reste du tas est {4, 3, 1}") {
                queue.pop();
                REQUIRE(queue.top() == Data(4));
                queue.pop();
                REQUIRE(queue.top() == Data(3));
                queue.pop();
                REQUIRE(queue.top() == Data(1));
            }
        }
    }
}