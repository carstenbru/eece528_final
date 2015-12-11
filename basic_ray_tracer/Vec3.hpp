#include <iostream>

#ifndef VEC3_HPP_
#define VEC3_HPP_

typedef struct {
	float x;
	float y;
	float z;
} Vec3f;

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
Color generateColorI(Vec3f v);
Color generateColor(float r, float g, float b);
Color generateColor(Vec3f v);
Vec3f generateVector(Vec3i v);
Vec3f generateVector(Color v);
Vec3f generateVector(float x, float y, float z);
Vec3f generateVector(float val);
Vec3i generateVectorI(int x, int y, int z);
Vec3i generateVector(Vec3f v);

Color add(const Color v1, const Color v2);
Color mul(const Color v1, int mul);
Color mul(const Color v1, const Color v2);

Vec3i add(const Vec3i v1, const Vec3i v2);
Vec3i sub(const Vec3i v1, const Vec3i v2);
Vec3i mul(const Vec3i v1, int mul);
Vec3i conv_fp(const Vec3i v1, int cur_precision);
long int dot(const Vec3i v1, const Vec3i v2);
Vec3i* normalize(Vec3i* v);
long int length2(const Vec3i v);


float dot(const Vec3f v1, const Vec3f v2);
Vec3f* normalize(Vec3f* v);
float length2(const Vec3f v);
Vec3f sub(const Vec3f v1, const Vec3f v2);
Vec3f add(const Vec3f v1, const Vec3f v2);
Vec3f mul(const Vec3f v1, float mul);
Vec3f mul(const Vec3f v1, const Vec3f v2);


#endif
