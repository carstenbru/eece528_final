#include "Vec3.hpp"
#include <math.h>

Color generateColorI(unsigned int r, unsigned int g, unsigned int b) {
	Color c = { r, g, b };
	return c;
}

Color generateColor(float r, float g, float b) {
	Color c = { r * 255, g * 255, b * 255 };
	return c;
}

Vec3i generateVectorI(int x, int y, int z) {
	Vec3i v = { x, y, z };
	return v;
}

Color add(const Color v1, const Color v2) {
	Color v = { v1.r + v2.r, v1.g + v2.g, v1.b + v2.b };
	return v;
}

Color mul(const Color v1, int mul) {
	Color v = { (v1.r * mul) >> FP_PRECISION, (v1.g * mul) >> FP_PRECISION, (v1.b
			* mul) >> FP_PRECISION };
	return v;
}

Color mul(const Color v1, const Color v2) {
	Color v = { (v1.r * v2.r) >> 8, (v1.g * v2.g) >> 8, (v1.b * v2.b) >> 8 };
	return v;
}

Vec3i sub(const Vec3i v1, const Vec3i v2) {
	Vec3i v = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return v;
}

Vec3i add(const Vec3i v1, const Vec3i v2) {
	Vec3i v = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	return v;
}

Vec3i conv_fp(const Vec3i v1, int cur_precision) {
	Vec3i v =
			{ v1.x << (FP_PRECISION - cur_precision), v1.y
					<< (FP_PRECISION - cur_precision), v1.z
					<< (FP_PRECISION - cur_precision) };
	return v;
}

Vec3i mul(const Vec3i v1, int mul) {
	Vec3i v = { (v1.x * (long) mul) >> FP_PRECISION, (v1.y * (long) mul)
			>> FP_PRECISION, (v1.z * (long) mul) >> FP_PRECISION };
	return v;
}

Vec3i* normalize(Vec3i* v) {  //TODO do calulation in fp arithmetic
	long int nor2 = length2(*v);
	if (nor2 > 0) {
		unsigned int invNor = FP_ONE / sqrt(nor2 / (float) FP_ONE);
		v->x = ((long)v->x*invNor) >> FP_PRECISION;
		v->y = ((long)v->y*invNor) >> FP_PRECISION;
		v->z = ((long)v->z*invNor) >> FP_PRECISION;
	}
	return v;
}

long int length2(const Vec3i v) {
	return (v.x * (long) v.x + v.y * (long) v.y + v.z * (long) v.z)
			>> (FP_PRECISION);
}

long int dot(const Vec3i v1, const Vec3i v2) {
	return ((long) v1.x * (long) v2.x + (long) v1.y * (long) v2.y
			+ (long) v1.z * (long) v2.z);
}
