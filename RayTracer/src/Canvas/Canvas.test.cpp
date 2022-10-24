#pragma once
#include "catch.hpp"
#include "Tuple/Tuple.h"
#include "Color/Color.h"
#include "Canvas.h"
#include "Test/TupleEqualMatcher.h"

SCENARIO("Creating a canvas") {
	GIVEN("c <- canvas(10, 20)") {
		auto c = Canvas(10, 20);

		THEN("c.width = 10 AND c.height = 20") {
			REQUIRE(c.width() == 10);
			REQUIRE(c.height() == 20);
		}

		THEN("Every pixel of c is a color(0, 0 ,0)") {
			CHECK_THAT(c.pixels()[0], isEqualTo(Color(0, 0, 0)));
			CHECK_THAT(c.pixels()[5], isEqualTo(Color(0, 0, 0)));
			CHECK_THAT(c.pixels()[10], isEqualTo(Color(0, 0, 0)));
			CHECK_THAT(c.pixels()[100], isEqualTo(Color(0, 0, 0)));
			CHECK_THAT(c.pixels()[199], isEqualTo(Color(0, 0, 0)));
		}
	}
}

SCENARIO("Writing pixels to a canvas") {
	GIVEN("c <- canvas(10, 20) AND red <- color(1, 0, 0)") {
		auto c = Canvas(10, 20);
		auto red = Color(1, 0, 0);

		WHEN("write_pixel(c, 2, 3, red)") {
			c.writePixel(2, 3, red);

			THEN("pixel_at(c, 2, 3) = red") {
				CHECK_THAT(c.pixelAt(2, 3), isEqualTo(red));
			}
		}
	}
}

SCENARIO("Constructing the PPM header") {
	GIVEN("c <- canvas(5, 3)") {
		auto c = Canvas(5, 3);

		WHEN("ppm <- canvas_to_ppm(c)") {
			auto ppm = Canvas::canvasToPPM(c);

			THEN("lines 1-3 of ppm are \nP3\n5 3\n255") {
				std::istringstream is(ppm);

				std::string line;
				std::getline(is, line, '\n');

				REQUIRE(line == "P3");

				std::getline(is, line, '\n');

				REQUIRE(line == "5 3");

				std::getline(is, line, '\n');

				REQUIRE(line == "255");
			}
		}
	}
}

SCENARIO("Constructing the PPM pixel data") {
	GIVEN("c <- canvas(5, 3) AND c1 <- color(1.5, 0, 0) AND c2 <- color(0, 0.5, 0) AND c3 <- color(-0.5, 0, 1)") {
		auto c = Canvas(5, 3);
		auto c1 = Color(1.5, 0, 0);
		auto c2 = Color(0, 0.5, 0);
		auto c3 = Color(-0.5, 0, 1);

		WHEN("write_pixel(c, 0, 0 c1), write_pixel(c, 2, 1, c2), write_pixel(c, 4, 2, c3) AND ppm <- canvas_to_ppm(c)") {
			c.writePixel(0, 0, c1);
			c.writePixel(2, 1, c2);
			c.writePixel(4, 2, c3);
			auto ppm = Canvas::canvasToPPM(c);

			THEN("lines 4 - 6 of ppm are 255 ...0\n...0 128 0...\n...0 255") {
				std::istringstream is(ppm);
				std::string line;

				is.ignore(INFINITE, '\n');
				is.ignore(INFINITE, '\n');
				is.ignore(INFINITE, '\n');

				std::getline(is, line, '\n');

				REQUIRE(line == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");

				std::getline(is, line, '\n');

				REQUIRE(line == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");

				std::getline(is, line, '\n');

				REQUIRE(line == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
			}
		}

	}
}

SCENARIO("Splitting long lines in PPM files") {
	GIVEN("c <- canvas(10, 2)") {
		auto c = Canvas(10, 2);

		WHEN("every pixel of c is set to color(1, 0.8, 0.6) and ppm <- canvas_to_ppm(c)") {
			for (int y = 0; y < 2; y++) {
				for (int x = 0; x < 10; x++) {
					c.writePixel(x, y, Color(1, 0.8, 0.6));
				}
			}

			auto ppm = Canvas::canvasToPPM(c);

			THEN("lines 4-7 of ppm are") {
				std::istringstream is(ppm);
				std::string line;

				is.ignore(INFINITE, '\n');
				is.ignore(INFINITE, '\n');
				is.ignore(INFINITE, '\n');

				std::getline(is, line, '\n');

				REQUIRE(line == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");

				std::getline(is, line, '\n');

				REQUIRE(line == "153 255 204 153 255 204 153 255 204 153 255 204 153");

				std::getline(is, line, '\n');

				REQUIRE(line == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");

				std::getline(is, line, '\n');

				REQUIRE(line == "153 255 204 153 255 204 153 255 204 153 255 204 153");
			}
		}
	}
}

SCENARIO("PPM files are terminated by a newline character") {
	GIVEN("c <- canvas(5, 3)") {
		auto c = Canvas(5, 3);
		
		WHEN("ppm <- canvas_to_ppm(c)") {
			auto ppm = Canvas::canvasToPPM(c);

			THEN("ppm ends with a newline character") {
				REQUIRE(ppm[ppm.size() - 1] == '\n');
			}
		}
	}
}