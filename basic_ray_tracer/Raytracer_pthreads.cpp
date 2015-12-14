#include "Raytracer_pthreads.hpp"

#include <pthread.h>

unsigned int y;

using namespace std;

typedef struct {
	unsigned int* imageData;
	vector<Sphere*>& objects;
	unsigned int screenWidth;
	unsigned int screenHeight;
} traceStart;

Color trace_it(Vec3i &rayorig, Vec3i &raydir, std::vector<Sphere*>& objects) {
	Color resColor = generateColor(0, 0, 0);
	Color mulColor = generateColor(1, 1, 1);
	int stop = 0;
	for (int rec_depth = 0; rec_depth <= MAX_RAY_DEPTH; rec_depth++) {
		unsigned int tnear = UNSIGNED_MAX;
		const Sphere* object = NULL;
		// find intersection of this ray with the sphere in the scene
		for (unsigned i = 0; i < objects.size(); ++i) {
			unsigned int t0 = UNSIGNED_MAX, t1 = UNSIGNED_MAX;
			if (intersect(objects[i], rayorig, raydir, &t0, &t1)) {
				if (t0 < 0)
					t0 = t1;
				if (t0 < tnear) {
					tnear = t0;
					object = objects[i];
				}
			}
		}
		// if there's no intersection return black or background color
		if (!object) {
			resColor = add(resColor, mul(mulColor, 3 * FP_ONE));
			break;
		}

		Color surfaceColor = object->surfaceColor;  // color of the ray/surface of the object intersected by the ray
		Vec3i phit = mul(add(rayorig, raydir), tnear);  // point of intersection
		Vec3i nhit = sub(phit, conv_fp(object->center, SCENE_COORDINATE_PRECISION));  // normal at the intersection point

		normalize(&nhit);  // normalize normal direction
		// If the normal and the view direction are not opposite to each other
		// reverse the normal direction. That also means we are inside the sphere so set
		// the inside bool to true. Finally reverse the sign of IdotN which we want
		// positive.
		unsigned int bias = 65;  //1e-4;  // add some bias to the point from which we will be tracing
		if (dot(raydir, nhit) > 0)
			nhit = sub(generateVectorI(0, 0, 0), nhit);  //invert normal if necessary
		if ((object->reflection > 0) && rec_depth < MAX_RAY_DEPTH) {
			int facingratio = (-dot(raydir, nhit) >> FP_PRECISION);
			// change the mix value to tweak the effect
			facingratio = FP_ONE - facingratio;
						unsigned int fr2 = (facingratio * (int64)facingratio) >> FP_PRECISION;
						unsigned int fr3 = (fr2 * facingratio) >> FP_PRECISION;
						fr3 = (((unsigned int)(0.9*FP_ONE) * fr3)) >> FP_PRECISION;
						unsigned int fresneleffect = ((unsigned int) (0.1 * FP_ONE)) + fr3;
			// compute reflection direction (not need to normalize because all vectors
			// are already normalized)
			raydir = mul(sub(raydir, nhit), 2 * dot(raydir, nhit) >> FP_PRECISION);
			normalize(&raydir);
			rayorig = add(phit, mul(nhit, bias));
			//Color reflection = trace(add(phit, mul(nhit, bias)), refldir, depth + 1);
			//surfaceColor = mul(object->surfaceColor, mul(reflection, fresneleffect));
			resColor = add(resColor, mul(mulColor, object->emissionColor));
			mulColor = mul(mulColor, mul(object->surfaceColor, fresneleffect));
		} else {
			// it's a diffuse object, no need to raytrace any further
			for (unsigned i = 0; i < objects.size(); ++i) {
				if (objects[i]->emissionColor.r > 0) {
					// this is a light
					unsigned int shadow = 0;
					Vec3i lightDirection = sub(
							conv_fp(objects[i]->center, SCENE_COORDINATE_PRECISION), phit);
					normalize(&lightDirection);
					for (unsigned j = 0; j < objects.size(); ++j) {
						if (i != j) {
							unsigned int t0, t1;
							if (intersect(objects[j], add(phit, mul(nhit, bias)),
									lightDirection, &t0, &t1)) {
								shadow = 1;
								break;
							}
						}
					}
					if (!shadow) {
						surfaceColor = add(surfaceColor,
								mul(
										mul(object->surfaceColor,
												std::max(0,
														(int) (dot(nhit, lightDirection) >> FP_PRECISION))),
										objects[i]->emissionColor));
					}
				}
			}
			resColor = add(resColor, mul(mulColor, surfaceColor));
			stop = 1;
		}
		if (stop) {
			break;
		}
	}
	return resColor;
}

bool getNextLine(unsigned int& y_next, unsigned int screenHeight) {
	y_next = y;			//TODO use lock for access to y!!
	if (y < screenHeight) {
		y++;
		return true;
	}
	return false;
}

void traceThread(unsigned int* imageData, std::vector<Sphere*>& objects,
		unsigned int screenWidth, unsigned int screenHeight) {
	int invWidth_2x = (FP_ONE << 1) / screenWidth;
	int invHeight_2x = (FP_ONE << 1) / screenHeight;
	int aspectratio = (screenWidth << FP_PRECISION) / screenHeight;
	int angle = (unsigned int) (0.267949194 * FP_ONE);

	unsigned int y;
	while (getNextLine(y, screenHeight)) {
		for (unsigned int x = 0; x < screenWidth; x++) {
			int xx = (((int) ((((((x << FP_PRECISION) + (FP_ONE >> 1))
					* (long) invWidth_2x) >> FP_PRECISION) - FP_ONE) * angle)
					>> FP_PRECISION) * aspectratio) >> FP_PRECISION;
			int yy = ((FP_ONE
					- ((((y << FP_PRECISION) + (FP_ONE >> 1)) * (long) invHeight_2x)
							>> FP_PRECISION)) * angle) >> FP_PRECISION;
			Vec3i raydir = { xx, yy, -FP_ONE };
			normalize(&raydir);
			Vec3i rayorig = generateVectorI(0, 0, 0);
			Color pixel = trace_it(rayorig, raydir, objects);
			*(imageData + x + y * screenWidth) = (std::min((unsigned int) 255,
					pixel.r)) << 16 | (std::min((unsigned int) 255, pixel.g)) << 8
					| (std::min((unsigned int) 255, pixel.b));
		}
	}
}

void* startTraceThread(void* _startStruct) {
	traceStart* startStruct = (traceStart*) _startStruct;
	traceThread(startStruct->imageData, startStruct->objects,
			startStruct->screenWidth, startStruct->screenHeight);
	return NULL;
}

void Raytracer_pthreads::render(unsigned int* imageData) {
	y = 0;
	traceStart startStruct = { imageData, objects, screenWidth, screenHeight };

	pthread_t threads[THREAD_NUM - 1];
	for (int i = 0; i < THREAD_NUM - 1; i++) {
		pthread_create(&threads[i], NULL, startTraceThread, &startStruct);
	}
	startTraceThread(&startStruct);
	for (int i = 0; i < THREAD_NUM - 1; i++) {
		pthread_join(threads[i], NULL);
	}

	objects[1]->center.z -= 1;  //TODO remove, only for testing
}

