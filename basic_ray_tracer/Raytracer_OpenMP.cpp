#include "Raytracer_OpenMP.hpp"

#include <omp.h>

void Raytracer_OpenMP::render(unsigned int* imageData) {
	int invWidth_2x = (FP_ONE << 1) / screenWidth;
	int invHeight_2x = (FP_ONE << 1) / screenHeight;
	int aspectratio = (screenWidth << FP_PRECISION) / screenHeight;
	int angle = (unsigned int) (0.267949194 * FP_ONE);

	omp_set_num_threads(THREAD_NUM);
	omp_set_dynamic(true);

#pragma omp parallel for
	for (unsigned y = 0; y < screenHeight; ++y) {
		for (unsigned x = 0; x < screenWidth; ++x) {
			int xx = (((int) ((((((x << FP_PRECISION) + (FP_ONE >> 1))
					* (long) invWidth_2x) >> FP_PRECISION) - FP_ONE) * angle)
					>> FP_PRECISION) * aspectratio) >> FP_PRECISION;
			int yy = ((FP_ONE
					- ((((y << FP_PRECISION) + (FP_ONE >> 1)) * (long) invHeight_2x)
							>> FP_PRECISION)) * angle) >> FP_PRECISION;
			Vec3i raydir = { xx, yy, -FP_ONE };
			normalize(&raydir);
			Vec3i rayorig = generateVectorI(0, 0, 0);
			Color pixel = trace_it(rayorig, raydir);
			*(imageData + x + y * screenWidth) = (std::min((unsigned int) 255,
					pixel.r)) << 16 | (std::min((unsigned int) 255, pixel.g)) << 8
					| (std::min((unsigned int) 255, pixel.b));
		}
	}

	//objects[1]->center.z -= 1;  //TODO remove, only for testing

}
