#include <math.h>


#define FP_PRECISION (16)
#define FP_ONE (1<<FP_PRECISION)
#define SCENE_COORDINATE_PRECISION 0 //TODO


typedef unsigned long long uint64;
typedef long long int64;

typedef struct {
	unsigned int r;
	unsigned int g;
	unsigned int b;
} Color;

typedef struct  {
	int x;
	int y;
	int z;
}Vec3i;

typedef struct {
	Vec3i center;                           /// position of the object

	unsigned int radius;
	int radius2;

	Color surfaceColor, emissionColor;      /// surface color and emission (light)
	unsigned int reflection;      /// surface reflectivity
} Sphere;

Vec3i sub(const Vec3i v1, const Vec3i v2) {
	Vec3i v = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return v;
}

int64 dot(const Vec3i v1, const Vec3i v2) {
	return ((int64) v1.x * (int64) v2.x + (int64) v1.y * (int64) v2.y
			+ (int64) v1.z * (int64) v2.z);
}

Vec3i conv_fp(const Vec3i v1, int cur_precision) {
	Vec3i v =
			{ v1.x << (FP_PRECISION - cur_precision), v1.y
					<< (FP_PRECISION - cur_precision), v1.z
					<< (FP_PRECISION - cur_precision) };
	return v;
}

//adapted from https://github.com/asik/FixedMath.Net/issues/6
unsigned int fix64_sqrt(uint64 num) {
    uint64 result = 0UL;

    // second-to-top bit
    uint64 bit = 1UL << (62);

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
            }
            else {
                result = result >> 1;
            }
            bit >>= 2;
        }

        if (i == 0) {
            // Then process it again to get the lowest 16 bits.
            if (num > (1UL << (16)) - 1) {
                // The remainder 'num' is too large to be shifted left
                // by 32, so we have to add 1 to result manually and
                // adjust 'num' accordingly.
                // num = a - (result + 0.5)^2
                //       = num + result^2 - (result + 0.5)^2
                //       = num - result - 0.5
                num -= result;
                num = (num << (16)) - 0x4000UL;
                result = (result << (16)) + 0x4000UL;
            }
            else {
                num <<= (16);
                result <<= (16);
            }

            bit = 1UL << (14);
        }
    }
    // Finally, if next bit would have been 1, round the result upwards.
    if (num > result) {
        ++result;
    }
    return result;
}



unsigned char intersect(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir,
		unsigned int* t0, unsigned int* t1, int square_root) {
	Vec3i l = sub(conv_fp(sphere->center, SCENE_COORDINATE_PRECISION), rayorig);
	int tca = dot(l,raydir) >> FP_PRECISION;
	if (tca < 0)
		return 0;
	int64 d2 = (dot(l,l) >> FP_PRECISION) - (((int64)tca * tca) >> FP_PRECISION);
	if (d2 > (((int64)sphere->radius2) << FP_PRECISION))
		return 0;
	int thc = fix64_sqrt(((int64)sphere->radius2 << FP_PRECISION) - (d2))*256;
	*t0 = tca - thc;
	*t1 = tca + thc;

	return 1;
}
