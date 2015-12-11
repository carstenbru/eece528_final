#ifndef RAYTRACER_PTHREADS_HPP_
#define RAYTRACER_PTHREADS_HPP_

#include "Raytracer_int.hpp"

class Raytracer_pthreads: public Raytracer_int {
public:
	Raytracer_pthreads(unsigned int screenWidth, unsigned int screenHeight) :
			Raytracer_int(screenWidth, screenHeight) {
	}
	virtual ~Raytracer_pthreads() {

	}
	virtual void render(unsigned int* imageData);
};

#endif /* RAYTRACER_PTHREADS_HPP_ */
