#include "Vec3.hpp"
#include <math.h>

#if (USE_FP_SQRT_ALGO == 1)
//adapted from https://github.com/asik/FixedMath.Net/issues/6
unsigned int fix64_sqrt(uint64 num) {
	uint64 result = 0UL;

	// second-to-top bit
	uint64 bit = (uint64)0x4000000000000000;//1UL << (62);

	while (bit > num) {
		bit >>= 2;
	}

	// The main part is executed twice, in order to avoid
	// using 128 bit values in computations.
	for (int i = 0; i < 2; ++i) {
		// First we get the top 48 bits of the answer.
		while (bit != 0) {
			if (num >= result + bit) {
				num -= result + bit;
				result = (result >> 1) + bit;
			} else {
				result = result >> 1;
			}
			bit >>= 2;
		}

		if (i == 0) {
			// Then process it again to get the lowest 16 bits.
			if (num > (uint64)65535) {
				// The remainder 'num' is too large to be shifted left
				// by 32, so we have to add 1 to result manually and
				// adjust 'num' accordingly.
				// num = a - (result + 0.5)^2
				//       = num + result^2 - (result + 0.5)^2
				//       = num - result - 0.5
				num -= result;
				num = (num << (16)) - (uint64)0x4000;
				result = (result << (16)) + (uint64)0x4000;
			} else {
				num <<= (16);
				result <<= (16);
			}

			bit = ((uint64)1) << (14);
		}
	}
	// Finally, if next bit would have been 1, round the result upwards.
	if (num > result) {
		++result;
	}
	return result;
}
#endif

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
	Vec3i v = { (v1.x * (int64) mul) >> FP_PRECISION, (v1.y * (int64) mul)
			>> FP_PRECISION, (v1.z * (int64) mul) >> FP_PRECISION };
	return v;
}

Vec3i* normalize(Vec3i* v) {  //TODO do calulation in fp arithmetic
	int64 nor2 = length2(*v);
	if (nor2 > 0) {
#if (USE_FP_SQRT_ALGO == 1)
		unsigned int invNor = ((uint64)FP_ONE * FP_ONE) / fix64_sqrt(nor2);
#else
		unsigned int invNor = FP_ONE / sqrt(nor2 / (float) FP_ONE);
#endif
		v->x = ((int64) v->x * invNor) >> FP_PRECISION;
		v->y = ((int64) v->y * invNor) >> FP_PRECISION;
		v->z = ((int64) v->z * invNor) >> FP_PRECISION;
	}
	return v;
}

int64 length2(const Vec3i v) {
	return (v.x * (int64) v.x + v.y * (int64) v.y + v.z * (int64) v.z)
			>> (FP_PRECISION);
}

int64 dot(const Vec3i v1, const Vec3i v2) {
	return ((int64) v1.x * (int64) v2.x + (int64) v1.y * (int64) v2.y
			+ (int64) v1.z * (int64) v2.z);
}
