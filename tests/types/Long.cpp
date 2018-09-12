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

#include "types/Long.hpp"
#include "types/InfinityError.hpp"

using namespace types;

SCENARIO("Long", "[types]") {
    GIVEN("One long is the +infinity") {
        Long l = Long::infinity;

        WHEN("The other long is +infinity") {
            Long o = Long::infinity;

            THEN("The sum is OK") {
                REQUIRE(l+o == Long::infinity);
            }

            THEN("The difference is NOK") {
                REQUIRE_THROWS_AS(l-o == Long::infinity, InfinityError);
            }

            THEN("No one is > or <") {
                REQUIRE_FALSE(l > o);
                REQUIRE_FALSE(l < o);
            }

            THEN("<= and >= are OK") {
                REQUIRE(l <= o);
                REQUIRE(l >= o);
            }

            THEN("l == o") {
                REQUIRE(l==o);
                REQUIRE_FALSE(l!=o);
            }
        }

        WHEN("The other long is -infinity") {
            Long o = -Long::infinity;

            THEN("The sum is NOK") {
                REQUIRE_THROWS_AS(l+o == Long::infinity, InfinityError);
            }

            THEN("The difference is OK") {
                REQUIRE(l-o == Long::infinity);
            }

            THEN("+inf > -inf") {
                REQUIRE(l > o);
                REQUIRE(l >= o);
                REQUIRE_FALSE(l < o);
                REQUIRE_FALSE(l <= o);
            }

            THEN("l != o") {
                REQUIRE(l!=o);
                REQUIRE_FALSE(l==o);
            }
        }

        WHEN("The other Long is a number") {
            Long o = 18;

            THEN("The sum/difference is +inf") {
                REQUIRE(l+o == Long::infinity);
                REQUIRE(l-o == Long::infinity);
            }

            THEN("+inf > number") {
                REQUIRE(l > o);
                REQUIRE(l >= o);
                REQUIRE_FALSE(l < o);
                REQUIRE_FALSE(l <= o);
                REQUIRE_FALSE(l == o);
                REQUIRE(l != o);
            }
        }
    }

    GIVEN("One long is -infinity") {
        Long l = -Long::infinity;

        WHEN("The other long is +infinity") {
            Long o = Long::infinity;

            THEN("The sum is NOK") {
                REQUIRE_THROWS_AS(l+o == -Long::infinity, InfinityError);
            }

            THEN("The difference is OK") {
                REQUIRE(l-o == -Long::infinity);
            }

            THEN("-inf < +inf") {
                REQUIRE_FALSE(l > o);
                REQUIRE_FALSE(l >= o);
                REQUIRE(l < o);
                REQUIRE(l <= o);
                REQUIRE_FALSE(l == o);
                REQUIRE(l != o);
            }
        }

        WHEN("The other long is -infinity") {
            Long o = -Long::infinity;

            THEN("The sum is OK") {
                REQUIRE(l+o == -Long::infinity);
            }

            THEN("The difference is NOK") {
                REQUIRE_THROWS_AS(l-o == -Long::infinity, InfinityError);
            }

            THEN("-inf <= -inf") {
                REQUIRE_FALSE(l > o);
                REQUIRE_FALSE(l < o);
                REQUIRE(l >= o);
                REQUIRE(l <= o);
                REQUIRE(l == o);
                REQUIRE_FALSE(l != o);
            }
        }

        WHEN("The other Long is a number") {
            Long o = 18;

            THEN("The sum/difference is -inf") {
                REQUIRE(l+o == -Long::infinity);
                REQUIRE(l-o == -Long::infinity);
            }

            THEN("-inf < number") {
                REQUIRE_FALSE(l > o);
                REQUIRE_FALSE(l >= o);
                REQUIRE(l < o);
                REQUIRE(l <= o);
                REQUIRE_FALSE(l == o);
                REQUIRE(l != o);
            }
        }
    }

    GIVEN("One long is a number") {
        Long l = 18;

        WHEN("The other long is +inf") {
            Long o = Long::infinity;
            THEN("The sum (difference) is +inf (-inf)") {
                REQUIRE(l + o == Long::infinity);
                REQUIRE(l - o == -Long::infinity);
            }

            THEN("number < +inf") {
                REQUIRE(l < o);
                REQUIRE(l <= o);
                REQUIRE_FALSE(l > o);
                REQUIRE_FALSE(l >= o);
                REQUIRE_FALSE(l == o);
                REQUIRE(l != o);
            }
        }

        WHEN("The other long is -inf") {
            Long o = -Long::infinity;
            THEN("The sum (difference) is -inf (+inf)") {
                REQUIRE(l + o == -Long::infinity);
                REQUIRE(l - o == Long::infinity);
            }

            THEN("number > -inf") {
                REQUIRE_FALSE(l < o);
                REQUIRE_FALSE(l <= o);
                REQUIRE(l > o);
                REQUIRE(l >= o);
                REQUIRE_FALSE(l == o);
                REQUIRE(l != o);
            }
        }

        WHEN("The other long is a number") {
            Long o = 5;
            THEN("The sum (difference) is a number") {
                REQUIRE(l + o == 23);
                REQUIRE(l - o == 13);
                REQUIRE(l + 5 == 23);
            }

            THEN("18 > 5") {
                REQUIRE_FALSE(l < o);
                REQUIRE_FALSE(l <= o);
                REQUIRE(l > o);
                REQUIRE(l >= o);
                REQUIRE_FALSE(l == o);
                REQUIRE(l != o);
            }
        }
    }
}