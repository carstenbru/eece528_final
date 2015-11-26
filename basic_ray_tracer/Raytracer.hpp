#include <iostream>
#include <vector>
#include <cmath>

#include "Vec3.hpp"
#include "Sphere.hpp"

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

class Raytracer {
public:
	Raytracer() {
	}
	;

	Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir,
			const std::vector<Sphere> &spheres, const int &depth);
	void render();
	void loadScene(std::string filename);

private:
	std::vector<Sphere> spheres;
};

#endif
