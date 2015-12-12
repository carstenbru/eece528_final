#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "Vec3.hpp"
#include "Sphere.hpp"

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

protected:
	void parseScene(std::ifstream& in);
	void parseSphere(std::ifstream& in);
	Vec3i parseVector(std::string line);
	Color parseColor(std::string line) ;
	float parseFloat(std::string line);

	std::vector<Sphere*> objects;

	unsigned int screenWidth;
	unsigned int screenHeight;
};

#endif
