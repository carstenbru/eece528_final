#include "Sphere.hpp"
#include <malloc.h>
#include <math.h>
#include "dtypes.h"

Sphere* generateSphere(const Vec3i &c, const unsigned int &r, const Color &sc,
		const unsigned int &refl, const Color &ec) {
	Sphere* s = (Sphere*)malloc(sizeof(Sphere));
	s->center = c;
	s->radius = r;
	s->radius2 = r * r;
	s->surfaceColor = sc;
	s->emissionColor = ec;
	s->reflection = refl;

	return s;
}

bool intersect(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir,
		unsigned int* t0, unsigned int* t1) {
	Vec3i l = sub(conv_fp(sphere->center, SCENE_COORDINATE_PRECISION), rayorig);
	int tca = dot(l,raydir) >> FP_PRECISION;
	if (tca < 0)
		return false;
	int64 d2 = (dot(l,l) >> FP_PRECISION) - (((int64)tca * tca) >> FP_PRECISION);
	if (d2 > (((int64)sphere->radius2) << FP_PRECISION))
		return false;
	//int thc = sqrt((float)sphere->radius2 - d2/65536.0f) * FP_ONE;!
	int thc = ((int)sqrt(((int64)sphere->radius2 << FP_PRECISION) - (d2))) * 256;
	*t0 = tca - thc;
	*t1 = tca + thc;

	return true;
}

/*
bool intersect(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir,
		unsigned int* t0, unsigned int* t1) {
	Vec3i l = sub(conv_fp(sphere->center, SCENE_COORDINATE_PRECISION), rayorig);
	int tca = dot(l,raydir) >> FP_PRECISION;
	int64 d2 = (dot(l,l) >> FP_PRECISION) - (((int64)tca * tca) >> FP_PRECISION);
	int thc = sqrt((float)sphere->radius2 - d2/65536.0f) * FP_ONE; //TODO srqt in int/fp!
	*t0 = tca - thc;
	*t1 = tca + thc;

	if ((d2 > (((int64)sphere->radius2) << FP_PRECISION)) || (tca < 0))
			return false;
	else
	  return true;
}*/
