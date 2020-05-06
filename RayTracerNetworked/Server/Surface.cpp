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

SurfaceSphere::SurfaceSphere()
{
	m_radius = 1.0f;
	m_pos = Vector(0.0f, 0.0f, 0.0f);
}

SurfaceSphere::SurfaceSphere(const Vector & pos)
{
	m_radius = 1.0f;
	m_pos = pos;
}

SurfaceSphere::SurfaceSphere(const float & r, const Vector & pos)
{
	m_radius = r;
	m_pos = pos;
}

bool SurfaceSphere::Intersect(const Ray & r, float & dist)
{
	//move everything relitve to the sphere
	Vector LocalSphereRayOrgin = r.m_orgin - m_pos;


	float a = r.m_dir.DotProduct(r.m_dir);
	float b = 2.0f * r.m_dir.DotProduct(LocalSphereRayOrgin);
	//float c = ray.orgin.DotProduct(LocalSphereRayOrgin) - r * r;
	float c = LocalSphereRayOrgin.DotProduct(LocalSphereRayOrgin) - m_radius * m_radius;

	float Denom = 2.0f * a;
	float RootTerm = sqrt(b * b - 4.00f * a * c);
	float d = (b * b - 4.00f * a * c);
	//Check if we are close enough

	if (d > 0.0f) {
		int fdsf = 543;
	}

	if (d < Config::MinHitDistance)
	{
		return false;
	}

	if (RootTerm > Config::Tolerance)
	{
		float tp = (-b + RootTerm) / Denom;
		float tn = (-b - RootTerm) / Denom;

		if (tp == 0 || tn == 0)
		{
			dist = 0;
			return false;
		}

		float t = tp;

		if (tn > Config::MinHitDistance && tn < tp)
		{
			t = tn;
			dist = t;
			return true;
		}
		else if (tp > Config::MinHitDistance)
		{
			dist = t;
			return true;
		}

		return false;
	}

	return false;
}

Ray SurfaceSphere::Reflect(const Vector & vec, const Vector & dir, const float & dist, const Ray & ray)
{
	Vector nextOrgin(ray.m_orgin + dist * ray.m_dir);
	Vector nextNormal = (nextOrgin - this->m_pos).Normalize();
	nextOrgin = nextOrgin + nextNormal * 0.01f;
	return Helpers::SurfaceFunc::Reflect(m_mat, nextOrgin, ray.m_dir, nextNormal);
}

Vector SurfaceSphere::CalculateSurfaceNormal()
{
	return Vector((m_dist * p_lastRay->m_dir + (p_lastRay->m_orgin - m_pos)).Normalize());
}
