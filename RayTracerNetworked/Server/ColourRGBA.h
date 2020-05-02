#ifndef COLOUR_RGBA_H_INCLUDED
#define COLOUR_RGBA_H_INCLUDED
#include "Vector.h"

class ColourRGBA
{
public:
	ColourRGBA() {
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	};

	ColourRGBA(const ColourRGBA &c) {
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}

	ColourRGBA(const Vector &v, const float &a)	{
		r = v.m_x;
		g = v.m_y;
		b = v.m_z;
		this->a = a;
	}

	ColourRGBA(const float &r, const float &g, const float &b, const float &a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	~ColourRGBA() {};

	void SetColour(const float &r, const float &g, const float &b, const float &a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Normalize() {

		if (r != 0)
		{
			r /= 255;
		}
		if (g != 0)
		{
			g /= 255;
		}
		if (b != 0)
		{
			b /= 255;
		}
		if (a != 0)
		{
			a /= 255;
		}

	}

	void Scale(const float &s) {
		r *= s;
		g *= s;
		b *= s;
		a *= s;
	}

	void Clamp() {
		if (r > 255)
		{
			r = 255;
		}
		if (g > 255)
		{
			g = 255;
		}
		if (b > 255)
		{
			b = 255;
		}
		if (a > 255)
		{
			a = 255;
		}

		if (r < 0)
		{
			r = 0;
		}
		if (g < 0)
		{
			g = 0;
		}
		if (b < 0)
		{
			b = 0;
		}
		if (a < 0)
		{
			a = 0;
		}
	}

	//Operator overloads
	ColourRGBA operator+(const ColourRGBA &c) {
		ColourRGBA rtn;

		if ((this->r + c.r) > 255)
		{
			rtn.r = 255;
		}
		else if ((this->r + c.r) < 0)
		{
			rtn.r = 0;
		}
		else
		{
			rtn.r = this->r + c.r;
		}



		if ((this->g + c.g) > 255)
		{
			rtn.g = 255;
		}
		else if ((this->g + c.g) < 0)
		{
			rtn.g = 0;
		}
		else
		{
			rtn.g = this->g + c.g;
		}


		if ((this->b + c.b) > 255)
		{
			rtn.b = 255;
		}
		else if ((this->b + c.b) < 0)
		{
			rtn.b = 0;
		}
		else
		{
			rtn.b = this->b + c.b;
		}


		if ((this->a + c.a) > 255)
		{
			rtn.a = 255;
		}
		else if ((this->a + c.a) < 0)
		{
			rtn.a = 0;
		}
		else
		{
			rtn.a = this->a + c.a;
		}

	}

	ColourRGBA& operator+=(const ColourRGBA &c) {
		*this = *this + c;
		return *this;
	}

	ColourRGBA operator/(const float &f) {
		return ColourRGBA(this->r / f, this->g / f, this->b / f, this->a / f);
	}

	ColourRGBA& operator/=(const float &f) {
		*this = *this / f;
		return *this;
	}

	Vector ColourToVector(float &a) {
		a = this->a;
		return Vector(r, g, b);
	}

	float r;
	float g;
	float b;
	float a;

};

#endif //COLOUR_RGBA_H_INCLUDED
