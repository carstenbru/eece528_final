// [header]

// A very basic raytracer example.
// [/header]
// [compile]
// c++ -o raytracer -O3 -Wall raytracer.cpp
// [/compile]
// [ignore]
// Copyright (C) 2012  www.scratchapixel.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// [/ignore]

#include "Raytracer_int.hpp"

#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>

#include "Sphere.hpp"

using namespace std;

#define MAX_RAY_DEPTH 10

#define UNSIGNED_MAX 0xFFFFFFFF

Color Raytracer_int::trace(const Vec3i &rayorig, const Vec3i &raydir,
		const int &depth) {
	unsigned int tnear = UNSIGNED_MAX;
	const Sphere* object = NULL;
	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < objects.size(); ++i) {
		unsigned int t0 = UNSIGNED_MAX, t1 = UNSIGNED_MAX;
		if (intersect_uint(objects[i], rayorig, raydir, &t0, &t1)) {
			if (t0 < 0)
				t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				object = objects[i];
			}
		}
	}
	// if there's no intersection return black or background color
	if (!object)
		return generateColorI(3 * 256, 3 * 256, 3 * 256);

	Color surfaceColor = object->surfaceColor;  // color of the ray/surface of the object intersected by the ray
	Vec3i phit = mul(add(rayorig, raydir), tnear);  // point of intersection
	Vec3i nhit = sub(phit, conv_fp(object->center, SCENE_COORDINATE_PRECISION));  // normal at the intersection point

	normalize(&nhit);  // normalize normal direction
	// If the normal and the view direction are not opposite to each other
	// reverse the normal direction. That also means we are inside the sphere so set
	// the inside bool to true. Finally reverse the sign of IdotN which we want
	// positive.
	unsigned int bias = 65;  //1e-4;  // add some bias to the point from which we will be tracing
	if (dot(raydir, nhit) > 0)
		nhit = sub(generateVectorI(0, 0, 0), nhit);  //invert normal if necessary
	if ((object->reflection > 0) && depth < MAX_RAY_DEPTH) {
		int facingratio = (-dot(raydir, nhit) >> FP_PRECISION);
		// change the mix value to tweak the effect
		unsigned int fresneleffect = ((unsigned int) (0.1 * FP_ONE)
				+ (unsigned int) (0.9 * FP_ONE)
						* (pow((FP_ONE - facingratio) / (float) FP_ONE, 3)));  //TODO pow in fixed-point
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vec3i refldir = mul(sub(raydir, nhit),
				2 * dot(raydir, nhit) >> FP_PRECISION);
		normalize(&refldir);
		Color reflection = trace(add(phit, mul(nhit, bias)), refldir, depth + 1);
		surfaceColor = mul(object->surfaceColor, mul(reflection, fresneleffect));
	} else {
		// it's a diffuse object, no need to raytrace any further
		for (unsigned i = 0; i < objects.size(); ++i) {
			if (objects[i]->emissionColor.r > 0) {
				// this is a light
				unsigned int shadow = 0;
				Vec3i lightDirection = sub(
						conv_fp(objects[i]->center, SCENE_COORDINATE_PRECISION), phit);
				normalize(&lightDirection);
				for (unsigned j = 0; j < objects.size(); ++j) {
					if (i != j) {
						unsigned int t0, t1;
						if (intersect_uint(objects[j], add(phit, mul(nhit, bias)),
								lightDirection, &t0, &t1)) {
							shadow = 1;
							break;
						}
					}
				}
				if (!shadow) {
					surfaceColor = add(surfaceColor,
							mul(
									mul(object->surfaceColor,
											std::max(0,
													(int) (dot(nhit, lightDirection) >> FP_PRECISION))),
									objects[i]->emissionColor));
				}
			}
		}
	}

	return add(surfaceColor, object->emissionColor);
}

Color Raytracer_int::trace_it(Vec3i &rayorig, Vec3i &raydir) {
	Color resColor = generateColor(0, 0, 0);
	Color mulColor = generateColor(1, 1, 1);
	int stop = 0;
	for (int rec_depth = 0; rec_depth <= MAX_RAY_DEPTH; rec_depth++) {
		unsigned int tnear = UNSIGNED_MAX;
		const Sphere* object = NULL;
		// find intersection of this ray with the sphere in the scene
		for (unsigned i = 0; i < objects.size(); ++i) {
			unsigned int t0 = UNSIGNED_MAX, t1 = UNSIGNED_MAX;
			if (intersect_uint(objects[i], rayorig, raydir, &t0, &t1)) {
				if (t0 < 0)
					t0 = t1;
				if (t0 < tnear) {
					tnear = t0;
					object = objects[i];
				}
			}
		}
		// if there's no intersection return black or background color
		if (!object) {
			resColor = add(resColor, mul(mulColor, 3 * FP_ONE));
			break;
		}

		Color surfaceColor = object->surfaceColor;  // color of the ray/surface of the object intersected by the ray
		Vec3i phit = mul(add(rayorig, raydir), tnear);  // point of intersection
		Vec3i nhit = sub(phit, conv_fp(object->center, SCENE_COORDINATE_PRECISION));  // normal at the intersection point

		normalize(&nhit);  // normalize normal direction
		// If the normal and the view direction are not opposite to each other
		// reverse the normal direction. That also means we are inside the sphere so set
		// the inside bool to true. Finally reverse the sign of IdotN which we want
		// positive.
		unsigned int bias = 65;  //1e-4;  // add some bias to the point from which we will be tracing
		if (dot(raydir, nhit) > 0)
			nhit = sub(generateVectorI(0, 0, 0), nhit);  //invert normal if necessary
		if ((object->reflection > 0) && rec_depth < MAX_RAY_DEPTH) {
			int facingratio = (-dot(raydir, nhit) >> FP_PRECISION);
			// change the mix value to tweak the effect
			unsigned int fresneleffect = ((unsigned int) (0.1 * FP_ONE)
					+ (unsigned int) (0.9 * FP_ONE)
							* (pow((FP_ONE - facingratio) / (float) FP_ONE, 3)));  //TODO pow in fixed-point
			// compute reflection direction (not need to normalize because all vectors
			// are already normalized)
			raydir = mul(sub(raydir, nhit), 2 * dot(raydir, nhit) >> FP_PRECISION);
			normalize(&raydir);
			rayorig = add(phit, mul(nhit, bias));
			//Color reflection = trace(add(phit, mul(nhit, bias)), refldir, depth + 1);
			//surfaceColor = mul(object->surfaceColor, mul(reflection, fresneleffect));
			resColor = add(resColor, mul(mulColor, object->emissionColor));
			mulColor = mul(mulColor, mul(object->surfaceColor, fresneleffect));
		} else {
			// it's a diffuse object, no need to raytrace any further
			for (unsigned i = 0; i < objects.size(); ++i) {
				if (objects[i]->emissionColor.r > 0) {
					// this is a light
					unsigned int shadow = 0;
					Vec3i lightDirection = sub(
							conv_fp(objects[i]->center, SCENE_COORDINATE_PRECISION), phit);
					normalize(&lightDirection);
					for (unsigned j = 0; j < objects.size(); ++j) {
						if (i != j) {
							unsigned int t0, t1;
							if (intersect_uint(objects[j], add(phit, mul(nhit, bias)),
									lightDirection, &t0, &t1)) {
								shadow = 1;
								break;
							}
						}
					}
					if (!shadow) {
						surfaceColor = add(surfaceColor,
								mul(
										mul(object->surfaceColor,
												std::max(0,
														(int) (dot(nhit, lightDirection) >> FP_PRECISION))),
										objects[i]->emissionColor));
					}
				}
			}
			resColor = add(resColor, mul(mulColor, surfaceColor));
			stop = 1;
		}
		if (stop) {
			break;
		}
	}
	return resColor;
}

void Raytracer_int::render(unsigned int* imageData) {
	Color pixel;
	int invWidth_2x = (FP_ONE << 1) / screenWidth;
	int invHeight_2x = (FP_ONE << 1) / screenHeight;
	int aspectratio = (screenWidth << FP_PRECISION) / screenHeight;
	int angle = (unsigned int) (0.267949194 * FP_ONE);
	// Trace rays
	for (unsigned y = 0; y < screenHeight; ++y) {
		for (unsigned x = 0; x < screenWidth; ++x) {
			int xx = (((int) ((((((x << FP_PRECISION) + (FP_ONE >> 1))
					* (long) invWidth_2x) >> FP_PRECISION) - FP_ONE) * angle)
					>> FP_PRECISION) * aspectratio) >> FP_PRECISION;
			int yy = ((FP_ONE
					- ((((y << FP_PRECISION) + (FP_ONE >> 1)) * (long) invHeight_2x)
							>> FP_PRECISION)) * angle) >> FP_PRECISION;
			Vec3i raydir = { xx, yy, -FP_ONE };
			normalize(&raydir);
			//pixel = trace(generateVectorI(0, 0, 0), raydir, 0);
			Vec3i rayorig = generateVectorI(0, 0, 0);
			pixel = trace_it(rayorig, raydir);
			*imageData++ = (std::min((unsigned int) 255, pixel.r)) << 16
					| (std::min((unsigned int) 255, pixel.g)) << 8
					| (std::min((unsigned int) 255, pixel.b));
		}
	}

	objects[1]->center.z -= 1;  //TODO remove, only for testing
}
