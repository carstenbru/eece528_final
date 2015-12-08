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
Color mul(const Color v1, float mul);
Color mul(const Color v1, const Color v2);



float dot(const Vec3f v1, const Vec3f v2);
Vec3f* normalize(Vec3f* v);
float length2(const Vec3f v);
Vec3f sub(const Vec3f v1, const Vec3f v2);
Vec3f add(const Vec3f v1, const Vec3f v2);
Vec3f mul(const Vec3f v1, float mul);
Vec3f mul(const Vec3f v1, const Vec3f v2);

/*template<typename T>
class Vec3 {
public:
	T x, y, z;
	Vec3() :
			x(T(0)), y(T(0)), z(T(0)) {
	}
	Vec3(T xx) :
			x(xx), y(xx), z(xx) {
	}
	Vec3(T xx, T yy, T zz) :
			x(xx), y(yy), z(zz) {
	}
	Vec3& normalize() {
		T nor2 = length2();
		if (nor2 > 0) {
			T invNor = 1 / sqrt(nor2);
			x *= invNor, y *= invNor, z *= invNor;
		}
		return *this;
	}
	Vec3<T> operator *(const T &f) const {
		return Vec3<T>(x * f, y * f, z * f);
	}
	Vec3<T> operator *(const Vec3<T> &v) const {
		return Vec3<T>(x * v.x, y * v.y, z * v.z);
	}
	T dot(const Vec3<T> &v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	Vec3<T> operator -(const Vec3<T> &v) const {
		return Vec3<T>(x - v.x, y - v.y, z - v.z);
	}
	Vec3<T> operator +(const Vec3<T> &v) const {
		return Vec3<T>(x + v.x, y + v.y, z + v.z);
	}
	Vec3<T>& operator +=(const Vec3<T> &v) {
		x += v.x, y += v.y, z += v.z;
		return *this;
	}
	Vec3<T>& operator *=(const Vec3<T> &v) {
		x *= v.x, y *= v.y, z *= v.z;
		return *this;
	}
	Vec3<T> operator -() const {
		return Vec3<T>(-x, -y, -z);
	}
	T length2() const {
		return x * x + y * y + z * z;
	}
	T length() const {
		return sqrt(length2());
	}
	friend std::ostream & operator <<(std::ostream &os, const Vec3<T> &v) {
		os << "[" << v.x << " " << v.y << " " << v.z << "]";
		return os;
	}
};

typedef Vec3<float> Vec3f;*/

#endif
