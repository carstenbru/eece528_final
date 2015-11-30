#include "Vec3.hpp"
#include <math.h>

float dot(const Vec3f &v1, const Vec3f &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3f& normalize(Vec3f &v) {
	float nor2 = length2(v);
	if (nor2 > 0) {
		float invNor = 1 / sqrt(nor2);
		v.x *= invNor, v.y *= invNor, v.z *= invNor;
	}
	return v;
}

float length2(const Vec3f &v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vec3f sub(const Vec3f &v1, const Vec3f &v2) {
	return {v1.x-v2.x, v1.y-v2.y,v1.z-v2.z};
}

Vec3f add(const Vec3f &v1, const Vec3f &v2) {
	return {v1.x+v2.x, v1.y+v2.y,v1.z+v2.z};
}

Vec3f mul(const Vec3f &v1, float mul) {
	return {v1.x*mul, v1.y*mul,v1.z*mul};
}

Vec3f mul(const Vec3f &v1, const Vec3f &v2) {
	return {v1.x*v2.x, v1.y*v2.y,v1.z*v2.z};
}
