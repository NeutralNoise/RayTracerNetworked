// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "Vector.h"
#include "Material.h"
#include "Helpers.h"
#include "Config.h"
#include "Camera.h"
#include "Surface.h"
#include "Helpers.h"
#include "ThreadManager.h"
#include "World.h"
#include "TaskManager.h"

int main(int argc, char ** argv)
{
    std::cout << "Hello World!\n";
	TaskManager myTasks;
	ThreadManager tm(&myTasks);
    bool finished = false;
	int x = 0;
	int y = 0;
	World theWorld;
	theWorld.CreateWorld();
	//Create a camera
	Camera camera;
	//camera.SetPosition(Vector(0.0f, -10.0f, 1.0f));
	camera.SetPosition(Vector(0.0f, -10.0f, 1.0f));
	camera.SetRotation(CameraRotation());
	camera.SetFov(45.0f);

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
	time_t startTime = time(NULL);
	int maxChunks = Helpers::MaxChunks(Config::ImageWidth, Config::ImageHeight, Config::ChunkWidth, Config::ChunkHeight);
	bool generatedTasks = false;
	int insertCount = 0;
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
			case::SDL_MOUSEMOTION:
				//std::cout << "MouseMove\n";
				break;
			default:
				break;
			}
		}
		//Generate new Tasks;
		if (!generatedTasks) {

			for (int t = 0; t < maxChunks; t++) {
				myTasks.AddTask(Task(t, Config::ChunkWidth, Config::ChunkHeight));
			}
			//Create some new threads.
			for (int i = 0; i < Config::MaxThreadCount; i++) {
				tm.CreateThread();
			}
			generatedTasks = true;
		}

		if (!imageComplete) {
			if (myTasks.HasCompletedTask()) {
				CompletedTask ct = myTasks.GetCompletedTask();
				render.LockTexture();

				render.SetPixel(ct.x, ct.y, ct.colour.r, ct.colour.g, ct.colour.b);
				if (insertCount > (Config::ChunkWidth * Config::ChunkHeight)) {
					render.UnlockTexture();
					render.Draw();
					render.LockTexture();
					insertCount = 0;
				}
				else {
					insertCount++;
				}
			}
		}

		if (!myTasks.HasTask()) {
			if (!imageComplete) {
				if (!myTasks.HasCompletedTask()) {
					//imageComplete = true;
					render.UnlockTexture();
					std::cout << "Image Completed\n";
					std::cout << time(NULL) - startTime << "\n";
					render.Draw();
				}
			}
			
		}

		//render.Draw();
	}
	tm.JoinAllThreads();
	render.Clean();
	theWorld.DestroyWorld();
	//std::cin.get();
	return 0;
}

