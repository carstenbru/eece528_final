#include "Raytracer.hpp"
#include <CL/cl.h>


#ifndef OPENCL_RAYTRACER_HPP_
#define OPENCL_RAYTRACER_HPP_

class OpenCL_Raytracer: public Raytracer {
public:
	OpenCL_Raytracer(unsigned int screenWidth, unsigned int screenHeight);
	virtual ~OpenCL_Raytracer() {
	}

	virtual void render(unsigned int* imageData);

protected:
	cl_context context;
	cl_program prog;
	cl_kernel trace_kernel;
	cl_command_queue command_queue;
	cl_mem scene;
	cl_mem frame;

	int frameSize;
	int scene_objects;
};

#endif
