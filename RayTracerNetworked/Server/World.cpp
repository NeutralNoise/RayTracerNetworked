#include "World.h"
#include "Vector.h"
#include "Surface.h"
#include "Material.h"

void World::CreateWorld()
{
	Vector lightPos(5, -9, 5);
	lights.push_back(Light(lightPos, Vector()));

	//Define some colours to use.
	ColourRGBA whiteLight(1.0f, 1.0f, 1.0f, 1.0f);
	ColourRGBA greenLight(255 / 2, 255, 255 / 2, 255);
	ColourRGBA gray(255 / 255 / 2, 255, 255 / 2, 255);

	//Create some Materials
	Material mat;
	mat.disfuse = ColourRGBA(255.0f, 125.0f, 136.0f, 255.0f);
	//mat.disfuse = new ColourRGBA(1.0f, 1.0f, 1.0f, 1.0f);
	mat.disfuse.Normalize();
	mat.reflect = 0.1f;

	Material smat;
	smat.disfuse = ColourRGBA(0.0f, 0.0f, 1.0f, 1.0f);
	smat.reflect = 0.9f;

	Material smat2;
	smat2.disfuse = ColourRGBA(0.5f, 1.0f, 0.5f, 1.0f);
	//smat2.reflect = 0.5f;

	Material smat3;
	smat3.disfuse = ColourRGBA(0.5f, 0.5f, 0.5f, 1.0f);

	//Create objects to place in the world.
	SurfacePlane* worldPlane = new SurfacePlane;
	worldPlane->SetMat(mat);

	SurfaceSphere *worldSphere = new SurfaceSphere;
	worldSphere->SetMat(smat);

	SurfaceSphere *worldSphere2 = new SurfaceSphere(Vector(-2.0f, -2.0f, 2.0f));
	worldSphere2->SetMat(smat2);
	SurfaceSphere *worldSphere3 = new SurfaceSphere(Vector(2.0f, -2.0f, 2.0f));
	worldSphere3->SetMat(smat2);
	SurfaceSphere *worldSphere4 = new SurfaceSphere(Vector(0.0f, 2.0f, 2.0f));
	worldSphere4->SetMat(smat3);

	Walls.push_back(worldPlane);
	Walls.push_back(worldSphere);
	Walls.push_back(worldSphere2);
	Walls.push_back(worldSphere3);
	Walls.push_back(worldSphere4);

}

void World::DestroyWorld()
{
	for (size_t i = 0; i < Walls.size(); i++) {
		delete Walls[i];
		Walls[i] = nullptr;
	}
}

std::vector<Surface*> World::Walls;
std::vector<Light> World::lights;