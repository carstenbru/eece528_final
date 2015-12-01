#include "Raytracer.hpp"

#ifndef OPENCL_RAYTRACER_HPP_
#define OPENCL_RAYTRACER_HPP_

class OpenCL_Raytracer: public Raytracer {
public:
	OpenCL_Raytracer(unsigned int screenWidth, unsigned int screenHeight) :
			Raytracer(screenWidth, screenHeight) {
	}
	virtual ~OpenCL_Raytracer() {
	}

	virtual void render(unsigned int* imageData);
};

#endif
