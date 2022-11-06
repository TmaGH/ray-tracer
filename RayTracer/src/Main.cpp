#include <iostream>
#include <fstream>
#include "Tuple/Tuple.h"
#include "Canvas/Canvas.h"
#include "Matrix/Matrix.h";

struct Projectile {
	Tuple position;
	Tuple velocity;
};

struct Environment {
	Tuple gravity;
	Tuple wind;
};

void tick(const Environment& env, Projectile& proj) {
	proj.position = proj.position + proj.velocity;
	proj.velocity = proj.velocity + env.gravity + env.wind;
}

/*
int main() {
	auto identity = Matrix::getFourByFourIdentity();

	auto inverseOfIdentity = Matrix::invert(identity);

	auto a = Matrix{ 4,4 };

	float matrixContent[] = {
			3.0f, -9.0f, 7.0f, 3.0f,
			3.0f, -8.0f, 2.0f, -9.0f,
			-4.0f, 4.0f, 4.0f, 1.0f,
			-6.0f, 5.0f, -1.0f, 1.0f,
	};
	a.setData(matrixContent);

	std::cout << Matrix::invert(Matrix::transpose(a)) << std::endl;

	std::cout << Matrix::transpose(Matrix::invert(a)) << std::endl;

}
*/

/*
int main() {
	auto canvas = Canvas(1000, 1000);

	Projectile proj;
	proj.position = Tuple::point(0, 900, 0);
	proj.velocity = Tuple::vector(50, 0, 0);

	Environment env;
	env.gravity = Tuple::vector(0, -9.5, 0);
	env.wind = Tuple::vector(-2, 0, 0);

	while (proj.position.y > 0) {
		tick(env, proj);
		std::cout << "Projectile pos: " << proj.position << std::endl;
		std::cout << "Projectile vel: " << proj.velocity << std::endl;
		std::cout << "----------------------------" << std::endl;
		canvas.writePixel(std::round(proj.position.x), 899 - std::clamp((int) std::round(proj.position.y), 0, 899), Color(255, 0, 0));
		canvas.writePixel(std::round(proj.position.x) + 1, 899 - std::clamp((int) std::round(proj.position.y), 0, 899), Color(255, 0, 0));
		canvas.writePixel(std::round(proj.position.x) - 1, 899 - std::clamp((int) std::round(proj.position.y), 0, 899), Color(255, 0, 0));
	}

	std::cout << "Ended" << std::endl;

	std::ofstream o;

	o.open("test.ppm");
	o << Canvas::canvasToPPM(canvas);
	o.close();

	std::cout << "File closed" << std::endl;
}
*/