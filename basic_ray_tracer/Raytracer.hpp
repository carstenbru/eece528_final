#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "Vec3.hpp"
#include "RayObject.hpp"

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

class Raytracer {
public:
	Raytracer() {
	}
	;
	void render(unsigned int* imageData);
	void loadScene(std::string filename);
	void generateSimpleScene();

private:
	Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir, const int &depth);
	void parseScene(std::ifstream& in);
	void parseSphere(std::ifstream& in);
	Vec3f parseVector(std::string line);
	float parseFloat(std::string line);

	std::vector<RayObject*> objects;
};

#endif
