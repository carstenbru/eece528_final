#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Vec3.hpp"

typedef struct {
	Vec3i center;                           /// position of the object

	unsigned int radius, radius2;

	Color surfaceColor, emissionColor;      /// surface color and emission (light)
	unsigned int reflection;      /// surface reflectivity

} Sphere;

Sphere* generateSphere(const Vec3i &c, const unsigned int &r, const Color &sc,
		const unsigned int &refl, const Color &ec);
bool intersect(Sphere* sphere, const Vec3f rayorig, const Vec3f raydir,
		float* t0, float* t1);
bool intersect_uint(Sphere* sphere, const Vec3f rayorig, const Vec3f raydir,
		unsigned int* t0, unsigned int* t1);

#endif
