#pragma once
#include "catch.hpp"
#include "Tuple/Tuple.h"
#include "Color.h"
#include "Test/TupleEqualMatcher.h"

SCENARIO("Colors are (red, green, blue) tuples") {
	GIVEN("c <- color(-0.5, 0.4, 1.7)") {
		Color c = Color(-0.5, 0.4, 1.7);

		THEN("c.red = -0.5 AND c.green = 0.4 AND c.blue = 1.7") {
			REQUIRE(c.red() == -0.5f);
			REQUIRE(c.green() == 0.4f);
			REQUIRE(c.blue() == 1.7f);
			CHECK_THAT(c, isEqualTo(Tuple::vector(-0.5, 0.4, 1.7)));
		}
	}
}

SCENARIO("Adding colors") {
	GIVEN("c1 <- color(0.9, 0.6, 0.75) AND c2 <= color(0.7, 0.1, 0.25)") {
		auto c1 = Color(0.9, 0.6, 0.75);
		auto c2 = Color(0.7, 0.1, 0.25);

		THEN("c1 + c2 = color(1.6, 0.7, 1.0)") {
			CHECK_THAT(c1 + c2, isEqualTo(Color(1.6, 0.7, 1.0)));
		}
	}
}

SCENARIO("Subtracting colors") {
	GIVEN("c1 <- color(0.9, 0.6, 0.75) AND c2 <= color(0.7, 0.1, 0.25)") {
		auto c1 = Color(0.9, 0.6, 0.75);
		auto c2 = Color(0.7, 0.1, 0.25);

		THEN("c1 - c2 = color(0.2, 0.5, 0.5)") {
			CHECK_THAT(c1 - c2, isEqualTo(Color(0.2, 0.5, 0.5)));
		}
	}
}

SCENARIO("Multiplying a color by a scalar") {
	GIVEN("c <- color(0.2, 0.3, 0.4") {
		auto c = Color(0.2, 0.3, 0.4);
		THEN("c * 2 = color(0.4, 0.6, 0.8") {
			CHECK_THAT(c * 2, isEqualTo(Color(0.4, 0.6, 0.8)));
		}
	}
}

SCENARIO("Multiplying colors") {
	GIVEN("c1 <- color(1, 0.2, 0.4) AND c2 <- color(0.9, 1, 0.1)") {
		auto c1 = Color(1, 0.2, 0.4);
		auto c2 = Color(0.9, 1, 0.1);

		THEN("c1 * c2 = color(0.9, 0.2, 0.04)") {
			CHECK_THAT(c1 * c2, isEqualTo(Color(0.9, 0.2, 0.04)));
		}
	}
}
