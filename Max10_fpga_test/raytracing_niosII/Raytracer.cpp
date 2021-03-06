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

#include "Raytracer.hpp"

#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
//#include <fstream>

#include "Sphere.hpp"
extern "C"{
	#include "LCD32.h"
}

using namespace std;

//[comment]
// This variable controls the maximum recursion depth
//[/comment]
#define MAX_RAY_DEPTH 10

float mix(const float &a, const float &b, const float &mix) {
	return b * mix + a * (1 - mix);
}

//[comment]
// This is the main trace function. It takes a ray as argument (defined by its origin
// and direction). We test if this ray intersects any of the geometry in the scene.
// If the ray intersects an object, we compute the intersection point, the normal
// at the intersection point, and shade this point using this information.
// Shading depends on the surface property (is it transparent, reflective, diffuse).
// The function returns a color for the ray. If the ray intersects an object that
// is the color of the object at the intersection point, otherwise it returns
// the background color.
//[/comment]
Vec3f Raytracer::trace(const Vec3f &rayorig, const Vec3f &raydir,
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
		return generateVector(3);
	Vec3f surfaceColor = { 0, 0, 0 };  // color of the ray/surfaceof the object intersected by the ray
	Vec3f phit = mul(add(rayorig, raydir), tnear);  // point of intersection
	Vec3f nhit = sub(phit, object->center);  // normal at the intersection point
	normalize(&nhit);  // normalize normal direction
	// If the normal and the view direction are not opposite to each other
	// reverse the normal direction. That also means we are inside the sphere so set
	// the inside bool to true. Finally reverse the sign of IdotN which we want
	// positive.
	float bias = 1e-4;  // add some bias to the point from which we will be tracing
	if (dot(raydir, nhit) > 0)
		nhit = sub(generateVector(0), nhit);  //, inside = true;
	if ((object->reflection > 0) && depth < MAX_RAY_DEPTH) {
		float facingratio = -dot(raydir, nhit);
		// change the mix value to tweak the effect
		float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vec3f refldir = mul(sub(raydir, nhit), 2 * dot(raydir, nhit));
		normalize(&refldir);
		Vec3f reflection = trace(add(phit, mul(nhit, bias)), refldir, depth + 1);
		// the result is a mix of reflection and refraction (if the sphere is transparent)
		surfaceColor = mul(object->surfaceColor, mul(reflection, fresneleffect));
	} else {
		// it's a diffuse object, no need to raytrace any further
		for (unsigned i = 0; i < objects.size(); ++i) {
			if (objects[i]->emissionColor.x > 0) {
				// this is a light
				Vec3f transmission = { 1, 1, 1 };
				Vec3f lightDirection = sub(objects[i]->center, phit);
				normalize(&lightDirection);
				for (unsigned j = 0; j < objects.size(); ++j) {
					if (i != j) {
						float t0, t1;
						if (intersect(objects[j], add(phit, mul(nhit, bias)),
								lightDirection, &t0, &t1)) {
							transmission = generateVector(0);
							break;
						}
					}
				}
				surfaceColor = add(surfaceColor,
						mul(
								mul(object->surfaceColor,
										mul(transmission,
												std::max(float(0), dot(nhit, lightDirection)))),
								objects[i]->emissionColor));
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
void Raytracer::render(unsigned int* imageData) {
	Vec3f pixel;
	float invWidth = 1 / float(screenWidth), invHeight = 1 / float(screenHeight);
	float fov = 30, aspectratio = screenWidth / float(screenHeight);
	float angle = tan(M_PI * 0.5 * fov / 180.);
	unsigned char R,G,B;
	// Trace rays

	for (unsigned y = 0; y < screenHeight; ++y) {
		for (unsigned x = 0; x < screenWidth; ++x) {
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Vec3f raydir = { xx, yy, -1 };
			normalize(&raydir);
			pixel = trace(generateVector(0), raydir, 0);
			R=(unsigned char)(std::min(float(1), pixel.x) * 255);
			G=(unsigned char)(std::min(float(1), pixel.y) * 255);
			B=(unsigned char)(std::min(float(1), pixel.z) * 255);
			vid_set_pixel(x, y,RGB565CONVERT(R,G,B));
//			*imageData++ =(R<<16)| (G<<8)
//					| (int) (std::min(float(1), pixel.z) * 255);
		}
	}

	objects[1]->center.z -= 0.5;  //TODO remove, only for testing
}

void Raytracer::generateSimpleScene() {
	objects.push_back(
			generateSphere(generateVector(0.0, -10004, -20), 10000,
					generateVector(0.20, 0.20, 0.20), 0, generateVector(0)));
	objects.push_back(
			generateSphere(generateVector(0.0, 0, -20), 4,
					generateVector(1.00, 0.32, 0.36), 1, generateVector(0)));
	objects.push_back(
			generateSphere(generateVector(5.0, -1, -15), 2,
					generateVector(0.90, 0.76, 0.46), 1, generateVector(0)));
	objects.push_back(
			generateSphere(generateVector(5.0, 0, -25), 3,
					generateVector(0.65, 0.77, 0.97), 1, generateVector(0)));
	objects.push_back(
			generateSphere(generateVector(-5.5, 0, -25), 3,
					generateVector(0.90, 0.90, 0.90), 1, generateVector(0)));
	// light
	objects.push_back(
			generateSphere(generateVector(0.0, 20, -30), 3,
					generateVector(0.00, 0.00, 0.00), 0, generateVector(3)));
}

Vec3f Raytracer::parseVector(string line) {
	int pos = line.find("=\"") + 2;
	int pos2 = line.find("\"", pos) - pos;
	string number1 = line.substr(pos, line.find("\"", pos) - pos);

	pos = line.find("=\"", pos + pos2) + 2;
	pos2 = line.find("\"", pos) - pos;
	string number2 = line.substr(pos, line.find("\"", pos) - pos);

	pos = line.find("=\"", pos + pos2) + 2;
	pos2 = line.find("\"", pos) - pos;
	string number3 = line.substr(pos, line.find("\"", pos) - pos);

	return generateVector(
			atof(number1.c_str()), atof(number2.c_str()), atof(number3.c_str()));
}

float Raytracer::parseFloat(string line) {
	int pos = line.find("value=\"") + 7;
	string number = line.substr(pos, line.find("\"", pos) - pos);
	return atof(number.c_str());
}

void Raytracer::parseScene(ifstream& in) {
	string line;
	while (getline(in, line)) {
		if (line.find("</Scene>") != string::npos) {
			return;
		}
		if (line.find("<Sphere>") != string::npos) {
			parseSphere(in);
		}
	}
}

void Raytracer::parseSphere(ifstream& in) {
	Vec3f center = { 0, 0, 0 };
	float radius = 0;
	Vec3f surfaceColor = { 0, 0, 0 };
	float reflection = 0;
	Vec3f emissionColor = { 0, 0, 0 };

	string line;
	while (getline(in, line)) {
		if (line.find("</Sphere>") != string::npos) {
			objects.push_back(
					generateSphere(center, radius, surfaceColor, reflection,
							emissionColor));
			return;
		}
		if (line.find("<center") != string::npos) {
			center = parseVector(line);
		}
		if (line.find("<radius") != string::npos) {
			radius = parseFloat(line);
		}
		if (line.find("<surfaceColor") != string::npos) {
			surfaceColor = parseVector(line);
		}
		if (line.find("<reflection") != string::npos) {
			reflection = parseFloat(line);
		}
		if (line.find("<emissionColor") != string::npos) {
			emissionColor = parseVector(line);
		}
	}
}

void Raytracer::loadScene(std::string filename) {	 // position, radius, surface color, reflectivity, transparency, emission color
	string line;
	ifstream in(filename.c_str());
	if (in.is_open()) {
		while (getline(in, line)) {
			if (line.find("<Scene>") != string::npos) {
				parseScene(in);
			}
		}
		in.close();
	}
}
