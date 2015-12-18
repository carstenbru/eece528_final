#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Vec3.hpp"

#define SCENE_COORDINATE_PRECISION 0 //TODO


typedef struct {
	Vec3i center;                           /// position of the object

	unsigned int radius;
	int radius2;

	Color surfaceColor, emissionColor;      /// surface color and emission (light)
	unsigned int reflection;      /// surface reflectivity

} Sphere;

Sphere* generateSphere(const Vec3i &c, const unsigned int &r, const Color &sc,
		const unsigned int &refl, const Color &ec);
bool intersect(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir,
		unsigned int* t0, unsigned int* t1);
bool intersect_hw(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir,
		unsigned int* t0, unsigned int* t1);
unsigned int fix64_sqrt(uint64 num);

#endif
