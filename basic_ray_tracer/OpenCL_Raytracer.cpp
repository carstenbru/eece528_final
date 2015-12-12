#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "OpenCL_Raytracer.hpp"

using namespace std;

OpenCL_Raytracer::OpenCL_Raytracer(unsigned int screenWidth,
		unsigned int screenHeight) :
		Raytracer(screenWidth, screenHeight), scene_objects(0) {
	char build_c[65535 * 64];
	size_t srcsize;

	cl_int error;
	cl_platform_id platform;
	cl_device_id device;
	cl_uint platforms, devices;

	/* Fetch the Platforms, we only want one. */
	error = clGetPlatformIDs(1, &platform, &platforms);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	/* Fetch the Devices for this platform */
	error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &devices);
	if (error != CL_SUCCESS) {
		printf("\nhi\n");
		printf("\n Error number %d", error);
	}
	/* Create a memory context for the device we want to use  */
	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM,
			(cl_context_properties) platform, 0 };
	/* Note that nVidia's OpenCL requires the platform property */
	context = clCreateContext(properties, 1, &device, NULL, NULL, &error);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	/* Create a command queue to communicate with the device */
	command_queue = clCreateCommandQueue(context, device, 0, &error);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}

	/* Read the source kernel code in exmaple.cl as an array of char's */
	char src[8192];
	FILE *fil = fopen("trace.cl", "r");
	srcsize = fread(src, sizeof src, 1, fil);
	fclose(fil);

	const char *srcptr[] = { src };
	/* Submit the source code of the kernel to OpenCL, and create a program object with it */
	prog = clCreateProgramWithSource(context, 1, srcptr, &srcsize, &error);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}

	/* Compile the kernel code (after this we could extract the compiled version) */
	error = clBuildProgram(prog, 0, NULL, "", NULL, NULL);
	if (error != CL_SUCCESS) {
		printf("Error on buildProgram ");
		printf("\n Error number %d", error);
		fprintf( stdout, "\nRequestingInfo\n");
		clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG, 4096, build_c,
		NULL);
		printf("Build Log for %s_program:\n%s\n", "example", build_c);
	}

	frameSize = screenWidth * screenHeight * sizeof(unsigned int);
	trace_kernel = clCreateKernel(prog, "trace_cl", &error);
	frame = clCreateBuffer(context, CL_MEM_WRITE_ONLY, frameSize, NULL, &error);

	/* Set the kernel parameters, scene size will be set later */
	clSetKernelArg(trace_kernel, 2, sizeof(frame), &frame);
}

void OpenCL_Raytracer::render(unsigned int* imageData) {
	cl_int error;
	int sceneSize = objects.size() * sizeof(Sphere);
	scene = clCreateBuffer(context, CL_MEM_READ_ONLY, sceneSize, NULL, &error); //TODO generate in separate method
	scene_objects = objects.size();
	clSetKernelArg(trace_kernel, 0, sizeof(scene), &scene);
	clSetKernelArg(trace_kernel, 1, sizeof(int), &scene_objects);

	//pass scene data to OpenGL
	for (unsigned int i = 0; i < objects.size(); i++) {
		clEnqueueWriteBuffer(command_queue, scene, CL_FALSE, i * sizeof(Sphere),
				sizeof(Sphere), objects[i], 0, NULL,
				NULL);
	}
	/* Tell the Device, through the command queue, to execute the Kernel */
	size_t global_item_size[2] = { screenWidth, screenHeight };
	clEnqueueNDRangeKernel(command_queue, trace_kernel, 2, NULL, global_item_size,
	NULL, 0, NULL, NULL);
	/* Read the result back into framebuffer */
	clEnqueueReadBuffer(command_queue, frame, CL_FALSE, 0, frameSize, imageData,
			0,
			NULL,
			NULL);
	/* Await completion of all the above */
	clFinish(command_queue);

	objects[1]->center.z -= 1;  //TODO remove, only for testing
	//cout << "OpenCL Raytracer finished!" << endl;  //TODO remove
}
