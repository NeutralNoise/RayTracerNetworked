// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "Vector.h"
#include "Material.h"
#include "Helpers.h"
#include "Config.h"
#include "Camera.h"
#include "Surface.h"
#include "Helpers.h"

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n";

    bool finished = false;
	int x = 0;
	int y = 0;

	//Define some colours to use.

	ColourRGBA whiteLight(1.0f, 1.0f, 1.0f, 1.0f);
	ColourRGBA greenLight(255 / 2, 255, 255 / 2, 255);
	ColourRGBA gray(255 / 255 / 2, 255, 255 / 2, 255);

	//Position a light
	Vector lightPos(5, -9, 5);

	//Light mainLight(lightPos, Vector());

	//Some where to store lights.
	std::vector<Light> lights{Light(lightPos, Vector())};

	//Create a camera
	Camera camera;
	//camera.SetPosition(Vector(0.0f, -10.0f, 1.0f));
	camera.SetPosition(Vector(0.0f, -10.0f, 1.0f));
	camera.SetRotation(CameraRotation());
	camera.SetFov(45.0f);

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
	SurfacePlane worldPlane;
	worldPlane.SetMat(mat);

	SurfaceSphere worldSphere;
	worldSphere.SetMat(smat);

	SurfaceSphere worldSphere2(Vector(-2.0f, -2.0f, 2.0f));
	worldSphere2.SetMat(smat2);
	SurfaceSphere worldSphere3(Vector(2.0f, -2.0f, 2.0f));
	worldSphere3.SetMat(smat2);
	SurfaceSphere worldSphere4(Vector(0.0f, 2.0f, 2.0f));
	worldSphere4.SetMat(smat3);

	//Store all the objects

	std::vector<Surface*> Walls{ &worldPlane, &worldSphere, &worldSphere2 , &worldSphere3, &worldSphere4 };

	//Cast the ray
	bool hit = false;
	//bool exit = false;

	float filmDist = 1.0f;

	//Aspect ratio
	float filmW = 1.0f;
	float filmH = 1.0f;

	//Work out the Aspect ratio
	if (Config::Width > Config::Height)
	{
		filmH = filmW * ((float)Config::Height / (float)Config::Width);
	}
	else if (Config::Height > Config::Width)
	{
		filmW = filmH * ((float)Config::Width / (float)Config::Height);
	}

	float halffilmW = 0.5f * filmW;
	float halffilmH = 0.5f * filmH;

	float halfPixW = 0.5f / Config::Width;
	float halfPixH = 0.5f / Config::Height;

	//How much each ray add to the colour of a pixel.
	float RayColourContrib = 1.0f / Config::Ray::RaysPerPixel;

	UInt64 rayCount = 0;
	//Create our render surface.
	Renderer render;
	render.InitRenderer(Config::Width, Config::Height);
	bool running = true;
	bool imageComplete = false;
	while (running) {
		SDL_Event ievent;
		while (SDL_PollEvent(&ievent) != 0) {
			switch (ievent.type) {
			case::SDL_QUIT:
				running = false;
			case::SDL_KEYDOWN:
				switch (ievent.key.keysym.sym)
				{
				case::SDLK_RETURN:
					if (finished || imageComplete) {
						running = false;
					}
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		Vector testVec = (filmDist * camera.GetRotation().CameraZ);
		Vector FilmCenter = camera.GetPosition() - (filmDist * camera.GetRotation().CameraZ);

		//Create a new Ray to Cast
		Ray ray;
		if (!imageComplete) {
			for (int x = 0; x < Config::Width; x++)
			{
				render.LockTexture();
				for (int y = 0; y < Config::Height; y++)
				{

					//Work out where we are casting this ray from.
					float filmX = -1.0f + 2.0f * ((float)x / (float)Config::Width); ;
					float filmY = -1.0f + 2.0f * ((float)y / (float)Config::Height);

					float alpha = 1.0f;
					Vector rayColour;
					bool hitSurface = false;
					//build up our colour
					for (UInt64 r = 0; r < Config::Ray::RaysPerPixel; r++)
					{
						//Jittering AA
						float offX = filmX + Helpers::Rand::RandomBilateral() * halfPixW;
						float offY = filmY + Helpers::Rand::RandomBilateral() * halfPixH;
						Vector filmP = FilmCenter + offX * halffilmW * camera.GetRotation().CameraX + offY * halffilmH * camera.GetRotation().CameraY;

						ray.m_orgin = camera.GetPosition();
						ray.m_dir = (filmP - camera.GetPosition());

						float coef = 1.0f;
						Vector result(0.0f, 0.0f, 0.0f);
						bool hitLight = false;
						if (hitSurface) {
							ray.Trace(ray, &Walls, &lights, 0, coef, result, hitLight);
						}
						else {
							hitSurface = ray.Trace(ray, &Walls, &lights, 0, coef, result, hitLight);
						}
						//rayColour += RayColourContrib * (ray.Trace(ray, Walls, lights, 0, ref coef, ref result, ref hitLight).ColourToVector(ref a));
						rayColour += RayColourContrib * result;
						rayCount++;
					}

					float p = (float)rayCount / (float)((UInt64)(Config::Width * Config::Height) * Config::Ray::RaysPerPixel);
					std::cout << std::to_string(p * 100) << " perenct complete\r";

					ColourRGBA colour(rayColour, alpha);

					//Nothing intersects with this ray so black
					if (!hitSurface)
					{
						//colour = new ColourRGBA(0.0f, 0.0f, 0.0f, 255.0f);
						//colour = ColourRGBA(0.0f, 0.0f, 0.0f, 255.0f);
						colour = Config::Ray::SkyColour;
					}
					else if (hitSurface) {
						colour.Scale(255);
						colour.Clamp();
					}
					else
					{
						//Correct the gamma.
						/*
						colour.r = Lin2srgb(colour.r);
						colour.g = Lin2srgb(colour.g);
						colour.b = Lin2srgb(colour.b);
						*/
						//colour.Normalize();
						colour.Scale(255);
						colour.Clamp();


					}
					render.SetPixel(x, y, colour.r, colour.g, colour.b);
				}
				render.UnlockTexture();

				//We want to drew this each frame for testing
				render.Draw();
				//Check if the image is complete
				if (x == Config::Width - 1) {
					imageComplete = true;
				}
			}
		}
		//render.Draw();

	}
	render.Clean();

	//std::cin.get();
	return 0;
}

