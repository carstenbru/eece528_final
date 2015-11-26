#ifndef RAYOBJECT_HPP_
#define RAYOBJECT_HPP_

class RayObject {
public:
	RayObject(const Vec3f &c, const Vec3f &sc, const float &refl = 0,
			const float &transp = 0, const Vec3f &ec = 0) :
			center(c), surfaceColor(sc), emissionColor(ec), transparency(transp), reflection(
					refl) {
	}
	;
	virtual ~RayObject() {
	}
	;
	virtual bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0,
			float &t1) const {
		return false;
	}
	;

	Vec3f center;                           /// position of the object

	Vec3f surfaceColor, emissionColor;      /// surface color and emission (light)
	float transparency, reflection;      /// surface transparency and reflectivity
};

#endif
