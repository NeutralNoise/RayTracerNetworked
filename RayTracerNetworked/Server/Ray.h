#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED
#include <vector>
#include "Vector.h"
//#include "Surface.h"
#include "Light.h"

class Surface;

class Ray
{
public:
	Ray() {};

	Ray(const Vector &o) {
		m_orgin = o;
	}

	Ray(const Vector &o, const Vector &d) {
		m_orgin = o;
		m_dir = d;
	}

	ColourRGBA Trace(Ray &r, const std::vector<Surface>* quads, const std::vector<Light> *lights, const float &c, float &coef, Vector &result, bool &hitLight);

	Vector m_orgin;
	Vector m_dir;
};

#endif // !RAY_H_INCLUDED