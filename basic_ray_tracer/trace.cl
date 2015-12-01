typedef struct {
	float x;
	float y;
	float z;
} Vec3f;

typedef struct {
	Vec3f center;                           /// position of the object

	float radius, radius2;

	Vec3f surfaceColor, emissionColor;      /// surface color and emission (light)
	float reflection;      /// surface reflectivity
} Sphere;

#define MAX_RAY_DEPTH 10

Vec3f generateVector(float x, float y, float z);
Vec3f generateVector3(float val);

float dot_cl(const Vec3f v1, const Vec3f v2);
Vec3f* normalize_cl(Vec3f* v);
float length2(const Vec3f v);
Vec3f sub(const Vec3f v1, const Vec3f v2);
Vec3f add(const Vec3f v1, const Vec3f v2);
Vec3f mulf(const Vec3f v1, float mul);
Vec3f mul(const Vec3f v1, const Vec3f v2);

bool intersect(Sphere* sphere, const Vec3f rayorig, const Vec3f raydir,
		float* t0, float* t1);

float mix_cl(float a, float b, float mix) {
	return b * mix + a * (1 - mix);
}

Vec3f generateVector(float x, float y, float z) {
	Vec3f v = { x, y, z };
	return v;
}

Vec3f generateVector3(float val) {
	Vec3f v = { val, val, val };
	return v;
}

float dot_cl(const Vec3f v1, const Vec3f v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3f* normalize_cl(Vec3f* v) {
	float nor2 = length2(*v);
	if (nor2 > 0) {
		float invNor = 1 / sqrt(nor2);
		v->x *= invNor, v->y *= invNor, v->z *= invNor;
	}
	return v;
}

float length2(const Vec3f v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vec3f sub(const Vec3f v1, const Vec3f v2) {
	Vec3f v = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return v;
}

Vec3f add(const Vec3f v1, const Vec3f v2) {
	Vec3f v = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	return v;
}

Vec3f mulf(const Vec3f v1, float mul) {
	Vec3f v = { v1.x * mul, v1.y * mul, v1.z * mul };
	return v;
}

Vec3f mul(const Vec3f v1, const Vec3f v2) {
	Vec3f v = { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
	return v;
}

bool intersect(Sphere* sphere, const Vec3f rayorig, const Vec3f raydir,
		float* t0, float* t1) {
	Vec3f l = sub(sphere->center, rayorig);
	float tca = dot_cl(l,raydir);
	if (tca < 0)
		return false;
	float d2 = dot_cl(l,l) - tca * tca;
	if (d2 > sphere->radius2)
		return false;
	float thc = sqrt(sphere->radius2 - d2);
	*t0 = tca - thc;
	*t1 = tca + thc;

	return true;
}

Vec3f trace(Sphere* scene, int scene_size, const Vec3f rayorig, const Vec3f raydir,
		const int depth) {
	float tnear = INFINITY;
	const Sphere* object = 0;
	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < scene_size; ++i) {
		float t0 = INFINITY, t1 = INFINITY;
		if (intersect((scene+i), rayorig, raydir, &t0, &t1)) {
			if (t0 < 0)
				t0 = t1;
			if (t0 < tnear) {
				tnear = t0;
				object = (scene+i);
			}
		}
	}
	
	if (!object)
		return generateVector3(3);
        return object->surfaceColor; //TODO rest of algorithm..
	
}

__kernel void example(Sphere* scene, int scene_size, __global unsigned int* frame ){
       int x = get_global_id(0);
       int y = get_global_id(1);
       int screenWidth = get_global_size(0);
       int screenHeight = get_global_size(1);
              
       float invWidth = 1 / (float)(screenWidth);
       float invHeight = 1 / (float)(screenHeight);
       float fov = 30;
       float aspectratio = screenWidth / (float)(screenHeight);
       float angle = tan(M_PI * 0.5 * fov / 180.);
       
       float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
       float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
       Vec3f raydir = { xx, yy, -1 };
       normalize_cl(&raydir);
       
       Vec3f pixel = trace(scene, scene_size, generateVector3(0), raydir, 0);       
       
       *(frame + x + y*screenWidth) = (min(255, (int)(pixel.x*255)) << 16) | (min(255, (int)(pixel.y*255)) << 8) | (min(255, (int)(pixel.z*255)));
}