#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "Raytracer.hpp"
#include "Vec3.hpp"
#include "Sphere.hpp"

#ifndef RAYTRACER_INT_HPP_
#define RAYTRACER_INT_HPP_

class Raytracer_int : public Raytracer {
public:
	Raytracer_int(unsigned int screenWidth, unsigned int screenHeight) :
			Raytracer(screenWidth, screenHeight) {
	}
	virtual ~Raytracer_int() {
	}
	virtual void render(unsigned int* imageData);

protected:
	Color trace(const Vec3f &rayorig, const Vec3f &raydir, const int &depth);
};

#endif
