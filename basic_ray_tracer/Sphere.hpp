#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Vec3.hpp"

typedef struct {
	Vec3f center;                           /// position of the object

	float radius, radius2;

	Vec3f surfaceColor, emissionColor;      /// surface color and emission (light)
	float reflection;      /// surface reflectivity

} Sphere;

Sphere* generateSphere(const Vec3f &c, const float &r, const Vec3f &sc,
		const float &refl, const Vec3f &ec);
bool intersect(Sphere* sphere, const Vec3f rayorig, const Vec3f raydir,
		float* t0, float* t1);

#endif
