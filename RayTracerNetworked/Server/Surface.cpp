#include "Surface.h"
#include "Ray.h"
#include "Config.h"
#include "Helpers.h"

Ray Surface::Reflect(const Vector & vec, const Vector & dir, const float & dist, const Ray &ray)
{
	return Ray();
}

Vector Surface::CalculateSurfaceNormal()
{
	return Vector();
}

SurfacePlane::SurfacePlane()
{
	m_d = 0;
	m_norm = Config::UP;
}

SurfacePlane::SurfacePlane(const float & d, const Vector & n)
{
	this->m_d = d;
	m_norm = n;
}

SurfacePlane::~SurfacePlane()
{
}

bool SurfacePlane::Intersect(const Ray & r, float & dist)
{
	//Check if the ray hits the plane
//for the ray
//f(t) = ro + t * rd
// ro is ray orgin
// rd is ray direction
// where t is marching down the ray dir from the orgin

//N(ro + t * rd) + d = 0;
	float Denom = m_norm.DotProduct(r.m_dir);
	if ((Denom < -Config::Tolerance) || (Denom > Config::Tolerance))
	{
		dist = (-m_d - m_norm.DotProduct(r.m_orgin)) / Denom;
		return true;
	}
	return false;
}

Ray SurfacePlane::Reflect(const Vector & vec, const Vector & dir, const float & dist, const Ray &ray)
{
	Ray tmpRay = ray;
	float tmpf = dist;
	Vector nextOrgin = Vector(tmpRay.m_orgin + dist * tmpRay.m_dir );
	//Vector nextOrgin = dist * ray.dir;
	Vector nextNormal = m_norm;
	
	return Helpers::SurfaceFunc::Reflect(m_mat, nextOrgin, ray.m_dir, nextNormal);
}

Vector SurfacePlane::CalculateSurfaceNormal()
{
	return m_norm;
}
