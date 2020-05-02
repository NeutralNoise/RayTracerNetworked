#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#include "Vector.h"
#include "ColourRGBA.h"

class Vertex
{
public:
	Vertex() {};

	Vertex(const Vector &v) {
		m_pos = v;
	};

	Vertex(const Vector &v, const ColourRGBA &colour) {
		m_pos = v;
		m_colour = colour;
	};

	~Vertex() {};

	Vector m_pos;
	ColourRGBA m_colour;
};


#endif // !VERTEX_H_INCLUDED


