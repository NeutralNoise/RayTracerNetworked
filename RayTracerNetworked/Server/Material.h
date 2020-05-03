#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED
#include "ColourRGBA.h"

struct Material
{
	Material()
	{
		reflect = 1.0f;
		disfuse = ColourRGBA(1.0f, 1.0f, 1.0f, 1.0f);
	}
	Material(const float &r, const float &g, const float &b, const float &a)
	{
		reflect = 1.0f;
		disfuse = ColourRGBA(r, b, b, a);
	}

	Material(const float &r, const ColourRGBA &d)
	{
		reflect = r;
		disfuse = d;
	}

	float reflect;
	ColourRGBA disfuse;
};

#endif // !MATERIAL_H_INCLUDED

