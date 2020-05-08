#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include "ColourRGBA.h"
#include "Vector.h"
#include "TypeDef.h"

struct Config
{
public:

	struct Ray
	{
		static UInt64 RaysPerPixel;
		static UInt64 MaxBounce;
		static ColourRGBA ColourWhite;
		static ColourRGBA Nothing;
		static ColourRGBA SkyColour;
	};
	static int Width;
	static int Height;
	static int ImageWidth;
	static int ImageHeight;

	static int ChunkWidth;
	static int ChunkHeight;

	static float Tolerance;
	static Vector Orgin;
	static Vector UP;
	static float MinTolerance;
	static float MinHitDistance;//Clipingplan.

};

#endif // !CONFIG_H_INCLUDED

