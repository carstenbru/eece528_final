#ifndef RAYTRACER_OPENMP_HPP_
#define RAYTRACER_OPENMP_HPP_

#include "Raytracer_int.hpp"

class Raytracer_OpenMP: public Raytracer_int {
public:
	Raytracer_OpenMP(unsigned int screenWidth, unsigned int screenHeight) :
			Raytracer_int(screenWidth, screenHeight) {
	}
	virtual ~Raytracer_OpenMP() {
	}
	virtual void render(unsigned int* imageData);
};

#endif /* RAYTRACER_OPENMP_HPP_ */
