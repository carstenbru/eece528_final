#include "Sphere.hpp"
#include <malloc.h>
#include <math.h>
#include "dtypes.h"

#define USE_FP_SQRT_ALGO 0

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

#if (USE_FP_SQRT_ALGO == 1)
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
#endif

bool intersect(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir,
		unsigned int* t0, unsigned int* t1) {
	Vec3i l = sub(conv_fp(sphere->center, SCENE_COORDINATE_PRECISION), rayorig);
	int tca = dot(l,raydir) >> FP_PRECISION;
	if (tca < 0)
		return false;
	int64 d2 = (dot(l,l) >> FP_PRECISION) - (((int64)tca * tca) >> FP_PRECISION);
	if (d2 > (((int64)sphere->radius2) << FP_PRECISION))
		return false;
#if (USE_FP_SQRT_ALGO == 1)
	int thc = fix64_sqrt(((int64)sphere->radius2 << FP_PRECISION) - (d2));
#else
	int thc = ((int)sqrt(((int64)sphere->radius2 << FP_PRECISION) - (d2))) * 256; //TODO use integer sqrt instead of float algorithm
#endif
	*t0 = tca - thc;
	*t1 = tca + thc;

	return true;
}

