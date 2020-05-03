#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
#include "Vector.h"
#include "ColourRGBA.h"

class Light
{
public:
	Light()
	{
		pos = Vector(0, 0, 0);
		dir = Vector(0, 0, 0);
		intesity = ColourRGBA(1.0f, 1.0f, 1.0f, 1.0f);
	}

	Light(const Vector &pos, const Vector &dir)
	{
		this->pos = pos;
		this->dir = dir;
		intesity = ColourRGBA(1.0f, 1.0f, 1.0f, 1.0f);
	}

	Light(const Vector &pos, const Vector &dir, const ColourRGBA &intesity)
	{
		this->pos = pos;
		this->dir = dir;
		this->intesity = intesity;
	}

	Vector pos;
	Vector dir;
	ColourRGBA intesity;
};

#endif // !LIGHT_H_INCLUDED

