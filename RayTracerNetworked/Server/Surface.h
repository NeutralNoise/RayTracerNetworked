#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED
#include "Material.h"
#include "Vector.h"

class Ray;

class Surface
{
public:
	Surface() {};
	Material m_mat;
	//TODO: remove these.
	float m_dist; //Distance from casting orgin. This is updated every ray.
	Ray* p_lastRay;

	virtual bool Intersect(const Ray &r, float &dist) { return false; };

	virtual Ray Reflect(const Vector &vec, const Vector &dir, const float &dist, const Ray ray);

	virtual Vector CalculateSurfaceNormal();

	void SetMat(const Material &mat) { m_mat = mat; }

	Material GetMat() {	return m_mat; }

};

#endif // !SURFACE_H_INCLUDED