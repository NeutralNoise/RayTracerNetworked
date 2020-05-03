#include "Ray.h"
#include "Config.h"
#include "Surface.h"

ColourRGBA Ray::Trace(Ray &r, const std::vector<Surface>* quads, const std::vector<Light>* lights, const float & c, float & coef, Vector & result, bool & hitLight)
{
	if (c < Config::Ray::MaxBounce) {
		Surface* closestSurface = nullptr;
		Vector normalVec;
		float dist = 0.0f;
		float closestDist = 0.0f;

		for (Surface quad : *quads) {
			//Have we hit something
			if (quad.Intersect(r, dist)) {
				//Find the closest surface.
				if (closestSurface == nullptr) {
					if (dist > 0) {
						closestDist = dist;
						closestSurface = &quad;
					}
				}
				else {
					if (dist > 0 && dist < closestDist)
					{
						closestDist = dist;
						closestSurface = &quad;
					}
				}
			}
		}

		//This is the Closest surface
		if (closestSurface != nullptr) {
			{

				//Bounce off the surface then just fuck off
				//TODO: This is shit bro.
				closestSurface->m_dist = closestDist;
				closestSurface->p_lastRay = &r;

				normalVec = closestSurface->CalculateSurfaceNormal();
				Ray ray = closestSurface->Reflect(r.m_orgin, closestSurface->CalculateSurfaceNormal(), closestDist, r);
				
				//for each light we need to check if there is anything in the way the new ray orgin and the light.
				//check to see if this position has a visable light.
				Ray lsr;
				for(Light ls : *lights)
				{
					bool lightBlocker = false;
					//check if anything is in the way
					for(Surface s : *quads)
					{
						float ld = 0;
						Vector sl = (ls.pos - ray.m_orgin).Normalize();
						lsr = Ray(ray.m_orgin, sl);
						if (s.Intersect(lsr, ld))
						{
							if (ld > 0.01)
							{
								lightBlocker = true;
								break;
							}
						}
					}
					//check if there was a light blocker and if not add lighting to the ray point.
					if (!lightBlocker)
					{
						//Get the distance to the light so we know if its hitting us.
						//float lightPointDist = (float)SurfaceFunc.Vec3Distance(ray.orgin, ls.pos);
						float lambert = lsr.m_dir.DotProduct(closestSurface->CalculateSurfaceNormal()) * coef;
						//float lambert = 1.0f;
						//Lambert disfuseion
						result.m_x += lambert * ls.intesity.r * closestSurface->GetMat().disfuse.r;
						result.m_y += lambert * ls.intesity.g * closestSurface->GetMat().disfuse.g;
						result.m_z += lambert * ls.intesity.b * closestSurface->GetMat().disfuse.b;
					}

					coef *= closestSurface->GetMat().reflect;
					if (coef < 0.0f)
					{
						break;
					}

				}
				ray.Trace(ray, quads, lights, c + 1, coef, result, hitLight);
				return ColourRGBA(result, 255);
			}
		}
		else {
			return ColourRGBA(result, 255);
		}
	}
	return ColourRGBA();
}
