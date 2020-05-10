#include "ThreadFunctions.h"
#include "SDL2/SDL.h"
#include "ThreadManager.h"
#include "TaskManager.h"
#include "Helpers.h"
#include "Camera.h"
#include "World.h"
void TaskPerThread(TaskManager * tm, bool * isRunning)
{
	bool running = true;
	bool hasTask = false;
	Task localTask;
	//TODO remove this
	Camera camera;
	//camera.SetPosition(Vector(0.0f, -10.0f, 1.0f));
	camera.SetPosition(Vector(0.0f, -10.0f, 1.0f));
	camera.SetRotation(CameraRotation());
	camera.SetFov(45.0f);

	while (running) {
		ThreadManager::m_runningMutex.lock();
		running = *isRunning;
		ThreadManager::m_runningMutex.unlock();
		//Make sure we are still running if not close this shit down.
		if (!running) {
			return;
		}
		//Get a new task
		if (!hasTask) {
			if (tm->HasTask()) {
				try
				{
					localTask = tm->GetTask();
				}
				catch (const std::exception&e)
				{
					std::cout << e.what() << "\n";
				}
				
				hasTask = true;
			}
		}
		if (hasTask) {
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

			Vector FilmCenter = camera.GetPosition() - (filmDist * camera.GetRotation().CameraZ);

			//Calculate the area to work in.
			SDL_Rect area;
			Helpers::GetChunkArea(localTask.chunk, localTask.chunk_width, localTask.chunk_height, &area.x, &area.y, &area.w, &area.h);
			Ray ray;
			//Ray trace in calculated area.
			for (int x = area.x; x < area.w; x++) {
				for (int y = area.y; y < area.h; y++) {
					//RayTrace
					bool hitSurface;
					//Work out where we are casting this ray from.
					float filmX = -1.0f + 2.0f * ((float)x / (float)Config::ImageWidth); ;
					float filmY = -1.0f + 2.0f * ((float)y / (float)Config::ImageHeight);

					float alpha = 1.0f;
					Vector rayColour;

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
						hitSurface = ray.Trace(ray, &World::Walls, &World::lights, 0, coef, result, hitLight);
						//rayColour += RayColourContrib * (ray.Trace(ray, Walls, lights, 0, ref coef, ref result, ref hitLight).ColourToVector(ref a));
						rayColour += RayColourContrib * result;
					}

					ColourRGBA colour(rayColour, alpha);

					//Nothing intersects with this ray so black
					if (!hitSurface)
					{
						//colour = new ColourRGBA(0.0f, 0.0f, 0.0f, 255.0f);
						//colour = ColourRGBA(0.0f, 0.0f, 0.0f, 255.0f);
						colour = Config::Ray::SkyColour;
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
					tm->AddCompletedTask(CompletedTask(x, y, colour));
					if (x == area.w - 1) {
						hasTask = false;
					}
				}
			}
		}
	}

}
