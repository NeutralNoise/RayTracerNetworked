#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <vector>
#include "Light.h"
class Surface;

class World
{

public:
	void CreateWorld();
	void DestroyWorld();
	static std::vector<Surface*> Walls;
	static std::vector<Light> lights;
};

#endif //WORLD_H_INCLUDED
