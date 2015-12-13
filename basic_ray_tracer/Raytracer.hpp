#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "Vec3.hpp"
#include "Sphere.hpp"
#include "dtypes.h"

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

class Raytracer {
public:
	Raytracer(unsigned int screenWidth, unsigned int screenHeight) :
			screenWidth(screenWidth), screenHeight(screenHeight) {
	}
	virtual ~Raytracer() {}
	virtual void render(unsigned int* imageData) = 0;

	void loadScene(std::string filename);
	void generateSimpleScene();

	void setreal_frame_width(unsigned int real_frame_width) {
		this->real_frame_width = real_frame_width;
	}

protected:
	void parseScene(std::ifstream& in);
	void parseSphere(std::ifstream& in);
	Vec3i parseVector(std::string line);
	Color parseColor(std::string line) ;
	float parseFloat(std::string line);

	std::vector<Sphere*> objects;

	unsigned int screenWidth;
	unsigned int screenHeight;
	unsigned int real_frame_width;
};

#endif
