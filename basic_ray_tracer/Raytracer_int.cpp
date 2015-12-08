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

/*
 float mix(const float &a, const float &b, const float &mix) {
 return b * mix + a * (1 - mix);
 }*/
float mix(const float &a, const float &b, const float &mix);

Color Raytracer_int::trace(const Vec3f &rayorig, const Vec3f &raydir,
		const int &depth) {
	float tnear = INFINITY;
	const Sphere* object = NULL;
	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < objects.size(); ++i) {
		float t0 = INFINITY, t1 = INFINITY;
		if (intersect(objects[i], rayorig, raydir, &t0, &t1)) {
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
	Color surfaceColor = { 0, 0, 0 };  // color of the ray/surfaceof the object intersected by the ray
	Vec3f phit = mul(add(rayorig, raydir), tnear);  // point of intersection
	Vec3f nhit = sub(phit, generateVector(object->center));  // normal at the intersection point
	normalize(&nhit);  // normalize normal direction
	// If the normal and the view direction are not opposite to each other
	// reverse the normal direction. That also means we are inside the sphere so set
	// the inside bool to true. Finally reverse the sign of IdotN which we want
	// positive.
	float bias = 1e-4;  // add some bias to the point from which we will be tracing
	if (dot(raydir, nhit) > 0)
		nhit = sub(generateVector(0), nhit);
	if ((object->reflection > 0) && depth < MAX_RAY_DEPTH) {
		float facingratio = -dot(raydir, nhit);
		// change the mix value to tweak the effect
		float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vec3f refldir = mul(sub(raydir, nhit), 2 * dot(raydir, nhit));
		normalize(&refldir);
		Color reflection = trace(add(phit, mul(nhit, bias)), refldir, depth + 1);
		surfaceColor = mul(object->surfaceColor, mul(reflection, fresneleffect));
	} else {
		// it's a diffuse object, no need to raytrace any further
		for (unsigned i = 0; i < objects.size(); ++i) {
			if (objects[i]->emissionColor.r > 0) {
				// this is a light
				unsigned int shadow = 0;
				Vec3f lightDirection = sub(generateVector(objects[i]->center), phit);
				normalize(&lightDirection);
				for (unsigned j = 0; j < objects.size(); ++j) {
					if (i != j) {
						float t0, t1;
						if (intersect(objects[j], add(phit, mul(nhit, bias)),
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
											std::max(float(0), dot(nhit, lightDirection))),
									objects[i]->emissionColor));
				}
			}
		}
	}

	return add(surfaceColor, object->emissionColor);
}

//[comment]
// Main rendering function. We compute a camera ray for each pixel of the image
// trace it and return a color. If the ray hits a sphere, we return the color of the
// sphere at the intersection point, else we return the background color.
//[/comment]
void Raytracer_int::render(unsigned int* imageData) {
	Color pixel;
	float invWidth = 1 / float(screenWidth), invHeight = 1 / float(screenHeight);
	float fov = 30, aspectratio = screenWidth / float(screenHeight);
	float angle = tan(M_PI * 0.5 * fov / 180.);
	// Trace rays
	for (unsigned y = 0; y < screenHeight; ++y) {
		for (unsigned x = 0; x < screenWidth; ++x) {
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Vec3f raydir = { xx, yy, -1 };
			normalize(&raydir);
			pixel = trace(generateVector(0), raydir, 0);
			*imageData++ = (std::min((unsigned int) 255, pixel.r)) << 16
					| (std::min((unsigned int) 255, pixel.g)) << 8
					| (std::min((unsigned int) 255, pixel.b));
		}
	}

	objects[1]->center.z -= 1;  //TODO remove, only for testing
}
