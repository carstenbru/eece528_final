#include <iostream>

#ifndef VEC3_HPP_
#define VEC3_HPP_

#include "dtypes.h"

typedef struct {
	unsigned int r;
	unsigned int g;
	unsigned int b;
} Color;

typedef struct {
	int x;
	int y;
	int z;
} Vec3i;

#define FP_PRECISION (16)
#define FP_ONE (1<<FP_PRECISION)

Color generateColorI(unsigned int r, unsigned int g, unsigned int b);
Color generateColor(float r, float g, float b);
Vec3i generateVectorI(int x, int y, int z);

Color add(const Color v1, const Color v2);
Color mul(const Color v1, int mul);
Color mul(const Color v1, const Color v2);

Vec3i add(const Vec3i v1, const Vec3i v2);
Vec3i sub(const Vec3i v1, const Vec3i v2);
Vec3i mul(const Vec3i v1, int mul);
Vec3i conv_fp(const Vec3i v1, int cur_precision);
int64 dot(const Vec3i v1, const Vec3i v2);
Vec3i* normalize(Vec3i* v);
int64 length2(const Vec3i v);


#endif
