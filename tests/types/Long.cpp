#include "catch.hpp"

#include "types/Long.hpp"
#include "types/InfinityError.hpp"

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