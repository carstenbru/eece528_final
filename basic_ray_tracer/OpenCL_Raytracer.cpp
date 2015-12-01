#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "OpenCL_Raytracer.hpp"

using namespace std;

void OpenCL_Raytracer::render(unsigned int* imageData) {
	char buf[] = "Hello, World!";
	char build_c[4096];
	size_t srcsize, worksize = strlen(buf);

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
	cl_context context = clCreateContext(properties, 1, &device, NULL, NULL,
			&error);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	/* Create a command queue to communicate with the device */
	cl_command_queue cq = clCreateCommandQueue(context, device, 0, &error);
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
	cl_program prog = clCreateProgramWithSource(context, 1, srcptr, &srcsize,
			&error);
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

	/* Create memory buffers in the Context where the desired Device is. These will be the pointer
	 parameters on the kernel. */
	cl_mem scene, frame;
	int sceneSize = objects.size() * sizeof(Sphere);
	int frameSize = screenWidth * screenHeight * sizeof(unsigned int);
	scene = clCreateBuffer(context, CL_MEM_READ_ONLY, sceneSize, NULL, &error);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	frame = clCreateBuffer(context, CL_MEM_WRITE_ONLY, frameSize, NULL, &error);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	/* Create a kernel object with the compiled program */
	cl_kernel k_example = clCreateKernel(prog, "example", &error);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}

	/* Set the kernel parameters */
	error = clSetKernelArg(k_example, 0, sizeof(scene), &scene);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	int scene_objects = objects.size();
	error = clSetKernelArg(k_example, 1, sizeof(int), &scene_objects);
		if (error != CL_SUCCESS) {
			printf("\n Error number %d", error);
		}
	error = clSetKernelArg(k_example, 2, sizeof(frame), &frame);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}

	/* Send input data to OpenCL (async, don't alter the buffer!) */
	for (unsigned int i = 0; i < objects.size(); i++) {
		error = clEnqueueWriteBuffer(cq, scene, CL_FALSE, i * sizeof(Sphere),
				sizeof(Sphere), objects[i], 0, NULL,
				NULL);
		if (error != CL_SUCCESS) {
			printf("\n Error number %d", error);
		}
	}
	/* Tell the Device, through the command queue, to execute the Kernel */
	size_t global_item_size[2] = { screenWidth, screenHeight};
	error = clEnqueueNDRangeKernel(cq, k_example, 2, NULL, global_item_size, NULL,
			0, NULL, NULL);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	/* Read the result back into buf2 */
	error = clEnqueueReadBuffer(cq, frame, CL_FALSE, 0, frameSize, imageData, 0,
	 NULL,
	 NULL);
	 if (error != CL_SUCCESS) {
	 printf("\n Error number %d", error);
	 }
	/* Await completion of all the above */
	error = clFinish(cq);
	if (error != CL_SUCCESS) {
		printf("\n Error number %d", error);
	}
	/* Finally, output the result */
	//TODO
	cout << "OpenCL Raytracer finished!" << endl; //TODO remove
}

Vec3f OpenCL_Raytracer::trace_openCL(const Vec3f &rayorig, const Vec3f &raydir,
		const int &depth) {
//TODO
}
