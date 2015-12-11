
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

typedef struct {
    Vec3i center;                           /// position of the object
    
    unsigned int radius;
    int radius2;
    
    Color surfaceColor, emissionColor;      /// surface color and emission (light)
    unsigned int reflection;      /// surface reflectivity
    
} Sphere;

#define MAX_RAY_DEPTH 10
#define FP_PRECISION (16)
#define SCENE_COORDINATE_PRECISION 0
#define FP_ONE (1<<FP_PRECISION)
#define UNSIGNED_MAX 0xFFFFFFFF


Color generateColorI(unsigned int r, unsigned int g, unsigned int b);
Vec3i generateVectorI(int x, int y, int z);

Color addc(const Color v1, const Color v2);
Color mulci(const Color v1, int mul);
Color mulc(const Color v1, const Color v2);

Vec3i add(const Vec3i v1, const Vec3i v2);
Vec3i sub(const Vec3i v1, const Vec3i v2);
Vec3i muli(const Vec3i v1, int mul);
Vec3i conv_fp(const Vec3i v1, int cur_precision);
long int dot_cl(const Vec3i v1, const Vec3i v2);
Vec3i* normalize_cl(Vec3i* v);
long int length2(const Vec3i v);

bool intersect(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir,
		unsigned int* t0, unsigned int* t1);

Color generateColorI(unsigned int r, unsigned int g, unsigned int b) {
    Color c = { r, g, b };
    return c;
}

Vec3i generateVectorI(int x, int y, int z) {
	Vec3i v = { x, y, z };
	return v;
}

Color addc(const Color v1, const Color v2) {
    Color v = { v1.r + v2.r, v1.g + v2.g, v1.b + v2.b };
    return v;
}

Color mulci(const Color v1, int mul) {
    Color v = { (v1.r * mul) >> FP_PRECISION, (v1.g * mul) >> FP_PRECISION, (v1.b* mul) >> FP_PRECISION };
    return v;
}

Color mulc(const Color v1, const Color v2) {
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
	Vec3i v = { (v1.x * (long) mul) >> FP_PRECISION, (v1.y
			* (long) mul) >> FP_PRECISION, (v1.z * (long) mul) >> FP_PRECISION };
	return v;
}

Vec3i* normalize_cl(Vec3i* v) {  //TODO do calulation in fp arithmetic
	float nor2 = length2(*v) / (float) FP_ONE;
	if (nor2 > 0) {
		float invNor = 1 / sqrt(nor2);
		v->x *= invNor, v->y *= invNor, v->z *= invNor;
	}
	return v;
}

long int length2(const Vec3i v) {
	return (v.x * (long) v.x + v.y * (long) v.y + v.z * (long) v.z)
			>> (FP_PRECISION);
}

long int dot_cl(const Vec3i v1, const Vec3i v2) {
	return ((long)v1.x * (long)v2.x +(long) v1.y * (long)v2.y + (long)v1.z * (long)v2.z);
}

bool intersect(Sphere* sphere, const Vec3i rayorig, const Vec3i raydir, unsigned int* t0, unsigned int* t1) {
	Vec3i l = sub(conv_fp(sphere->center, SCENE_COORDINATE_PRECISION), rayorig);
	int tca = dot_cl(l,raydir) >> FP_PRECISION;
	if (tca < 0)
		return false;
	long int d2 = (dot_cl(l,l) >> FP_PRECISION) - (((long)tca * tca) >> FP_PRECISION);
	if (d2 > (((long)sphere->radius2) << FP_PRECISION))
		return false;
	int thc = sqrt((float)sphere->radius2 - d2/65536.0f) * FP_ONE; //TODO srqt in int/fp!
	*t0 = tca - thc;
	*t1 = tca + thc;

	return true;
}

Color trace(Sphere* scene, int scene_size, Vec3i rayorig, Vec3i raydir) {
	Color resColor = generateColorI(0, 0, 0);
	Color mulColor = generateColorI(255, 255, 255);
	int stop = 0;
	for (int rec_depth = 0; rec_depth <= MAX_RAY_DEPTH; rec_depth++) {
		unsigned int tnear = UNSIGNED_MAX;
		const Sphere* object = 0;
		// find intersection of this ray with the sphere in the scene
		for (unsigned i = 0; i < scene_size; ++i) {
			unsigned int t0 = UNSIGNED_MAX, t1 = UNSIGNED_MAX;
			if (intersect((scene+i), rayorig, raydir, &t0, &t1)) {
				if (t0 < 0)
					t0 = t1;
				if (t0 < tnear) {
					tnear = t0;
					object = scene+i;
				}
			}
		}
		// if there's no intersection return black or background color
		if (!object) {
			resColor = addc(resColor, mulci(mulColor, 3 * FP_ONE));
			break;
		}

		Color surfaceColor = object->surfaceColor;  // color of the ray/surface of the object intersected by the ray
		Vec3i phit = mul(add(rayorig, raydir), tnear);  // point of intersection
		Vec3i nhit = sub(phit, conv_fp(object->center, SCENE_COORDINATE_PRECISION));  // normal at the intersection point

		normalize_cl(&nhit);  // normalize normal direction
		// If the normal and the view direction are not opposite to each other
		// reverse the normal direction. That also means we are inside the sphere so set
		// the inside bool to true. Finally reverse the sign of IdotN which we want
		// positive.
		unsigned int bias = 65;  //1e-4;  // add some bias to the point from which we will be tracing
		if (dot_cl(raydir, nhit) > 0)
			nhit = sub(generateVectorI(0, 0, 0), nhit);  //invert normal if necessary
		if ((object->reflection > 0) && rec_depth < MAX_RAY_DEPTH) {
			int facingratio = (-dot_cl(raydir, nhit) >> FP_PRECISION);
			// change the mix value to tweak the effect
			unsigned int fresneleffect = ((unsigned int) (0.1 * FP_ONE)
					+ (unsigned int) (0.9 * FP_ONE)
							* (pow((FP_ONE - facingratio) / (float) FP_ONE, 3)));  //TODO pow in fixed-point
			// compute reflection direction (not need to normalize because all vectors
			// are already normalized)
			raydir = mul(sub(raydir, nhit), 2 * dot_cl(raydir, nhit) >> FP_PRECISION);
			normalize_cl(&raydir);
			rayorig = add(phit, mul(nhit, bias));
			//Color reflection = trace(add(phit, mul(nhit, bias)), refldir, depth + 1);
			//surfaceColor = mul(object->surfaceColor, mul(reflection, fresneleffect));
			resColor = addc(resColor, mulc(mulColor, object->emissionColor));
			mulColor = mulc(mulColor, mulci(object->surfaceColor, fresneleffect));
		} else {
			// it's a diffuse object, no need to raytrace any further
			for (unsigned i = 0; i < scene_size; ++i) {
				if ((scene+i)->emissionColor.r > 0) {
					// this is a light
					unsigned int shadow = 0;
					Vec3i lightDirection = sub(
							conv_fp((scene+i)->center, SCENE_COORDINATE_PRECISION), phit);
					normalize_cl(&lightDirection);
					for (unsigned j = 0; j < scene_size; ++j) {
						if (i != j) {
							unsigned int t0, t1;
							if (intersect(scene+j, add(phit, mul(nhit, bias)),
									lightDirection, &t0, &t1)) {
								shadow = 1;
								break;
							}
						}
					}
					if (!shadow) {
						surfaceColor = addc(surfaceColor,
								mulc(
										mulci(object->surfaceColor,
												max(0,
														(int) (dot_cl(nhit, lightDirection) >> FP_PRECISION))),
										(scene+i)->emissionColor));
					}
				}
			}
			resColor = addc(resColor, mulc(mulColor, surfaceColor));
			stop = 1;
		}
		if (stop) {
			break;
		}
	}
	return resColor;
}

__kernel void trace_cl(Sphere* scene, int scene_size, __global unsigned int* frame ){
    int x = get_global_id(0);
    int y = get_global_id(1);
    int screenWidth = get_global_size(0);
    int screenHeight = get_global_size(1);
    
    int invWidth_2x = (FP_ONE << 1) / screenWidth;
    int invHeight_2x = (FP_ONE << 1) / screenHeight;
    int aspectratio = (screenWidth << FP_PRECISION) / screenHeight;
    int angle = (unsigned int) (0.267949194 * FP_ONE);
    
    int xx = (((int) ((((((x << FP_PRECISION) + (FP_ONE >> 1))
    * (long) invWidth_2x) >> FP_PRECISION) - FP_ONE) * angle)
    >> FP_PRECISION) * aspectratio) >> FP_PRECISION;
    int yy = ((FP_ONE
    - ((((y << FP_PRECISION) + (FP_ONE >> 1)) * (long) invHeight_2x)
    >> FP_PRECISION)) * angle) >> FP_PRECISION;
    Vec3i raydir = { xx, yy, -FP_ONE };
    normalize_cl(&raydir);
    Vec3i rayorig = generateVectorI(0, 0, 0);
    
    Color pixel = trace(scene, scene_size, rayorig, raydir);      
    
    *(frame + x + y*screenWidth) = (min((unsigned int)255, pixel.r) << 16) | (min((unsigned int)255, pixel.g) << 8) | (min((unsigned int)255, pixel.b));
}
