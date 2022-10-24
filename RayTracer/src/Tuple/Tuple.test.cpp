#pragma once
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Tuple.h"
#include "Test/TupleEqualMatcher.h"

SCENARIO("A tuple with w=1.0 is a point", "[tuple]") {
	GIVEN("a <- Tuple(4.3, -4.2, 3.1, 1.0)") {
		Tuple a(4.3f, -4.2f, 3.1f, 1.0f);

		THEN("a.x = 4.3") {
			REQUIRE(a.x == 4.3f);
		}

		THEN("a.y = -4.2") {
			REQUIRE(a.y == -4.2f);
		}

		THEN("a.z = 3.1") {
			REQUIRE(a.z == 3.1f);
		}

		THEN("a.w = 1.0") {
			REQUIRE(a.w == 1.0f);
		}

		THEN("a is a point") {
			REQUIRE(a.isPoint());
		}

		THEN("a is not a vector") {
			REQUIRE(!a.isVector());
		}
	}
}

SCENARIO("A tuple with w=0.0 is a point", "[tuple]") {
	GIVEN("a <- Tuple(4.3, -4.2, 3.1, 0.0)") {
		Tuple a(4.3f, -4.2f, 3.1f, 0.0f);

		THEN("a.x = 4.3") {
			REQUIRE(a.x == 4.3f);
		}

		THEN("a.y = -4.2") {
			REQUIRE(a.y == -4.2f);
		}

		THEN("a.z = 3.1") {
			REQUIRE(a.z == 3.1f);
		}

		THEN("a.w = 0.0") {
			REQUIRE(a.w == 0.0f);
		}

		THEN("a is not a point") {
			REQUIRE(!a.isPoint());
		}

		THEN("a is a vector") {
			REQUIRE(a.isVector());
		}
	}
}

SCENARIO("point() creates tuple with w=1") {
	GIVEN("p <- point(4, -4, 3)") {
		auto p = Tuple::point(4, -4, 3);
		
		THEN("p = tuple(4, -4, 3, 1)") {
			CHECK_THAT(p, isEqualTo(Tuple(4, -4, 3, 1)));
		}
	}
}

SCENARIO("vector() creates a tuple with w=0") {
	GIVEN("v <- vector(4, -4, 3)") {
		auto v = Tuple::vector(4, -4, 3);
		
		THEN("v = tuple(4, -4, 3, 0)") {
			CHECK_THAT(v, isEqualTo(Tuple(4, -4, 3, 0)));
		}
	}

}

SCENARIO("Adding two tuples") {
	GIVEN("a1 <- tuple(3, -2, 5, 1) AND a2 <- tuple(-2, 3, 1, 0)") {
		auto a1 = Tuple(3, -2, 5, 1);
		auto a2 = Tuple(-2, 3, 1, 0);

		THEN("a1 + a2 = tuple(1, 1, 6, 1)") {
			CHECK_THAT(a1 + a2, isEqualTo(Tuple(1, 1, 6, 1)));
		}
	}
}

SCENARIO("Subtracting two points") {
	GIVEN("p1 <- point(3, 2, 1) AND p2 <- point(5, 6, 7)") {
		auto p1 = Tuple::point(3, 2, 1);
		auto p2 = Tuple::point(5, 6, 7);

		THEN("p1 - p2 = vector(-2, -4, -6)") {
			CHECK_THAT(p1 - p2, isEqualTo(Tuple::vector(-2, -4, -6)));
		}
	}
}

SCENARIO("Subtracting a vector from the zero vector") {
	GIVEN("zero <- vector(0, 0, 0) AND v <- vector(1, -2, 3)") {
		auto v = Tuple::vector(1, -2, 3);
		THEN("zero - v = vector(-1, 2, -3)") {
			CHECK_THAT(ZERO_VECTOR - v, isEqualTo(Tuple::vector(-1, 2, -3)));
		}
	}
}

SCENARIO("Negating a tuple") {
	GIVEN("a <- tuple(1, -2, 3, -4)") {
		auto a = Tuple(1, -2, 3, -4);

		THEN("-a = tuple(-1, 2, -3, 4)") {
			CHECK_THAT(-a, isEqualTo(Tuple(-1, 2, -3, 4)));
		}
	}
}

SCENARIO("Multiplying a tuple by a scalar") {
	GIVEN("a <- tuple(1, -2, 3, -4)") {
		auto a = Tuple(1, -2, 3, -4);
		THEN("a * 3.5 = tuple(3.5, -7, 10.5, -14)") {
			CHECK_THAT(a * 3.5, isEqualTo(Tuple(3.5, -7, 10.5, -14)));
		}
	}
}

SCENARIO("Multiplying a tuple by a fraction") {
	GIVEN("a <- tuple(1, -2, 3, -4)") {
		auto a = Tuple(1, -2, 3, -4);
		THEN("a * 0.5 = tuple(0.5, -1, 1.5, -2)") {
			CHECK_THAT(a * 0.5, isEqualTo(Tuple(0.5, -1, 1.5, -2)));
		}
	}
}

SCENARIO("Dividing a tuple by a scalar") {
	GIVEN("a <- tuple(1, -2, 3, -4)") {
		auto a = Tuple(1, -2, 3, -4);
		THEN("a / 2 = tuple(0.5, -1, 1.5, -2") {
			CHECK_THAT(a * 0.5, isEqualTo(Tuple(0.5, -1, 1.5, -2)));
		}
	}
}

SCENARIO("Computing the magnitude of a vector(1, 2, 3)") {
	GIVEN("v <- vector(1, 2, 3)") {
		auto v = Tuple::vector(1, 2, 3);
		THEN("magnitude(v) = 1") {
			CHECK_THAT(v.magnitude(), Catch::WithinAbs(std::sqrt(14), EPSILON));
		}
	}
}

SCENARIO("Computing the magnitude of a vector(-1, -2, -3)") {
	GIVEN("v <- vector(-1, -2, -3)") {
		auto v = Tuple::vector(-1, -2, -3);
		THEN("magnitude(v) = 1") {
			CHECK_THAT(v.magnitude(), Catch::WithinAbs(std::sqrt(14), EPSILON));
		}
	}
}

SCENARIO("Normalizing vector(4, 0, 0) gives (1, 0, 0)") {
	GIVEN("v <- vector(4, 0, 0)") {
		auto v = Tuple::vector(4, 0, 0);
		THEN("normalize(v) = vector(1, 0, 0)") {
			CHECK_THAT(v.normalized(), isEqualTo(Tuple::vector(1, 0, 0)));
		}
	}
}

SCENARIO("Normalizing vector(1, 2, 3)") {
	GIVEN("v <- vector(1, 2, 3)") {
		auto v = Tuple::vector(1, 2, 3);
		THEN("normalize(v) = approximately vector(0.26726, 0.53452, 0.80178)") {
			CHECK_THAT(v.normalized(), isEqualTo(Tuple::vector(0.26726, 0.53452, 0.80178)));
		}
	}
}

SCENARIO("The magnitude of a normalized vector") {
	GIVEN("v <- vector(1, 2, 3)") {
		auto v = Tuple::vector(1, 2, 3);
		WHEN("norm <- normalize(v)") {
			auto norm = v.normalized();
			THEN("magnitude(norm) = 1") {
				CHECK_THAT(norm.magnitude(), Catch::WithinAbs(1, EPSILON));
			}
		}
	}
}

SCENARIO("The dot product of two tuples") {
	GIVEN("a <- vector(1, 2, 3) AND b <- vector(2, 3, 4)") {
		auto a = Tuple::vector(1, 2, 3);
		auto b = Tuple::vector(2, 3, 4);

		THEN("dot(a, b) = 20") {
			REQUIRE(a.dot(b) == 20);
		}
	}
}

SCENARIO("The cross product of two vectors") {
	GIVEN("a <- vector(1, 2, 3) AND b <- vector(2, 3, 4)") {
		auto a = Tuple::vector(1, 2, 3);
		auto b = Tuple::vector(2, 3, 4);

		THEN("cross(a, b) = vector(-1, 2, -1)") {
			CHECK_THAT(a.cross(b), isEqualTo(Tuple::vector(-1, 2, -1)));
		}

		THEN("cross(b, a) = vector(1, -2, 1)") {
			CHECK_THAT(b.cross(a), isEqualTo(Tuple::vector(1, -2, 1)));
		}
	}
}

