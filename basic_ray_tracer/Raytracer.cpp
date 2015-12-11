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
#include <fstream>

#include "Sphere.hpp"

using namespace std;

void Raytracer::generateSimpleScene() {
	objects.push_back(
			generateSphere(generateVectorI(0, -10004, -20), 10000,
					generateColor(51, 51, 51), 0, generateColor(0, 0, 0)));
	objects.push_back(
			generateSphere(generateVectorI(0, 0, -20), 4,
					generateColor(1.00, 0.32, 0.36), 1, generateColor(0, 0, 0)));
	objects.push_back(
			generateSphere(generateVectorI(5, -1, -15), 2,
					generateColor(0.90, 0.76, 0.46), 1, generateColor(0, 0, 0)));
	objects.push_back(
			generateSphere(generateVectorI(5, 0, -25), 3,
					generateColor(0.65, 0.77, 0.97), 1, generateColor(0, 0, 0)));
	objects.push_back(
			generateSphere(generateVectorI(-5.5, 0, -25), 3,
					generateColor(0.90, 0.90, 0.90), 1, generateColor(0, 0, 0)));
	// light
	objects.push_back(
			generateSphere(generateVectorI(0.0, 20, -30), 3,
					generateColor(0.00, 0.00, 0.00), 0, generateColor(3, 3, 3)));
}

Vec3i Raytracer::parseVector(string line) {
	int pos = line.find("=\"") + 2;
	int pos2 = line.find("\"", pos) - pos;
	string number1 = line.substr(pos, line.find("\"", pos) - pos);

	pos = line.find("=\"", pos + pos2) + 2;
	pos2 = line.find("\"", pos) - pos;
	string number2 = line.substr(pos, line.find("\"", pos) - pos);

	pos = line.find("=\"", pos + pos2) + 2;
	pos2 = line.find("\"", pos) - pos;
	string number3 = line.substr(pos, line.find("\"", pos) - pos);

	return generateVectorI(atoi(number1.c_str()), atoi(number2.c_str()),
			atoi(number3.c_str()));
}

Color Raytracer::parseColor(string line) {
	int pos = line.find("=\"") + 2;
	int pos2 = line.find("\"", pos) - pos;
	string number1 = line.substr(pos, line.find("\"", pos) - pos);

	pos = line.find("=\"", pos + pos2) + 2;
	pos2 = line.find("\"", pos) - pos;
	string number2 = line.substr(pos, line.find("\"", pos) - pos);

	pos = line.find("=\"", pos + pos2) + 2;
	pos2 = line.find("\"", pos) - pos;
	string number3 = line.substr(pos, line.find("\"", pos) - pos);

	return generateColor(atof(number1.c_str()), atof(number2.c_str()),
			atof(number3.c_str()));
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
	Vec3i center = { 0, 0, 0 };
	float radius = 0;
	Color surfaceColor = { 0, 0, 0 };
	float reflection = 0;
	Color emissionColor = { 0, 0, 0 };

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
			surfaceColor = parseColor(line);
		}
		if (line.find("<reflection") != string::npos) {
			reflection = parseFloat(line);
		}
		if (line.find("<emissionColor") != string::npos) {
			emissionColor = parseColor(line);
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
