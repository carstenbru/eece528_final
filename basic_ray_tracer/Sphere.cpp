#include "Sphere.hpp"
#include <malloc.h>
#include <math.h>

Sphere* generateSphere(const Vec3f &c, const float &r, const Vec3f &sc,
		const float &refl, const Vec3f &ec) {
	Sphere* s = (Sphere*)malloc(sizeof(Sphere));
	s->center = c;
	s->radius = r;
	s->radius2 = r * r;
	s->surfaceColor = sc;
	s->emissionColor = ec;
	s->reflection = refl;

	return s;
}

bool intersect(Sphere* sphere, const Vec3f &rayorig, const Vec3f &raydir,
		float &t0, float &t1) {
	Vec3f l = sub(sphere->center, rayorig);
	float tca = dot(l,raydir);
	if (tca < 0)
		return false;
	float d2 = dot(l,l) - tca * tca;
	if (d2 > sphere->radius2)
		return false;
	float thc = sqrt(sphere->radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}
